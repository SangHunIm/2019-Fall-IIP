﻿
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
	ON_COMMAND(ID_Histogram, &CIIPDoc::OnHistogram)
	ON_COMMAND(ID_Binarization, &CIIPDoc::OnBinarization)
	ON_COMMAND(ID_Gonzalez, &CIIPDoc::OnGonzalez)
	ON_COMMAND(ID_Otsu, &CIIPDoc::OnOtsu)
	ON_COMMAND(ID_Lowpassfilter, &CIIPDoc::OnLowpassfilter)
	ON_COMMAND(ID_Highpassfilter, &CIIPDoc::OnHighpassfilter)
	ON_COMMAND(ID_Medianfilter, &CIIPDoc::OnMedianfilter)
	ON_COMMAND(ID_Fdct, &CIIPDoc::OnFdct)
	ON_COMMAND(ID_Idct, &CIIPDoc::OnIdct)
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
			temp = m_InImage[(i*width) + j] + 50;

			//뺄셈
			//temp = m_InImage[(i*width) + j] - 40;

			//곱셈
			//temp = m_InImage[(i*width) + j] * 2;

			//나눗셈
			//temp = m_InImage[(i*width) + j] / 2;

			if (temp > 255) 
				m_OutImage[(i*width) + j] = 255;
			else if (temp < 0) 
				m_OutImage[(i*width) + j] = 0;
			else 
				m_OutImage[(i*width) + j] = (unsigned char)temp;
		}
	}
	UpdateAllViews(NULL);
}			


void CIIPDoc::OnHistogram()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	int Hist[256];
	int MaxVal = 0;
	int i, j;

	memset(Hist, 0, sizeof(int) * 256);

	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			Hist[m_InImage[(i*width) + j]]++;
			if (MaxVal < Hist[m_InImage[(i*width) + j]])
				MaxVal = Hist[m_InImage[(i*width) + j]];
		}
	}

	m_OutImage = (unsigned char*)malloc(sizeof(char) * height * width);
	memset(m_OutImage, 255, sizeof(unsigned char) * height * width);
	float w_ratio = (float)255 / (width - 1);
	float h_ratio = (float)(height - 1) / MaxVal;
	for (i = 0; i < width; i++) {
		int idx = i * w_ratio;
		int value = Hist[idx] * h_ratio;
		for (j = 0; j < value; j++)
			m_OutImage[(height - j - 1)*width + i] = 0;
	}
	UpdateAllViews(NULL);
}


void CIIPDoc::OnBinarization()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_Threshold = 130;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (m_InImage[(i*width) + j] >= m_Threshold)
				m_OutImage[(i*width) + j] = 255;
			else
				m_OutImage[(i*width) + j] = 0;
		}
	}
	UpdateAllViews(NULL);
}


void CIIPDoc::OnGonzalez()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	int hist[256];

	memset(hist, 0, sizeof(int) * 256);

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			hist[m_InImage[(i*width) + j]]++;
		}
	}

	int T, min, max;

	for (int i = 0; i < 256; i++) {
		if (hist[i] > 0) {
			min = i;
			i = 257;
		}
	}
	for (int i = 255; i > 0; i--) {
		if (hist[i] > 0) {
			max = i;
			i = -1;
		}
	}

	T = (min + max) / 2;

	int Diff = 5; //새롭게 계산된 임계값과 이전임계값과의 차이에 대한 초기값
	while (Diff >= 1)
	{
		// 그룹 1에 속한 화소 집합의 평균계산
		int nSum = 0, nCnt = 0;
		// nCnt: 그룹 1의 전체 화소수
		for (int i = 0; i < T; i++) {
			nSum += hist[i] * i;
			nCnt += hist[i];
		}
		double Mu_1 = (double)(nSum / nCnt); // 그룹 1의 밝기값 평균
		// 그룹 2에 속한 화소 집합의 평균계산
		nSum = 0, nCnt = 0;
		// nCnt: 그룹 2의 전체 화소수
		for (int i = T; i < 256; i++)
		{
			nSum += hist[i] * i;
			nCnt += hist[i];
		}
		double Mu_2 = (double)(nSum / nCnt); // 그룹 2의 밝기값 평균
		// 두 화소 그룹의 밝기값 평균을 이용한 임계값 결정
		int T_Last = (int)((Mu_1 + Mu_2) / 2);
		Diff = abs(T - T_Last);
		T = T_Last;
	}

	m_Threshold = T;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (m_InImage[(i*width) + j] >= m_Threshold)
				m_OutImage[(i*width) + j] = 255;
			else
				m_OutImage[(i*width) + j] = 0;
		}
	}

	UpdateAllViews(NULL);

	CString strTemp;
	strTemp.Format(_T("Gonzalez 임계값 = %d"), m_Threshold);
	AfxMessageBox(strTemp);

}


