
// 测试Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "测试.h"
#include "测试Dlg.h"
#include "afxdialogex.h"
#include "ping.h"
#include "speaker.h"
#include <Windows.h>
#include <mmsystem.h>

#pragma comment(lib,"Winmm.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CAboutDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// C测试Dlg 对话框



C测试Dlg::C测试Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C测试Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_teacher_speed, teacher_speed);
	DDX_Control(pDX, IDC_teacher_assess, teacher_assess);
	DDX_Control(pDX, IDC_plat_speed, plat_speed);
	DDX_Control(pDX, IDC_plat_assess, plat_assess);
	DDX_Control(pDX, IDC_audio_speed, audio_speed);
	DDX_Control(pDX, IDC_audio_assess, audio_assess);
//	DDX_Control(pDX, IDC_audio_speed2, audio_assess);
}

BEGIN_MESSAGE_MAP(C测试Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &C测试Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &C测试Dlg::OnBnClickedCancel)
//	ON_STN_CLICKED(IDC_teacher_speed2, &C测试Dlg::OnStnClickedteacherspeed2)
	ON_STN_CLICKED(IDC_teacher_speed, &C测试Dlg::OnStnClickedteacherspeed)
	ON_STN_CLICKED(IDC_audio_speed, &C测试Dlg::OnStnClickedaudiospeed)
	ON_STN_CLICKED(IDC_audio_assess, &C测试Dlg::OnStnClickedaudioassess)
END_MESSAGE_MAP()


// C测试Dlg 消息处理程序

