
// ����Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// C����Dlg �Ի���
class C����Dlg : public CDialogEx
{
// ����
public:
	C����Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
