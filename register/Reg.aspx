<%@ Page Language="C#" AutoEventWireup="true" CodeFile="Reg.aspx.cs" Inherits="Login" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
<title>防伪识别信息系统</title>
<link href="../CSS/regStyle.css" rel="stylesheet" type="text/css" />
<link href="../CSS/Nstyles.css" rel="stylesheet" type="text/css" />
<script type="text/javascript" src="../JS/jquery-1.3.1.js"></script>


    <script  language="javascript" type="text/javascript" >

</script>

</head>
<body scroll= "yes">
<div id="header">

<h1 style="font-family: 隶书; left: 1.7em; height:60px; margin-top: 17px; ">
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; 防伪识别信息系统</h1>

</div>
    <form id="form1" runat="server">




<table width="100%" border="0" align="center" cellspacing="35" cellpadding="0"  class="login-table" >
<tr>
<td valign="top" class="right" style="width: 365px; height: 238px;">
<div class="title-n">
用户注册
</div>
<br />


<div class="reg">
<div class="regbox">
<div class="ld">
</div>
<div class="rd">
</div>
<h1>
</h1>
<ul>
<li >
<span>地区信息：</span>




   <asp:DropDownList ID="DropDownList1" runat="server" 
        DataSourceID="SqlDataSource1" DataTextField="ProvinceName" 
        DataValueField="ProvinceID" AutoPostBack="True" ToolTip="请选择注册地所在省份">
    </asp:DropDownList>
    <asp:SqlDataSource ID="SqlDataSource1" runat="server" 
        ConnectionString="<%$ ConnectionStrings:sealConnectionString %>" 
        SelectCommand="SELECT * FROM [RegionalismProvinceCode]"></asp:SqlDataSource> 

     <asp:DropDownList ID="DropDownList2" runat="server" 
        DataSourceID="SqlDataSource2" DataTextField="CityName" 
        DataValueField="CityID" AutoPostBack="True" ToolTip="请选择注册地所在市">
    </asp:DropDownList>
     <asp:SqlDataSource ID="SqlDataSource2" runat="server" 
        ConnectionString="<%$ ConnectionStrings:sealConnectionString %>" 
        SelectCommand="SELECT * FROM [RegionalismCityCode] WHERE ([ProvinceID] = @ProvinceID)">
         <SelectParameters>
             <asp:ControlParameter ControlID="DropDownList1" Name="ProvinceID" 
                 PropertyName="SelectedValue" Type="String" />
         </SelectParameters>
    </asp:SqlDataSource>
     <asp:DropDownList ID="DropDownList3" runat="server" 
        DataSourceID="SqlDataSource3" DataTextField="RegionalismName" 
        DataValueField="RegionalismID" AutoPostBack="True" ToolTip="请选择注册地所在区县">
    </asp:DropDownList>
    <asp:SqlDataSource ID="SqlDataSource3" runat="server" 
        ConnectionString="<%$ ConnectionStrings:sealConnectionString %>" 
        SelectCommand="SELECT * FROM [RegionalismCode] WHERE ([CityID] = @CityID)">
        <SelectParameters>
            <asp:ControlParameter ControlID="DropDownList2" Name="CityID" 
                PropertyName="SelectedValue" Type="String" />
        </SelectParameters>
    </asp:SqlDataSource> 
  </li>
  <li><span>选择帐号类型：</span>
      <asp:ListBox ID="ListBox1" runat="server" Height="36px">
          <asp:ListItem Selected="True" Value="客户">客户端用户</asp:ListItem>
          <asp:ListItem Value="查询">查询端用户</asp:ListItem>
      </asp:ListBox>
 
</li>
<li><span>您的帐号：</span>
<input name="userName" type="text" id="userName" onfocus="ShowInfo(&#39;userName_info&#39;)"
maxlength="50" />
<em id="userName_info" style="display: none" class="wrong">
<samp>
不能为空</samp></em><b>已输入
<label id="userNameCount">
0</label>
个字符</b></li>

