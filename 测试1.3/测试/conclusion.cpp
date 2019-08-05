// conclusion.cpp : 实现文件
//

#include "stdafx.h"
#include "测试.h"
#include "conclusion.h"
#include "afxdialogex.h"


// conclusion 对话框

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


// conclusion 消息处理程序


BOOL conclusion::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化


	C测试App *pApp = (C测试App *)AfxGetApp();//保存
	
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
		teache_assess.SetWindowTextW(TEXT("优"));
	}
	else if (time_tech >= 0 && time_tech <= 50)
	{
		CString strtmp_tech;
		strtmp_tech.Format(_T("%.0fms"), time_tech);
		teache_speed.SetWindowTextW(strtmp_tech);
		teache_assess.SetWindowTextW(TEXT("良"));

	}

	else if (time_tech >= 0 && time_tech <= 100)
	{
		CString strtmp_tech;
		strtmp_tech.Format(_T("%.0fms"), time_tech);
		teache_speed.SetWindowTextW(strtmp_tech);
		teache_assess.SetWindowTextW(TEXT("较差"));
	}
	else if (time_tech >= 0&&time_tech<1000)
	{
		CString strtmp_tech;
		strtmp_tech.Format(_T("%.0fms"), time_tech);
		teache_speed.SetWindowTextW(strtmp_tech);
		teache_assess.SetWindowTextW(TEXT("很差"));
	}
	else
	{
		teache_assess.SetWindowTextW(TEXT("超时"));//没链接上或者其他情况


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
		sum.SetWindowTextW(TEXT("设备检测未通过"));
	}
	else
	{
		sum.SetWindowTextW(TEXT("设备正常"));
	}








	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void conclusion::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