void CIIPDoc::OnOtsu()
{
	int hist[256];

	memset(hist, 0, sizeof(int) * 256);

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			hist[m_InImage[(i*width) + j]]++;

	int N = 256 * 256;
	int L = 256;
	int temp_threshold;
	double Mu_1, Mu_2;
	double Mu_T;
	double W1, W2;
	double Sigma_B;
	double Sigma_Bmax = 0;
	double H_m[256], H_cdf[256];
	H_m[0] = 0; H_cdf[0] = hist[0];

	for (int i = 1; i < L; i++) {
		H_m[i] = H_m[i - 1] + hist[i] * (double)i;
		H_cdf[i] = H_cdf[i - 1] + hist[i];
	}
	Mu_T = H_m[255] / N;
	for (int k = 3; k < L; k += 4) {
		W1 = H_cdf[k] / N;
		W2 = 1. - W1;
		if (H_cdf[k] == 0.) continue;
		Mu_1 = H_m[k] / H_cdf[k];
		if ((N - H_cdf[k]) == 0.) continue;
		Mu_2 = (H_m[L - 1] - H_m[k]) / (N - H_cdf[k]);
		Sigma_B = W1 * (Mu_1 - Mu_T)*(Mu_1 - Mu_T) +
			W2 * (Mu_2 - Mu_T)*(Mu_2 - Mu_T);
		if (Sigma_B > Sigma_Bmax) {
			Sigma_Bmax = Sigma_B;
			temp_threshold = k;
		}
	}
	for (int k = temp_threshold - 3; k <= temp_threshold + 3; k++) {
		W1 = H_cdf[k] / N; 
		W2 = 1. - W1;
		Mu_1 = H_m[k] / H_cdf[k]; 
		Mu_2 = (H_m[L - 1] - H_m[k]) / (N - H_cdf[k]);
		Sigma_B = W1 * (Mu_1 - Mu_T)*(Mu_1 - Mu_T) + W2 * (Mu_2 - Mu_T)*(Mu_2 - Mu_T);
		if (Sigma_B > Sigma_Bmax) {
			Sigma_Bmax = Sigma_B;
			m_Threshold = k; 
		}
	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (m_InImage[(i*width) + j] >= m_Threshold)
				m_OutImage[(i*width) + j] = 255;
			else
				m_OutImage[(i*width) + j] = 0;
		}
	}
	UpdateAllViews(NULL);
	CString strTemp;
	strTemp.Format(_T("Otsu 임계값 = %d"), m_Threshold);
	AfxMessageBox(strTemp);
}


void CIIPDoc::OnLowpassfilter()
{
	static int mask[3][3] = { {1, 1, 1}, {1, 1, 1}, {1, 1, 1} };
	int temp;

	for (int i = 1; i < height; i++) {
		for (int j = 1; j < width; j++) {
			temp = 0;
			for (int r = 0; r < 3; r++) {
				for (int c = 0; c < 3; c++)
					temp += (mask[r][c] * m_InImage[((i + r - 1) * width) + j + c - 1]);
			}
			m_OutImage[(i*width) + j] = (unsigned char)(temp / 9);
		}
	}

	for (int i = 0; i < width; i++) {
		m_OutImage[i] = m_InImage[i];
		m_OutImage[((height - 2)*width) + i] = m_InImage[((height - 2)*width) + i];
	}
	for (int i = 0; i < height; i++) {
		m_OutImage[((i)*width)] = m_InImage[((i)*width)];
		m_OutImage[((i + 1)*width - 1)] = m_InImage[((i + 1)*width - 1)];
	}
	UpdateAllViews(NULL);
}


void CIIPDoc::OnHighpassfilter()
{
	static int mask[3][3] = { {-1, -1, -1}, {-1, 9, -1}, {-1, -1, -1} };
	int temp, Max = -256 * 256, Min = 256 * 256;
	int i, j, r, c;
	int *Result = (int*)malloc(sizeof(int) * width * height);

	for (i = 1; i < height; i++) {
		for (j = 1; j < width; j++) {
			temp = 0; 
			for (r = 0; r < 3; r++) {
				for (c = 0; c < 3; c++)
					temp += (mask[r][c] * m_InImage[((i + r - 1)*width) + j + c - 1]); 
			}
			if (temp > Max) Max = temp;
			if (temp < Min) Min = temp;
			Result[(i*width) + j] = temp;
		}
	}
	int size = width * height;

	for (int i = 0; i < width; i++) {
		m_OutImage[i] = m_InImage[i];
		m_OutImage[size - i - 1] = m_InImage[size - i - 1];
	}
	for (int i = 0; i < height; i++) {
		m_OutImage[((i)*width)] = m_InImage[((i)*width)];
		m_OutImage[((i + 1)*width - 1)] = m_InImage[((i + 1)*width - 1)];
	}

	//그대로 출력
	/*
	for(i = 0 ; i < height; i++){
		for(j = 0 ; j < width ; j++){
			m_OutImage[(i*width)+j] = (unsigned
			char)Result[(i*width)+j];
		}
	}*/

	//클리핑
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			if (Result[(i*width) + j] > 255) m_OutImage[(i*width) + j] =
				255;
			else if (Result[(i*width) + j] < 0) m_OutImage[(i*width) + j] =
				0;
			else
				m_OutImage[(i*width) + j] = (unsigned
					char)Result[(i*width) + j];
		}
	}

	//매핑
	/*
	double C1 = (double)(255.0 / (Max - Min));
	double C2 = (double)(-255.0*Min / (Max - Min));
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			m_OutImage[(i*width) + j] = (unsigned
				char)(C1*Result[(i*width) + j] + C2);
		}
	}

	CString strTemp;
	strTemp.Format(_T("최대값 = %d , 최소값 = %d"), Max, Min);
	AfxMessageBox(strTemp);
	*/

	UpdateAllViews(NULL);
}


