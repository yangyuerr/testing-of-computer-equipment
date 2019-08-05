// speaker.cpp : 实现文件
//

#include "stdafx.h"
#include <iostream>
#include "测试.h"
#include "speaker.h"
#include "resource.h"

#include "afxdialogex.h"
#include "internet.h"
#include <Windows.h>
#include "mmsystem.h"
#include "MicTest.h"


#pragma comment(lib,"Winmm.lib")

using namespace std;



// speaker 对话框

IMPLEMENT_DYNAMIC(speaker, CDialogEx)

speaker::speaker(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SPEAKER, pParent)
{

}

speaker::~speaker()
{
}

void speaker::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, spelist);
	DDX_Control(pDX, IDC_SLIDER1, volslider);
	DDX_Control(pDX, IDC_PROGRESS1, spepro);
}


BEGIN_MESSAGE_MAP(speaker, CDialogEx)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_PROGRESS1, &speaker::OnNMCustomdrawProgress1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &speaker::OnCbnSelchangeCombo1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &speaker::OnNMCustomdrawSlider1)
	ON_BN_CLICKED(IDC_BUTTON1, &speaker::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &speaker::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &speaker::OnBnClickedButton3)
	ON_CBN_SETFOCUS(IDC_COMBO1, &speaker::OnCbnSetfocusCombo1)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// speaker 消息处理程序





void speaker::OnNMCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}





void speaker::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码


}


void speaker::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int m_int = volslider.GetPos();//取得当前位置值  
	DWORD dwVolume_L = 0xffff * (m_int - 1) * 0.1;
	DWORD dwVolume_R = dwVolume_L << 16;
	DWORD dwVolume = dwVolume_L + dwVolume_R;
	waveOutSetVolume(0, dwVolume);//设置音量

	*pResult = 0;
}


void speaker::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!finum)
	{
		AfxMessageBox(_T("请先进行扬声器测试！"));
		return;
	}

	if (!flag)
	{
		KillTimer(1);
		flag = 1;
		waveOutReset(hWaveOut);
		waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		HeapFree(GetProcessHeap(), 0, block);
		waveOutClose(hWaveOut);
	}
	
	finum = 0;
	C测试App *pApp = (C测试App *)AfxGetApp();//保存
	pApp->m_speaker = 1;
	CDialogEx::OnOK();
	CMicTest dlg;
	dlg.DoModal();
}


void speaker::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!finum)
	{
		AfxMessageBox(_T("请先进行扬声器测试！"));
		return;
	}

	if (!flag)
	{
		KillTimer(1);
		flag = 1;
		waveOutReset(hWaveOut);
		waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		HeapFree(GetProcessHeap(), 0, block);
		waveOutClose(hWaveOut);
	}

	finum = 0;
	C测试App *pApp = (C测试App *)AfxGetApp();//保存
	pApp->m_speaker = 0;
	CDialogEx::OnOK();
	CMicTest dlg;
	dlg.DoModal();
}


void speaker::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码

	//选择一个扬声器获取其信息
	//首先判断内存是否释放
	if (!flag)
	{
		flag = 1;
		waveOutReset(hWaveOut);
		waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		KillTimer(1);
		HeapFree(GetProcessHeap(), 0, block);
		waveOutClose(hWaveOut);
	}

	UINT numlist = spelist.GetCurSel();
	if (numlist == -1)
	{
		return;
	}

	flag = 0;
	numflg = 0;
	finum = 1;

//	waveOutGetDevCaps(numlist-1, &woc, sizeof(WAVEOUTCAPS));

	wfx.nSamplesPerSec = 4000; 
	wfx.wBitsPerSample = 16; 
	wfx.nChannels = 2; 

	wfx.cbSize = 0;
	wfx.wFormatTag = WAVE_FORMAT_PCM;
	wfx.nBlockAlign = (wfx.wBitsPerSample >> 3) * wfx.nChannels;
	wfx.nAvgBytesPerSec = wfx.nBlockAlign * wfx.nSamplesPerSec;

	//打开选中的扬声器
	if (waveOutOpen(&hWaveOut, numlist, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR) {
		return;
	}

	block = loadAudioBlock(TEXT("../SoundTest.wav"), &size);
	writeAudioBlock(hWaveOut, block, size, header);
	UINT m_timer = (UINT)SetTimer(1, 14, NULL);
}


void speaker::OnCbnSetfocusCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	spelist.ResetContent(); //清空下拉菜单

	WAVEOUTCAPS woc;
	int numdevs = waveOutGetNumDevs();//读取扬声器设备数

									  //获取扬声器设备信息并添加到下拉菜单中
	for (int i = 0; i < numdevs; i++)
	{
		waveOutGetDevCaps(i, &woc, sizeof(WAVEOUTCAPS));
		spelist.AddString(woc.szPname);
		//	spelist.AddString(_T("扬声器/听筒 (Internal High Definition Audio Bus)"));
	}
	//默认选择第一项
	spelist.SetCurSel(0);
}

//提取音频数据块
LPSTR speaker::loadAudioBlock(LPCTSTR filename, DWORD* blockSize)
{
	HANDLE hFile = INVALID_HANDLE_VALUE;
	DWORD size = 0;
	DWORD readBytes = 0;
	void* block = NULL;
	if ((hFile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL)) == INVALID_HANDLE_VALUE)
	{
		return NULL;
	}
	do
	{
		if ((size = GetFileSize(hFile, NULL)) == 0)
		{
			break;
		}
		if ((block = HeapAlloc(GetProcessHeap(), 0, size)) == NULL)
		{
			break;
		}
		ReadFile(hFile, block, size, &readBytes, NULL);
	} while (0);
	CloseHandle(hFile);
	*blockSize = size;
	return (LPSTR)block;
}

//将音乐数据块写入音频设备
void speaker::writeAudioBlock(HWAVEOUT hWaveOut, LPSTR block, DWORD size, WAVEHDR& header)
{
	ZeroMemory(&header, sizeof(WAVEHDR));
	header.dwBufferLength = size;
	header.lpData = block;

	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	Sleep(500);
}

BOOL speaker::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	volslider.SetRange(1, 10);//设置滑动范围为1到10
	volslider.SetTicFreq(1);//每1个单位画一刻度
	volslider.SetPos(3);//设置滑块初始位置为1 

	spepro.SetRange(0, 60);    //进度条范围是0到60
	spepro.SetPos(0);
//	UINT m_timer = (UINT)SetTimer(1, 14, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void speaker::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (numflg > 398)
	{
		spepro.SetPos(0);
	}
	else
	{
		double sumVolume = 0.0;
		double avgVolume = 0.0;
		double volume = 0.0;
		//每隔10ms计算一次音量平均值
		int num = size / 400;

		for (int i = 0; i < num; i += 2)
		{
			int v1 = block[num*numflg + i] & 0xFF;
			int v2 = block[num*numflg + i + 1] & 0xFF;
			int temp = v1 + (v2 << 8);// 小端
			if (temp >= 0x8000)
			{
				temp = 0xffff - temp;
			}
			sumVolume += abs(temp);
		}

		numflg++;
		//音量减去一个较小值以加大区分度
		avgVolume = sumVolume / (num/2)-270;//260
		//求出声音分贝
		volume = 10.0 * log10(1.0 + avgVolume);
		//最小最大处理
		if (volume <= 0)
		{
			volume = 0;
		}
		if (volume >= 60)
		{
			volume = 60;
		}

		spepro.SetPos((int)volume);
	}
	
	CDialogEx::OnTimer(nIDEvent);
}
