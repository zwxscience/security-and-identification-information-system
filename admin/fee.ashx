<%@ WebHandler Language="C#" Class="fee" %>

using System;
using System.Web;
using System.Data.SqlClient;
using System.Text;

using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;
using System.Data;
using System.Configuration;
public class fee : IHttpHandler {
    
    public void ProcessRequest (HttpContext context) {
        context.Response.ContentType = "text/plain";
        //context.Response.Write("Hello World");
        string key = "";
        if (context.Request.QueryString["username"] != null)
        {
            key = context.Request.QueryString["q"];
            context.Response.Write(GetusernameList(key));
        }
        if (context.Request.QueryString["userMan"] != null)
        {
            key = context.Request.QueryString["q"];
            context.Response.Write(GetuserManList(key));
        }
        if (context.Request.QueryString["month"] != null)
        {
            key = context.Request.QueryString["q"];
            context.Response.Write(GetmonthList(key, context));
        }
        
    }

    public string GetmonthList(string key, HttpContext context)
    {
        Datacon dacon = new Datacon();
        SqlConnection con = dacon.getcon();
        StringBuilder items = new StringBuilder();
        string result = "";
        string sqlstr = " SELECT DISTINCT TOP (10)  month FROM userFees WHERE   (month LIKE '%" + key + "%') ";
        DataSet ds = dacon.getds(sqlstr);

        for (int i = 0; i < ds.Tables[0].Rows.Count; i++)
        {//历遍所有的
            if (ds.Tables[0].Rows[i]["month"].ToString() != "")
                items.Append(ds.Tables[0].Rows[i]["month"].ToString() + "\n");

        }

        result = items.ToString();
        return result;

    }
    public string GetuserManList(string key)
    {
        Datacon dacon = new Datacon();
        SqlConnection con = dacon.getcon();
        StringBuilder items = new StringBuilder();
        string result = "";
        string sqlstr = " SELECT DISTINCT TOP (10)  username FROM userInfo WHERE   (userName LIKE '%" + key + "%') and (role='客户' or role='查询')";
        DataSet ds = dacon.getds(sqlstr);

        for (int i = 0; i < ds.Tables[0].Rows.Count; i++)
        {//历遍所有的
            if (ds.Tables[0].Rows[i]["username"].ToString() != "")
                items.Append(ds.Tables[0].Rows[i]["username"].ToString() + "\n");

        }

        result = items.ToString();
        return result;

    }
    public string GetusernameList(string key)
    {
        Datacon dacon = new Datacon();
        SqlConnection con = dacon.getcon();
        StringBuilder items = new StringBuilder();
        string result = "";
        string sqlstr = " SELECT DISTINCT TOP (10)  ClientName FROM userFees WHERE   (ClientName LIKE '%" + key + "%')";
        DataSet ds = dacon.getds(sqlstr);
       
            for (int i = 0; i < ds.Tables[0].Rows.Count; i++)
            {//历遍所有的
                if (ds.Tables[0].Rows[i]["ClientName"].ToString() != "")
                    items.Append(ds.Tables[0].Rows[i]["ClientName"].ToString() + "\n");

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