<li><span>设置帐号密码：</span>
<input name="passwordBox" type="password" id="passwordBox" onfocus="ShowInfo(&#39;passwordBox_info&#39;)"
maxlength="40"/>
<em id="passwordBox_info" style="display: none" class="wrong">
<samp>
不能为空</samp></em>
 <b>密码强度：弱
 <i class="i" id="Safety">
 </i>强
 </b></li>
<li><span>再输一次密码：</span>
<input name="passwordConfirm" type="password" id="passwordConfirm" onfocus="ShowInfo(&#39;passwordConfirm_info&#39;)"
maxlength="16"/>
<em id="passwordConfirm_info" style="display: none">再次输入密码</em>
</li>
<li class="pt"><span>单位名称：</span>
<input name="comname" type="text" id="comName" onfocus="ShowInfo(&#39;comName_info&#39;);"  maxlength="50"/>
<em id="comName_info" style="display: none" class="wrong">
<samp>
不能为空</samp></em><b>已输入
<label id="comNameCount">
0</label>
个字符</b>
</li>


<li class="pt"><span>单位地址：</span>
<input name="comaddress" type="text" id="comAddress"  maxlength="80"/>
<div id="cdTip"></div>
</li>
<li class="pt"><span>单位网址：</span>
<input name="comnet" type="text" id="comNet"  maxlength="50"/>
</li>
<li class="pt"><span>单位电话：</span>
<input name="comTel" type="text" id="comTel"  maxlength="50"/>
</li>
<li class="pt"><span>单位Email：</span>
<input name="email" id="email" onfocus="ShowInfo(&#39;email_info&#39;)"
maxlength="50"/>
  <em id="email_info" style="display: none">安全邮箱可以帮你取回丢失的密码，请正确填写。</em></li>
              
<li>
<div class="agree">
<input type="checkbox" checked="checked" id="cbpro" style="background: none; display: inherit;
height: 18px; line-height: normal; width: 20px;"/>
我已经认真阅读并同意<a href="javascript:void(0)" onclick="$(&#39;#clauseer&#39;).toggle();">《防伪信息系统服务条款》</a>

<br/>

</div>
<table id="clauseer" style="display: none" cellspacing="0" cellpadding="0" width="100%"
border="0">
<tbody>
<tr>
<td align="left">
<textarea name="textfield" style="width: 700px" rows="8" cols=""> 本服务条款系由用户与防伪信息系统所有网络相关服务所订立的相关权利义务规范。用户指愿意通过防伪信息系统提供的途径获得许可（帐号和密码）使用本网站所提供的网络服务的个人。


提供您使用本网站及相关网络服务的前提是，您必须接受本合约全部的条款、条件和须知。若您使用本网站及相关网络服务，即表示您同意接受本合约一切条款、条件和须知。


若您选择使用本网站及相关网络服务，您即同意熟悉并遵守这些使用规定，"防伪信息系统隐私权声明"及使用本网站及相关网络服务陆续发现之其它规定及原则。


防伪信息系统保留数据以提供变更本网站及相关网络服务服务的规定、条件及须知。您有责任定期检视这些规定与条件。您继续使用本网站及相关网络服务也将构成您同意所有变更的规定、条件与须知。


个人及非商业使用的限制除非您是本网站服务合约签署人，本网站及本网站服务是仅供个人及非商业目的使用的。除了本网站服务合约另有明示规定外(仅适用于本网站合作站台)，您不得就取自于或经由本网站及服务之资料、软件、产品或服务加以修改、拷贝、散布、传送、展示、执行、重制、发行、授权、制作衍生著作、移转或销售。


与第三方网站的连结

本网站可能包括指向第三方网站的连结（以下简称"连结网站"）。"连结网站"非由本网站(防伪信息系统网站)所控制，对于任何"连结网站"的内容，包含但不限于"连结网站"内含的任何连结，或"连结网站"的任何改变或更新防伪信息系统均不予负责。自"连结网站"接收的网络传播或其它形式之传
送，本网站(防伪信息系统网站)不负其责。防伪信息系统提供这些连结仅为了您的便利所设，加入任何连结不表示防伪信息系统与这些网站业者有任何关连。您有责任检视并遵守"连结网站"登载的隐私声明及使用规定。


