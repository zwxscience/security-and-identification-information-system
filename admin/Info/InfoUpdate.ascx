<%@ Control Language="C#" AutoEventWireup="true" CodeFile="InfoUpdate.ascx.cs" Inherits="Infoup"  %>
  <link href="../Info/xhEditor/common.css" type="text/css" />
 <script type="text/javascript" src="../../JS/jquery-1.3.1.js"></script>
 <script type="text/javascript" src="../Info/js/common.js"></script>
 <script type="text/javascript" src="../Info/xhEditor/xheditor.js"></script>
      <link  href="../../CSS/jquery.autocomplete.css" type="text/css" />
        <script type="text/javascript" src="../../JS/jquery.autocomplete.js"></script>
<script type="text/javascript">
    var editor = "#<%=editor.ClientID%>"; //内容输入框
    var caption = "#<%=caption.ClientID%>"; //内容输入框
    var obj = "#<%=DropDownList1.ClientID%>"; //对象框
    var obj2 = "#uerIn"; //对象框
    var user = "#<%=TextBox1.ClientID%>"; //对象框
    function pageInit() {

    }
    function findValue(li) {
        if (li == null) return alert("No match!");
        if (!!li.extra)
            var sValue = unescape(li.extra[0]);

    }
    function selectItem(li) {
        findValue(li);
    }
    $(document).ready(function () {
        $(caption).focus();

        $(editor).xheditor({
            html5Upload: false,
            forcePtag: false,
            upLinkUrl: "upload.ashx?id=1", upLinkExt: "zip,rar,txt",
            upImgUrl: "upload.ashx?id=2", upImgExt: "jpg,jpeg,gif,png",
            upFlashUrl: "upload.ashx?id=3", upFlashExt: "swf",
            upMediaUrl: "upload.ashx?id=4", upMediaExt: "avi"
        });
        $(obj).click(function () {
            if ($(obj).val() == '特定')
                $(obj2).show();
            else $(obj2).hide();
        });
        if ($(obj).val() == '特定')
            $(obj2).show();

        $(user).autocomplete("InfoOp.ashx",
          {
              extraParams: { userStr: 1 },
              delay: 10,
              minChars: 0,
              matchSubset: 1, //使用对服务器查询的缓存
              cacheLength: 1, //  缓存的长度.即对从数据库中取到的结果集要缓存多少条记录.设成1为不缓存
              onItemSelect: selectItem,
              onFindValue: findValue,
              autoFill: true,
              mustMatch: true,
              maxItemsToShow: 10
          });
    }
            );
    
 </script>
<table style="width: 100%">
    <tr style="height:20pt">
        <td align="center" 
            style="font-family: 华文楷体; font-size: x-large; font-style: inherit;">
            <asp:Label ID="Label1" runat="server"  Font-Names="华文楷体" Text="信息更新"></asp:Label>
        </td>
    </tr>
    <tr style="height:3px; background-color: #ffccff">
        <td align="center" >
        </td>
    </tr>
    <tr style="height:24pt">
        <td style="width:100%; height: 24pt;" align="center">
         
            <asp:TextBox ID="caption" runat="server" Width="65%" ToolTip="请更新标题" 
                Height="25px" Font-Size="Large" MaxLength="50" 
                 ></asp:TextBox></td>
    </tr>
    <tr style="height:24pt">
        <td style="width:100%; height: 24pt;" align="center">
            <asp:Label ID="Label2" runat="server" Text="发布对象:"></asp:Label>
            <asp:DropDownList ID="DropDownList1" runat="server">
                <asp:ListItem Value="全部">全部用户</asp:ListItem>
                <asp:ListItem Value="客户">客户端用户</asp:ListItem>
                <asp:ListItem Value="查询">查询端用户</asp:ListItem>
                <asp:ListItem Value="特定">特定用户</asp:ListItem>
            </asp:DropDownList>
            <em id="uerIn" style=" display:none">
            <asp:TextBox ID="TextBox1" runat="server" ></asp:TextBox></em>
        </td>
    </tr>
    </tr>
    <tr style="height:24pt">
        <td style="width:100%; height: 24pt; font-size: 24px;" align="center">
      
            <asp:TextBox ID="editor" runat="server" Width="73%"  Font-Size="Large" 
                Rows="10" MaxLength="30000"
                TextMode="MultiLine" Height="400px"></asp:TextBox>
        </td>
        
    </tr>
   
    <tr style="height:12pt">
       <td style="width:100%; height: 12pt; font-size: 14px;" align="center">
      
            <asp:CheckBox ID="CheckBox1" runat="server" Text="允许评论" Checked="True" />
        </td>
        
    </tr>
   
     <tr style="height:12pt">
         <td align="center">
            <asp:Button ID="btnis" runat="server" Text="更新" onclick="btnis_Click" 
                 style="height: 26px"  />&nbsp;&nbsp;
             &nbsp;&nbsp;</td>
    </tr>
        
</table>