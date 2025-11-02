#include "framework.h"
#include "VinaApp.h"
#include "VinaAppTool.h"
#include "VertexUI/VertexUI.ClickArea.h"
#include "VertexUI/VertexUI.Panel.h"
#include "VertexUI/VertexUI.min.h"
#include "MainUI.hpp"
#include "VinaWindow.hpp"

#include <Psapi.h>
#include <direct.h>
#include <io.h>
#include <regex>

#pragma warning(disable:4996)
#pragma warning(disable : 4244)

HANDLE hMyFont;
HGLOBAL hFntMem;
#define VERSION_STR L"v0.1.1"
#define MAX_LOADSTRING 100

VertexUIInit;

VinaWindow* MainWindow = new VinaWindow;
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);

    InitGlobalD2D();


    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_VINAAPP));


    VuiColorSystemInit();
    gScale = GetScreenScale();
    //LoadVinaCom();


    hMyFont = INVALID_HANDLE_VALUE; // Here, we will (hopefully) get our font handle
    HRSRC  hFntRes = FindResource(hInstance, MAKEINTRESOURCE(IDF_FONTAWESOME), L"BINARY");
    if (hFntRes) { // If we have found the resource ... 
        hFntMem = LoadResource(hInstance, hFntRes); // Load it
        if (hFntMem != nullptr) {
            void* FntData = LockResource(hFntMem); // Lock it into accessible memory
            DWORD nFonts = 0, len = SizeofResource(hInstance, hFntRes);
            hMyFont = AddFontMemResourceEx(FntData, len, nullptr, &nFonts); // Fake install font!
        }
    }
    std::wstring fntBase = std::wstring(LocalData) + std::wstring(L"\\Font-AwesomeFree.ttf");
    FreeAnyResource(IDF_FONTAWESOME, L"BINARY", fntBase.c_str());
    AddFontResource(fntBase.c_str());


    MainWindow->Set(100, 100, 720 * gScale, 480 * gScale, L"VinaClock.main", L"Vilinko VinaUI");
    MainWindow->CreatePanel([](HWND hWnd, ID2D1HwndRenderTarget* hrt)->void {


        RECT rc;
        GetClientRect(hWnd, &rc);
        D2DDrawSolidRect(hrt, 0, 0, rc.right, rc.bottom, VERTEXUICOLOR_MIDNIGHT);
        MainWindow->GetPanel()->Set(hWnd, hrt);

        static std::shared_ptr<VinaCaptionBar>capt = std::make_shared<VinaCaptionBar>();
        capt->Set(0, 0, rc.right / gScale - 160, 40, L"VinaUI App", VERTEXUICOLOR_MIDNIGHT, 18);
        MainWindow->GetPanel()->Add(capt);

        static std::shared_ptr<VinaFAIcon>close = std::make_shared<VinaFAIcon>();
        close->Set(rc.right / gScale - 32, 20, L"win-close", 15, VERTEXUICOLOR_WHITE, [] {DestroyWindow(MainWindow->GetHandle()); PostQuitMessage(0); });
        MainWindow->GetPanel()->Add(close);

        static bool IsMaximized = false;
        if (IsZoomed(hWnd) == true)IsMaximized = true;
        else IsMaximized = false;

        if (IsMaximized == false)
        {
            static std::shared_ptr<VinaFAIcon>max = std::make_shared<VinaFAIcon>();
            max->Set(rc.right / gScale - 32 - 32, 20, L"win-max", 15, VERTEXUICOLOR_WHITE, [hWnd] {
                IsMaximized = !IsMaximized;
                SendMessage(hWnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0); });
            MainWindow->GetPanel()->Add(max);
        }
        else {
            static std::shared_ptr<VinaFAIcon>max = std::make_shared<VinaFAIcon>();
            max->Set(rc.right / gScale - 32 - 32, 20, L"win-restore", 15, VERTEXUICOLOR_WHITE, [hWnd] {
                IsMaximized = !IsMaximized;
                SendMessage(hWnd, WM_SYSCOMMAND, SC_RESTORE, 0); });
            MainWindow->GetPanel()->Add(max);
        }
        static std::shared_ptr<VinaFAIcon>min = std::make_shared<VinaFAIcon>();
        min->Set(rc.right / gScale - 32 - 32 - 32, 20, L"win-min", 15, VERTEXUICOLOR_WHITE, [hWnd] {MainWindow->KillAnimation(); SendMessage(hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0); });
        MainWindow->GetPanel()->Add(min);



        });

    MainWindow->SetOutFrame(VinaWindow::Client);
    MainWindow->OnCreateCmd = [] {
        VertexUI::Window::Utils::CenterWindow(MainWindow->GetHandle());
        };
    MainWindow->RunFull();

    return 0;
}