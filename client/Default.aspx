<%@ Page Language="C#" MasterPageFile="clientPage.master" AutoEventWireup="true" CodeFile="Default.aspx.cs" Inherits="_Default" Title="防伪信息系统客户端" %>

<%@ Register src="PersonInfo.ascx" tagname="PersonInfo" tagprefix="uc1" %>


<%@ Register src="InfoShow.ascx" tagname="InfoShow" tagprefix="uc3" %>

<asp:Content ID="Content1" ContentPlaceHolderID="ContentPlaceHolder1" Runat="Server">
    

    <uc1:PersonInfo ID="PersonInfo1" runat="server" />
    <uc3:InfoShow ID="InfoShow1" runat="server" />

    

</asp:Content>

