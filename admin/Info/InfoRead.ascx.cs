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
using System.Text;
public partial class admin_InfoRead : System.Web.UI.UserControl
{
    Datacon dacon = new Datacon();
    string key = "";
    protected void Page_Load(object sender, EventArgs e)
    {
        if (!IsPostBack)
        {//记录浏览量
            if (Request.QueryString["NewsId"] != null)
            {

                SqlConnection con = dacon.getcon();
                key = Request.QueryString["NewsId"].ToString();//NewsID是请求参数
                Session["NewsId"] = key;
               // this.Label2.Text = key;
               // StringBuilder items = new StringBuilder();
                string sqlstr = "SELECT  * FROM xxfb WHERE (MessagesId = '" + key + "')";
                DataSet ds = dacon.getds(sqlstr);
                for (int i = 0; i < ds.Tables[0].Rows.Count; i++)
                {//历遍所有的
                    if (ds.Tables[0].Rows[i]["MessageName"].ToString() != "")
                        this.Caption.Text = ds.Tables[0].Rows[i]["MessageName"].ToString();
                    if (ds.Tables[0].Rows[i]["MessageContent"].ToString() != "")
                        this.content.InnerHtml = ds.Tables[0].Rows[i]["MessageContent"].ToString();
                        //this.Content.Text = ds.Tables[0].Rows[i]["NewsContent"].ToString();
                    if (ds.Tables[0].Rows[i]["MessageOwner"].ToString() != "")
                        this.Lowner.Text += ds.Tables[0].Rows[i]["MessageOwner"].ToString();

                    if (ds.Tables[0].Rows[i]["MessageDate"].ToString() != "")
                        this.Ldate.Text = this.Ldate.Text.ToString() + ds.Tables[0].Rows[i]["MessageDate"].ToString();
                    if (ds.Tables[0].Rows[i]["Comswitch"].ToString() != "1")
                    {
                        this.Button1.Visible = false;
                        this.TextBox1.Visible = false;
                    }
                    if (ds.Tables[0].Rows[i]["visitcount"].ToString() != "")
                    {
                        int count=Convert.ToInt32(ds.Tables[0].Rows[i]["visitcount"])+1;
                          checkUpdate(key, count);
                        this.Lread.Text = this.Lread.Text.ToString() +count.ToString();
                    }
                }

            }
            else
                Response.Redirect("../Default.aspx");
        }


    }
    

   private int checkUpdate(string key1,int count)
    {


        SqlConnection con = dacon.getcon();
        if (key.Trim() == "") key = key1;
        string time = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss");
        SqlCommand myCommand = new SqlCommand("update xxfb set visitcount=@visitcount where MessagesId='" + key + "'", con);
        myCommand.Parameters.Add(new SqlParameter("@visitcount", SqlDbType.Int, 50));
        myCommand.Parameters["@visitcount"].Value = count;
        myCommand.Connection.Open();
        int i = (int)myCommand.ExecuteNonQuery();
        myCommand.Connection.Close();
        return i;


    }
   protected void Button1_Click(object sender, EventArgs e)
   {
        SqlConnection con = dacon.getcon();
        if (key.Trim() == ""&&Session["NewsId"] == null) return;
        if (key.Trim() == "") key = Session["NewsId"].ToString();
        string time = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss");
        SqlCommand myCommand = new SqlCommand("insert into Comment(messageId,owner,time,Con) values('" + key + "','" + Session["username"] + "','" + time + "',@Con)", con);
        myCommand.Parameters.Add(new SqlParameter("@Con", SqlDbType.NVarChar, 500));
        myCommand.Parameters["@Con"].Value = this.TextBox1.Text.ToString();
        myCommand.Connection.Open();
        int i = (int)myCommand.ExecuteNonQuery();
        myCommand.Connection.Close();
       
   }
 
}