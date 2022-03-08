#pragma once
#include "afxdialogex.h"


// CEditDlg 对话框

class CEditDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEditDlg)

public:
	CEditDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CEditDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDIT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strEdit;
	afx_msg void OnBnClickedOk();
	CString m_strInfo;
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedCancel();

	BOOL m_bUpdate;
};
