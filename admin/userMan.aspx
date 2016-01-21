<%@ Page Title="" Language="C#" MasterPageFile="~/admin/adminPage.master" AutoEventWireup="true" CodeFile="userMan.aspx.cs" Inherits="userMan" %>

<%@ Register src="userMan.ascx" tagname="userMan" tagprefix="uc1" %>

<asp:Content ID="Content1" ContentPlaceHolderID="ContentPlaceHolder1" Runat="Server">
    <uc1:userMan ID="userMan1" runat="server" />
</asp:Content>

