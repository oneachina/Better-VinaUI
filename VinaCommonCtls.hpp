#pragma once
#include <variant>
#include "VinaInternalFunctionMapping.hpp"
using namespace VertexUI::Click;


typedef ID2D1DCRenderTarget* DCRT;
typedef ID2D1HwndRenderTarget* HRT;

struct VertexUICtlColor
{
	unsigned long color = VERTEXUICOLOR_MIDNIGHT;
	unsigned long borderColor = VERTEXUICOLOR_MIDNIGHTPLUS;
	unsigned long innerColor = VERTEXUICOLOR_WHITEDRAW;
	unsigned long hoverColor = VERTEXUICOLOR_MIDNIGHT;
	unsigned long hoverBorderColor = VERTEXUICOLOR_MIDNIGHTPLUS;
	unsigned long hoverInnerColor = VERTEXUICOLOR_WHITEDRAW;
	unsigned long activeColor = VERTEXUICOLOR_LAVENDER;
	unsigned long activeBorderColor = VERTEXUICOLOR_MIDNIGHTPLUS;
	unsigned long activeInnerColor = VERTEXUICOLOR_WHITEDRAW;

};
class VinaButton : public VertexUIControl {
public:
	void Set(int x, int y, int cx, int cy, const wchar_t* txt, std::function<void()>events = [] {}, unsigned long clr = VERTEXUICOLOR_MIDNIGHT, int TxtSize = 15, unsigned long TxtColor = VERTEXUICOLOR_WHITE)
	{
		this->func = events;
		this->Clr = clr;
		this->txtsz = TxtSize;
		this->txtClr = TxtColor;
		this->txt = txt;
		this->x = x;
		this->y = y;
		this->cx = cx;
		this->cy = cy;
	}

	virtual void CreateCtl(HWND hWnd, HRT hdc)
	{
		if (Isvalid == false)return;
		RECT rc;
		GetClientRect(hWnd, &rc);
		if (this->IsPushed == true)
		{
			if (flag == 0)
			{
				GlobalAnimationCount++;
				flag = 1;
			}
			if (ap < 10)
			{
				if (flag == 1)
					ap++;
			}
			if (ap >= 10)
			{
				flag = 0;
				GlobalAnimationCount--;
			}

			float num;
			num = CalcBounceCurve(ap, 0, 0.5, 10);
			/*
			CompGdiD2D(hWnd, hdc, [this, num](HWND hWnd, HDC hdc) {
				VertexUI::Window::SimpleShadow::iDropShadow Shadow;
				Shadow.SetSharpness(15);
				Shadow.SetColor(VuiCalcShadow(VERTEXUICOLOR_DARKNIGHT));
				Shadow.SetSize(5 + num * 10);
				Shadow.SetDarkness(100 - (10 - ap) * 5);
				Shadow.SetPosition(0, 0);
				Shadow.Create(hdc, this->x, this->y, this->cx, this->cy, 8);
				});
				*/
			unsigned long nClr;
			int nR, nG, nB;
			nR = GetMaxValue(GetRValue(Clr) + num * 20, 255);
			nG = GetMaxValue(GetGValue(Clr) + num * 20, 255);
			nB = GetMaxValue(GetBValue(Clr) + num * 20, 255);
			nClr = RGB(nR, nG, nB);
			D2DDrawRoundRect(hdc, x + num, y + num, cx - num * 2, cy - num * 2, nClr, 8, 1, 1.0f, VERTEXUICOLOR_MIDNIGHTPLUS);

			D2DDrawText2(hdc, txt.c_str(), x, (float)(y + cy / 2 - txtsz / 1.5), cx, cy, txtsz - num, txtClr, L"Segoe UI", 1, true);
		}
		else if (this->IsHoverd == true)
		{
			if (flag == 0)
			{
				GlobalAnimationCount++;
				flag = 1;
			}
			if (ap < 10)
			{
				if (flag == 1)
					ap++;
			}
			if (ap >= 10)
			{
				flag = 0;
				GlobalAnimationCount--;
			}

			float num;
			num = CalcEaseOutCurve(ap, 0, 0.5, 10);
			/*
			CompGdiD2D(hWnd, hdc, [this, num](HWND hWnd, HDC hdc) {
				VertexUI::Window::SimpleShadow::iDropShadow Shadow;
				Shadow.SetSharpness(15);
				Shadow.SetColor(VuiCalcShadow(VERTEXUICOLOR_DARKNIGHT));
				Shadow.SetSize(5 + num * 10);
				Shadow.SetDarkness(100 - (10 - ap) * 5);
				Shadow.SetPosition(0, 0);
				Shadow.Create(hdc, this->x, this->y, this->cx, this->cy, 8);
				});
				*/
			unsigned long nClr;
			int nR, nG, nB;
			nR = GetMaxValue(GetRValue(Clr) + num * 20, 255);
			nG = GetMaxValue(GetGValue(Clr) + num * 20, 255);
			nB = GetMaxValue(GetBValue(Clr) + num * 20, 255);
			nClr = RGB(nR, nG, nB);
			D2DDrawRoundRect(hdc, x - num, y - num, cx + num * 2, cy + num * 2, nClr, 8, 1, 1.0f + num, VERTEXUICOLOR_MIDNIGHTPLUS);

			D2DDrawText2(hdc, txt.c_str(), x, (float)(y + cy / 2 - txtsz / 1.5), cx, cy, txtsz, txtClr, L"Segoe UI", 1, true);
		}
		else
		{
			if (flag == 0)
			{
				GlobalAnimationCount++;
				flag = 1;
			}
			if (ap > 0)
			{
				if (flag == 1)
					ap--;
			}
			if (ap == 0)
			{
				flag = 0;
				GlobalAnimationCount--;
			}
			float num;
			num = CalcEaseOutCurve(ap, 0, (float)(0.5), 10);
			if (ap != 0)
			{
				/*
				CompGdiD2D(hWnd, hdc, [this, num](HWND hWnd, HDC hdc) {
					VertexUI::Window::SimpleShadow::iDropShadow Shadow;
					Shadow.SetSharpness(15);
					Shadow.SetColor(VuiCalcShadow(VERTEXUICOLOR_DARKNIGHT));
					Shadow.SetSize(5 + num * 10);
					Shadow.SetDarkness(100 - (10 - ap) * 5);
					Shadow.SetPosition(0, 0);
					Shadow.Create(hdc, this->x, this->y, this->cx, this->cy, 8);
					});
					*/
			}
			unsigned long nClr = Clr;
			if (ap != 0)
			{
				int nR, nG, nB;
				nR = GetMaxValue(GetRValue(Clr) + num * 20, 255);
				nG = GetMaxValue(GetGValue(Clr) + num * 20, 255);
				nB = GetMaxValue(GetBValue(Clr) + num * 20, 255);
				nClr = RGB(nR, nG, nB);
			}
			D2DDrawRoundRect(hdc, x - num, y - num, cx + num * 2, cy + num * 2, nClr, 8, 1, 1.0f, VERTEXUICOLOR_MIDNIGHTPLUS);
			D2DDrawText2(hdc, txt.c_str(), x, (float)(y + cy / 2 - txtsz / 1.5), cx, cy, txtsz, txtClr, L"Segoe UI", 1, true);
		}
	}
	void SetValidity(bool v)
	{
		Isvalid = v;
	}
	virtual int OnMouseUp()
	{
		ap = 0;
		Refresh(hWnd);
		func();
		//if(func)vinaFuncMap[_event.c_str()]();
		return 0;
	}
	virtual int OnMouseDown()
	{
		ap = 0;
		this->IsPushed = true;
		Refresh(hWnd);
		return 0;
	}
	virtual int AddEvent(const vinaPoint& pt, vinaEvent eventtype)
	{
		if (Isvalid == false)return 0;
		if (eventtype == vinaEvent::mouseUp)this->OnMouseUp();
		if (eventtype == vinaEvent::mouseDown)this->OnMouseDown();

		if (eventtype == vinaEvent::mouseOver) {

			this->IsHoverd = true;
			Refresh(hWnd);
		}
		return 0;
	}
	virtual void CreateInheritedCtl(HWND hWnd, HRT hdc, std::shared_ptr<VinaButton> vuic)
	{
		this->hWnd = hWnd;
		CreateCtl(hWnd, hdc);
	}
	virtual VertexUIPos GetCurrentRect() {
		VertexUIPos _{ x,y,cx,cy };
		return _;
	}
	void SetInternalEvent(std::wstring ev)
	{
		this->_event = ev;
	}

	std::wstring txt;
	std::wstring c;
	std::wstring _event = L"";
	unsigned long Clr;

