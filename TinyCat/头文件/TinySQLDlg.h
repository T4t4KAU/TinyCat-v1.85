
// TinySQLDlg.h: 头文件
//

#pragma once


// CTinySQLDlg 对话框
class CTinySQLDlg : public CDialogEx
{
// 构造
public:
	CTinySQLDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TINYSQL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	BOOL m_bConnect;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedConnect();
	CString m_strUsername;
	HTREEITEM m_hRootItem;
	HTREEITEM m_hFoucesItem;
	MYSQL conn;
	CString m_strPassword;
	CTreeCtrl m_Tree;
	afx_msg void OnBnClickedQuery();
	CString m_strQuery;
	CListCtrl m_List;
	CString m_strTableName;
	afx_msg void OnBnClickedHelp();
	CString m_CurrentDB;
	afx_msg void OnDblclkTree(NMHDR* pNMHDR, LRESULT* pResult);

	int m_nColumnCount;

	void FindTable(CString strDBName, HTREEITEM hSelectItem);
	void FindField(CString strTableName);
	void FindData(CString strTableName);

	CString* FindListData(int nSel);
	CString* FindListColumn();
	void DeleteAllColumns();
	int DataQuery(CString strQuery);
	unsigned int m_nPort;
	CImageList m_ImageList;
	afx_msg void OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedAdd();
	afx_msg void OnSetfocusTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedSub();
	afx_msg void OnBnClickedAddrow();
};
