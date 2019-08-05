#pragma once

#include "afxwin.h"
// camera 对话框
#pragma once
#include "afxwin.h"
#include<iostream>
#include "strmif.h"
#include <initguid.h>
#include<vector>
#include<string>
#include<Vfw.h>

using namespace std;

#pragma comment(lib, "vfw32")

// camera_change 对话框

class camera_change : public CDialogEx
{
	DECLARE_DYNAMIC(camera_change)

public:
	camera_change(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~camera_change();
	int  listDevices(vector<string>& list);
	HWND   m_hWndVideo; //视频显示窗口
	HBRUSH m_hMyGreen;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_camera };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSetfocusCombo1();
	CComboBox combox;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnStnClickedvedio();
	CStatic picture;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();

private:
	int finum = 0;
};
