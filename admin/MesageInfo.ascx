<%@ Control Language="C#" AutoEventWireup="true" CodeFile="MesageInfo.ascx.cs" Inherits="MesageInfo" %>
<%@ Register Src="InfoShow.ascx" TagName="InfoShow" TagPrefix="uc1" %>

<script type="text/javascript" language="javascript">
  

    
</script>

<link href="../CSS/InfoShow.css" type="text/css" />
<link href="../CSS/InfoShow.css" type="text/css" />
<table style="width: 100%">
    <tr style="height:5px; background-color: #ffccff">
        <td align="center" >
        </td>
    </tr>
    <tr  align="center" width="100%" style=" ">
    <td  align="center" style="height:12pt; color: blue;" width="100%">
         <asp:Panel ID="Panel1" runat="server" Width="100%"  Enabled="False" 
             GroupingText="最新消息" BackColor="White" ForeColor="#003399"  >
        <uc1:InfoShow ID="InfoShow1" runat="server" />
        </asp:Panel>
        
        &nbsp;
     </td>
    </tr>
</table>