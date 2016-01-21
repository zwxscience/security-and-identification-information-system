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

public partial class check_MesageInfo : System.Web.UI.UserControl
{

    Datacon dacon = new Datacon();
    static int num_of_data;
    static bool tag = false;//设置判断按钮标志
    protected void Page_Load(object sender, EventArgs e)
    {
        if (!IsPostBack)
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
    protected void datadeal(int pageindex, string sqlwhere)//处理语句
    {
        int a;//当前页
        string sqlstr, sqlstr1 = "select count(*) from  xxfb where (sendto='" + Session["username"] + "' or sendto='全部' or sendto='查询')";
        if (pageindex > 0)//翻页了
        {
            a = pageindex * 10;
            sqlstr = "SELECT *  FROM xxfb where MessagesId not in (select top "
            + a.ToString() + "MessagesId from xxfb where 1=1" + sqlwhere + " and (sendto='" + Session["username"] + "' or sendto='全部' or sendto='查询') order by MessageDate desc)";
        }
        else//第一次加载
            sqlstr = "SELECT top 10 * FROM xxfb where (sendto='" + Session["username"] + "' or sendto='全部' or sendto='查询')";
        sqlstr = sqlstr + sqlwhere + " order by MessageDate desc;" + sqlstr1 + sqlwhere;
        DataSet ds = dacon.getds(sqlstr);
        //为空时显示默认值
        for (int i = 0; i < ds.Tables[0].Rows.Count; i++)
        {

            if (ds.Tables[0].Rows[i]["MessageOwner"].ToString() == "")
                ds.Tables[0].Rows[i]["MessageOwner"] = "暂无数据";
            if (ds.Tables[0].Rows[i]["visitcount"].ToString() == "")
                ds.Tables[0].Rows[i]["visitcount"] = "暂无数据";

        }
        Info.DataSource = ds.Tables[0];
        Info.DataBind();
        int s = (int)ds.Tables[1].Rows[0][0];
        totalnum.Text = "共查到记录" + s.ToString() + "条";
        int zh = s / 10;
        int yu = s - zh * 10;
        if (yu == 0) num_of_data = zh;
        else num_of_data = zh + 1;
        Info.Visible = true;
        Panel_jq.Visible = true;
    }

    protected void jqbind(int pageindex)
    {
        string sqlwhere = "";
        if (caption.Text.Trim() != "") sqlwhere = sqlwhere + " and xxfb.MessageName='" + caption.Text.Trim() + "'";
        if (Infokssj.Text.Trim() != "")
        //string time1=Infokssj.Text.ToString("yyyy-MM-dd 00:00:00");
        {
            string times = Infokssj.Text.ToString() + " 00:00:00";
            sqlwhere = sqlwhere + " and xxfb.MessageDate>='" + times + "'";
        }
        if (Infojssj.Text.Trim() != "")
        {
            string timee = Infojssj.Text.ToString() + " 23:59:59";
            sqlwhere = sqlwhere + " and xxfb.MessageDate<='" + timee + "'";
        }
        datadeal(pageindex, sqlwhere);




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
        if (caption.Text.Trim() != "") sqlwhere = sqlwhere + " and xxfb.MessageName like '%" + caption.Text.Trim() + "%'";
        if (Infokssj.Text.Trim() != "")
        //string time1=Infokssj.Text.ToString("yyyy-MM-dd 00:00:00");
        {
            string times = Infokssj.Text.ToString() + " 00:00:00";
            sqlwhere = sqlwhere + " and xxfb.MessageDate>='" + times + "'";
        }
        if (Infojssj.Text.Trim() != "")
        {
            string timee = Infojssj.Text.ToString() + " 23:59:59";
            sqlwhere = sqlwhere + " and xxfb.MessageDate<='" + timee + "'";
        }
        datadeal(pageindex, sqlwhere);

    }

    protected void RowDeleting(object sender, GridViewDeleteEventArgs e)
    {
        int i = e.RowIndex;

    } 

}
