<%@ Control Language="C#" AutoEventWireup="true" CodeFile="ProcInfo.ascx.cs" Inherits="client_ProcInfo" %>

    <script type="text/javascript" src="../JS/jquery-1.3.1.js"></script>
<script type="text/javascript" language="javascript">
   //获取输入框内容
        $(document).ready(function () {
        $("#return").click(function () {
            window.location.href = 'QueryInfo.aspx'; return false;
        });
</script>


<style type="text/css">
    .style1
    {
        height: 12pt;
    }
    .style2
    {
        width: 100%;
    }
    .style3
    {
        width: 50%;
        }
    .style4
    {
        height: 12pt;
        width: 50%;
    }
</style>

    <div id="VIPInfo" >
    <table style="width: 100%">
     <tr>
         <td align="center" colspan="2" class="style1">
             &nbsp;&nbsp;
             <asp:Label ID="Label19" runat="server" Text="二维码信息" Font-Bold="True" Font-Names="宋体" 
                Font-Size="16pt"  ForeColor="MidnightBlue"></asp:Label>
             &nbsp;&nbsp;</td>
    </tr>
    <tr>
        <td colspan="2" style="background-color: #ffccff; text-align:center; font-size:10pt" >
        
            <asp:Label ID="Label23" runat="server"></asp:Label>
        </td>
        </tr>
         <tr >
        <td style="font-size:10pt" class="style3">
            <asp:Label ID="Label24" runat="server" Text="二维码编号：" Width="100px"  style= "TEXT-ALIGN:   right "   ></asp:Label>
            <asp:Label ID="Lyz_mc1" runat="server" Font-Size="10pt" 
                Width="300px" />
        </td>
        <td style="width:50%; height: 12pt;font-size:10pt">
            <asp:Label ID="Label38" runat="server" Font-Size="10pt" Text="尺寸(mm):" 
                Width="113px"  style= "TEXT-ALIGN:   right "  ></asp:Label>
            <asp:Label ID="Lyz_mc2" runat="server" Font-Size="10pt" 
                Width="200px" Height="16px" />
        </td>
        
        </tr>
         <tr >
        <td class="style4">
            <asp:Label ID="Label26" runat="server" Font-Size="10pt" Text="产品名称：" Width="100px"  style= "TEXT-ALIGN:   right "   ></asp:Label>
            <asp:Label ID="Lyz_mc0" runat="server" Font-Size="10pt" 
                Width="302px" />
        </td>
        <td style="width:50%; height: 12pt;">
            <asp:Label ID="Label37" runat="server" Font-Size="10pt" Text="生产日期:" 
                Width="113px"  style= "TEXT-ALIGN:   right "  ></asp:Label>
            <asp:Label ID="Lyz_zt1" runat="server" Font-Size="10pt" 
                Width="132px" Height="16px" style="margin-left: 0px" />
        </td>
        
        </tr>
        <tr>
        <td class="style4">
            <asp:Label ID="Label27" runat="server" Font-Size="10pt" Text="印刷日期：" Width="100px"  style= "TEXT-ALIGN:   right "  ></asp:Label>
            <asp:Label ID="Lyz_lx1" runat="server" Font-Size="10pt" 
                Width="294px"  />
        </td>
           <td style="width:50%; height: 12pt;">
               &nbsp;</td>
        </tr>
                
</table>
</div>
   
    <div id="Info" >
    <table style="width: 100%">

         <tr >
        <td style="width:50%; height: 12pt;">
            <asp:Label ID="Label28" runat="server" Font-Size="10pt" Text="质检人：" 
                Width="100px"  style= "TEXT-ALIGN:   right "   ></asp:Label>
            <asp:Label ID="Label2" runat="server" Font-Size="10pt" 
                Width="303px" />
        </td>
        <td style="width:50%; height: 12pt;">
            <asp:Label ID="Label36" runat="server" Font-Size="10pt" Text="接收单位:" 
                Width="113px"  style= "TEXT-ALIGN:   right "  ></asp:Label>
            <asp:Label ID="Label3" runat="server" Font-Size="10pt" 
                Width="198px" Height="16px" />
        </td>
        
        </tr>
         <tr >
        <td style="width:50%; height: 12pt;">
            <asp:Label ID="Label29" runat="server" Font-Size="10pt" Text="产品批号：" 
                Width="100px"  style= "TEXT-ALIGN:   right "   ></asp:Label>
            <asp:Label ID="Label4" runat="server" Font-Size="10pt" 
                Width="295px" Height="16px" />
        </td>
        <td style="width:50%; height: 12pt;">
            <asp:Label ID="Label35" runat="server" Font-Size="10pt" Text="存储地点:" 
                Width="113px"  style= "TEXT-ALIGN:   right "  ></asp:Label>
            <asp:Label ID="Label5" runat="server" Font-Size="10pt" 
                Width="200px" Height="16px"></asp:Label>
        </td>
        
        </tr>
        <tr>
        <td style="width:50%; height: 12pt;">
            <asp:Label ID="Label30" runat="server" Font-Size="10pt" Text="产品性能：" 
                Width="100px"  style= "TEXT-ALIGN:   right "  ></asp:Label>
            <asp:Label ID="Label6" runat="server" Font-Size="10pt" 
                Width="305px" Height="16px" />
        </td>
           <td style="width:50%; height: 12pt;">
            <asp:Label ID="Label34" runat="server" Font-Size="10pt" Text="质保内容:" 
                   Width="113px"  style= "TEXT-ALIGN:   right "  ></asp:Label>
            <asp:Label ID="Label7" runat="server" Font-Size="10pt" 
                   Width="220px" Height="16px"></asp:Label>
        </td>
        </tr>
        <tr>
        <td style="width: 50%; height: 12pt">
            <asp:Label ID="Label25" runat="server" Font-Size="10pt" Text="本次生产总量：" Width="100px"  style= "TEXT-ALIGN:   right "  ></asp:Label>
            <asp:Label ID="Label8" runat="server" Font-Size="10pt" 
                Width="299px" />
        </td>
        <td style="width: 50%; height: 12pt">
            <asp:Label ID="Label33" runat="server" Font-Size="10pt" Text="发往销售目的地:" 
                Width="113px"  style= "TEXT-ALIGN:   right "  ></asp:Label>
            <asp:Label ID="Label9" runat="server" Font-Size="10pt" 
                   Width="194px" Height="16px"></asp:Label>
            </td>
        </tr>
        
        <tr>
        <td style="width: 50%; height: 12pt">
            <asp:Label ID="Label31" runat="server" Font-Size="10pt" Text="申请时间：" 
                Width="100px"  style= "TEXT-ALIGN:   right "  ></asp:Label>
            <asp:Label ID="Label21" runat="server" Font-Size="10pt" 
                Width="300px" />
        </td>
        <td style="width: 50%; height: 12pt">
            <asp:Label ID="Label32" runat="server" Font-Size="10pt" Text="当前状态："   
                Width="113px"  style= "TEXT-ALIGN:   right "></asp:Label>
            <asp:Label ID="Label22" runat="server" Font-Size="10pt" 
                Width="202px" Height="16px" />
            </td>
        </tr>
        
        <tr>
        <td style=" width: 50%;">
            <asp:Label ID="Label20" runat="server" Text="产品备注：" Font-Size="10pt" 
              Width="100px"  style= "TEXT-ALIGN:   right; vertical-align:middle "   />
            <asp:TextBox ID="TextBox12" runat="server" Height="79px" TextMode="MultiLine" 
                Width="296px" ReadOnly="True"></asp:TextBox>
        </td>
         <td>
         <em id="imageP">
             <asp:Image ID="Image1" runat="server" Height="111px" ToolTip="二维码" 
                 Width="111px" Visible="False" />
            <asp:Button ID="Button4" runat="server" Text="下载" Visible="False" 
                 onclick="Button4_Click" /></em>
        </td>
        </tr>
        
        </table>
</div>
<table class="style2">
    <tr>
        <td align=left>
            <asp:Label ID="Label40" runat="server" Text="审批意见：" Font-Size="10pt"  style=" height: 12pt; vertical-align:middle" 
                Width="100px" />
            <asp:TextBox ID="spyj" runat="server" Height="79px" TextMode="MultiLine" 
                Width="389px" ToolTip="请您输入审批意见" ReadOnly="True"></asp:TextBox>
        
       
        </td>
    </tr>
    <tr>
        <td align=center>
            <asp:Button ID="Button1" runat="server" Text="提交" onclick="Button1_Click" 
                style="height: 26px" Visible="False" />
        &nbsp;&nbsp;
            <asp:Button ID="Button2" runat="server" Text="生成图像" onclick="Button2_Click" 
                Visible="False" />
        </td>
    </tr>
    <tr>
        <td align=center>
           
            &nbsp;</td>
    </tr>
</table>

