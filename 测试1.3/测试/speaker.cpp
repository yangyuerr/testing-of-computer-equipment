// speaker.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include <iostream>
#include "����.h"
#include "speaker.h"
#include "resource.h"

#include "afxdialogex.h"
#include "internet.h"
#include <Windows.h>
#include "mmsystem.h"
#include "MicTest.h"


#pragma comment(lib,"Winmm.lib")

using namespace std;



// speaker �Ի���

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


// speaker ��Ϣ�������





void speaker::OnNMCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}





void speaker::OnCbnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������


}


void speaker::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int m_int = volslider.GetPos();//ȡ�õ�ǰλ��ֵ  
	DWORD dwVolume_L = 0xffff * (m_int - 1) * 0.1;
	DWORD dwVolume_R = dwVolume_L << 16;
	DWORD dwVolume = dwVolume_L + dwVolume_R;
	waveOutSetVolume(0, dwVolume);//��������

	*pResult = 0;
}


void speaker::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!finum)
	{
		AfxMessageBox(_T("���Ƚ������������ԣ�"));
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
	C����App *pApp = (C����App *)AfxGetApp();//����
	pApp->m_speaker = 1;
	CDialogEx::OnOK();
	CMicTest dlg;
	dlg.DoModal();
}


void speaker::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!finum)
	{
		AfxMessageBox(_T("���Ƚ������������ԣ�"));
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
	C����App *pApp = (C����App *)AfxGetApp();//����
	pApp->m_speaker = 0;
	CDialogEx::OnOK();
	CMicTest dlg;
	dlg.DoModal();
}


void speaker::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//ѡ��һ����������ȡ����Ϣ
	//�����ж��ڴ��Ƿ��ͷ�
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

	//��ѡ�е�������
	if (waveOutOpen(&hWaveOut, numlist, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR) {
		return;
	}

	block = loadAudioBlock(TEXT("../SoundTest.wav"), &size);
	writeAudioBlock(hWaveOut, block, size, header);
	UINT m_timer = (UINT)SetTimer(1, 14, NULL);
}


void speaker::OnCbnSetfocusCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	spelist.ResetContent(); //��������˵�

	WAVEOUTCAPS woc;
	int numdevs = waveOutGetNumDevs();//��ȡ�������豸��

									  //��ȡ�������豸��Ϣ����ӵ������˵���
	for (int i = 0; i < numdevs; i++)
	{
		waveOutGetDevCaps(i, &woc, sizeof(WAVEOUTCAPS));
		spelist.AddString(woc.szPname);
		//	spelist.AddString(_T("������/��Ͳ (Internal High Definition Audio Bus)"));
	}
	//Ĭ��ѡ���һ��
	spelist.SetCurSel(0);
}

//��ȡ��Ƶ���ݿ�
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

//���������ݿ�д����Ƶ�豸
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	volslider.SetRange(1, 10);//���û�����ΧΪ1��10
	volslider.SetTicFreq(1);//ÿ1����λ��һ�̶�
	volslider.SetPos(3);//���û����ʼλ��Ϊ1 

	spepro.SetRange(0, 60);    //��������Χ��0��60
	spepro.SetPos(0);
//	UINT m_timer = (UINT)SetTimer(1, 14, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void speaker::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (numflg > 398)
	{
		spepro.SetPos(0);
	}
	else
	{
		double sumVolume = 0.0;
		double avgVolume = 0.0;
		double volume = 0.0;
		//ÿ��10ms����һ������ƽ��ֵ
		int num = size / 400;

		for (int i = 0; i < num; i += 2)
		{
			int v1 = block[num*numflg + i] & 0xFF;
			int v2 = block[num*numflg + i + 1] & 0xFF;
			int temp = v1 + (v2 << 8);// С��
			if (temp >= 0x8000)
			{
				temp = 0xffff - temp;
			}
			sumVolume += abs(temp);
		}

		numflg++;
		//������ȥһ����Сֵ�ԼӴ����ֶ�
		avgVolume = sumVolume / (num/2)-270;//260
		//��������ֱ�
		volume = 10.0 * log10(1.0 + avgVolume);
		//��С�����
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