	int id = -1;
protected:
	bool Isvalid = true;
	HWND hWnd;
	int ap = 0;
	int flag = 0;
	float txtsz = 15;
	unsigned long txtClr;
	std::function<void()>func;
	std::wstring text;
};
class VinaNotice : public VertexUIControl {
public:
	void Set(int x, int y, int cx, int cy, const wchar_t* txt, unsigned long clr = VERTEXUICOLOR_SEA, int TxtSize = 14, unsigned long TxtColor = VERTEXUICOLOR_WHITE, std::function<void()>events = [] {})
	{
		this->func = events;
		this->Clr = clr;
		this->txtsz = TxtSize;
		this->txtClr = TxtColor;
		this->txt = txt;
		this->x = x;
		this->y = y;
		this->cx = cx;
		this->cy = cy;
	}

	virtual void CreateCtl(HWND hWnd, HRT hdc)
	{
		RECT rc;
		GetClientRect(hWnd, &rc);
		if (this->IsPushed == true)
		{
			if (flag == 0)
			{
				GlobalAnimationCount++;
				flag = 1;
			}
			if (ap < 10)
			{
				if (flag == 1)
					ap++;
			}
			if (ap >= 10)
			{
				flag = 0;
				GlobalAnimationCount--;
			}

			float num;
			num = CalcBounceCurve(ap, 0, 0.5, 10);
			/*
			CompGdiD2D(hWnd, hdc, [this, num](HWND hWnd, HDC hdc) {
				VertexUI::Window::SimpleShadow::iDropShadow Shadow;
				Shadow.SetSharpness(15);
				Shadow.SetColor(VuiCalcShadow(VERTEXUICOLOR_DARKNIGHT));
				Shadow.SetSize(5 + num * 10);
				Shadow.SetDarkness(100 - (10 - ap) * 5);
				Shadow.SetPosition(0, 0);
				Shadow.Create(hdc, this->x, this->y, this->cx, this->cy, 8);
				});
				*/
			unsigned long nClr;
			int nR, nG, nB;
			nR = GetMaxValue(GetRValue(Clr) + num * 20, 255);
			nG = GetMaxValue(GetGValue(Clr) + num * 20, 255);
			nB = GetMaxValue(GetBValue(Clr) + num * 20, 255);
			nClr = RGB(nR, nG, nB);
			D2DDrawRoundRect(hdc, x + num, y + num, cx - num * 2, cy - num * 2, Clr, 8, 1, 1.0f, VuiFadeColor(Clr, 40));

			D2DDrawText2(hdc, txt.c_str(), x + 10, (float)(y + cy / 2 - txtsz / 1.5), cx, cy, txtsz - num, txtClr, L"Segoe UI", 1, false);
		}
		else if (this->IsHoverd == true)
		{
			if (flag == 0)
			{
				GlobalAnimationCount++;
				flag = 1;
			}
			if (ap < 10)
			{
				if (flag == 1)
					ap++;
			}
			if (ap >= 10)
			{
				flag = 0;
				GlobalAnimationCount--;
			}

			float num;
			num = CalcEaseOutCurve(ap, 0, 0.5, 10);
			/*
			CompGdiD2D(hWnd, hdc, [this, num](HWND hWnd, HDC hdc) {
				VertexUI::Window::SimpleShadow::iDropShadow Shadow;
				Shadow.SetSharpness(15);
				Shadow.SetColor(VuiCalcShadow(VERTEXUICOLOR_DARKNIGHT));
				Shadow.SetSize(5 + num * 10);
				Shadow.SetDarkness(100 - (10 - ap) * 5);
				Shadow.SetPosition(0, 0);
				Shadow.Create(hdc, this->x, this->y, this->cx, this->cy, 8);
				});
				*/
			unsigned long nClr;
			int nR, nG, nB;
			nR = GetMaxValue(GetRValue(Clr) + num * 20, 255);
			nG = GetMaxValue(GetGValue(Clr) + num * 20, 255);
			nB = GetMaxValue(GetBValue(Clr) + num * 20, 255);
			nClr = RGB(nR, nG, nB);
			D2DDrawRoundRect(hdc, x - num, y - num, cx + num * 2, cy + num * 2, Clr, 8, 1, 1.0f + num, VuiFadeColor(Clr, 40));

			D2DDrawText2(hdc, txt.c_str(), x + 10, (float)(y + cy / 2 - txtsz / 1.5), cx, cy, txtsz, txtClr, L"Segoe UI", 1, false);
		}
		else
		{
			if (flag == 0)
			{
				GlobalAnimationCount++;
				flag = 1;
			}
			if (ap > 0)
			{
				if (flag == 1)
					ap--;
			}
			if (ap == 0)
			{
				flag = 0;
				GlobalAnimationCount--;
			}
			float num;
			num = CalcEaseOutCurve(ap, 0, (float)(0.5), 10);
			if (ap != 0)
			{
				/*
				CompGdiD2D(hWnd, hdc, [this, num](HWND hWnd, HDC hdc) {
					VertexUI::Window::SimpleShadow::iDropShadow Shadow;
					Shadow.SetSharpness(15);
					Shadow.SetColor(VuiCalcShadow(VERTEXUICOLOR_DARKNIGHT));
					Shadow.SetSize(5 + num * 10);
					Shadow.SetDarkness(100 - (10 - ap) * 5);
					Shadow.SetPosition(0, 0);
					Shadow.Create(hdc, this->x, this->y, this->cx, this->cy, 8);
					});
					*/
			}
			unsigned long nClr = Clr;
			if (ap != 0)
			{
				int nR, nG, nB;
				nR = GetMaxValue(GetRValue(Clr) + num * 20, 255);
				nG = GetMaxValue(GetGValue(Clr) + num * 20, 255);
				nB = GetMaxValue(GetBValue(Clr) + num * 20, 255);
				nClr = RGB(nR, nG, nB);
			}
			D2DDrawRoundRect(hdc, x - num, y - num, cx + num * 2, cy + num * 2, Clr, 8, 1, 1.0f + num, VuiFadeColor(Clr, 40));

			D2DDrawText2(hdc, txt.c_str(), x + 10, (float)(y + cy / 2 - txtsz / 1.5), cx, cy, txtsz, txtClr, L"Segoe UI", 1, false);
		}
	}

	virtual int OnMouseUp()
	{
		ap = 0;
		Refresh(hWnd);
		func();
		//if(func)vinaFuncMap[_event.c_str()]();
		return 0;
	}
	virtual int OnMouseDown()
	{
		ap = 0;
		this->IsPushed = true;
		Refresh(hWnd);
		return 0;
	}
	virtual int AddEvent(const vinaPoint& pt, vinaEvent eventtype)
	{

		if (eventtype == vinaEvent::mouseUp)this->OnMouseUp();
		if (eventtype == vinaEvent::mouseDown)this->OnMouseDown();

		if (eventtype == vinaEvent::mouseOver) {

			this->IsHoverd = true;
			Refresh(hWnd);
		}
		return 0;
	}
	virtual void CreateInheritedCtl(HWND hWnd, HRT hdc, std::shared_ptr<VinaNotice > vuic)
	{
		this->hWnd = hWnd;
		CreateCtl(hWnd, hdc);
	}
	virtual VertexUIPos GetCurrentRect() {
		VertexUIPos _{ x,y,cx,cy };
		return _;
	}
	void SetInternalEvent(std::wstring ev)
	{
		this->_event = ev;
	}

	std::wstring txt;
	std::wstring c;
	std::wstring _event = L"";
	unsigned long Clr;

	int id = -1;
protected:

