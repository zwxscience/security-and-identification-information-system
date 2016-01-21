using System;
using System.Data;
using System.Configuration;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;
using System.Data.SqlClient;

/// <summary>
/// Datacon 的摘要说明
/// </summary>
public class Datacon
{
	public Datacon()
	{
		//
		// TODO: 在此处添加构造函数逻辑
		//
	}

 
    
    #region  建立数据库连接
    /// <summary>
    /// 建立数据库连接.
    /// </summary>
    /// <returns>返回SqlConnection对象</returns>
    public SqlConnection getcon()
    {
        string M_str_sqlcon = System.Configuration.ConfigurationSettings.AppSettings["ConnectionString"].ToString(); //"Data Source=(local);Database=SIIS;user id=sa;pwd=123456";
        SqlConnection myCon = new SqlConnection(M_str_sqlcon);
        return myCon;
    }
    #endregion

    #region  执行SqlCommand命令
    /// <summary>
    /// 执行SqlCommand
    /// </summary>
    /// <param name="M_str_sqlstr">SQL语句</param>
    public void getcom(string M_str_sqlstr)
    {
        SqlConnection sqlcon = this.getcon();
        sqlcon.Open();
        SqlCommand sqlcom = new SqlCommand(M_str_sqlstr, sqlcon);
        sqlcom.ExecuteNonQuery();
        sqlcom.Dispose();
        sqlcon.Close();
        sqlcon.Dispose();
    }
    #endregion

    //#region  执行SqlCommand命令返回受影响行数
    ///// <summary>
    ///// 执行SqlCommand命令返回受影响行数
    ///// </summary>
    ///// <param name="M_str_str">SQL语句</param>
    //public int exccom(string M_str_sqlstr)
    //{
    //    int a = 0;
    //    SqlConnection sqlcon = this.getcon();
    //    sqlcon.Open();
    //    SqlCommand sqlcom = new SqlCommand(M_str_sqlstr, sqlcon);
    //    a = sqlcom.ExecuteNonQuery();
    //    sqlcom.Dispose();
    //    sqlcon.Close();
    //    sqlcon.Dispose();
    //    return a;
    //}
    //#endregion

    #region  创建DataSet对象
    /// <summary>
    /// 创建一个DataSet对象
    /// </summary>
    /// <param name="M_str_sqlstr">SQL语句</param>
    /// <returns>返回DataSet对象</returns>
    public DataSet getds(string M_str_sqlstr)
    {
        SqlConnection sqlcon = this.getcon();
        SqlDataAdapter sqlda = new SqlDataAdapter(M_str_sqlstr, sqlcon);
        DataSet myds = new DataSet();
        sqlda.Fill(myds);
        sqlcon.Dispose();
         sqlcon.Close();
        return myds;
    }
    #endregion

    #region  在DataSet中插入表
    /// <summary>
    ///  一个DataSet中插入多个表
    /// </summary>
    /// <param name="ds">DataSet名</param>
    /// <param name="M_str_sqlstr">SQL语句</param>
    /// <param name="M_str_table">表名</param>

    public void getdstable(DataSet ds, string M_str_sqlstr, string M_str_table)
    {
        SqlConnection sqlcon = this.getcon();
        SqlDataAdapter sqlda = new SqlDataAdapter(M_str_sqlstr, sqlcon);
        sqlda.Fill(ds, M_str_table);

    }
    #endregion

    #region  创建SqlDataReader对象
    /// <summary>
    /// 创建一个SqlDataReader对象
    /// </summary>
    /// <param name="M_str_sqlstr">SQL语句</param>
    /// <returns>返回SqlDataReader对象</returns>
    public SqlDataReader getread(string M_str_sqlstr)
    {
        SqlConnection sqlcon = this.getcon();
        SqlCommand sqlcom = new SqlCommand(M_str_sqlstr, sqlcon);
        sqlcon.Open();
        SqlDataReader sqlread = sqlcom.ExecuteReader(CommandBehavior.CloseConnection);
        return sqlread;
    }
    #endregion

  

}

    


