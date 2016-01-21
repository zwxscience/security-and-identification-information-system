﻿<%@ WebHandler Language="C#" Class="login" %>

using System;
using System.Web;
using System.Web.SessionState;
using System.Drawing;
using System.Drawing.Imaging;
using System.Drawing.Drawing2D;
public class login : IHttpHandler, System.Web.SessionState.IRequiresSessionState
{
    
    public void ProcessRequest (HttpContext context) {
        context.Response.ContentType = "text/plain";
        CreateCheckCodeImage(GenerateCheckCode(context), context);
        //context.Response.Write("Hello World");
    }
     /// <summary>
    /// 生成随机字符串
    /// </summary>
    /// <returns></returns>
    private string GenerateCheckCode(HttpContext context)
    {
        //  PageUtils.VerifyCode = checkCode.ToLower();


        //自定义自己验证码需要显示的字符
        //如果仅仅是数字和26个字母，您可以写一个循环遍历
        char[] myCodeChar = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
        int number;
        char code;
        string checkCode = string.Empty;


        //使用随机函数，产生一个随机数
        System.Random random = new Random();
        for (int i = 0; i < 4; i++)
        {
            number = random.Next(myCodeChar.Length);

            code = (char)(myCodeChar[number]);

            checkCode += code.ToString();
        }
     //   Session["ValidateCode"].
        context.Session["checkCode"] = checkCode.ToLower();//把生成的验证码存入session
        if (context.Session["checkCode"].ToString().Trim() == null)
        {
           context.Response.Redirect("Login.aspx");
        }
        return checkCode;
    }

    /// <summary>
    /// 生成验证码图片，并输出
    /// </summary>
    /// <param name="checkCode"></param>
    private void CreateCheckCodeImage(string checkCode, HttpContext context)
    {
        if (checkCode == null || checkCode.Trim() == String.Empty) return;

        Matrix m = new Matrix();//定义几何变换
        Bitmap charbmp = new Bitmap(90, 30);//图片前景色，即生成背景透明的随机字符串图片

        //定义字体
        Font[] fonts = {
                                       new Font(new FontFamily("Times New Roman"), 17, FontStyle.Regular),
                                       new Font(new FontFamily("Georgia"), 17, FontStyle.Regular),
                                       new Font(new FontFamily("Arial"), 17, FontStyle.Regular),
                                       new Font(new FontFamily("Comic Sans MS"), 17, FontStyle.Regular)
                                    };


        //定义图片背景色
        System.Drawing.Bitmap image = new System.Drawing.Bitmap((int)Math.Ceiling((checkCode.Length * 22.5)), 30);

        //开始描绘
        Graphics g = Graphics.FromImage(image);

        g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.HighSpeed;

        //定义背景色为白色
        g.Clear(Color.White);
        try
        {
            Random random = new Random();       //生成随机生成器
            g.Clear(Color.White);               //清空图片背景色
            for (int i = 0; i < 2; i++)              //画图片的背景噪音线，i表示画多少条噪音线
            {
                int x1 = random.Next(image.Width);
                int x2 = random.Next(image.Width);
                int y1 = random.Next(image.Height);
                int y2 = random.Next(image.Height);
                g.DrawLine(new Pen(Color.Black), x1, y1, x2, y2);
            }



            //开始描绘前景图
            Graphics charg = Graphics.FromImage(charbmp);

            SolidBrush drawBrush = new SolidBrush(Color.FromArgb(random.Next(101), random.Next(101), random.Next(101)));
            float charx = -18;

            //把随机字符串，逐个写入前景图
            for (int i = 0; i < checkCode.Length; i++)
            {
                m.Reset();
                m.RotateAt(random.Next(31) - 25, new PointF(random.Next(4) + 7, random.Next(4) + 7));

                charg.Clear(Color.Transparent);//定义前景图为透明
                charg.Transform = m;
                //定义前景色为黑色
                drawBrush.Color = Color.Black;

                charx = charx + 20 + random.Next(3);
                PointF drawPoint = new PointF(charx, 0.1F);
                charg.DrawString(checkCode[i].ToString(), fonts[random.Next(fonts.Length)], drawBrush, new PointF(0, 0));//通过特定的几何变换，旋转或变形随机字符，写入前景图

                charg.ResetTransform();

                g.DrawImage(charbmp, drawPoint);
            }


            //画图片的前景噪音点
            for (int i = 0; i < 25; i++)
            {
                int x = random.Next(image.Width);
                int y = random.Next(image.Height);

                image.SetPixel(x, y, Color.FromArgb(random.Next()));
            }

            //画图片的边框线
            g.DrawRectangle(new Pen(Color.Silver), 0, 0, image.Width - 1, image.Height - 1);

            //输出
            System.IO.MemoryStream ms = new System.IO.MemoryStream();
            image.Save(ms, System.Drawing.Imaging.ImageFormat.Gif);
            context.Response.ClearContent();
            context.Response.ContentType = "image/Gif";
            context.Response.BinaryWrite(ms.ToArray());
        }
        finally
        {
            g.Dispose();
            image.Dispose();
        }
    }
    public bool IsReusable {
        get {
            return true;
        }
    }

}