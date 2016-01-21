using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data.SqlClient;
using System.Configuration;
using System.Collections;
using System.Data;
public partial class admin_userfee : System.Web.UI.UserControl
{
    Datacon dacon = new Datacon();
    static int num_of_data;
    static bool tag = false;//设置判断按钮标志
    protected void Page_Load(object sender, EventArgs e)
    {
        if (!IsPostBack)
        {

            string sqlstr = "select* from userFees";
            DataSet myds = dacon.getds(sqlstr);


            rate.DataSource = myds.Tables[0].DefaultView;

            rate.PageSize = 10;
            rate.DataBind();


            this.mhbind(0);
            jq_current.Text = "1";
            jq_all.Text = Convert.ToString(num_of_data);
            if (num_of_data == 1)
            {


                jq_First.Enabled = false;
                jq_Previous.Enabled = false;
                jq_Last.Enabled = false;
                jq_Next.Enabled = false;
            }
            else
            {
                jq_First.Enabled = false;
                jq_Previous.Enabled = false;
                jq_Last.Enabled = true;
                jq_Next.Enabled = true;
            }


        }

    }
    protected void First_Click(object sender, EventArgs e)
    {
        if (tag)
            this.jqbind(0);
        else
            this.mhbind(0);
        jq_current.Text = "1";
        jq_First.Enabled = false;
        jq_Previous.Enabled = false;
        jq_Last.Enabled = true;
        jq_Next.Enabled = true;
    }
    protected void Previous_Click(object sender, EventArgs e)
    {
        int a = Convert.ToInt32(jq_current.Text) - 1;
        if (tag)
            this.jqbind(a - 1);
        else
            this.mhbind(a - 1);
        if (a == 1)
        {
            jq_current.Text = "1";
            jq_First.Enabled = false;
            jq_Previous.Enabled = false;
            jq_Last.Enabled = true;
            jq_Next.Enabled = true;
        }
        else
        {
            jq_current.Text = Convert.ToString(a);
            jq_First.Enabled = true;
            jq_Previous.Enabled = true;
            jq_Last.Enabled = true;
            jq_Next.Enabled = true;
        }
    }
    protected void Next_Click(object sender, EventArgs e)
    {
        int a = Convert.ToInt32(jq_current.Text) - 1;
        if (tag)
            this.jqbind(a + 1);
        else
            this.mhbind(a + 1);
        if (a == num_of_data - 2)
        {
            jq_current.Text = Convert.ToString(num_of_data);
            jq_First.Enabled = true;
            jq_Previous.Enabled = true;
            jq_Last.Enabled = false;
            jq_Next.Enabled = false;
        }
        else
        {
            jq_current.Text = Convert.ToString(a + 2);
            jq_First.Enabled = true;
            jq_Previous.Enabled = true;
            jq_Last.Enabled = true;
            jq_Next.Enabled = true;
        }
    }
    protected void Last_Click(object sender, EventArgs e)
    {
        if (tag)
            this.jqbind(num_of_data - 1);
        else
            this.mhbind(num_of_data - 1);
        jq_current.Text = Convert.ToString(num_of_data);
        jq_First.Enabled = true;
        jq_Previous.Enabled = true;
        jq_Last.Enabled = false;
        jq_Next.Enabled = false;
    }
    protected void btnjq_Click(object sender, EventArgs e)
    {
        tag = true;
        this.jqbind(0);
        jq_current.Text = "1";
        jq_all.Text = Convert.ToString(num_of_data);
        if (num_of_data <= 1)
        {
            jq_Next.Enabled = false;
            jq_Last.Enabled = false;
            jq_First.Enabled = false;
            jq_Previous.Enabled = false;
        }
        else
        {
            jq_First.Enabled = false;
            jq_Previous.Enabled = false;
            jq_Last.Enabled = true;
            jq_Next.Enabled = true;
        }
    }
    protected void jqbind(int pageindex)
    {

        string sqlwhere = "";
        if (username.Text.Trim() != "") sqlwhere = sqlwhere + " and ClientName='" + username.Text.Trim() + "'";
        if (month.Text.Trim() != "") sqlwhere = sqlwhere + " and month='" + month.Text.Trim() + "'";
        datadeal(pageindex, sqlwhere);
    }
    protected void datadeal(int pageindex, string sqlwhere)//处理语句
    {
        int a;//当前页
        string sqlstr, sqlstr1 = "select count(*) from  userFees where 1=1";
        if (pageindex > 0)//翻页了
        {

            a = pageindex * 10;
            sqlstr = "select top 10 * from userFees where id not in (select top  "
            + a.ToString() + " id from userFees where 1=1 " + sqlwhere + " order by id desc)";
        }
        else//第一次加载
            sqlstr = "select top 10 * from userFees where 1=1 ";

        sqlstr = sqlstr + sqlwhere + " order by id desc;" + sqlstr1 + sqlwhere;
        DataSet ds = dacon.getds(sqlstr);
        //为空时显示默认值
   
        rate.DataSource = ds.Tables[0];
        rate.DataBind();
        int s = (int)ds.Tables[1].Rows[0][0];
        Label1.Text = "共查到记录" + s.ToString() + "条";
        int zh = s / 10;
        int yu = s - zh * 10;
        if (yu == 0) num_of_data = zh;
        else num_of_data = zh + 1;
        rate.Visible = true;
        Panel_jq.Visible = true;

    }