	HWND hWnd;
	int ap = 0;
	int flag = 0;
	float txtsz = 15;
	unsigned long txtClr;
	std::function<void()>func;
	std::wstring text;
};
class VinaText : public VertexUIControl {
public:
	void Set(int x, int y, int cx, int cy, const wchar_t* txt, int TxtSize = 15, unsigned long TxtColor = VERTEXUICOLOR_WHITE, std::function<void()>events = [] {})
	{
		this->func = events;
		this->txtsz = TxtSize;
		this->Clr = TxtColor;
		this->txt = txt;
		this->x = x;
		this->y = y;
		this->cx = cx;
		this->cy = cy;
	}
	virtual void CreateCtl(HWND hWnd, HRT hdc)
	{
		RECT rc;
		GetClientRect(hWnd, &rc);

		if (GetPtInfo(hWnd, x, y, cx, cy))
		{

			if (flag == 0)
			{
				GlobalAnimationCount++;
				flag = 1;
			}
			if (ap < 10)
			{
				if (flag == 1)
					ap++;
			}
			if (ap >= 10)
			{
				flag = 0;
				GlobalAnimationCount--;
			}

			float num;
			num = CalcEaseOutCurve(ap, 0, 0.5, 10);
			unsigned long nClr;
			int nR, nG, nB;
			int fact = 1;
			if (VuiColorAverage(Clr) > 128)fact = -2;
			nR = GetMaxValue(GetRValue(Clr) + num * 20 * fact, 255);
			nG = GetMaxValue(GetGValue(Clr) + num * 20 * fact, 255);
			nB = GetMaxValue(GetBValue(Clr) + num * 20 * fact, 255);
			nClr = RGB(nR, nG, nB);
			D2DDrawText(hdc, txt.c_str(), x, (float)(y + cy / 2 - txtsz / 1.5), cx, cy, txtsz, nClr, L"Segoe UI", 1);
		}
		else
		{
			if (flag == 0)
			{
				GlobalAnimationCount++;
				flag = 1;
			}
			if (ap > 0)
			{
				if (flag == 1)
					ap--;
			}
			if (ap == 0)
			{
				flag = 0;
				GlobalAnimationCount--;
			}
			float num;
			num = CalcEaseOutCurve(ap, 0, (float)(0.5), 10);
			unsigned long nClr = Clr;
			if (ap != 0)
			{
				int nR, nG, nB;
				int fact = 1;
				if (VuiColorAverage(Clr) > 128)fact = -2;
				nR = GetMaxValue(GetRValue(Clr) + num * 20 * fact, 255);
				nG = GetMaxValue(GetGValue(Clr) + num * 20 * fact, 255);
				nB = GetMaxValue(GetBValue(Clr) + num * 20 * fact, 255);
				nClr = RGB(nR, nG, nB);
			}
			D2DDrawText(hdc, txt.c_str(), x, (float)(y + cy / 2 - txtsz / 1.5), cx, cy, txtsz, nClr, L"Segoe UI", 1);
		}
	}
	virtual int OnMouseUp()
	{
		this->func();
		//if(func)vinaFuncMap[_event.c_str()]();
		return 0;
	}
	virtual int OnMouseDown()
	{



		return 0;
	}
	virtual int AddEvent(const vinaPoint& pt, vinaEvent eventtype)
	{

		if (eventtype == vinaEvent::mouseUp)this->OnMouseUp();
		if (eventtype == vinaEvent::mouseDown)this->OnMouseDown();

		if (eventtype == vinaEvent::mouseOver) {

			this->IsHoverd = true;
			Refresh(hWnd);
		}
		return 0;
	}
	virtual VertexUIPos GetCurrentRect() {
		VertexUIPos _{ x,y,cx,cy };
		return _;
	}
	virtual void CreateInheritedCtl(HWND hWnd, HRT hdc, std::shared_ptr<VinaText> vuic)
	{
		this->hWnd = hWnd;
		CreateCtl(hWnd, hdc);
	}
	std::wstring txt;
	std::wstring c;
	std::wstring _event;
	unsigned long Clr;

	int id = -1;
protected:
	int x, y, cx, cy;
	HWND hWnd;
	int ap = 0;
	int flag = 0;
	float txtsz = 15;
	unsigned long txtClr;
	std::function<void()>func;
	std::wstring text;
};
class VinaFAIcon : public VertexUIControl {
public:
	std::wstring CvtFont(std::wstring from)
	{
		if (from == std::wstring(L"test-right"))return std::wstring(L"\uf178");
		if (from == std::wstring(L"test-right-upd"))return std::wstring(L"\uf178");
		if (from == std::wstring(L"test-right-dld"))return std::wstring(L"\uf178");
		if (from == std::wstring(L"win-close"))return std::wstring(L"\uf00d");
		if (from == std::wstring(L"win-max"))return std::wstring(L"\uf065");
		if (from == std::wstring(L"win-winmax"))return std::wstring(L"\uf424");
		if (from == std::wstring(L"win-winrestore"))return std::wstring(L"\uf422");
		if (from == std::wstring(L"win-min"))return std::wstring(L"\uf068");
		if (from == std::wstring(L"win-restore"))return std::wstring(L"\uf066");
		if (from == std::wstring(L"test-left"))return std::wstring(L"\uf177");
		if (from == std::wstring(L"test-more"))return std::wstring(L"\uf141");
		if (from == std::wstring(L"test-more2"))return std::wstring(L"\uf52c");
		if (from == std::wstring(L"test-more3"))return std::wstring(L"\uf142");
	}
	void Set(int x, int y, const wchar_t* txt, int TxtSize = 15, unsigned long TxtColor = VERTEXUICOLOR_WHITE, std::function<void()>events = [] {})
	{
		this->func = events;
		this->txtsz = TxtSize;
		this->Clr = TxtColor;
		this->txt = txt;
		this->x = x;
		this->y = y;
		this->cx = TxtSize;
		this->cy = TxtSize;
	}
	void Set(int x, int y, int cx, const wchar_t* txt, int TxtSize = 15, unsigned long TxtColor = VERTEXUICOLOR_WHITE, std::function<void()>events = [] {})
	{
		this->func = events;
		this->txtsz = TxtSize;
		this->Clr = TxtColor;
		this->txt = txt;
		this->x = x;
		this->y = y;
		this->cx = cx;
		this->cy = TxtSize;
	}
	virtual void CreateCtl(HWND hWnd, HRT hdc)
	{
		RECT rc;
		GetClientRect(hWnd, &rc);

		if (GetPtInfo(hWnd, x, y, cx, cy))
		{

			if (flag == 0)
			{
				GlobalAnimationCount++;
				flag = 1;
			}
			if (ap < 10)
			{
				if (flag == 1)
					ap++;
			}
			if (ap >= 10)
			{
				flag = 0;
				GlobalAnimationCount--;
			}

			float num;
			num = CalcEaseOutCurve(ap, 0, 0.5, 10);
			unsigned long nClr;
			int nR, nG, nB;
			int fact = 1;
			if (VuiColorAverage(Clr) > 128)fact = -2;
			nR = GetMaxValue(GetRValue(Clr) + num * 20 * fact, 255);
			nG = GetMaxValue(GetGValue(Clr) + num * 20 * fact, 255);
			nB = GetMaxValue(GetBValue(Clr) + num * 20 * fact, 255);
			nClr = RGB(nR, nG, nB);
			std::wstring newStr = this->CvtFont(txt.c_str());
			if (txt == std::wstring(L"test-left"))
			{
				D2DDrawText(hdc, newStr.c_str(), x - num * 3, (float)(y + cy / 2 - txtsz / 1.5), cx, cy, txtsz, nClr, L"Font Awesome 6 Free Solid", 1);
			}
			else if (txt == std::wstring(L"test-right"))
			{
				D2DDrawText(hdc, newStr.c_str(), x + num * 3, (float)(y + cy / 2 - txtsz / 1.5), cx, cy, txtsz, nClr, L"Font Awesome 6 Free Solid", 1);
			}
			else if (txt == std::wstring(L"test-right-upd"))
			{
				D2DDrawText3(hdc, L"现在更新", x - 5 + num * 3, (float)(y + cy / 2 - txtsz / 1.5), cx, cy, txtsz - 4, nClr, L"Segoe UI", 1);
				D2DDrawText(hdc, newStr.c_str(), x + cx - txtsz + num * 3, (float)(y + 1 + cy / 2 - txtsz / 1.5), cx, cy, txtsz, nClr, L"Font Awesome 6 Free Solid", 1);
			}
			else if (txt == std::wstring(L"test-right-dld"))
			{
				D2DDrawText3(hdc, L"下载", x - 5 + num * 3, (float)(y + cy / 2 - txtsz / 1.5), cx, cy, txtsz - 4, nClr, L"Segoe UI", 1);
				D2DDrawText(hdc, newStr.c_str(), x + cx - txtsz + num * 3, (float)(y + 1 + cy / 2 - txtsz / 1.5), cx, cy, txtsz, nClr, L"Font Awesome 6 Free Solid", 1);
			}
			else D2DDrawText(hdc, newStr.c_str(), x, (float)(y + cy / 2 - txtsz / 1.5), cx, cy, txtsz, nClr, L"Font Awesome 6 Free Solid", 1);
		}
		else
		{
			if (flag == 0)
			{
				GlobalAnimationCount++;
				flag = 1;
			}
			if (ap > 0)
			{
				if (flag == 1)
					ap--;
			}
			if (ap == 0)
			{
				flag = 0;
				GlobalAnimationCount--;
			}
			float num;
			num = CalcEaseOutCurve(ap, 0, (float)(0.5), 10);
			unsigned long nClr = Clr;
			if (ap != 0)
			{
				int nR, nG, nB;
				int fact = 1;
				if (VuiColorAverage(Clr) > 128)fact = -2;
				nR = GetMaxValue(GetRValue(Clr) + num * 20 * fact, 255);
				nG = GetMaxValue(GetGValue(Clr) + num * 20 * fact, 255);
				nB = GetMaxValue(GetBValue(Clr) + num * 20 * fact, 255);
				nClr = RGB(nR, nG, nB);
			}
			std::wstring newStr = this->CvtFont(txt.c_str());
			if (txt == std::wstring(L"test-left"))
			{
				D2DDrawText(hdc, newStr.c_str(), x - num * 3, (float)(y + cy / 2 - txtsz / 1.5), cx, cy, txtsz, nClr, L"Font Awesome 6 Free Solid", 1);
			}
			else if (txt == std::wstring(L"test-right"))
			{
				D2DDrawText(hdc, newStr.c_str(), x + num * 3, (float)(y + cy / 2 - txtsz / 1.5), cx, cy, txtsz, nClr, L"Font Awesome 6 Free Solid", 1);
			}
			else if (txt == std::wstring(L"test-right-upd"))
			{
				D2DDrawText3(hdc, L"现在更新", x - 5 + num * 3, (float)(y + cy / 2 - txtsz / 1.5), cx, cy, txtsz - 4, nClr, L"Segoe UI", 1);
				D2DDrawText(hdc, newStr.c_str(), x + cx - txtsz + num * 3, (float)(y + 1 + cy / 2 - txtsz / 1.5), cx, cy, txtsz, nClr, L"Font Awesome 6 Free Solid", 1);
			}
			else if (txt == std::wstring(L"test-right-dld"))
			{
				D2DDrawText3(hdc, L"下载", x - 5 + num * 3, (float)(y + cy / 2 - txtsz / 1.5), cx, cy, txtsz - 4, nClr, L"Segoe UI", 1);
				D2DDrawText(hdc, newStr.c_str(), x + cx - txtsz + num * 3, (float)(y + 1 + cy / 2 - txtsz / 1.5), cx, cy, txtsz, nClr, L"Font Awesome 6 Free Solid", 1);
			}
			else D2DDrawText(hdc, newStr.c_str(), x, (float)(y + cy / 2 - txtsz / 1.5), cx, cy, txtsz, nClr, L"Font Awesome 6 Free Solid", 1);

		}
	}
	virtual int OnMouseUp()
	{
		this->func();
		//if(func)vinaFuncMap[_event.c_str()]();
		return 0;
	}
	virtual int OnMouseDown()
	{



		return 0;
	}
	virtual int AddEvent(const vinaPoint& pt, vinaEvent eventtype)
	{

		if (eventtype == vinaEvent::mouseUp)this->OnMouseUp();
		if (eventtype == vinaEvent::mouseDown)this->OnMouseDown();

		if (eventtype == vinaEvent::mouseOver) {

			this->IsHoverd = true;
			Refresh(hWnd);
		}
		return 0;
	}
	virtual VertexUIPos GetCurrentRect() {
		VertexUIPos _{ x,y,cx,cy };
		return _;
	}
	virtual void CreateInheritedCtl(HWND hWnd, HRT hdc, std::shared_ptr<VinaFAIcon> vuic)
	{
		this->hWnd = hWnd;
		CreateCtl(hWnd, hdc);
	}
	std::wstring txt;
	std::wstring c;
	std::wstring _event;
	unsigned long Clr;

