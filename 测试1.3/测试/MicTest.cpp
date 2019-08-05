// MicTest.cpp : 实现文件
//

#include "stdafx.h"
#include "测试.h"
#include "MicTest.h"
#include "afxdialogex.h"
#include <cmath>
#include <windows.h>
#include <iostream>
#include "mmsystem.h"
#include "camera_change.h"
#pragma comment(lib, "winmm.lib")
void WaveInitFormat(LPWAVEFORMATEX m_WaveFormat, WORD nCh, DWORD nSampleRate, WORD BitsPerSample);
DWORD CALLBACK MicCallback(HWAVEIN hwavein, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2);

// CMicTest 对话框

IMPLEMENT_DYNAMIC(CMicTest, CDialogEx)

CMicTest::CMicTest(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MicTest, pParent)
{

}

CMicTest::~CMicTest()
{
}

void CMicTest::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cbExample);
	DDX_Control(pDX, IDC_SLIDER1, m_slider);
	DDX_Control(pDX, IDC_PROGRESS1, m_pc1);
}


BEGIN_MESSAGE_MAP(CMicTest, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMicTest::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CMicTest::OnBnClickedButton1)
	ON_CBN_SETFOCUS(IDC_COMBO1, &CMicTest::OnCbnSetfocusCombo1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CMicTest::OnNMCustomdrawSlider1)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDOK, &CMicTest::OnBnClickedOk)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_PROGRESS1, &CMicTest::OnNMCustomdrawProgress1)
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDCANCEL, &CMicTest::OnBnClickedCancel)
END_MESSAGE_MAP()


// CMicTest 消息处理程序

DWORD CALLBACK MicCallback(HWAVEIN hwavein, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
{
	switch (uMsg)
	{
	case WIM_OPEN://	设备已经打开
		break;

	case WIM_DATA://	缓冲区存满
		waveInAddBuffer(hwavein, (LPWAVEHDR)dwParam1, sizeof(WAVEHDR));
		break;

	case WIM_CLOSE://	设备已经关闭
		waveInStop(hwavein);
		waveInReset(hwavein);
		waveInClose(hwavein);
		break;
	default:
		break;
	}
	return 0;
}

void CALLBACK waveOutProc(HWAVEOUT hwo,
	UINT uMsg,
	DWORD dwInstance,
	DWORD dwParam1,
	DWORD dwParam2)
{
	if (uMsg == WOM_DONE)
	{
		LPWAVEHDR pWaveHeader = (LPWAVEHDR)dwParam1;//系统自动识别是哪一个WAVEHDR播放完毕

		waveOutUnprepareHeader(hwo, pWaveHeader, sizeof(WAVEHDR));//播放完后须调用此函数

																  //此处填充WAVEHDR的lpdate缓冲

		waveOutPrepareHeader(hwo, pWaveHeader, sizeof(WAVEHDR));
		waveOutWrite(hwo, pWaveHeader, sizeof(WAVEHDR));
	}
	return;
}

void WaveInitFormat(LPWAVEFORMATEX m_WaveFormat, WORD nCh, DWORD nSampleRate, WORD BitsPerSample)
{
	m_WaveFormat->wFormatTag = WAVE_FORMAT_PCM;
	m_WaveFormat->nChannels = nCh;
	m_WaveFormat->nSamplesPerSec = nSampleRate;
	m_WaveFormat->nAvgBytesPerSec = m_WaveFormat->nBlockAlign * m_WaveFormat->nSamplesPerSec;
	m_WaveFormat->nBlockAlign = m_WaveFormat->nChannels * BitsPerSample / 8;
	m_WaveFormat->wBitsPerSample = BitsPerSample;
	m_WaveFormat->cbSize = 0;
	return;
}

void CMicTest::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码

}


void CMicTest::OnCbnSetfocusCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CMicTest::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	
	finum = 1;
	nIndex = m_cbExample.GetCurSel();
	if (nIndex == -1)
	{
		return;
	}

	if (flag)
	{
		waveOutClose(hWaveOut);
		Sleep(500);
	}

	WAVEINCAPS waveInCaps;
	waveInGetDevCaps(nIndex, &waveInCaps, sizeof(waveInCaps));	//选择的麦克风设备
	WaveInitFormat(&pwfx, 1, 44100, 16);		//	请求打开音频输入设备,采样参数：单声道 44.1kHz 16bit

	waveInOpen(&phwi, WAVE_MAPPER, &pwfx, (DWORD)(MicCallback), NULL, CALLBACK_FUNCTION);//打开麦克风

	pwh1.lpData = buffer1;
	pwh1.dwBufferLength = 10240;
	pwh1.dwUser = 1;
	pwh1.dwFlags = 0;
	waveInPrepareHeader(phwi, &pwh1, sizeof(WAVEHDR));	 //	准备输入缓冲区1
			
	waveInAddBuffer(phwi, &pwh1, sizeof(WAVEHDR));	//	将缓冲区1加入音频输入设备
	waveInStart(phwi);		//	请求开始录音

	

	WaveInitFormat(&waveform, 1, 44100, 16);	//定义音频流相关设备信息
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &waveform, (DWORD_PTR)waveOutProc, NULL, CALLBACK_FUNCTION);//启动音频输出设备

	pWaveHdr1.lpData = buffer1;//录音数据 ;
	pWaveHdr1.dwBufferLength = 10240;//缓冲区大小 ;
	pWaveHdr1.dwBytesRecorded = 0;
	pWaveHdr1.dwUser = 0;
	pWaveHdr1.dwFlags = WHDR_BEGINLOOP | WHDR_ENDLOOP;
	pWaveHdr1.lpNext = NULL;
	pWaveHdr1.reserved = 0;

	waveOutPrepareHeader(hWaveOut, &pWaveHdr1, sizeof(WAVEHDR));//	准备输出缓冲区1
	waveOutWrite(hWaveOut, &pWaveHdr1, sizeof(WAVEHDR));//开始放声音


	flag = 1;
}