void CIIPDoc::OnMedianfilter()
{
	const int winSize = 3;

	unsigned char* arr = new unsigned char[winSize * winSize];

	for (int y = 0 + winSize / 2; y < height - winSize / 2; y++)
	{
		for (int x = 0 + winSize / 2; x < width - winSize / 2; x++)
		{
			int total = 0; 
			for (int by = 0; by < winSize; by++)
			{
				for (int bx = 0; bx < winSize; bx++)
				{
					arr[total] = m_InImage[((y + (by - winSize / 2)) * width) + x + (bx - winSize / 2)];
					for (int i = total; i > 0; i--)
					{
						
						if (arr[i] < arr[i - 1])
						{
							unsigned char temp = arr[i];
							arr[i] = arr[i - 1];
							arr[i - 1] = temp;
						}
					}
					total++;
				}
			}
			m_OutImage[(y*width) + x] = arr[winSize * winSize / 2];
		}
	}
	delete[] arr; 

	UpdateAllViews(NULL);
}


void CIIPDoc::OnFdct()
{
	const double PI = 3.14159265;	const double scale = 1 / 2.;	const int N = (width<height? width: height) * scale;	m_Dct = (double*)malloc(sizeof(double) * N*N);	unsigned char *ZoomImage;	ZoomImage = new unsigned char[sizeof(char) * N * N];	for (int y_new = 0; y_new < N; y_new++) {
		for (int x_new = 0; x_new < N; x_new++) {
			double x = x_new / scale;
			double y = y_new / scale;

			int x_org = (int)(x + 0.5);
			int y_org = (int)(y + 0.5);

			ZoomImage[y_new * N + x_new] = m_InImage[y_org * width + x_org];
		}
	}	int u_max, v_max;
	double Sum, Cu, Cv, DCT_max = 0.;	for (int u = 0; u < N; u++) {
		if (u == 0) Cu = sqrt(1. / 2.); else Cu = 1;
		for (int v = 0; v < N; v++) {
			Sum = 0;
			if (v == 0) Cv = sqrt(1. / 2.); else Cv = 1;
			for (int y = 0; y < N; y++) {
				for (int x = 0; x < N; x++) {
					double cosValue1 = cos(v * PI * (2 * y + 1) / (2 * N));
					double cosValue2 = cos(u * PI * (2 * x + 1) / (2 * N));
					Sum += (double)ZoomImage[y*N + x] * cosValue1*cosValue2;
				}
			}
			m_Dct[u*N + v] = 2. / N * Cu*Cv*Sum;
			if (abs((int)m_Dct[u*N + v]) > DCT_max) {
				DCT_max = abs((int)m_Dct[u*N + v]);
				u_max = u;
				v_max = v;
			}
		}
	}	CString strTemp;
	strTemp.Format(_T("(u,v)=(%d,%d)일때 DCT_max값=%5.3f"), u_max, v_max, DCT_max);
	AfxMessageBox(strTemp);	const int threshold = DCT_max * 0.05;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (abs((int)m_Dct[y*N + x]) > threshold)
				m_OutImage[y*width + x] = 255;
			else
				m_OutImage[y*width + x] = abs((int)m_Dct[y*N + x]) * 255 / threshold;
		}
	}

	memset(m_InImage, 0, sizeof(unsigned char) * (width*height));
	
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			m_InImage[y*width + x] = ZoomImage[y*N + x];
		}
	}
	delete[] ZoomImage;

	UpdateAllViews(NULL);}


void CIIPDoc::OnIdct()
{
	const double PI = 3.14159265;
	const double scale = 1 / 2.;
	const int N = (width < height ? width : height) * scale; // IDCT 변환 열
	//m_Dct = (double*) malloc(sizeof(double) * N*N);
	double Sum, Cu, Cv, temp;

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			Sum = 0;
			for (int u = 0; u < N; u++)
			{
				for (int v = 0; v < N; v++)
				{
					if (v == 0) Cv = sqrt(1. / 2.); else Cv = 1;
					if (u == 0) Cu = sqrt(1. / 2.); else Cu = 1;
					double cosValue1 = cos(v * PI * (2 * y + 1) / (2 * N));
					double cosValue2 = cos(u * PI * (2 * x + 1) / (2 * N));
					Sum += Cu * Cv*m_Dct[u*N + v] * cosValue1*cosValue2;
				}
			}
			temp = Sum * 2. / N;
			m_OutImage[y*width + x] = (unsigned char)temp;
		}
	}

	UpdateAllViews(NULL);
}
