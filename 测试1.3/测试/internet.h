#pragma once
#include "ping.h"

// internet �Ի���

class internet : public CDialogEx
{
	DECLARE_DYNAMIC(internet)

public:
	internet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~internet();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
