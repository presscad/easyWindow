#include "easyWindow.h"
#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <fstream>

using namespace std;

//����һЩȫ�ֱ��������ڼ򻯵��ã���Щ����������wininit�����г�ʼ����
char* afxclassName;
HINSTANCE afxhInstance,afxhPrevInstance;
int afxnCmd;
LPSTR afxcmdLine;
MSG afxmsg;
static const WORD MAX_CONSOLE_LINES = 500;//����̨������������
//ȫ�ֱ����������

//����ṹ�壬���ڶ��̵߳�ʱ�򴫵ݸ��ڲ�ʹ��
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
//���ڴ�����
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
//��Ϣѭ������������Ҫ�ȴ��ĵط�ʹ�ã���waitkey����
void msgCircle(MSG &msg,HWND hwnd)
{
	while(GetMessage(&msg,hwnd,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}
//������ʼ������������Ҫ��ʼ��ȫ�ֱ�����ע�ᴰ����
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
//�������ڵ��̣߳�һ������һ���߳�
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
//��������,һ���߳�һ������
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
//�ض����׼������������ڵ���
void RedirectIOToConsole(void)
{
	int hConHandle;
	HANDLE lStdHandle;
	CONSOLE_SCREEN_BUFFER_INFO coninfo;
	FILE *fp;

	//Ϊ��Ӧ�ô���һ������̨
	AllocConsole();
	//������������Ϊ�㹻�󣬱�����������͹������� 
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
	coninfo.dwSize.Y = MAX_CONSOLE_LINES;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);
	// �ѻ��������STDOUT�ض��򵽿���̨
	lStdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	hConHandle = _open_osfhandle((INT_PTR)lStdHandle, _O_TEXT);
	fp = _fdopen( hConHandle, "w" );
	*stdout = *fp;
	setvbuf( stdout, NULL, _IONBF, 0 );
	// �ѻ���������STDIN�ض��򵽿���̨
	lStdHandle = GetStdHandle(STD_INPUT_HANDLE);
	hConHandle = _open_osfhandle((INT_PTR)lStdHandle, _O_TEXT);
	fp = _fdopen( hConHandle, "r" );
	*stdin = *fp;
	setvbuf( stdin, NULL, _IONBF, 0 );
	// �Ѵ���STDERR�ض��򵽿���̨
	lStdHandle = GetStdHandle(STD_ERROR_HANDLE);
	hConHandle = _open_osfhandle((INT_PTR)lStdHandle, _O_TEXT);
	fp = _fdopen( hConHandle, "w" );
	*stderr = *fp;
	setvbuf( stderr, NULL, _IONBF, 0 );
	// ��cout,wcout,cin,wcin,wcerr,cerr,wclog��clogָ�����̨
	ios::sync_with_stdio();
}
