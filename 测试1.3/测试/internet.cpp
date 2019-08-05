// internet.cpp : 实现文件
//

#include "stdafx.h"
#include "测试.h"
#include "internet.h"
#include "afxdialogex.h"
#include "ping.h"

// internet 对话框

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


// internet 消息处理程序


void internet::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void internet::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