    protected void btnmh_Click(object sender, EventArgs e)
    {
        tag = false;
        this.mhbind(0);
        jq_current.Text = "1";
        jq_all.Text = Convert.ToString(num_of_data);
        if (num_of_data <= 1)
        {
            jq_Next.Enabled = false;
            jq_Last.Enabled = false;
            jq_First.Enabled = false;
            jq_Previous.Enabled = false;
        }
        else
        {
            jq_First.Enabled = false;
            jq_Previous.Enabled = false;
            jq_Last.Enabled = true;
            jq_Next.Enabled = true;
        }

    }

    protected void mhbind(int pageindex)
    {
        string sqlwhere = "";

        if (username.Text.Trim() != "") sqlwhere = sqlwhere + " and ClientName like '%" + username.Text.Trim() + "%'";
        if (month.Text.Trim() != "") sqlwhere = sqlwhere + " and month like '%" + month.Text.Trim() + "%'";
        datadeal(pageindex, sqlwhere);
    }


    protected void rate_RowCommand(object sender, GridViewCommandEventArgs e)
    {
        if (e.CommandName == "通知")
        {
            try
            {
                int index = Convert.ToInt32(e.CommandArgument);
                string MessageContent = "";//评论内容
                string MessageName = "";//消息名称
                //string MessageDate = "";//消息日期
                string MessageOwner = Session["username"].ToString();
                string sendto = "";//对象
                int Comswitch = 0;//关闭评论
                GridViewRow row = rate.Rows[index];
                int id = int.Parse(row.Cells[0].Text.ToString());//获取id
                string username = row.Cells[2].Text.ToString();
                string role = row.Cells[3].Text.ToString();
                string count1 = row.Cells[4].Text.ToString();
                string count2 = row.Cells[5].Text.ToString();
                string Cost = row.Cells[6].Text.ToString();
                string pay = row.Cells[7].Text.ToString();
                string remain = row.Cells[8].Text.ToString();
                string month = row.Cells[1].Text.ToString();
                string sqlstr1 = "select top 1 * from rateSet order by id desc";
                DataSet myds = dacon.getds(sqlstr1);
                float SIRate = int.Parse(myds.Tables[0].Rows[0]["SIRate"].ToString());
                float BIRate = int.Parse(myds.Tables[0].Rows[0]["BIRate"].ToString());
                float GetRate = int.Parse(myds.Tables[0].Rows[0]["GetRate"].ToString());
                sendto = username.Trim();
                if (role.Trim() == "客户")
                {

                    MessageContent = "<p>尊敬的<span style=\"color:#FF0000;\">客户端</span>用户<span style=\"background-color: rgb(255, 0, 0);\">" + username + "</span>，您好：</p><p>您在" + month + "的费用使用如下：</p><table border=\"1\" cellpadding=\"0\" cellspacing=\"0\"> <tbody><tr>  <td valign=\"top\"><p>单次生成费率</p></td>  <td valign=\"top\"><p>批量生成费率</p></td>  <td valign=\"top\"><p>单次生成次数</p></td>  <td valign=\"top\"><p>批量生成次数</p></td>  <td valign=\"top\"><p>应付金额</p></td>  <td valign=\"top\"><p>实付金额</p></td>  <td valign=\"top\"><p>未结算费用</p></td> </tr> <tr>  <td valign=\"top\"><p>" + SIRate.ToString() + "元</p></td>  <td valign=\"top\"><p>" + BIRate.ToString() + "元</p></td>  <td valign=\"top\"><p>" + count1 + "元</p></td>  <td valign=\"top\"><p>" + count2 + "元</p></td>  <td valign=\"top\"><p>" + Cost + "元</p></td>  <td valign=\"top\"><p>" + pay + "元</p></td>  <td valign=\"top\"><p>" + remain + "元</p></td> </tr></tbody></table><p>请尽快缴纳未结算余额，以免给您的使用带来不便。</p><p align=\"right\">防伪信息管理系统管理端</p><p align=\"right\">"+DateTime.Now.ToString("D")+"</p>";
                    MessageName = "客户端用户" + sendto + "费用催缴通知单";


                }
                else if (role.Trim() == "查询")
                {
                    MessageContent = "<p>尊敬的<span style=\"color:#FF0000;\">客户端</span>用户<span style=\"background-color: rgb(255, 0, 0);\">zwxscience</span>，您好：</p><p>您在2012年4月的费用使用如下：</p><table border=\"1\" cellpadding=\"0\" cellspacing=\"0\"> <tbody><tr>  <td valign=\"top\"><p>单次生成费率</p></td>  <td valign=\"top\"><p>批量生成费率</p></td>  <td valign=\"top\"><p>单次生成次数</p></td>  <td valign=\"top\"><p>批量生成次数</p></td>  <td valign=\"top\"><p>应付金额</p></td>  <td valign=\"top\"><p>实付金额</p></td>  <td valign=\"top\"><p>未结算费用</p></td> </tr> <tr>  <td valign=\"top\"><p>2元</p></td>  <td valign=\"top\"><p>1元</p></td>  <td valign=\"top\"><p>1元</p></td>  <td valign=\"top\"><p>1元</p></td>  <td valign=\"top\"><p>3元</p></td>  <td valign=\"top\"><p>0元</p></td>  <td valign=\"top\"><p>3元</p></td> </tr></tbody></table><p>请尽快缴纳未结算余额，以免给您的使用带来不便。</p><p align=\"right\">防伪信息管理系统管理端</p><p align=\"right\">" + DateTime.Now.ToString("D") + "</p>";
                    MessageName = "查询端用户" + sendto + "费用催缴通知单";
                }
                SqlConnection con = dacon.getcon();
                SqlCommand myCommand = new SqlCommand("INSERT INTO xxfb(MessageName,MessageOwner,MessageContent, MessageDate,sendto,Comswitch) VALUES(@NewsName,@MessageOwner,@NewsContent,@NewsDate,@sendto,@Comswitch)", con);
      myCommand.Parameters.Add(new SqlParameter("@NewsName", SqlDbType.NVarChar, 50));
      myCommand.Parameters["@NewsName"].Value = MessageName;
        myCommand.Parameters.Add(new SqlParameter("@NewsContent", SqlDbType.Text, 30000));
        myCommand.Parameters["@NewsContent"].Value = MessageContent;
        myCommand.Parameters.Add(new SqlParameter("@NewsDate", SqlDbType.NVarChar, 30));
        myCommand.Parameters.Add(new SqlParameter("@MessageOwner", SqlDbType.NVarChar, 30));
        string time = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss");
        myCommand.Parameters["@MessageOwner"].Value = Session["username"].ToString();
        myCommand.Parameters["@NewsDate"].Value = time;
        myCommand.Parameters.Add(new SqlParameter("@sendto", SqlDbType.NVarChar, 30));
        myCommand.Parameters["@sendto"].Value = sendto;
        myCommand.Parameters.Add(new SqlParameter("@Comswitch", SqlDbType.Int, 30));
        myCommand.Parameters["@Comswitch"].Value = Comswitch; 
        myCommand.Connection.Open();
        int i = (int)myCommand.ExecuteNonQuery();
        myCommand.Connection.Close();
      if (i < 1)
                {

                    string str_Message = "通知操作失败。";
                    Page.ClientScript.RegisterStartupScript(this.GetType(), "", "<Script>alert('" + str_Message + "');</Script>");
                    //Page.RegisterStartupScript("", "<script>alert('" + str_Message + "');</script>");
                    return;
                }
                else
                {
               
                    string str_Message = "通知操作成功。";
                    Page.ClientScript.RegisterStartupScript(this.GetType(), "", "<Script>alert('" + str_Message + "');</Script>");
                    //Page.RegisterStartupScript("", "<script>alert('" + str_Message + "');</script>");
                    return;
                }
            }
            catch (Exception e1)
            {
                Label10.Text = "出错了。出错信息：" + e1.Message;
            }

        }
        else return;
    }


   
}