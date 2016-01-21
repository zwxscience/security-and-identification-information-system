<%@ Control Language="C#" AutoEventWireup="true" CodeFile="ProcCheck.ascx.cs" Inherits="check_ProcCheck" %>
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
        
          
            <asp:Label ID="Label35" runat="server"></asp:Label>
            </td>
        </tr>
         <tr >
        <td style="height: 12pt;" colspan="2">
            <asp:Label ID="Label21" runat="server" Text="选择红外图像" Font-Size="10pt" ></asp:Label>
               <asp:FileUpload ID="FileUpload1" runat="server" />
            <asp:Button ID="Button5" runat="server" Text="上传并识别" onclick="Button5_Click" />
        </td>
        <td class="style4" colspan="2" style="  text-align:center; font-size:10pt">
          
           <input  id="Button6" type="button" value="查看相关数据"  
                 />
        </td>
        
        </tr>
                  <tr>
                      <td style="width:15%; " rowspan="3">
                          <asp:Image ID="Image1" runat="server" Height="150px" Width="150px" 
                              ImageUrl="~/images/default.bmp" /></td>
                      <td style="width:35%; height: 12pt; font-size:10pt"  >
                          图像名称:<asp:Label ID="Label24" runat="server" Text="未知"></asp:Label>
                      </td>
                      <td  style=" width:15%" class="style4" rowspan="3">
                          <asp:Image ID="Image2" runat="server" Height="150px" Width="150px" 
                              ImageUrl="~/images/default.bmp" />
                      </td>
                      <td  style="width:35%;height:12pt;Font-Size:10pt">
                          文本内容：<asp:Label ID="Label22" runat="server" Font-Size="10pt"></asp:Label>
                      </td>
                  </tr>
                  <tr>
                      <td style="width:35%; height: 12pt; font-size:10pt">
                          图像大小:<asp:Label ID="Label23" runat="server" Text="未知"></asp:Label>
                      </td>
                      <td style="width:35%; height: 12pt;Font-Size:10pt">
                          &nbsp;&nbsp;&nbsp; 版本号：<asp:Label ID="Label25" runat="server" Font-Size="10pt"></asp:Label>
                      </td>
                  </tr>
                  <tr>
                      <td style="width:35%; height: 12pt;font-size:10pt">
                          &nbsp;&nbsp;&nbsp; IP地址:<asp:Label ID="Label27" runat="server" Text="未知"></asp:Label>
                      </td>
                      <td style="width:35%; height:12pt;Font-Size:10pt">
                          纠错等级：<asp:Label ID="Label26" runat="server" Font-Size="10pt"></asp:Label>
                      </td>
                  </tr>
        </table>
   
        </asp:Panel>

    <div id="VIPInfo" style=" display:none" >
    <table style="width: 100%; font-size:10pt">
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
            <asp:Label ID="Label38" runat="server" Text="二维码编号：" Width="100px" style= "TEXT-ALIGN:   right " ></asp:Label>
            <asp:Label ID="Lyz_mc1" runat="server" Font-Size="10pt" 
                Width="210px" />
        </td>
        <td style="width:50%; height: 12pt;">
            <asp:Label ID="Label45" runat="server" Text="尺寸（mm）：" Width="110px" style= "TEXT-ALIGN:   right " ></asp:Label>
            <asp:Label ID="Lyz_mc2" runat="server" Font-Size="10pt" 
                Width="210px" />
        </td>
        
        </tr>
         <tr >
        <td style="width:50%; height: 12pt;">
            <asp:Label ID="Label39" runat="server" Text="产品名称：" Width="100px" style= "TEXT-ALIGN:   right " ></asp:Label>
&nbsp;<asp:Label ID="Lyz_mc0" runat="server" Font-Size="10pt" 
                Width="210px" style="margin-top: 0px" />
        </td>
        <td style="width:50%; height: 12pt;">
            <asp:Label ID="Label46" runat="server" Text="生产日期：" Width="110px" style= "TEXT-ALIGN:   right " ></asp:Label>
&nbsp;<asp:Label ID="Lyz_zt1" runat="server" Font-Size="10pt" 
                Width="210px" />
        </td>
        
        </tr>
        <tr>
        <td style="width:50%; height: 12pt;">
            <asp:Label ID="Label40" runat="server" Text="印刷日期：" Width="100px" style= "TEXT-ALIGN:   right " ></asp:Label>
