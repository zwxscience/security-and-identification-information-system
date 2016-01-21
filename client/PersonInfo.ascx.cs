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
public partial class client_PersonInfo : System.Web.UI.UserControl
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

            string sqlstr = "select * from userInfo where username='" + Session["username"].ToString() + "'";
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
            state.Text = myds.Tables[0].Rows[0]["state"].ToString();
            TextBox1.Text = myds.Tables[0].Rows[0]["ComName"].ToString();
            TextBox2.Text = myds.Tables[0].Rows[0]["ComTel"].ToString();
            TextBox3.Text = myds.Tables[0].Rows[0]["ComEmail"].ToString();
            TextBox4.Text = myds.Tables[0].Rows[0]["ComAddress"].ToString();
            TextBox5.Text = myds.Tables[0].Rows[0]["ComNet"].ToString();


        }
    }

  
 
    protected void PswMod_Click(object sender, EventArgs e)
    {
        string sp = "", np = "", np1 = "";
        sp = TextBox6.Text;
        if(sp==""){
             info.Text = "密码不能为空";
            return;
        }
        SqlConnection con = dacon.getcon();
        SqlCommand myCommand = new SqlCommand("select * from userInfo where username='" + Session["username"] + "' and password='" + sp + "'", con);
        myCommand.Connection.Open();
        int i = (int)myCommand.ExecuteScalar();
        myCommand.Connection.Close();

        if (i < 1)
        {
            info.Text = "原密码输入不正确";
            return;
        }

        if (TextBox7.Text.Length < 6 || TextBox7.Text.Length > 30)
        {
            info.Text = "新密码长度需要大于6个字符";
            return;
        }
        if (TextBox7.Text.ToString().Trim() != TextBox8.Text.ToString().Trim())
        {
            info.Text = "新密码与确认密码不一致";
            return;
        }
        if (TextBox7.Text.ToString().Trim() == TextBox6.Text.ToString().Trim())
        {
            info.Text = "新密码与原始密码不能相同";
            return;
        }
        con = dacon.getcon();
        myCommand = new SqlCommand("update userInfo set password=@password where username='" + Session["username"] + "'", con);
        myCommand.Parameters.Add(new SqlParameter("@password", SqlDbType.NVarChar, 50));

        myCommand.Parameters["@password"].Value = TextBox7.Text;

        myCommand.Connection.Open();
        i = (int)myCommand.ExecuteNonQuery();
        myCommand.Connection.Close();
        if (i < 1)
        {
            info.Text = "密码更新失败";
            return;
        }
        else
        {
            info.Text = "密码更新成功，刷新页面后显示";
            return;
        }
    }
    protected void InfoMod_Click(object sender, EventArgs e)
    {
        SqlConnection con = dacon.getcon();
        string comName = "", ComAddress = "", ComTel = "", ComNet = "", ComEmail = "";
        if (TextBox1.Text.Length < 1 || TextBox1.Text.Length > 30)
        {
            info.Text = "公司名不得为空或超出30个字符！";
            return;
        }
        else comName = TextBox1.Text;
        if (TextBox2.Text.Length < 1 || TextBox2.Text.Length > 30)
        {
            info.Text = "公司电话不得为空或超出30个字符！";
            return;
        }
        else
            ComTel = TextBox2.Text;
        if (TextBox3.Text.Length < 1 || TextBox3.Text.Length > 30)
        {
            info.Text = "公司电邮不得为空或超出30个字符！"; return;
        }
        else
            ComEmail = TextBox3.Text;
        if (TextBox4.Text.Length < 1 || TextBox4.Text.Length > 30)
        {
            info.Text = "公司地址不得为空或超出30个字符！"; return;
        }
        else
            ComAddress = TextBox4.Text;
        if (TextBox5.Text.Length < 1 || TextBox5.Text.Length > 30)
        {
            info.Text = "公司网址不得为空或超出30个字符！"; return;
        }
        else
            ComNet = TextBox5.Text;
        SqlCommand myCommand = new SqlCommand("update userInfo set ComName=@ComName,ComAddress=@ComAddress,ComTel=@ComTel,ComNet=@ComNet,ComEmail=@ComEmail where username='" + Session["username"] + "'", con);
        myCommand.Parameters.Add(new SqlParameter("@ComName", SqlDbType.NVarChar, 50));

        myCommand.Parameters["@ComName"].Value = comName;
        myCommand.Parameters.Add(new SqlParameter("@ComAddress", SqlDbType.Text, 30000));
        myCommand.Parameters["@ComAddress"].Value = ComAddress;
        myCommand.Parameters.Add(new SqlParameter("@ComTel", SqlDbType.NVarChar, 30));
        myCommand.Parameters["@ComTel"].Value = ComTel;
        myCommand.Parameters.Add(new SqlParameter("@ComNet", SqlDbType.NVarChar, 30));
        myCommand.Parameters["@ComNet"].Value = ComNet;
        myCommand.Parameters.Add(new SqlParameter("@ComEmail", SqlDbType.NVarChar, 30));
        myCommand.Parameters["@ComEmail"].Value = ComEmail;

        myCommand.Connection.Open();
        int i = (int)myCommand.ExecuteNonQuery();
        myCommand.Connection.Close();
        if (i < 1)
        {
            info.Text = "信息修改失败！";
            return;
        }
        else
        {
            info.Text = "信息修改成功！刷新页面后显示。";
            return;
        }

    }
}