	int id = -1;
protected:
	int x, y, cx, cy;
	HWND hWnd;
	int ap = 0;
	int flag = 0;
	float txtsz = 15;
	unsigned long txtClr;
	std::function<void()>func;
	std::wstring text;
};
class VinaSwitch : public VertexUIControl {
public:
	void Set(int x, int y, int cx, int cy, VertexUICtlColor ci, std::function<void()>events = [] {})
	{
		this->func = events;
		this->Clr = ci.color;
		this->borderClr = ci.borderColor;
		this->innerClr = ci.innerColor;
		this->aBorderClr = ci.activeBorderColor;
		this->aClr = ci.activeColor;
		this->aInnerClr = ci.activeInnerColor;
		this->x = x;
		this->y = y;
		this->cx = cx;
		this->cy = cy;
	}
	virtual void CreateCtl(HWND hWnd, HRT hdc)
	{
		RECT rc;
		GetClientRect(hWnd, &rc);

		if (GetPtInfo(hWnd, x, y, cx, cy))
		{

			if (flag == 0)
			{
				GlobalAnimationCount++;
				flag = 1;
			}
			if (ap < 10)
			{
				if (flag == 1)
					ap++;
			}
			if (ap >= 10)
			{
				flag = 0;
				GlobalAnimationCount--;

			}


			float num;
			num = CalcEaseOutCurve(ap, 0, 0.5, 10);
			CompGdiD2D(hWnd, hdc, [this, num](HWND hWnd, HDC hdc) {
				VertexUI::Window::SimpleShadow::iDropShadow Shadow;
				Shadow.SetSharpness(25);
				Shadow.SetColor(VuiCalcShadow(VERTEXUICOLOR_DARKNIGHT));
				Shadow.SetSize(5 + num * 10);
				Shadow.SetDarkness(100 - (10 - ap) * 5);
				Shadow.SetPosition(0, 0);
				Shadow.Create(hdc, this->x, this->y, this->cx, this->cy, cy / 2);
				});
			unsigned long nClr;
			int nR, nG, nB;
			nR = GetMaxValue(GetRValue(Clr) + num * 20, 255);
			nG = GetMaxValue(GetGValue(Clr) + num * 20, 255);
			nB = GetMaxValue(GetBValue(Clr) + num * 20, 255);
			nClr = RGB(nR, nG, nB);
			int dist = cy * 0.15;
			int innerBlockSize = cy - dist * 2;
			if (value == false)
			{
				D2DDrawRoundRect(hdc, x, y, cx, cy, nClr, cy / 2, 1, 1.0f, borderClr);
				D2DDrawRoundRect(hdc, x + dist, y + dist, innerBlockSize, innerBlockSize, innerClr, cy / 2, 1, 1.0f, borderClr);
			}
			else {
				D2DDrawRoundRect(hdc, x, y, cx, cy, aClr, cy / 2, 1, 1.0f, aBorderClr);
				D2DDrawRoundRect(hdc, x + cx - innerBlockSize - dist, y + dist, innerBlockSize, innerBlockSize, aInnerClr, cy / 2, 1, 1.0f, aBorderClr);
			}

		}
		else
		{
			if (flag == 0)
			{
				GlobalAnimationCount++;
				flag = 1;
			}
			if (ap > 0)
			{
				if (flag == 1)
					ap--;
			}
			if (ap == 0)
			{
				flag = 0;
				GlobalAnimationCount--;
			}
			float num;
			num = CalcEaseOutCurve(ap, 0, (float)(0.5), 10);
			if (ap != 0)
			{
				CompGdiD2D(hWnd, hdc, [this, num](HWND hWnd, HDC hdc) {
					VertexUI::Window::SimpleShadow::iDropShadow Shadow;
					Shadow.SetSharpness(25);
					Shadow.SetColor(VuiCalcShadow(VERTEXUICOLOR_DARKNIGHT));
					Shadow.SetSize(5 + num * 10);
					Shadow.SetDarkness(100 - (10 - ap) * 5);
					Shadow.SetPosition(0, 0);
					Shadow.Create(hdc, this->x, this->y, this->cx, this->cy, cy / 2);
					});
			}
			unsigned long nClr = Clr;
			if (ap != 0)
			{
				int nR, nG, nB;
				nR = GetMaxValue(GetRValue(Clr) + num * 20, 255);
				nG = GetMaxValue(GetGValue(Clr) + num * 20, 255);
				nB = GetMaxValue(GetBValue(Clr) + num * 20, 255);
				nClr = RGB(nR, nG, nB);
			}
			int dist = cy * 0.15;
			int innerBlockSize = cy - dist * 2;
			if (value == false)
			{
				D2DDrawRoundRect(hdc, x, y, cx, cy, nClr, cy / 2, 1, 1.0f, borderClr);
				D2DDrawRoundRect(hdc, x + dist, y + dist, innerBlockSize, innerBlockSize, innerClr, cy / 2, 1, 1.0f, borderClr);
			}
			else {
				D2DDrawRoundRect(hdc, x, y, cx, cy, aClr, cy / 2, 1, 1.0f, aBorderClr);
				D2DDrawRoundRect(hdc, x + cx - innerBlockSize - dist, y + dist, innerBlockSize, innerBlockSize, aInnerClr, cy / 2, 1, 1.0f, aBorderClr);
			}
		}
	}
	virtual int AddEvent()
	{
		if (GetPtInfo(hWnd, x, y, cx, cy))
		{
			if (ClickMsg == 1)
			{
				ClickMsg = 0;
				preValue = value;
				value = !value;
				Refresh(hWnd);
			}
			if (KeepDownMsg == 1)
			{

			}
			if (RClickMsg == 1)
			{
				RClickMsg = 0;

			}
			if (hState == 0)
			{
				Refresh(hWnd);
				hState = 1;
			}
			return 0;
		}
		return -1;
	}
	virtual void CreateInheritedCtl(HWND hWnd, HRT hdc, VinaSwitch* vuic)
	{
		this->hWnd = hWnd;
		CreateCtl(hWnd, hdc);
	}
	bool GetValue()
	{
		return this->value;
	}
	void SetValue(bool val)
	{
		this->value = val;
	}
	std::wstring txt;
	std::wstring c;
	std::wstring _event;


