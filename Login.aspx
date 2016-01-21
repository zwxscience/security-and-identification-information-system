<%@ Page Language="C#" AutoEventWireup="true" CodeFile="Login.aspx.cs" Inherits="Login" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title>防伪识别信息系统</title>
    <link href="CSS/logInOutStyle.css" rel="stylesheet" type="text/css" />
  
</head>

<body >
    <form id="form1" runat="server">
    <div id="outer">
	<div id="header">	
		<h1 style="font-family: 隶书; left: 1.18em; margin-left:263px"><a >防伪识别信息系统</a></h1>
		        
	<div>
	 <img src="images/head.jpg" style=" margin-left:183px; margin-top:17px"  alt="logo"/></div>
  </div>
    </div>
    <div>
    <br /> <br /> <br /> <br /> <br /> <br /> <br /> <br /> <br /> <br /> <br /> <br />

    <table width="500" border="0" align="center" cellpadding="0"
			cellspacing="15" class="login-table">
			<tr>
				<td width="368" valign="top" class="right">
					<div class="title-n">
                        用户登录
					</div>
				
						<table width="320" border="0" align="center" cellpadding="0"
							cellspacing="8">
							<tr>
								<td colspan="2" align="center">
									&nbsp;
                                    <asp:Label ID="lab_er" runat="server" Width="202px" Visible="False" BackColor="White" ForeColor="Red"></asp:Label><font color="red"></font></td>
							</tr>
							<tr>
								<td align="right" style="width: 109px">
                                    用户名：
								</td>
								<td width="196" align="left">
                                    <asp:TextBox ID="username" runat="server" MaxLength="60" class="input" Width="130px"></asp:TextBox>			
								</td>
							</tr>
							<tr>
								<td align="right" style="width: 109px">
									密&nbsp;&nbsp;码：
								</td>
								<td align="left">

		                        <asp:TextBox type="password" ID="password" runat="server"  MaxLength="18" 
                                        class="input" EnableTheming="True" Width="129px" TextMode="Password"></asp:TextBox>							
                                    <span style="color: #0155c7; text-decoration: underline"><a href="mailto:zwxsciecne@163.com" title="通过管理员找回密码">找回密码</a></span>
								</td>
							</tr>
							<tr>
								<td align="right" class="style1">
                                    验证码：
								</td>
								<td align="left" class="style2">
									 <asp:TextBox ID="yz" runat="server" MaxLength="4" class="input" Width="62px" ></asp:TextBox>			<img src="login.ashx" alt="点击切换验证码" id="yzpic"   onclick="this.src='login.ashx?update='+(new Date().getTime())"/>
								</td>
							</tr>
							<tr>
								<td align="right" style="width: 109px">
                                    登陆角色：</td>
								<td align="left" style="height: 20px">
									 <asp:RadioButtonList ID="RBL1" runat="server" RepeatDirection="Horizontal">
                                         <asp:ListItem Selected="True" Value="客户">客户端</asp:ListItem>
                                         <asp:ListItem Value="查询">查询端</asp:ListItem>
                                         <asp:ListItem Value="管理员">管理端</asp:ListItem>
                                     </asp:RadioButtonList>
								</td>
							</tr>
							<tr>
								<td align="right" style="width: 109px">
									&nbsp;
								</td>
								<td align="left">
                                    <asp:Button ID="submit" runat="server" Text="登录" OnClick="submit_Click" />
									&nbsp;
									 <asp:Button ID="reg" runat="server" Text="注册" onclick="reg_Click"  />
								</td>
							</tr>
						</table>
</td>
</tr>
</table>
      </div>
    </form>
</body>
</html>
