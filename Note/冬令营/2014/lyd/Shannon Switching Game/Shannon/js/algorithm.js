
function pullbackE(G,E){return $.map(E,function(e){return G.E[e.id];});}
function pullbackV(G,V){return $.map(V,function(v){return G.V[v.id];});}

// G -> G
function transpose(G)
{
  var res = {V: {}, E: {}};
  $.each(G.V,function(){
    res.V[this.id] = {id: this.id, inc: []};
  });

  $.each(G.E,function(){
    var e = res.E[this.id] = {
      id: this.id,
      head: res.V[this.tail.id],
      tail: res.V[this.head.id]
    };
    e.tail.inc.push(e);
  });
  return res;
}

// directed
// G -> [V] -> [V]
function reachable(G,V)
{
  var res = [];
  var visited = {};
  $.each(V,function(){
    if(visited[this.id])
      return;
    visited[this.id] = true;
    res.push(this);

    var visit = arguments.callee;
    $.each(this.inc,function(){
      visit.call(this.head);
    });
  });
  return res;
}

function mincut(G,s,t)
{
  var f = {};
  $.each(G.E,function(){f[this.id]=0;});

  return (function(){
    var aux = makeAux();
    var path = shortestPath(aux,[aux.V[s.id]],[aux.V[t.id]]);
    if(path!=null)
    {
      $.each(path.E,function(){this.doit()});
      return arguments.callee.call();
    }
    else
    {
      var V = pullbackV(G,reachable(aux,[aux.V[s.id]]));
      var inV = asSet(V);
      var E = $.grep(asArray(G.E),function(e){
        return ((inV[e.head.id]!==undefined?1:0)+(inV[e.tail.id]!==undefined?1:0))==1;
      });
      return {E:E,V:V};
    }
  })();

  function makeAux()
  {
    var res = {V: {}, E: {}};
    $.each(G.V,function(){
      res.V[this.id] = {
        id: this.id,
        inc: []
      };
    });

    $.each(G.E,function(){
      var eid = this.id;
      if(f[eid] <= 0)
      {
        var h = res.V[this.head.id];
        var t = res.V[this.tail.id];
        var e = {
          id: uniqID(),
          head: h,
          tail: t,
          doit: function(){f[eid]++;}
        };
        res.E[e.id] = e;
        t.inc.push(e);
      }
      if(f[eid] >= 0)
      {
        var h = res.V[this.tail.id];
        var t = res.V[this.head.id];
        var e = res.E[eid] = {
          head: h,
          tail: t,
          doit: function(){f[eid]--;}
        };
        t.inc.push(e);
      }
    });
    return res;
  }
}

// undirected
// G -> {
//   component: cid => [Vertex],
//   map: G.V.key => component.key
// }
function connectedComponent(G)
{
  var visited = {};
  var component = {};
  var map = {};

  $.each(G.V,function(cid){
    if(map[this.id]!==undefined)
      return;
    if(cid===null)
    {
      cid = uniqID();
      component[cid] = [];
    }
    component[cid].push(this);
    map[this.id] = cid;

    var visit = arguments.callee;
    $.each(this.inc,function(){
      visit.call(this.tail,cid);
      visit.call(this.head,cid);
    });
  },[null]);

  return {map: map, component: component};
}

//undirected or directed
// G -> [E] -> G
function restriction(G,E)
{
  var valid = asSet(E);
  //$.each(E,function(){valid[this.id]=true;});

  var resG = {V:{},E:{}};
  $.each(G.V,function(){
    resG.V[this.id] = {
      id: this.id,
      inc: $.grep(this.inc,function(e){
        return valid[e.id]!==undefined;
      })
    };
  });

  $.each(E,function(){
    resG.E[this.id] = {
      id: this.id,
      head: resG.V[this.head.id],
      tail: resG.V[this.tail.id]
    };
  });

  $.each(resG.V,function(){
    this.inc = pullbackE(resG,this.inc);
  });

  return resG;
}

// G -> [E] -> {G, map: arg.G.V.key -> res.G.V.key}
// undirected
function contraction(G,E)
{
  var cc = connectedComponent(restriction(G,E));
  var resG = {V:{},E:{}};

  for(var i in cc.component)
  {
    resG.V[i] = {
      id: i,
      inc: []
    };
    cc.component[i] = pullbackV(G,cc.component[i]);
  }

  $.each(G.E,function(){
    if(cc.map[this.head.id] != cc.map[this.tail.id])
    {
      var e = {
        id: this.id,
        head: resG.V[cc.map[this.head.id]],
        tail: resG.V[cc.map[this.tail.id]]
      };
      resG.E[e.id] = e;
      e.head.inc.push(e);
      e.tail.inc.push(e);
    }
  });

  return {G:resG, map:cc.map, component:cc.component};
}

