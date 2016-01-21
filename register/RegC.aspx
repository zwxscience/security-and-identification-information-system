<%@ Page Language="C#" AutoEventWireup="true" CodeFile="RegC.aspx.cs" Inherits="Login" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
<title>防伪识别信息系统</title>
<link href="../CSS/regStyle.css" rel="stylesheet" type="text/css" />
<link href="../CSS/Nstyles.css" rel="stylesheet" type="text/css" />
<script type="text/javascript" src="../JS/jquery-1.3.1.js"></script>


</head>
<body>
<div id="header">

<h1 style="font-family: 隶书; left: 1.7em; height:60px; margin-top: 17px; bottom: 204px;">
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; 防伪识别信息系统</h1>

</div>
    <form id="form1" runat="server">




<table width="100%" border="0" align="center" cellspacing="35" cellpadding="0"  class="login-table" >
<tr>
<td valign="top" class="right" style="width: 365px; height: 238px;">
<div class="title-n">
用户注册完成
</div>
<br />
  <div id="finish" class="frame">
        <div class="reg">
            <div class="regbox finish">
              <div class="ld"></div>
      <div class="rd"></div>
      <h1></h1>
        <ul>
        <li>
                <dl>
                 <dd class="success">注册成功</dd>
              
               <dd> <a href="../Login.aspx" >点击进入会员中心</a> </dd>
               <em id="info">4秒后自动跳转到会员中心</em>
                      </dl>
   </li>
   </ul>
   </div>
                   
          


<script type="text/javascript" src="../JS/Nreg.js">

</script>
<script type="text/javascript">
function clock(){
 i = i -1;
 if(document.getElementById("info")){
  document.getElementById("info").innerHTML = i+"秒后自动跳转到首页";
 }
 if(i > 0)
  setTimeout("clock();",1000);
 else
   window.parent.parent.location.href='../Login.aspx';
  
} 
var i=5;
clock();
</script>
</td>
</tr>
</table>


    </form>


</body>
</html>
