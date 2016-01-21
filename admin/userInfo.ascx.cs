using System;
using System.Data;
using System.Configuration;
using System.Collections;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;
using System.Data.SqlClient;
public partial class admin_userInfo : System.Web.UI.UserControl
{
    Datacon dacon = new Datacon();

    protected void Page_Load(object sender, EventArgs e)
    {
        if (Session["username"] == null)
        {
            Response.Write("<script>alert('用户登录超时，请重新登录。');location='../Login.aspx'</script>");

            return;
        }
        if (!IsPostBack)
        {
            if (Request.QueryString["username"] != null)
            {
                string userName = Request.QueryString["username"].ToString();
                string sqlstr = "select * from userInfo where username='" + userName + "'";
                DataSet myds = dacon.getds(sqlstr);

                PID.Text = myds.Tables[0].Rows[0]["id"].ToString();
                Regionalism.Text = myds.Tables[0].Rows[0]["Regionalism"].ToString();
                int t = (int)myds.Tables[0].Rows[0]["number"];
                if (t < 10) Regionalism.Text = Regionalism.Text + "0" + t.ToString();
                else Regionalism.Text = Regionalism.Text + t.ToString();

                ComName.Text = myds.Tables[0].Rows[0]["ComName"].ToString();
                ComAddress.Text = myds.Tables[0].Rows[0]["ComAddress"].ToString();
                ComEmail.Text = myds.Tables[0].Rows[0]["ComEmail"].ToString();
                ComNet.Text = myds.Tables[0].Rows[0]["ComNet"].ToString();
                ComTel.Text = myds.Tables[0].Rows[0]["ComTel"].ToString();
                RegDate.Text = myds.Tables[0].Rows[0]["RegDate"].ToString();
                Gold.Text = myds.Tables[0].Rows[0]["Gold"].ToString();
                state.Text = myds.Tables[0].Rows[0]["state"].ToString();
            }

        }
    }

  
 
  
}


