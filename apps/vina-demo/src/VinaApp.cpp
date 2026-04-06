#include "VinaApp.h"
#include <chrono>

struct WaterfallCard {
	float y;
	std::wstring text;
	unsigned long color;
	float animY = 20.0f;
	float alpha = 0.0f;
	bool animated = false;
};

class MainAppContext {
public:
	int currentTabIndex = 0;
	float scrollVal = 0.0f;
	float scrollTarget = 0.0f;
	std::vector<std::shared_ptr<VinaSideTab>> tabs;
	std::shared_ptr<VinaButton> btn = std::make_shared<VinaButton>();
	std::shared_ptr<VinaSlider> sli = std::make_shared<VinaSlider>();
	std::shared_ptr<VinaSwitch> sw = std::make_shared<VinaSwitch>();
	std::shared_ptr<VinaFileSelector> fi = std::make_shared<VinaFileSelector>();
	std::shared_ptr<VinaMultiTextBox> mt = std::make_shared<VinaMultiTextBox>();
	std::shared_ptr<VinaEdit> edt = std::make_shared<VinaEdit>();
	std::shared_ptr<VinaCaptionBar> capt = std::make_shared<VinaCaptionBar>();

	std::wstring lastText;
	std::list<CharAnim> animatingChars;
	ID2D1Bitmap* pAppLogo = nullptr;

	std::vector<WaterfallCard> waterfallData;

	float maxScrollLimit = 0.0f; 
	bool isGenerating = false; 
	int activeAnimationCount = 0;
	double lastLoadTimeSec = 0.0;

	void InitTabs() {
		if (!tabs.empty()) return;
		auto tab1 = std::make_shared<VinaSideTab>();
		tab1->Set(0, 55, 120, L"DemoUI", L"test-home", 20, VuiFadeColor(VERTEXUICOLOR_WHITE,40));
		tab1->Activate(true);

		auto tab2 = std::make_shared<VinaSideTab>();
		tab2->Set(0, 55, 120, L"Waterfall", L"test-test1", 20, VuiFadeColor(VERTEXUICOLOR_WHITE, 20));

		auto tab3 = std::make_shared<VinaSideTab>();
		tab3->Set(0, 55, 120, L"About", L"test-info", 20, VuiFadeColor(VERTEXUICOLOR_WHITE, 20));


		tabs.push_back(tab1);
		tabs.push_back(tab2);
		tabs.push_back(tab3);
	}

	void InitWaterfall() {
		if (!waterfallData.empty()) return;
		GenerateCards(6);
	}

	void GenerateCards(int count) {
		unsigned long macaronColors[] = { VERTEXUICOLOR_SEA, VERTEXUICOLOR_BLOOMLAVENDER, VERTEXUICOLOR_DAWN, VERTEXUICOLOR_FOREST, VERTEXUICOLOR_SEA };
		for (int i = 0; i < count; i++) {
			WaterfallCard card;
			card.text = L"VinaUI Card " + std::to_wstring(waterfallData.size());
			card.color = macaronColors[rand() % 5];
			waterfallData.push_back(card);
		}
	}

	void ResetWaterfallAnimationState() {
		activeAnimationCount = 0;
		scrollTarget = scrollVal;
		for (auto& card : waterfallData) {
			if (card.animated && (card.alpha < 1.0f || card.animY > 0.0f)) {
				card.alpha = 1.0f;
				card.animY = 0.0f;
			}
		}
	}
};


