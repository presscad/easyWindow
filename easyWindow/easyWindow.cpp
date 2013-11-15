#include "easyWindow.h"
#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <fstream>

using namespace std;

//定义一些全局变量，便于简化调用，这些变量都会在wininit函数中初始化。
char* afxclassName;
HINSTANCE afxhInstance,afxhPrevInstance;
int afxnCmd;
LPSTR afxcmdLine;
MSG afxmsg;
static const WORD MAX_CONSOLE_LINES = 500;//控制台输出的最大行数
//全局变量定义完毕

//定义结构体，用于多线程的时候传递给内部使用
struct HWNDandMSG
{
	HWND hwnd;
	MSG msg;
	char* classname;
	char* name;
	HINSTANCE hInstance;
	unsigned long threadId;
	int nCmd;
};
//窗口处理函数
LRESULT CALLBACK windProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	switch(message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
	case WM_KEYDOWN:
		cout<<"hwnd:"<<hwnd<<"\tkeydown:[wParam:"<<wParam<<",lParam:"<<lParam<<"]\tmsg:"<<message<<endl;
		return 0;
	default:
		return DefWindowProc(hwnd,message,wParam,lParam);
	}
	return (0);
}
//消息循环函数，在需要等待的地方使用，比waitkey好玩
void msgCircle(MSG &msg,HWND hwnd)
{
	while(GetMessage(&msg,hwnd,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}
//批量初始化化函数，主要初始化全局变量和注册窗口类
bool WinInit(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR cmdLine,int nCmd,char* className)
{
	afxhInstance=hInstance;
	afxhPrevInstance=hPrevInstance;
	afxnCmd=nCmd;
	afxclassName=className;
	afxcmdLine=cmdLine;

	WNDCLASS wndclass;
	wndclass.style=0;
	wndclass.cbClsExtra=0;
	wndclass.cbWndExtra=0;
	wndclass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hCursor=LoadCursor(NULL,IDC_ARROW);
	wndclass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName=NULL;

	wndclass.lpfnWndProc=windProc;
	wndclass.hInstance=hInstance;
	wndclass.lpszClassName=className;

	if(!RegisterClass(&wndclass))
	{
		return false;
	}
	return true;
}
//创建窗口的线程，一个窗口一个线程
unsigned long __stdcall wndMsgCircle(void* pParam)
{
	HWNDandMSG* pHM=(HWNDandMSG*)pParam;
	pHM->hwnd=CreateWindow(pHM->classname,pHM->name,WS_OVERLAPPEDWINDOW,1000,50,300,200,NULL,NULL,pHM->hInstance,NULL);
	ShowWindow(pHM->hwnd,pHM->nCmd);
	UpdateWindow(pHM->hwnd);
	cout<<"build\t"<<pHM->name<<"\t"<<pHM->threadId<<endl;
	msgCircle(pHM->msg);
	cout<<"close\t"<<pHM->name<<"\t"<<pHM->threadId<<endl;
	WPARAM returnValue=pHM->msg.wParam;
	delete pHM;
	return returnValue;
}
//创建窗口,一个线程一个窗口
HWND newNamedWindow(char name[],HINSTANCE hInstance,int nCmd,char className[])
{
	HWNDandMSG* pHM=new HWNDandMSG;
	pHM->classname=className;
	pHM->name=name;
	pHM->hInstance=hInstance;
	pHM->nCmd=nCmd;
	pHM->hwnd=0;
	CloseHandle(CreateThread(NULL,0,&wndMsgCircle,pHM,0,&pHM->threadId));
	while(!pHM->hwnd)Sleep(10);
	return pHM->hwnd;
}
//重定向标准输入输出，用于调试
void RedirectIOToConsole(void)
{
	int hConHandle;
	HANDLE lStdHandle;
	CONSOLE_SCREEN_BUFFER_INFO coninfo;
	FILE *fp;

	//为该应用创建一个控制台
	AllocConsole();
	//将缓冲区设置为足够大，便于我们输出和滚动窗口 
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
	coninfo.dwSize.Y = MAX_CONSOLE_LINES;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);
	// 把缓冲区输出STDOUT重定向到控制台
	lStdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	hConHandle = _open_osfhandle((INT_PTR)lStdHandle, _O_TEXT);
	fp = _fdopen( hConHandle, "w" );
	*stdout = *fp;
	setvbuf( stdout, NULL, _IONBF, 0 );
	// 把缓冲区输入STDIN重定向到控制台
	lStdHandle = GetStdHandle(STD_INPUT_HANDLE);
	hConHandle = _open_osfhandle((INT_PTR)lStdHandle, _O_TEXT);
	fp = _fdopen( hConHandle, "r" );
	*stdin = *fp;
	setvbuf( stdin, NULL, _IONBF, 0 );
	// 把错误STDERR重定向到控制台
	lStdHandle = GetStdHandle(STD_ERROR_HANDLE);
	hConHandle = _open_osfhandle((INT_PTR)lStdHandle, _O_TEXT);
	fp = _fdopen( hConHandle, "w" );
	*stderr = *fp;
	setvbuf( stderr, NULL, _IONBF, 0 );
	// 把cout,wcout,cin,wcin,wcerr,cerr,wclog和clog指向控制台
	ios::sync_with_stdio();
}
