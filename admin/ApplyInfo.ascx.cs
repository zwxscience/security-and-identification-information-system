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
public partial class admin_ApplyInfo : System.Web.UI.UserControl
{
    Datacon dacon = new Datacon();
   
    protected void Page_Load(object sender, EventArgs e)
    {
        if (!IsPostBack)
        {
            
            string id=Request.QueryString["id"].ToString();
            if(id!=null)
            Session["id"]=id;
            string sqlstr = "select * from proApply where id=" + id;
            DataSet myds = dacon.getds(sqlstr);


            if (myds != null)
            {
                Lyz_mc1.Text = Lyz_mc1.Text + myds.Tables[0].Rows[0]["code"].ToString();
                Lyz_mc2.Text = Lyz_mc2.Text + myds.Tables[0].Rows[0]["codesize"].ToString();
                Lyz_mc0.Text = Lyz_mc0.Text + myds.Tables[0].Rows[0]["productName"].ToString();
                Lyz_zt1.Text = Lyz_zt1.Text + myds.Tables[0].Rows[0]["productDate"].ToString();
                Lyz_lx1.Text = Lyz_lx1.Text + myds.Tables[0].Rows[0]["printDate"].ToString();
                Label2.Text = Label2.Text + myds.Tables[0].Rows[0]["QCman"].ToString();
                Lyz_mc3.Text =myds.Tables[0].Rows[0]["id"].ToString();
                Label4.Text = Label4.Text + myds.Tables[0].Rows[0]["lotNumber"].ToString();
                Label6.Text = Label6.Text + myds.Tables[0].Rows[0]["productCapacity"].ToString();
                Label8.Text = Label8.Text + myds.Tables[0].Rows[0]["totalNumber"].ToString();
                Label3.Text = Label3.Text + myds.Tables[0].Rows[0]["receiver"].ToString();
                Label5.Text = Label5.Text + myds.Tables[0].Rows[0]["storageLocation"].ToString();
                Label7.Text = Label7.Text + myds.Tables[0].Rows[0]["guaranteeRange"].ToString();
                Label9.Text = Label9.Text + myds.Tables[0].Rows[0]["DesName"].ToString();
                TextBox12.Text = TextBox12.Text + myds.Tables[0].Rows[0]["remark"].ToString();
                if (TextBox12.Text.ToString().Trim() == "")
                {
                    Label20.Visible = false;
                    TextBox12.Visible = false;
                }
                Label21.Text = Label21.Text + myds.Tables[0].Rows[0]["Applydate"].ToString();
                string state = "";
                int i = (int)myds.Tables[0].Rows[0]["AllocFlag"];
                switch (i)
                {
                    case 0:
                        state = "已经保存";
                        break;
                    case 1:
                        state = "已经提交（未受理）";
                        break;
                    case 2:
                        state = "受理未通过";
                        break;
                    case 3:
                        state = "受理通过";
                        break;
                    case 4:
                        state = "通过并生成二维码图像";
                        break;
                }
         Label22.Text = Label22.Text +state;
        
            }

  else Page.ClientScript.RegisterStartupScript(this.GetType(), "", "<Script>alert('读取信息失败');</Script>");

        }
      
    }

    protected void DropDownList1_SelectedIndexChanged(object sender, EventArgs e)
    {

    }
protected void  Button1_Click(object sender, EventArgs e)
{
      SqlConnection con = dacon.getcon();
      SqlCommand myCommand = new SqlCommand("update proApply set  AllocFlag=3 and Suggest='"+spyj.Text.Trim()+"' where id=" + Session["id"], con);
        myCommand.Connection.Open();
        int i = (int)myCommand.ExecuteNonQuery();
        myCommand.Connection.Close();

        if (i < 1)
        {
             string str_Message = "审批信息失败。";
            Page.ClientScript.RegisterStartupScript(this.GetType(), "", "<Script>alert('" + str_Message + "');</Script>");
            //Page.RegisterStartupScript("", "<script>alert('" + str_Message + "');</script>");
            return;
        }else
        {
              string str_Message = "审批信息成功。";
            Page.ClientScript.RegisterStartupScript(this.GetType(), "", "<Script>alert('" + str_Message + "');</Script>");
            //Page.RegisterStartupScript("", "<script>alert('" + str_Message + "');</script>");
            return;
        }

}
protected void Button2_Click(object sender, EventArgs e)
{
    SqlConnection con = dacon.getcon();
    SqlCommand myCommand = new SqlCommand("update proApply set  AllocFlag=2 and Suggest='" + spyj.Text.Trim() + "' where id=" + Session["id"], con);
    myCommand.Connection.Open();
    int i = (int)myCommand.ExecuteNonQuery();
    myCommand.Connection.Close();

    if (i < 1)
    {
        string str_Message = "审批信息失败。";
        Page.ClientScript.RegisterStartupScript(this.GetType(), "", "<Script>alert('" + str_Message + "');</Script>");
        //Page.RegisterStartupScript("", "<script>alert('" + str_Message + "');</script>");
        return;
    }
    else
    {
        string str_Message = "审批信息成功。";
        Page.ClientScript.RegisterStartupScript(this.GetType(), "", "<Script>alert('" + str_Message + "');</Script>");
        //Page.RegisterStartupScript("", "<script>alert('" + str_Message + "');</script>");
        return;
    }

}
protected void spyj_TextChanged(object sender, EventArgs e)
{

}
}