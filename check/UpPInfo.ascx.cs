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
using System.Runtime.InteropServices;
using System.Text;
using System.Data.SqlClient;

public partial class check_UpPInfo : System.Web.UI.UserControl
{
    Datacon dacon = new Datacon();


    protected void Page_Load(object sender, EventArgs e)
    {

        
                if (Session["username"] == null)
        {
            Response.Write("<script>alert('用户登录超时，请重新登录。');location='../Default.aspx'</script>"); 

            return;
        }
        if (!IsPostBack)
        {
           if(Request.QueryString["id"]!=null)
           {
               int id= int.Parse( Request.QueryString["id"].ToString());
               SQLQuery(id);

           }


           

        }
    }
    // 转换接收到的字符串
    
   
int SQLQuery(int  id )
{

    string sqlstr = "select * from checkRecord where id=" + id + "  and username='"+Session["username"]+"'";
            DataSet myds = dacon.getds(sqlstr);
            if (myds.Tables[0].Rows.Count>=1)
            {
                Image1.ImageUrl = "~\\check\\QRPic\\" + myds.Tables[0].Rows[0]["filenameS"].ToString();
                Image2.ImageUrl = "~\\check\\QRPic\\" + myds.Tables[0].Rows[0]["filenameC"].ToString();
                Label24.Text = myds.Tables[0].Rows[0]["fileNameS"].ToString();
                Label23.Text = myds.Tables[0].Rows[0]["date"].ToString();
                Label36.Text = myds.Tables[0].Rows[0]["IP"].ToString();
                if (Label36.Text == "") Label36.Text = "暂无查询端IP信息";
                Label22.Text = myds.Tables[0].Rows[0]["QRString"].ToString();
                Label25.Text = myds.Tables[0].Rows[0]["QRVersion"].ToString();
                Label26.Text = myds.Tables[0].Rows[0]["QRLevel"].ToString();
                if (Label22.Text != "" && SQLQuery2(Label22.Text)==1)
                    Label35.Text = "查询成功。";
                else
                    Label35.Text = "查询过程出现错误。";

                    return 1;
            } return 0;

}
int SQLQuery2(string QRString)
{

    string sqlstr = "select * from proApply where code='" + QRString + "' and AllocFlag=4";
    DataSet myds = dacon.getds(sqlstr);


    if (myds.Tables[0].Rows.Count >= 1)
    {

        Lyz_mc1.Text = myds.Tables[0].Rows[0]["code"].ToString();
        Lyz_mc2.Text = myds.Tables[0].Rows[0]["codesize"].ToString();
        Lyz_mc0.Text = myds.Tables[0].Rows[0]["productName"].ToString();
        Lyz_zt1.Text = myds.Tables[0].Rows[0]["productDate"].ToString();
        Lyz_lx1.Text = myds.Tables[0].Rows[0]["printDate"].ToString();
        Label2.Text = myds.Tables[0].Rows[0]["QCman"].ToString();
        Label4.Text = myds.Tables[0].Rows[0]["lotNumber"].ToString();
        Label6.Text = myds.Tables[0].Rows[0]["productCapacity"].ToString();
        Label8.Text = myds.Tables[0].Rows[0]["totalNumber"].ToString();
        Label3.Text = myds.Tables[0].Rows[0]["receiver"].ToString();
        Label5.Text = myds.Tables[0].Rows[0]["storageLocation"].ToString();
        Label7.Text = myds.Tables[0].Rows[0]["guaranteeRange"].ToString();
        Label9.Text = myds.Tables[0].Rows[0]["DesName"].ToString();
        TextBox12.Text = myds.Tables[0].Rows[0]["remark"].ToString();
        Label34.Text = myds.Tables[0].Rows[0]["Applydate"].ToString();
        string state = "";
        int i = (int)myds.Tables[0].Rows[0]["AllocFlag"];
        switch (i)
        {
            case 0:
                state = "已经保存";
                break;
            case 1:
                state = "已经提交（未受理）";
                break;
            case 2:
                state = "受理未通过";
                break;
            case 3:
                state = "受理通过";
                break;
            case 4:
                state = "通过并生成二维码图像";
                break;
        }

        Label32.Text = state;
        return 1;
    } return 0;

}

}
