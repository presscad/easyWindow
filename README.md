#easyWindow简介
==========

为需要用调用窗口调试的windows的VC程序快速搭建调试环境，类似于OpenCV里面的namedwindow（）不过，这个很简洁代码很少，同时为你提供cin和cout调试。

==========

#easyWindow
****
Created 星期日 17 十一月 2013


##easyWindow适用什么样的人群？
如果你在VC开发非mfc程序，你侧重的是后台效率或者其他，但是你代码调试的时候却需要一个窗口作为调试环境，那么easyWindow很适合你。
加点废话：有些人说做后台和侧重其他的同学怎么会用窗口呢？这个是有的。比如你调试个图像处理的代码，你侧重的是图像处理，但是图像显示的时候需要用一个窗口，要求你传入一个HWND类型的参数，这样你的库就能帮助你显示图像了。（很多库不提供创建窗口的，但是提供显示显示方法，需要个hwnd参数，窗口自己创建。）
	

##easyWindow都做什么？
1. 创建窗口，采用最简单最默认的方式，窗口大小可调。

2. 简单可定制的标准输入输出重定向，便于习惯使用cout和cin的同学：在窗口程序中，你依然可以使用cout和cin来查看结果和中间输入数据。


##easyWindow不能做什么？
easyWindow不奢求你将easyWindow加入你们的最终项目并作为很重要的一部分。easyWindow只是想为你们提供一个调试你们后台类代码的环境，你们的界面可以使用mfc重搭，或者使用其他。

easyWindow只提供一个在VC下的调试框架。你们的代码当然也可以是跨平台的，这样非常好，但是目前的easyWindow只提供VC下的调试，其他开发环境根据情况而定吧，easyWindow在合适的时候会考虑为你提供帮助的，当然我们欢迎高手将代码提交给我们，这样easyWindow会更好用。

easyWindow是一个开源的代码调试框架，他的功能也很简单，不能满足你太多的要求，比如说你需要一个按钮控件什么的。当然，这个会成为可能，需要的是你继续开发一些代码：easyWindow本身就是VS的C++项目，你要是很懂GDI的话，自己来不是难事。

##easyWindow的优势与不同是什么？

1. easyWindow采用多线程管理窗口消息，在你代码运行的过程中，你的窗口是活动状态的，不会一直处于假死状态，这是比openCV的namedwindow好的地方。

2. 小巧灵活，这个从代码的行数上你应该是能看明白的。

	
##怎么使用easyWindow？
easyWindow希望为你提供最傻瓜简单的方式来调试你的代码，所以他的使用也非常的简单。

有一下几种方法可供选择（一种就够用了）：

1. 直接使用源代码：你可以将easyWindow.h和easyWindow.cpp文件直接加入你的工程中，像easyWindow.h中注释掉的示例那样把他们复制一下在另一个文件中粘贴就可以了。你可以使用的函数都在easyWindow中声明了。他们的作用你可以查看他们的注释，要是感兴趣的话你也可以查看源代码。

2. 使用easyWindow.lib文件和easyWindow.h头文件：使用lib文件的好处是你省去了编译的麻烦（虽然这么一点代码一点也不麻烦），同时也能避免你错误修改源文件或者犯其他错误。后面的使用方法同上，还要做的是把lib文件加入你的链接目录，或是声明一下链接文件（用#pragma comment（lib，“easyWind.lib”））。

3. 动态库的方法。也没有太多新意，和2差不多，先自己探索吧。


##你需要给作者什么？
easyWindow采用最简单的开放精神，完全开源，不需要你作出什么报酬，如果你愿意的话在使用后对easyWindow表示感谢即可，如果你不想感谢，也是没有关系的，一切随你。你有权随便修改easyWindow，修改后你可以拥有它的近乎一切权责。但是1.不得恶意评价源作者和作品，比如你修改后easyWindow_yourversion很牛，不能说原来的就是个狗屁。2.更改后的版本命名不得使用“easyWindow+数字“的方式。

我们也希望你能贡献你的智慧，提交bug和修改意见，这样的话，我们一定会感谢你的。

	
##从哪里得到easyWindow？
easyWindow的代码目前会托管在作者自己的github和gitcafe上，你在任意一个站点都可以拿到比较新的版本。如果你善于使用git那是最好不过的了，如果不是，那也没有关系，用你的鼠标复制和粘贴源代码其实也是很简单的事情。

Github:  <https://github.com/wangwenbin/easyWindow>

Gitcafe: <https://gitcafe.com/wangwenbin/easyWindow>

	
##如何为easyWindow做贡献？
1. 提出你的修改建议和bug，可以在Issue上反映，也可以mail作者（wangwenbin@outlook.com）（最好去issue（在gitcafe上叫工单，需要登录）上提交吧）。

2. 通过你的github或者gitcafe提交合并申请。这种方式非常欢迎。
