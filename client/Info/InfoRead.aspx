<%@ Page Title="" Language="C#" MasterPageFile="clientPage.master" AutoEventWireup="true" CodeFile="InfoRead.aspx.cs" Inherits="InfoRead" %>

<%@ Register src="../../admin/Info/InfoRead.ascx" tagname="InfoRead" tagprefix="uc2" %>

<asp:Content ID="Content1" ContentPlaceHolderID="ContentPlaceHolder1" Runat="Server">
    <uc2:InfoRead ID="InfoRead1" runat="server" />
</asp:Content>

