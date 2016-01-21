<%@ Page Title="" Language="C#" MasterPageFile="~/client/clientPage.master" AutoEventWireup="true" CodeFile="MessageInfo.aspx.cs" Inherits="client_MessageInfo" %>

<%@ Register src="MessageInfo.ascx" tagname="MessageInfo" tagprefix="uc1" %>

<asp:Content ID="Content1" ContentPlaceHolderID="ContentPlaceHolder1" Runat="Server">
    <uc1:MessageInfo ID="MessageInfo1" runat="server" />
</asp:Content>

