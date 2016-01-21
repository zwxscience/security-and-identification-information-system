<%@ Page Title="" Language="C#" MasterPageFile="~/client/clientPage.master" AutoEventWireup="true" CodeFile="userFees.aspx.cs" Inherits="client_userFees" %>

<%@ Register src="userfee.ascx" tagname="userfee" tagprefix="uc1" %>

<asp:Content ID="Content1" ContentPlaceHolderID="ContentPlaceHolder1" Runat="Server">
    <uc1:userfee ID="userfee1" runat="server" />
</asp:Content>

