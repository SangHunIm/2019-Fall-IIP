
// IIPView.cpp: CIIPView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "IIP.h"
#endif

#include "IIPDoc.h"
#include "IIPView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIIPView

IMPLEMENT_DYNCREATE(CIIPView, CView)

BEGIN_MESSAGE_MAP(CIIPView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CIIPView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CIIPView 생성/소멸

CIIPView::CIIPView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CIIPView::~CIIPView()
{
}

BOOL CIIPView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CIIPView 그리기

void CIIPView::OnDraw(CDC* pDC)
{
	CIIPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	for (unsigned int i = 0; i < pDoc->height; i++)
	{
		for (unsigned int j = 0; j < pDoc->width; j++)
		{
			unsigned char InVal = pDoc->m_InImage[(i * pDoc->width) + j];
			unsigned char OutVal = pDoc->m_OutImage[(i * pDoc->width) + j];
			pDC->SetPixel(j, i, RGB(InVal, InVal, InVal));
			pDC->SetPixel(j + pDoc->width + 50, i, RGB(OutVal, OutVal, OutVal));
		}
	}
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			unsigned char refVal = pDoc->m_RefImage[i][j];
			pDC->SetPixel(j, i + 266, RGB(refVal, refVal, refVal));
		}
	}
}


// CIIPView 인쇄


void CIIPView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CIIPView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CIIPView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CIIPView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CIIPView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CIIPView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CIIPView 진단

#ifdef _DEBUG
void CIIPView::AssertValid() const
{
	CView::AssertValid();
}

void CIIPView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CIIPDoc* CIIPView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIIPDoc)));
	return (CIIPDoc*)m_pDocument;
}
#endif //_DEBUG


// CIIPView 메시지 처리기
