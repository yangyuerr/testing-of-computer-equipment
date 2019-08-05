#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include <cmath>
#include <windows.h>
#include <iostream>
#include "mmsystem.h"
#pragma comment(lib, "winmm.lib")


// CMicTest 对话框

class CMicTest : public CDialogEx
{
	DECLARE_DYNAMIC(CMicTest)

private:
	int flag = 0;
	int nIndex;
	HWAVEIN phwi;
	WAVEFORMATEX pwfx;
	char buffer1[10240];
	WAVEHDR pwh1;
	HWAVEOUT hWaveOut;
	WAVEFORMATEX waveform;
	WAVEHDR pWaveHdr1; 
	int length;
	int finum = 0;
public:
	CMicTest(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMicTest();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MicTest };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeCombo1();
	CComboBox m_cbExample;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnCbnSetfocusCombo1();
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_slider;
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedOk();
	afx_msg void OnNMCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult);
	CProgressCtrl m_pc1;

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedCancel();
};
