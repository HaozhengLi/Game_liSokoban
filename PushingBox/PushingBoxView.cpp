
// PushingBoxView.cpp : implementation of the CPushingBoxView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PushingBox.h"
#endif

#include "PushingBoxDoc.h"
#include "PushingBoxView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPushingBoxView

IMPLEMENT_DYNCREATE(CPushingBoxView, CView)

BEGIN_MESSAGE_MAP(CPushingBoxView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPushingBoxView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_KEYDOWN()
	ON_WM_CREATE()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CPushingBoxView construction/destruction

CPushingBoxView::CPushingBoxView()
{
	// TODO: add construction code here

	m_RowCount=10;	//10行
	m_ColCount=10;	//10列

	//初始化闪烁按钮
	//shanshuo初始为8,即一开始全都不亮，t_shanshuo一开始等于shanshuo
	t_shanshuo=shanshuo=8;

	//初始化元素位图数组，物品位图数组，按钮位图数组
	for(int i=0;i<3;i++)
		m_Bitmap[i].LoadBitmap(IDB_BITMAP1+i);
	for(int j=0;j<3;j++)
		m_Thing[j].LoadBitmap(IDB_THING1+j);

	//初始化LOGO位图
	m_Title.LoadBitmap(IDB_TITLE);
	//初始化控制区位图
	m_Anniu.LoadBitmap(IDB_ANNIU);
	//初始化闪烁的按钮
	m_AnniuShan.LoadBitmap(IDB_ANNIUSHAN);
	//初始化暂停位图
	m_Pause.LoadBitmap(IDB_PAUSE);
	//初始化胜利位图
	m_Win.LoadBitmap(IDB_WIN);
	//初始化悔棋位图
	m_Regret.LoadBitmap(IDB_REGRET);

	//初始化棋局
	Start();

}

CPushingBoxView::~CPushingBoxView()
{
}

BOOL CPushingBoxView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CPushingBoxView drawing

void CPushingBoxView::OnDraw(CDC* pDC)
{
	CPushingBoxDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here

	//画背景
	CBrush myBrush1;
	myBrush1.CreateSolidBrush(RGB(0,30,50));
	CRect myRect1(0,0,370,420);
	pDC->FillRect(myRect1,&myBrush1);

	//画计步器
	//画计步器的黑色屏幕
	CBrush myBrush2;
	myBrush2.CreateSolidBrush(RGB(0,0,0));
	CRect myRect2(20,20,70,50);
	pDC->FillRect(myRect2,&myBrush2);
	//画计步器的白色边框
	CPen myPen1;
	CPen *myOldPen1;
	myPen1.CreatePen(PS_SOLID,2,RGB(255,255,255));
	myOldPen1=pDC->SelectObject(&myPen1);
	pDC->MoveTo(20,50);
	pDC->LineTo(70,50);
	pDC->LineTo(70,20);
	pDC->SelectObject(&myOldPen1);
	//画计步器的红色边框
	CPen myPen2;
	CPen *myOldPen2;
	myPen2.CreatePen(PS_SOLID,2,RGB(200,0,0));
	myOldPen2=pDC->SelectObject(&myPen2);
	pDC->MoveTo(19,51);
	//pDC->LineTo(71,51);
	//pDC->LineTo(71,19);
	pDC->LineTo(19,19);
	pDC->LineTo(71,19);
	pDC->SelectObject(&myOldPen2);
	//画计步器的数字
	int nOldDc=pDC->SaveDC();
	pDC->SetTextColor(RGB(255,0,0));
	pDC->SetBkColor(RGB(0,0,0));
	CFont myFont1;
	if(myFont1.CreatePointFont(153,_T("Comic Sans MS"))==0)
	{
		AfxMessageBox(_T("Can't Create Font!"));
	}
	pDC->SelectObject(&myFont1);
	//位数设置
	CString str;
	if(foot<10)
		str.Format(_T("00%d"),foot);
	else if(foot<100)
		str.Format(_T("0%d"),foot);
	else
		str.Format(_T("%d"),foot);
	pDC->TextOut(27,20,str);
	pDC->RestoreDC(nOldDc);

	//画游戏区域的weitu
	//
	//对于weitu:
	//根据取值不同显示不同的位图
	//取0代表空地
	//取1代表墙壁
	//取2代表存放点
	CDC Dc;
	if(Dc.CreateCompatibleDC(pDC)==FALSE)
		AfxMessageBox(_T("Can't Create DC!"));
	for(int i=0;i<m_RowCount;i++)
		for(int j=0;j<m_ColCount;j++)
		{
			if(cell[i][j].weitu==0)
			{
				Dc.SelectObject(m_Bitmap[0]);
				pDC->BitBlt(i*35+10,j*35+60,160,160,&Dc,0,0,SRCCOPY);
			}
			if(cell[i][j].weitu==1)
			{
				Dc.SelectObject(m_Bitmap[1]);
				pDC->BitBlt(i*35+10,j*35+60,160,160,&Dc,0,0,SRCCOPY);
			}
			if(cell[i][j].weitu==2)
			{
				Dc.SelectObject(m_Bitmap[2]);
				pDC->BitBlt(i*35+10,j*35+60,160,160,&Dc,0,0,SRCCOPY);
			}
		}

	//
	//对于thing:
	//取0时代表没东西在（空地或存放点）上面
	//取1时代表有人
	//取2时代表有箱子
	for(int i=0;i<m_RowCount;i++)
		for(int j=0;j<m_ColCount;j++)
		{
			if(cell[i][j].thing==1)
			{
				Dc.SelectObject(m_Thing[0]);
				pDC->BitBlt(i*35+10,j*35+60,160,160,&Dc,0,0,SRCCOPY);
			}
			if(cell[i][j].thing==2)
			{
				Dc.SelectObject(m_Thing[1]);
				pDC->BitBlt(i*35+10,j*35+60,160,160,&Dc,0,0,SRCCOPY);
			}
			if(cell[i][j].weitu==2 && cell[i][j].thing==2)
			{
				Dc.SelectObject(m_Thing[2]);
				pDC->BitBlt(i*35+10,j*35+60,160,160,&Dc,0,0,SRCCOPY);
			}
		};

	//画LOGO
	Dc.SelectObject(m_Title);
	pDC->BitBlt(85,5,1600,160,&Dc,0,0,SRCCOPY);

	////画控制区背景
	//CBrush myBrush3;
	//myBrush3.CreateSolidBrush(RGB(172,172,172));
	//CRect myRect3(5,420,365,645);
	//pDC->FillRect(myRect3,&myBrush3);

	////画控制区域
	////按九宫格0~8分别代表确认、上、悔棋、左、无、右、暂停、下、重置
	//Dc.SelectObject(m_Anniu);
	//pDC->BitBlt(20,430,350,350,&Dc,0,0,SRCCOPY);
	//Dc.SelectObject(m_AnniuShan);
	//switch(shanshuo)
	//{
	//	case 0:
	//		pDC->BitBlt(20,430,160,160,&Dc,0,0,SRCCOPY);break;
	//	case 1:
	//		pDC->BitBlt(130,430,160,160,&Dc,0,0,SRCCOPY);break;
	//	case 2:
	//		pDC->BitBlt(240,430,160,160,&Dc,0,0,SRCCOPY);break;
	//	case 3:
	//		pDC->BitBlt(20,500,160,160,&Dc,0,0,SRCCOPY);break;
	//	case 4:
	//		pDC->BitBlt(130,500,160,160,&Dc,0,0,SRCCOPY);break;
	//	case 5:
	//		pDC->BitBlt(240,500,160,160,&Dc,0,0,SRCCOPY);break;
	//	case 6:
	//		pDC->BitBlt(20,570,160,160,&Dc,0,0,SRCCOPY);break;
	//	case 7:
	//		pDC->BitBlt(130,570,160,160,&Dc,0,0,SRCCOPY);break;
	//	case 8:
	//		pDC->BitBlt(240,570,160,160,&Dc,0,0,SRCCOPY);break;
	//	default:break;
	//}

	//画悔棋提示
	if(huiqi==1)
	{
		Dc.SelectObject(m_Regret);
		pDC->BitBlt(78,152,250,250,&Dc,0,0,SRCCOPY);
	}

	//画暂停提示
	if(zanting==-1)
	{
		Dc.SelectObject(m_Pause);
		pDC->BitBlt(78,152,250,250,&Dc,0,0,SRCCOPY);
	}
	
	//画结束提示
	if(jieshu==1)
	{
		Dc.SelectObject(m_Win);
		pDC->BitBlt(78,152,250,250,&Dc,0,0,SRCCOPY);
	}

}


// CPushingBoxView printing


void CPushingBoxView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPushingBoxView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPushingBoxView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPushingBoxView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CPushingBoxView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	//注释掉以阻止鼠标右键弹出
	//ClientToScreen(&point);
	//OnContextMenu(this, point);
}