	int id = -1;
protected:
	int x, y, cx, cy;
	HWND hWnd;
	int ap = 0;
	int ap2 = 0;
	int flag = 0;
	unsigned long innerClr;
	unsigned long borderClr;
	unsigned long Clr;
	unsigned long aInnerClr;
	unsigned long aBorderClr;
	unsigned long aClr;
	std::function<void()>func;
	bool value = false;
	bool preValue;
};

class VinaCaptionBar : public VertexUIControl {
public:
	void Set(int x, int y, int cx, int cy, const wchar_t* txt, unsigned long clr = VERTEXUICOLOR_MIDNIGHT, int TxtSize = 15, unsigned long TxtColor = VERTEXUICOLOR_WHITE, std::function<void()>events = [] {})
	{
		this->func = events;
		this->Clr = clr;
		this->txtsz = TxtSize;
		this->txtClr = TxtColor;
		this->txt = txt;
		this->x = x;
		this->y = y;
		this->cx = cx;
		this->cy = cy;
	}

	virtual void CreateCtl(HWND hWnd, HRT hdc)
	{
		RECT rc;
		GetClientRect(hWnd, &rc);
		D2DDrawSolidRect(hdc, x, y, cx, cy, Clr, 1);
		D2DDrawText2(hdc, txt.c_str(), x + 20, y + 10, cx, cy, txtsz, txtClr, L"Segoe UI", 1, false);
	}

	virtual int OnMouseUp()
	{
		Refresh(hWnd);
		//if(func)vinaFuncMap[_event.c_str()]();
		return 0;
	}
	virtual int OnMouseDown()
	{
		SendMessage(hWnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);
		Refresh(hWnd);
		func();
		return 0;
	}
	virtual int AddEvent(const vinaPoint& pt, vinaEvent eventtype)
	{

		if (eventtype == vinaEvent::mouseUp)this->OnMouseUp();
		if (eventtype == vinaEvent::mouseDown)this->OnMouseDown();

		if (eventtype == vinaEvent::mouseOver) {

		}
		return 0;
	}
	virtual void CreateInheritedCtl(HWND hWnd, HRT hdc, std::shared_ptr<VinaCaptionBar> vuic)
	{
		this->hWnd = hWnd;
		CreateCtl(hWnd, hdc);
	}
	virtual VertexUIPos GetCurrentRect() {
		VertexUIPos _{ x,y,cx,cy };
		return _;
	}
	void SetInternalEvent(std::wstring ev)
	{
		this->_event = ev;
	}

	std::wstring txt;
	std::wstring c;
	std::wstring _event = L"";
	unsigned long Clr;

	int id = -1;
protected:

	HWND hWnd;
	int ap = 0;
	int flag = 0;
	float txtsz = 15;
	unsigned long txtClr;
	std::function<void()>func;
	std::wstring text;
};

class VinaMultiTextBox : public VertexUIControl {
public:
	void Set(int x, int y, int cx, int cy, const wchar_t* txt, int TxtSize = 15, unsigned long TxtColor = VERTEXUICOLOR_WHITE, unsigned long clr = VERTEXUICOLOR_MIDNIGHT)
	{
		//this->func = events;
		this->Clr = clr;
		this->txtsz = TxtSize;
		this->txtClr = TxtColor;
		this->txt = txt;
		this->x = x;
		this->y = y;
		this->cx = cx;
		this->cy = cy;
	}

	int GetTxtLine2(const wchar_t* str) {
		int n = 0;
		if (NULL == str) return 0;
		if (str[0] == 0) return 0;
		while (*str) { if (*str == L'\n') n++; str++; }
		if (str[-1] != L'\n') n++;//最后一行末尾没有'\n'也算一行
		return n;
	}
	virtual void CreateCtl(HWND hWnd, HRT hdc)
	{
		RECT rc;
		GetClientRect(hWnd, &rc);
		ScrollDepth += this->GetParent()->GetInstantScrollDepth();


		int TextArea = (GetTxtLine2(this->txt.c_str()) * txtsz * gScale);
		//	MonitorValue(TextArea);
		ScrollDepth = GetMaxValue(GetMinValue(ScrollDepth, 1), TextArea - cy);
		//	MonitorValue(ScrollDepth);
		float SlideRate = static_cast<float>(TextArea) / cy;
		float BlankRate = static_cast<float>(TextArea) / GetMinValue(ScrollDepth, 1);
		float dist = (cy / BlankRate);
		float height = (cy / SlideRate);

		D2DDrawRoundRect(hdc, x, y, cx, cy, VuiFadeColor(VERTEXUICOLOR_MIDNIGHT, 10), 12, 1, 2, VERTEXUICOLOR_MIDNIGHTPLUS);
		D2DDrawInClippedRoundRect(hWnd, hdc, x, y, cx, cy, 12,
			[this, dist, height](HWND hWnd, HRT hdc2, int x, int y, int cx, int cy)->void {
				D2DDrawText(hdc2, this->txt.c_str(), x + 20, y + 20 - GetMinValue(ScrollDepth, 1), cx + 240, cy + 240, this->txtsz, VERTEXUICOLOR_WHITE);
				D2DDrawRoundRect(hdc2, x + cx - 6, y + dist, 5, height, VuiFadeColor(VERTEXUICOLOR_MIDNIGHT, 40), 4, 1, 0, VERTEXUICOLOR_MIDNIGHTPLUS);
			}
		);

	}

	virtual int OnMouseUp()
	{
		//ap = 0;
		Refresh(hWnd);
		//func();
		//if(func)vinaFuncMap[_event.c_str()]();
		return 0;
	}
	virtual int OnMouseDown()
	{
		//	ap = 0;
		this->IsPushed = true;
		Refresh(hWnd);
		return 0;
	}
	virtual int AddEvent(const vinaPoint& pt, vinaEvent eventtype)
	{

		if (eventtype == vinaEvent::mouseUp)this->OnMouseUp();
		if (eventtype == vinaEvent::mouseDown)this->OnMouseDown();

		if (eventtype == vinaEvent::mouseOver) {

			this->IsHoverd = true;
			Refresh(hWnd);
		}
		return 0;
	}
	virtual void CreateInheritedCtl(HWND hWnd, HRT hdc, std::shared_ptr< VinaMultiTextBox> vuic)
	{
		this->hWnd = hWnd;
		CreateCtl(hWnd, hdc);
	}
	virtual VertexUIPos GetCurrentRect() {
		VertexUIPos _{ x,y,cx,cy };
		return _;
	}
	void SetInternalEvent(std::wstring ev)
	{
		this->_event = ev;
	}

	std::wstring txt;
	std::wstring c;
	std::wstring _event = L"";
	unsigned long Clr;

	int id = -1;
protected:
	int ScrollDepth = 0;
	HWND hWnd;
	int ap = 0;
	int flag = 0;
	float txtsz = 15;
	unsigned long txtClr;
	std::function<void()>func;
	std::wstring text;
};
class VinaBarrier : public VertexUIControl {
public:
	void Set(int x, int y, int cx, int cy, std::function<void()>fun = [] {})
	{
		this->x = x;
		this->y = y;
		this->cx = cx;
		this->cy = cy;
		this->func = fun;
	}
	virtual void CreateCtl(HWND hWnd, HRT hdc)
	{

	}

	virtual int OnMouseUp()
	{
		//ap = 0;
		Refresh(hWnd);
		//func();
		//if(func)vinaFuncMap[_event.c_str()]();
		return 0;
	}
	virtual int OnMouseDown()
	{
		//	ap = 0;
		//this->IsPushed = true;
		func();
		Refresh(hWnd);
		return 0;
	}
	virtual int AddEvent(const vinaPoint& pt, vinaEvent eventtype)
	{

		if (eventtype == vinaEvent::mouseUp)this->OnMouseUp();
		if (eventtype == vinaEvent::mouseDown)this->OnMouseDown();

		if (eventtype == vinaEvent::mouseOver) {

			this->IsHoverd = true;
			Refresh(hWnd);
		}
		return 0;
	}
	virtual void CreateInheritedCtl(HWND hWnd, HRT hdc, std::shared_ptr< VinaBarrier> vuic)
	{
		this->hWnd = hWnd;
		CreateCtl(hWnd, hdc);
	}
	virtual VertexUIPos GetCurrentRect() {
		VertexUIPos _{ x,y,cx,cy };
		return _;
	}
	void SetInternalEvent(std::wstring ev)
	{
		this->_event = ev;
	}

	std::wstring txt;
	std::wstring c;
	std::wstring _event = L"";
	unsigned long Clr;

