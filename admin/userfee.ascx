<%@ Control Language="C#" AutoEventWireup="true" CodeFile="userfee.ascx.cs" Inherits="admin_userfee" %>

<script type="text/javascript" language="javascript">
    //获取输入框内容
    var username = "#<%=username.ClientID%>"; //
    var month1 = "#<%=month.ClientID%>"; //

//    function getToday() {
//        //得到今天的年,月,日
//        this.now = new Date();
//        this.year = this.now.getFullYear();
//        this.month = this.now.getMonth() + 1; //0-11
//        this.day = this.now.getDate();
//    }


    function findValue(li) {
        if (li == null) return alert("No match!");
        if (!!li.extra)
            var sValue = unescape(li.extra[0]);

    }
    function selectItem(li) {
        findValue(li);
    }

    $(document).ready(function () {
        $(username).autocomplete("fee.ashx",
          {
              extraParams: { username: 1 },
              delay: 10,
              minChars: 0,
              matchSubset: 1, //使用对服务器查询的缓存
              cacheLength: 1, //  缓存的长度.即对从数据库中取到的结果集要缓存多少条记录.设成1为不缓存
              onItemSelect: selectItem,
              onFindValue: findValue,
              autoFill: true,
              mustMatch: false,
              maxItemsToShow: 10
          });
//          $(month1).autocomplete("fee.ashx",
//          {
//              extraParams: { month: 1 },
//              delay: 10,
//              minChars: 0,
//              matchSubset: 1, //使用对服务器查询的缓存
//              cacheLength: 1, //  缓存的长度.即对从数据库中取到的结果集要缓存多少条记录.设成1为不缓存
//              onItemSelect: selectItem,
//              onFindValue: findValue,
//              autoFill: true,
//              mustMatch: false,
//              maxItemsToShow: 10
//          });

          $(month1).datepick({ dateFormat: 'yy年m月' });
    
    });       
</script>

<table style="width: 100%">
    <tr style="height:20pt">
        <td align="center">
        <asp:Label ID="Label2" runat="server" Text="用户费用查询" Font-Bold="True" 
                Font-Names="宋体" Font-Size="16pt"  ForeColor="MidnightBlue"></asp:Label>
        </td>
    </tr>
    <tr style="height:5px; background-color: #ffccff">
        <td align="center"  style=" font-size:10pt" >
            <asp:Label ID="Label10" runat="server"></asp:Label>
        </td>
    </tr>
   <tr style="height: 12pt">
        <td class="style1">
            <asp:Label ID="Lyzspr" runat="server" Font-Size="10pt" Text="按用户名：" style= "TEXT-ALIGN:   right "
                Width="100px"></asp:Label><asp:TextBox ID="username" runat="server" 
                ToolTip="请输入用户名" Width="50%"></asp:TextBox>
              
                </td>
    </tr>

    <tr style="height: 12pt">
        <td class="style1">
            <asp:Label ID="Label5" runat="server" Font-Size="10pt" Text="按月份查询：" style= "TEXT-ALIGN:   right "
                Width="100px"></asp:Label>
            <asp:TextBox
                ID="month" runat="server" ToolTip="请输入月份" Width="50%"></asp:TextBox></td>
    </tr>
   
    </table>

    <table style="width: 100%">
     <tr style="height:12pt">
         <td align="center">
            <asp:Button ID="btnjq" runat="server" Text="精确查询" OnClick="btnjq_Click" />&nbsp;&nbsp;
             &nbsp;&nbsp;<asp:Button ID="btnmh" runat="server" Text="模糊查询" OnClick="btnmh_Click" />
         &nbsp;&nbsp;&nbsp;
             </td>
    </tr>
  
    <tr style="height: 12pt">
        <td align=left class="style1" >
