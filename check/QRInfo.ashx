<%@ WebHandler Language="C#" Class="sealInfo" %>

using System;
using System.Web;
using System.Data;
using System.Text;
using System.Data.SqlClient;
using System.Web.SessionState ;
public class sealInfo : IHttpHandler, IRequiresSessionState
{
    
    public void ProcessRequest (HttpContext context) {
        string key = "";
        context.Response.ContentType = "text/plain";
        if (context== null)
            context.Response.Redirect("../Login.aspx");
        if (context.Request.QueryString["cpbhStr"] != null)
        {
            key = context.Request.QueryString["q"];
            context.Response.Write(this.GetcpbhList(key,context,1) );
        }
        if (context.Request.QueryString["cpbhStr2"] != null)
        {
            key = context.Request.QueryString["q"];
            context.Response.Write(this.GetcpbhList(key, context, 2));
        }

        if (context.Request.QueryString["cpmcStr"] != null)
        {
            key = context.Request.QueryString["q"];
            context.Response.Write(this.GetcpmcList(key, context,1));
        }
      


    }
    //获取印章名称
    private string GetcpbhList(string key, HttpContext context,int tag)
    {
        Datacon dacon = new Datacon();
        string result = "";
        StringBuilder items = new StringBuilder();
        string sqlstr="";
      switch(tag){
          case 1:
       sqlstr = "SELECT DISTINCT TOP (10)  code FROM proApply WHERE   (code LIKE '%" + key + "%') and AllocFlag=4";
              break;
          case 2:
              sqlstr = "SELECT DISTINCT TOP (10)  QRString FROM checkRecord WHERE   (QRString LIKE '%" + key + "%') and username='"+context.Session["username"]+"'";
              break;
               
        
    }
        DataSet ds = dacon.getds(sqlstr);
        if (tag == 1)
        {
            for (int i = 0; i < ds.Tables[0].Rows.Count; i++)
            {//历遍所有的
                if (ds.Tables[0].Rows[i]["code"].ToString() != "")
                    items.Append(ds.Tables[0].Rows[i]["code"].ToString() + "\n");

            }

          
        }
        else if(tag==2)
        {
            for (int i = 0; i < ds.Tables[0].Rows.Count; i++)
            {//历遍所有的
                if (ds.Tables[0].Rows[i]["QRString"].ToString() != "")
                    items.Append(ds.Tables[0].Rows[i]["QRString"].ToString() + "\n");

            }

            
        }
        result = items.ToString();
        return result;
    }

    private string GetcpmcList(string key, HttpContext context,int tag)
    {
        Datacon dacon = new Datacon();
        string result = "";
        StringBuilder items = new StringBuilder();
          string sqlstr="";
      switch(tag){
          case 1:
      sqlstr = "SELECT DISTINCT TOP (10)  productName FROM proApply WHERE (productName LIKE '%" + key + "%') and AllocFlag=4";
              break;
          
          
               
      }
        DataSet ds = dacon.getds(sqlstr);
      
        for (int i = 0; i < ds.Tables[0].Rows.Count; i++)
        {//历遍所有的
            if (ds.Tables[0].Rows[i]["productName"].ToString() != "")
                items.Append(ds.Tables[0].Rows[i]["productName"].ToString() + "\n");

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