void CPushingBoxView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CPushingBoxView diagnostics

#ifdef _DEBUG
void CPushingBoxView::AssertValid() const
{
	CView::AssertValid();
}

void CPushingBoxView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPushingBoxDoc* CPushingBoxView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPushingBoxDoc)));
	return (CPushingBoxDoc*)m_pDocument;
}
#endif //_DEBUG


// CPushingBoxView message handlers

//OnKeyDown键盘控制函数
void CPushingBoxView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	//下面多处要画图，先在函数开头写好这几行
	//获取指针pDC
	CDC *pDC=GetDC();
	CDC Dc;
	if(Dc.CreateCompatibleDC(pDC)==FALSE)
		AfxMessageBox(_T("Can't Create DC!"));

	//如果按F2，就重新游戏
	if(nChar==VK_F2)
	{
		Start();
		Invalidate();
	}

	//判断游戏是否已经结束
	if(jieshu == 1)
		return;

	//如果已经弹出了“已经悔棋一次”的提示框，此时按回车，可回到游戏
	if(nChar==VK_RETURN)
	{
		huiqi=0;
		//AfxMessageBox(_T("Test"));
		CRect rect;
		rect.left=78;
		rect.right=rect.left+220;
		rect.top=152;
		rect.bottom=rect.top+150;
		InvalidateRect(&rect);
	}
	
	//如果已经悔棋一次，就不能再悔棋了
	if(huiqi==1)
		return;

	//如果按空格，就暂停游戏，并在画面有提示
	if(nChar==VK_SPACE)
	{
		zanting=pause(zanting);
	}
	//判断游戏是否已经暂停
	if(zanting==-1)
		return;

	//利用方向键控制人物，并重画人前进方向的3个格子
	switch(nChar)
	{
		case VK_UP:
		{
			t_nChar=nChar;
			if(reny > 0 && cell[renx][reny-1].weitu != 1)
			{
				if(cell[renx][reny-1].thing==2 && reny-1==0)
					break;
				if(cell[renx][reny-1].thing==2 && cell[renx][reny-2].weitu==1)
					break;
				if(cell[renx][reny-1].thing==2 && cell[renx][reny-2].thing==2)
					break;
				reny--;
				foot++;
				cell[t_renx][t_reny].thing=0;
				if(cell[renx][reny].thing==2 && reny>0)
				{
					cell[renx][reny-1].thing=2;
					t_xiang=1;
				}
				else
					t_xiang=0;
				cell[renx][reny].thing=1;
				//重画
				CRect rect;
				rect.left=renx*35+10;
				rect.right=renx*35+10+35;
				rect.top=(reny-1)*35+60;
				rect.bottom=(reny+2)*35+60;
				InvalidateRect(&rect);
				//更新t_renx，t_reny
				t_renx=renx;
				t_reny=reny;
				//huiqi恢复为0
				huiqi=0;
			}
			break;
		}
		case VK_DOWN:
		{
			t_nChar=nChar;
			if(reny < m_RowCount-1 && cell[renx][reny+1].weitu != 1)
			{
				if(cell[renx][reny+1].thing==2 && reny+1==m_RowCount-1)
					break;
				if(cell[renx][reny+1].thing==2 && cell[renx][reny+2].weitu==1)
					break;
				if(cell[renx][reny+1].thing==2 && cell[renx][reny+2].thing==2)
					break;
				reny++;
				foot++;
				cell[t_renx][t_reny].thing=0;
				if(cell[renx][reny].thing==2 && reny<m_RowCount-1)
				{
					cell[renx][reny+1].thing=2;
					t_xiang=1;
				}
				else
					t_xiang=0;
				cell[renx][reny].thing=1;
				//重画
				CRect rect;
				rect.left=renx*35+10;
				rect.right=renx*35+10+35;
				rect.top=(reny-1)*35+60;
				rect.bottom=(reny+2)*35+60;
				InvalidateRect(&rect);
				//更新t_renx，t_reny
				t_renx=renx;
				t_reny=reny;
				//huiqi恢复为0
				huiqi=0;
			}
			break;
		}
		case VK_LEFT:
		{
			t_nChar=nChar;
			if(renx > 0 && cell[renx-1][reny].weitu != 1)
			{
				
				if(cell[renx-1][reny].thing==2 && renx-1==0)
					break;
				if(cell[renx-1][reny].thing==2 && cell[renx-2][reny].weitu==1)
					break;
				if(cell[renx-1][reny].thing==2 && cell[renx-2][reny].thing==2)
					break;
				renx--;
				foot++;
				cell[t_renx][t_reny].thing=0;
				if(cell[renx][reny].thing==2 && renx>0)
				{
					cell[renx-1][reny].thing=2;
					t_xiang=1;
				}
				else
					t_xiang=0;
				cell[renx][reny].thing=1;
				//重画
				CRect rect;
				rect.left=(renx-1)*35+10;
				rect.right=(renx+2)*35+10;
				rect.top=reny*35+60;
				rect.bottom=reny*35+60+35;
				InvalidateRect(&rect);
				//更新t_renx，t_reny
				t_renx=renx;
				t_reny=reny;
				//huiqi恢复为0
				huiqi=0;
			}
			break;			 
		}
		case VK_RIGHT:
		{
			t_nChar=nChar;
			if(renx < m_ColCount-1 && cell[renx+1][reny].weitu != 1)
			{
				if(cell[renx+1][reny].thing==2 && renx+1==m_ColCount-1)
					break;
				if(cell[renx+1][reny].thing==2 && cell[renx+2][reny].weitu==1)
					break;
				if(cell[renx+1][reny].thing==2 && cell[renx+2][reny].thing==2)
					break;
				renx++;
				foot++;
				cell[t_renx][t_reny].thing=0;
				if(cell[renx][reny].thing==2 && renx<m_ColCount-1)
				{
					cell[renx+1][reny].thing=2;
					t_xiang=1;
				}
				else
					t_xiang=0;
				cell[renx][reny].thing=1;
				//重画
				CRect rect;
				rect.left=(renx-1)*35+10;
				rect.right=(renx+2)*35+10;
				rect.top=reny*35+60;
				rect.bottom=reny*35+60+35;
				InvalidateRect(&rect);
				//更新t_renx，t_reny
				t_renx=renx;
				t_reny=reny;
				//huiqi恢复为0
				huiqi=0;
			}
			break;			  
		}
		case 0x52:
		{
			switch(t_nChar)
			{
				//判断是否已经悔棋一次，如果是，就不能再悔棋了
				case 0x52:
				{
					//弹出“只能悔棋一次”的提示，已在OnDraw中预先把胜利提示位图画好了
					//AfxMessageBox(_T("已经悔棋一次"));
					huiqi=1;
					CRect rect;
					rect.left=78;
					rect.right=rect.left+220;
					rect.top=152;
					rect.bottom=rect.top+150;
					InvalidateRect(&rect);
					break;
				}
				case VK_UP:
				{
					reny++;
					foot++;
					cell[t_renx][t_reny].thing=0;
					if(t_xiang==1)
					{
						cell[t_renx][t_reny-1].thing=0;
						cell[t_renx][t_reny].thing=2;
					}
					cell[renx][reny].thing=1;
					//重画
					CRect rect;
					rect.left=renx*35+10;
					rect.right=renx*35+10+35;
					rect.top=(reny-2)*35+60;
					rect.bottom=(reny+1)*35+60;
					InvalidateRect(&rect);
					//更新t_renx，t_reny
					t_renx=renx;
					t_reny=reny;
					//记录“上一个按的键为R”，另游戏只能悔棋一次
					t_nChar=nChar;
					//将t_xiang还原为0，在控制方向时会重新赋值
					t_xiang=0;
					break;
				}
				case VK_DOWN:
				{
					reny--;
					foot++;
					cell[t_renx][t_reny].thing=0;
					if(t_xiang==1)
					{
						cell[t_renx][t_reny+1].thing=0;
						cell[t_renx][t_reny].thing=2;
					}
					cell[renx][reny].thing=1;
					//重画
					CRect rect;
					rect.left=renx*35+10;
					rect.right=renx*35+10+35;
					rect.top=reny*35+60;
					rect.bottom=(reny+3)*35+60;
					InvalidateRect(&rect);
					//更新t_renx，t_reny
					t_renx=renx;
					t_reny=reny;
					//记录“上一个按的键为R”，另游戏只能悔棋一次
					t_nChar=nChar;
					//将t_xiang还原为0，在控制方向时会重新赋值
					t_xiang=0;
					break;
				}
				case VK_LEFT:
				{
					renx++;
					foot++;
					cell[t_renx][t_reny].thing=0;
					if(t_xiang==1)
					{
						cell[t_renx-1][t_reny].thing=0;
						cell[t_renx][t_reny].thing=2;
					}
					cell[renx][reny].thing=1;
					//重画
					CRect rect;
					rect.left=(renx-2)*35+10;
					rect.right=(renx+1)*35+10;
					rect.top=reny*35+60;
					rect.bottom=reny*35+60+35;
					InvalidateRect(&rect);
					//更新t_renx，t_reny
					t_renx=renx;
					t_reny=reny;
					//记录“上一个按的键为R”，另游戏只能悔棋一次
					t_nChar=nChar;
					//将t_xiang还原为0，在控制方向时会重新赋值
					t_xiang=0;
					break;
				}
				case VK_RIGHT:
				{
					renx--;
					foot++;
					cell[t_renx][t_reny].thing=0;
					if(t_xiang==1)
					{
						cell[t_renx+1][t_reny].thing=0;
						cell[t_renx][t_reny].thing=2;
					}
					cell[renx][reny].thing=1;
					//重画
					CRect rect;
					rect.left=renx*35+10;
					rect.right=(renx+3)*35+10;
					rect.top=reny*35+60;
					rect.bottom=reny*35+60+35;
					InvalidateRect(&rect);
					//更新t_renx，t_reny
					t_renx=renx;
					t_reny=reny;
					//记录“上一个按的键为R”，另游戏只能悔棋一次
					t_nChar=nChar;
					//将t_xiang还原为0，在控制方向时会重新赋值
					t_xiang=0;
					break;	
				}
				default: break;
			}
		}
		default:break;
	}

	//重画计步器
	CRect rect;
	rect.left=20;
	rect.right=90;
	rect.top=20;
	rect.bottom=50;
	InvalidateRect(&rect);

	//判断是否已经游戏结束
	jieshu = win();
	if(jieshu == 1)
		return;

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

