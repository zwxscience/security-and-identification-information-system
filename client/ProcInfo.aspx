<%@ Page Title="" Language="C#" MasterPageFile="~/client/clientPage.master" AutoEventWireup="true" CodeFile="ProcInfo.aspx.cs" Inherits="client_ProcInfo" %>

<%@ Register src="ProcInfo.ascx" tagname="ProcInfo" tagprefix="uc1" %>

<asp:Content ID="Content1" ContentPlaceHolderID="ContentPlaceHolder1" Runat="Server">
    <uc1:ProcInfo ID="ProcInfo1" runat="server" />
</asp:Content>

