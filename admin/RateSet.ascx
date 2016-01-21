<%@ Control Language="C#" AutoEventWireup="true" CodeFile="RateSet.ascx.cs" Inherits="admin_RateSet" %>
<table style="width: 100%">
    <tr style="height:20pt">
        <td align="center">
        <asp:Label ID="Label2" runat="server" Text="费率设置" Font-Bold="True" 
                Font-Names="宋体" Font-Size="16pt"  ForeColor="MidnightBlue"></asp:Label>
        </td>
    </tr>
    <tr style="height:5px; background-color: #ffccff">
        <td align="center" >
            <asp:Label ID="Label6" runat="server"></asp:Label>
        </td>
    </tr>
    <tr style="height: 12pt">
        <td class="style1">
            <asp:Label ID="Lyzspr" runat="server" Font-Size="10pt" Text="单次生成费用：" 
                Width="100px"></asp:Label>
            <asp:TextBox ID="dcsc" runat="server" 
                ToolTip="请输入单次生成" Width="20%" MaxLength="10"></asp:TextBox>
                元/次</td>
    </tr>
  
    <tr style="height: 12pt">
        <td class="style1">
            <asp:Label ID="Label5" runat="server" Font-Size="10pt" Text="批量生成费用：" 
                Width="100px"></asp:Label>
            <asp:TextBox
                ID="plsc" runat="server" ToolTip="请输入批量生成费用" Width="20%" MaxLength="10"></asp:TextBox>元/次</td>
    </tr>
    <tr style="height: 12pt">
        <td align=left class="style1" >
            <asp:Label ID="Lyz_jbr" runat="server" Text="单次查询费用：" Font-Size="10pt" 
                Width="100px"   ></asp:Label>
            <asp:TextBox ID="cxsc" runat="server" 
                Width="20%"　 style="margin-left: 0px" 
                ToolTip="单次查询费用" MaxLength="10"></asp:TextBox>
            元/次</td>
    </tr>
    <tr style="height: 12pt">
        <td align=left class="style1" >
            <asp:Button ID="Button1" runat="server" onclick="Button1_Click" Text="设置" />
        </td>
    </tr>
    </table>
    <table style="width: 100%">
    <tr style="height:20pt">
        <td align="center">
        <asp:Label ID="Label1" runat="server" Text="往次费率设置" Font-Bold="True" 
                Font-Names="宋体" Font-Size="16pt"  ForeColor="MidnightBlue"></asp:Label>
        </td>
    </tr>
    <tr style="height:5px; background-color: #ffccff">
        <td align="center" >
        </td>
    </tr>
    </table>
<asp:GridView  ID="rate" runat="server" AllowSorting="True" 
    AutoGenerateColumns="False" BackColor="White" BorderColor="Transparent" 
    BorderStyle="None" BorderWidth="1px" CellPadding="2" EmptyDataText="无记录" 
    Font-Size="10pt" HorizontalAlign="Left"  Style="vertical-align: middle;
            text-align: left" Width="100%" DataSourceID="SqlDataSource1">
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
    <Columns>
        <asp:BoundField DataField="SIRate" HeaderText="单次生成费率" 
            SortExpression="SIRate" />
        <asp:BoundField DataField="BIRate" HeaderText="批次生成费率" 
            SortExpression="BIRate" />
        <asp:BoundField DataField="GetRate" HeaderText="单次查询费率" 
            SortExpression="GetRate" />
        <asp:BoundField DataField="MoDate" HeaderText="起始时间" SortExpression="MoDate" />
          <asp:BoundField DataField="endDate" HeaderText="结束时间"  NullDisplayText="在有效期内"
            SortExpression="endDate" />
    </Columns>
    <EmptyDataRowStyle HorizontalAlign="Center" />
    
</asp:GridView>
<asp:SqlDataSource ID="SqlDataSource1" runat="server" 
    ConnectionString="<%$ ConnectionStrings:sealConnectionString %>" 
    
    
    SelectCommand="SELECT * FROM [rateSet] order by id desc">
</asp:SqlDataSource>