不得为非法或禁止的使用

您必须向防伪信息系统保证，您不得为任何非法或为本规定、条件及须知所禁止之目的而使用本网站或本网站服务，此为您使用本网站或本网站服务的一个先决条件。您不得以任何可能损害、瘫痪、使过度负荷或损害本网站或本网站服务或干扰他人对于本网站或本网站服务的使用及享用等方式使用本网站
网站或本网站服务。您不得经由非本网站预定提供的任何方式取得或试图取得任何资料或信息。


对于申请使用本网站及相关网络服务的用户：


一、考虑到为您提供服务的重要性，您必须同意：
1、提供及时、详细及准确的个人资料。

2、不断更新注册资料，符合及时、详细准确的要求。所有原始键入的资料将引用为注册资料。

3、注册成为用户后即可授权本网站向第三方透露其注册资料，但本网站不能公开您的姓名、住址、邮件地址、电子邮箱、帐号。除非：
（1）您要求本网站或授权某人通过电子邮件服务透露这些信息。

（2）相应的法律要求及程序要求本网站(防伪信息系统网站)提供您的个人资料。

（3）如果您提供的资料不准确，本网站(防伪信息系统网站)保留结束您使用本网站及相关网络服务的权利

二、本网站(防伪信息系统网站)尊重您的个人隐私。

所以，作为对以上第三点个人注册资料分析的补充，本网站(防伪信息系统网站)一定不会公开、编辑或透露您注册资料及保存在本网站的非公开内容，除非有法律许可要求。


三、您明确同意使用本网站及相关网络服务由您个人承担风险。

服务提供是建立在免费和有偿并存的基础上。本网站(防伪信息系统网站)明确表示不提供任何类型的担保，不论是明确的或隐含的。本网站(防伪信息系统网站)不担保服务一定能满足用户的要求，也不担保服务不会受中断，对服务的及时性，安全性，出错发生都不作担保。本网站(防伪信息系统网站)拒绝提供任何担保，包括信
息能否准确，及时，顺利的传送。您可以理解并接受任何信息资料(下载或通过本网站服务取得)，这些取决于您自己并由其承担系统受损或资料丢失的所有风险和责任。


四、用户的权利
1、一旦注册成功成为本网站的用户，将得到一个密码和帐号。如果不保管好自己的帐号和密码安全，将负全部责任。另外，每个用户都要对其帐户中的所有活动和事件负全责。用户若发现任何非法使用用户帐号或网站安全漏洞的情况，立即通告本网站，对现有技术无法解决的问题、黑客问题、因特网线路问题、和其他任何非本网站过错引致的用户帐号和网站安全漏洞等情况，以及由此对用户和任何他人产生的任何损失，概与本网站(防伪信息系统网站)无关。用户使用本网站(防伪信息系统网站)服务的权利是个人的。用户只能是一个单独的个体而不能是一个公司或实体的商业性组织。用户承诺不经本网站(防伪信息系统网站)同意，不能利用本网站(防伪信息系统网站)服务进行销售或其他商业用途。

2、本网站(防伪信息系统网站)可随时根据实际情况中断和变更本网站服务。本网站(防伪信息系统网站)无需对任何个人或第三方负责而随时中断或变更服务。用户若反对任何服务条款的建议或对后来的条款修改有异议，或对本网站(防伪信息系统网站)服务不满，用户只有以下的追索权：
(1)不再使用本网站(防伪信息系统网站)服务。

(2)结束用户使用本网站(防伪信息系统网站)服务的资格。

(3)通告本网站停止该用户的服务。结束服务后，用户使用本网站服务的权利马上中止。
从那时起，本网站不再对用户承担任何义务。


五、用户的义务
1、您在享用本网站服务的同时，同意按照本网站不时发布、变更和修改的服务条款、基本法、规定、申明、规章制度等其他所有规定接受本网站提供的各类服务。

2、本网站(防伪信息系统网站)会在必要时修改服务条款，本网站服务条款一旦发生变动，公司将会及时通知用户。若您要继续使用本网站网上服务则本网站认为您已同意如下需要两方面的确认：
(1)首先确认本网站网上服务条款及其变动。

