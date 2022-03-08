#pragma once
#include "afxdialogex.h"


// HelpDlg 对话框

class HelpDlg : public CDialogEx
{
	DECLARE_DYNAMIC(HelpDlg)

public:
	HelpDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~HelpDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HELP_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