	int id = -1;
protected:
	int ScrollDepth = 0;
	HWND hWnd;
	int ap = 0;
	int flag = 0;
	float txtsz = 15;
	unsigned long txtClr;
	std::function<void()>func;
	std::wstring text;
};
class VinaSlider : public VertexUIControl {
public:
	void Set(int x, int y, int cx, int cy, int Value = -1, unsigned long clr = VERTEXUICOLOR_DARKEN, const wchar_t* placeholder = L"", std::function<void()>events = [] {})
	{
		this->func = events;
		this->txt = placeholder;
		this->x = x - 10;
		this->y = y - 10;
		this->cx = cx + 20;
		this->cy = cy + 20;
		if (Value != -1)this->Value = Value;
		this->Clr = clr;
	}

	virtual void CreateCtl(HWND hWnd, HRT hdc)
	{
		RECT rc;
		GetClientRect(hWnd, &rc);

		RECT crc;

		double progress = ((double)(cx - 20) * Value) / 100.0;
		D2DDrawRoundRect(hdc, x + 10, y + 10, cx - 20, cy - 20, VuiFadeColor(Clr, 60), 8, 0.2f, 2, VuiFadeColor(Clr, 100), 0.6f);
		D2DDrawRoundRect(hdc, x + 10, y + 10, progress, cy - 20, VuiFadeColor(Clr, 10), 8);
		D2DDrawText2(hdc, this->txt.c_str(), x + 10, y + 12, cx - 20, cy - 20, 12, VuiFadeColor(Clr, 120), L"Segoe UI", 0.75f, true);
	}

	virtual int OnMouseUp()
	{

		this->OnEdit = false;
		Refresh(hWnd);
		return 0;
	}
	virtual int OnMouseDown()
	{
		this->OnEdit = true;
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(hWnd, &pt);
		double p = (static_cast<double>(pt.x) - static_cast<double>((this->x + 10) * gScale)) / static_cast<double>((cx - 20) * gScale);
		this->Value = GetMaxValue(GetMinValue(p * 100, 0), 100);
		func();
		Refresh(hWnd);
		return 0;
	}
	virtual int AddEvent(const vinaPoint& pt, vinaEvent eventtype)
	{

		if (eventtype == vinaEvent::mouseUp)this->OnMouseUp();
		if (eventtype == vinaEvent::mouseDown)this->OnMouseDown();
		if (eventtype == vinaEvent::mouseOver) {
			if (this->OnEdit == false)return 0;
			POINT pt;
			GetCursorPos(&pt);
			ScreenToClient(hWnd, &pt);
			double p = (static_cast<double>(pt.x) - static_cast<double>((this->x + 10) * gScale)) / static_cast<double>((cx - 20) * gScale);
			this->Value = GetMaxValue(GetMinValue(p * 100, 0), 100);
			func();
			Refresh(hWnd);
		}

		return 0;
	}
	virtual void CreateInheritedCtl(HWND hWnd, HRT hdc, std::shared_ptr<VinaSlider> vuic)
	{
		this->hWnd = hWnd;
		CreateCtl(hWnd, hdc);
	}
	virtual VertexUIPos GetCurrentRect() {
		VertexUIPos _{ x,y,cx,cy };
		return _;
	}
	void SetInternalEvent(std::wstring ev)
	{
		this->_event = ev;
	}
	int GetValue()
	{
		return Value;
	}
	void SetValue(int val)
	{
		this->Value = val;
	}
	std::wstring txt;
	std::wstring c;
	std::wstring _event = L"";
	unsigned long Clr;

	int id = -1;
protected:
	bool OnEdit = false;
	int Value = 0;
	HWND hWnd;
	int ap = 0;
	int flag = 0;
	float txtsz = 15;
	unsigned long txtClr;
	std::function<void()>func;
	std::wstring text;
};
class VinaProgress : public VertexUIControl {
public:
	void Set(int x, int y, int cx, int cy, int Value = -1, unsigned long clr = VERTEXUICOLOR_DARKEN, const wchar_t* placeholder = L"")
	{
		this->txt = placeholder;
		this->x = x - 10;
		this->y = y - 10;
		this->cx = cx + 20;
		this->cy = cy + 20;
		if (Value != -1)this->Value = Value;
		this->Clr = clr;
	}

	virtual void CreateCtl(HWND hWnd, HRT hdc)
	{
		RECT rc;
		GetClientRect(hWnd, &rc);

		RECT crc;

		double progress = ((double)(cx - 20) * Value) / 100.0;
		D2DDrawRoundRect(hdc, x + 10, y + 10, cx - 20, cy - 20, VuiFadeColor(Clr, 60), 8, 0.2f, 1.2f, VuiFadeColor(Clr, 100), 0.6f);
		D2DDrawRoundRect(hdc, x + 10, y + 10, progress, cy - 20, VuiFadeColor(Clr, 10), 8);
		D2DDrawText2(hdc, this->txt.c_str(), x + 20, y + cy / 2 - 9, cx - 20, cy - 20, 12, VuiFadeColor(Clr, 140), L"Segoe UI", 0.75f);
	}

	virtual int OnMouseUp()
	{

		Refresh(hWnd);
		return 0;
	}
	virtual int OnMouseDown()
	{

		Refresh(hWnd);
		return 0;
	}
	virtual int AddEvent(const vinaPoint& pt, vinaEvent eventtype)
	{
		if (eventtype == vinaEvent::mouseUp)this->OnMouseUp();
		if (eventtype == vinaEvent::mouseDown)this->OnMouseDown();
		if (eventtype == vinaEvent::mouseOver) {
			if (this->OnEdit == false)return 0;
			Refresh(hWnd);
		}

		return 0;
	}
	virtual void CreateInheritedCtl(HWND hWnd, HRT hdc, std::shared_ptr<VinaProgress> vuic)
	{
		this->hWnd = hWnd;
		CreateCtl(hWnd, hdc);
	}
	virtual VertexUIPos GetCurrentRect() {
		VertexUIPos _{ x,y,cx,cy };
		return _;
	}
	void SetInternalEvent(std::wstring ev)
	{
		this->_event = ev;
	}
	int GetValue()
	{
		return Value;
	}
	void SetValue(int val)
	{
		this->Value = val;
	}
	std::wstring txt;
	std::wstring c;
	std::wstring _event = L"";
	unsigned long Clr;

	int id = -1;
protected:
	bool OnEdit = false;
	int Value = 0;
	HWND hWnd;
	int ap = 0;
	int flag = 0;
	float txtsz = 15;
	unsigned long txtClr;
	std::function<void()>func;
	std::wstring text;
};
class VinaFileSelector : public VertexUIControl {
public:
	struct FileInfo {
		std::wstring name;
		std::wstring path;
		bool isDirectory;
		std::wstring iconPath;
		int x, y, cx, cy;
		bool useIconText;
		int ap = 0;
		int flag = 0;
		bool isSpecialFolder = false; // 新增：标识是否为特殊文件夹
	};

	enum class ViewMode {
		DriveSelection,
		FileBrowser
	};

	bool evercreated = false;
	ViewMode currentMode = ViewMode::DriveSelection;

	void Set(int x, int y, int cx, int cy, unsigned long bgColor = VERTEXUICOLOR_MIDNIGHT) {
		this->x = x;
		this->y = y;
		this->cx = cx;
		this->cy = cy;
		this->bgColor = bgColor;
		this->itemHeight = 30;

		if (evercreated == false) {
			this->hoveredIndex = -1;
			this->selectedIndex = -1;
			this->scrollOffset = 0;
			currentMode = ViewMode::DriveSelection;
			currentPath = L"";
			RefreshFileList();
		}
		evercreated = true;
	}

	virtual void CreateCtl(HWND hWnd, HRT hdc) {
		if (!Isvalid) return;
		scrollOffset += this->GetParent()->GetInstantScrollDepth() / 6;
		scrollOffset = GetMinValue(scrollOffset, 0);

		D2DDrawRoundRect(hdc, x, y, cx, cy, bgColor, 8, 1, 1.0f, VERTEXUICOLOR_MIDNIGHTPLUS);

		DrawPathBar(hWnd, hdc);

		DrawFileList(hWnd, hdc);

		DrawScrollBar(hWnd, hdc);
	}

	virtual int AddEvent(const vinaPoint& pt, vinaEvent eventtype) override {
		if (!Isvalid) return 0;

		if (eventtype == vinaEvent::mouseDown) {
			HandleMouseDown(pt);
			Refresh(hWnd);
		}
		if (eventtype == vinaEvent::mouseUp) {
			HandleMouseUp(pt);
			Refresh(hWnd);
		}
		if (eventtype == vinaEvent::mouseOver) {
			this->IsHoverd = true;
			HandleMouseMove(pt);
			Refresh(hWnd);
		}
		else {
			this->IsHoverd = false;
			hoveredIndex = -1;
		}

		return 0;
	}