&nbsp;<asp:Label ID="Lyz_lx1" runat="server" Font-Size="10pt" 
                Width="210px" />
        </td>
           <td style="width:50%; height: 12pt; font-size:10pt">
               <asp:Label ID="Label47" runat="server" Text="当前状态：" Width="110px" style= "TEXT-ALIGN:   right " ></asp:Label>
               <asp:Label ID="Label32" runat="server" Font-Size="10pt" 
                Width="210px" Height="16px" /></td>
        </tr>
                
      <tr >
        <td style="width:50%; height: 12pt;">
            <asp:Label ID="Label41" runat="server" Text="质检人：" Width="100px" style= "TEXT-ALIGN:   right " ></asp:Label>
&nbsp;<asp:Label ID="Label2" runat="server" Font-Size="10pt" 
                Width="210px" />
        </td>
        <td style="width:50%; height: 12pt;">
          <asp:Label ID="Label48" runat="server" Text="  接收单位：" style= "TEXT-ALIGN:   right " 
                Width="110px"></asp:Label>
            <asp:Label ID="Label3" runat="server" Font-Size="10pt" 
                Width="210px" />
        </td>
        
        </tr>
         <tr >
        <td style="width:50%; height: 12pt;">
            <asp:Label ID="Label42" runat="server" Text="产品批号：" Width="100px" style= "TEXT-ALIGN:   right " ></asp:Label>
&nbsp;<asp:Label ID="Label4" runat="server" Font-Size="10pt" 
                Width="210px" />
        </td>
        <td style="width:50%; height: 12pt;">
         
            <asp:Label ID="Label49" runat="server" Text="  存储地点：" Width="110px" 
                style= "TEXT-ALIGN:   right " ></asp:Label>
            <asp:Label ID="Label5" runat="server" Font-Size="10pt" 
                Width="210px" Height="16px"></asp:Label>
        </td>
        
        </tr>
        <tr>
        <td style="width:50%; height: 12pt;">
            <asp:Label ID="Label43" runat="server" Text="产品性能：" Width="100px" style= "TEXT-ALIGN:   right " ></asp:Label>
            <asp:Label ID="Label6" runat="server" Font-Size="10pt" 
                Width="210px" />
        </td>
           <td style="width:50%; height: 12pt;">
            <asp:Label ID="Label50" runat="server" Text="质保内容：" style= "TEXT-ALIGN:   right " 
                   Width="110px"></asp:Label>
               <asp:Label ID="Label7" runat="server" Font-Size="10pt" 
                   Width="210px"></asp:Label>
        </td>
        </tr>
        <tr>
        <td style="width: 50%; height: 12pt">
           &nbsp;<asp:Label ID="Label37" runat="server" Text="本次生产总量：" Width="100px" style= "TEXT-ALIGN:   right " ></asp:Label>
            <asp:Label ID="Label8" runat="server" Font-Size="10pt" 
                Width="210px" />
        </td>
        <td style="width: 50%; height: 12pt">
           <asp:Label ID="Label51" runat="server" Text=" 发往销售目的地：" style= "TEXT-ALIGN:   right " 
                Width="110px"></asp:Label>
            <asp:Label ID="Label9" runat="server" Font-Size="10pt" 
                   Width="210px"></asp:Label>
            </td>
        </tr>

    <tr>
        <td align=left>
            <asp:Label ID="Label44" runat="server" Text="申请日期：" Width="100px" 
                style= "TEXT-ALIGN:   right " ></asp:Label>
            <asp:Label ID="Label34" runat="server" Width="210px"></asp:Label>
        </td>
        <td align=left>
            &nbsp;</td>
    </tr>
</table>

        <table>
        <tr>
        <td style=" height: 12pt">
            <asp:Label ID="Label20" runat="server" Text="产品备注：" Font-Size="10pt"  style= "TEXT-ALIGN:   right; vertical-align:middle" 
                Width="100px" />
            <asp:TextBox ID="TextBox12" runat="server" Height="79px" TextMode="MultiLine" 
                Width="300px" ReadOnly="True"></asp:TextBox>
        </td>
        </tr>
        
</table>
</div>

