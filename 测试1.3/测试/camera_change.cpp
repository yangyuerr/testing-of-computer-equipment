// camera_change.cpp : ʵ���ļ�
//
#include "stdafx.h"
#include "����.h"
#include "camera_change.h"
#include "afxdialogex.h"
#include "afxwin.h"
// camera �Ի���
#include<atlimage.h>
#include "����.h"
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






//�г�Ӳ���豸
// Camera �Ի���




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



// camera_change �Ի���

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


// camera_change ��Ϣ�������


void camera_change::OnCbnSetfocusCombo1()
{


	
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	combox.ResetContent();//���һ�Σ����һ��
	vector<string> CameraName;//�洢����ͷ����
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

	capDriverDisconnect(m_hWndVideo);//�Ͽ�����
	int nIndex = combox.GetCurSel();
	m_hMyGreen = CreateSolidBrush(RGB(202, 225, 243));

	//����Ԥ������

	m_hWndVideo = capCreateCaptureWindow(NULL, WS_POPUP, 1, 1, 10, 10, m_hWnd, 0);

	//HWND VFWAPI capCreateCaptureWindow(LPCSTR lpszWindowName, DWORD dwStyle, int x,

	//	int y, int nWidth, int nHeight, HWND hWnd, int nID);

	//����˵����

	//	lpszWindowName����ʾ��Ƶ��׽���ڵ����ơ�

	//	dwStyle����ʾ��Ƶ���񴰿ڵķ��һ�������WS_CHILD �� WS_VISIBLE���

	//	x��y����ʾ��Ƶ��׽���ڵ����Ͻ����ꡣ

	//	nWidth��nHeight����ʾ��Ƶ��׽���ڵĿ�Ⱥ͸߶ȡ�

	//	hWnd����ʾ��Ƶ��׽���ڸ����ڵľ����

	//	nID����ʾ��Ƶ��׽���ڱ�ʶ��


	//������������

	if (capDriverConnect(m_hWndVideo, nIndex))
	{
		::SetParent(m_hWndVideo, *this);
		::SetWindowLong(m_hWndVideo, GWL_STYLE, WS_CHILD);
		CRect wndRC;
		picture.GetClientRect(wndRC);

		picture.MapWindowPoints(this, wndRC);
		wndRC.DeflateRect(1, 1, 1, 1);//��ʾ�����С
		::SetWindowPos(m_hWndVideo, NULL, wndRC.left,
			wndRC.top, wndRC.Width(), wndRC.Height(), SWP_NOZORDER);
		::ShowWindow(m_hWndVideo, SW_SHOW);
		capPreviewRate(m_hWndVideo, 20);//����֡
		capPreview(m_hWndVideo, TRUE);//��ʾ
	}
		// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	//combox.ResetContent();//���һ�Σ����һ��


}


void camera_change::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ




}


BOOL camera_change::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��


	


	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void camera_change::OnStnClickedvedio()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void camera_change::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!finum)
	{
		AfxMessageBox(_T("���Ƚ�������ͷ���ԣ�"));
		return;
	}

	finum = 0;
	capDriverDisconnect(m_hWndVideo);//�Ͽ�����
	C����App *pApp = (C����App *)AfxGetApp();//����
	pApp->m_camera = 1;
	CDialogEx::OnCancel();
	conclusion dlg;
	dlg.DoModal();

}


void camera_change::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!finum)
	{
		AfxMessageBox(_T("���Ƚ�������ͷ���ԣ�"));
		return;
	}

	finum = 0;

	capDriverDisconnect(m_hWndVideo);//�Ͽ�����
	C����App *pApp = (C����App *)AfxGetApp();//����
	pApp->m_camera = 0;
	CDialogEx::OnCancel();
	conclusion dlg;
	dlg.DoModal();

}
