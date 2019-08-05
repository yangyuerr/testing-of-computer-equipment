// camera_change.cpp : 实现文件
//
#include "stdafx.h"
#include "测试.h"
#include "camera_change.h"
#include "afxdialogex.h"
#include "afxwin.h"
// camera 对话框
#include<atlimage.h>
#include "测试.h"
#include "afxdialogex.h"
#include<iostream>
#include "strmif.h"
#include <initguid.h>
#include<vector>
#include<string>
#include <iostream> 
#include <cstdio> 
#include <fstream> 
#include <algorithm> 
#include <cmath> 
#include <deque> 
#include <vector> 
#include <queue> 
#include <string> 
#include <cstring> 
#include <map> 
#include <stack> 
#include <set> 
#include "stdafx.h"
//#include "MediaStreamingDemoDlg.h"
#include "afxdialogex.h"
#include <sstream>
#include "conclusion.h"
#pragma comment(lib, "setupapi.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;


#define VI_MAX_CAMERAS 20
DEFINE_GUID(CLSID_SystemDeviceEnum, 0x62be5d10, 0x60eb, 0x11d0, 0xbd, 0x3b, 0x00, 0xa0, 0xc9, 0x11, 0xce, 0x86);
DEFINE_GUID(CLSID_VideoInputDeviceCategory, 0x860bb310, 0x5d01, 0x11d0, 0xbd, 0x3b, 0x00, 0xa0, 0xc9, 0x11, 0xce, 0x86);
DEFINE_GUID(IID_ICreateDevEnum, 0x29840822, 0x5b84, 0x11d0, 0xbd, 0x3b, 0x00, 0xa0, 0xc9, 0x11, 0xce, 0x86);






//列出硬件设备
// Camera 对话框




int  camera_change::listDevices(vector<string>& list)
{
	ICreateDevEnum *pDevEnum = NULL;
	IEnumMoniker *pEnum = NULL;
	int deviceCounter = 0;
	CoInitialize(NULL);

	HRESULT hr = CoCreateInstance(
		CLSID_SystemDeviceEnum,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_ICreateDevEnum,
		reinterpret_cast<void**>(&pDevEnum)
	);

	if (SUCCEEDED(hr))
	{
		hr = pDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEnum, 0);
		if (hr == S_OK) {

			IMoniker *pMoniker = NULL;
			while (pEnum->Next(1, &pMoniker, NULL) == S_OK)
			{
				IPropertyBag *pPropBag;
				hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag,
					(void**)(&pPropBag));

				if (FAILED(hr)) {
					pMoniker->Release();
					continue; // Skip this one, maybe the next one will work.
				}

				VARIANT varName;
				VariantInit(&varName);
				hr = pPropBag->Read(L"Description", &varName, 0);
				if (FAILED(hr))
				{
					hr = pPropBag->Read(L"FriendlyName", &varName, 0);
				}

				if (SUCCEEDED(hr))
				{
					hr = pPropBag->Read(L"FriendlyName", &varName, 0);
					int count = 0;
					char tmp[255] = { 0 };
					while (varName.bstrVal[count] != 0x00 && count < 255)
					{
						tmp[count] = (char)varName.bstrVal[count];
						count++;
					}
					list.push_back(tmp);
				}

				pPropBag->Release();
				pPropBag = NULL;
				pMoniker->Release();
				pMoniker = NULL;

				deviceCounter++;
			}

			pDevEnum->Release();
			pDevEnum = NULL;
			pEnum->Release();
			pEnum = NULL;
		}
	}
	//pwnd = getdlgitem(idc_vedio);
	////pwnd->movewindow(35,30,352,288);
	//pdc = pwnd->getdc();
	////pdc =getdc();
	//hdc = pdc->getsafehdc();
	//pwnd->getclientrect(&rect);




	return deviceCounter;



}



// camera_change 对话框

IMPLEMENT_DYNAMIC(camera_change, CDialogEx)

camera_change::camera_change(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_camera, pParent)
{
	int a = 1;

}

camera_change::~camera_change()
{
}

void camera_change::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, combox);
	DDX_Control(pDX, IDC_vedio, picture);
}


