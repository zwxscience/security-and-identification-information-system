<%@ WebHandler Language="C#" Class="InfoOp" %>

using System;
using System.Web;
using System.Data;
using System.Text;
using System.Data.SqlClient;
public class InfoOp : IHttpHandler {
    
    public void ProcessRequest (HttpContext context) {
        context.Response.ContentType = "text/plain";
        //context.Response.Write("Hello World");
        string key = "";
        if (context.Request.QueryString["captionstr"] != null)
        {
            key = context.Request.QueryString["q"];
            context.Response.Write(this.GetCaptionList(key));
        }
        else if (context.Request.QueryString["userStr"] != null)
        {
            key = context.Request.QueryString["q"];
            context.Response.Write(this.GetUserList(key));
        }
        else
        {
            context.Response.Redirect("InfoOp.aspx");
        }
        
    }
    //获取用户ID
    private string GetUserList(string key)
    {
        Datacon dacon = new Datacon();
        string result = "";
        StringBuilder items = new StringBuilder();
        string sqlstr = "SELECT DISTINCT TOP (10)  username  FROM userInfo WHERE (username LIKE '%" + key + "%')";
        DataSet ds = dacon.getds(sqlstr);
        for (int i = 0; i < ds.Tables[0].Rows.Count; i++)
        {//历遍所有的
            if (ds.Tables[0].Rows[i]["username"].ToString() != "")
                items.Append(ds.Tables[0].Rows[i]["username"].ToString() + "\n");

        }

        result = items.ToString();
        return result;
    }
    //获取录入
    private string GetCaptionList(string key)
    {
        Datacon dacon = new Datacon();
        string result = "";
        StringBuilder items = new StringBuilder();
        string sqlstr = "SELECT DISTINCT TOP (10)  MessageName  FROM xxfb WHERE (MessageName LIKE '%" + key + "%')";
        DataSet ds = dacon.getds(sqlstr);
        for (int i = 0; i < ds.Tables[0].Rows.Count; i++)
        {//历遍所有的
            if (ds.Tables[0].Rows[i]["MessageName"].ToString() != "")
                items.Append(ds.Tables[0].Rows[i]["MessageName"].ToString() + "\n");

        }

        result = items.ToString();
        return result;
    }

    public bool IsReusable {
        get {
            return false;
        }
    }

}