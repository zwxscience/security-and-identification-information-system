<%@ Control Language="C#" AutoEventWireup="true" CodeFile="UpPInfo.ascx.cs" Inherits="check_UpPInfo" %>
<%@  Import   Namespace="System.Data"   %>

<script type="text/javascript" language="javascript">
   //获取输入框内容
    $(document).ready(function () {
       
            $("#Button6").toggle(function () {
            $("#VIPInfo").show('fast');
        }, function () {
            $("#VIPInfo").hide('slow');
            });
      
    });


</script>


<style type="text/css">
    .style1
    {
        height: 12pt;
    }
    .style4
    {
    }
</style>
<asp:Panel ID="Panel1" runat="server" Width="100%" 
             GroupingText="文件上传" BackColor="White" ForeColor="#003399"  >

              <table style="width: 100%">
     <tr>
         <td align="center" colspan="4" class="style1">
             &nbsp;&nbsp;
             <asp:Label ID="Label1" runat="server" Text="图像信息" Font-Bold="True" Font-Names="宋体" 
                Font-Size="16pt"  ForeColor="MidnightBlue"></asp:Label>
             &nbsp;&nbsp;</td>
    </tr>
    <tr>
        <td colspan="4" style="background-color: #ffccff;height: 12pt; font-size:10pt; text-align:center">
        
          
            <asp:Label ID="Label35" runat="server" Text="Label"></asp:Label>
        </td>
        </tr>
         <tr >
        <td style="height: 12pt;" colspan="2">
            &nbsp;</td>
        <td class="style4" colspan="2" style="  text-align:center; font-size:10pt">
          
           <input  id="Button6" type="button" value="查看相关数据"  
                 />
        </td>
        
        </tr>
                  <tr>
                      <td style="width:15%; " rowspan="3">
                          <asp:Image ID="Image1" runat="server" Height="150px" Width="150px" /></td>
                      <td style="width:35%; height: 12pt; font-size:10pt"  >
                          图像名称:<asp:Label ID="Label24" runat="server" Text="未知"></asp:Label>
                      </td>
                      <td  style=" width:15%" class="style4" rowspan="3">
                          <asp:Image ID="Image2" runat="server" Height="150px" Width="150px" />
                      </td>
                      <td  style="width:35%;height:12pt;Font-Size:10pt">
                          文本内容：<asp:Label ID="Label22" runat="server" Font-Size="10pt"></asp:Label>
                      </td>
                  </tr>
                  <tr>
                      <td style="width:35%; height: 12pt; font-size:10pt">
                          查询时间:<asp:Label ID="Label23" runat="server" Text="未知"></asp:Label>
                      </td>
                      <td style="width:35%; height: 12pt;Font-Size:10pt">
                          版本号：<asp:Label ID="Label25" runat="server" Font-Size="10pt"></asp:Label>
                      </td>
                  </tr>
                  <tr>
                      <td style="width:35%; height: 12pt;font-size:10pt">
                          &nbsp;&nbsp;&nbsp; IP地址:<asp:Label ID="Label36" runat="server" Text="未知"></asp:Label>
                      </td>
                      <td style="width:35%; height:12pt;Font-Size:10pt">
                          纠错等级：<asp:Label ID="Label26" runat="server" Font-Size="10pt"></asp:Label>
                      </td>
                  </tr>
        </table>
   
        </asp:Panel>

    <div id="VIPInfo" style=" display:none; font-size:10pt"  >
    <table style="width: 100%">
     <tr>
         <td align="center" colspan="2" class="style1">
             &nbsp;&nbsp;
             <asp:Label ID="Label19" runat="server" Text="二维码信息" Font-Bold="True" Font-Names="宋体" 
                Font-Size="16pt"  ForeColor="MidnightBlue"></asp:Label>
             &nbsp;&nbsp;</td>
    </tr>
     <%
 
    Datacon dacon = new Datacon();
    string sqlstr = "select * from proApply where AllocFlag=4 and code='" + Label22.Text + "'";
    DataSet myds = dacon.getds(sqlstr);
    //历遍所有的
    if (myds.Tables[0].Rows.Count>1)
    {
        Label33.Text = "查到与图像相关的QR码信息大于一条，更多请点击...";
       
         %>
    <tr>
   
        <td colspan="2" style="background-color: #ffccff;height: 12pt; font-size:10pt; text-align:center">
     
           <a href="QueryInfo.aspx?code=<% =myds.Tables[0].Rows[0]["code"].ToString()%>" target="_parent"> <asp:Label ID="Label33" runat="server" Text="Label"></asp:Label></a>
        </td>
       
        </tr> <%
        
}
    else if (myds.Tables[0].Rows.Count ==1) Label33.Text = "查到一条记录";
    else Label33.Text = "无记录";
                
                   %>
         <tr >
        <td style="width:50%; height: 12pt;">
            二维码编号：<asp:Label ID="Lyz_mc1" runat="server" Text="" Font-Size="10pt" 
                Width="418px" />
        </td>
        <td style="width:50%; height: 12pt;">
        尺寸（mm）：<asp:Label ID="Lyz_mc2" runat="server" Text="" Font-Size="10pt" 
                Width="321px" />
        </td>
        
        </tr>
         <tr >
        <td style="width:50%; height: 12pt;">
           产品名称： <asp:Label ID="Lyz_mc0" runat="server" Text="" Font-Size="10pt" 
                Width="343px" />
        </td>
        <td style="width:50%; height: 12pt;">
           生产日期： <asp:Label ID="Lyz_zt1" runat="server" Text="" Font-Size="10pt" 
                Width="393px" />
        </td>
        
        </tr>
        <tr>
        <td style="width:50%; height: 12pt;">
          印刷日期：  <asp:Label ID="Lyz_lx1" runat="server" Text="" Font-Size="10pt" 
                Width="408px" />
        </td>
           <td style="width:50%; height: 12pt; font-size:10pt">
               当前状态：<asp:Label ID="Label32" runat="server" Font-Size="10pt" 
                Width="364px" Height="16px" /></td>
        </tr>
                
      <tr >
        <td style="width:50%; height: 12pt;">
           质检人： <asp:Label ID="Label2" runat="server" Text="" Font-Size="10pt" 
                Width="422px" />
        </td>
        <td style="width:50%; height: 12pt;">
            接收单位：<asp:Label ID="Label3" runat="server" Text="" Font-Size="10pt" 
                Width="448px" />
        </td>
        
        </tr>
         <tr >
        <td style="width:50%; height: 12pt;">
           产品批号： <asp:Label ID="Label4" runat="server" Text="" Font-Size="10pt" 
                Width="386px" />
        </td>
        <td style="width:50%; height: 12pt;">
           存储地点: <asp:Label ID="Label5" runat="server" Font-Size="10pt" 
                Width="438px" Height="16px"></asp:Label>
        </td>
        
        </tr>
        <tr>
        <td style="width:50%; height: 12pt;">
            产品性能:<asp:Label ID="Label6" runat="server" Text="" Font-Size="10pt" 
                Width="366px" />
        </td>
           <td style="width:50%; height: 12pt;">
            质保内容:<asp:Label ID="Label7" runat="server" Font-Size="10pt" 
                   Width="427px"></asp:Label>
        </td>
        </tr>
        <tr>
        <td style="width: 50%; height: 12pt">
           本次生产总量： <asp:Label ID="Label8" runat="server" Text="" Font-Size="10pt" 
                Width="394px" />
        </td>
        <td style="width: 50%; height: 12pt">
            发往销售目的地：<asp:Label ID="Label9" runat="server" Font-Size="10pt" 
                   Width="434px"></asp:Label>
            </td>
        </tr>

    <tr>
        <td align=left>
            申请时间:<asp:Label ID="Label34" runat="server"></asp:Label>
        </td>
        <td align=left>
            &nbsp;</td>
    </tr>
</table>

        <table>
        <tr>
        <td style=" width: 25%;height: 12pt">
            <asp:Label ID="Label20" runat="server" Text="产品备注：" Font-Size="10pt" 
                Width="100px" />
        </td>
         <td style="width: 75%; height: 12pt">
            <asp:TextBox ID="TextBox12" runat="server" Height="79px" TextMode="MultiLine" 
                Width="466px" ReadOnly="True"></asp:TextBox>
        </td>
        </tr>
        
</table>
</div>

