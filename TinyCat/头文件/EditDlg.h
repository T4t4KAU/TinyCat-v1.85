#pragma once
#include "afxdialogex.h"

// EditDlg 对话框

class EditDlg : public CDialogEx
{
	DECLARE_DYNAMIC(EditDlg)

public:
	EditDlg(CWnd* pParent = nullptr); // 标准构造函数
	virtual ~EditDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDIT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString* m_pstrColumn;
	CString* m_pstrData;
	int m_nColumnCount;
	CString m_strColumn;
	CString m_strNewData;
	CString m_strOldData;
	CListCtrl m_List;
	BOOL m_bUpdate;
	CString m_strTableName;

	MYSQL* m_pconn;

	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnDblclkEditList(NMHDR* pNMHDR, LRESULT* pResult);
	int UpdateTable();
};
