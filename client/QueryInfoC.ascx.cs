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

public partial class query_SealInfo : System.Web.UI.UserControl
{
    Datacon dacon = new Datacon();
    static int num_of_data;
    static bool tag = false;//设置判断按钮标志
    protected void Page_Load(object sender, EventArgs e)
    {
        if (!IsPostBack)
        {

            string sqlstr = "select id,code,productName,productDate,Applydate,AllocFlag from proApply where username=' " + Session["username"] + "' and AllocFlag>2";
            DataSet myds = dacon.getds(sqlstr);


            QRInfo.DataSource = myds.Tables[0].DefaultView;

        
            QRInfo.DataBind();

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
        if (Session["username"] == null) Response.Write("<script>alert('用户登录超时，请重新登录。');location='../Login.aspx'</script>");
        string sqlwhere = " and username='"+Session["username"]+"'";;
        if (cpbh.Text.Trim() != "") sqlwhere = sqlwhere + " and code='" + cpbh.Text.Trim() + "'";
        if (cpmc.Text.Trim() != "") sqlwhere = sqlwhere + " and productName='" + cpmc.Text.Trim() + "'";

        if (ksrq.Text.Trim() != "")
            sqlwhere = sqlwhere + " and productDate >='" + ksrq.Text.Trim() + "'";
        if (jzrq.Text.Trim() != "") sqlwhere = sqlwhere + " and productDate<='" + jzrq.Text.Trim() + "'";
        datadeal(pageindex, sqlwhere);
    }
    protected void datadeal(int pageindex, string sqlwhere)//处理语句
    {
        int a;//当前页
        string sqlstr, sqlstr1 = "select count(*) from  proApply where AllocFlag>2";
        if (pageindex > 0)//翻页了
        {

            a = pageindex * 10;
            sqlstr = "select top 10 * from  proApply where id not in (select top "
            + a.ToString() + "id from proApply where AllocFlag>2" + sqlwhere + " order by Applydate desc)";
        }
        else//第一次加载
            sqlstr = "select top 10 * from proApply where AllocFlag>2";

        sqlstr = sqlstr + sqlwhere + " order by Applydate desc;" + sqlstr1 + sqlwhere;
        DataSet ds = dacon.getds(sqlstr);
        //为空时显示默认值
        for (int i = 0; i < ds.Tables[0].Rows.Count; i++)
        {
            if (ds.Tables[0].Rows[i]["code"].ToString() == "")
                ds.Tables[0].Rows[i]["code"] = "暂无数据";
            if (ds.Tables[0].Rows[i]["productName"].ToString() == "")
                ds.Tables[0].Rows[i]["productName"] = "暂无数据";
            if (ds.Tables[0].Rows[i]["productDate"].ToString() == "")
                ds.Tables[0].Rows[i]["productDate"] = "暂无数据";
            if (ds.Tables[0].Rows[i]["AllocFlag"].ToString() == "")
                ds.Tables[0].Rows[i]["AllocFlag"] = "暂无数据";

        }
        QRInfo.DataSource = ds.Tables[0];
        QRInfo.DataBind();
        int s = (int)ds.Tables[1].Rows[0][0];
        Label1.Text = "共查到记录" + s.ToString() + "条";
        int zh = s / 10;
        int yu = s - zh * 10;
        if (yu == 0) num_of_data = zh;
        else num_of_data = zh + 1;
        QRInfo.Visible = true;
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
        if (Session["username"] == null) Response.Write("<script>alert('用户登录超时，请重新登录。');location='../Login.aspx'</script>");
        string sqlwhere = " and username='"+Session["username"]+"'";
  
        if (cpbh.Text.Trim() != "") sqlwhere = sqlwhere + " and code like '%" + cpbh.Text.Trim() + "%'";
        if (cpmc.Text.Trim() != "") sqlwhere = sqlwhere + " and productName like '%" + cpmc.Text.Trim() + "%'";

        if (ksrq.Text.Trim() != "")
            sqlwhere = sqlwhere + " and productDate >='" + ksrq.Text.Trim() + "'";
        if (jzrq.Text.Trim() != "") sqlwhere = sqlwhere + " and productDate<='" + jzrq.Text.Trim() + "'";
        datadeal(pageindex, sqlwhere);
    }

    protected void TextBox1_TextChanged(object sender, EventArgs e)
    {

    }
    protected void QRInfo_SelectedIndexChanged(object sender, EventArgs e)
    {

    }
}
