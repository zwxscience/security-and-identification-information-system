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
public partial class admin_ClientInfoManagement : System.Web.UI.UserControl
{
    Datacon dacon = new Datacon();
    static int num_of_data;
    static bool tag = false;//设置判断按钮标志
    protected void Page_Load(object sender, EventArgs e)
    {
        if (!IsPostBack)
        {

            string sqlstr = "select id,username,code,productName,productDate,Applydate,AllocFlag from proApply where  AllocFlag=1 ";
            DataSet myds = dacon.getds(sqlstr);


            QRInfo.DataSource = myds.Tables[0].DefaultView;

            QRInfo.PageSize = 10;
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

        string sqlwhere = "";
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
        string sqlstr, sqlstr1 = "select count(*) from  proApply where AllocFlag=1";
        if (pageindex > 0)//翻页了
        {

            a = pageindex * 10;
            sqlstr = "select top 10 * from proApply where id not in (select top  "
            + a.ToString() + " id from proApply where AllocFlag=1" + sqlwhere + " order by Applydate desc)";
        }
        else//第一次加载
            sqlstr = "select top 10 * from proApply where AllocFlag=1";

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
        string sqlwhere = "";
  
        if (cpbh.Text.Trim() != "") sqlwhere = sqlwhere + " and code like '%" + cpbh.Text.Trim() + "%'";
        if (cpmc.Text.Trim() != "") sqlwhere = sqlwhere + " and productName like '%" + cpmc.Text.Trim() + "%'";

        if (ksrq.Text.Trim() != "")
            sqlwhere = sqlwhere + " and productDate >='" + ksrq.Text.Trim() + "'";
        if (jzrq.Text.Trim() != "") sqlwhere = sqlwhere + " and productDate<='" + jzrq.Text.Trim() + "'";
        datadeal(pageindex, sqlwhere);
    }


    protected void QRInfo_RowCommand(object sender, GridViewCommandEventArgs e)
    {
        if (e.CommandName== "通过")
        {
            int index = Convert.ToInt32(e.CommandArgument);

            // Retrieve the row that contains the button clicked 
            // by the user from the Rows collection.      
            GridViewRow row = QRInfo.Rows[index];
            int id = int.Parse(row.Cells[0].Text.ToString());//获取id
            string username=row.Cells[1].Text.ToString().Trim();
            SqlConnection con = dacon.getcon();
            SqlCommand myCommand = new SqlCommand("update proApply set  AllocFlag=3 where id=" + id, con);
            myCommand.Connection.Open();
            int i = (int)myCommand.ExecuteNonQuery();
            myCommand.Connection.Close();
            if (i < 1)
            {

                string str_Message = "通过操作失败。";
                Page.ClientScript.RegisterStartupScript(this.GetType(), "", "<Script>alert('" + str_Message + "');</Script>");
                //Page.RegisterStartupScript("", "<script>alert('" + str_Message + "');</script>");
                return;
            }
            else
            {
                string sqlstr = "select id,username,code,productName,productDate,Applydate,AllocFlag,PLflag from proApply where  AllocFlag=1";
                DataSet myds = dacon.getds(sqlstr);


                QRInfo.DataSource = myds.Tables[0].DefaultView;

                QRInfo.PageSize = 10;
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

              //下面统计次数，传申请ID
                staticCount(id,username);

                string str_Message = "通过操作成功。";
                Page.ClientScript.RegisterStartupScript(this.GetType(), "", "<Script>alert('" + str_Message + "');</Script>");
                //Page.RegisterStartupScript("", "<script>alert('" + str_Message + "');</script>");
                return;
            }
      
        }

    }
       void  staticCount(int id,string clientName)
{
           //(1)确定id的批量还是单次
    string sqlstr1 = "select * from proApply where  id=" + id.ToString();
    DataSet myds = dacon.getds(sqlstr1);
    int PLflag = int.Parse(myds.Tables[0].Rows[0]["PLflag"].ToString());
           myds.Clear();
           //获取当前费率
           sqlstr1 = "select top 1 * from rateSet order by id desc";
           myds = dacon.getds(sqlstr1);
           float SI=float.Parse(myds.Tables[0].Rows[0]["SIRate"].ToString());
           float BI=float.Parse(myds.Tables[0].Rows[0]["BIRate"].ToString());
           myds.Clear();
           //(3)获取当前月份
           string month=DateTime.Now.ToString("Y");
    string sqlstr = "select * from userFees where  month='"+month+"' and  ClientName='"+clientName+"'";
     myds = dacon.getds(sqlstr);

    if (myds.Tables[0].Rows.Count > 0)//fee记录
    {
        int count1 = 0, count2 = 0;
        if (PLflag == 1) count2 = 1;
        else count1 = 1;
        int count3 = 0, count4 = 0;
        try
        {
            count3 = int.Parse(myds.Tables[0].Rows[0]["count1"].ToString());
            count4 = int.Parse(myds.Tables[0].Rows[0]["count2"].ToString());
        }
        catch (Exception e)
        {
            Response.Write("<script language='javascript'>alert('读取当前费率读取错误，请检查费率设置！错误信息：" + e.Message + "');</script>");
            return;
        }
        count3 =count1+count3;
        count4 = count4 + count2;
        float Cost = float.Parse(myds.Tables[0].Rows[0]["Cost"].ToString());
       // float pay = float.Parse(myds.Tables[0].Rows[0]["pay"].ToString());
      float remain = float.Parse(myds.Tables[0].Rows[0]["remain"].ToString());
      Cost = Cost + SI * count1+ count2 * BI;
        remain =remain+ count1 * SI + count2 * BI; 
        string Remark = "记录被添加，更改日期：" + DateTime.Now.ToString("Y") + ",由申请号ID为" + id.ToString() + "的申请表所更新。";
        try
        {
            SqlConnection con = dacon.getcon();
            SqlCommand myCommand = new SqlCommand("update userFees set  count1=" + count3.ToString() + " , count2=" + count4.ToString() + " , Cost=" + Cost.ToString() + " , remain=" + remain.ToString() + ",Remark='" + Remark + "' where ClientName='" + clientName + "' and month='" + month + "'", con);
            myCommand.Connection.Open();
            int i = (int)myCommand.ExecuteNonQuery();
            myCommand.Connection.Close();
        }
        catch (Exception e)
        {
            Label11.Text = "更新费用表格时出现错误，错误：" + e.Message;
        }
    }
    else//无记录创建记录
    {
        SqlConnection con = dacon.getcon();
        string ClientName = clientName;
        string role = "客户";
        int count1=0,count2=0;
        if (PLflag == 1) count2++;
        else count1++;
       float Cost = count1 * SI + count2 * BI;
       float pay = 0;
       float remain = Cost;
       string Remark = "管理员批准后创建该记录，创建日期：" + DateTime.Now.ToString("Y")+",由申请号ID为"+id.ToString()+"的申请表创建";
       try
       {
           SqlCommand myCommand = new SqlCommand("insert into userFees(ClientName,role,count1,count2,Cost,pay,remain,month,Remark,OpTime)  values('" + ClientName + "','" + role + "'," + count1 + "," + count2 + "," + Cost + "," + pay + "," + remain + ",'" + month + "','" + Remark + "','" + DateTime.Now.ToString() + "')", con);
           myCommand.Connection.Open();
           int i = (int)myCommand.ExecuteNonQuery();
           myCommand.Connection.Close();
       }
       catch (Exception e)
       {
           Label11.Text = "创建费用表格时出现错误，错误：" + e.Message;
       }

    }




}


}
