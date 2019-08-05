#pragma once
#include "ping.h"

// internet 对话框

class internet : public CDialogEx
{
	DECLARE_DYNAMIC(internet)

public:
	internet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~internet();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
