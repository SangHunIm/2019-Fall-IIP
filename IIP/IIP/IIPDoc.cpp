
// IIPDoc.cpp: CIIPDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "IIP.h"
#endif

#include "IIPDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CIIPDoc

IMPLEMENT_DYNCREATE(CIIPDoc, CDocument)

BEGIN_MESSAGE_MAP(CIIPDoc, CDocument)
	ON_COMMAND(ID_ARITHMETIC, &CIIPDoc::OnArithmetic)
END_MESSAGE_MAP()


// CIIPDoc 생성/소멸

CIIPDoc::CIIPDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
	m_InImage = NULL;
	m_OutImage = NULL;
	height = 0;
	width = 0;
}

CIIPDoc::~CIIPDoc()
{
	if (m_InImage != NULL)
		delete(m_InImage);
	if (m_OutImage != NULL)
		delete(m_OutImage);
}

BOOL CIIPDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CIIPDoc serialization

void CIIPDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
		if (width != 0 && height != 0)
		{
			ar.Write(m_OutImage, width*height);
		}
	}
	
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
		CString strTemp = ar.m_strFileName.Right(3);
		// 영상파일이 RAW로 저장되어 있는 경우
		if (toupper(strTemp[0]) == 'B' &&
			toupper(strTemp[1]) == 'M' &&
			toupper(strTemp[2]) == 'P')
		{
			// 입력할 화일의 포인트를 가져옴.
			CImage m_Image;
			m_Image.Load(ar.m_strFileName);
			width = m_Image.GetWidth();
			height = m_Image.GetHeight();
			m_InImage = (unsigned char*)malloc(sizeof(unsigned char)* width * height);
			m_OutImage = (unsigned char*)malloc(sizeof(unsigned char) * width * height);
			int ws = width * (m_Image.GetBPP() / 8);
			unsigned char *m_tmpImage = (unsigned char*)malloc(sizeof(unsigned char) * ws * height);
			if (m_Image.GetBPP() == 1)
			{
				AfxMessageBox((LPCTSTR)"읽을 수 있는 파일 형식이 아닙니다.");
				return;
			}
			else if (m_Image.GetBPP() == 8)
			{
				for (int y = 0; y < height; y++) {
					BYTE * srcImg = NULL;
					;
					srcImg = (BYTE *)
						m_Image.GetPixelAddress(0, y);
					memcpy(&m_InImage[y * ws], srcImg, ws);
				}
			}
			else if (m_Image.GetBPP() == 24)
			{
				for (int y = 0; y < height; y++) {
					BYTE * srcImg = NULL;
					;
					srcImg = (BYTE *)
						m_Image.GetPixelAddress(0, y);
					memcpy(&m_tmpImage[y * ws], srcImg,
						ws);
				}
				int iter = 0;
				for (int y = 0; y < height; y++)
				{
					for (int x = 0; x < width; x++)
					{
						m_InImage[(y * width) + x] = (m_tmpImage[iter] * 0.21 + m_tmpImage[iter + 1] * 0.72 + m_tmpImage[iter + 2] * 0.07);
						iter += 3;
					}
				}
			}
		}
		// 입력파일이 BMP파일이 아닌경우
		else
		{
			AfxMessageBox((LPCTSTR)"읽을 수 있는 파일 형식이 아닙니다.");
			return;
		}
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CIIPDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CIIPDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CIIPDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CIIPDoc 진단

#ifdef _DEBUG
void CIIPDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CIIPDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CIIPDoc 명령


void CIIPDoc::OnArithmetic()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	int i, j; // 인덱스 처리릉 위한 변수
	int temp; // 임시 데이터 저장을 위한 변수
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {

			//덧셈
			temp = m_InImage[(i*width) + j] + 40;

			//뺄셈
			//temp = m_InImage[(i*width) + j] - 40;

			//곱셈
			//temp = m_InImage[(i*width) + j] * 2;

			//나눗셈
			//temp = m_InImage[(i*width) + j] / 2;

			if (temp > 255) m_OutImage[(i*width) + j] = 255;
			else if (temp < 0) m_OutImage[(i*width) + j] = 0;
			else m_OutImage[(i*width) + j] = (unsigned char)temp;
		}
	}
	UpdateAllViews(NULL);
}			
