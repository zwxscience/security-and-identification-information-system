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

public partial class QueryPage : System.Web.UI.MasterPage
{
    Datacon dacon = new Datacon();
    protected void Page_Load(object sender, EventArgs e)
    { 

          if (null == Session["username"]||!Session["role"].ToString().Equals("客户"))
          {
              Response.Write("<script>alert('用户登录超时，请重新登录。');location='../../Login.aspx'</script>");

                return;
           }
        string userid=Session["username"].ToString();
      //  测试账号：zwxscience
         // string userid = "zwxscience";
        user.Text = userid;
        return;



    }
    protected void loginout_Click(object sender, EventArgs e)
    {

        Response.Write("<script>  if(confirm('确认退出吗？')) { location.href='../../Login.aspx'; } </script>");
        Session.Clear();
    }
  
}