//定义胜利判断函数win()
int CPushingBoxView::win()
{
	for(int i=0;i<m_RowCount;i++)
		for(int j=0;j<m_ColCount;j++)
			if(cell[i][j].weitu==2)
				if(cell[i][j].thing!=2)
					return 0;
	//弹出胜利提示，已在OnDraw中预先把胜利提示位图画好了
	CRect rect;
	rect.left=78;
	rect.right=rect.left+220;
	rect.top=152;
	rect.bottom=rect.top+150;
	InvalidateRect(&rect);
	return 1;
}

//定义初始化棋局的函数
void CPushingBoxView::Start()
{
	jieshu=0;	//初始设为0，代表游戏未结束
	zanting=1;	//初始设为1，代表游戏进行中
	huiqi=0;	//初始设为0，代表还没使用悔棋机会

	foot=0;	//计步

	t_nChar=0;	//记录上一个按键
	t_xiang=0;	//标记人附近的箱子是否需要还原，取零表示不需要

	//初始化闪烁按钮
	//shanshuo初始为9,即一开始全都不亮，t_shanshuo一开始等于shanshuo
	t_shanshuo=shanshuo=9;

	//以下是一个测试用的棋局，所以非常简单，正式情况下要注释掉
	
	//初始化cell数组的weitu元素
	//根据取值不同显示不同的位图
	//取0代表空地
	//取1代表墙壁
	//取2代表存放点
	//先将所有元素设为空地
	for(int i=0;i<m_RowCount;i++)
		for(int j=0;j<m_ColCount;j++)
			cell[i][j].weitu=0;
	//设定哪些元素是墙壁
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			cell[i][j].weitu=1;
	for(int i=7;i<10;i++)
		for(int j=6;j<10;j++)
			cell[i][j].weitu=1;
	//设定哪些元素是存放点
	cell[1][5].weitu=2;
	cell[4][7].weitu=2;
	cell[7][2].weitu=2;

	//初始化cell数组的thing元素
	//根据取值不同表示放置在上面的物体不同
	//取0时代表没东西在（空地或存放点）上面
	//取1时代表有人
	//取2时代表有箱子
	//取3时代表放置正确的箱子
	//先假设所有元素都没有放箱子
	for(int i=0;i<m_RowCount;i++)
		for(int j=0;j<m_ColCount;j++)
			cell[i][j].thing=0;
	//设定哪些空地上面放了箱子
	cell[4][2].thing=2;
	cell[3][4].thing=2;
	cell[4][4].thing=2;

	//初始化人的位置
	renx=t_renx=4;
	reny=t_reny=1;

	//人所在的cell格子thing=1，代表上面放置了一个人
	cell[renx][reny].thing=1;
	

	//以下是一个正式用的棋局
	/*
	//初始化game数组，也即设计棋局
	int game[10][10]=
	{
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 0, 0, 0, 1, 1, 1, 1, 1},
		{1, 1, 0, 1, 0, 0, 0, 1, 1, 1},
		{1, 0, 2, 2, 0, 2, 0, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 1, 1, 1, 1},
		{1, 1, 1, 0, 1, 2, 1, 1, 1, 1},
		{1, 1, 1, 0, 0, 0, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};
	//初始化cell数组的weitu元素（也即把game转置给cell.weitu）
	for(int i=0;i<m_RowCount;i++)
		for(int j=0;j<m_ColCount;j++)
		cell[i][j].weitu=game[j][i];
	
	//初始化cell数组的thing元素
	//根据取值不同表示放置在上面的物体不同
	//取0时代表没东西在（空地或存放点）上面
	//取1时代表有人
	//取2时代表有箱子
	//取3时代表放置正确的箱子
	//先假设所有元素都没有放箱子
	for(int i=0;i<m_RowCount;i++)
		for(int j=0;j<m_ColCount;j++)
			cell[i][j].thing=0;
	//设定哪些空地上面放了箱子
	cell[2][2].thing=2;
	cell[4][2].thing=2;
	cell[3][4].thing=2;
	cell[4][4].thing=2;

	//初始化人的位置
	renx=t_renx=4;
	reny=t_reny=1;

	//人所在的cell格子thing=1，代表上面放置了一个人
	cell[renx][reny].thing=1;
	*/
}

