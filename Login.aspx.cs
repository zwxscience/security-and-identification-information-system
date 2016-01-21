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
using System.Web.SessionState;//用要到session保存的ID
[Serializable] 
public partial class Login : System.Web.UI.Page   
{

    Datacon dacon = new Datacon();
    protected void Page_Load(object sender, EventArgs e)
    {
     
        if (!Page.IsPostBack)
        {
            username.Text = null;
            password.Text = null;

        }
        else
        {
            //Session.Abandon();//取消当前会话   

        }

    }
  
    protected void submit_Click(object sender, EventArgs e)
    {
        //先判断验证码
        string yz1 = "";
     
        if (Context.Session["checkCode"] != null)
        {

            yz1 = Session["checkCode"].ToString();
        }

        string username1 = username.Text;
        string psw1 = password.Text;
        if(username1=="")
        {
            lab_er.Visible = true;
            lab_er.Text = "用户名不能为空！";
            username.Focus();
            return;
        }
        if (psw1.Trim() == "")
        {
            lab_er.Visible = true;
            lab_er.Text = "密码不能为空！";
            password.Focus();
            return;
        }
        string yz2 = yz.Text;
        if (yz2=="")
        {
            lab_er.Visible = true;
            lab_er.Text = "验证码不能为空！";
            yz.Focus();
            return;
        }
      
    

       // else return;

        if (!yz2.ToLower().Equals(yz1))
        {
            lab_er.Visible = true;
            lab_er.Text = "验证码错误！";
            return;
        }
        int i = this.checkLogin(username.Text.Trim(), password.Text.Trim(),RBL1.SelectedValue);
        if (i > 0)
        {
            Session["username"] = username.Text.Trim();
            Session["role"] = RBL1.SelectedValue;
            string sql = "select * from userInfo where username='" + Session["username"] + "' and password='" + password.Text.Trim() + "' and role='" + RBL1.SelectedValue + "'";
            DataSet ds = dacon.getds(sql);
            if (ds.Tables[0].Rows[0]["state"].ToString().Trim() == "禁用")
            {
                lab_er.Visible = true;
                lab_er.Text = "您的账户被禁用，请与管理员联系！";
                return;
            }

            if(RBL1.SelectedValue=="客户")
            Response.Redirect("client/Default.aspx");
            if (RBL1.SelectedValue == "管理员")
                Response.Redirect("admin/Default.aspx");
            if (RBL1.SelectedValue == "查询")
                Response.Redirect("check/Default.aspx");
            lab_er.Visible = false;
        }
        else
        {
            lab_er.Visible = true;
            lab_er.Text = "用户名或密码错误！";
        }

    }
    public int checkLogin(string loginName, string loginPwd,string role)
    {
        SqlConnection con = dacon.getcon();
        try
        {
            SqlCommand myCommand = new SqlCommand("select count(*) from userInfo where username=@loginName and password=@loginPwd and role=@role", con);
            myCommand.Parameters.Add(new SqlParameter("@loginName", SqlDbType.NVarChar, 50));
            myCommand.Parameters["@loginName"].Value = loginName;
            myCommand.Parameters.Add(new SqlParameter("@loginPwd", SqlDbType.NVarChar, 50));
            myCommand.Parameters["@loginPwd"].Value = loginPwd;
            myCommand.Parameters.Add(new SqlParameter("@role", SqlDbType.NVarChar, 50));
            myCommand.Parameters["@role"].Value = role;
            myCommand.Connection.Open();
            int i = (int)myCommand.ExecuteScalar();
            myCommand.Connection.Close();
            return i;
        }
        catch (Exception e)
        {
            lab_er.Visible = true;
            lab_er.Text = e.Message+",可能是数据库连接错误，请打开SQL服务！";
            return 0;
        }
      
    }



    protected void reg_Click(object sender, EventArgs e)
    {
        Response.Redirect("register/Reg.aspx");
    }
}