function graphicClosure(G,E)
{
  var ccm = connectedComponent(restriction(G,E)).map;
  var res = [];
  $.each(G.E,function(){
    if(ccm[this.head.id]==ccm[this.tail.id])
      res.push(this);
  });
  return res;
}

// undirected
function spanningtree(G)
{
  var res = [];
  var visited = {};
  $.each(G.V,function(e){
    if(visited[this.id])
      return;
    visited[this.id] = true;
    if(e)
      res.push(e);

    var visit = arguments.callee;
    $.each(this.inc,function(){
      visit.call(this.head,this);
      visit.call(this.tail,this);
    });
  },[null]);
  return res;
}

// directed
// G -> [V] -> [V] -> {[V],[E]}
function shortestPath(G,S,T)
{
  var goal = asSet(T);
  var visited = asSet(S);
  var back = {};
  var backEdge = {};
  while(S.length!=0)
  {
    var v = S.shift();
    if(goal[v.id])
    {
      var V = [v];
      var E = [];
      while(back[V[0].id])
      {
        E.unshift(backEdge[V[0].id]);
        V.unshift(back[V[0].id]);
      }
      return {V:V,E:E};
    }

    $.each(v.inc,function(){
      if(visited[this.head.id]===undefined)
      {
        visited[this.head.id] = true;
        backEdge[this.head.id] = this;
        back[this.head.id] = this.tail;
        S.push(this.head);
      }

      // 逆向き枝も見る．有向グラフでは自動的に無視される．
      if(visited[this.tail.id]===undefined)
      {
        visited[this.tail.id] = true;
        backEdge[this.tail.id] = this;
        back[this.tail.id] = this.head;
        S.push(this.tail);
      }
    });
  }
  return null;
}

// [A] -> [A] -> [A]
function intersection(X,Y)
{
  var inX = asSet(X);
  return $.grep(Y,function(y){return inX[y.id]!==undefined;});
}

// [A] -> [A] -> [A]
function setminus(X,Y)
{
  var inY = asSet(Y);
  return $.grep(X,function(x){return inY[x.id]===undefined;});
}

// 
function union(X,Y)
{
  var res = [];
  var inX = {};
  $.each(X,function(){
    inX[this.id]=true;
    res.push(this);
  });
  $.each(Y,function(){
    if(inX[this.id]===undefined)
      res.push(this);
  });
  return res;
}

function asArray(X)
{
  var res = [];
  $.each(X,function(){res.push(this);});
  return res;
}

function asSet(X)
{
  var res = {};
  $.each(X,function(){res[this.id]=this;});
  return res;
}

// G -> [E] -> [E] -> {G, map, component}
function decompose(G,T,U)
{
  var E = asArray(G.E);
  if(T===undefined)
  {
    T = E;
    //U = [];
  }
  else
  {
    T = $.grep(T,function(x){return G.E[x.id]!==undefined});
    T = pullbackE(G,T);
    //U = $.grep(U,function(x){return G.E[x.id]!==undefined});
  }

  T = pullbackE(G,spanningtree(restriction(G,T)));
  U = pullbackE(G,spanningtree(restriction(G,setminus(E,T))));

  return (function(){
    var clT = graphicClosure(G,T);
    var clU = graphicClosure(G,U);

    var aux = makeAux(clT,clU);
    var start = union(setminus(E,clT),setminus(E,clU));
    var goal = intersection(setminus(E,T),setminus(E,U));

    start = pullbackV(aux,start);
    goal = pullbackV(aux,goal);

    var path = shortestPath(aux,start.concat(),goal);
    if(path!=null)
    {
      var tu = asSet(clT)[path.V[0].id]===undefined?0:1;
      var dT = [],dU = [];
      $.each(path.V,function(){
        [dT,dU][tu++%2].push(G.E[this.id]);
      });
      T = union(setminus(T,dU),dT);
      U = union(setminus(U,dT),dU);
      return arguments.callee.call();
    }
    else
    {
      var p = partition(aux,start,goal);
      for(var i in p.component)
        p.component[i] = pullbackE(G,p.component[i]);
      p.T = T;
      p.U =U;
      return p;
    }
  })();

  function makeAux(clT,clU)
  {
    var V={};
    var E={};
    $.each(G.E,function(){
      V[this.id] = {
        id: this.id,
        inc: []
      };
    });

    makeEdge(T,clT);
    makeEdge(U,clU);
    function makeEdge(X,clX)
    {
      var inX = asSet(X);
      var GX = restriction(G,X);

      $.each(clX,function(){
        if(inX[this.id]!==undefined)
          return;
        var v = this;
        var path = shortestPath(GX,
                     [GX.V[this.head.id]],
                     [GX.V[this.tail.id]]).E;
        $.each(path,function(){
          var e = {
            id: uniqID(),
            tail: V[this.id],
            head: V[v.id]
          };
	  E[e.id] = e;
          e.tail.inc.push(e);
        });
      });
    }

    return {V:V,E:E};
  }
}

