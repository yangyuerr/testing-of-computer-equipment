
// 测试Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// C测试Dlg 对话框
class C测试Dlg : public CDialogEx
{
// 构造
public:
	C测试Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CStatic teacher_speed;
	afx_msg void OnStnClickedteacherspeed2();
	afx_msg void OnStnClickedteacherspeed();
	CStatic teacher_assess;
	CStatic plat_speed;
	CStatic plat_assess;
	CStatic audio_speed;
	CStatic audio;
	CStatic audio_assess;
	afx_msg void OnStnClickedaudiospeed();
	afx_msg void OnStnClickedaudioassess();

private:
	int finum = 0;
};
