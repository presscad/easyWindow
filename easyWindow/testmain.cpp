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