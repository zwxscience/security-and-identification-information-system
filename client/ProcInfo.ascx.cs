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
using System.Drawing;
using Gma.QrCodeNet.Encoding;
using System.Drawing.Drawing2D;
public partial class client_ProcInfo : System.Web.UI.UserControl
{
    Datacon dacon = new Datacon();
   
    protected void Page_Load(object sender, EventArgs e)
    {
       
            
            string id=Request.QueryString["id"].ToString();
            if (id == "") id = Session["id"].ToString();
            else Session["id"]=id;
            string sqlstr = "select * from proApply where id=" + id;
            DataSet myds = dacon.getds(sqlstr);
            if (myds.Tables[0].Rows.Count >0)
            {
                Lyz_mc1.Text =  myds.Tables[0].Rows[0]["code"].ToString();
                Lyz_mc2.Text =  myds.Tables[0].Rows[0]["codesize"].ToString();
                Lyz_mc0.Text  =myds.Tables[0].Rows[0]["productName"].ToString();
                Lyz_zt1.Text =  myds.Tables[0].Rows[0]["productDate"].ToString();
                Lyz_lx1.Text = myds.Tables[0].Rows[0]["printDate"].ToString();
                Label2.Text =  myds.Tables[0].Rows[0]["QCman"].ToString();

                Label4.Text =myds.Tables[0].Rows[0]["lotNumber"].ToString();
                Label6.Text =  myds.Tables[0].Rows[0]["productCapacity"].ToString();
                Label8.Text =  myds.Tables[0].Rows[0]["totalNumber"].ToString();
                Label3.Text =  myds.Tables[0].Rows[0]["receiver"].ToString();
                Label5.Text =myds.Tables[0].Rows[0]["storageLocation"].ToString();
                Label7.Text =  myds.Tables[0].Rows[0]["guaranteeRange"].ToString();
                Label9.Text =  myds.Tables[0].Rows[0]["DesName"].ToString();
                TextBox12.Text =  myds.Tables[0].Rows[0]["remark"].ToString();
                if (TextBox12.Text.Trim() == "") TextBox12.Visible = false;
                Label21.Text = myds.Tables[0].Rows[0]["Applydate"].ToString();
                spyj.Text = myds.Tables[0].Rows[0]["Suggest"].ToString().Trim();
                if (spyj.Text == "")
                {
                    spyj.Visible = false;
                    Label40.Visible = false;
                }
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
         Label22.Text = state;
         if (i == 0)//0保存1提交2未反馈3反馈4图像
         {
             Button1.Visible = true;
           
         }
         if (i == 3)//0保存1提交2未反馈3反馈4图像
         {
             Button2.Visible = true;

         }

            if(i==4)
            {
            Image1.Visible=true;
            Button4.Visible = true;
            this.Image1.ImageUrl = "~\\client\\ApplyPic\\" + Session["id"].ToString().Trim() + ".bmp"; 
            }
            }
        else Page.ClientScript.RegisterStartupScript(this.GetType(), "", "<Script>alert('读取信息失败');</Script>");
    }

