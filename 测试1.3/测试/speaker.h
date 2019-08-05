#pragma once
#include "afxwin.h"
#include <Windows.h>
#include <mmsystem.h>
#include "afxcmn.h"

#pragma comment(lib,"Winmm.lib")


// speaker 对话框

class speaker : public CDialogEx
{
	DECLARE_DYNAMIC(speaker)

public:
	speaker(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~speaker();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SPEAKER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	CComboBox spelist;
	afx_msg void OnCbnSetfocusCombo1();
	LPSTR loadAudioBlock(LPCTSTR filename, DWORD* blockSize);
	void writeAudioBlock(HWAVEOUT hWaveOut, LPSTR block, DWORD size, WAVEHDR& header);
private:
	WAVEOUTCAPS woc;
	HWAVEOUT hWaveOut;
	WAVEFORMATEX wfx;
	DWORD size = 0;
	LPSTR block;
	WAVEHDR header;
	int flag = 1;
	int numflg = 0;
	int numflg2 = 0;
	int finum = 0;
public:
	virtual BOOL OnInitDialog();
	CSliderCtrl volslider;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CProgressCtrl spepro;
};
