
// TinySQLDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "TinySQL.h"
#include "TinySQLDlg.h"
#include "afxdialogex.h"
#include "EditDlg.h"
#include "CEditDlg.h"
#include "CAddDlg.h"
#pragma comment(lib,"libmysql.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTinySQLDlg 对话框



CTinySQLDlg::CTinySQLDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TINYSQL_DIALOG, pParent)
	, m_strUsername(_T(""))
	, m_strPassword(_T(""))
	, m_strQuery(_T(""))
	, m_CurrentDB(_T(""))
	, m_nPort(3306)
	, m_bConnect(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTinySQLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_USERNAME, m_strUsername);
	DDX_Text(pDX, IDC_PASSWORD, m_strPassword);
	DDX_Text(pDX, IDC_SQL, m_strQuery);
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Control(pDX, IDC_TREE, m_Tree);
	DDX_Text(pDX, IDC_DATABASE, m_CurrentDB);
	DDX_Text(pDX, IDC_PORT, m_nPort);
}

BEGIN_MESSAGE_MAP(CTinySQLDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT, &CTinySQLDlg::OnBnClickedConnect)
	ON_BN_CLICKED(IDC_QUERY, &CTinySQLDlg::OnBnClickedQuery)
	ON_BN_CLICKED(IDC_HELP, &CTinySQLDlg::OnBnClickedHelp)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE, &CTinySQLDlg::OnDblclkTree)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, &CTinySQLDlg::OnDblclkList)
	ON_BN_CLICKED(IDC_ADD, &CTinySQLDlg::OnBnClickedAdd)
	ON_NOTIFY(NM_SETFOCUS, IDC_TREE, &CTinySQLDlg::OnSetfocusTree)
	ON_NOTIFY(NM_RCLICK, IDC_TREE, &CTinySQLDlg::OnRclickTree)
	ON_NOTIFY(NM_KILLFOCUS, IDC_TREE, &CTinySQLDlg::OnKillfocusTree)
	ON_BN_CLICKED(IDC_SUB, &CTinySQLDlg::OnBnClickedSub)
	ON_BN_CLICKED(IDC_ADDROW, &CTinySQLDlg::OnBnClickedAddrow)
END_MESSAGE_MAP()


// CTinySQLDlg 消息处理程序

BOOL CTinySQLDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	m_ImageList.Create(16, 16, ILC_COLOR8, 0, 3);
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON2));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON1));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON3));
	m_Tree.SetImageList(&m_ImageList, TVSIL_NORMAL);

	m_hRootItem = m_Tree.InsertItem("数据库", 0, 0);

	GetDlgItem(IDC_QUERY)->EnableWindow(FALSE);
	SetDlgItemText(IDC_DATABASE, "未选择");

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTinySQLDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTinySQLDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 单击连接按钮 连接数据库
void CTinySQLDlg::OnBnClickedConnect()
{
	UpdateData(TRUE);  //一个数据库结构体

	//初始化数据库
	mysql_init(&conn);
	//设置编码方式
	mysql_options(&conn, MYSQL_SET_CHARSET_NAME, "UTF8");
	//连接数据库
	if(!mysql_real_connect(&conn, "localhost", m_strUsername.GetBuffer(), m_strPassword.GetBuffer(), NULL, m_nPort, NULL, 0))
		MessageBox("连接失败");
	else
	{
		m_bConnect = TRUE;
		SetDlgItemText(IDC_CONNECT_STATUS, "已连接");
		GetDlgItem(IDC_CONNECT)->EnableWindow(FALSE);
		GetDlgItem(IDC_USERNAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_PASSWORD)->EnableWindow(FALSE);
		MessageBox("连接成功");
		GetDlgItem(IDC_QUERY)->EnableWindow(TRUE);
		SetDlgItemText(IDC_SQL, "");
		
		MYSQL_RES* res;
		MYSQL_ROW row;
		res = mysql_list_dbs(&conn, NULL);

		// 将数据库名称插入树控件
		while (row = mysql_fetch_row(res))
		{
			CString strDataBase;
			strDataBase.Format("%s", row[0]);
			m_Tree.InsertItem(strDataBase, 1, 1, m_hRootItem);
		}
		// 将树节点展开
		m_Tree.Expand(m_hRootItem, TVE_EXPAND);
	}
}