    protected void DropDownList1_SelectedIndexChanged(object sender, EventArgs e)
    {

    }
protected void  Button1_Click(object sender, EventArgs e)
{
      SqlConnection con = dacon.getcon();
      SqlCommand myCommand = new SqlCommand("update proApply set  AllocFlag=1,PLflag=0 where id=" + Session["id"] , con);//转为提交状态
        myCommand.Connection.Open();
        int i = (int)myCommand.ExecuteNonQuery();
        myCommand.Connection.Close();

        if (i < 1)
        {
             string str_Message = "申请信息提交失败。";
            Page.ClientScript.RegisterStartupScript(this.GetType(), "", "<Script>alert('" + str_Message + "');</Script>");
           
            return;
        }else
        {
              string str_Message = "申请信息提交成功。";

            Page.ClientScript.RegisterStartupScript(this.GetType(), "", "<Script>alert('" + str_Message + "');</Script>");
            //Page.RegisterStartupScript("", "<script>alert('" + str_Message + "');</script>");
            Response.Redirect("ProcInfo.aspx?id=" + Session["id"]);
            return;
        }

}
protected void Button2_Click(object sender, EventArgs e)
{
    if (Session["id"]== null||Lyz_mc1.Text=="")
    {
        Label23.Text = "获取信息ID失败，无法生成图片。请刷新页面。";
        return;
    }
    string code = Lyz_mc1.Text.Trim();
    string path = Server.MapPath("./") + "ApplyPic\\";
    string FileName =path+ Session["id"].ToString().Trim()+".bmp";

    string codesize = Lyz_mc2.Text.Trim();
    string size = codesize.Substring(codesize.LastIndexOf("*") + 1);
    int cm = int.Parse(size);
    QrEncoder qrEncoder = new QrEncoder(ErrorCorrectionLevel.H);
    QrCode qrCode = new QrCode();
    qrEncoder.TryEncode(code, out qrCode);
    writeToFile(qrCode.Matrix, System.Drawing.Imaging.ImageFormat.Bmp, FileName, cm);

    Label23.Text = "QR图像生成成功";
    //下面修改信息
    SqlConnection con = dacon.getcon();
    SqlCommand myCommand = new SqlCommand("update proApply set  AllocFlag=4 where id='" + Session["id"] + "' ", con);//转为已经生成状态
    myCommand.Connection.Open();
    int i = (int)myCommand.ExecuteNonQuery();
    myCommand.Connection.Close();

    if (i < 1)
    {
        string str_Message = "转为已经生成状态失败。";
        Page.ClientScript.RegisterStartupScript(this.GetType(), "", "<Script>alert('" + str_Message + "');</Script>");
        //Page.RegisterStartupScript("", "<script>alert('" + str_Message + "');</script>");
        return;
    }
    else
    {
        string str_Message = "转为已经生成状态成功。";
        this.Image1.ImageUrl = "~\\client\\ApplyPic\\" + Session["id"].ToString().Trim() + ".bmp"; 
        Page.ClientScript.RegisterStartupScript(this.GetType(), "", "<Script>alert('" + str_Message + "');</Script>");
        Response.Redirect("ProcInfo.aspx?id=" + Session["id"]);
        //Page.RegisterStartupScript("", "<script>alert('" + str_Message + "');</script>");
        return;
    }

}

public static Bitmap toBitmap(BitMatrix matrix, int width, int height)
{
    // int width = matrix.Width;
    // int height = matrix.Height;
    Bitmap bmap = new Bitmap(width, height, System.Drawing.Imaging.PixelFormat.Format32bppArgb);
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            bmap.SetPixel(x, y, matrix[x * matrix.Width / width, y * matrix.Height / height] != false ? ColorTranslator.FromHtml("0xFF000000") : ColorTranslator.FromHtml("0xFFFFFFFF"));
        }
    }
    return bmap;
} 
     
    public static void writeToFile(BitMatrix matrix, System.Drawing.Imaging.ImageFormat format, string file,int cm)
    {
        Bitmap bmap = toBitmap(matrix,matrix.Width,matrix.Height);
        //图像分辨率
        float dpiX = bmap.HorizontalResolution;
        float dpiY = bmap.VerticalResolution;
        double newW =cm * dpiX * 10/25.4;//cm转化为像素数
        double newH=cm*dpiY*10/25.4;
        bmap = toBitmap(matrix,(int)newW,(int)newH);
        bmap.Save(file, format);
    }
    protected void Button4_Click(object sender, EventArgs e)
    {
        if (Session["id"]== null||Lyz_mc1.Text=="")
    {
        Label23.Text = "获取信息ID失败，无法生成图片。请刷新页面。";
        return;
    }
    string code = Lyz_mc1.Text.Trim();
         string fileName=code+".bmp";
        Response.ContentType = "image/bmp";
        string path = Server.MapPath("./") + "ApplyPic\\";
        string FileName = path + Session["id"].ToString().Trim() + ".bmp";
Response.AppendHeader("Content-Disposition","attachment;filename="+fileName);
Response.TransmitFile(FileName);
    }
}