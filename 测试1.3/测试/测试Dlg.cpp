
// ����Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "����.h"
#include "����Dlg.h"
#include "afxdialogex.h"
#include "ping.h"
#include "speaker.h"
#include <Windows.h>
#include <mmsystem.h>

#pragma comment(lib,"Winmm.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// C����Dlg �Ի���



C����Dlg::C����Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C����Dlg::DoDataExchange(CDataExchange* pDX)
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

BEGIN_MESSAGE_MAP(C����Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &C����Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &C����Dlg::OnBnClickedCancel)
//	ON_STN_CLICKED(IDC_teacher_speed2, &C����Dlg::OnStnClickedteacherspeed2)
	ON_STN_CLICKED(IDC_teacher_speed, &C����Dlg::OnStnClickedteacherspeed)
	ON_STN_CLICKED(IDC_audio_speed, &C����Dlg::OnStnClickedaudiospeed)
	ON_STN_CLICKED(IDC_audio_assess, &C����Dlg::OnStnClickedaudioassess)
END_MESSAGE_MAP()


// C����Dlg ��Ϣ�������

BOOL C����Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void C����Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void C����Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR C����Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C����Dlg::OnBnClickedOk()
{
	finum = 1;

	CPing objPing_tech;
	CPing objPing_plat;
	CPing objPing_audio;

	//����������λIP
	// ���ص�������Ӧʵ��IP�ĸ���
	int ynIpCount_tech = 0;
	int ynIpCount_plat = 0;
	int ynIpCount_audio = 0;
	// ���ص�������Ӧʵ��I�б�
	char yszIpList_tech[50][100] = {0};
	char yszIpList_plat[50][100] = {0};
	char yszIpList_audio[50][100] = {0};

	// ����
	char yszDomain_tech[256] = { 0 };
	char yszIp_tech[1024] = { 0 };
	strcpy_s(yszDomain_tech, "api.hss.aicfe.cn");
	objPing_tech.GetRealIpByDomainName(yszDomain_tech, yszIpList_tech, &ynIpCount_tech);//�ú���������������IP������������yszIpList�У�ynIpCount���IP�ĸ������е������ж��IP��
	
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


	C����App *pApp = (C����App *)AfxGetApp();//����
	pApp->m_teach = time_tech;
	pApp->m_plat = time_plat;
	pApp->m_audio = time_audio;


	if (time_tech >=0&& time_tech <= 20)
	{
		CString strtmp_tech;
		strtmp_tech.Format(_T("%.0fms"), time_tech);
		teacher_speed.SetWindowTextW(strtmp_tech);
		teacher_assess.SetWindowTextW(TEXT("��"));
	}
	else if (time_tech >= 0 && time_tech <= 50)
	{
		CString strtmp_tech;
		strtmp_tech.Format(_T("%.0fms"), time_tech);
		teacher_speed.SetWindowTextW(strtmp_tech);
		teacher_assess.SetWindowTextW(TEXT("��"));

	}

	else if (time_tech >= 0 && time_tech <= 100)
	{
		CString strtmp_tech;
		strtmp_tech.Format(_T("%.0fms"), time_tech);
		teacher_speed.SetWindowTextW(strtmp_tech);
		teacher_assess.SetWindowTextW(TEXT("�ϲ�"));
	}
	else if (time_tech >= 0&&time_tech<1000)
	{
		CString strtmp_tech;
		strtmp_tech.Format(_T("%.0fms"), time_tech);
		teacher_speed.SetWindowTextW(strtmp_tech);
		teacher_assess.SetWindowTextW(TEXT("�ܲ�"));
	}
	else
	{
		teacher_assess.SetWindowTextW(TEXT("��ʱ"));//û�����ϻ����������


	}





	if (time_plat >= 0 && time_plat <= 20)
	{
		CString strtmp_plat;
		strtmp_plat.Format(_T("%.0fms"), time_plat);
		plat_speed.SetWindowTextW(strtmp_plat);
		plat_assess.SetWindowTextW(TEXT("��"));
	}
	else if (time_plat >= 0 && time_plat <= 50)
	{
		CString strtmp_plat;
		strtmp_plat.Format(_T("%.0fms"), time_plat);
		plat_speed.SetWindowTextW(strtmp_plat);
		plat_assess.SetWindowTextW(TEXT("��"));

	}

	else if (time_plat >= 0 && time_plat <= 100)
	{
		CString strtmp_plat;
		strtmp_plat.Format(_T("%.0fms"), time_plat);
		plat_speed.SetWindowTextW(strtmp_plat);
		plat_assess.SetWindowTextW(TEXT("�ϲ�"));

	}

	else if (time_plat >= 0&&time_plat<1000)
	{
		CString strtmp_plat;
		strtmp_plat.Format(_T("%.0fms"), time_plat);
		plat_speed.SetWindowTextW(strtmp_plat);
		plat_assess.SetWindowTextW(TEXT("�ܲ�"));

	}
	else
	{
		plat_assess.SetWindowTextW(TEXT("��ʱ"));//û�����ϻ����������

	}



	if (time_audio >= 0 && time_audio <= 20)
	{
		CString strtmp_audio;
		strtmp_audio.Format(_T("%.0fms"), time_audio);
		audio_speed.SetWindowTextW(strtmp_audio);
		audio_assess.SetWindowTextW(TEXT("��"));
	}
	else if (time_audio >= 0 && time_audio <= 50)
	{
		CString strtmp_audio;
		strtmp_audio.Format(_T("%.0fms"), time_audio);
		audio_speed.SetWindowTextW(strtmp_audio);
		audio_assess.SetWindowTextW(TEXT("��"));
	}

	else if (time_audio >= 0 && time_audio <= 100)
	{
		CString strtmp_audio;
		strtmp_audio.Format(_T("%.0fms"), time_audio);
		audio_speed.SetWindowTextW(strtmp_audio);
		audio_assess.SetWindowTextW(TEXT("�ϲ�"));
	}

	else if (time_audio >= 0&&time_audio<1000)
	{
		CString strtmp_audio;
		strtmp_audio.Format(_T("%.0fms"), time_audio);
		audio_speed.SetWindowTextW(strtmp_audio);
		audio_assess.SetWindowTextW(TEXT("�ܲ�"));
	}
	else
	{
		audio_assess.SetWindowTextW(TEXT("��ʱ"));//û�����ϻ����������

	}





	//CDialogEx::OnOK();
}



void C����Dlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!finum)
	{

		AfxMessageBox(_T("���Ƚ���������ԣ�"));
		return;
	}

	finum = 0;
	CDialogEx::OnCancel();
	speaker dlg;
	dlg.DoModal();


	
}


void C����Dlg::OnStnClickedteacherspeed2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void C����Dlg::OnStnClickedteacherspeed()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void C����Dlg::OnStnClickedaudiospeed()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void C����Dlg::OnStnClickedaudioassess()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CAboutDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();

}
