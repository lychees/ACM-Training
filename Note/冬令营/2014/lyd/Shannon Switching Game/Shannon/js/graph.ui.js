
function TODO(s){throw "TODO: "+s;}

function GraphUI(o)
{
  var ui = this;
  ui.inactiveCount = 0;

  var V = this.V = {};
  $.each(o.V,function(){
    V[this.id] = {
      id: this.id,
      x: this.x,
      y: this.y,
      onMove: []
    };
  });

  var E = this.E = {};
  $.each(o.E,function(){
    var e  = {
        id: this.id,
        head: V[this.head],
        tail: V[this.tail]
   };
   if(this.id==="special")
     ui.special = e;
   else
     E[e.id] = e;
  });
}
GraphUI.prototype = {
  V : {},
  E : {},
  w : 100,
  h : 100,
  r : 10,
  raphael : null,
  inactiveCount : 0,

  sanitize : function(o){
    var i = 0;
    var V = {};
    var E = {};
    var vMap = {};
    $.each(o["V"],function(){
      if(this===undefined ||
         this["id"] === undefined ||
         vMap[this["id"]] !== undefined ||
         this["x"] === undefined ||
         this["y"] === undefined)
        return;

      vMap[this["id"]] = i;
      V[i] = {
        id: i,
        x: parseFloat(this["x"]),
        y: parseFloat(this["y"])
      };
      if(!isFinite(V[i].x))V[i].x = .0;
      if(!isFinite(V[i].y))V[i].y = .0;
      ++i;
    });

    i = 0;
    $.each(o["E"],function(){
      if(this===undefined ||
         this["head"] === undefined ||
         vMap[this["head"]] === undefined ||
         this["tail"] === undefined ||
         vMap[this["tail"]] === undefined)
        return;

      var e = {
        id: (this["id"]==="special"?"special":i++),
        head: vMap[this["head"]],
        tail: vMap[this["tail"]]
      };
      E[e.id] = e;
    });
    return {V:V,E:E};
  },

  fit : function(){
    if(arguments.length == 1)
    {
      var n = $(arguments[0]);
      return this.fit(n.innerWidth(),n.innerHeight());
    }
    else if(arguments.length == 2)
    {
      var w = this.w = arguments[0];
      var h = this.h = arguments[1];

      var minX=Infinity, maxX=-Infinity;
      var minY=Infinity, maxY=-Infinity;
      $.each(this.V,function(){
        minX = Math.min(minX,this.x);
        maxX = Math.max(maxX,this.x);
        minY = Math.min(minY,this.y);
        maxY = Math.max(maxY,this.y);
      });

      minX -= 0.05*w;
      maxX += 0.05*w;
      minY -= 0.05*h;
      maxY += 0.05*h;

      $.each(this.V,function(){
        this.x = (this.x-minX)*w/(maxX-minX+1);
        this.y = (this.y-minY)*h/(maxY-minY+1);
      });
      return this;
    }
  },

  load : function(url,callback){
    return $.getJSON(url,function(o){
      if(callback)callback(GraphUI.fn.sanitize(o));
    });
  },

  strip : function(){
    var V = {};
    $.each(this.V,function(){
      V[this.id] = {
        id: this.id,
        x: this.x,
        y: this.y,
      };
    });

    var E = {};
    $.each(this.E,function(){
      E[this.id]  = {
          id: this.id,
          head: this.head.id,
          tail: this.tail.id
     };
    });

    E["special"] = {
      id: "special",
      head: this.special.head.id,
      tail: this.special.tail.id
    };
    return {V:V,E:E};
  },

  attach : function(R,onAction){
    var ui = this;
    //var R = ui.raphael = Raphael(n,ui.w,ui.h);
    ui.raphael = R;
    ui.onAction = onAction;
    GraphUI.fn.buildSibl(ui.E);

    $.each(ui.E,function(){
      var d = GraphUI.fn.calcPath(this);

      this.reprShadow = R.path(d);
      this.reprShadow.addClass("edge","shadow");
      this.repr = R.path(d);
      this.repr.addClass("edge");
    });

    $.each(ui.V,function(){
      this.repr = R.circle(this.x,this.y,ui.r);
      this.repr.addClass("vertex");
    });

    if(ui.special)
    {
      ui.special.head.repr.addClass("terminal");
      ui.special.tail.repr.addClass("terminal");
    }

    ui.bindEvent();
    return this;
  },

  clear: function(){
    var trash = [];
    this.unbindEvent();
    $.each(this.V,function(){
      this.repr.hide();
      trash.push(this.repr);
    });
    $.each(this.E,function(){
      this.repr.hide();
      this.reprShadow.hide();
      trash.push(this.repr);
      trash.push(this.reprShadow);
    });
    V = {};
    E = {};

    setTimeout(function(){
      $.each(trash,function(){this.remove()});
    },1000);
  },

  buildSibl : function(E){
    var siblMap = {};
    $.each(E,function(){
      var t = this.head.id;
      var h = this.tail.id;

      if(!siblMap[t])siblMap[t] = {};
      if(!siblMap[h])siblMap[h] = {};
      if(!siblMap[t][h])
        siblMap[t][h] = siblMap[h][t] = [];
      siblMap[t][h].push(this);
      this.sibl = siblMap[t][h];
    });
  },

  calcPath: function(e)
  {
    var h = e.head, t = e.tail;

    if(e.sibl.length==1)
      return ["M",t.x,t.y,"L",h.x,h.y];;

    var h = e.head, t = e.tail;
    var ci = 2*$.inArray(e,e.sibl)-e.sibl.length+1;
    if(h.id<t.id)
      ci = -ci;

    var x1=t.x, y1=t.y;
    var x2=h.x, y2=h.y;

    var dx = x2-x1;
    var dy = y2-y1;
    var d = Math.sqrt(dx*dx+dy*dy);

    if(d!=0)
    {
      dx = dx*20*ci/d;
      dy = dy*20*ci/d;
      return ["M",x1,y1,
              "C",x1+dy,y1-dx,
                  x2+dy,y2-dx,
                  x2,y2];
    }
    else
    {
      return ["M",x1,y1];
    }
  },

  unbindEvent: function(){
    var ui = this;
    ui.inactiveCount++;

    $.each(ui.E,function(){
      $(this.repr.node).unbind();
      $(this.reprShadow.node).unbind();
    });

    $.each(ui.V,function(){
      $(this.repr.node).unbind();
      this.onMove = [];
    });

    ui.inactiveCount--;
  },

  bindEvent : function(){
    var ui = this;
    ui.inactiveCount++;

    $.each(ui.E,function(){
      var e = this;
      e.head.onMove.push(redraw);
      e.tail.onMove.push(redraw);

      function redraw()
      {
        e.reprShadow.attr({"path":ui.calcPath(e)});
        e.repr.attr({"path":ui.calcPath(e)});
      }

      $(e.repr.node).mousedown(function(){return false;});
      $(e.reprShadow.node).mousedown(function(){return false;});

      $(e.repr.node).dblclick(function(){
        if(ui.inactiveCount > 0)
          return false;

        if(ui.onAction)
          ui.onAction(ui,e);
        return false;
      });
    });

    $.each(ui.V,function(){
      var v = this;
      $(this.repr.node).mousedown(function(e){
        if(ui.inactivecount > 0)
          return false;
        ui.inactiveCount++;

        var c = ui.raphael.circle(v.x,v.y,ui.r);

        var ox = e.clientX;
        var oy = e.clientY;
        var nx = v.x;
        var ny = v.y;

        c.addClass("vertex","dragging");

        $(document).mousemove(dragging);
        $(document).mouseup(function(e){
          $(document).unbind("mousemove",dragging);
          $(document).unbind("mouseup",arguments.callee);
          dragging(e);
          c.remove();
          ui.move(v,nx,ny);
          ui.inactiveCount--;
          return false;
        });

        function dragging(e)
        {
          nx = Math.max(Math.min(v.x+e.clientX-ox,ui.w-ui.r),ui.r);
          ny = Math.max(Math.min(v.y+e.clientY-oy,ui.h-ui.r),ui.r);
          c.attr({"cx":nx,"cy":ny});
          return false;
        }
        return false;
      });
    });
    ui.inactiveCount--;
  },

  move: function(v,x,y)
  {
    v.x = x;
    v.y = y;
    v.repr.attr({"cx":x,"cy":y});
    if(v.onMove)
     $.each(v.onMove,function(){this.call();});
  },

  deletion: function(X,callback)
  {
    if(X.length==0)
    {
      if(callback)callback();
      return;
    }

    var ui = this;
    ui.inactiveCount++;
    ui.unbindEvent();

    var active = {};//set
    var motion = [];
    var trash = [];

    $.each(X,function(){
      motion.push({
        repr: this.repr,
        attr: {"opacity": "0"}
      });

      motion.push({
        repr: this.reprShadow,
        attr: {"opacity": "0"}
      });
      trash.push(this.repr);
      trash.push(this.reprShadow);

      $.each(this.sibl,function(){active[this.id]=this;});
      delete ui.E[this.id];
    });

    ui.buildSibl(ui.E);

    $.each(active,function(){
      if(ui.E[this.id]!==undefined)
      {
        var attr = {"path": ui.calcPath(this)};
        motion.push({repr:this.repr,attr:attr});
        motion.push({repr:this.reprShadow,attr:attr});
      }
    });

    var count = motion.length;
    function term()
    {
      if(--count == 0){
        setTimeout(function(){$.each(trash,function(){this.remove();});},1000);
        ui.bindEvent();
        if(callback)callback();
        ui.inactiveCount--;
      }
    }

    motion[0].repr.animate(motion[0].attr,200,"linear",term);
    for(var k=1;k<motion.length;++k)
      motion[k].repr.animateWith(motion[0].repr,motion[k].attr,200,"linear",term);
  },

  contraction: function(X,callback)
  {
    var ui = this;
    ui.inactiveCount++;
    ui.unbindEvent();

    var motion = [];
    var trash = [];
    var activeV = {};// set
    var activeE = {};

    var G = Analyzer.prototype.compile(ui);
    var c = contraction(G,pullbackE(G,X));
    for(var i in c.component)
      c.component[i] = pullbackV(ui,c.component[i]);

    var V = {};
    $.each(c.G.V,function(){
      var v = {
        id: this.id,
        x: .0,
        y: .0,
        onMove: []
      };
      V[v.id] = v;

      $.each(c.component[v.id],function(){
        v.x += this.x;
        v.y += this.y;
      });
      v.x /= c.component[v.id].length;
      v.y /= c.component[v.id].length;
      v.repr = c.component[v.id][0].repr;

      if(c.component[v.id].length > 1)
      {
        var i = 0;
        $.each(c.component[v.id],function(){
          activeV[this.id] = true;
          motion.push({
            repr: this.repr,
            attr: {"cx": v.x,"cy": v.y}
          });
          if(i++!=0)
            trash.push(this.repr);
        });
      }
    });
    ui.V = V;

    var E = {};
    $.each(ui.E,function(){
      if(c.map[this.head.id]==c.map[this.tail.id])
      {
        var attr = {"path": ["M",V[c.map[this.head.id]].x,V[c.map[this.tail.id]].y].join(" ")};
        motion.push({repr: this.repr,attr: attr});
        motion.push({repr: this.reprShadow,attr: attr});
        trash.push(this.repr);
        trash.push(this.reprShadow);
        return;
      }

      var e = E[this.id] = {
        id: this.id,
        head: V[c.map[this.head.id]],
        tail: V[c.map[this.tail.id]],
        repr: this.repr,
        reprShadow: this.reprShadow,
        sibl: null
      };

      if(activeV[this.head.id] || activeV[this.tail.id])
        activeE[this.id] = e;
    });
    ui.E = E;

    ui.special.head = V[c.map[ui.special.head.id]];
    ui.special.tail = V[c.map[ui.special.tail.id]];

    $.each(c.component[ui.special.head.id],function(){
      this.repr.addClass("terminal");
    });

    $.each(c.component[ui.special.tail.id],function(){
      this.repr.addClass("terminal");
    });

    ui.buildSibl(E);
    $.each(activeE,function(){
      var attr = {"path":ui.calcPath(this)};
      motion.push({repr: this.repr,attr: attr});
      motion.push({repr: this.reprShadow,attr: attr});
    });

    var count = motion.length;
    function term()
    {
      if(--count == 0){
        setTimeout(function(){$.each(trash,function(){this.remove();});},1000);
        ui.bindEvent();
	if(callback)callback();
        ui.inactiveCount--;
      }
    }

    motion[0].repr.animate(motion[0].attr,500,"bounce",term);
    for(var k=1;k<motion.length;++k)
      motion[k].repr.animateWith(motion[0].repr,motion[k].attr,500,"bounce",term);
  },

  subst: function(o,callback)
  {
    var ui = this;
    var R = this.raphael;
    ui.inactiveCount++;
    ui.unbindEvent();


    var motion = [];
    var trashV = {};
    var trashE = {};
    $.each(ui.V,function(){trashV[this.id]=this.repr;});
    $.each(ui.E,function(){trashE[this.id]=[this.repr,this.reprShadow];});

    V = {};
    E = {};

    var V = this.V = {};
    $.each(o.V,function(){
      V[this.id] = {
        id: this.id,
        x: this.x,
        y: this.y,
        onMove: []
      };
    });

    var E = this.E = {};
    $.each(o.E,function(){
      var e  = {
          id: this.id,
          head: V[this.head],
          tail: V[this.tail]
      };
      if(this.id==="special")
        ui.special = e;
      else
        E[e.id] = e;
    });

    GraphUI.fn.buildSibl(E);

    $.each(E,function(){
      var d = GraphUI.fn.calcPath(this);

      if(trashE[this.id]!==undefined)
      {
        this.repr = trashE[this.id][0];
        this.reprShadow = trashE[this.id][1];
        motion.push({repr:this.repr,attr:{"path":d}});
        motion.push({repr:this.reprShadow,attr:{"path":d}});
	delete trashE[this.id];
      }
      else
      {
        this.repr = R.path(d);
        this.repr.addClass("edge").attr({"opacity":0});
	this.repr.toBack();
        this.reprShadow = R.path(d);
        this.reprShadow.addClass("edge","shadow").attr({"opacity":0});
	this.reprShadow.toBack();
        motion.push({repr:this.repr,attr:{"opacity":1}});
        motion.push({repr:this.reprShadow,attr:{"opacity":1}});
      }
    });

    $.each(ui.V,function(){
      if(trashV[this.id]!==undefined)
      {
        this.repr = trashV[this.id];
	motion.push({repr:this.repr,attr:{"cx":this.x,"cy":this.cy}});
	this.repr.setClass("vertex");
	delete trashV[this.id];
      }
      else
      {
        this.repr = R.circle(this.x,this.y,ui.r);
        this.repr.addClass("vertex").attr({"opacity":0});
	motion.push({repr:this.repr,attr:{"opacity":1}});
      }
    });

    ui.special.head.repr.addClass("terminal");
    ui.special.tail.repr.addClass("terminal");

    $.each(trashV,function(){motion.push({repr:this,attr:{"opacity":0}});});
    $.each(trashE,function(){
      motion.push({repr:this[0],attr:{"opacity":0}});
      motion.push({repr:this[1],attr:{"opacity":0}});
    });

    var count = motion.length;
    function term()
    {
      if(--count == 0){
        setTimeout(function(){
          $.each(trashE,function(){this.remove();});
          $.each(trashV,function(){this.remove();});
	},1000);
        ui.bindEvent();
	if(callback)callback();
        ui.inactiveCount--;
      }
    }

//    motion[0].repr.animate(motion[0].attr,200,"linear",term);
//    for(var k=1;k<motion.length;++k)
//      motion[k].repr.animateWith(motion[0].repr,motion[k].attr,200,"linear",term);
    $.each(motion,function(){this.repr.attr(this.attr);term();});  
  }
};
GraphUI.fn = GraphUI.prototype;