//directed
function topsort(G)
{
  var visited = {};
  var res = [];
  $.each(G.V,function(){
    if(visited[this.id]!==undefined)
      return;
    visited[this.id] = true;
    $.each(
      $.map(this.inc,function(e){return e.head;}),
      arguments.callee);
    res.push(this);
  });
  return res;
}

// directed
// strongly connected component
// G -> {G, map: arg.G.V.key => res.G.V.key, component: res.G.V.key => [V]}}
function sccDecomp(G)
{
  var tG = transpose(G);
  var resG = {V:{},E:{}};
  var map = {};
  var component = {};
  var visited = {};
  $.each(topsort(G).reverse(),function(cid){
    if(visited[this.id]!==undefined)
      return;
    visited[this.id] = true;

    if(cid==null)
    {
      cid = uniqID();
      resG.V[cid] = {
        id: cid,
        inc: []
      };
      component[cid] = [];
    }
    component[cid].push(this);
    map[this.id] = cid;
    $.each(
      $.map(tG.V[this.id].inc,function(e){return G.V[e.head.id];}),
      arguments.callee,[cid]);
  },[null]);

  $.each(G.E,function(){
    if(map[this.head.id]!=map[this.tail.id])
    {
      var e = resG.E[this.id] = {
        id: this.id,
        head: resG.V[map[this.head.id]],
        tail: resG.V[map[this.tail.id]]
      };
      e.tail.inc.push(e);
    }
  });
  return {G:resG, map:map, component: component};
}

// directed
function inducedGraph(G,V)
{
  var resG = {V:{},E:{}};
  $.each(V,function(){
    resG.V[this.id] = {
      id: this.id,
      inc: []
    };
  });

  $.each(G.E,function(){
    if(resG.V[this.head.id]!==undefined && resG.V[this.tail.id]!==undefined)
    {
      var e = resG.E[this.id] = {
        id: this.id,
        head: resG.V[this.head.id],
        tail: resG.V[this.tail.id]
      };
      resG.V[e.tail.id].inc.push(e);
    }
  });
  return resG;
}

// directed
// G -> V -> V -> {G, map: arg.G.V.key => res.G.V.key, component: res.G.V.key => [V]}
function partition(G,start,goal)
{
  var S = reachable(G,start);
  var T = (function(){
    var H = transpose(G);
    return reachable(H,pullbackV(H,goal));
  })();
  T = pullbackV(G,T);

  var H = inducedGraph(G,setminus(asArray(G.V),union(S,T)));
  var scc = sccDecomp(H);
  for(var i in scc.component)
    scc.component[i] = pullbackV(G,scc.component[i]);

  var v = {
    id: uniqID(),
    inc: []
  };
  scc.G.V[v.id] = v;
  scc.component[v.id] = S;
  $.each(S,function(){
    scc.map[this.id] = v.id;
  });
  var hi = v.id;

  v = {
    id: uniqID(),
    inc: []
  };
  scc.G.V[v.id] = v;
  scc.component[v.id] = T;
  $.each(T,function(){
    scc.map[this.id] = v.id;
  });
  var lo = v.id;

  $.each(G.E,function(){
    var h = scc.map[this.head.id];
    var t = scc.map[this.tail.id];
    if((h==hi && t!=hi) || (h!=lo && t==lo))
    {
      var e = {
        id: this.id,
	head: scc.G.V[h],
	tail: scc.G.V[t]
      };
      scc.G.E[e.id] = e;
      e.tail.inc.push(e);
      //scc.G.V[e.tail.id].push(e);
    }
  });

  scc.lower = lo;
  scc.upper = hi;
  return scc;
}
