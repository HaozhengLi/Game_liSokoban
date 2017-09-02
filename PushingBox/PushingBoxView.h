
// PushingBoxView.h : interface of the CPushingBoxView class
//

#pragma once

//TODO
//自定义类cell，将界面分割成一个个格子（元素）
class Cell
{
public:
	int weitu;
	//根据取值不同显示不同的位图
	//取0代表空地
	//取1代表墙壁
	//取2代表存放点
	
	int thing;
	//根据取值不同表示放置在上面的物体不同
	//取0时代表没东西在（空地或存放点）上面
	//取1时代表有人
	//取2时代表有箱子

};

class CPushingBoxView : public CView
{
protected: // create from serialization only
	CPushingBoxView();
	DECLARE_DYNCREATE(CPushingBoxView)

// Attributes
public:
	CPushingBoxDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CPushingBoxView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

//TODO
public:
	//数据成员:
	int m_RowCount;	//设置行数
	int m_ColCount;	//设置列数
	Cell cell[10][10];	//最大界面范围
	CBitmap m_Bitmap[3];	//元素位图数组
	CBitmap m_Thing[3];	//物品位图数组
	int foot;	//步数

	CBitmap m_Anniu;	//按钮位图，一个九宫格面板
	CBitmap m_AnniuShan;	//闪烁的按钮
	int shanshuo;	//随机取0~8，代表哪个按钮处于高亮状态
	int t_shanshuo;	//记录上一个高亮的按钮编号

	CBitmap m_Title;	//LOGO位图
	CBitmap m_Pause;	//暂停位图
	CBitmap m_Win;	//胜利位图
	CBitmap m_Regret;	//悔棋位图
	
	int renx;	//记录人的位置
	int reny;
	int t_renx;	//记录人的上一时刻的位置
	int t_reny;
	unsigned int t_nChar;	//记录上一个方向键按的是什么，悔棋的时候要用
	int	t_xiang;	//悔棋时，需要考虑人附近的箱子是否要还原，取0时表示不用，1时表示用 

	int jieshu;	//取0时代表游戏还未结束，取1时表示结束
	int zanting;	//取1时游戏继续,取-1游戏暂停
	int huiqi;	//取0时游戏继续，取1时弹出“只能撤销一次”的提示，游戏暂停

	//函数成员:
	int pause(int t_zanting);	//判断是否暂停
	int win();	//判断是否胜利
	void Start();	//设定墙壁、箱子布局
	void shuaxin(int num);	//刷新函数，形参代表刷新哪一个按钮
	
	//消息成员:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // debug version in PushingBoxView.cpp
inline CPushingBoxDoc* CPushingBoxView::GetDocument() const
   { return reinterpret_cast<CPushingBoxDoc*>(m_pDocument); }
#endif