<asp:GridView  ID="rate" runat="server" AllowSorting="True" 
    AutoGenerateColumns="False" BackColor="White" BorderColor="Transparent" 
    BorderStyle="None" BorderWidth="1px" CellPadding="2" EmptyDataText="无记录" 
    Font-Size="10pt" HorizontalAlign="Left" onrowcommand="rate_RowCommand"  Style="vertical-align: middle; 
            text-align: left" Width="100%">
    <FooterStyle BackColor="#99CCCC" ForeColor="#003399" />
    <RowStyle BackColor="White" BorderColor="Transparent" BorderWidth="1px" 
        ForeColor="#003399" Height="11pt" />
    <SelectedRowStyle BackColor="Transparent" Font-Bold="True" 
        ForeColor="LightSlateGray" />
    <PagerStyle BackColor="#99CCCC" ForeColor="#003399" HorizontalAlign="Right" />
    <HeaderStyle BackColor="#69A4B5" Font-Bold="True" ForeColor="MidnightBlue" 
        Height="11pt" HorizontalAlign="Center" />
    <AlternatingRowStyle BackColor="AliceBlue" BorderColor="Transparent" 
        BorderWidth="1px" />
    <EmptyDataRowStyle HorizontalAlign="Center" />
     <Columns>
            <asp:BoundField DataField="id" HeaderText="标识ID" />
                     <asp:BoundField DataField="month" HeaderText="统计月份" />
               <asp:BoundField DataField="ClientName" HeaderText="用户名" />
                <asp:BoundField DataField="role" HeaderText="角色" />
                <asp:BoundField DataField="count1" HeaderText="单次统计数" />
                <asp:BoundField DataField="count2" HeaderText="批量统计数" />
                     <asp:BoundField DataField="Cost" HeaderText="应付金额" />
                <asp:BoundField DataField="pay" HeaderText="实际支付" />
                <asp:BoundField DataField="remain" HeaderText="未结算" />
                <asp:BoundField DataField="OpTime" HeaderText="更新日期" />
          
                <asp:ButtonField ButtonType="Button" CommandName="通知" HeaderText="提醒用户" 
                    ShowHeader="True" Text="通知" >
                <ItemStyle Height="20px" Width="20px" />
                </asp:ButtonField>

                      
            </Columns>
</asp:GridView>
        </td>
    </tr>
    <tr style="height: 12pt">
        <td align=left class="style1" >
            <asp:Panel ID="Panel_jq" runat="server" Direction="LeftToRight" 
                ForeColor="#003399" Height="11px" HorizontalAlign="Right" Visible="False" 
                Width="100%">
                &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                <asp:Label ID="Label1" runat="server" Font-Size="10pt" Text="共查到记录0条"></asp:Label>
                &nbsp;&nbsp;&nbsp;
                <asp:Label ID="Label8" runat="server" Font-Size="10pt" Text="总页数:" />
                <asp:Label ID="jq_all" runat="server" Font-Size="10pt" Text="" />
                &nbsp;
                <asp:Label ID="Label9" runat="server" Font-Size="10pt" Text="当前页:" />
                <asp:Label ID="jq_current" runat="server" Font-Size="10pt" Text="" />
                &nbsp;
                <asp:LinkButton ID="jq_First" runat="server" Font-Size="10pt" 
                    OnClick="First_Click" Text="首页" />
                <asp:LinkButton ID="jq_Previous" runat="server" Font-Size="10pt" 
                    OnClick="Previous_Click" Text="上一页" />
                <asp:LinkButton ID="jq_Next" runat="server" Font-Size="10pt" 
                    OnClick="Next_Click" Text="下一页" />
                <asp:LinkButton ID="jq_Last" runat="server" Font-Size="10pt" 
                    OnClick="Last_Click" Text="末页" />
            </asp:Panel>
        </td>
    </tr>
    </table>
    <table style="width: 100%">
    <tr style="height:20pt">
        <td align="center">
            &nbsp;</td>
    </tr>
    <tr style="height:5px; background-color: #ffccff">
        <td align="center" >
        </td>
    </tr>
    </table>