	virtual void CreateInheritedCtl(HWND hWnd, HRT hdc, std::shared_ptr<VinaFileSelector> vuic) {
		this->hWnd = hWnd;
		CreateCtl(hWnd, hdc);
	}

	virtual VertexUIPos GetCurrentRect() override {
		VertexUIPos pos{ x, y, cx, cy };
		return pos;
	}

	void SetFileOpenCallback(std::function<void(const std::wstring&)> callback) {
		fileSelectedCallback = callback;
	}

	void SetPathDebugCallback(std::function<void(const std::wstring&)> callback) {
		pathChangedCallback = callback;
	}

private:
	void DrawPathBar(HWND hWnd, HRT hdc) {
		D2DDrawRoundRect(hdc, x + 5, y + 5, cx - 10, 30, VuiFadeColor(bgColor, 20), 6, 1, 1.5f, VERTEXUICOLOR_MIDNIGHTPLUS);

		std::wstring pathText;
		if (currentMode == ViewMode::DriveSelection) {
			pathText = L"计算机";
		}
		else {
			pathText = currentPath.empty() ? L"计算机" : currentPath;
		}

		D2DDrawText2(hdc, pathText.c_str(), x + 15, y + 12, cx - 20, 20, 14, VERTEXUICOLOR_WHITE, L"Segoe UI", 1, false);
	}

	void DrawFileList(HWND hWnd, HRT hdc) {
		int maxScrollOffset = std::max(0, (int)fileList.size() - (cy - 50) / itemHeight);
		scrollOffset = std::max(0, std::min(scrollOffset, maxScrollOffset));

		int startY = y + 40;
		int visibleItems = (cy - 50) / itemHeight;
		int startIndex = scrollOffset;
		int endIndex = std::min(startIndex + visibleItems + 1, (int)fileList.size());

		for (int i = startIndex; i < endIndex; i++) {
			int itemY = startY + (i - startIndex) * itemHeight;

			fileList[i].x = x + 5;
			fileList[i].y = itemY;
			fileList[i].cx = cx - 30;
			fileList[i].cy = itemHeight - 2;

			if (itemY + itemHeight < y + 40 || itemY > y + cy - 10) continue;

			HandleItemAnimationInCreate(i);

			DrawItemBackground(hdc, i, x + 5, itemY, cx - 30, itemHeight - 2);

			if (!fileList[i].useIconText) {
				D2DDisplayIcon(hdc, fileList[i].path.c_str(), x + 10, itemY + 5, 20);
			}

			if (fileList[i].useIconText) {
				unsigned long txtClr = VERTEXUICOLOR_WHITE;

				D2DDrawText(hdc, L"\uf060", x + 15, itemY + 7, cx - 50, itemHeight - 4, 15, txtClr, L"Font Awesome 6 Free Solid", 1);

				std::wstring displayName = GetParentFolderName(fileList[i].name);
				D2DDrawText2(hdc, displayName.c_str(), x + 35, itemY + 8, cx - 50, itemHeight - 4,
					13, VERTEXUICOLOR_WHITE, L"Segoe UI", 1, false);
			}
			else {
				D2DDrawText2(hdc, fileList[i].name.c_str(), x + 35, itemY + 8, cx - 50, itemHeight - 4,
					13, VERTEXUICOLOR_WHITE, L"Segoe UI", 1, false);
			}
		}
	}

	void HandleItemAnimationInCreate(int index) {
		FileInfo& file = fileList[index];

		bool isHovered = (index == hoveredIndex);

		if (isHovered) {
			if (file.flag == 0) {
				file.flag = 1;
			}
			if (file.ap < 10) {
				file.ap++;
			}
			if (file.ap >= 10) {
				file.flag = 0;
			}
		}
		else {
			if (file.flag == 0) {
				file.flag = 1;
			}
			if (file.ap > 0) {
				file.ap--;
			}
			if (file.ap == 0) {
				file.flag = 0;
			}
		}
	}

	void DrawItemBackground(HRT hdc, int index, int x, int y, int cx, int cy) {
		FileInfo& file = fileList[index];

		float num = 0;
		if (file.ap > 0) {
			num = CalcEaseOutCurve(file.ap, 0, 0.5, 10);
		}

		unsigned long bgColor;
		unsigned long borderColor = VERTEXUICOLOR_MIDNIGHTPLUS;

		if (index == selectedIndex) {
			bgColor = VERTEXUICOLOR_SEA;

			if (num > 0) {
				int nR = GetMaxValue(GetRValue(bgColor) + (int)(num * 20), 255);
				int nG = GetMaxValue(GetGValue(bgColor) + (int)(num * 20), 255);
				int nB = GetMaxValue(GetBValue(bgColor) + (int)(num * 20), 255);
				bgColor = RGB(nR, nG, nB);
			}
			D2DDrawRoundRect(hdc, x + num, y + num, cx - num * 2, cy - num * 2, bgColor, 4, 1, 1.0f, borderColor);
		}
		else if (file.ap > 0 || index == hoveredIndex) {
			int alpha = (int)(30 * (file.ap / 10.0f));
			bgColor = VuiFadeColor(VERTEXUICOLOR_MIDNIGHT, alpha);

			int nR = GetMaxValue(GetRValue(bgColor) + (int)(num * 15), 255);
			int nG = GetMaxValue(GetGValue(bgColor) + (int)(num * 15), 255);
			int nB = GetMaxValue(GetBValue(bgColor) + (int)(num * 15), 255);
			bgColor = RGB(nR, nG, nB);

			D2DDrawRoundRect(hdc, x - num, y - num, cx + num * 2, cy + num * 2, bgColor, 4, 1, 1.0f + num * 0.3f, borderColor);
		}
	}

	void DrawScrollBar(HWND hWnd, HRT hdc) {
		if (fileList.size() * itemHeight <= cy - 50) return;

		int maxScrollOffset = std::max(0, (int)fileList.size() - (cy - 50) / itemHeight);
		scrollOffset = std::max(0, std::min(scrollOffset, maxScrollOffset));

		int visibleHeight = cy - 50;
		int totalHeight = std::max(1, (int)fileList.size() * itemHeight);
		int scrollBarHeight = std::max(20, (visibleHeight * visibleHeight) / totalHeight);

		float scrollRatio = (fileList.size() > (cy - 50) / itemHeight) ?
			static_cast<float>(scrollOffset) / static_cast<float>(maxScrollOffset) : 0.0f;
		int scrollBarY = y + 40 + static_cast<int>(scrollRatio * (visibleHeight - scrollBarHeight));

		scrollBarY = std::max(y + 40, std::min(y + cy - 15 - scrollBarHeight, scrollBarY));

		D2DDrawRoundRect(hdc, x + cx - 15, y + 40, 10, cy - 50,
			VuiFadeColor(bgColor, 10), 5, 1, 1.0f, VERTEXUICOLOR_MIDNIGHTPLUS);

		D2DDrawRoundRect(hdc, x + cx - 15, scrollBarY, 10, scrollBarHeight,
			VuiFadeColor(VERTEXUICOLOR_MIDNIGHTPLUS, 20), 5, 1, 1.0f, VERTEXUICOLOR_MIDNIGHTPLUS);
	}

	void HandleMouseDown(const vinaPoint& pt) {
		this->IsPushed = true;

		int visibleItems = (cy - 50) / itemHeight;
		int startIndex = scrollOffset;
		int endIndex = std::min(startIndex + visibleItems + 1, (int)fileList.size());

		for (int i = startIndex; i < endIndex; i++) {
			if (GetPtInfo(pt, fileList[i].x, fileList[i].y, fileList[i].cx, fileList[i].cy)) {
				selectedIndex = i;
				break;
			}
		}
	}

	void HandleMouseUp(const vinaPoint& pt) {
		this->IsPushed = false;

		int visibleItems = (cy - 50) / itemHeight;
		int startIndex = scrollOffset;
		int endIndex = std::min(startIndex + visibleItems + 1, (int)fileList.size());

		for (int i = startIndex; i < endIndex; i++) {
			if (GetPtInfo(pt, fileList[i].x, fileList[i].y, fileList[i].cx, fileList[i].cy)) {
				selectedIndex = i;
				break;
			}
		}

		if (selectedIndex >= 0 && selectedIndex < (int)fileList.size()) {
			FileInfo& file = fileList[selectedIndex];

			if (currentMode == ViewMode::DriveSelection) {
				if (file.name == L"vui.QWQ") {
					// 特殊处理
				}
				else {
					currentMode = ViewMode::FileBrowser;
					currentPath = file.path;
					RefreshFileList();
				}
			}
			else {
				if (file.isDirectory) {
					if (file.name == L"计算机") {
						currentMode = ViewMode::DriveSelection;
						currentPath = L"";
						RefreshFileList();
					}
					else if (file.name == L"..") {
						if (IsRootPath(currentPath)) {
							currentMode = ViewMode::DriveSelection;
							currentPath = L"";
							RefreshFileList();
						}
						else {
							currentPath = file.path;
							RefreshFileList();
						}
					}
					else {
						// 对于特殊文件夹，直接使用其路径
						currentPath = file.path;
						RefreshFileList();
					}
					selectedIndex = -1;
					scrollOffset = 0;
					hoveredIndex = -1;

					if (pathChangedCallback && currentMode == ViewMode::FileBrowser) {
						pathChangedCallback(currentPath);
					}
				}
				else {
					// 选择文件
					if (fileSelectedCallback) {
						fileSelectedCallback(file.path);
					}
				}
			}
		}
	}

