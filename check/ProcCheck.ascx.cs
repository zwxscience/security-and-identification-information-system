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

public partial class check_ProcCheck : System.Web.UI.UserControl
{
    Datacon dacon = new Datacon();
    [DllImport("QRD.dll", CharSet = CharSet.Ansi)]
    static extern string picxdel(string fileName);
    [DllImport("QRD.dll", CharSet = CharSet.Ansi)]
    static extern int GetQRversion();
    [DllImport("QRD.dll", CharSet = CharSet.Ansi)]
    static extern char GetQRLevel();
    [DllImport("QRD.dll", CharSet = CharSet.Unicode)]
    static extern string GetQRstring();

    protected void Page_Load(object sender, EventArgs e)
    {


        if (Session["username"] == null)
        {
            Response.Write("<script>alert('用户登录超时，请重新登录。');location='../Default.aspx'</script>");

            return;
        }
        if (!IsPostBack)
        {
            Label22.Text = "";
            Label26.Text = "";
            Label25.Text = "";
            Label24.Text = "";
            Label23.Text = "";
            Label27.Text = "";

           

        }
    }
    // 转换接收到的字符串
    public string UTF8ToUnicode(string recvStr)
    {
        byte[] tempStr = Encoding.UTF8.GetBytes(recvStr);
        byte[] tempDef = Encoding.Convert(Encoding.UTF8, Encoding.Default, tempStr);
        string msgBody = Encoding.Default.GetString(tempDef);
        return msgBody;
    }
    void QRdeal(string filePath)
    {
        picxdel(filePath);
        Label22.Text = UTF8ToUnicode(GetQRstring());
        Label26.Text = GetQRLevel().ToString();
        Label25.Text = GetQRversion().ToString();


    }
    protected void DropDownList1_SelectedIndexChanged(object sender, EventArgs e)
    {

    }

    protected void Button5_Click(object sender, EventArgs e)
    {
        if (Session["username"] == null) return;
        string fullfilename = FileUpload1.PostedFile.FileName;
        if (fullfilename.Trim() == "")
        {
            Response.Write("<script>alert('文件为空，请先选择红外图像文件。')</script>");

            return;
        }
        int size = this.FileUpload1.PostedFile.ContentLength / 1024;
        if (size > 1024)
        {
            Response.Write("<script>alert('图像文件太大，请压缩到1MB以内。')</script>");

            return;
        }
        string filename = fullfilename.Substring(fullfilename.LastIndexOf("\\") + 1);
        string type = fullfilename.Substring(fullfilename.LastIndexOf(".") + 1);
        if (type == "jpg" || type == "bmp" || type == "gif" || type == "png")
        {
            //上传并重命名
            string fileN = Session["username"].ToString() + DateTime.Now.ToLongDateString() + DateTime.Now.Hour.ToString() + DateTime.Now.Minute.ToString() + DateTime.Now.Second.ToString();
           // string filename1 = fileN + "(源).bmp";//另存为
           string filename1= filename;
            string filename2 = fileN + "(识).bmp";//另存为
            string path = Server.MapPath("./") + "QRPic\\";
            try
            {
                this.FileUpload1.PostedFile.SaveAs(path + filename1);
                this.FileUpload1.PostedFile.SaveAs(path + filename2);
            }
            catch (Exception e1)
            {
                Response.Write("<script>alert('上传过程出现错误，错误信息："+e1.Message+"。')</script>");

                return; 
            }
           // string fileTName = filename.Substring(0, filename.Length - filename.Substring(filename.LastIndexOf(".") + 1).Length - 1);//无后缀
            Label24.Text = filename1;
            Label27.Text = GetUserIP();
            Label23.Text = (this.FileUpload1.PostedFile.ContentLength / 1024).ToString() + "KB";
            this.Image1.ImageUrl = "~\\check\\QRPic\\" + filename1;
            QRdeal(path + filename2);
            this.Image2.ImageUrl = "~\\check\\QRPic\\" + filename2;
            if (Label22.Text.Length > 0)
            {
                if (SQLInsert(filename1, filename2, path) == 1 && SQLQuery(Label22.Text) == 1)
                {
                    if (Label35.Text=="")
                    Label35.Text = "查询成功";
              
                }

            }

        }
        else
        {
            Response.Write("<script language='javascript'>alert('你选择的文件格式不正确！');</script>");
        }


    }
    public string GetUserIP()
    {
        string _userIP;
       
        if (Request.ServerVariables["HTTP_VIA"] == null)//无代理
        {
            _userIP = Request.UserHostAddress;
        }
        else
        {
            _userIP =Request.ServerVariables["HTTP_X_FORWARDED_FOR"];
        }
        return _userIP;
    }
    int SQLInsert(string filename1, string filename2, string path)
    {
      
        int i = 0;
        try
        {  
            Datacon dacon = new Datacon();
        SqlConnection con = dacon.getcon();
        SqlCommand myCommand = new SqlCommand("insert into checkRecord(username,filenameS,filenameC,date,QRString,QRLevel,QRVersion,path,IP)  values('" + Session["username"] + "','" + filename1 + "','" + filename2 + "','" + DateTime.Now.ToString() + "','" + Label22.Text + "','" + Label26.Text + "','" + Label25.Text + "','" + path + "','" + Label27.Text + "')", con);
        myCommand.Connection.Open();
            i = (int)myCommand.ExecuteNonQuery();
      
            myCommand.Connection.Close();     
            staticCount(filename1, Session["username"].ToString());
     
        }
        catch (Exception e)
        {
            Label35.Text = "译码结果在查询信息过程出错。错误：" + e.Message;
        }

          
        return i;

    }
    int SQLQuery(string QRString)
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


