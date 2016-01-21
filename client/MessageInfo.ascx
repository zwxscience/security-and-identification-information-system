<%@ Control Language="C#" AutoEventWireup="true" CodeFile="MessageInfo.ascx.cs" Inherits="check_MesageInfo" %>


<script type="text/javascript">

    $(document).ready(function () {
        function getToday() {
            //得到今天的年,月,日
            this.now = new Date();
            this.year = this.now.getFullYear();
            this.month = this.now.getMonth() + 1; //0-11
            this.day = this.now.getDate();
        }

        var Infokssj = "#<%=Infokssj.ClientID%>"; //录入操作日期开始
        var Infojssj = "#<%=Infojssj.ClientID%>"; //录入操作日期结束
        var str = new getToday();
        str = str.year + (str.month >= 10 ? str.month : ('0' + str.month)) + (str.day >= 10 ? str.day : ('0' + str.day));
        $(Infokssj).datepick({ dateFormat: 'yymmdd' });
        $(Infojssj).datepick({ dateFormat: 'yymmdd' });
        //下面设置标题的自动填写
        var caption = "#<%=caption.ClientID%>"; //标题


        function findValue(li) {
            if (li == null) return alert("No match!");
            if (!!li.extra)
                var sValue = unescape(li.extra[0]);

        }
        function selectItem(li) {
            findValue(li);
        }

        $(caption).autocomplete("fee.ashx",
{
    extraParams: { captionstr: 1 },
    delay: 10,
    minChars: 0,
    matchSubset: 1, //使用对服务器查询的缓存
    cacheLength: 1, // 缓存的长度.即对从数据库中取到的结果集要缓存多少条记录.设成1为不缓存
    onItemSelect: selectItem,
    onFindValue: findValue,
    autoFill: true,
    mustMatch: false,
    maxItemsToShow: 10
});

    });
</script>

<table style="width: 100%">
    <tr  style="font-size: 12pt; font-family: 微软雅黑;height: 12pt">
        <td align="center" colspan="2" class="style1">
            <asp:Label ID="Label2" runat="server" Font-Size="Larger"
                Text="系统消息查询"></asp:Label>
        </td>
    </tr>
    <tr style="height: 5px; background-color: #ffccff">
        <td align="center" colspan="2" style="height: 5px">
        </td>
    </tr>
    <tr style="font-size: 12pt; font-family: Times New Roman; height: 12pt">
        <td style="width: 20%; height: 12pt; text-align:right">
            <asp:Label ID="Lcaption" runat="server" Font-Size="10pt" Text="标题："></asp:Label></td>
        <td style="height: 12pt">
            <asp:TextBox
                ID="caption" runat="server" Width="50%" ToolTip="请输入信息标题"></asp:TextBox>
         
    </tr>
    <tr style="font-size: 12pt; font-family: Times New Roman; height: 12pt">
        <td style="width: 20%; height: 12pt;text-align:right">
            <asp:Label ID="CBdate" runat="server" Font-Size="10pt" Text="发布日期区间：" ></asp:Label>
        </td>
        <td style="height: 12pt">
            <asp:TextBox
                ID="Infokssj" runat="server" Width="22%"></asp:TextBox>--<asp:TextBox
                    ID="Infojssj" runat="server" Width="26%"></asp:TextBox></td>
    </tr>
    <tr style="font-size: 12pt; font-family: Times New Roman; height: 12pt">
        <td align="center" colspan="2">
            <asp:Button ID="btnjq" runat="server" OnClick="btnjq_Click" Text="精确查询" />
            &nbsp; &nbsp;&nbsp;
            <asp:Button ID="btnmh" runat="server" OnClick="btnmh_Click" Text="模糊查询" />
        </td>
    </tr>
    <tr style="font-size: 12pt; font-family: Times New Roman">
        <td colspan="2">
            <asp:GridView ID="Info" runat="server" AllowSorting="True" AutoGenerateColumns="False"
                BackColor="White" BorderColor="Transparent" BorderStyle="None" BorderWidth="1px"
                CellPadding="2" EmptyDataText="无记录" Font-Size="10pt" 
                HorizontalAlign="Left" Style="vertical-align: middle;
                text-align: left" Width="100%">
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
                <asp:BoundField DataField="MessagesId" HeaderText="标题ID" />
                    <asp:BoundField DataField="MessageName" HeaderText="标题" />
                    <asp:BoundField DataField="MessageDate" HeaderText="发布时间" />
                    <asp:BoundField DataField="MessageOwner" HeaderText="发布人" />
                     <asp:BoundField DataField="sendto" HeaderText="发布对象" />
                    <asp:BoundField DataField="visitcount" HeaderText="访问量" />
                                          <asp:HyperLinkField DataNavigateUrlFields="MessagesId" DataNavigateUrlFormatString="Info/InfoRead.aspx?NewsId={0}"
                        Text="查看">
                    
                        <ItemStyle Font-Strikeout="False" Width="45pt" />
                        <HeaderStyle Width="20px" />
                    </asp:HyperLinkField>

                </Columns>
            </asp:GridView>
        </td>
    </tr>
    <tr style="font-size: 12pt; font-family: Times New Roman">
        <td align="right" colspan="2" style="height: 41px">
            <asp:Panel ID="Panel_jq" runat="server" Direction="LeftToRight" ForeColor="#003399"
                Height="15pt" HorizontalAlign="Right" Visible="False" Width="100%">
    <asp:Label ID="totalnum" runat="server" Text="共查到记录0条" Font-Size="10pt" ></asp:Label>&nbsp;&nbsp;&nbsp;
                <asp:Label ID="Label8" runat="server" Font-Size="10pt" Text="总页数:"></asp:Label><asp:Label
                    ID="jq_all" runat="server" Font-Size="10pt" Text=""></asp:Label>&nbsp;
                <asp:Label ID="Label9" runat="server" Font-Size="10pt" Text="当前页:"></asp:Label><asp:Label
                    ID="jq_current" runat="server" Font-Size="10pt" Text=""></asp:Label>
                <asp:LinkButton ID="jq_First" runat="server" Font-Size="10pt" OnClick="First_Click"
                    Text="首页"></asp:LinkButton>
                <asp:LinkButton ID="jq_Previous" runat="server" Font-Size="10pt" OnClick="Previous_Click"
                    Text="上一页"></asp:LinkButton>
                <asp:LinkButton ID="jq_Next" runat="server" Font-Size="10pt" OnClick="Next_Click"
                    Text="下一页"></asp:LinkButton>
                <asp:LinkButton ID="jq_Last" runat="server" Font-Size="10pt" OnClick="Last_Click"
                    Text="末页"></asp:LinkButton>
            </asp:Panel>
        </td>
    </tr>
</table>
