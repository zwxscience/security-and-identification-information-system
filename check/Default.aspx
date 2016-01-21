<%@ Page Language="C#" MasterPageFile="checkPage.master" AutoEventWireup="true" CodeFile="Default.aspx.cs" Inherits="_Default" Title="防伪信息系统客户端" %>


<%@ Register src="checkInfo.ascx" tagname="checkInfo" tagprefix="uc2" %>

<%@ Register src="InfoShow.ascx" tagname="InfoShow" tagprefix="uc3" %>

<asp:Content ID="Content1" ContentPlaceHolderID="ContentPlaceHolder1" Runat="Server">
    

    <uc2:checkInfo ID="checkInfo1" runat="server" />
    <uc3:InfoShow ID="InfoShow1" runat="server" />

    

</asp:Content>

