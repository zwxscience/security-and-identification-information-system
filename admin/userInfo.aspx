<%@ Page Title="" Language="C#" MasterPageFile="~/admin/adminPage.master" AutoEventWireup="true" CodeFile="userInfo.aspx.cs" Inherits="userInfo" %>

<%@ Register src="userInfo.ascx" tagname="userInfo" tagprefix="uc1" %>

<asp:Content ID="Content1" ContentPlaceHolderID="ContentPlaceHolder1" Runat="Server">
    <uc1:userInfo ID="userInfo1" runat="server" />
</asp:Content>

