<%@ Page Title="" Language="C#" MasterPageFile="~/admin/adminPage.master" AutoEventWireup="true" CodeFile="ClientInfoManagement.aspx.cs" Inherits="ClientInfoManagement" %>

<%@ Register src="ClientInfoManagement.ascx" tagname="ClientInfoManagement" tagprefix="uc1" %>

<asp:Content ID="Content1" ContentPlaceHolderID="ContentPlaceHolder1" Runat="Server">
    <uc1:ClientInfoManagement ID="ClientInfoManagement1" runat="server" />
</asp:Content>

