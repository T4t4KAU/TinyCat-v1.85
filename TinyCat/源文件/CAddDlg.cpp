// CAddDlg.cpp: 实现文件
//

#include "pch.h"
#include "TinySQL.h"
#include "afxdialogex.h"
#include "CAddDlg.h"


// CAddDlg 对话框

IMPLEMENT_DYNAMIC(CAddDlg, CDialogEx)

CAddDlg::CAddDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADD_DIALOG, pParent)
	, m_strColumnName(_T(""))
	, m_strDataType(_T(""))
	, m_strTableName(_T(""))
{

}

CAddDlg::~CAddDlg()
{
}

void CAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TABLE, m_strColumnName);
	DDX_Control(pDX, IDC_COLUMN_LIST, m_List);
	DDX_Control(pDX, IDC_DATATYPE, m_DataType);
	DDX_CBString(pDX, IDC_DATATYPE, m_strDataType);
	DDX_Text(pDX, IDC_EDIT1, m_strTableName);
}


BEGIN_MESSAGE_MAP(CAddDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAddDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_ADD_DATA, &CAddDlg::OnBnClickedAddData)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CAddDlg 消息处理程序


// 点击确认后添加数据
void CAddDlg::OnBnClickedOk()
{
	
	CDialogEx::OnOK();
}

// 点击添加 将新的字段加入
void CAddDlg::OnBnClickedAddData()
{
	UpdateData(TRUE);
	
	if (m_strColumnName == "")
		return;
	if (m_strDataType == "")
		return;
	m_List.InsertItem(m_nColumnCount, m_strColumnName);
	m_List.SetItemText(m_nColumnCount, 1, m_strDataType);
	m_nColumnCount++;
	CString strText;
	strText.Format("%s %s,", m_strColumnName.GetBuffer(), m_strDataType.GetBuffer());
	m_strColumns += strText;
}


void CAddDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	m_List.SetExtendedStyle(LVS_EX_AUTOSIZECOLUMNS | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_List.InsertColumn(0, "列名", LVCFMT_LEFT, 100);
	m_List.InsertColumn(1, "数据类型", LVCFMT_LEFT, 100);
	m_nColumnCount = 0;
	m_strColumns = "";
}
