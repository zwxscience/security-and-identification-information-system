<%@ Control Language="C#" AutoEventWireup="true" CodeFile="QueryInfo.ascx.cs" Inherits="query_SealInfo" %>
<%@ Register Src="InfoShow.ascx" TagName="InfoShow" TagPrefix="uc1" %>

<script type="text/javascript" language="javascript">
   //获取输入框内容
    var cpbh = "#<%=cpbh.ClientID%>"; //
    var cpmc = "#<%=cpmc.ClientID%>"; //
    var ksrq = "#<%=ksrq.ClientID%>"; //
    var jzrq = "#<%=jzrq.ClientID%>"; //
    function getToday() {
        //得到今天的年,月,日
        this.now = new Date();
        this.year = this.now.getFullYear();
        this.month = this.now.getMonth() + 1; //0-11
        this.day = this.now.getDate();
    }
   
       
    function findValue(li)
     {  
        if (li == null)  return alert("No match!");
        if (!!li.extra)
        var sValue =unescape(li.extra[0]);
      
    }
    function selectItem(li)
     {
        findValue(li);
     }
   
  $(document).ready(function()
     {
         $(cpbh).autocomplete("../check/QRInfo.ashx",
          {
            extraParams: { cpbhStr:1}, 
            delay: 10,
            minChars:0,
            matchSubset: 1,//使用对服务器查询的缓存
            cacheLength: 1,//  缓存的长度.即对从数据库中取到的结果集要缓存多少条记录.设成1为不缓存
            onItemSelect: selectItem,
            onFindValue: findValue,
            autoFill: true,
            mustMatch:false,
            maxItemsToShow: 10
        });

        $(cpmc).autocomplete("../check/QRInfo.ashx",
          {
              extraParams: { cpmcStr:2 }, 
            delay: 10,
            minChars: 0,
            matchSubset: 1,//使用对服务器查询的缓存
            cacheLength: 1,//  缓存的长度.即对从数据库中取到的结果集要缓存多少条记录.设成1为不缓存
            onItemSelect: selectItem,
            onFindValue: findValue,
            autoFill: true,
            mustMatch:false,
            maxItemsToShow: 10
        });

        var ksrq = "#<%=ksrq.ClientID%>"; //日期开始
        var jzrq = "#<%=jzrq.ClientID%>"; //日期结束
        var str = new getToday();
        str = str.year + (str.month >= 10 ? str.month : ('0' + str.month)) + (str.day >= 10 ? str.day : ('0' + str.day));
//        $(ksrq).val(str);
//        $(jzrq).val(str);
        $(ksrq).datepick({ dateFormat: 'yymmdd' });
        $(jzrq).datepick({ dateFormat: 'yymmdd' });

        $("#more").toggle(function () {
          $("#moreS").show('fast');
      }, function () { $("#moreS").hide('slow'); });

    });       
</script>

<link href="../CSS/InfoShow.css" type="text/css" />
<link href="../CSS/InfoShow.css" type="text/css" />
<style type="text/css">
    .style1
    {
        height: 12pt;
        }
</style>
<table style="width: 100%">
    <tr style="height:20pt">
        <td align="center">
        <asp:Label ID="Label2" runat="server" Text="信息查询" Font-Bold="True" 
                Font-Names="宋体" Font-Size="16pt"  ForeColor="MidnightBlue"></asp:Label>
        </td>
    </tr>
    <tr style="height:5px; background-color: #ffccff">
        <td align="center" >
        </td>
    </tr>
    <tr style="height: 12pt">
        <td class="style1">
            <asp:Label ID="Lyzspr" runat="server" Font-Size="10pt" Text="按产品编号：" style= "TEXT-ALIGN:   right "
                Width="96px"></asp:Label>
            <asp:TextBox ID="cpbh" runat="server" 
                ToolTip="请输入产品编号" Width="34%"></asp:TextBox>
                <em id="more" style="font-size:10pt; "><img alt="更多搜索方式" height="25" 
                src="../images/more.png" /></em></td>
    </tr>
      </table>
    
