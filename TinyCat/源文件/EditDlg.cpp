// EditDlg.cpp: 实现文件
//

#include "pch.h"
#include "TinySQL.h"
#include "afxdialogex.h"
#include "EditDlg.h"
#include "CEditDlg.h"
#pragma comment(lib,"libmysql.lib")

// EditDlg 对话框

IMPLEMENT_DYNAMIC(EditDlg, CDialogEx)

EditDlg::EditDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EDIT_DIALOG, pParent)
{
	m_pstrColumn = NULL;
	m_pstrData = NULL;
	m_nColumnCount = 0;
	m_bUpdate = FALSE;
}

EditDlg::~EditDlg()
{
	if (m_pstrColumn)
	{
		delete[] m_pstrColumn;
		m_pstrColumn = NULL;
	}
	if (m_pstrData)
	{
		delete[] m_pstrData;
		m_pstrColumn = NULL;
	}
}

void EditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EIDT_LIST, m_List);
}


BEGIN_MESSAGE_MAP(EditDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_NOTIFY(NM_DBLCLK, IDC_EDIT_LIST, &EditDlg::OnDblclkEditList)
END_MESSAGE_MAP()


// EditDlg 消息处理程序


void EditDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (!m_pstrColumn || !m_pstrData)
		return;

	m_List.InsertColumn(0, "列名", LVCFMT_LEFT, 180);
	m_List.InsertColumn(1, "字段", LVCFMT_LEFT, 300);
	
	for (int row = 0; row < m_nColumnCount; row++)
	{
		m_List.InsertItem(row, m_pstrColumn[row]);
		m_List.SetItemText(row, 1, m_pstrData[row]);
	}
}


void EditDlg::OnDblclkEditList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	POSITION pos = m_List.GetFirstSelectedItemPosition();
	int nSel = m_List.GetNextSelectedItem(pos);
	m_strColumn = m_List.GetItemText(nSel, 0);
	m_strOldData = m_List.GetItemText(nSel, 1);

	if (m_strColumn == "")
		return;

	CEditDlg EditDlg;
	EditDlg.m_strInfo = "修改该字段["+ m_strColumn +"]对应的值:";
	EditDlg.DoModal();
	m_strNewData = EditDlg.m_strEdit; // 获取到新数据
	if (EditDlg.m_bUpdate == FALSE)
		return;
	m_List.SetItemText(nSel, 1, m_strNewData);
	m_List.Update(nSel);

	int nCode = UpdateTable();
	if (nCode != 0)
	{
		CString strError;
		strError.Format("执行失败 错误码: %d", nCode);
		AfxMessageBox(strError);
	}
	m_pstrData[nSel] = m_strNewData;

	*pResult = 0;
}

int EditDlg::UpdateTable()
{
	CString strMainColumn = m_pstrColumn[0];
	CString strMainData = m_pstrData[0];
	CString strQuery;
	strQuery.Format("UPDATE %s SET %s='%s' WHERE %s='%s' and %s='%s'", m_strTableName.GetBuffer(), m_strColumn.GetBuffer(), m_strNewData.GetBuffer(), strMainColumn.GetBuffer(), strMainData.GetBuffer(), m_strColumn.GetBuffer(), m_strOldData.GetBuffer());
	return mysql_query(m_pconn, strQuery.GetBuffer());
}