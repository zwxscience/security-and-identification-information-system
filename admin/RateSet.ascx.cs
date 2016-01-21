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
    protected void Page_Load(object sender, EventArgs e)
    {

    }
    protected void Button1_Click(object sender, EventArgs e)
    {
        SqlConnection con = dacon.getcon();
        try
        {
            SqlCommand myCommand = new SqlCommand("insert into rateSet(SIRate,BIRate,GetRate,MoDate)  values(@SIRate,@BIRate,@GetRate,@MoDate)", con);
            myCommand.Parameters.Add(new SqlParameter("@SIRate", SqlDbType.Float, 5));
            myCommand.Parameters["@SIRate"].Value = float.Parse(dcsc.Text);
            myCommand.Parameters.Add(new SqlParameter("@BIRate", SqlDbType.Float, 5));
            myCommand.Parameters["@BIRate"].Value = float.Parse(plsc.Text);
            myCommand.Parameters.Add(new SqlParameter("@GetRate", SqlDbType.Float, 5));
            myCommand.Parameters["@GetRate"].Value = float.Parse(cxsc.Text);
            myCommand.Parameters.Add(new SqlParameter("@MoDate", SqlDbType.DateTime, 50));
            myCommand.Parameters["@MoDate"].Value = DateTime.Now.ToString();
            SetLastendDate();
         
            myCommand.Connection.Open();
            int i = (int)myCommand.ExecuteNonQuery();
            myCommand.Connection.Close();
            Label6.Text = "生成成功。请刷新页面后查看记录。";

        }catch(Exception e1)
        {
            Label6.Text = "生成过程出现错误，错误原因：" + e1.Message;
        }

    }
    void SetLastendDate()
    {
        SqlConnection con = dacon.getcon();
        string str = "select * from rateSet";
        DataSet myds = dacon.getds(str);

        if (myds.Tables[0].Rows.Count > 0)
        {
            con = dacon.getcon();
            string sqlstr = "update rateSet set  endDate='" + DateTime.Now.ToString() + "' where id =(select top 1 id from rateSet order by id desc) ";//设置最后一条的endtime
            SqlCommand myCommand = new SqlCommand(sqlstr,con);
            myCommand.Connection.Open();
            int i = (int)myCommand.ExecuteNonQuery();
            myCommand.Connection.Close();
        }

    }
}