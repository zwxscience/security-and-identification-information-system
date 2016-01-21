<%@ Control Language="C#" AutoEventWireup="true" CodeFile="ApplyInfo.ascx.cs" Inherits="client_ApplyInfo" %>


<script type="text/javascript" language="javascript">
    //获取输入框内容
    function getToday() {
        //得到今天的年,月,日
        this.now = new Date();
        this.year = this.now.getFullYear();
        this.month = this.now.getMonth() + 1; //0-11
        this.day = this.now.getDate();
    }
   
    $(document).ready(function () {
        var bh = "#<%=bh.ClientID%>";

        $(bh).autocomplete("../client/QRInfo.ashx",
          {
              extraParams: { bhStr: 2 },
              delay: 10,
              minChars: 0,
              matchSubset: 1, //使用对服务器查询的缓存
              cacheLength: 1, //  缓存的长度.即对从数据库中取到的结果集要缓存多少条记录.设成1为不缓存
              onItemSelect: 1,
              onFindValue: 1,
              autoFill: true,
              mustMatch: false,
              maxItemsToShow: 10
          });


        if ($.browser.msie) {
            $('input:checkbox').click(function () {
                this.blur();
                this.focus();
            });
          

        };
        if ($('input:checkbox:[id=Checkbox1]').attr("checked") == true) {
            // $(bh).attr("readonly","readonly");
            $(bh).attr("readOnly", "readOnly");
            $('#InfoTip').html('添加新号是在您拥有编码的最后一位基础上加1');
        }
        $('input:checkbox:[id=option]').change(function () {
            var buttonNone = $('#Info');
            if ($('input:checkbox:[id=option]').attr("checked") == true)
                buttonNone.show(); //选用展开
            else buttonNone.hide(); //选用展开
        });
        $('input:checkbox:[id=Checkbox1]').change(function () {
            var buttonNone = $('#bh');
            if ($('input:checkbox:[id=Checkbox1]').attr("checked") == true) {
                // $("#hid").hide();
                $(bh).attr("readOnly", "readOnly");
                $('#InfoTip').html('添加新号是在您拥有编码的最后一位基础上加1');
            }
            else {
                // $("#hid").show();   //选用时禁用
                $(bh).removeAttr("readOnly");
                $('#InfoTip').html('您也可以不添加在右边输入原有的二维码编号');
            }
        });
       
        var ysrq = "#<%=ysrq.ClientID%>"; //印刷日期开始
        var scrq = "#<%=scrq.ClientID%>"; //生产日期结束
        var str = new getToday();
        str = str.year + (str.month >= 10 ? str.month : ('0' + str.month)) + (str.day >= 10 ? str.day : ('0' + str.day));
        $(ysrq).val(str);
        $(scrq).val(str);
        $(ysrq).datepick({ dateFormat: 'yymmdd' });
        $(scrq).datepick({ dateFormat: 'yymmdd' });

         
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
    #Checkbox1
    {
        width: 20px;
    }
    .style3
    {
        height: 12pt;
        width: 49%;
    }
    .style4
    {
        height: 12pt;
        width: 52%;
    }
</style>

    <div id="VIPInfo" >
    <table style="width: 100%">
     <tr>
         <td align="center" colspan="2" class="style1">
             &nbsp;&nbsp;
             <asp:Label ID="Label19" runat="server" Text="二维码申请" Font-Bold="True" Font-Names="宋体" 
                Font-Size="16pt"  ForeColor="MidnightBlue"></asp:Label>
             &nbsp;&nbsp;</td>
    </tr>
    <tr>
        <td colspan="2" style="background-color: #ffccff;height: 12pt; text-align:center">
        
            <Label ID="InfoTip"   Font-Size="10pt" Width="170px"></Label>
        </td>
        </tr>
    <tr>
        <td style="font-size: 10pt;" class="style4">
        
            <input id="Checkbox1" type="checkbox" checked="checked" value="是否采用新编号" />是否采用新编号
        </td>=
             <td  style="width:50%; height: 12pt;">
        
            <asp:Label ID="QRbh" runat="server" Text="QR码编号：" Font-Size="10pt"  style= "TEXT-ALIGN:   right " 
                Width="110px" Height="18px" />
                   <em id="hid" >
               <asp:TextBox ID="bh" runat="server" MaxLength=24 Width="191px"></asp:TextBox></em>
        </td>
        </tr>
         <tr >
        <td class="style4">
            <asp:Label ID="Lyz_mc0" runat="server" Text="产品名称：" Font-Size="10pt"   style= "TEXT-ALIGN:   right " 
                Width="110px" />
            <asp:TextBox ID="TextBox1" runat="server" MaxLength="50"></asp:TextBox>
        </td>
        <td style="width:50%; height: 12pt;">
            <asp:Label ID="InfoTip0" runat="server" Font-Size="10pt" 
                   Width="243px" ForeColor="Red"></asp:Label>
        </td>
        
        </tr>
        <tr>
        <td class="style4">
            <asp:Label ID="Lyz_zt0" runat="server" Text="生产日期：" Font-Size="10pt"  style= "TEXT-ALIGN:   right " 
                Width="110px" />
            <asp:TextBox ID="scrq" runat="server"></asp:TextBox>
            </td>
        <td style="width: 50%; height: 12pt">
            <asp:Label ID="Lyz_lx0" runat="server" Text="印刷日期：" Font-Size="10pt"  style= "TEXT-ALIGN:   right " 
                Width="110px" />
            <asp:TextBox ID="ysrq" runat="server" Width="190px"></asp:TextBox>
        </td>
        
        </tr>
        
        <tr>
        <td class="style4">
            <asp:Label ID="Lyz_mc2" runat="server" Text="选择尺寸(mm)：" Font-Size="10pt"  style= "TEXT-ALIGN: right " 
                 Width="110px" />
            <asp:DropDownList ID="DropDownList1" runat="server" 
                >
                <asp:ListItem Value="5*5">5*5</asp:ListItem>
                <asp:ListItem Value="5*5">6*6</asp:ListItem>
                <asp:ListItem Value="7*7">7*7</asp:ListItem>
                <asp:ListItem Value="8*8">8*8</asp:ListItem>
                <asp:ListItem Value="9*9">9*9</asp:ListItem>
                <asp:ListItem Value="10*10">10*10</asp:ListItem>
                <asp:ListItem Value="11*11">11*11</asp:ListItem>
                <asp:ListItem Value="12*12">12*12</asp:ListItem>
            </asp:DropDownList>
        </td>
        <td style="width: 50%; height: 12pt;font-size:10pt">
            <input id="option" type="checkbox" value="选填项" checked="checked"  Width="100px"/>选填项
            </td>
        </tr>
        
        </table>
</div>
   
    <div id="Info"  >
    <table style="width: 100%">

         <tr >
        <td class="style3">
            <asp:Label ID="Label2" runat="server" Text="质检人：" Font-Size="10pt"  style= "TEXT-ALIGN:   right " 
               Width="110px" />
            <asp:TextBox ID="TextBox7"  MaxLength="50" runat="server"></asp:TextBox>
        </td>
        <td style="width:50%; height: 12pt;">
            <asp:Label ID="Label3" runat="server" Text="接收单位:" Font-Size="10pt"  style= "TEXT-ALIGN:   right " 
                Width="110px"  />
            <asp:TextBox ID="TextBox10" MaxLength="50" runat="server" Width="190px"></asp:TextBox>
        </td>
        
        </tr>
         <tr >
        <td class="style3">
            <asp:Label ID="Label4" runat="server" Text="产品批号：" Font-Size="10pt"  style= "TEXT-ALIGN:   right " 
               Width="110px" />
            <asp:TextBox ID="TextBox4" MaxLength="50" runat="server"></asp:TextBox>
        </td>
        <td style="width:50%; height: 12pt;">
            <asp:Label ID="Label5" runat="server" Font-Size="10pt"  style= "TEXT-ALIGN:   right " 
                Width="110px" Height="16px">存储地点:</asp:Label>
            <asp:TextBox ID="TextBox8" MaxLength="50" runat="server" Width="190px"></asp:TextBox>
        </td>
        
        </tr>
        <tr>
        <td class="style3">
            <asp:Label ID="Label6" runat="server" Text="产品性能：" Font-Size="10pt"  style= "TEXT-ALIGN:   right " 
                Width="110px" />
            <asp:TextBox ID="TextBox5" MaxLength="50" runat="server"></asp:TextBox>
        </td>
           <td style="width:50%; height: 12pt;">
            <asp:Label ID="Label7" runat="server" Font-Size="10pt"  style= "TEXT-ALIGN:   right " 
                   Width="110px">质保内容:</asp:Label>
            <asp:TextBox ID="TextBox9" runat="server" Width="186px"></asp:TextBox>
        </td>
        </tr>
        <tr>
        <td class="style3">
            <asp:Label ID="Label8" runat="server" Text="本次生产总量：" Font-Size="10pt"  style= "TEXT-ALIGN:   right " 
                Width="110px" />
            <asp:TextBox ID="TextBox6" MaxLength="50" runat="server"></asp:TextBox>
        </td>
        <td style="width: 50%; height: 12pt">
            <asp:Label ID="Label9" runat="server" Font-Size="10pt"  style= "TEXT-ALIGN:   right " 
                   Width="110px">发往销售目的地:</asp:Label>
            <asp:TextBox ID="TextBox11" MaxLength="80" runat="server" Width="190px"></asp:TextBox>
            </td>
        </tr>
        
        <tr>
        <td class="style3">
            <asp:Label ID="Label20" runat="server" Text="产品备注：" Font-Size="10pt"  style= "TEXT-ALIGN:   right; vertical-align:middle " 
                Width="110px" />
            <asp:TextBox ID="TextBox12" runat="server" Height="79px" TextMode="MultiLine" 
                Width="389px"></asp:TextBox>
        </td>
       
        </tr>
        
</table>
</div>
<table class="style2">
    <tr>
        <td align=right>
            <asp:Button ID="Button1" runat="server" Text="保存" onclick="Button1_Click" />
        </td>
        <td align=left>
            <asp:Button ID="Button2" runat="server" Text="提交" onclick="Button2_Click" />
        </td>
    </tr>
</table>

