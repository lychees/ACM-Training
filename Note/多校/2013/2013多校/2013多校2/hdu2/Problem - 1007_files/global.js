function NavFolder()
{
	var x = document.getElementsByTagName('ul');
	for(i=0;i<5;i++)
	{
		flag = false;
		if( x[i].style.display == "" )        
		{
			flag = true;
			x[i].style.display = "none";
		}
		else x[i].style.display = "" ;
	}
	obj=document.getElementById("nav");
	if( flag == true )
		obj.style.height = "142px";
	else obj.style.height ="245px";
	return ;
}
function Highlight(objRef,state)
{
		objRef.style.background = ( 1==state)? '#d7ebff' : '';
} 
function ObjFolder(objName)
{
	var obj=document.getElementById(objName);
	if(obj.style.display == "")
		obj.style.display ="none";
	else obj.style.display = "";
}
function PassDisplay()
{
	var obj = document.getElementById("contesttype1");
	var tar = document.getElementById("password");

	if( obj.checked == true )
	{
		//tar.readOnly=false;
		tar.removeAttribute("disabled");
	}
	else
	{
		tar.value=""
		tar.setAttribute("disabled", true);
		//tar.readOnly=true;
	}
}
var pfsize = 15;
var divs = new Array("procon","proinput","prooutput","prosamplein","prosampleout","prohint","proauthor","prosource","prorecommend");
function ProFontAdd(v)
{
	var obj;
	pfsize = pfsize + v;
	for(i=0;i<divs.length;i++)
	{
		obj = document.getElementById(divs[i]);
		if( obj!=null)
				obj.style.fontSize = pfsize + 'px';
	}
}
function ProFont(f)
{
	var obj;
	for(i=0;i<divs.length;i++)
	{
		obj = document.getElementById(divs[i]);
		if( obj!=null)
				obj.style.fontFamily = f;
	}
}
function ReplaceTab(ObjName)
{
	obj = document.getElementById(ObjName);
	obj.value =obj.value.replace(/\t/gi,"\xa0\xa0\xa0\xa0");
}
function CopyCode(ObjName)
{
	obj = document.getElementById(ObjName);
	obj.value =obj.value.replace(/\xa0\xa0\xa0\xa0/gi,"\t");
	obj.select();
	obj.createTextRange().execCommand("Copy");
	ReplaceTab(ObjName);
}
function WriteProblem(ProblemList)
{
	for(i=1;i<ProblemList.length;i++)
		document.write("<a href='showproblem.php?pid=" + ProblemList[i] + "'>" + ProblemList[i] + "</a> ");
}
function WriteText()
{
	document.write("<textarea id='aaa' readonly='readonly'>aaaget	tet	er</textarea><script type=text/javascript>ReplaceTab('aaa');</script><h4><span onclick=\"CopyCode('aaa')\">[ Copy to clipboard ]</span></h4>");
}
function is_hide(ele)
{
    var obj;
    obj=document.getElementById(ele);
    if(obj!=null){
    	if(obj.style.display=="none")
      	  obj.style.display="";
   		else
      	  obj.style.display="";   
     } 
}
function id_color(ele,num)
{
       var obj;
       obj=document.getElementById(ele);
       if(num%2)
       {
            obj.style.bgColor="#D7EBFF";
       }else
        {
            obj.style.bgColor="";
        }    
        
        
 }
 function travel_table(ele,num)
 {
 	var tableObj=document.getElementById(ele);
 	var sum;
 	sum=tableObj.rows.length;
 	for(var i=0;i<=sum&&i<=num;i++)
 	{
 			var styles=tableObj.rows[i].id;
 			if(styles!='')
 				is_hide(styles);	
 	}	
 }
 
 function set_hidden(ele)
 {
 	var obj = document.getElementById(ele);
 	obj.style.display = "none";
 }
 
 