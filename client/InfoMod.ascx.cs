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

public partial class client_InfoMod : System.Web.UI.UserControl
{
    Datacon dacon = new Datacon();
   
    protected void Page_Load(object sender, EventArgs e)
    {
        if (!IsPostBack)
        {
            if (null == Session["username"])
            {
                Response.Write("<script>alert('用户登录超时,请重新登录。');location='../Login.aspx'</script>");

                return;
            }
            if(Request.QueryString["id"]=="")return;
            string id = Request.QueryString["id"].ToString();
            string sqlstr = "select * from proApply where id='" + id + "'";
            try{
            DataSet myds= dacon.getds(sqlstr);
            Label22.Text = id;
            if (myds.Tables[0].Rows.Count <= 0) { Label23.Text = "未查到数据"; return; }
            if (int.Parse(myds.Tables[0].Rows[0]["AllocFlag"].ToString().Trim())==1)//提交状态
            {
                Response.Write("<script>alert('该条目处于提交状态，无法修改信息。');location='QueryInfo.aspx'</script>");
                return;
            }
            bh.Text = myds.Tables[0].Rows[0]["code"].ToString();
            TextBox1.Text = myds.Tables[0].Rows[0]["productName"].ToString();
            scrq.Text = myds.Tables[0].Rows[0]["productDate"].ToString();
            ysrq.Text = myds.Tables[0].Rows[0]["printDate"].ToString();
            DropDownList1.SelectedValue = myds.Tables[0].Rows[0]["codesize"].ToString();

            TextBox7.Text = myds.Tables[0].Rows[0]["QCman"].ToString();
            TextBox10.Text = myds.Tables[0].Rows[0]["receiver"].ToString();
            TextBox4.Text = myds.Tables[0].Rows[0]["lotNumber"].ToString();
            TextBox8.Text = myds.Tables[0].Rows[0]["storageLocation"].ToString();
            TextBox5.Text = myds.Tables[0].Rows[0]["productCapacity"].ToString();
            TextBox9.Text = myds.Tables[0].Rows[0]["guaranteeRange"].ToString();
            TextBox6.Text = myds.Tables[0].Rows[0]["totalNumber"].ToString();
            TextBox11.Text = myds.Tables[0].Rows[0]["DesName"].ToString();
            TextBox12.Text = myds.Tables[0].Rows[0]["remark"].ToString();
       
            }
            catch (Exception e1)
                {Label23.Text="载入数据出错，错误信息："+e1.Message;return;}     

        }
    }


   
    protected void Button2_Click(object sender, EventArgs e)
    {
        if (TextBox1.Text.ToString().Trim() == "")
        {
            InfoTip0.Text = "产品名称不能为空";
            return;
        }
         int i = 0;
         try
         {
             SqlConnection con = dacon.getcon();
             SqlCommand myCommand = new SqlCommand("update  proApply set  username='" + Session["username"] + "',codesize='" + DropDownList1.SelectedValue + "',code='" + bh.Text + "',productName='" + TextBox1.Text + "',productDate='" + scrq.Text + "',printDate='" + ysrq.Text + "',QCman='" + TextBox7.Text + "',lotNumber='" + TextBox4.Text + "',productCapacity='" + TextBox5.Text + "',totalNumber='" + TextBox6.Text + "',DesName='" + TextBox11.Text + "',receiver='" + TextBox10.Text + "',storageLocation='" + TextBox8.Text + "',guaranteeRange='" + TextBox9.Text + "',remark='" + TextBox12.Text + "',AllocFlag=0 where id=" + Label22.Text, con);//修改后为保存状态

             myCommand.Connection.Open();
             i = (int)myCommand.ExecuteNonQuery();
             myCommand.Connection.Close();
         }
         catch (Exception e1) { Label23.Text = "更新数据出错，错误信息：" + e1.Message; return; }
            if (i < 1)
            {
                string str_Message = "申请信息更新失败,请重试。";
                Page.ClientScript.RegisterStartupScript(this.GetType(), "", "<Script>alert('" + str_Message + "');</Script>");
                //Page.RegisterStartupScript("", "<script>alert('" + str_Message + "');</script>");
                return;
            }
            else
            {
                string str_Message = "申请信息更新成功。";
                Page.ClientScript.RegisterStartupScript(this.GetType(), "", "<Script>alert('" + str_Message + "');</Script>");
                //Page.RegisterStartupScript("", "<script>alert('" + str_Message + "');</script>");
                return;
            }
     
    }
}
