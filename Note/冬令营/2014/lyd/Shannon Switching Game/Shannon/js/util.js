
function uniqID(){return uniqID.prototype.N++;}
uniqID.prototype.N = 0;

function dump(obj)
{
  var s = "";
  for(var i in obj)
    s += i+": "+(obj[i]?obj[i].toString():obj[i])+"\n";
  alert(s);
}

Raphael.el.addClass = function(c){
  var self = arguments.callee;
  var o = this;
  if(arguments.length>1)
  {
    $.each(arguments,function(){self.apply(o,[this]);});
    return this;
  }

  var cs = this.node.getAttribute("class");
  cs = cs?cs.split(/\s+/):[];

  if($.inArray(c,cs)<0)
  //if(cs.indexOf(c)<0)
  {
    cs.push(c);
    this.node.setAttribute("class",cs.join(" "));
  }
  return this;
};

Raphael.el.setClass = function(){
  this.node.setAttribute("class",$.makeArray(arguments).join(" "));
  return this;
};
