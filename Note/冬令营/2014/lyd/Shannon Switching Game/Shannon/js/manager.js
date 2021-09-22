

$(function(){

  var prob = document.location.search.substring(1) || "advanced3";
  var mode = document.location.hash.substring(1);

  var hist = [];
  var n = $("#field")[0];
  var width = $(n).innerWidth();
  var height = $(n).innerHeight();
  var R = Raphael(n,width,height);

  var ui = null;
  var analyzer = new Analyzer();
  GraphUI.fn.load("prob/"+prob+".json",onLoadProb);

  function onLoadProb(o)
  {
    ui = new GraphUI(o).fit(n).attach(R,onAction);
    analyzer.analyze(ui);
    phase(mode);
  }

  function pushHist()
  {
    hist.push(ui.strip());

    if(hist.length==1)
    {
      $("#undo").removeClass("invalid");
      $("#undo").click(popHist);
    }
  }

  function popHist()
  {
    if(ui && ui.inactiveCount > 0)
      return;

    if(history.length>0)
    {
      ui.subst(hist.pop());
      analyzer.analyze(ui);
    }

    if(hist.length==0)
    {
      $("#undo").unbind();
      $("#undo").addClass("invalid");
    }
  }

  function onAction(ui,e)
  {
    if(mode=="short")
    {
      analyzer.analyze(ui);
      if(!analyzer.winner)
      {
        pushHist();
        ui.contraction([e],function(){
          phase("cut")
          analyzer.analyze(ui);
          if(analyzer.winner=="short")
          {
            onPlayerWin();
            return;
          }

          ui.inactiveCount++;
          setTimeout(function(){
            var i = Math.floor(Math.random()*analyzer.recommended.length);
            ui.deletion([ui.E[analyzer.recommended[i].id]],function(){
              phase("short")
              analyzer.analyze(ui);
              if(analyzer.winner=="cut")
              {
                onPlayerLose();
                return;
              }
              ui.inactiveCount--;
            });
          },500);
        });
      }
    }
    else if(mode=="cut")
    {
      analyzer.analyze(ui);
      if(!analyzer.winner)
      {
        pushHist();
        ui.deletion([e],function(){
          phase("short");
          analyzer.analyze(ui);
          if(analyzer.winner=="cut")
          {
            onPlayerWin();
            return;
          }

          ui.inactiveCount++;
          setTimeout(function(){
            var i = Math.floor(Math.random()*analyzer.recommended.length);
            ui.contraction([ui.E[analyzer.recommended[i].id]],function(){
              phase("cut");
              analyzer.analyze(ui);
              if(analyzer.winner=="short")
              {
                onPlayerLose();
                return;
              }
              ui.inactiveCount--;
            });
          },500);
        });
      }
    }
  }

  (function(){
    var tree = false;
    $("#tree").click(function(){
      $("#treeMode")[0].href = !tree?"css/tree.css":"";
      tree = !tree;
      return false;
    });
  })();

  (function(){
    var cheat = false;
    $("#cheat").click(function(){
      $("#cheatMode")[0].href = !cheat?"css/cheat.css":"";
      cheat = !cheat;
      return false;
    });
  })();

  (function(){
    var recom = false;
    $("#recommended").click(function(){
      $("#recommendedMode")[0].href = !recom?"css/recommended.css":"";
      recom = !recom;
      return false;
    });
  })();

  $("#restart").click(function(){
    if(hist.length!=0)
    {
      hist = [hist[0]];
      popHist();
    }
    //document.location.reload();
    return false;
  });

  function phase(p)
  {
    $(".phase li").removeClass("active");
    $("#"+p).addClass("active");
  }

  function onPlayerWin(){alert("You Win!");window.history.back();}
  function onPlayerLose(){alert("You Lose!");document.location.reload();}
});

function Analyzer(){}
Analyzer.prototype = {
  T: [],
  U: [],

  map: {},
  component: {},
  cutEdge: [],
  shortEdge: [],
  neutralEdge: [],
  recommended: null,

  winner: null,

  analyze : function(ui)
  {
    var G = this.compile(ui);
    var omitSP = $.grep(asArray(G.E),function(x){return x.id!="special";});

    if(G.E["special"].head.id==G.E["special"].tail.id)
    {
      this.winner = "short";
      return;
    }
    else
    {
      var H = restriction(G,omitSP);
      if(shortestPath(H,
           [H.V[G.E["special"].head.id]],
           [H.V[G.E["special"].tail.id]])==null)
      {
        this.winner = "cut";
        return;
      }
    }
    this.winner = null;

    var cc = decompose(G,this.T,this.U);

    this.T = cc.T;
    this.U = cc.U;

    this.shortEdge = cc.component[cc.lower];
    this.cutEdge = cc.component[cc.upper];
    this.neutralEdge = [];
    for(var i in cc.component)
      if(i!=cc.lower && i!=cc.upper)
        this.neutralEdge = this.neutralEdge.concat(cc.component[i]);

    $.each(ui.E,function(){this.repr.setClass("edge");});

    if(cc.map["special"]==cc.lower)
    {// short game
      var H = restriction(G,intersection(this.shortEdge,omitSP));
      var sp = shortestPath(H,[H.V[ui.special.head.id]],[H.V[ui.special.tail.id]]).E;
      sp = pullbackE(G,sp);

      H = restriction(G,omitSP);
      var mc = mincut(H,H.V[ui.special.head.id],H.V[ui.special.tail.id]).E;
      mc = pullbackE(G,mc);

      this.recommended = intersection(sp,mc);
    }
    else if(cc.map["special"]==cc.upper)
    {// cut game
      var H = restriction(G,omitSP);
      var sp = shortestPath(H,[H.V[ui.special.head.id]],[H.V[ui.special.tail.id]]).E;
      sp = pullbackE(G,sp);

      var c = contraction(G,setminus(omitSP,this.cutEdge));
      H = c.G;
      var mc = mincut(H,H.V[c.map[ui.special.head.id]],H.V[c.map[ui.special.tail.id]]).E;
      mc = pullbackE(G,mc);

      this.recommended = intersection(sp,mc);
    }
    else
    {
      this.recommended = $.grep(cc.component[cc.map["special"]],function(x){return x.id!="special";});
    }

    $.each(this.recommended,function(){
      ui.E[this.id].repr.addClass("recommended");
    });

    $.each(this.T,function(){
      if(this.id!="special")
        ui.E[this.id].repr.addClass("left");
    });
 
    $.each(this.U,function(){
      if(this.id!="special")
        ui.E[this.id].repr.addClass("right");
    });

    $.each(this.shortEdge,function(){
      if(this.id!="special")
        ui.E[this.id].repr.addClass("short");
    });

    $.each(this.cutEdge,function(){
      if(this.id!="special")
        ui.E[this.id].repr.addClass("cut");
    });

    $.each(this.neutralEdge,function(){
      if(this.id!="special")
        ui.E[this.id].repr.addClass("neutral");
    });
  },

  compile: function(ui)
  {
    var V = {};
    var E = {};

    $.each(ui.V,function(){
      V[this.id] = {
        id: this.id,
        inc: []
      };
    });

    $.each(ui.E,function(){
      var e = E[this.id] = {
        id: this.id,
        head: V[this.head.id],
        tail: V[this.tail.id],
      };
      e.tail.inc.push(e);
      e.head.inc.push(e);
    });

    var e = E["special"] = {
      id: "special",
      head: V[ui.special.head.id],
      tail: V[ui.special.tail.id],
    };
    e.tail.inc.push(e);
    e.head.inc.push(e);
    return {V:V,E:E};
  }
};

