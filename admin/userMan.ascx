<%@ Control Language="C#" AutoEventWireup="true" CodeFile="userMan.ascx.cs" Inherits="admin_userMan" %>

<script type="text/javascript" language="javascript">
    //获取输入框内容
    var username = "#<%=username.ClientID%>"; //
 

 

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
              extraParams: { userMan: 1 },
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
  
    
    });       
</script>

<table style="width: 100%">
    <tr style="height:20pt">
        <td align="center">
        <asp:Label ID="Label2" runat="server" Text="用户查询" Font-Bold="True" 
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
                
               <asp:BoundField DataField="username" HeaderText="用户名" />
                <asp:BoundField DataField="role" HeaderText="角色" />
                <asp:BoundField DataField="Regionalism" HeaderText="注册地区号" />
                <asp:BoundField DataField="ComName" HeaderText="公司名称" />
                     <asp:BoundField DataField="ComTel" HeaderText="公司电话" />
                <asp:BoundField DataField="state" HeaderText="账户状态" />
                     <asp:HyperLinkField DataNavigateUrlFields="username" DataNavigateUrlFormatString="userInfo.aspx?username={0}"    Text="详细》">
               
                    <ItemStyle Width="45pt" Font-Strikeout="False" />
                    <HeaderStyle Width="20px" />
                </asp:HyperLinkField>

          
                <asp:ButtonField ButtonType="Button" CommandName="更改" HeaderText="账户状态操作" 
                    ShowHeader="True" Text="更改" >
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