	void HandleMouseMove(const vinaPoint& pt) {
		int visibleItems = (cy - 50) / itemHeight;
		int startIndex = scrollOffset;
		int endIndex = std::min(startIndex + visibleItems + 1, (int)fileList.size());

		hoveredIndex = -1;
		for (int i = startIndex; i < endIndex; i++) {
			if (GetPtInfo(pt, fileList[i].x, fileList[i].y, fileList[i].cx, fileList[i].cy)) {
				hoveredIndex = i;
				break;
			}
		}
	}

	void RefreshFileList() {
		ClearVector(fileList);

		if (currentMode == ViewMode::DriveSelection) {
			LoadDriveList();
		}
		else {
			LoadRealFileList();
		}

		selectedIndex = -1;
		scrollOffset = 0;
		hoveredIndex = -1;
	}

	void LoadDriveList() {
		ClearVector(fileList);

		// 加载逻辑驱动器
		wchar_t drives[1024];
		DWORD drivesSize = GetLogicalDriveStringsW(1024, drives);

		if (drivesSize > 0 && drivesSize < 1024) {
			wchar_t* drive = drives;
			while (*drive) {
				UINT driveType = GetDriveTypeW(drive);

				if (driveType == DRIVE_FIXED || driveType == DRIVE_REMOVABLE || driveType == DRIVE_CDROM) {
					FileInfo driveInfo;
					driveInfo.name = drive;
					driveInfo.path = drive;
					driveInfo.isDirectory = true;
					driveInfo.iconPath = L"";
					driveInfo.useIconText = false;
					driveInfo.ap = 0;
					driveInfo.flag = 0;
					driveInfo.isSpecialFolder = false; // 普通驱动器
					fileList.push_back(driveInfo);
				}

				drive += wcslen(drive) + 1;
			}
		}

		// 添加快速访问项：桌面 和 文档
		{
			// 获取桌面路径
			PWSTR desktopPath = nullptr;
			if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Desktop, 0, NULL, &desktopPath))) {
				FileInfo desktopInfo;
				desktopInfo.name = L"桌面";
				desktopInfo.path = desktopPath;
				// 确保路径以反斜杠结尾
				if (!desktopInfo.path.empty() && desktopInfo.path.back() != L'\\') {
					desktopInfo.path += L"\\";
				}
				desktopInfo.isDirectory = true;
				desktopInfo.iconPath = L"";
				desktopInfo.useIconText = false;
				desktopInfo.ap = 0;
				desktopInfo.flag = 0;
				desktopInfo.isSpecialFolder = true; // 标记为特殊文件夹
				fileList.push_back(desktopInfo);
				CoTaskMemFree(desktopPath);
			}

			// 获取文档路径
			PWSTR documentsPath = nullptr;
			if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Documents, 0, NULL, &documentsPath))) {
				FileInfo documentsInfo;
				documentsInfo.name = L"文档";
				documentsInfo.path = documentsPath;
				// 确保路径以反斜杠结尾
				if (!documentsInfo.path.empty() && documentsInfo.path.back() != L'\\') {
					documentsInfo.path += L"\\";
				}
				documentsInfo.isDirectory = true;
				documentsInfo.iconPath = L"";
				documentsInfo.useIconText = false;
				documentsInfo.ap = 0;
				documentsInfo.flag = 0;
				documentsInfo.isSpecialFolder = true; // 标记为特殊文件夹
				fileList.push_back(documentsInfo);
				CoTaskMemFree(documentsPath);
			}
		}

		if (fileList.empty()) {
			FileInfo noDriveInfo;
			noDriveInfo.name = L"未找到可用驱动器";
			noDriveInfo.path = L"";
			noDriveInfo.isDirectory = false;
			noDriveInfo.iconPath = L"";
			noDriveInfo.useIconText = false;
			noDriveInfo.ap = 0;
			noDriveInfo.flag = 0;
			noDriveInfo.isSpecialFolder = false;
			fileList.push_back(noDriveInfo);
		}
	}

	void LoadRealFileList() {
		ClearVector(fileList);

		// 添加返回上级目录的选项（如果不是根路径）
		if (!currentPath.empty() && !IsRootPath(currentPath)) {
			FileInfo parentDir;
			parentDir.name = L"..";
			parentDir.path = GetParentPath(currentPath);
			parentDir.isDirectory = true;
			parentDir.iconPath = L"";
			parentDir.useIconText = true;
			parentDir.ap = 0;
			parentDir.flag = 0;
			parentDir.isSpecialFolder = false;
			fileList.push_back(parentDir);
		}

		// 如果是根路径，添加返回计算机的选项
		if (!currentPath.empty() && IsRootPath(currentPath)) {
			FileInfo driveSelect;
			driveSelect.name = L"计算机";
			driveSelect.path = L"";
			driveSelect.isDirectory = true;
			driveSelect.iconPath = L"";
			driveSelect.useIconText = true;
			driveSelect.ap = 0;
			driveSelect.flag = 0;
			driveSelect.isSpecialFolder = false;
			fileList.push_back(driveSelect);
		}

		// 加载当前路径下的文件和文件夹
		if (!currentPath.empty()) {
			WIN32_FIND_DATAW findData;
			HANDLE hFind;
			std::wstring searchPath = currentPath + L"*"; // 确保路径格式正确

			hFind = FindFirstFileW(searchPath.c_str(), &findData);
			if (hFind != INVALID_HANDLE_VALUE) {
				do {
					if (wcscmp(findData.cFileName, L".") == 0) continue;
					if (wcscmp(findData.cFileName, L"..") == 0 && !IsRootPath(currentPath)) continue;

					FileInfo fileInfo;
					fileInfo.name = findData.cFileName;
					fileInfo.path = currentPath + findData.cFileName;
					fileInfo.iconPath = L"";
					fileInfo.useIconText = false;
					fileInfo.ap = 0;
					fileInfo.flag = 0;
					fileInfo.isSpecialFolder = false;

					if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
						fileInfo.isDirectory = true;
						fileInfo.path += L"\\";
					}
					else {
						fileInfo.isDirectory = false;
					}

					fileList.push_back(fileInfo);
				} while (FindNextFileW(hFind, &findData));

				FindClose(hFind);
			}
		}

		if (pathChangedCallback) {
			pathChangedCallback(currentPath);
		}
	}

	std::wstring GetParentFolderName(const std::wstring& currentName) {
		if (currentName == L"..") {
			std::wstring parentPath = GetParentPath(currentPath);
			if (!parentPath.empty()) {
				std::wstring cleanPath = parentPath;
				if (cleanPath.back() == L'\\' && cleanPath.length() > 1) {
					cleanPath.pop_back();
				}
				size_t pos = cleanPath.find_last_of(L'\\');
				if (pos != std::wstring::npos) {
					return cleanPath.substr(pos + 1);
				}
				else {
					return parentPath;
				}
			}
			return L"上级目录";
		}
		return currentName;
	}

	std::wstring GetFileIconPath(const FileInfo& file) {
		if (file.path.size() > 255)return L"qwq";
		if (file.name == std::wstring(L"计算机"))return L"qwq";
		else return file.path;
	}

	bool IsRootPath(const std::wstring& path) {
		return (path.length() == 3 && path[1] == L':' && path[2] == L'\\');
	}

	std::wstring GetParentPath(const std::wstring& path) {
		if (path.length() <= 3) return path;

		std::wstring tempPath = path;
		if (tempPath.back() == L'\\' && tempPath.length() > 1) {
			tempPath.pop_back();
		}

		size_t pos = tempPath.find_last_of(L'\\');
		if (pos != std::wstring::npos) {
			return tempPath.substr(0, pos + 1);
		}
		return L"C:\\";
	}

protected:
	std::wstring currentPath;
	std::vector<FileInfo> fileList;
	int itemHeight;
	int scrollOffset;
	int selectedIndex;
	int hoveredIndex;
	unsigned long bgColor;

	std::function<void(const std::wstring&)> fileSelectedCallback;
	std::function<void(const std::wstring&)> pathChangedCallback;

	bool Isvalid = true;
	HWND hWnd;
	bool IsHoverd = false;
	bool IsPushed = false;
};