<%@ Control Language="C#" AutoEventWireup="true"   CodeFile="InfoRead.ascx.cs" Inherits="admin_InfoRead" %>
<%@ Import Namespace="System.Data" %>
<style type="text/css">
    .style1
    {
        width: 107%;
    }
    .style2
    {
        height: 5px;
        width: 107%;
    }
    .style3
    {
        height: 12pt;
        width: 107%;
    }
</style>
<script type="text/javascript" src="../Info/xhEditor/xheditor.js"></script>
<script type="text/javascript">
    var i = 10;
    function closewin() {
        self.opener = null;
        self.close();
    }
    function clock() {
        i = i - 1;
        document.title = "本窗口将在" + i + "秒后自动关闭!";
        if (i > 0) setTimeout("clock();", 1000);
        else closewin();
    }
    function back() {
        history.go(-1);
    }
    var name, value;
    function UrlSearch() {

        var str = location.href; //取得整个地址栏
        var num = str.indexOf("?")
        str = str.substr(num + 1); //取得所有参数
        var arr = str.split("&"); //各个参数放到数组里
        for (var i = 0; i < arr.length; i++) {
            num = arr[i].indexOf("=");
            if (num > 0) {
                name = arr[i].substring(0, num);
                value = arr[i].substr(num + 1);
                this[name] = value;
                //alert(name);
                //alert(value);
            }
        }
    }
    var editor = "#<%=TextBox1.ClientID%>"; //内容输入框
    $(document).ready(function () {

        $(editor).xheditor({ tools: 'mini' });
    });

</script>
<table style="width: 100%; table-layout: fixed;" rules=cols>
    <tr style="font-size: 12pt; font-family: 微软雅黑; height: 12pt">
        <td align="center" class="style1">
            <asp:Label ID="Caption" runat="server" Font-Size="Large"></asp:Label>
        </td>
    </tr>
    <tr style="background-color: #ffccff">
        <td align="center" class="style2">
        </td>
    </tr>
    <tr style="font-size: 12pt; font-family: Times New Roman; height: 12pt">
        <td align="center" class="style3">
            <asp:Label ID="Lowner" runat="server" Font-Size="10pt" Text="发布人："></asp:Label>
            &nbsp;&nbsp;
            <asp:Label ID="Ldate" runat="server" Font-Size="10pt" Text="发布日期："></asp:Label>
            &nbsp;&nbsp;&nbsp;
            <asp:Label ID="Lread" runat="server" Font-Size="10pt" Text="浏览量:"></asp:Label>
        </td>
    </tr>
    <tr style="font-size: 1pt; font-family: Times New Roman; height: 12pt">
        <td style="height: 1pt">
            <hr />
            &nbsp;
        </td>
    </tr>
    <tr style="font-size: 12pt; font-family: Times New Roman; height: 12pt; table-layout: fixed;
        word-wrap: break-word;">
        <td runat="server" id="content" class="style3" width="150px">
        </td>
    </tr>
</table>
<table style="width: 100%">
    <tr style="height: 5px; background-color: #ffddee">
        <td align="left" style="font-size: 12pt; font-family: Times New Roman; height: 12pt;"
            colspan="4">
            评论内容：
        </td>
    </tr>
    <%
        if (Session["NewsId"] != null)
        {

            string key = Session["NewsId"].ToString();//NewsID是请求参数
            Datacon dacon = new Datacon();
            string sqlstr = "SELECT* FROM Comment  where messageId='" + key + "' order by time asc";
            DataSet ds = dacon.getds(sqlstr);
            int num = 1;
            for (int i = 0; i < ds.Tables[0].Rows.Count; i++)
            {  //历遍所有的
               
    %>
    <tr style="font-size: 12pt; font-family: Times New Roman; height: 12pt; table-layout: fixed;
        background-color: #ffccff;" >
        <td class="style3" style="width: 15%">
            用户：<%=ds.Tables[0].Rows[i]["owner"].ToString()%>
        </td>
        <td class="style3" style="width: 35%">
            发表时间：<%=ds.Tables[0].Rows[i]["time"].ToString()%>
        </td>
        <td class="style3" style="width: 15%">
            <%=num.ToString()%>楼&nbsp;
        </td>
        <td class="style3" style="width: 35%">
            <% 
        if (Session["username"].ToString().Trim() == ds.Tables[0].Rows[i]["owner"].ToString().Trim() || Session["role"] == "管理员")
        {%>
            <a href="comDel.ashx?comId=<%=ds.Tables[0].Rows[i]["comId"].ToString() %>&NewsId=<%=ds.Tables[0].Rows[i]["messageId"].ToString() %>">
                删除该评论</a>
            <%}
        %>
        </td>
    </tr>
    <tr style="font-size: 12pt; font-family: Times New Roman; height: 12pt; table-layout: fixed;">
        <td id="pinglun" class="style3" width="150" colspan="4">
            <%=ds.Tables[0].Rows[i]["Con"].ToString()%>
            &nbsp;
        </td>
    </tr>
    <%
        num++;
            }
        }
    %>
    <tr style="font-size: 12pt; font-family: Times New Roman; height: 12pt; table-layout: fixed;
        word-wrap: break-word;">
        <td runat="server" id="return" class="style3" width="150" align="left" colspan="4">
            <asp:TextBox ID="TextBox1" runat="server" Height="93px" TextMode="MultiLine" Width="547px"
                MaxLength="500" ToolTip="最多输入500字符评论"></asp:TextBox>
        </td>
    </tr>
    <tr>
        <td colspan="4">
            <asp:Button ID="Button1" runat="server" Text="回复" OnClick="Button1_Click" /></td>
    </tr>
    <tr style="font-size: 12pt; font-family: Times New Roman; height: 12pt">
        <td align="center" class="style1" colspan="4">
            <br />
            <br />
            <br />
            <span onclick="clock()" style="color: #FF00FF;">关闭网页</span> &nbsp;&nbsp; <span onclick="back()"
                style="color: #FF00FF">返回</span>
        </td>
    </tr>
</table>
