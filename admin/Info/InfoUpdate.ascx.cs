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
public partial class Infoup : System.Web.UI.UserControl
{  
    Datacon dacon = new Datacon();
    string key = "";
    int checkUpdate(string caption, string editor)
    {
        string sendto = "";
        if (DropDownList1.SelectedValue == "全部")
            sendto = "全部";
        else if (DropDownList1.SelectedValue == "客户")
            sendto = "客户";
        else if (DropDownList1.SelectedValue == "查询")
            sendto = "查询";
        else if (DropDownList1.SelectedValue == "特定")
            sendto = TextBox1.Text;
        int p = 1;
        if (!CheckBox1.Checked) p = 0;
        if (sendto == "")
        {
            Page.ClientScript.RegisterStartupScript(this.GetType(), "", "<Script>alert('对象确定失败，请重新发布');</Script>");
        }
        
            SqlConnection con = dacon.getcon();
            if (key == "") key = Session["NewsId"].ToString();
            string time = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss");
            SqlCommand myCommand = new SqlCommand("update xxfb set MessageName=@NewsName,MessageContent=@NewsContent,MessageDate=@NewsDate,sendto=@sendto,Comswitch=@Comswitch where MessagesId='" + key + "'", con);
            myCommand.Parameters.Add(new SqlParameter("@NewsName", SqlDbType.NVarChar, 50));
            myCommand.Parameters["@NewsName"].Value = caption;
            myCommand.Parameters.Add(new SqlParameter("@NewsContent", SqlDbType.Text, 30000));
            myCommand.Parameters["@NewsContent"].Value = editor;
            myCommand.Parameters.Add(new SqlParameter("@NewsDate", SqlDbType.NVarChar, 30));
            myCommand.Parameters["@NewsDate"].Value = time;

            myCommand.Parameters.Add(new SqlParameter("@sendto", SqlDbType.NVarChar, 30));
            myCommand.Parameters["@sendto"].Value = sendto;
            myCommand.Parameters.Add(new SqlParameter("@Comswitch", SqlDbType.Int, 30));
            myCommand.Parameters["@Comswitch"].Value = p; 
            myCommand.Connection.Open();
            int i = (int)myCommand.ExecuteNonQuery();
            myCommand.Connection.Close();
            return i;
        

    }
    protected void Page_Load(object sender, EventArgs e)
    {

        if (!IsPostBack)
        {
           
            if (Request.QueryString["NewsId"] != null)
            {
                Datacon dacon = new Datacon();
                key = Request.QueryString["NewsId"].ToString();
                Session["NewsId"] = key;
                StringBuilder items = new StringBuilder();
                string sqlstr = "SELECT  MessageName,MessageContent  FROM xxfb WHERE (MessagesId = '" + key + "')";
                DataSet ds = dacon.getds(sqlstr);
                for (int i = 0; i < ds.Tables[0].Rows.Count; i++)
                {//历遍所有的
                    if (ds.Tables[0].Rows[i]["MessageName"].ToString() != "")
                        this.caption.Text = ds.Tables[0].Rows[i]["MessageName"].ToString();
                    if(ds.Tables[0].Rows[i]["MessageContent"].ToString() != "")
                        this.editor.Text = ds.Tables[0].Rows[i]["MessageContent"].ToString();

                }
                     
                }
            else
                Response.Redirect("InfoOp.aspx");
               
            }
           
        }


    protected void btnis_Click(object sender, EventArgs e)
    {

        string caption = this.caption.Text.ToString().Trim();
        string editor = this.editor.Text.ToString().Trim();
        string str_Message;
        if (caption.Length <= 0)
        {
            str_Message = "标题不能为空，请输入标题。";
            Page.ClientScript.RegisterStartupScript(this.GetType(), "", "<Script>alert('" + str_Message + "');</Script>");
         // Page.RegisterStartupScript("", "<script>alert('" + str_Message + "');</script>");
            return;
        }
        if (caption.Length >50)
        {
            str_Message = "标题不能太长，请保持在五十个字符内。";
            Page.ClientScript.RegisterStartupScript(this.GetType(), "", "<Script>alert('" + str_Message + "');</Script>");
            //Page.RegisterStartupScript("", "<script>alert('" + str_Message + "');</script>");
            return;
        }

        if (editor.Length <= 0)
        {
            str_Message = "内容不能为空，请输入内容。";
            Page.ClientScript.RegisterStartupScript(this.GetType(), "", "<Script>alert('" + str_Message + "');</Script>");
          //  Page.RegisterStartupScript("", "<script>alert('" + str_Message + "');</script>");
            return;
        }
        if (editor.Length > 30000)
        {
            str_Message = "内容不能太长，请保持在3w个字符内。";
            Page.ClientScript.RegisterStartupScript(this.GetType(), "", "<Script>alert('" + str_Message + "');</Script>");
           // Page.RegisterStartupScript("", "<script>alert('" + str_Message + "');</script>");
            return;
        }

        int i = this.checkUpdate(caption, editor);
        if (i > 0)
        {

                Page.ClientScript.RegisterStartupScript(this.GetType(), "", "<Script>alert('更新信息成功');window.location.href('InfoOp.aspx')</Script>"); 
            
            return;
        }
        else
        {
           
            Page.ClientScript.RegisterStartupScript(this.GetType(), "", "<Script>alert('更新信息失败');window.location.href('InfoOp.aspx')</Script>");
            return;
        }

    }
   

}