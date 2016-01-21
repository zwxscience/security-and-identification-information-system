<%@ Control Language="C#" AutoEventWireup="true" CodeFile="checkInfo.ascx.cs" Inherits="check_checkInfo" %>


<script type="text/javascript" language="javascript">
   //获取输入框内容
    $(document).ready(function () {
        $('#ImageButton1').click(function () {
            var buttonNone = $('#InfoChange');
            buttonNone.toggle(buttonNone.css('display') == 'none');
        });
        $('#ImageButton2').click(function () {
            var buttonNone = $('#pswMod');
            buttonNone.toggle(buttonNone.css('display') == 'none');
        });
    });
   
</script>


<style type="text/css">
    .style1
    {
        height: 12pt;
    }
</style>
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
            <asp:Label ID="Lyzsydw" runat="server" Font-Size="10pt" Text="区域企业号:"  style= "TEXT-ALIGN:   right " 
                Width="100px"></asp:Label>
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
                Width="100px"></asp:Label>
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
                   Width="100px"></asp:Label>
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
                Width="100px" Height="16px"></asp:Label>
            <asp:Label ID="RegDate" runat="server" Text="Label"></asp:Label>
        </td>
    </tr>
    <tr style="height: 12pt">
        <td style="width: 50%; height: 12pt">
            <asp:Label ID="Label6" runat="server" Font-Size="10pt" Text="账号状态："  style= "TEXT-ALIGN:   right " 
                Width="100px"></asp:Label>
            <asp:Label ID="state" runat="server"></asp:Label>
        </td>
        <td style="width: 50%; height: 12pt">
    
   <img alt="信息变更" src="../images/modify.png" ID="ImageButton1" />
             <img alt="密码修改" src="../images/modifyP.png" height="20px" width="20px" ID="ImageButton2" />
             <asp:Label ID="info" runat="server" ></asp:Label>
        </td>
    </tr>
    </table>
 
    <div id="InfoChange" style=" display:none" >
    <table style="width: 100%">
     <tr>
         <td align="center" colspan="2" class="style1">
             &nbsp;&nbsp;
             <asp:Label ID="Label19" runat="server" Text="基本信息变更" Font-Bold="True" Font-Names="宋体" 
                Font-Size="16pt"  ForeColor="MidnightBlue"></asp:Label>
             &nbsp;&nbsp;</td>
    </tr>
    <tr>
        <td colspan="2" style="background-color: #ffccff">
       
       
            &nbsp;</td>
        </tr>
         <tr >
        <td style="width:50%; height: 12pt;">
            <asp:Label ID="Lyz_mc0" runat="server" Text="公司名称：" Font-Size="10pt"  style= "TEXT-ALIGN:   right " 
                Width="100px" />
            <asp:TextBox ID="TextBox1"  MaxLength="50" runat="server"></asp:TextBox>
        </td>
        <td style="width:50%; height: 12pt;">
            <asp:Label ID="Label21" runat="server" Font-Size="10pt" Text="公司地址："  style= "TEXT-ALIGN:   right " 
                Width="170px"></asp:Label>
            <asp:TextBox ID="TextBox4" MaxLength="80" runat="server"></asp:TextBox>
        </td>
        
        </tr>
        <tr>
        <td style="width:50%; height: 12pt;">
            <asp:Label ID="Lyz_zt0" runat="server" Text="公司电话：" Font-Size="10pt"  style= "TEXT-ALIGN:   right " 
                Width="100px" />
            <asp:TextBox ID="TextBox2" MaxLength="50" runat="server"></asp:TextBox>
        </td>
           <td style="width:50%; height: 12pt;">
            <asp:Label ID="Lyzsydwyw0" runat="server" Font-Size="10pt" Text="公司网址："  style= "TEXT-ALIGN:   right " 
                   Width="170px"></asp:Label>
               <asp:TextBox ID="TextBox5" MaxLength="50" runat="server"></asp:TextBox>
        </td>
        </tr>
        <tr>
        <td style="width: 50%; height: 12pt">
            <asp:Label ID="Lyz_lx0" runat="server" Text="公司电子邮箱：" Font-Size="10pt"  style= "TEXT-ALIGN:   right " 
                Width="100px" />
            <asp:TextBox ID="TextBox3" MaxLength="50" runat="server"></asp:TextBox>
        </td>
        <td style="width: 50%; height: 12pt">
            <asp:Button ID="InfoMod" runat="server" Text="信息变更" onclick="InfoMod_Click" />
            </td>
        </tr>
        
</table>
</div>
    <div id="pswMod" style=" display:none" >
    <table style="width: 100%">
     <tr>
         <td align="center" colspan="2" class="style1">
             &nbsp;&nbsp;
             <asp:Label ID="Label1" runat="server" Text="密码变更" Font-Bold="True" Font-Names="宋体" 
                Font-Size="16pt"  ForeColor="MidnightBlue"></asp:Label>
             &nbsp;&nbsp;</td>
    </tr>
    <tr>
        <td colspan="2" style="background-color: #ffccff">
       
            &nbsp;</td>
        </tr>
         <tr >
        <td style="width:50%; height: 12pt;">
            <asp:Label ID="Label4" runat="server" Text="请输入原始密码：" Font-Size="10pt"  style= "TEXT-ALIGN:   right " 
                Width="122px" />
            <asp:TextBox ID="TextBox6" MaxLength="50" runat="server" TextMode="Password"></asp:TextBox>
        </td>
        <td style="width:50%; height: 12pt;">
            &nbsp;</td>
        
        </tr>
        <tr>
        <td style="width:50%; height: 12pt;">
            <asp:Label ID="Label5" runat="server" Font-Size="10pt" Text="请输入新密码："  style= "TEXT-ALIGN:   right " 
                Width="122px" Height="16px"></asp:Label>
            <asp:TextBox ID="TextBox7" MaxLength="50" TextMode="Password" runat="server"></asp:TextBox>
        </td>
           <td style="width:50%; height: 12pt;">
               &nbsp;</td>
        </tr>
        <tr>
        <td style="width: 50%; height: 12pt">
            <asp:Label ID="Label7" runat="server" Text="请再次输入新密码：" Font-Size="10pt"  style= "TEXT-ALIGN:   right " 
                Width="122px" />
            <asp:TextBox ID="TextBox8"  MaxLength="50" TextMode="Password" runat="server"></asp:TextBox>
        </td>
        <td style="width: 50%; height: 12pt">
            &nbsp;</td>
        </tr>
         <tr>
        <td colspan="2" align="center" style="height: 10px">
       
            <asp:Button ID="PswMod" runat="server" Text="修改" onclick="PswMod_Click"  />
             </td>
        </tr>
    <tr  align="center" width="100%" style=" ">
    <td  align="center" colspan="2" style="height:12pt; color: blue;" width="100%">
         &nbsp;</td>
    </tr>
</table>
</div>
