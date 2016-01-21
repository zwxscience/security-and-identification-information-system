<%@ WebHandler Language="C#" Class="upload" %>

using System;
using System.Web;

using System.Configuration;

public class upload : IHttpHandler
{

    public void ProcessRequest(HttpContext context)
    {
        context.Response.ContentType = "text/plain";
        //context.Response.Write("Hello World");

        savefile(context);
    }
    private void savefile(HttpContext context)
    {
        context.Response.ClearHeaders();
        context.Response.Clear();
        context.Response.Expires = 0;
        context.Response.ClearContent();
        context.Response.Charset = "UTF-8";
        // 初始化一大堆变量
        string inputname = "filedata";//表单文件域name
        string attachdir = "../../admin/Info/upload";     // 上传文件保存路径，结尾不要带/
        int dirtype = 1;                 // 1:按天存入目录 2:按月存入目录 3:按扩展名存目录  建议使用按天存
        int maxattachsize = 2097152;     // 最大上传大小，默认是2M
        string upext = "txt,rar,zip,jpg,jpeg,gif,png,swf,wmv,avi,wma,mp3,mid";    // 上传扩展名
        string immediate = context.Request.QueryString["id"];//立即上传模式，仅为演示用
        if (immediate == null) return;//没有获得值
        if (immediate != null && immediate.Equals("1"))
        {//文件
            attachdir += "/files";

        }
        if (immediate != null && immediate.Equals("2"))
        {//图片
            attachdir += "/images";

        }
        if (immediate != null && immediate.Equals("3"))
        {//flash
            attachdir += "/flashes";

        }
        if (immediate != null && immediate.Equals("4"))
        {//视频
            attachdir += "/media";

        }
        Data d = new Data();
        byte[] file;                     // 统一转换为byte数组处理
        string localname = "";
        string disposition = context.Request.ServerVariables["HTTP_CONTENT_DISPOSITION"];
        string err = "";

        if (disposition != null)
        {
            // HTML5上传
            file = context.Request.BinaryRead(context.Request.TotalBytes);
            localname = System.Text.RegularExpressions.Regex.Match(disposition, "filename=\"(.+?)\"").Groups[1].Value;// 读取原始文件名
        }
        else
        {
            HttpFileCollection filecollection = context.Request.Files;
            HttpPostedFile postedfile = filecollection.Get(inputname);
            // 读取原始文件名
            localname = postedfile.FileName;
            // 初始化byte长度.
            file = new Byte[postedfile.ContentLength];
            // 转换为byte类型
            System.IO.Stream stream = postedfile.InputStream;
            stream.Read(file, 0, postedfile.ContentLength);
            stream.Close();

            filecollection = null;
        }
        if (file.Length == 0) err = "无数据提交";
        else
        {
            if (file.Length > maxattachsize) err = "文件大小超过" + maxattachsize + "字节";
            else
            {
                string attach_dir, attach_subdir, filename, extension, target;

                // 取上载文件后缀名
                extension = GetFileExt(localname);
                if (("," + upext + ",").IndexOf("," + extension + ",") < 0) err = "上传文件扩展名必需为：" + upext;
                else
                {
                    switch (dirtype)
                    {
                        case 2:
                            attach_subdir = "month_" + DateTime.Now.ToString("yyMM");
                            break;
                        case 3:
                            attach_subdir = "ext_" + extension;
                            break;
                        default:
                            attach_subdir = "day_" + DateTime.Now.ToString("yyMMdd");
                            break;
                    }
                    attach_dir = attachdir + "/" + attach_subdir + "/";
                    // 生成随机文件名
                    Random random = new Random(DateTime.Now.Millisecond);
                    filename = DateTime.Now.ToString("yyyyMMddhhmmss") + random.Next(10000) + "." + extension;
                    target = attach_dir + filename;
                    d.msg = target;
                    try
                    {
                        CreateFolder(context.Server.MapPath(attach_dir));
                        System.IO.FileStream fs = new System.IO.FileStream(context.Server.MapPath(target), System.IO.FileMode.Create, System.IO.FileAccess.Write);
                        fs.Write(file, 0, file.Length);
                        fs.Flush();
                        fs.Close();
                    }
                    catch (Exception ex)
                    {
                        err = ex.Message.ToString();
                    }

                }

            }
        }

        //try
        //{
        //    if (context.Request.Files.Count > 0)
        //    {
        //        var file = context.Request.Files[0];
        //        string filename = context.Request.Files[0].FileName.Substring(context.Request.Files[0].FileName.LastIndexOf("\\") + 1);
        //        string path = context.Server.MapPath("images\\" + filename);
        //        d.msg = "images/" + filename;
        //        file.SaveAs(path);
        //    }
        //}
        //catch (Exception e)
        //{
        //    d.err = e.Message;
        //}
//.net 3.5以上
       // JavaScriptSerializer serializer = new JavaScriptSerializer();
       // context.Response.Write(serializer.Serialize(d));
 //。net2.0需要自己构造json
        string js="{\"err\":\""+d.err+"\",\"msg\":\""+d.msg+"\"}";
        context.Response.Write(js);
        context.Response.Flush();
        context.Response.End();
    }



    string GetFileExt(string FullPath)
    {
        if (FullPath != "") return FullPath.Substring(FullPath.LastIndexOf('.') + 1).ToLower();
        else return "";
    }

    void CreateFolder(string FolderPath)
    {
        if (!System.IO.Directory.Exists(FolderPath)) System.IO.Directory.CreateDirectory(FolderPath);
    }


    public bool IsReusable
    {
        get
        {
            return false;
        }
    }

    public class Data
    {
        private string _err;
        private string _msg;
        public string err
        {
            get
            {
                if (_err == null)
                    return string.Empty;
                return _err;
            }
            set
            {
                _err = value;
            }
        }
        public string msg
        {
            get
            {
                if (_msg == null)
                    return string.Empty;
                return _msg;
            }
            set
            {
                _msg = value;
            }
        }
    }

}