 var Sys = {};

        var ua = navigator.userAgent.toLowerCase();
        var s;
        (s = ua.match(/msie ([\d.]+)/)) ? Sys.ie = s[1] :
        (s = ua.match(/firefox\/([\d.]+)/)) ? Sys.firefox = s[1] :
        (s = ua.match(/chrome\/([\d.]+)/)) ? Sys.chrome = s[1] :
        (s = ua.match(/opera.([\d.]+)/)) ? Sys.opera = s[1] :
        (s = ua.match(/version\/([\d.]+).*safari/)) ? Sys.safari = s[1] : 0;


function show(obj,maxg,obj2)
{
 var hhh = obj.offsetHeight;
  if(hhh <maxg)
  {
    hhh +=maxg/10;
   obj.style.height=hhh+"px";
                 
        //以下进行测试
        if(Sys.ie)  {
     obj.filters.alpha.opacity+=20;
          }
        if(Sys.firefox) 
        {
  obj.style.MozOpacity +=20;

          }
        else
        {
         
      obj.style.Opacity  +=20;
 
        }
	obj2.background="../images/title_hide.gif";

    if(hhh ==maxg/10)
	  obj.style.display='block';
	myObj=obj;
	mymaxg=maxg;
	myObj2=obj2;
	setTimeout('show(myObj,mymaxg,myObj2)','5');
  }
}
function hide(obj,maxg,obj2)
{
 var hhh = obj.offsetHeight;
  if(hhh>0)
  {
    if(hhh==maxg/5)
	  obj.style.display='none';
    obj.style.height=(hhh-maxg/5)+"px";

    //以下进行测试
        if(Sys.ie)  {
	obj.filters.alpha.opacity-=10;
          }
        if(Sys.firefox) 
        {
  obj.style.MozOpacity -=10;

          }
        else
        {
         
      obj.style.Opacity  -=10;
 
        }
	obj2.background="../images/title_show.gif";
	myObj=obj;
	mymaxg=maxg
	myObj2=obj2;
	setTimeout('hide(myObj,mymaxg,myObj2)','5');
  }
  else    if(whichcontinue)
	  whichcontinue.click();
}
function chang(obj,maxg,obj2)
{
  if(obj.offsetHeight)
  {
    hide(obj,maxg,obj2);
	nopen='';
	whichcontinue='';
  }
  else    if(nopen)
	{
	  whichcontinue=obj2;
      nopen.click();
	}
	else
	{
	  show(obj,maxg,obj2);
	  nopen=obj2;
	  whichcontinue='';
	}
}
var nopen="";
var whichContinue='';
function TABLE1_onclick() {

}
function IMG1_onclick() {

}
function TABLE2_onclick() {

}

function menu1_onclick() {

}