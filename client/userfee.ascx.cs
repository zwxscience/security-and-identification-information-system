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
public partial class admin_RateSet : System.Web.UI.UserControl
{
    Datacon dacon = new Datacon();
    static int num_of_data;
    static bool tag = false;//设置判断按钮标志
    protected void Page_Load(object sender, EventArgs e)
    {
        if (!IsPostBack)
        {

            string sqlstr = "select* from userFees where ClientName='"+Session["username"]+"'";
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
     
        if (month.Text.Trim() != "") sqlwhere = sqlwhere + " and month='" + month.Text.Trim() + "'";
        datadeal(pageindex, sqlwhere);
    }
    protected void datadeal(int pageindex, string sqlwhere)//处理语句
    {
        int a;//当前页
        string sqlstr, sqlstr1 = "select count(*) from  userFees where ClientName='" + Session["username"] + "'";
        if (pageindex > 0)//翻页了
        {

            a = pageindex * 10;
            sqlstr = "select top 10 * from userFees where id not in (select top  "
            + a.ToString() + " id from userFees where " + sqlwhere + " and ClientName='" + Session["username"] + "' order by id desc) and ClientName='" + Session["username"] + "'";
        }
        else//第一次加载
            sqlstr = "select top 10 * from userFees where ClientName='"+Session["username"]+"'";

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

      
        if (month.Text.Trim() != "") sqlwhere = sqlwhere + " and month like '%" + month.Text.Trim() + "%'";
        datadeal(pageindex, sqlwhere);
    }






    protected void Button1_Click(object sender, EventArgs e)
    {


        //SqlConnection conn = dacon.getcon();


        //SqlDataAdapter da = new SqlDataAdapter("SELECT id as '序号',month as '统计月份',	count1	as '单次统计数', count2	as '批量统计数',Cost as '应付金额',pay as '实际支付',remain as '未结算',OpTime	as '更新日期' FROM userFees where ClientName='" + Session["username"] + "' ORDER BY id", conn);
        //DataSet ds = new DataSet();
        //da.Fill(ds, "table1");
        //if(ds.Tables[0].Rows.Count<1)
        //{
        //    Response.Write("<script>alert('您的费用记录为空，暂时不能下载。')</script>");
        //    return;
        //}
        //System.Data.DataTable dt = ds.Tables["table1"]; //获取数据集
        //DataView dv = ds.Tables["table1"].DefaultView;

        if (this.rate.Rows.Count <= 0)
        {
            Response.Write("<script>alert('您当前表格的记录为空，暂时不能下载。请重新搜索')</script>");
            return;
        }
        if (Session["username"] == null)
        {
            Response.Write("<script>alert('用户名失效，请重新登录')</script>");
            return;
        }
        //Gridview转datable
        DataTable dt = new DataTable();
        dt.Columns.Add("序号", typeof(string));
        dt.Columns.Add("统计月份", typeof(string));
        dt.Columns.Add("用户名", typeof(string));
        dt.Columns.Add("单次统计数", typeof(int));
        dt.Columns.Add("批量统计数", typeof(int));
        dt.Columns.Add("应付金额", typeof(float));
        dt.Columns.Add("实际支付", typeof(float));
        dt.Columns.Add("未结算", typeof(float));
        dt.Columns.Add("更新日期", typeof(string));

        for (int i = 0; i < this.rate.Rows.Count; i++)
        {
            //dt.Rows.Add(rate.Rows[i]);
            DataRow newrow = dt.NewRow();
            for (int j = 0; j < rate.Columns.Count; j++)
                newrow[j] = rate.Rows[i].Cells[j].Text.Trim();
            dt.Rows.Add(newrow);
        }
        DataView dv = dt.DefaultView;
        string str1 = "用户" + Session["username"].ToString() + DateTime.Now.ToString("D") + "的账单";
        string str2 = "用户" + Session["username"].ToString() + "的账单统计";
        if (str1 == "")
        {
            Response.Write("<script>alert('导出的Excel表文件的名称不能为空。')</script>");
            return;
        }
        if (str2 == "")
        {
            Response.Write("<script>alert('该表的标题不能为空。')</script>");
            return;
        }
        try
        {
            SQLtoExcel se = new SQLtoExcel();

            String filepath = Server.MapPath("用户报表/" + "" + str1 + ".xls");
            se.OutputExcel(dv, str1, str2, filepath);
            //在服务器上产生excel的方法，dv为要输出到Excel的数据，str1为文件名称 ,str2为标题名称 ，path是路径
            string path = Server.MapPath("用户报表/" + str1 + ".xls");

            System.IO.FileInfo file = new System.IO.FileInfo(path);
            Response.Clear();
            Response.Charset = "GB2312";
            Response.ContentEncoding = System.Text.Encoding.UTF8;
            // 添加头信息，为"文件下载/另存为"对话框指定默认文件名 
            Response.AddHeader("Content-Disposition", "attachment; filename=" + Server.UrlEncode(file.Name));
            // 添加头信息，指定文件大小，让浏览器能够显示下载进度 
            Response.AddHeader("Content-Length", file.Length.ToString());

            // 指定返回的是一个不能被客户端读取的流，必须被下载 
            Response.ContentType = "application/ms-excel";

            // 把文件流发送到客户端 
            Response.WriteFile(file.FullName);
            // 停止页面的执行 

            Response.End();
        }
        catch (Exception e1)
        {
            Response.Write("<script>alert('生成excel过程出现错误，错误原因：" + e1.Message + "。')</script>");
            return;
        }
    }
}