BOOL C测试Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C测试Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void C测试Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR C测试Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C测试Dlg::OnBnClickedOk()
{
	finum = 1;

	CPing objPing_tech;
	CPing objPing_plat;
	CPing objPing_audio;

	//将域名解析位IP
	// 返回的域名对应实际IP的个数
	int ynIpCount_tech = 0;
	int ynIpCount_plat = 0;
	int ynIpCount_audio = 0;
	// 返回的域名对应实际I列表
	char yszIpList_tech[50][100] = {0};
	char yszIpList_plat[50][100] = {0};
	char yszIpList_audio[50][100] = {0};

	// 域名
	char yszDomain_tech[256] = { 0 };
	char yszIp_tech[1024] = { 0 };
	strcpy_s(yszDomain_tech, "api.hss.aicfe.cn");
	objPing_tech.GetRealIpByDomainName(yszDomain_tech, yszIpList_tech, &ynIpCount_tech);//该函数将域名解析成IP，并放在数组yszIpList中，ynIpCount存放IP的个数（有的域名有多个IP）
	
	char yszDomain_plat[256] = { 0 };
	char yszIp_plat[1024] = { 0 };
	strcpy_s(yszDomain_plat, "fepapi.edu.web.sdp.101.com");
	objPing_tech.GetRealIpByDomainName(yszDomain_plat, yszIpList_plat, &ynIpCount_plat);

	char yszDomain_audio[256] = { 0 };
	char yszIp_audio[1024] = { 0 };
	strcpy_s(yszDomain_audio, "api.netease.im");
	objPing_tech.GetRealIpByDomainName(yszDomain_audio, yszIpList_audio, &ynIpCount_audio);


	char IP_tech[100];
	strcpy(IP_tech, yszIpList_tech[0]);
	char *szDestIP_tech = IP_tech;
	PingReply reply_tech;
	int i = 0;
	float time_tech=0;

	char IP_plat[100];
	strcpy(IP_plat, yszIpList_plat[0]);
	char *szDestIP_plat = IP_plat;
	PingReply reply_plat;
	float time_plat = 0;

	char IP_audio[100];
	strcpy(IP_audio, yszIpList_audio[0]);
	char *szDestIP_audio = IP_audio;
	PingReply reply_audio;
	float time_audio = 0;

	for (i = 0; i<3; i++)
	{
		objPing_tech.Ping(szDestIP_tech, &reply_tech);
		time_tech = time_tech + reply_tech.m_dwRoundTripTime;

		objPing_plat.Ping(szDestIP_plat, &reply_plat);
		time_plat = time_plat + reply_plat.m_dwRoundTripTime;

		objPing_audio.Ping(szDestIP_audio, &reply_audio);
		time_audio = time_audio + reply_audio.m_dwRoundTripTime;



		//printf("Reply from %s: bytes=%d time=%ldms TTL=%ld\n", szDestIP, reply.m_dwBytes, reply.m_dwRoundTripTime, reply.m_dwTTL);
		//Sleep(500);
	}

	time_tech = time_tech / 3.0;
	time_plat = time_plat / 3.0;
	time_audio = time_audio / 3.0;


	C测试App *pApp = (C测试App *)AfxGetApp();//保存
	pApp->m_teach = time_tech;
	pApp->m_plat = time_plat;
	pApp->m_audio = time_audio;


	if (time_tech >=0&& time_tech <= 20)
	{
		CString strtmp_tech;
		strtmp_tech.Format(_T("%.0fms"), time_tech);
		teacher_speed.SetWindowTextW(strtmp_tech);
		teacher_assess.SetWindowTextW(TEXT("优"));
	}
	else if (time_tech >= 0 && time_tech <= 50)
	{
		CString strtmp_tech;
		strtmp_tech.Format(_T("%.0fms"), time_tech);
		teacher_speed.SetWindowTextW(strtmp_tech);
		teacher_assess.SetWindowTextW(TEXT("良"));

	}

	else if (time_tech >= 0 && time_tech <= 100)
	{
		CString strtmp_tech;
		strtmp_tech.Format(_T("%.0fms"), time_tech);
		teacher_speed.SetWindowTextW(strtmp_tech);
		teacher_assess.SetWindowTextW(TEXT("较差"));
	}
	else if (time_tech >= 0&&time_tech<1000)
	{
		CString strtmp_tech;
		strtmp_tech.Format(_T("%.0fms"), time_tech);
		teacher_speed.SetWindowTextW(strtmp_tech);
		teacher_assess.SetWindowTextW(TEXT("很差"));
	}
	else
	{
		teacher_assess.SetWindowTextW(TEXT("超时"));//没链接上或者其他情况


	}





	if (time_plat >= 0 && time_plat <= 20)
	{
		CString strtmp_plat;
		strtmp_plat.Format(_T("%.0fms"), time_plat);
		plat_speed.SetWindowTextW(strtmp_plat);
		plat_assess.SetWindowTextW(TEXT("优"));
	}
	else if (time_plat >= 0 && time_plat <= 50)
	{
		CString strtmp_plat;
		strtmp_plat.Format(_T("%.0fms"), time_plat);
		plat_speed.SetWindowTextW(strtmp_plat);
		plat_assess.SetWindowTextW(TEXT("良"));

	}

	else if (time_plat >= 0 && time_plat <= 100)
	{
		CString strtmp_plat;
		strtmp_plat.Format(_T("%.0fms"), time_plat);
		plat_speed.SetWindowTextW(strtmp_plat);
		plat_assess.SetWindowTextW(TEXT("较差"));

	}

	else if (time_plat >= 0&&time_plat<1000)
	{
		CString strtmp_plat;
		strtmp_plat.Format(_T("%.0fms"), time_plat);
		plat_speed.SetWindowTextW(strtmp_plat);
		plat_assess.SetWindowTextW(TEXT("很差"));

	}
	else
	{
		plat_assess.SetWindowTextW(TEXT("超时"));//没链接上或者其他情况

	}



	if (time_audio >= 0 && time_audio <= 20)
	{
		CString strtmp_audio;
		strtmp_audio.Format(_T("%.0fms"), time_audio);
		audio_speed.SetWindowTextW(strtmp_audio);
		audio_assess.SetWindowTextW(TEXT("优"));
	}
	else if (time_audio >= 0 && time_audio <= 50)
	{
		CString strtmp_audio;
		strtmp_audio.Format(_T("%.0fms"), time_audio);
		audio_speed.SetWindowTextW(strtmp_audio);
		audio_assess.SetWindowTextW(TEXT("良"));
	}

	else if (time_audio >= 0 && time_audio <= 100)
	{
		CString strtmp_audio;
		strtmp_audio.Format(_T("%.0fms"), time_audio);
		audio_speed.SetWindowTextW(strtmp_audio);
		audio_assess.SetWindowTextW(TEXT("较差"));
	}

	else if (time_audio >= 0&&time_audio<1000)
	{
		CString strtmp_audio;
		strtmp_audio.Format(_T("%.0fms"), time_audio);
		audio_speed.SetWindowTextW(strtmp_audio);
		audio_assess.SetWindowTextW(TEXT("很差"));
	}
	else
	{
		audio_assess.SetWindowTextW(TEXT("超时"));//没链接上或者其他情况

	}





	//CDialogEx::OnOK();
}



void C测试Dlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!finum)
	{

		AfxMessageBox(_T("请先进行网络测试！"));
		return;
	}

	finum = 0;
	CDialogEx::OnCancel();
	speaker dlg;
	dlg.DoModal();


	
}


void C测试Dlg::OnStnClickedteacherspeed2()
{
	// TODO: 在此添加控件通知处理程序代码
}


void C测试Dlg::OnStnClickedteacherspeed()
{
	// TODO: 在此添加控件通知处理程序代码
}


void C测试Dlg::OnStnClickedaudiospeed()
{
	// TODO: 在此添加控件通知处理程序代码
}


void C测试Dlg::OnStnClickedaudioassess()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CAboutDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();

}