void CMicTest::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	int m_int = m_slider.GetPos();//取得当前位置值  
	DWORD dwVolume_L = 0xffff * (m_int-1) * 0.1;
	DWORD dwVolume_R = dwVolume_L << 16;
	DWORD dwVolume = dwVolume_L + dwVolume_R;
	waveOutSetVolume(0, dwVolume);//设置音量
	*pResult = 0;
}



BOOL CMicTest::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_cbExample.ResetContent();
	int inputAudioDeviceNum = waveInGetNumDevs();	//获得麦克风设备数量
	WAVEINCAPS waveInCaps;
	for (int i = 0; i < inputAudioDeviceNum; ++i)
	{
		MMRESULT mmResult = waveInGetDevCaps(i, &waveInCaps, sizeof(waveInCaps));	//获得麦克风名称
		m_cbExample.AddString(waveInCaps.szPname);			//显示麦克风名称
	}
	m_cbExample.SetCurSel(0);//默认选择第一个

	m_slider.SetRange(1, 10);//设置滑动范围为1到10
	m_slider.SetTicFreq(1);//每1个单位画一刻度
	m_slider.SetPos(3);//设置滑块初始位置为3

	m_pc1.SetRange(0, 70);    //进度条范围是0到70
	m_pc1.SetPos(0);		//设置进度条初始位置
	UINT m_timer = (UINT)SetTimer(1, 2, NULL);
	return TRUE;
}


void CMicTest::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	UpdateData(TRUE);
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
	UpdateData(FALSE);
}


void CMicTest::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if (finum == 1)
	{
		for (int i = 0; i < 10240; i++)
		{
			buffer1[i] = 0;
		}
		waveInUnprepareHeader(phwi, &pwh1, sizeof(WAVEHDR));
		waveInStop(phwi);
		waveOutUnprepareHeader(hWaveOut, &pWaveHdr1, sizeof(WAVEHDR));
		waveOutClose(hWaveOut);

		C测试App *pApp = (C测试App *)AfxGetApp();//保存
		pApp->m_mic = 1;

		waveOutClose(hWaveOut);

		CDialogEx::OnOK();
		camera_change dlg;
		dlg.DoModal();
	}
	else
	{
		AfxMessageBox(_T("请先进行麦克风测试！"));
		return;
	}
}


void CMicTest::OnNMCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CMicTest::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//计算录音音量
	double sumVolume = 0.0;
	double avgVolume = 0.0;
	double volume = 0.0;
	length = pwh1.dwBufferLength;
	for (int i = 0; i < length; i += 2)
	{
		int v1 = buffer1[i] & 0xFF;
		int v2 = buffer1[i + 1] & 0xFF;
		int temp = v1 + (v2 << 8);// 小端
		if (temp >= 0x8000)
		{
			temp = 0xffff - temp;
		}
		sumVolume += abs(temp);
	}
	avgVolume = sumVolume / length / 2.0;
	volume = 10.0 * log10(1.0 + avgVolume);

	m_pc1.SetPos((int)volume);
	CDialogEx::OnTimer(nIDEvent);
}


HBRUSH CMicTest::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CMicTest::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	if (finum == 1)
	{
		for (int i = 0; i < 10240; i++)
		{
			buffer1[i] = 0;
		}
		waveInUnprepareHeader(phwi, &pwh1, sizeof(WAVEHDR));
		waveInStop(phwi);
		waveOutUnprepareHeader(hWaveOut, &pWaveHdr1, sizeof(WAVEHDR));
		waveOutClose(hWaveOut);

		C测试App *pApp = (C测试App *)AfxGetApp();//保存
		pApp->m_mic = 0;

		waveOutClose(hWaveOut);

		CDialogEx::OnCancel();
		camera_change dlg;
		dlg.DoModal();
	}

	else
	{
		AfxMessageBox(_T("请先进行麦克风测试！"));
		return;
	}
}
