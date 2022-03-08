// CEditDlg.cpp: 实现文件
//

#include "pch.h"
#include "TinySQL.h"
#include "afxdialogex.h"
#include "CEditDlg.h"


// CEditDlg 对话框

IMPLEMENT_DYNAMIC(CEditDlg, CDialogEx)

CEditDlg::CEditDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EDIT, pParent)
	, m_strEdit(_T(""))
	, m_strInfo(_T(""))
{
	m_bUpdate = FALSE;
}

CEditDlg::~CEditDlg()
{
}

void CEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT, m_strEdit);
	DDX_Text(pDX, IDC_TEXT, m_strInfo);
}


BEGIN_MESSAGE_MAP(CEditDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CEditDlg::OnBnClickedOk)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDCANCEL, &CEditDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CEditDlg 消息处理程序


void CEditDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	if (m_strEdit == "")
	{
		AfxMessageBox("空字符串!");
		m_bUpdate = FALSE;
	}
	else
		m_bUpdate = TRUE;
	CDialogEx::OnOK();
}


void CEditDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	UpdateData(TRUE);
	UpdateData(FALSE);
}


void CEditDlg::OnBnClickedCancel()
{
	m_bUpdate = FALSE;
	CDialogEx::OnCancel();
}