// SQL查询
int CTinySQLDlg::DataQuery(CString strQuery)
{
	if (m_CurrentDB)
	{
		mysql_select_db(&conn, m_CurrentDB.GetBuffer());
	}
	else
	{
		SetDlgItemText(IDC_QUERY_RESULT, "未选择数据库");
		return 1;
	}

	int bRes = 0;
	CString strText;
	m_strQuery = strQuery;
	bRes = mysql_query(&conn, m_strQuery.GetBuffer());
	if (bRes == 0)
	{
		SetDlgItemText(IDC_QUERY_RESULT, "执行成功");
	}
	else
	{
		CString strText;
		strText.Format("执行失败 错误码: %d", bRes);
		SetDlgItemText(IDC_QUERY_RESULT, strText);
	}
	return bRes;
}

// 执行按钮
void CTinySQLDlg::OnBnClickedQuery()
{
	UpdateData(TRUE);
	if (m_strQuery == "")
	{
		SetDlgItemText(IDC_QUERY_RESULT, "执行失败 输入为空");
		return;
	}
	DataQuery(m_strQuery);
}

void CTinySQLDlg::FindTable(CString strDBName, HTREEITEM hSelectItem)
{
	MYSQL_RES* res = mysql_list_tables(&conn, NULL);
	MYSQL_ROW row;
	while (row = mysql_fetch_row(res))
	{
		CString strTableName;
		strTableName.Format("%s", row[0]);
		// 在树控件中插入表名及其图标
		m_Tree.InsertItem(strTableName, 2, 2, hSelectItem);
	}

	mysql_free_result(res);
}

// 向报表中插入列
void CTinySQLDlg::FindField(CString strTableName)
{
	char szText[256] = { 0 };
	sprintf_s(szText, "DESC %s", strTableName.GetBuffer());
	mysql_query(&conn, szText);
	MYSQL_RES* res = mysql_store_result(&conn);
	MYSQL_ROW row;
	int i = 0;
	
	Sleep(TIME_WAIT);
	m_List.SetExtendedStyle(LVS_EX_AUTOSIZECOLUMNS | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	while (row = mysql_fetch_row(res))
	{
		m_List.InsertColumn(i, row[0], LVCFMT_LEFT, 100);
		i++;
	}
	mysql_free_result(res);
}

// 在报表中插入数据
void CTinySQLDlg::FindData(CString strTableName)
{
	char szText[1024] = { 0 };
	sprintf_s(szText, "select * from %s", strTableName.GetBuffer());
	mysql_query(&conn, szText);
	MYSQL_RES* res = mysql_store_result(&conn);
	MYSQL_ROW row;
	int column = 0, num_of_fields = mysql_num_fields(res);

	// 在报表中显示数据
	CString strText;
	while (row = mysql_fetch_row(res))
	{
		strText.Format("%s", row[0]);
		m_List.InsertItem(column, strText);
		for (int i = 1; i < num_of_fields; i++)
		{
			strText.Format("%s", row[i]);
			m_List.SetItemText(column, i, strText);
		}
		column++;
	}

	mysql_free_result(res);
}

//删除报表中所有列
void CTinySQLDlg::DeleteAllColumns()
{
	int nColumnCount = m_List.GetHeaderCtrl()->GetItemCount();
	for (int i = 0; i < nColumnCount; i++)
	{
		m_List.DeleteColumn(0);
	}
}

// 弹出帮助对话框
void CTinySQLDlg::OnBnClickedHelp()
{
	CDialog HelpDlg(IDD_HELP_DIALOG, AfxGetApp()->GetMainWnd());
	HelpDlg.DoModal();
}

// 双击树控件节点 在报表控件中展开数据
void CTinySQLDlg::OnDblclkTree(NMHDR* pNMHDR, LRESULT* pResult)
{
	HTREEITEM hSelectItem = m_Tree.GetSelectedItem(), hChildItem;
	if (hSelectItem == m_Tree.GetRootItem())
		return;

	Sleep(TIME_WAIT/2);
	// 删除指定控件原来的节点
	while (hChildItem = m_Tree.GetNextItem(hSelectItem, TVGN_CHILD))
	{
		m_Tree.DeleteItem(hChildItem);
	}

	// 判断选中节点是否为数据库 如果父节点是根节点则为数据库
	if(m_Tree.GetParentItem(hSelectItem) == m_hRootItem)
	{
		CString strDBName;
		strDBName = m_Tree.GetItemText(hSelectItem);
		mysql_select_db(&conn, strDBName.GetBuffer());
		FindTable(strDBName, hSelectItem);
		m_CurrentDB = strDBName;
	}
	// 选中节点为数据表
	else
	{
		m_List.DeleteAllItems();
		Sleep(TIME_WAIT/2);
		DeleteAllColumns();
		m_strTableName = m_Tree.GetItemText(hSelectItem);
		FindField(m_strTableName); // 向报表中插入列
		FindData(m_strTableName);  // 向报表中插入数据
	}

	UpdateData(FALSE);
	SetDlgItemText(IDC_SQL, "");

	*pResult = 0;
}

CString* CTinySQLDlg::FindListColumn()
{
	// 获取列表头 同时获取列数
	m_nColumnCount = m_List.GetHeaderCtrl()->GetItemCount();
	CString* pstrText = new CString[m_nColumnCount];
	char szText[256] = { 0 };
	LVCOLUMN lvCol;
	lvCol.mask = LVCF_TEXT;
	lvCol.pszText = szText;
	lvCol.cchTextMax = 256;
	// 获取列名的文本
	for (int i = 0; i < m_nColumnCount; i++)
	{
		m_List.GetColumn(i, &lvCol);
		pstrText[i].Format("%s", lvCol.pszText);
	}
	return pstrText;
}

// 获取选中行的数据 返回字符串数组
CString* CTinySQLDlg::FindListData(int nSel)
{
	m_List.GetItemText(nSel, 0);
	CString* pstrText = new CString[m_nColumnCount];
	for (int i = 0; i < m_nColumnCount; i++)
	{
		pstrText[i] = m_List.GetItemText(nSel, i);
	}
	return pstrText;
}

// 双击列表 弹出编辑对话框
void CTinySQLDlg::OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	POSITION pos = m_List.GetFirstSelectedItemPosition();
	int nSel = m_List.GetNextSelectedItem(pos);
	if (nSel < 0)
		return;
	
	// 创建对话框
	EditDlg DataDlg;
	DataDlg.m_pstrColumn = FindListColumn();
	DataDlg.m_pstrData = FindListData(nSel);
	DataDlg.m_nColumnCount = m_nColumnCount;
	DataDlg.m_pconn = &conn;
	DataDlg.m_strTableName = m_strTableName;
	DataDlg.DoModal();

	for (int i = 0; i < m_nColumnCount; i++)
	{
		m_List.SetItemText(nSel, i,DataDlg.m_pstrData[i]);
	}
	m_List.Update(nSel);

	*pResult = 0;
}


