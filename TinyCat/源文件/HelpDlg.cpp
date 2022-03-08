// HelpDlg.cpp: 实现文件
//

#include "pch.h"
#include "TinySQL.h"
#include "afxdialogex.h"
#include "HelpDlg.h"


// HelpDlg 对话框

IMPLEMENT_DYNAMIC(HelpDlg, CDialogEx)

HelpDlg::HelpDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HELP_DIALOG, pParent)
{

}

HelpDlg::~HelpDlg()
{
}

void HelpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(HelpDlg, CDialogEx)
END_MESSAGE_MAP()


// HelpDlg 消息处理程序
