
$('#userName').blur(checkUserName);
$('#userName').keyup(checkUserNameCount);
$('#passwordBox').blur(checkPassword);
$('#passwordBox').keyup(isSecurity);
$('#passwordConfirm').blur(checkPasswordConfirm);
$('#email').blur(checkEmail);
//$('#userName').focus(ShowInfo('userName_info'));
//$('#passwordBox').focus(ShowInfo('passwordBox_info'));
//$('#passwordConfirm').focus(ShowInfo('passwordConfirm_info'));
//$('#email').focus(ShowInfo('email_info'));
//$('#vcode').blur(checkVCode);
$('#comName').blur(checkComName);
$('#comName').keyup(checkComNameCount);

function ShowInfo(name){
$('#'+name).show();

}
var vcode=false;
//function checkVCode(e) {
//    var p = $('#vcode').val();
//    var info = $('#vcode').parents('.item').find('.plus');

//    $.get("VCode.ashx?code=" + p + "&_=" + Math.random(), function(data) {
//        var data = data.split('|');
//        if (data.length != 2) return true;
//        
//        if (eval(data[0])) {
//            info.find('div').show().attr('className', 'icoright');
//            info.find('span').text('');
//            return true;
//        } else {
//            info.find('div').show().attr('className', 'icoerror');
//            info.find('span').text(data[1]);
//            info.find('span').attr('className', 'h3');
//            return false;
//        }
//    });
//    if (p.length == 4) {
//        info.find('div').show().attr('className', 'icoright');
//        info.find('span').text('');
//        return true;
//    } else {
//        info.find('div').show().attr('className', 'icoerror');
//        info.find('span').text('验证码输入有误');
//        info.find('span').attr('className', 'h3');
//        return false;
//    }
//}
function checkEmail(e) {
    var p = $('#email').val();
    var info = $('#email_info');
      info.removeClass();
   if(p==""){info.html('<samp >不能为空</samp>'); info.addClass("wrong"); return false;}
    if (!/^[\w-]+[\.]*[\w-]+[@][\w\-]{1,}([.]([\w\-]{1,})){1,3}$/.test(p)) {
       info.html('<samp >Email格式有误</samp>');
       info.addClass("wrong");
        return false;
    } else {
      $.get("ajax/CheckEmail.ashx?Email=" + encodeURIComponent(p) + "&_=" + new Date().getTime(), function(data) {
      if(data!=""){
      if(data!="0"){
         info.html("<samp>此邮箱已经被注册</samp>");
                 info.addClass("wrong");
                return false;
      }else{
        info.html("恭喜,邮箱可以使用");
                 info.addClass("right");
                return true;
      }
  }
    });  
        
    }
   //   alert(info.html().toLowerCase());
       if(info.html().toLowerCase()=="<samp>此邮箱已经被注册</samp>"){
          return false;
        }
   return true;
}
function checkPassword(e) {
    var p = $('#passwordBox').val();
    var info = $('#passwordBox_info');
      info.removeClass();
     if(p==""){info.html('<samp >不能为空</samp>');  info.addClass("wrong"); return false;}
    if (p.length < 6 || p.length > 16) {
      
        info.html('<samp >请确保密码长度在6到16个字符之间</samp>');
        info.addClass("wrong");
        return false;
    } else {
    info.addClass("right");
        info.html('正确');
        return true;
    }
}
function checkPasswordConfirm(e) {

    var info = $('#passwordConfirm_info');
   info.removeClass();
    var p = $('#passwordConfirm').val();
    var q = $('#passwordBox').val();
    if (p != q) {
        info.html('<samp >两次输入密码不相同</samp>');
         info.addClass("wrong");
        return false;
    } else {
  if(p==""){info.html('<samp >不能为空</samp>');  info.addClass("wrong"); return false;}
      
      
        info.html('正确');
        info.addClass("right");
        return true;
  
    }
}
function checkUserNameCount(){
 var username = $('#userName').val().trim();
 var info = $('#userNameCount');
 info.html(username.getBytes());
}
function checkComNameCount() {
    var comname = $('#comName').val().trim();
    var info = $('#comNameCount');
    info.html(comname.getBytes());
}
function checkUserName(e) {

    var username = $('#userName').val();
    var info = $('#userName_info');
        info.show();
        info.removeClass();
    if (username == '') {
        info.html("<samp>不能为空</samp>");
        info.addClass("wrong");
        return false;
    }

    //判断用户名字符长度
    if (username.getBytes() > 20 || username.getBytes() < 4) {
       info.html('<samp >请确保用户名长度在4到20个字符之间</samp>');
        info.addClass("wrong");
        return false;
    }
    if(username.indexOf(' ')>=0)
                                {  
        info.html('<samp >确保用户名由数字、字母、中文组成</samp>');
        info.addClass("wrong");
        return false;
     }
    //判断用户名字符第一位是否是数字
    if (!isNaN(username.charAt(0))) {
        info.html('<samp >请确保用户名第一位不能为数字</samp>');
        info.addClass("wrong");
        return false;
    }
    //判断用户名由数字、字母、中文组成
    var regex = /^(\w|[\u4E00-\u9FA5])*$/;
    if (!regex.test(username)) {
        info.html('<samp >请确保用户名由数字、字母、中文组成</samp>');
        info.addClass("wrong");
        return false;
    }


    $.get("reg.ashx?username=" + encodeURIComponent(username) + "&_=" + new Date().getTime(), function (data) {
        if (data != "") {
            switch (data) {
                case "-1":
                    info.html("");
                    return false;
                case "0":
                    info.html("恭喜,此用户名可用");
                    info.addClass("right");
                    return true;
                case "-2":
                    info.html("<samp >用户名不合法，请确保用户名为2-10个中文字符或4-20个英文字符，由数组、字母、中文组成，且第一位不能为数字和不能全为数字</samp>");
                    info.addClass("wrong");
                    return false;
                default:
                    info.html("<samp >此用户名已经被注册</samp>");

                    info.addClass("wrong");
                    return false;
            }
        }
    });
    return true;
}

