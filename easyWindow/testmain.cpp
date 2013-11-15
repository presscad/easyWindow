#include "easyWindow.h"
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR cmdLine,int nCmd)
{
	HWND hwnd,hwnd2;
	//批量初始化
	WinInit(hInstance,hPrevInstance,cmdLine,nCmd,"video");
	//这句话用于实现控制台调试输出。没有的话不会影响程序的执行。
	RedirectIOToConsole();

	hwnd=newNamedWindow("wnd1");
	hwnd2=newNamedWindow("wnd2");
	
	//尽情的使用窗口hwnd吧，如果要自定义窗口行为，请修改easyWindow.cpp里面的windProc函数


	msgCircle();
	return afxmsg.wParam;
}