<div  id="moreS" style=" display:none">
<table style="width: 100%">
    <tr style="height: 12pt">
        <td class="style1">
            <asp:Label ID="Label5" runat="server" Font-Size="10pt" Text="按产品名称：" style= "TEXT-ALIGN:   right "
                Width="97px"></asp:Label>
            <asp:TextBox
                ID="cpmc" runat="server" ToolTip="请输入产品名称" Width="34%"></asp:TextBox></td>
    </tr>
    <tr style="height: 12pt">
        <td align=left class="style1" >
            <asp:Label ID="Lyz_jbr" runat="server" Text="生产日期区间：" Font-Size="10pt" style= "TEXT-ALIGN:   right "
                Width="96px" Height="16px"   ></asp:Label>
            <asp:TextBox ID="ksrq" runat="server" 
                Width="14%"　ToolTip="请输入开始日期，数字形式如：19870318" style="margin-left: 0px"></asp:TextBox>
            --<asp:TextBox 
                ID="jzrq" runat="server" 
                ToolTip="请输入截止日期，数字形式如：19870318" Width="18%"></asp:TextBox>
            </td>
    </tr>
    </table>
    </div>
        <table style="width: 100%">
     <tr style="height:12pt">
         <td align="center">
            <asp:Button ID="btnjq" runat="server" Text="精确查询" OnClick="btnjq_Click" />&nbsp;&nbsp;
             &nbsp;&nbsp;<asp:Button ID="btnmh" runat="server" Text="模糊查询" OnClick="btnmh_Click" />
         &nbsp;&nbsp;&nbsp;
             </td>
    </tr>
    <tr>
        <td >
        
        <asp:GridView ID="QRInfo" runat="server" AllowSorting="True" AutoGenerateColumns="False"
            BackColor="White" BorderColor="Transparent" BorderStyle="None" BorderWidth="1px"
            CellPadding="2" EmptyDataText="无记录" Font-Size="10pt" HorizontalAlign="Left" Style="vertical-align: middle;
            text-align: left" Width="100%" 
                onselectedindexchanged="QRInfo_SelectedIndexChanged" >
            <FooterStyle BackColor="#99CCCC" ForeColor="#003399" />
            <RowStyle BackColor="White" BorderColor="Transparent" BorderWidth="1px" ForeColor="#003399"
                Height="11pt" />
            <SelectedRowStyle BackColor="Transparent" Font-Bold="True" ForeColor="LightSlateGray" />
            <PagerStyle BackColor="#99CCCC" ForeColor="#003399" HorizontalAlign="Right" />
            <HeaderStyle BackColor="#69A4B5" Font-Bold="True" ForeColor="MidnightBlue" Height="11pt"
                HorizontalAlign="Center" />
            <AlternatingRowStyle BackColor="AliceBlue" BorderColor="Transparent" BorderWidth="1px" />
            <EmptyDataRowStyle HorizontalAlign="Center" />
            <Columns>
                <asp:BoundField DataField="code" HeaderText="产品编号" />
                <asp:BoundField DataField="productName" HeaderText="产品名称" />
                <asp:BoundField DataField="productDate" HeaderText="生产日期" />
                 <asp:BoundField DataField="AllocFlag" HeaderText="审批状态"  />
                <asp:BoundField DataField="Applydate" HeaderText="申请日期" />
        
                <asp:HyperLinkField DataNavigateUrlFields="id" DataNavigateUrlFormatString="ProcInfo.aspx?id={0}"    Text="详细》">
                    <ItemStyle Width="45pt" Font-Strikeout="False" />
                    <HeaderStyle Width="20px" />
                </asp:HyperLinkField>
                
            </Columns>
        </asp:GridView>
            
        
        </td>
        </tr>
         <tr>
        <td align="right" style="height: 10px">
                <asp:Label ID="Label10" runat="server" 
                Text="审批状态注释：0--已经保存，1--已经提交（未受理），2---受理未通过" Font-Size="10pt" ></asp:Label>

        </td>
        </tr>
         <tr>
        <td align="right" style="height: 10px">
            <asp:Panel ID="Panel_jq" runat="server" Direction="LeftToRight" ForeColor="#003399" Height="11px" HorizontalAlign="Right" Width="100%" Visible="False">
                &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                <asp:Label ID="Label1" runat="server" Font-Size="10pt" Text="共查到记录0条"></asp:Label>
                &nbsp;&nbsp;&nbsp;
                <asp:Label ID="Label8" runat="server" Text="总页数:" Font-Size="10pt" /><asp:Label ID="jq_all" runat="server" Text="" Font-Size="10pt" />&nbsp;
                <asp:Label ID="Label9" runat="server" Text="当前页:" Font-Size="10pt" /><asp:Label ID="jq_current" runat="server" Text="" Font-Size="10pt" />&nbsp;
                <asp:LinkButton ID="jq_First" runat="server" Text="首页" OnClick="First_Click" Font-Size="10pt" />
                <asp:LinkButton ID="jq_Previous" runat="server" Text="上一页" OnClick="Previous_Click" Font-Size="10pt" />
                <asp:LinkButton ID="jq_Next" runat="server" Text="下一页" OnClick="Next_Click" Font-Size="10pt" />
                <asp:LinkButton ID="jq_Last" runat="server" Text="末页" OnClick="Last_Click" Font-Size="10pt" />
            </asp:Panel>

        </td>
        </tr>
    <tr  align="center" width="100%" style=" ">
    <td  align="center" style="height:12pt; color: blue;width:100%">
        
        &nbsp;
     </td>
    </tr>
</table>