(2)同意接受所有的服务条款限制。

3、您单独承担所发布信息内容的责任。您对服务的使用是根据所有适用于网络社区?服务的地方法律、国家法律和国际法律标准的。不过您可要遵循：

(1)发布信息时必须中华人民共和国的各项有关法律法规，遵守网上一般道德及规范。

(2)不得发布任何宣扬反动、封建迷信、淫秽、色情、赌博、暴力、凶杀、恐怖，教唆犯罪等不符合国家法律规定的以及任何包含种族,性别，宗教歧视性和猥亵性的信息内容。

(3)不得发布任何带有漫骂、辱骂以及包含人身攻击等会产生不良后果的信息内容。

(4)不得利用本网站散布广告以及其它商业化的宣传。

(5)承担一切因不当行为而直接或间接导致的民事或刑事法律责任。

(6)不干扰或混乱本网站网络服务。

4.所有发给您或其他用户的通告电子邮件、邮件列表或其它有效方式传送本网站(防伪信息系统网站)会通过这些方式告知您服务条款的修改、服务变更、或其它重要事情。


六、用户身份的取消:
任何本网站(防伪信息系统网站)有如下行为而导致其帐户被取消，责任自负：

有违反服务条款的行为。

滥用所享受的权利。

提供虚假注册信息。

通过不正当手段参与本网站活动。

有损害其他用户的行为。

违反中国的法律、法规。

违背社会风俗和社会道德的行为。

其他本网站认为不正当的行为。


法律规范:
本网站(防伪信息系统网站)保留防伪信息系统网站的最终解释权。

本网站(防伪信息系统网站)保留在任何时刻，发布、变更和修改的服务条款、基本法、规定、申明、规章制度等其他所有规定全部或部份的权利。

本网站用户服务条款应与国家法律解析一致，包括法律条款中有争议抵触的内容。若有任何服务条款与法律相抵触，应以国家法律为准，同时本网站用户服务相关条款将重新解析，而其它条款则保持对用户产生法律效力和影响。


补充条款一：本网站保护隐私条款
本网站保护隐私条款是本网站和使用本网站之个人用户之间有关个人用户向本网站提供的个人隐私的约定。尊重用户个人隐私是本网站的一项基本原则，由于网络的本身特征，本网站将无可避免地与您产生直接或间接


的互动关系，故本条款说明本网站和用户个人之间就有关用户信息的收集、使用和保护政策的约定，任何使用本网站的用户必须接受本条款的约定,若您不接受如下约定,请选择不使用本网站的服务,因此请您务必仔细阅读：


一、建立本网站
当您拜访本网站合作站台时，会有建立本网站的选项。如果您选择建立本网站，在您的同意及确认下，本网站将要求您提供一些个人资料。同时也需要您的电子邮件来建立本网站。本网站会将您选择要提供的信息储存在一个安全的数据库中。


二、登入

当您拜访一个本网站站台，而且选择登入该站台时，您的本网站基本资料会安全地传送至该站台，如此一来可以节省您在网站之间移动时需要重复输入信息的时间。本网站使用先进的加密技术保障您基本资料的安全及隐私。


三、存取您的本网站基本资料
您可以在任何时候透过拜访本网站会员服务，新增或更新本网站基本资料文件。

如果您使用的是公用的计算机，每当您结束浏览时，您有义务注销本网站，以确保其它人无法存取您的本网站基本资料。


四、熟悉站点的隐私权政策

请您先阅读本网站所提供每个网络服务的隐私权声明和使用规定,因为这对您而言是很重要的，这样可以确保您了解他们可能如何使用您的个人信息。


五、本网站隐私权原则

对本网站而言，如何让您透过本网站使用Internet提供的资源时，同时在本网站现有设备及技术条件下保有您的隐私权是本网站当前相当重要的课题。因此，本网站采取下列几项原则尽可能地保护您的隐私权：

原则一：个人资料

（一）当你同意注册本网站的时候，会要求你提供一些个人资料，这些个人资料包括：

