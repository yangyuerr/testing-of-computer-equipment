// internet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "����.h"
#include "internet.h"
#include "afxdialogex.h"
#include "ping.h"

// internet �Ի���

IMPLEMENT_DYNAMIC(internet, CDialogEx)

internet::internet(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY_DIALOG, pParent)
{

}

internet::~internet()
{
}

void internet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(internet, CDialogEx)
	ON_BN_CLICKED(IDOK, &internet::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &internet::OnBnClickedCancel)
END_MESSAGE_MAP()


// internet ��Ϣ�������


void internet::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


void internet::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