BEGIN_MESSAGE_MAP(camera_change, CDialogEx)
	ON_CBN_SETFOCUS(IDC_COMBO1, &camera_change::OnCbnSetfocusCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &camera_change::OnCbnSelchangeCombo1)
	ON_WM_TIMER()
	ON_STN_CLICKED(IDC_vedio, &camera_change::OnStnClickedvedio)
	ON_BN_CLICKED(IDC_BUTTON1, &camera_change::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &camera_change::OnBnClickedButton2)
END_MESSAGE_MAP()


// camera_change 消息处理程序


void camera_change::OnCbnSetfocusCombo1()
{


	
	// TODO: 在此添加控件通知处理程序代码

	combox.ResetContent();//点击一次，清除一次
	vector<string> CameraName;//存储摄像头名称
	camera_change  ID;
	int num = ID.listDevices(CameraName);
	int i;
	CString  name;
	for (i = 0; i < num; i++)
	{
		
		CString  name(CameraName[i].c_str());
		combox.AddString(name);
		
	}
	combox.SetCurSel(0);









}


void camera_change::OnCbnSelchangeCombo1()
{



	finum = 1;

	capDriverDisconnect(m_hWndVideo);//断开连接
	int nIndex = combox.GetCurSel();
	m_hMyGreen = CreateSolidBrush(RGB(202, 225, 243));

	//创建预览窗口

	m_hWndVideo = capCreateCaptureWindow(NULL, WS_POPUP, 1, 1, 10, 10, m_hWnd, 0);

	//HWND VFWAPI capCreateCaptureWindow(LPCSTR lpszWindowName, DWORD dwStyle, int x,

	//	int y, int nWidth, int nHeight, HWND hWnd, int nID);

	//参数说明：

	//	lpszWindowName：表示视频捕捉窗口的名称。

	//	dwStyle：表示视频捕获窗口的风格，一般包含有WS_CHILD 和 WS_VISIBLE风格。

	//	x、y：表示视频捕捉窗口的左上角坐标。

	//	nWidth、nHeight：表示视频捕捉窗口的宽度和高度。

	//	hWnd：表示视频捕捉窗口父窗口的句柄。

	//	nID：表示视频捕捉窗口标识。


	//连接驱动程序

	if (capDriverConnect(m_hWndVideo, nIndex))
	{
		::SetParent(m_hWndVideo, *this);
		::SetWindowLong(m_hWndVideo, GWL_STYLE, WS_CHILD);
		CRect wndRC;
		picture.GetClientRect(wndRC);

		picture.MapWindowPoints(this, wndRC);
		wndRC.DeflateRect(1, 1, 1, 1);//显示框的缩小
		::SetWindowPos(m_hWndVideo, NULL, wndRC.left,
			wndRC.top, wndRC.Width(), wndRC.Height(), SWP_NOZORDER);
		::ShowWindow(m_hWndVideo, SW_SHOW);
		capPreviewRate(m_hWndVideo, 20);//设置帧
		capPreview(m_hWndVideo, TRUE);//显示
	}
		// TODO: 在此添加控件通知处理程序代码
	
	//combox.ResetContent();//点击一次，清除一次


}


void camera_change::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值




}


BOOL camera_change::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化


	


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void camera_change::OnStnClickedvedio()
{
	// TODO: 在此添加控件通知处理程序代码
}


void camera_change::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!finum)
	{
		AfxMessageBox(_T("请先进行摄像头测试！"));
		return;
	}

	finum = 0;
	capDriverDisconnect(m_hWndVideo);//断开连接
	C测试App *pApp = (C测试App *)AfxGetApp();//保存
	pApp->m_camera = 1;
	CDialogEx::OnCancel();
	conclusion dlg;
	dlg.DoModal();

}


void camera_change::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!finum)
	{
		AfxMessageBox(_T("请先进行摄像头测试！"));
		return;
	}

	finum = 0;

	capDriverDisconnect(m_hWndVideo);//断开连接
	C测试App *pApp = (C测试App *)AfxGetApp();//保存
	pApp->m_camera = 0;
	CDialogEx::OnCancel();
	conclusion dlg;
	dlg.DoModal();

}