function checkComName(e) {

    var comname = $('#comName').val();
    var info = $('#comName_info');
    info.show();
    info.removeClass();

    //判断用户名字符长度
    if (comname.getBytes() > 20 || comname.getBytes() < 4) {
        info.html('<samp >请确保公司名长度在4到20个字符之间</samp>');
        info.addClass("wrong");
        return false;
    }
    if (comname.indexOf(' ') >= 0) {
        info.html('<samp >确保公司名由数字、字母、中文组成</samp>');
        info.addClass("wrong");
        return false;
    }
    
  
    //判断用户名由数字、字母、中文组成
    var regex = /^(\w|[\u4E00-\u9FA5])*$/;
    if (!regex.test(comname)) {
        info.html('<samp >请确保用户名由数字、字母、中文组成</samp>');
        info.addClass("wrong");
        return false;
    }


    $.get("reg.ashx?ComName=" + encodeURIComponent(comname) + "&_=" + new Date().getTime(), function (data) {
        if (data != "") {
            switch (data) {
                case "-1":
                    info.html("");
                    return false;
                case "0":
                    info.html("恭喜,此公司名未注册");
                    info.addClass("right");
                    return true;
                case "-2":
                    info.html("<samp >公司名名不合法，请确保公司名为2-10个中文字符或4-20个英文字符，由数组、字母、中文组成，且第一位不能为数字和不能全为数字</samp>");
                    info.addClass("wrong");
                    return false;
                default:
                    info.html("<samp >此公司名已经被注册</samp>");

                    info.addClass("wrong");
                    return false;
            } 
        }
    });
    return true;
}

function onSubmit() {
$("em[id$='info']").show();
    var vlist = [checkUserName, checkPassword, checkPasswordConfirm,checkComName, checkEmail];
    var returnValue = true;
    for (var i = 0; i < vlist.length; i++) {
        if (!vlist[i]()) {
            returnValue = false; //alert("未通过" + i); 
        }
    }
    if(!$("#cbpro").attr("checked")){
        alert("必须接受信息系统网站协议才可以注册账户");
        return false;
    }
    if (!returnValue) {
      alert("未通过");
        return returnValue;
    }else {
       

       var Regionalism = $('#DropDownList3').val();
       var role = $('#ListBox1').val();
        var username = $('#userName').val();
       //  alert("通过"+role);
        var password = $('#passwordBox').val();
        //var number = $('#username').val();
        var ComName = $('#comName').val();
        var ComAddress = $('#comAddress').val();
        var ComTel = $('#comTel').val();
        var ComNet = $('#comNet').val();
        var ComEmail = $('#email').val();
        var info = $('#userName_info');

        $.get("reg.ashx?Regionalism=" + encodeURIComponent(Regionalism) + "&role=" + encodeURIComponent(role) + "&username=" +
        encodeURIComponent(username) + "&password=" + encodeURIComponent(password) + "&ComName=" + encodeURIComponent(ComName) + "&ComAddress=" +
         encodeURIComponent(ComAddress) + "&ComTel=" + encodeURIComponent(ComTel) + "&ComNet=" + encodeURIComponent(ComNet) + "&ComEmail=" +
          encodeURIComponent(ComEmail), function (data) {
              if (data!=1){
                  info.html("<samp >返回值为空，无法注册</samp>");
                  info.addClass("wrong");
                   return false;
                 }else{

                              window.parent.parent.location.href = 'RegC.aspx';
                              return true;
                          }
                  
             
          });
    }

}

//删除字符串左右空格
String.prototype.trim = function() {
    return this.replace(/^\s+|\s+$/g, "");
}
//字符串获取字节数
String.prototype.getBytes = function() {
    var bytes = 0;
    for (var i = 0; i < this.length; i++) {
        if (this.charCodeAt(i) > 256) { bytes += 2; }
        else { bytes += 1; }
    }
    return bytes;
}


 function isSecurity() {
         var v=$("#passwordBox").val();

            if (v.length < 6) { iss.reset(); return; }
            var lv = -1;
            if (v.match(/[a-z]/ig)) { lv++; }
            if (v.match(/[0-9]/ig)) { lv++; }
            if (v.match(/(.[^a-z0-9])/ig)) { lv++; }
            if (v.length < 6 && lv > 0) { lv--; }
            iss.reset();
            switch (lv) {
                case 0:
                    iss.level0();
                    break;
                case 1:
                    iss.level1();
                    break;
                case 2:
                    iss.level2();
                    break;
                default:
                    iss.reset();
            }
        }
        var iss = {

            reset: function() {
            $('#Safety').removeClass();
                $('#Safety').addClass("i");
              
            },
            level0: function() {
                $('#Safety').removeClass();
                $('#Safety').addClass("i1");
              
            },
            level1: function() {
               $('#Safety').removeClass();
                $('#Safety').addClass( "i2");
               
            },
            level2: function() {
             $('#Safety').removeClass();
                $('#Safety').addClass("i3");
               

            }
        }
        
        
//function Check(s){

//if(s=="1"){
//vcode=true;
//}
//checkCode();
//return vcode;

//}

//function  checkCode(){
//ShowInfo('vcode_info');
// var info = $('#vcode_info');
//      info.removeClass();
//if(vcode){  info.html('正确');    info.addClass("right");}else{ info.html('<samp>验证码错误</samp>');    info.addClass("wrong");}
//return vcode;
//}
