// conclusion.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "����.h"
#include "conclusion.h"
#include "afxdialogex.h"


// conclusion �Ի���

IMPLEMENT_DYNAMIC(conclusion, CDialogEx)

conclusion::conclusion(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_sum, pParent)
{

}

conclusion::~conclusion()
{
}

void conclusion::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_teache_speed, teache_speed);
	DDX_Control(pDX, IDC_teache_assess, teache_assess);
	DDX_Control(pDX, IDC_plat_speed, plat_speed);
	DDX_Control(pDX, IDC_plat_assess, plat_assess);
	DDX_Control(pDX, IDC_audio_speed, audio_speed);
	DDX_Control(pDX, IDC_audio_assess, audio_assess);
	DDX_Control(pDX, IDC_speaker, speaker);
	DDX_Control(pDX, IDC_mic, mic);
	DDX_Control(pDX, IDC_camera, camera);
	DDX_Control(pDX, IDC_sum, sum);
}


BEGIN_MESSAGE_MAP(conclusion, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &conclusion::OnBnClickedButton1)
END_MESSAGE_MAP()


// conclusion ��Ϣ�������


BOOL conclusion::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��


	C����App *pApp = (C����App *)AfxGetApp();//����
	
	float time_tech;
	float time_plat;
	float time_audio;
	time_tech = pApp->m_teach;
	time_plat = pApp->m_plat;
	time_audio = pApp->m_audio;
	
	if (time_tech >= 0 && time_tech <= 20)
	{
		CString strtmp_tech;
		strtmp_tech.Format(_T("%.0fms"), time_tech);
		teache_speed.SetWindowTextW(strtmp_tech);
		teache_assess.SetWindowTextW(TEXT("��"));
	}
	else if (time_tech >= 0 && time_tech <= 50)
	{
		CString strtmp_tech;
		strtmp_tech.Format(_T("%.0fms"), time_tech);
		teache_speed.SetWindowTextW(strtmp_tech);
		teache_assess.SetWindowTextW(TEXT("��"));

	}

	else if (time_tech >= 0 && time_tech <= 100)
	{
		CString strtmp_tech;
		strtmp_tech.Format(_T("%.0fms"), time_tech);
		teache_speed.SetWindowTextW(strtmp_tech);
		teache_assess.SetWindowTextW(TEXT("�ϲ�"));
	}
	else if (time_tech >= 0&&time_tech<1000)
	{
		CString strtmp_tech;
		strtmp_tech.Format(_T("%.0fms"), time_tech);
		teache_speed.SetWindowTextW(strtmp_tech);
		teache_assess.SetWindowTextW(TEXT("�ܲ�"));
	}
	else
	{
		teache_assess.SetWindowTextW(TEXT("��ʱ"));//û�����ϻ����������


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


	if (pApp->m_speaker == 0)
	{
		speaker.SetWindowTextW(TEXT("error"));
	}
	else
	{
		speaker.SetWindowTextW(TEXT("right"));
	}


	if (pApp->m_mic == 0)
	{
		mic.SetWindowTextW(TEXT("error"));
	}
	else
	{
		mic.SetWindowTextW(TEXT("right"));
	}
	if (pApp->m_camera == 0)
	{
		camera.SetWindowTextW(TEXT("error"));
	}
	else
	{
		camera.SetWindowTextW(TEXT("right"));
	}



	if (time_tech > 1000 || time_plat > 1000 || time_audio > 1000 || pApp->m_mic == 0 || pApp->m_speaker == 0 || pApp->m_camera == 0)

	{
		sum.SetWindowTextW(TEXT("�豸���δͨ��"));
	}
	else
	{
		sum.SetWindowTextW(TEXT("�豸����"));
	}








	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void conclusion::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
