<%@ Page Language="C#" MasterPageFile="adminPage.master" AutoEventWireup="true" CodeFile="Default.aspx.cs" Inherits="_Default" Title="防伪信息系统管理端" %>

<%@ Register src="adminInfo.ascx" tagname="adminInfo" tagprefix="uc1" %>
<%@ Register src="MesageInfo.ascx" tagname="MesageInfo" tagprefix="uc2" %>

<asp:Content ID="Content1" ContentPlaceHolderID="ContentPlaceHolder1" Runat="Server">
    
       <uc1:adminInfo ID="adminInfo1" runat="server" />
    <uc2:MesageInfo ID="MesageInfo1" runat="server" />
 
    

</asp:Content>