void CTinySQLDlg::OnBnClickedAdd()
{
	if (m_hFoucesItem == NULL)
		return;

	CAddDlg AddDlg;
	AddDlg.DoModal();
}


void CTinySQLDlg::OnSetfocusTree(NMHDR* pNMHDR, LRESULT* pResult)
{
	HTREEITEM hSelectItem = m_Tree.GetSelectedItem();
	m_hFoucesItem = hSelectItem;
	*pResult = 0;
}


void CTinySQLDlg::OnRclickTree(NMHDR* pNMHDR, LRESULT* pResult)
{
	HTREEITEM hSelectItem = m_Tree.GetSelectedItem();
	if (m_Tree.GetParentItem(hSelectItem) != m_hRootItem)
	{
		CString strTableName = m_Tree.GetItemText(hSelectItem);
		CEditDlg EditDlg;
		EditDlg.m_strInfo = "为表[" + strTableName + "]设置一个新的表名:";
		EditDlg.DoModal();
		CString strQuery = "RENAME TABLE " + strTableName + " TO " + EditDlg.m_strEdit;
		if (!EditDlg.m_bUpdate)
			return;
		DataQuery(strQuery);
		m_Tree.Expand(m_Tree.GetParentItem(hSelectItem), TVE_COLLAPSE);
	}
	*pResult = 0;
}


void CTinySQLDlg::OnKillfocusTree(NMHDR* pNMHDR, LRESULT* pResult)
{
	// m_hFoucesItem = NULL;
	*pResult = 0;
}


void CTinySQLDlg::OnBnClickedSub()
{
	CString strTableName = m_Tree.GetItemText(m_hFoucesItem);
	if (MessageBox("是否删除该表(" + strTableName + ")", "提示", MB_YESNO | MB_ICONQUESTION) == IDYES)
	{
		if (DataQuery("DROP TABLE " + strTableName) == 0)
		{
			m_Tree.DeleteItem(m_hFoucesItem);
			if (m_strTableName == strTableName)
				m_strTableName = "";
			m_List.DeleteAllItems();
			Sleep(TIME_WAIT / 2);
			DeleteAllColumns();
		}
	}
}


void CTinySQLDlg::OnBnClickedAddrow()
{
	CAddDlg AddDlg;
	AddDlg.DoModal();
}
