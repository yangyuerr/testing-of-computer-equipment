#pragma once
#include "afxwin.h"


// conclusion �Ի���

class conclusion : public CDialogEx
{
	DECLARE_DYNAMIC(conclusion)

public:
	conclusion(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~conclusion();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_sum };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CStatic teache_speed;
	CStatic teache_assess;
	CStatic plat_speed;
	CStatic plat_assess;
	CStatic audio_speed;
	CStatic audio_assess;
	CStatic speaker;
	CStatic mic;
	CStatic camera;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	CStatic sum;
};