//OnCreate函数
int CPushingBoxView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	//生成计时器，1.5s计时一次
	SetTimer(1,1500,NULL);

	return 0;
}

//OnTimer函数
void CPushingBoxView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	//以时间为种子生成随机数
	srand((unsigned)time(NULL));
	//随机生成0~8表示9个按钮谁处于高亮状态
	shanshuo=(rand())%9;
	//重画高亮按钮，并将上一个高亮按钮恢复
	shuaxin(t_shanshuo);
	shuaxin(shanshuo);
	t_shanshuo=shanshuo;	//记录当前闪烁按钮的编号

	CView::OnTimer(nIDEvent);
}

//刷新函数
void CPushingBoxView::shuaxin(int num)
{
	CRect rect;
	switch(num)
	{
		//确认
		case 0:
			rect.left=20;
			rect.right=rect.left+110;
			rect.top=430;
			rect.bottom=rect.top+70;
			InvalidateRect(&rect);
			break;
		//上
		case 1:
			rect.left=130;
			rect.right=rect.left+110;
			rect.top=430;
			rect.bottom=rect.top+70;
			InvalidateRect(&rect);
			break;
		//悔棋
		case 2:
			rect.left=240;
			rect.right=rect.left+110;
			rect.top=430;
			rect.bottom=rect.top+70;
			InvalidateRect(&rect);
			break;
		//左
		case 3:
			rect.left=20;
			rect.right=rect.left+110;
			rect.top=500;
			rect.bottom=rect.top+70;
			InvalidateRect(&rect);
			break;
		//无
		case 4:
			rect.left=130;
			rect.right=rect.left+110;
			rect.top=500;
			rect.bottom=rect.top+70;
			InvalidateRect(&rect);
			break;
		//右
		case 5:
			rect.left=240;
			rect.right=rect.left+110;
			rect.top=500;
			rect.bottom=rect.top+70;
			InvalidateRect(&rect);
			break;
		//暂停
		case 6:
			rect.left=20;
			rect.right=rect.left+110;
			rect.top=570;
			rect.bottom=rect.top+70;
			InvalidateRect(&rect);
			break;
		//下
		case 7:
			rect.left=130;
			rect.right=rect.left+110;
			rect.top=570;
			rect.bottom=rect.top+70;
			InvalidateRect(&rect);
			break;
		//重置
		case 8:
			rect.left=240;
			rect.right=rect.left+110;
			rect.top=570;
			rect.bottom=rect.top+70;
			InvalidateRect(&rect);
			break;
		default:break;
	}
}

int CPushingBoxView::pause(int t_zanting)
{
	//如果按空格，就暂停游戏，并在画面有提示
	t_zanting=t_zanting*(-1);
	CRect rect;
	rect.left=78;
	rect.right=rect.left+220;
	rect.top=152;
	rect.bottom=rect.top+150;
	InvalidateRect(&rect);
	return t_zanting;
}