1、个人识别资料：如姓名、性别、年龄、出生日期、身份证号码(或护照号码)、电话、通信地址、住址、电子邮件地址等情况。

2、个人背景：职业、教育程度、收入状况、婚姻、家庭状况。

(二)、请了解，在未经您同意及确认之前，本网站不会将您为参加本网站特定活动所提供的资料利用于其它目的。在按下列第六条规定应政府及法律要求披露时不在此限制内。


原则二、使用非个人化信息

本网站将通过您的IP地址来收集非个人化的信息，例如您的浏览器性质、操作系统种类、给您提供接入服务的ISP的域名等，以优化在您计算机屏幕上显示的页面。通过收集上述信息，我们亦进行客流量统计，从而改进网站的管理和服务。


原则三

(一)、本网站将对您所提供的资料在现有条件下进行严格的管理及保护，本网站将使用现有相应的技术，尽力防止您的个人资料丢失、被盗用或遭窜改。

(二)、本网站将视情况在必要时委托专门的技术人员代为对该类资料进行电脑处理，以符合专业分工时代的需求。如本网站将电脑处理之通知送达予您，而您未在通知规定的时间内主动表示反对，本网站将依此判断您已同意。


原则四、安全的资料储存与转送。

本网站具安全性的服务器使用控制设备保护，您的本网站信息储存在该服务器。当您要求将本网站信息传送到某个支持网站时，本网站会加密您的个人信息，然后使用先进的加密技术将个人信息传送到该网站。


原则五、限制利用原则

本网站只有在符合下列条件之一，方对收集的个人资料进行必要范围以外利用：

(一)、已取得您的书面同意；

(二)、为免除您在生命、身体或财产方面之急迫危险；

(三)、为防止他人权益之重大危害；
(四)、为增进公共利益，且无害于您的重大利益。


原则六、个人资料的披露
当国家政府机关依照法定程序要求本网站披露个人资料时，本网站将根据执法单位的要求或为公共安全目的提供个人资料。在此情况下披露的任何内容，本网站不承担任何责任。


原则七、有关免责

除上述第六条规定属免责外，下列情况时本网站亦无需承担任何责任：

(一)、由于您将用户密码告知他人或未保管好自己的密码或与他人共享注册帐户或任何其他非本网站的过错，由此导致的任何个人资料泄露。

(二)、任何由于计算机2000年问题、黑客攻击、计算机病毒侵入或发作、电信部门技术调整导致之影响、因政府管制而造成的暂时性关闭、由于第三方原因(包括不可抗力，例如国际出口的主干链路及国际出口电信提供商一方出现故障、火灾、水灾、雷击、地震、洪水、台风、龙卷风、火山爆发、瘟疫和传染病流行、罢工、战争或暴力行为或类似事件等)造成本网站不能正常发布以及其它影响网络正常经营之不可抗力及其他任何非因本网站过错而造成的个人资料泄露、丢失、被盗用或被窜改等。

(三)、由于与本网站链接的其它网站所造成的个人资料泄露及由此而导致的任何法律争议和后果。

(四)、任何个人用户，包括未成年人用户向本网站提供错误、不完整、不实信息等造成不能正常使用本网站服务或遭受任何其他损失，概与本网站无关。

(五)、为了网站的正常运行，需要定期或不定期地对网站进行停机维护，因此类情况而造成的正常服务中断等。

(六)、本网站服务使用者与防伪信息系统公司之本网站合约及本网站不时颁布和修改的规章、制度、条款等规定的其他免责条款。本保护隐私条款为本网站用户服务条款的补充，若有任何与前述和约冲突的地方，以和约为准。本网站保护隐私声明的修改权、解释权和更新权均属于本网站。 </textarea>
</td>
<td align="center">
&nbsp;
</td>
</tr>
</tbody>
</table>
</li>
<li><span></span><a onclick="return onSubmit();" id="submit" class="regbutton" ></a><a href=""></a></li>
</ul>
</div>
</div>


<script type="text/javascript" src="../JS/Nreg.js">

</script>

</td>
</tr>
</table>


    </form>


</body>
</html>
