#pragma once

#include "afxwin.h"
// camera �Ի���
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

// camera_change �Ի���

class camera_change : public CDialogEx
{
	DECLARE_DYNAMIC(camera_change)

public:
	camera_change(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~camera_change();
	int  listDevices(vector<string>& list);
	HWND   m_hWndVideo; //��Ƶ��ʾ����
	HBRUSH m_hMyGreen;

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_camera };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
