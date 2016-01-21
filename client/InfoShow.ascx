<%@ Control Language="C#" AutoEventWireup="true" CodeFile="InfoShow.ascx.cs" Inherits="query_InfoShow" %>

<%@  Import   Namespace="System.Data"   %>
<link href="../CSS/InfoShow.css"  type="text/css" />
  <asp:Panel ID="Panel1" runat="server" Width="100%"  Enabled="False" 
             GroupingText="最新消息" BackColor="White" ForeColor="#003399"  >
       
    
<div id="marqueebox0" class="cls_container">
 <marquee scrollAmount=2  scrolldelay="100" onMouseOver="this.scrollDelay=500" onMouseOut="this.scrollDelay=1" width="100%" height="130px" direction="up" >
 <table width="668">
<%
 
    Datacon dacon = new Datacon();
    string sqlstr = "SELECT distinct top 5 MessagesId,MessageName,MessageDate FROM xxfb  where sendto='全部' or sendto='客户'  or sendto='" + Session["username"] + "' order by MessageDate desc ";
    DataSet ds = dacon.getds(sqlstr);
                for (int i = 0; i < ds.Tables[0].Rows.Count; i++)
                {  //历遍所有的
               
        %>
<tr onmouseover="this.bgColor='#00BFFF'"   onmouseout="this.bgColor=''">


<td width="70%"  align="left" >
<a href="Info/InfoRead.aspx?NewsId=<%=ds.Tables[0].Rows[i]["MessagesId"].ToString() %>" target="_parent"><%=ds.Tables[0].Rows[i]["MessageName"].ToString()%></a></td>
<td width="30%"  align="left"><%=ds.Tables[0].Rows[i]["MessageDate"].ToString()%></td></tr>
<%
                } %>
 </table></marquee>
</div>
    </asp:Panel>