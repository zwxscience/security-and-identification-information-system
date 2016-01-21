<%@ WebHandler Language="C#" Class="reg" %>

using System;
using System.Web;
using System.Text;
using System.Data.SqlClient;
using System.Data;
public class reg : IHttpHandler {
    
    public void ProcessRequest (HttpContext context) {
        context.Response.ContentType = "text/plain";
    //    context.Response.Write("Hello World");
        string key = "";
        if (context.Request.QueryString["username"] != null)
        {
            key = context.Request.QueryString["username"];
            int t = this.checkusername(key);
           
            context.Response.Write(t);
        }
        if (context.Request.QueryString["ComName"] != null)
        {
            key = context.Request.QueryString["ComName"];
            int t = this.checkcomname(key);
            context.Response.Write(t);
        }
        if (context.Request.QueryString["ComName"] != null && context.Request.QueryString["Regionalism"] != null && context.Request.QueryString["role"] != null && context.Request.QueryString["username"] != null && context.Request.QueryString["password"] != null)
        {
  string Regionalism =context.Request.QueryString["Regionalism"];
  string role = context.Request.QueryString["role"];
  string username = context.Request.QueryString["username"];
  string password = context.Request.QueryString["password"];
        int number = this.getNumber( Regionalism);
        number = int.Parse(number.ToString("D2"));
        string ComName = context.Request.QueryString["ComName"];
        string ComAddress = context.Request.QueryString["ComAddress"];
        string ComTel = context.Request.QueryString["ComTel"];
        string ComNet = context.Request.QueryString["ComNet"];
        string ComEmail = context.Request.QueryString["ComEmail"];
        string RegDate = DateTime.Now.ToString(); 
        int t = this.insertS( Regionalism, role, username , password, number, ComName, ComAddress, ComTel, ComNet, ComEmail, RegDate);
            context.Response.Write(t);
        }
    }
    //获取ID
    private int checkusername(string key)
    {
        Datacon dacon = new Datacon();
        SqlConnection con = dacon.getcon();
        SqlCommand myCommand = new SqlCommand("select count(*) from userInfo where username=@loginName", con);
        myCommand.Parameters.Add(new SqlParameter("@loginName", SqlDbType.NVarChar, 50));
        myCommand.Parameters["@loginName"].Value = key;
        myCommand.Connection.Open();
        int i = (int)myCommand.ExecuteScalar();
        myCommand.Connection.Close();
        return i;
    }
    private int checkcomname(string key)
    {
        Datacon dacon = new Datacon();
        SqlConnection con = dacon.getcon();
        SqlCommand myCommand = new SqlCommand("select count(*) from userInfo where ComName=@loginName", con);
        myCommand.Parameters.Add(new SqlParameter("@loginName", SqlDbType.NVarChar, 50));
        myCommand.Parameters["@loginName"].Value = key;
        myCommand.Connection.Open();
        int i = (int)myCommand.ExecuteScalar();
        myCommand.Connection.Close();
        return i;
    }
    int getNumber(string Regionalism)
    {
        Datacon dacon = new Datacon();
        SqlConnection con = dacon.getcon();
        SqlCommand myCommand = new SqlCommand("select count(*) from userInfo where Regionalism=@Regionalism", con);
        myCommand.Parameters.Add(new SqlParameter("@Regionalism", SqlDbType.NVarChar, 50));
        myCommand.Parameters["@Regionalism"].Value = Regionalism;
        myCommand.Connection.Open();
        int i = (int)myCommand.ExecuteScalar();
        myCommand.Connection.Close();
        return i;//以0为起始编号
    }
    int insertS(string Regionalism,string role,string username ,string password,int number,string ComName,string ComAddress,string ComTel,string ComNet,string ComEmail,string RegDate)
    {
        Datacon dacon = new Datacon();
        SqlConnection con = dacon.getcon();
        SqlCommand myCommand = new SqlCommand("insert into userInfo(role,username,password,Regionalism,number,ComName,ComAddress,ComTel,ComNet,ComEmail,RegDate)  values('" + role + "','" + username + "','" + password + "','" + Regionalism + "','" + number + "','" + ComName + "','" + ComAddress + "','" + ComTel + "','" + ComNet + "','" + ComEmail + "','" + RegDate + "')", con);
        myCommand.Connection.Open();
        int i = 0;
        try
        {
            i = (int)myCommand.ExecuteNonQuery();
        }catch(Exception e){}
        myCommand.Connection.Close();
        return i;
       
    }
    public bool IsReusable {
        get {
            return false;
        }
    }

}