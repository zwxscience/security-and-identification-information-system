<%@ Control Language="C#" AutoEventWireup="true" CodeFile="userInfo.ascx.cs" Inherits="admin_userInfo" %>


<script type="text/javascript" language="javascript">
   //获取输入框内容
    $(document).ready(function () {
   

           $(document).ready(function () {
//        $("#return").click(function () {
//            window.location.href = 'userMan.aspx'; return false;
//        });
    });
   
</script>


<table style="width: 100%">
    <tr style="height:20pt">
        <td colspan="2" align="center">
        <asp:Label ID="Label2" runat="server" Text="基本信息" Font-Bold="True" Font-Names="宋体" 
                Font-Size="16pt"  ForeColor="MidnightBlue"></asp:Label>
        </td>
    </tr>
    <tr style="height:5px; background-color: #ffccff">
        <td align="center" colspan="2" >

        </td>
    </tr>
    <tr style="height:12pt">
        <td style="width:50%; height: 12pt;">
            <asp:Label ID="Lyz_bm" runat="server" Text="编号：" Font-Size="10pt"  style= "TEXT-ALIGN:   right " 
                Width="100px" />
            <asp:Label ID="PID" runat="server" Text="Label"></asp:Label>
        </td>
        <td style="width:50%; height: 12pt;">
            <asp:Label ID="Lyzsydw" runat="server" Font-Size="10pt" Text="区域企业号："  style= "TEXT-ALIGN:   right " 
                Width="170px"></asp:Label>
            <asp:Label ID="Regionalism" runat="server" Text="Label"></asp:Label>
        </td>
    </tr>
    <tr style="height:12pt">
        <td style="width:50%; height: 12pt;">
            <asp:Label ID="Lyz_mc" runat="server" Text="公司名称：" Font-Size="10pt"  style= "TEXT-ALIGN:   right " 
                Width="100px" />
            <asp:Label ID="ComName" runat="server" Text="Label"></asp:Label>
        </td>
        <td style="width:50%; height: 12pt;">
            <asp:Label ID="Label3" runat="server" Font-Size="10pt" Text="公司地址："  style= "TEXT-ALIGN:   right " 
                Width="170px"></asp:Label>
            <asp:Label ID="ComAddress" runat="server" Text="Label"></asp:Label>
        </td>
        
    </tr>
    <tr style="height:12pt">
        <td style="width:50%; height: 12pt;">
            <asp:Label ID="Lyz_zt" runat="server" Text="公司电话：" Font-Size="10pt"  style= "TEXT-ALIGN:   right " 
                Width="100px" />
            <asp:Label ID="ComTel" runat="server" Text="Label"></asp:Label>
        </td>
           <td style="width:50%; height: 12pt;">
            <asp:Label ID="Lyzsydwyw" runat="server" Font-Size="10pt" Text="公司网址："  style= "TEXT-ALIGN:   right " 
                   Width="170px"></asp:Label>
               <asp:Label ID="ComNet" runat="server" Text="Label"></asp:Label>
        </td>
    </tr>
    <tr style="height: 12pt">
        <td style="width: 50%; height: 12pt">
            <asp:Label ID="Lyz_lx" runat="server" Text="公司电子邮箱：" Font-Size="10pt"  style= "TEXT-ALIGN:   right " 
                Width="100px" />
            <asp:Label ID="ComEmail" runat="server" Text="Label"></asp:Label>
        </td>
        <td style="width: 50%; height: 12pt">
            <asp:Label ID="Lyzzzdy" runat="server" Font-Size="10pt" Text="注册时间："  style= "TEXT-ALIGN:   right " 
                Width="170px"></asp:Label>
            <asp:Label ID="RegDate" runat="server" Text="Label"></asp:Label>
        </td>
    </tr>
    <tr style="height: 12pt">
        <td style="width: 50%; height: 12pt">
            <asp:Label ID="Label6" runat="server" Font-Size="10pt" Text="可用金额："  style= "TEXT-ALIGN:   right " 
                Width="100px"></asp:Label>
            <asp:Label ID="Gold" runat="server" Text="Label"></asp:Label>
        </td>
        <td style="width: 50%; height: 12pt">
    

            <asp:Label ID="Label7" runat="server" Font-Size="10pt" Text="账号状态："  style= "TEXT-ALIGN:   right " 
                Width="166px" Height="16px"></asp:Label>
            <asp:Label ID="state" runat="server"></asp:Label>
        </td>
    </tr>
    <tr style="height: 12pt">
        <td style="width: 50%; height: 12pt">
            &nbsp;</td>
        <td style="width: 50%; height: 12pt">
    

            &nbsp;</td>
    </tr>
    </table>
 
    