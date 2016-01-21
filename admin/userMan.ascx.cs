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
public partial class admin_userMan : System.Web.UI.UserControl
{
    Datacon dacon = new Datacon();
    static int num_of_data;
    static bool tag = false;//设置判断按钮标志
    protected void Page_Load(object sender, EventArgs e)
    {
        if (!IsPostBack)
        {

            string sqlstr = "select* from userInfo";
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
        if (username.Text.Trim() != "") sqlwhere = sqlwhere + " and username='" + username.Text.Trim() + "'";
     
        datadeal(pageindex, sqlwhere);
    }
    protected void datadeal(int pageindex, string sqlwhere)//处理语句
    {
        int a;//当前页
        string sqlstr, sqlstr1 = "select count(*) from  userInfo where 1=1";
        if (pageindex > 0)//翻页了
        {

            a = pageindex * 10;
            sqlstr = "select top 10 * from userInfo where id not in (select top  "
            + a.ToString() + " id from userInfo where " + sqlwhere + " order by id desc)";
        }
        else//第一次加载
            sqlstr = "select top 10 * from userInfo  where 1=1 ";

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

        if (username.Text.Trim() != "") sqlwhere = sqlwhere + " and username like '%" + username.Text.Trim() + "%'";
        
        datadeal(pageindex, sqlwhere);
    }


    protected void rate_RowCommand(object sender, GridViewCommandEventArgs e)
    {
        if (e.CommandName == "更改")
        {
            int index = Convert.ToInt32(e.CommandArgument);
            GridViewRow row = rate.Rows[index];
            int id = int.Parse(row.Cells[0].Text.ToString());//获取id
            string state = row.Cells[6].Text.ToString().Trim();
            try
            {
                
                SqlConnection con = dacon.getcon(); string mysql="";
                if (state == "禁用")
                {
                    mysql = "update userInfo set state='激活' where id=" + id;
                    state = "激活";
                }
                else if (state == "激活")
                {
                    mysql = "update userInfo set state='禁用' where id=" + id;
                    state = "禁用";
                }
                SqlCommand myCommand = new SqlCommand(mysql, con);
      
              myCommand.Connection.Open();
        int i = (int)myCommand.ExecuteNonQuery();
        myCommand.Connection.Close();
      if (i < 1)
                {
                    
                    string str_Message = state+"操作失败。";
                    Page.ClientScript.RegisterStartupScript(this.GetType(), "", "<Script>alert('" + str_Message + "');</Script>");
                    //Page.RegisterStartupScript("", "<script>alert('" + str_Message + "');</script>");
                    return;
                }
                else
                {
                    string sqlstr = "select * from userInfo";
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

             
                    string str_Message = state+"操作成功。";
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