using System;
using System.Web;
using System.Text;

using System.Data;
using System.Configuration;

using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;
using System.Data.SqlClient;

public partial class InfoDel : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {
        string key = "";
        if (Request.QueryString["id"] != null)
        {
            key = Request.QueryString["id"].ToString();
            if (this.checkDel(key) >= 1)
            {
                Page.ClientScript.RegisterStartupScript(this.GetType(), "", "<Script>alert('删除成功');window.location.href('QueryInfo.aspx')</Script>");
                Context.Response.Redirect("QueryInfo.aspx");
            }
            else
            {
                Page.ClientScript.RegisterStartupScript(this.GetType(), "", "<Script>alert('删除失败');window.location.href('QueryInfo.aspx')</Script>");
                Context.Response.Redirect("QueryInfo.aspx");
            }
        }
        else
        {
            Context.Response.Redirect("QueryInfo.aspx");
        }
    }

    public int checkDel(string key)
    {
        Datacon dacon = new Datacon();
        SqlConnection con = dacon.getcon();
        string time = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss");
        //SqlCommand myCommand = new SqlCommand("INSERT INTO xxfb(NewsName, NewsContent, NewsDate) VALUES('" + caption + "','" + editor + "', '" + time + "')", con);

        SqlCommand myCommand = new SqlCommand(" delete  from proApply where id=@Id", con);
        myCommand.Parameters.Add(new SqlParameter("@Id", SqlDbType.Int, 50));
        myCommand.Parameters["@Id"].Value = key;
        myCommand.Connection.Open();
        int i = (int)myCommand.ExecuteNonQuery();
        myCommand.Connection.Close();
        return i;
    }
}