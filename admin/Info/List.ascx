<%@ Control Language="C#" AutoEventWireup="true" CodeFile="List.ascx.cs" Inherits="List" %>

<div  style="font-size:12px;"  onload="show(menu1,120,list1);">            
     <table cellspacing="0 "cellpadding="0 "width="158"   style="text-align:center" id="TABLE2" >
       <tbody>
        <tr style="CURSOR: hand">
          <td valign="bottom" style=" height:38px; width: 159px;" >
          <img src="../../images/title.gif" width="158" height="38" alt="标题栏" id="IMG1" 
                  onclick="IMG1_onclick()"/> 
          </td>
        </tr>
       </tbody>
     </table>



     <table cellspacing="0" cellpadding="0"width="158" style="text-align:center">
       <tbody>
        <tr style="CURSOR: hand;font-size:12px">
          <td class="list_title" id="list1" 
            onmouseover="this.typename='list_title2';" 
             onclick="chang(document.getElementById('menu1'),75,document.getElementById('list1'))";
            onmouseout="this.typename='list_title';" 
            style="height: 25px ; background:url(../../images/title_show.gif); width: 161px;">
           <span>个人信息管理</span> 
         </td>
       </tr>
       <tr>
       
         <td style="text-align:center; width: 161px; color:#4682B4" valign="middle"> 
            <div class="sec_menu" id="menu1" 
style="DISPLAY: none; width: 158px; height: 0px; filter:alpha(opacity=0);" onclick="return menu1_onclick()">
                 <table  cellspacing="2" cellpadding="0" width="135" style="text-align:center">
                    <tbody>       
                        <tr> 
                      <td style=" height:25px;font-size:12px"><a href="../Default.aspx" target="_parent" style="text-decoration: none;color:#4682B4">个人信息</a></td>
                    </tr>
                   <tr> 
                     
                  
             <td style=" height:25px;font-size:12px"><a href="../Default.aspx" target="_parent" style="text-decoration: none;color:#4682B4">消息系统</a></td>
                    </tr>
                    </tbody>  
                 </table>
           </div>
         </td>
        </tr>
       </tbody>
     </table>
     <% 
        // if(Session["bz"]!=null&&Session["bz"].ToString().Equals("系统管理员") ){
             %>
          <table cellspacing="0" cellpadding="0"width="158" style="text-align:center">
       <tbody>
        <tr style="CURSOR: hand;font-size:12px">
          <td class="list_title" id="Td11" 
            onmouseover="this.typename='list_title2';" 
             onclick="chang(document.getElementById('Div11'),130,document.getElementById('Td11'))";
            onmouseout="this.typename='list_title';" 
            style="height: 25px ; background:url(../../images/title_show.gif); width: 161px;">
           <span>功能管理</span> 
         </td>
       </tr>
       <tr>
       
         <td style="text-align:center; width: 161px; color:#4682B4" valign="middle"> 
            <div class="sec_menu" id="Div11" 
style="DISPLAY: none; width: 158px; height: 0px; filter:alpha(opacity=0);" onclick="return menu1_onclick()">
                 <table  cellspacing="2" cellpadding="0" width="135" style="text-align:center">
                    <tbody>       
                        <tr> 
                      <td style=" height:25px;font-size:12px"><a href="../rateSet.aspx" target="_parent" style="text-decoration: none;color:#4682B4">费率设置</a></td>
                    </tr>
                    <tr> 
                      <td style=" height:25px;font-size:12px"><a href="../ClientInfoManagement.aspx" target="_parent" style="text-decoration: none;color:#4682B4">申请审批</a></td>
                    </tr>
                    <tr> 
                      <td style=" height:25px;font-size:12px"><a href="../userfee.aspx" target="_parent" style="text-decoration: none;color:#4682B4">用户费用统计</a></td>
                    </tr>
                     <tr> 
                      <td style=" height:25px;font-size:12px"><a href="InfoOp.aspx" target="_parent" style="text-decoration: none;color:#4682B4">系统广播</a></td>
                    </tr>
                           <tr> 
                      <td style=" height:25px;font-size:12px"><a href="../userMan.aspx" target="_parent" style="text-decoration: none;color:#4682B4">用户管理</a></td>
                    </tr>
                    </tbody>  
                 </table>
           </div>
         </td>
        </tr>
       </tbody>
     </table>
  <%//}  %>
</div>