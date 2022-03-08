#pragma once
#include "afxdialogex.h"


// CAddDlg 对话框

class CAddDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddDlg)

public:
	CAddDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CAddDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedAddData();
	CString m_strColumnName;
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	CListCtrl m_List;
	CComboBox m_DataType;
	int m_nColumnCount;
	CString m_strDataType;
	CString m_strQuery;
	CString m_strColumns;
	CString m_strTableName;
}; 
