#include <Windows.h>
extern char* afxclassName;
extern HINSTANCE afxhInstance,afxhPrevInstance;
extern int afxnCmd;
extern LPSTR afxcmdLine;
extern MSG afxmsg;
void RedirectIOToConsole(void);
bool WinInit(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR cmdLine,int nCmd,char* className);
HWND newNamedWindow(char name[],HINSTANCE hInstance=afxhInstance,int nCmd=afxnCmd,char className[]=afxclassName);
void msgCircle(MSG &msg=afxmsg,HWND hwnd=NULL);
/****************************************************************************************
//ʾ�����£��ǲ��ǳ�������
#include "easyWindow.h"
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR cmdLine,int nCmd)
{
	HWND hwnd,hwnd2;
	//������ʼ��
	WinInit(hInstance,hPrevInstance,cmdLine,nCmd,"video");
	//��仰����ʵ�ֿ���̨���������û�еĻ�����Ӱ������ִ�С�
	RedirectIOToConsole();

	hwnd=newNamedWindow("wnd1");
	hwnd2=newNamedWindow("wnd2");
	
	//�����ʹ�ô���hwnd�ɣ����Ҫ�Զ��崰����Ϊ�����޸�easyWindow.cpp�����windProc����


	msgCircle();
	return afxmsg.wParam;
}
/*******************************************************************************************/