VinaWindow* MainWindow = new VinaWindow;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int        nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);

	InitGlobalD2D();

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_VINAAPP));

	VuiColorSystemInit();
	gScale = GetScreenScale();
	//LoadVinaCom();

	// Optional: set a project-wide default UI font via API.
	// MainWindow->SetDefaultFontFamily(L"Microsoft YaHei UI");
	// MainWindow->SetFontAlias(L"ui-body", L"Microsoft YaHei UI");
	// MainWindow->SetDefaultFontFamily(L"ui-body");
	// MainWindow->AddFontFallback(L"Segoe UI Emoji");

	auto fontData = AppResourceManager::LoadRawResource(hInstance, IDF_FONTAWESOME, L"BINARY");

	if (!fontData.empty()) {
		MainWindow->RegisterFontFromMemory(fontData.data(), (DWORD)fontData.size());
	}

	namespace fs = std::filesystem;
	fs::path fontPath =  L"Font-AwesomeFree.ttf";

	FreeAnyResource(IDF_FONTAWESOME, L"BINARY", fontPath.c_str());
	MainWindow->RegisterFontFromFile(fontPath.c_str());

	auto ctx = std::make_shared<MainAppContext>();

	MainWindow->Set(100, 100, 720 * gScale, 480 * gScale, L"Vina.Class.App.Main.Test", L"Vilinko VinaUI");

	MainWindow->CreatePanel([ctx](HWND hWnd, ID2D1HwndRenderTarget* hrt)->void {
		auto nowSec = []() -> double {
			using namespace std::chrono;
			return duration<double>(steady_clock::now().time_since_epoch()).count();
		};

		RECT rc;
		GetClientRect(hWnd, &rc);
		const float viewWidth = rc.right / gScale;
		const float viewHeight = rc.bottom / gScale;
		D2DDrawSolidRect(hrt, 0, 0, rc.right, rc.bottom, VERTEXUICOLOR_DARKNIGHT);
		MainWindow->GetPanel()->Set(hWnd, hrt);

		/*
		CreatePanel 会在窗口刷新时被调用。

		控件需要使用静态标识，或者在 CreatePanel 外部初始化。

		使用 std::vector 等容器储存控件也是较好的方法。
		*/


		if (ctx->currentTabIndex == 0) {
			const float marginX = 36.0f;
			const float contentTop = 112.0f;
			const float colGap = 28.0f;
			const float leftW = std::max(180.0f, std::min(260.0f, viewWidth * 0.32f));
			const float rightX = marginX + leftW + colGap;
			const float rightW = std::max(220.0f, viewWidth - rightX - marginX);

			ctx->btn->Set((int)marginX, (int)contentTop, (int)leftW, 44, L"Button", [] {return 0; });
			MainWindow->GetPanel()->Add(ctx->btn);

			ctx->sli->Set((int)marginX, (int)(contentTop + 62), (int)leftW, 34, -1, VERTEXUICOLOR_DARKEN, L"Slider", [] {});
			MainWindow->GetPanel()->Add(ctx->sli);

			ctx->sw->Set((int)marginX, (int)(contentTop + 112), 72, 34, { VERTEXUICOLOR_DARKEN }, [] {});
			MainWindow->GetPanel()->Add(ctx->sw);

			if (ctx->sw->GetValue())
			{
				const float fiH = std::max(130.0f, viewHeight - (contentTop + 170.0f) - 36.0f);
				ctx->fi->Set((int)marginX, (int)(contentTop + 162), (int)leftW, (int)fiH);
				ctx->fi->SetFileOpenCallback([](std::wstring path)->void {
					MessageBox(0, path.c_str(), L"Current", 0);
					});
				ctx->fi->SetParent(MainWindow->GetPanel());
				MainWindow->GetPanel()->Add(ctx->fi);
			}

			const float mtH = std::max(130.0f, viewHeight * 0.30f);
			ctx->mt->Set((int)rightX, (int)contentTop, (int)rightW, (int)mtH, L"This is a test string.\nAnd this is a multi line text area.\ne.g:\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10");
			ctx->mt->SetParent(MainWindow->GetPanel());
			MainWindow->GetPanel()->Add(ctx->mt);

			if (ctx->edt->cx == 0)/*这里为了演示方便，做简单的初始化。实际使用建议将Set移动到外层。*/
			{
				ctx->edt->Set((int)rightX, (int)(contentTop + mtH + 18), (int)rightW, 34, L"This is a Edit...");
			}
			ctx->edt->Set2((int)rightX, (int)(contentTop + mtH + 18), (int)rightW, 36, VERTEXUICOLOR_MIDNIGHT, VERTEXUICOLOR_WHITE);
			MainWindow->GetPanel()->Add(ctx->edt);

			/*
			此处演示动画效果，以及动画播放时的内存管理。

			动画效果可以直接在 CreatePanel（也就是 OnPaint ）时操作，也可以在控件内部操作。

			此处为了演示方便，直接在 CreatePanel 内部操作。
			*/

			std::wstring currentText = ctx->edt->GetText();

			if (currentText != ctx->lastText) {
				if (currentText.length() > ctx->lastText.length()) {

					for (size_t i = ctx->lastText.length(); i < currentText.length(); ++i) {

						float lockedX = VuiMeasureStringWidth(currentText.substr(0, i), 18);

						ctx->animatingChars.push_back({ currentText[i], 0.0f, lockedX, 18.0f, false });
						CharAnim& ref = ctx->animatingChars.back();

						ref.alphaAnimId = MainWindow->AnimateVariableWithBezier(hWnd, ref.alpha, 0.0f, 1.0f, 0.4);
						ref.yOffsetAnimId = MainWindow->AnimateVariableWithBezier(hWnd, ref.yOffset, 18.0f, 0.0f, 0.4);
					}
				}
				else if (currentText.length() < ctx->lastText.length()) {

					size_t diff = ctx->lastText.length() - currentText.length();
					for (size_t i = 0; i < diff; ++i) {

						auto it = std::find_if(ctx->animatingChars.rbegin(), ctx->animatingChars.rend(),
							[](const CharAnim& c) { return !c.isRemoving; });

						if (it != ctx->animatingChars.rend()) {
							it->isRemoving = true;
							CharAnim& ref = *it;

							ref.alphaAnimId = MainWindow->AnimateVariableWithBezier(hWnd, ref.alpha, ref.alpha, 0.0f, 0.3);
							ref.yOffsetAnimId = MainWindow->AnimateVariableWithBezier(hWnd, ref.yOffset, ref.yOffset, 10.0f, 0.3);
						}
					}
				}
				ctx->lastText = currentText;
			}

			//清理
			ctx->animatingChars.remove_if([&](const CharAnim& c) {
				if (c.isRemoving && c.alpha <= 0.01f) {
		
					if (c.alphaAnimId != -1) {
						MainWindow->StopAnimation(c.alphaAnimId);
					}
					if (c.yOffsetAnimId != -1) {
						MainWindow->StopAnimation(c.yOffsetAnimId);
					}
					return true; 
				}
				return false;
				});

			float startX_txt = rightX;
			float startY_txt = contentTop + mtH + 70.0f;

			for (auto& item : ctx->animatingChars) {
				D2DDrawText2(hrt, std::wstring(1, item.ch).c_str(),
					startX_txt + item.xOffset, startY_txt + item.yOffset,
					20, 20, 18,
					VERTEXUICOLOR_WHITE, L"Segoe UI", item.alpha);
			}
		}
		if (ctx->currentTabIndex == 1)
		{
			float delta = MainWindow->GetPanel()->GetInstantScrollDepth();
			ctx->scrollTarget -= delta;
			if (ctx->scrollTarget > 0.0f) ctx->scrollTarget = 0.0f;

			if (ctx->waterfallData.empty()) {
				ctx->GenerateCards(16);
			}

			float cardW = (viewWidth - 60.0f) / 2.0f;
			float cardH = 150.0f;
			float spacing = 20.0f;
			float startY = 120.0f;

			int rowCount = (int)ceil(ctx->waterfallData.size() / 2.0f);
			float totalContentHeight = startY + rowCount * (cardH + spacing);

			float minScroll = viewHeight - totalContentHeight - 50.0f;
			if (minScroll > 0) minScroll = 0;
			if (ctx->scrollTarget < minScroll) ctx->scrollTarget = minScroll;
			ctx->scrollVal += (ctx->scrollTarget - ctx->scrollVal) * 0.18f;
			if (fabs(ctx->scrollTarget - ctx->scrollVal) < 0.2f) ctx->scrollVal = ctx->scrollTarget;

			// 触发加载
			double t = nowSec();
			if (totalContentHeight + ctx->scrollVal < viewHeight + 100.0f
				&& ctx->waterfallData.size() < 200
				&& (t - ctx->lastLoadTimeSec) > 0.22) {
				ctx->GenerateCards(6);
				ctx->lastLoadTimeSec = t;
			}

			
			for (size_t i = 0; i < ctx->waterfallData.size(); i++) {
				auto& card = ctx->waterfallData[i];
				int row = (int)(i / 2);
				int col = (int)(i % 2);

				float drawX = 20.0f + col * (cardW + spacing);
				float drawY = startY + row * (cardH + spacing) + ctx->scrollVal;

				// 剪裁
				if (drawY + cardH < 0) continue;
				if (drawY > viewHeight) break;

				
				if (!card.animated) {
					// 渲染排队
					if (ctx->activeAnimationCount < 4) {
						card.animated = true;
						ctx->activeAnimationCount++;
						const size_t cardIndex = i;

						MainWindow->AnimateVariableWithBezier(hWnd, card.alpha, 0.0f, 1.0f, 0.5);
						MainWindow->AnimateVariableWithBezier(hWnd, card.animY, 30.0f, 0.0f, 0.6,
							0.25, 0.1, 0.25, 1.0,
							[ctx, cardIndex] {
								if (cardIndex < ctx->waterfallData.size()) {
									ctx->waterfallData[cardIndex].animY = 0.0f;
									ctx->waterfallData[cardIndex].alpha = 1.0f;
								}
								if (ctx->activeAnimationCount > 0) ctx->activeAnimationCount--;
							}
						);
					}
				}

				if (card.animated) {
					float finalY = drawY + (card.animY < 0 ? 0 : card.animY);

					D2DDrawQuickShadow(hrt, drawX, finalY, cardW, cardH, 10, 0, 2, 10, 5, 0, 0.05f * card.alpha, VERTEXUICOLOR_WHITE);
					D2DDrawRoundRect(hrt, drawX, finalY, cardW, cardH, card.color, 12, card.alpha);
					if(card.text.c_str())D2DDrawText3(hrt, card.text.c_str(), drawX + 15, finalY+cardH - 45, cardW - 30, cardH - 30, 20,
						VERTEXUICOLOR_WHITEDRAW, L"Segoe UI", card.alpha * 0.9f);
				}
			}
		}
		if (ctx->currentTabIndex == 2)
		{
			float pageX = 60.0f;
			float pageY = 120.0f;
			float cardW = rc.right / gScale - 120.0f;
			float cardH = 300.0f;

			// 静态缓存位图，提升性能
			if (!ctx->pAppLogo) {
				ctx->pAppLogo = LoadIconToD2DBitmap(hrt, IDI_SMALL);
			}
			D2DDrawQuickShadow(hrt, pageX, pageY, rc.right / gScale - 120, 300, 15, 0, 2, 16, 8, 0, 0.02f, VERTEXUICOLOR_WHITE);
			D2DDrawRoundRect(hrt, pageX, pageY, rc.right / gScale - 120, 300, VERTEXUICOLOR_MIDNIGHT, 15, 0.5f, 1, 0, 0.1f);

			if (ctx->pAppLogo) {

				D2D1_RECT_F iconRect = D2D1::RectF(pageX + 40, pageY + 40, pageX + 104, pageY + 104);
				hrt->DrawBitmap(ctx->pAppLogo, iconRect);
			}

			D2DDrawText3(hrt, L"Vilinko VinaUI", pageX + 130, pageY + 45, 300, 40, 28,
				VERTEXUICOLOR_WHITE);

			D2DDrawText(hrt, L"Developer & Designer : CimiMoly", pageX + 130, pageY + 85, 300, 30, 14,
				VuiDarkenColor(VERTEXUICOLOR_WHITE, 100), L"Segoe UI", 0.8f);

			D2DDrawSolidRect(hrt, pageX + 40, pageY + 130, cardW - 80, 1,
				VuiDarkenColor(VERTEXUICOLOR_DARKNIGHT, 20), 0.5f);

			std::wstring description = L"Nice to meet U(●'◡'●)! VinaUI is here! Special thanks to @Haceau-Zoac for vina parser~\n";
			D2DDrawText(hrt, description.c_str(), pageX + 40, pageY + 150, cardW - 80, 100, 16,
				VERTEXUICOLOR_WHITE, L"Segoe UI", 0.9f);

			std::wstring copyright = L"Copyright © 2026 Vilinko. All rights reserved.";
			float cpWidth = VuiMeasureStringWidth(copyright, 14);
			D2DDrawText(hrt, copyright.c_str(), (rc.right / gScale - cpWidth) / 2.0f, pageY + cardH - 40,
				cpWidth + 20, 30, 14, VuiDarkenColor(VERTEXUICOLOR_WHITE, 150), L"Segoe UI", 0.7f);

			static std::shared_ptr<VinaButton> webBtn = std::make_shared<VinaButton>();
			webBtn->Set(pageX + 40, pageY + cardH - 90, 120, 35, L"Github", [] {
				ShellExecute(0, L"open", L"https://github.com/EnderMo/VinaUI", 0, 0, SW_SHOWNORMAL);
				});
			MainWindow->GetPanel()->Add(webBtn);

			static std::shared_ptr<VinaButton> spBtn = std::make_shared<VinaButton>();
			spBtn->Set(pageX + 180, pageY + cardH - 90, 120, 35, L"Sponsor", [] {
				ShellExecute(0, L"open", L"https://afdian.com/a/EnderMo", 0, 0, SW_SHOWNORMAL);
				});
			MainWindow->GetPanel()->Add(spBtn);
		}

		for (float i = 2; i < 90; i++)
		{
			D2DDrawSolidRect(hrt, 0, 1 * (i - 2), rc.right / gScale, 1.5F, VERTEXUICOLOR_DARKNIGHT, 1.0f - (i - 1.0f) / 80.0f);
		}
		D2DCreateQuickHeavyBlur(hrt, 0, 0, rc.right, 90 * gScale, 12);

		ctx->capt->Set(0, 0, rc.right / gScale - 160, 40, L"VinaUI App", VERTEXUICOLOR_DARKNIGHT, 18);
		MainWindow->GetPanel()->Add(ctx->capt);

		static std::shared_ptr<VinaFAIcon>close = std::make_shared<VinaFAIcon>();
		close->Set(rc.right / gScale - 32, 20, L"win-close", 15, VERTEXUICOLOR_WHITE, [] {DestroyWindow(MainWindow->GetHandle()); PostQuitMessage(0); });
		MainWindow->GetPanel()->Add(close);

		bool IsMaximized = IsZoomed(hWnd) != 0;

		if (!IsMaximized)
		{
			static std::shared_ptr<VinaFAIcon>max = std::make_shared<VinaFAIcon>();
			max->Set(rc.right / gScale - 32 - 32, 20, L"win-max", 15, VERTEXUICOLOR_WHITE, [hWnd] {
				SendMessage(hWnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0); });
			MainWindow->GetPanel()->Add(max);
		}
		else {
			static std::shared_ptr<VinaFAIcon>max = std::make_shared<VinaFAIcon>();
			max->Set(rc.right / gScale - 32 - 32, 20, L"win-restore", 15, VERTEXUICOLOR_WHITE, [hWnd] {
				SendMessage(hWnd, WM_SYSCOMMAND, SC_RESTORE, 0); });
			MainWindow->GetPanel()->Add(max);
		}
		static std::shared_ptr<VinaFAIcon>min = std::make_shared<VinaFAIcon>();
		min->Set(rc.right / gScale - 32 - 32 - 32, 20, L"win-min", 15, VERTEXUICOLOR_WHITE, [hWnd] {MainWindow->KillAnimation(); SendMessage(hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0); });
		MainWindow->GetPanel()->Add(min);

		static bool isLightTheme = false;
		static std::shared_ptr<VinaButton> themeBtn = std::make_shared<VinaButton>();
		themeBtn->Set(rc.right / gScale - 220, 10, 100, 28, isLightTheme ? L"Dark" : L"Light", [&]() {
			isLightTheme = !isLightTheme;
			if (isLightTheme) MainWindow->SetThemeLight();
			else MainWindow->SetThemeDark();
			themeBtn->SetInfo(themeBtn->GetCurrentRect(), isLightTheme ? L"Dark" : L"Light");
			});
		MainWindow->GetPanel()->Add(themeBtn);



		ctx->InitTabs();

		float totalWidth = ctx->tabs.size() * 130.0f;
		float startX = (rc.right / gScale - totalWidth) / 2.0f;

		for (size_t i = 0; i < ctx->tabs.size(); i++) {
			ctx->tabs[i]->Set(startX + i * 130, 55, 120, ctx->tabs[i]->GetText().c_str(), ctx->tabs[i]->txt.c_str(), 20, VuiFadeColor(VERTEXUICOLOR_WHITE, 20), [ctx, i] {
				ctx->currentTabIndex = (int)i;
				ctx->ResetWaterfallAnimationState();
				});
			ctx->tabs[i]->Activate(ctx->currentTabIndex == i);
			MainWindow->GetPanel()->Add(ctx->tabs[i]);
		}

		//LoadBitmapFromFile(hrt, m_ImageFactory, L"D:\\FLUENTEMOJI\\four_leaf_clover_3d.png", 20, 20, 100, 100);

		});

	MainWindow->SetOutFrame(VinaWindow::Client);
	MainWindow->OnCreateCmd = [] {
		CenterWindow(MainWindow->GetHandle());
		MainWindow->InitAnimation();
		MainWindow->StartAnimationSystem();
		};
	MainWindow->RunFull();

	return 0;
}
