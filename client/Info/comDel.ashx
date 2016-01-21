<%@ WebHandler Language="C#" Class="comDel" %>

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
public class comDel : IHttpHandler {
    
    public void ProcessRequest (HttpContext context) {
        context.Response.ContentType = "text/plain";
        //context.Response.Write("Hello World");
        string key = "";
        if (context.Request.QueryString["comId"] != null)
        {
            key = context.Request.QueryString["comId"];
             if (this.checkDel(key) >= 1)
            {
                context.Response.Redirect("InfoRead.aspx?NewsId=" + context.Request.QueryString["NewsId"]);
               //context.Response.Write("<script>alert('删除评论成功');</script>"); 
            }
            else
            {

                context.Response.Redirect("InfoRead.aspx?NewsId=" + context.Request.QueryString["NewsId"]);
            }
        }
        else
        {
            context.Response.Redirect("InfoRead.aspx?NewsId=" + context.Request.QueryString["NewsId"]);
        }
        
        
    }
  public int checkDel(string key)
    {
        Datacon dacon = new Datacon();
        SqlConnection con = dacon.getcon();


        SqlCommand myCommand = new SqlCommand(" delete  from Comment where comId=@comId", con);
        myCommand.Parameters.Add(new SqlParameter("@comId", SqlDbType.Int, 50));
        myCommand.Parameters["@comId"].Value = key;
        myCommand.Connection.Open();
        int i = (int)myCommand.ExecuteNonQuery();
        myCommand.Connection.Close();
        return i;
    }
    public bool IsReusable {
        get {
            return false;
        }
    }

}