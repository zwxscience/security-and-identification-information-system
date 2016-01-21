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

public partial class client_ApplyInfo : System.Web.UI.UserControl
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

            string sqlstr = "select top 1 userInfo.Regionalism as Regionalism,userInfo.number as number,proApply.code as code from userInfo,proApply where proApply.username='" + Session["username"].ToString() + "' and codeType='二维码' order by proApply.code desc";//查找已有编号记录,选择最大的记录+1
            DataSet myds = dacon.getds(sqlstr);
            string strnumber =myds.Tables[0].Rows[0]["number"].ToString();
            if (strnumber.Length < 2) strnumber = "0" + strnumber;//补位
            string tail = new string('0',18-strnumber.Length);
            if (myds.Tables[0].Rows[0]["code"].ToString().Trim() == null)
            {
                //无记录
                bh.Text = myds.Tables[0].Rows[0]["Regionalism"].ToString() + myds.Tables[0].Rows[0]["number"].ToString() + tail;//9-24位
            }
            else
            {
                int i = int.Parse(myds.Tables[0].Rows[0]["code"].ToString().Substring(myds.Tables[0].Rows[0]["code"].ToString().Length-8, 8));//考虑有一亿个种类
                i++;
                string m = "";
                for (int j = 0; j < 8 - i.ToString().Length; j++)
                    m = m + "0";
                bh.Text = myds.Tables[0].Rows[0]["code"].ToString().Substring(0, 16) + m + i.ToString();

            }
            
          

        }
    }


    protected void Button1_Click(object sender, EventArgs e)
    {

          if (TextBox1.Text=="")
        {
           InfoTip0.Text = "产品名称不能为空";
            return;
        }
      
       SqlConnection con = dacon.getcon();
      SqlCommand  myCommand = new SqlCommand("insert into proApply(username,codeType,codesize,code,productName,productDate,printDate,QCman,lotNumber,productCapacity,totalNumber,DesName,receiver,storageLocation,guaranteeRange,remark,Applydate,AllocFlag) values('"+Session["username"]+"','二维码','"+DropDownList1.SelectedValue+"','"+bh.Text+"','"+TextBox1.Text+"','"+scrq.Text+"','"+ysrq.Text+"','"+TextBox7.Text+"','"+TextBox4.Text+"','"+TextBox5.Text+"','"+TextBox6.Text+"','"+TextBox11.Text+"','"+TextBox10.Text+"','"+TextBox8.Text+"','"+TextBox9.Text+"','"+TextBox12.Text+"','"+DateTime.Now.ToString()+"','0')", con);
    
        myCommand.Connection.Open();
        int i = (int)myCommand.ExecuteNonQuery();
        myCommand.Connection.Close();
        if (i < 1)
        {
            string str_Message = "申请信息保存失败,请重试。";
            Page.ClientScript.RegisterStartupScript(this.GetType(), "", "<Script>alert('" + str_Message + "');</Script>");
            //Page.RegisterStartupScript("", "<script>alert('" + str_Message + "');</script>");
            return;
        }
        else
        {
            string str_Message = "申请信息保存成功。";
            Page.ClientScript.RegisterStartupScript(this.GetType(), "", "<Script>alert('" + str_Message + "');</Script>");
            //Page.RegisterStartupScript("", "<script>alert('" + str_Message + "');</script>");
            return;
        }

    }
    protected void Button2_Click(object sender, EventArgs e)
    {
        if (TextBox1.Text.ToString().Trim() == "")
        {
            InfoTip0.Text = "产品名称不能为空";
            return;
        }

        SqlConnection con = dacon.getcon();
        SqlCommand myCommand = new SqlCommand("insert into proApply(username,codeType,codesize,code,productName,productDate,printDate,QCman,lotNumber,productCapacity,totalNumber,DesName,receiver,storageLocation,guaranteeRange,remark,Applydate,AllocFlag) values('" + Session["username"] + "','二维码','" + DropDownList1.SelectedValue + "','" + bh.Text + "','" + TextBox1.Text + "','" + scrq.Text + "','" + ysrq.Text + "','" + TextBox7.Text + "','" + TextBox4.Text + "','" + TextBox5.Text + "','" + TextBox6.Text + "','" + TextBox11.Text + "','" + TextBox10.Text + "','" + TextBox8.Text + "','" + TextBox9.Text + "','" + TextBox12.Text + "','" + DateTime.Now.ToString() + "','1')", con);

        myCommand.Connection.Open();
        int i = (int)myCommand.ExecuteNonQuery();
        myCommand.Connection.Close();
        if (i < 1)
        {
            string str_Message = "申请信息提交失败,请重试。";
            Page.ClientScript.RegisterStartupScript(this.GetType(), "", "<Script>alert('" + str_Message + "');</Script>");
            //Page.RegisterStartupScript("", "<script>alert('" + str_Message + "');</script>");
            return;
        }
        else
        {
            string str_Message = "申请信息提交成功。";
            Page.ClientScript.RegisterStartupScript(this.GetType(), "", "<Script>alert('" + str_Message + "');</Script>");
            //Page.RegisterStartupScript("", "<script>alert('" + str_Message + "');</script>");
            return;
        }
    }
}
