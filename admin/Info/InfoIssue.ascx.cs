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
public partial class admin_InfoIssue : System.Web.UI.UserControl
{  
    Datacon dacon = new Datacon();
    protected void Page_Load(object sender, EventArgs e)
    {
       // string sc = "$(pageInit);function pageInit(){ $(pageInit); function pageInit() { $('#" + this.editor.ClientID + "').xheditor(true, { tools: 'full' }); }}";
       // Page.ClientScript.RegisterStartupScript(this.GetType(), "editor", sc, true);
      
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

        int i = this.checkInsert(caption, editor);
        if (i > 0)
        {
            str_Message = "信息发布成功。";
            Page.ClientScript.RegisterStartupScript(this.GetType(), "", "<Script>alert('" + str_Message + "');</Script>");
            this.caption.Text ="";
            this.editor.Text = "";
           // Page.RegisterStartupScript("", "<script>alert('" + str_Message + "');</script>");
           // Response.Write(str_Message);
           // Response.Redirect("Default.aspx");
            return;
        }
        else
        {
            str_Message = "信息发布失败，请重试。";
            Page.ClientScript.RegisterStartupScript(this.GetType(), "", "<Script>alert('" + str_Message + "');</Script>");
            //Page.RegisterStartupScript("", "<script>alert('" + str_Message + "');</script>");
        }

    }
    public int checkInsert(string caption, string editor)
    {
        SqlConnection con = dacon.getcon();
        string time = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss");
        //SqlCommand myCommand = new SqlCommand("INSERT INTO xxfb(MessageName, MessageContent, MessageDate) VALUES('" + caption + "','" + editor + "', '" + time + "')", con);
        string sendto="";
        if (DropDownList1.SelectedValue == "全部")
            sendto = "全部";
        else if (DropDownList1.SelectedValue == "客户")
            sendto = "客户";
        else if (DropDownList1.SelectedValue == "查询")
            sendto = "查询";
        else if (DropDownList1.SelectedValue == "特定")
            sendto = TextBox1.Text;
        int p=1;
        if(!CheckBox1.Checked) p=0;
        if (sendto == "" || DropDownList1.SelectedValue=="")
        {
            Page.ClientScript.RegisterStartupScript(this.GetType(), "", "<Script>alert('对象确定失败，请重新发布');</Script>");
            return 0;
        }
        try
        {
            SqlCommand myCommand = new SqlCommand("INSERT INTO xxfb(MessageName, MessageContent,MessageOwner, MessageDate,sendto,Comswitch) VALUES(@NewsName,@NewsContent,@MessageOwner,@NewsDate,@sendto,@Comswitch)", con);
            myCommand.Parameters.Add(new SqlParameter("@NewsName", SqlDbType.NVarChar, 50));
            myCommand.Parameters["@NewsName"].Value = caption;
            myCommand.Parameters.Add(new SqlParameter("@NewsContent", SqlDbType.Text, 30000));
            myCommand.Parameters["@NewsContent"].Value = editor;
            myCommand.Parameters.Add(new SqlParameter("@NewsDate", SqlDbType.NVarChar, 30));

            myCommand.Parameters["@NewsDate"].Value = time;
            myCommand.Parameters.Add(new SqlParameter("@MessageOwner", SqlDbType.NVarChar, 30));
            myCommand.Parameters["@MessageOwner"].Value = Session["username"].ToString();
            myCommand.Parameters.Add(new SqlParameter("@sendto", SqlDbType.NVarChar, 30));
            myCommand.Parameters["@sendto"].Value = sendto;
            myCommand.Parameters.Add(new SqlParameter("@Comswitch", SqlDbType.Int, 30));
            myCommand.Parameters["@Comswitch"].Value = p;
            myCommand.Connection.Open();
            int i = (int)myCommand.ExecuteNonQuery();
            myCommand.Connection.Close();
            return i;
        }catch(Exception e)
        {
            Page.ClientScript.RegisterStartupScript(this.GetType(), "", "<Script>alert('发布信息过程出错，请重新发布');</Script>");
            return 0;
        }
    }

 
}