    void staticCount(string filename, string clientName)
{
           //(1)查询为单次
     int count1 = 1, count2 = 0;
          
           //获取当前费率
        string   sqlstr1 = "select top 1 * from rateSet order by id desc";
         DataSet  myds = dacon.getds(sqlstr1);
         float SI =0;
         try
         {
             SI = float.Parse(myds.Tables[0].Rows[0]["GetRate"].ToString());
             //float BI=float.Parse(myds.Tables[0].Rows[0]["BIRate"].ToString());
         }
         catch (Exception e)
         {

             Response.Write("<script language='javascript'>alert('查询费率读取错误，请检查费率设置！错误信息："+e.Message+"');</script>");
             return ;
         }
           myds.Clear();
           //(3)获取当前月份
           string month=DateTime.Now.ToString("Y");
    string sqlstr = "select * from userFees where  month='"+month+"' and  ClientName='"+clientName+"'";
     myds = dacon.getds(sqlstr);

    if (myds.Tables[0].Rows.Count > 0)//fee记录
    {
      
        count1 = int.Parse(myds.Tables[0].Rows[0]["count1"].ToString());   
        count1++;
        float Cost = float.Parse(myds.Tables[0].Rows[0]["Cost"].ToString());
      float remain = float.Parse(myds.Tables[0].Rows[0]["remain"].ToString());
        Cost = Cost+ SI;
        remain =remain+  SI; 
        string Remark = "记录被添加，更改日期：" + DateTime.Now.ToString("Y") + ",由上传文件路径为" + filename.ToString() + "的查询表所更新。";
         try
       {
        SqlConnection con = dacon.getcon();
        SqlCommand myCommand = new SqlCommand("update userFees set  count1=" + count1.ToString() + " ,Cost=" + Cost.ToString() + ",remain=" + remain.ToString() + " ,Remark='" + Remark + "' where ClientName='" + clientName+"' and month='"+month+"'", con);
        myCommand.Connection.Open();
        int i = (int)myCommand.ExecuteNonQuery();
        myCommand.Connection.Close();
         }
     catch (Exception e)
       {
               Label35.Text  = "更新费用表格时出现错误，错误：" + e.Message;
       }
    }
    else//无记录创建记录
    {
        SqlConnection con = dacon.getcon();
        string ClientName = clientName;
        string role = "查询";
       float Cost = count1 * SI;
       float pay = 0;
       float remain = Cost;
       string Remark = "本月上传查询后创建该记录，创建日期：" + DateTime.Now.ToString("Y")+",由上传文件名为"+filename+"查询操作所创建";
       try
       {
           SqlCommand myCommand = new SqlCommand("insert into userFees(ClientName,role,count1,count2,Cost,pay,remain,month,Remark,OpTime)  values('" + ClientName + "','" + role + "'," + count1 + "," + count2 + "," + Cost + "," + pay + "," + remain + ",'" + month + "','" + Remark + "','" + DateTime.Now.ToString() + "')", con);
           myCommand.Connection.Open();
           int i = (int)myCommand.ExecuteNonQuery();
           myCommand.Connection.Close();
       }
       catch (Exception e)
       {
           Label35.Text = "创建费用表格时出现错误，错误：" + e.Message;
       }

    }




}





}