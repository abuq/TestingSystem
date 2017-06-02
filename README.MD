# 法院速录系统
----
内容
===
在我国的各级人民法院，为了记录庭审现场各类人员（包括：司法人员、嫌疑人、律师等）的谈话内容，有一批工作人员专门负责此项工作，这批工作人员被称之为“速录员”。速录员要求具有很快的文字录入速度和较高的录入准确率，以保证庭审记录的完整性和准确性。因此，如何有效地评测速录员录入文字的速度以及准确率是各级人民法院在招聘和考核速录员时需要面对的难题。针对这一现状，本实验要求各位同学在Visual Studio 2010下使用C++语言独立开发出一个速录员评测系统。
功能描述
======

+ 1、音频播放：音频文件的格式为MP3或者WMA，使用MCI（Media Control Interface，媒体控制接口）中的相关函数（参考资料如下http://blog.csdn.net/dancewyr/article/details/7183572）；
+ 2、文字录入及身份证校验：根据音频文件播放的内容，使用“Edit Box”控件录入文字；考虑文字的自动换行（提示：选中“Edit Box”的多行属性和垂直滚动条属性）。另外，录入身份证之后应该校验身份证的长度及相关信息的合法性。
+ 3、倒计时：设置一个定时器，每隔一秒钟刷新一次剩余时间（如图3所示），并且当剩余时间为零时将文字录入区域变为非激活状态，即：剩余时间为零时不能再录入文字。
+ 4、配置文件：通过读取.ini文件（如下图所示）获取评测时长、可选的音频文件个数、音频文件格式、最大录入速度（计算成绩时使用）、录入速度与准确率的权重等信息。（参考资料http://zhidao.baidu.com/question/33265898.html）![权重](/img/over.png)
+ 5、成绩评定：通过编辑距离（Edit Distance）算法，计算录入文字与标准答案之间的相似度，即：准确率（参考资料http://cfanz.cn/index.php?c=article&a=read&id=25938）；另外，根据录入速度和准确率以及所设定的权重，根据如下公式计算最终成绩。
score = percentage_accuracy * accuracy + percentage_speed * speed
   其中：score是最终成绩，percentage_accuracy是准确率的权重，accuracy是录入的准确率，percentage_speed是录入速度的权重，speed是录入速度。并且，percentage_accuracy+ percentage_speed=1（如上图所示，这两个权重分别设为0.7和0.3）。
   并且，录入速度speed的计算公式如下：
speed = 录入文字个数 / 所用时间(分钟)
   说明：当计算得到的speed超过配置文件中所设定的最快录入速度（如上图所示的max_speed）时，speed按100分参与最终成绩的计算。否则，按实际计算分值参与最终成绩的计算。
+ 6、成绩单打印：利用PDFLib工具，将评测用户的个人信息（准考证号、身份证号等）、录入的文字及其成绩等内容写入一个PDF文件，防止评测用户自行修改相关内容。（参考资料http://www.sudu.cn/info/html/edu/20080403/259607.html）
+ 7、加密算法：为了保证标准答案文件的安全性，需要将其加密处理（请自行设计加密算法），防止评测人员找到标准答案文件，拷贝其中内容。
+ 8、操作手册：根据你所开发的系统，编写操作手册，方便用户的使用。
+ 9、打包程序：将开发好的应用程序及其所需的DLL文件通过打包软件，制作成安装程序，以供他人使用。
参考界面
=======
初始界面
![初始界面](/img/1.png)
录入考生信息
![录入考生信息](/img/2.png)
点击“开始考试”之后的界面
![点击“开始考试”之后的界面](/img/3.png)
点击“提交”之后的消息框
![点击“提交”之后的消息框](/img/4.png)
点击“确定”之后的界面
![点击“确定”之后的界面](/img/5.png)
点击“打印成绩单”之后的界面
![点击“打印成绩单”之后的界面](/img/6.png)