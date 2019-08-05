// MicTest.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "����.h"
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

// CMicTest �Ի���

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


// CMicTest ��Ϣ�������

DWORD CALLBACK MicCallback(HWAVEIN hwavein, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
{
	switch (uMsg)
	{
	case WIM_OPEN://	�豸�Ѿ���
		break;

	case WIM_DATA://	����������
		waveInAddBuffer(hwavein, (LPWAVEHDR)dwParam1, sizeof(WAVEHDR));
		break;

	case WIM_CLOSE://	�豸�Ѿ��ر�
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
		LPWAVEHDR pWaveHeader = (LPWAVEHDR)dwParam1;//ϵͳ�Զ�ʶ������һ��WAVEHDR�������

		waveOutUnprepareHeader(hwo, pWaveHeader, sizeof(WAVEHDR));//�����������ô˺���

																  //�˴����WAVEHDR��lpdate����

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
	// TODO: �ڴ���ӿؼ�֪ͨ����������

}


void CMicTest::OnCbnSetfocusCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMicTest::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
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
	waveInGetDevCaps(nIndex, &waveInCaps, sizeof(waveInCaps));	//ѡ�����˷��豸
	WaveInitFormat(&pwfx, 1, 44100, 16);		//	�������Ƶ�����豸,���������������� 44.1kHz 16bit

	waveInOpen(&phwi, WAVE_MAPPER, &pwfx, (DWORD)(MicCallback), NULL, CALLBACK_FUNCTION);//����˷�

	pwh1.lpData = buffer1;
	pwh1.dwBufferLength = 10240;
	pwh1.dwUser = 1;
	pwh1.dwFlags = 0;
	waveInPrepareHeader(phwi, &pwh1, sizeof(WAVEHDR));	 //	׼�����뻺����1
			
	waveInAddBuffer(phwi, &pwh1, sizeof(WAVEHDR));	//	��������1������Ƶ�����豸
	waveInStart(phwi);		//	����ʼ¼��

	

	WaveInitFormat(&waveform, 1, 44100, 16);	//������Ƶ������豸��Ϣ
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &waveform, (DWORD_PTR)waveOutProc, NULL, CALLBACK_FUNCTION);//������Ƶ����豸

	pWaveHdr1.lpData = buffer1;//¼������ ;
	pWaveHdr1.dwBufferLength = 10240;//��������С ;
	pWaveHdr1.dwBytesRecorded = 0;
	pWaveHdr1.dwUser = 0;
	pWaveHdr1.dwFlags = WHDR_BEGINLOOP | WHDR_ENDLOOP;
	pWaveHdr1.lpNext = NULL;
	pWaveHdr1.reserved = 0;

	waveOutPrepareHeader(hWaveOut, &pWaveHdr1, sizeof(WAVEHDR));//	׼�����������1
	waveOutWrite(hWaveOut, &pWaveHdr1, sizeof(WAVEHDR));//��ʼ������


	flag = 1;
}


void CMicTest::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	int m_int = m_slider.GetPos();//ȡ�õ�ǰλ��ֵ  
	DWORD dwVolume_L = 0xffff * (m_int-1) * 0.1;
	DWORD dwVolume_R = dwVolume_L << 16;
	DWORD dwVolume = dwVolume_L + dwVolume_R;
	waveOutSetVolume(0, dwVolume);//��������
	*pResult = 0;
}



BOOL CMicTest::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_cbExample.ResetContent();
	int inputAudioDeviceNum = waveInGetNumDevs();	//�����˷��豸����
	WAVEINCAPS waveInCaps;
	for (int i = 0; i < inputAudioDeviceNum; ++i)
	{
		MMRESULT mmResult = waveInGetDevCaps(i, &waveInCaps, sizeof(waveInCaps));	//�����˷�����
		m_cbExample.AddString(waveInCaps.szPname);			//��ʾ��˷�����
	}
	m_cbExample.SetCurSel(0);//Ĭ��ѡ���һ��

	m_slider.SetRange(1, 10);//���û�����ΧΪ1��10
	m_slider.SetTicFreq(1);//ÿ1����λ��һ�̶�
	m_slider.SetPos(3);//���û����ʼλ��Ϊ3

	m_pc1.SetRange(0, 70);    //��������Χ��0��70
	m_pc1.SetPos(0);		//���ý�������ʼλ��
	UINT m_timer = (UINT)SetTimer(1, 2, NULL);
	return TRUE;
}


void CMicTest::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	UpdateData(TRUE);
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
	UpdateData(FALSE);
}


void CMicTest::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

		C����App *pApp = (C����App *)AfxGetApp();//����
		pApp->m_mic = 1;

		waveOutClose(hWaveOut);

		CDialogEx::OnOK();
		camera_change dlg;
		dlg.DoModal();
	}
	else
	{
		AfxMessageBox(_T("���Ƚ�����˷���ԣ�"));
		return;
	}
}


void CMicTest::OnNMCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CMicTest::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//����¼������
	double sumVolume = 0.0;
	double avgVolume = 0.0;
	double volume = 0.0;
	length = pwh1.dwBufferLength;
	for (int i = 0; i < length; i += 2)
	{
		int v1 = buffer1[i] & 0xFF;
		int v2 = buffer1[i + 1] & 0xFF;
		int temp = v1 + (v2 << 8);// С��
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

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void CMicTest::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

		C����App *pApp = (C����App *)AfxGetApp();//����
		pApp->m_mic = 0;

		waveOutClose(hWaveOut);

		CDialogEx::OnCancel();
		camera_change dlg;
		dlg.DoModal();
	}

	else
	{
		AfxMessageBox(_T("���Ƚ�����˷���ԣ�"));
		return;
	}
}
