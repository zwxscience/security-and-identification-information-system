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
        if (Request.QueryString["NewsId"] != null)
        {
            key = Request.QueryString["NewsId"].ToString();
            if (this.checkDel(key) >= 1)
            {
                Page.ClientScript.RegisterStartupScript(this.GetType(), "", "<Script>alert('删除成功');document.location.href('InfoOp.aspx')</Script>");
                Response.Redirect("InfoOp.aspx");
            }
            else
            {
                Page.ClientScript.RegisterStartupScript(this.GetType(), "", "<Script>alert('删除失败');document.location.href('InfoOp.aspx')</Script>");
                Response.Redirect("InfoOp.aspx");
            }
        }
        else
        {
            Response.Redirect("InfoOp.aspx");
        }
    }

    public int checkDel(string key)
    {
        Datacon dacon = new Datacon();
        SqlConnection con = dacon.getcon();
        string time = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss");
        //SqlCommand myCommand = new SqlCommand("INSERT INTO xxfb(NewsName, NewsContent, NewsDate) VALUES('" + caption + "','" + editor + "', '" + time + "')", con);

        SqlCommand myCommand = new SqlCommand(" delete  from xxfb where MessagesId=@NewsId", con);
        myCommand.Parameters.Add(new SqlParameter("@NewsId", SqlDbType.Int, 50));
        myCommand.Parameters["@NewsId"].Value = key;
        myCommand.Connection.Open();
        int i = (int)myCommand.ExecuteNonQuery();
        myCommand.Connection.Close();
        return i;
    }
}