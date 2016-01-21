<%@ Page Title="" Language="C#" MasterPageFile="adminPage.master" AutoEventWireup="true" CodeFile="InfoIssue.aspx.cs" Inherits="InfoIssue"  validateRequest="false"  Debug="true" %>

<%@ Register src="InfoIssue.ascx" tagname="InfoIssue" tagprefix="uc1" %>

<asp:Content ID="Content1" ContentPlaceHolderID="ContentPlaceHolder1" Runat="Server">
    <uc1:InfoIssue ID="InfoIssue1" runat="server" />
</asp:Content>

