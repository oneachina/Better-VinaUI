// VinaApp.cpp : 定义应用程序的入口点。
//
#include "framework.h"
#include "VinaApp.h"
#include "VertexUI/VertexUI.ClickArea.h"
#include "VertexUI/VertexUI.Panel.h"
#include "VertexUI/VertexUI.min.h"
#include "MainUI.hpp"
#include "VinaWindow.hpp"

#include <Psapi.h>
#include <ShlObj.h>
#include <direct.h>
#include <io.h>
#include <regex>
#pragma warning(disable:4996)
HANDLE hMyFont;
HGLOBAL hFntMem;
#define VERSION_STR L"v0.1.1"
VertexUIInit;
#define MAX_LOADSTRING 100


void GetAppdataPath(wchar_t* ud)
{
    wchar_t szDocument[MAX_PATH] = { 0 };

    LPITEMIDLIST pidl = NULL;
    SHGetSpecialFolderLocation(NULL, CSIDL_APPDATA, &pidl);
    if (pidl && SHGetPathFromIDList(pidl, szDocument))
    {
        GetShortPathName(szDocument, ud, _MAX_PATH);
    }
}
void GetLocalAppdataPath(wchar_t* ud)
{
    wchar_t szDocument[MAX_PATH] = { 0 };

    LPITEMIDLIST pidl = NULL;
    SHGetSpecialFolderLocation(NULL, CSIDL_LOCAL_APPDATA, &pidl);
    if (pidl && SHGetPathFromIDList(pidl, szDocument))
    {
        GetShortPathName(szDocument, ud, _MAX_PATH);
    }
}
void GetAppdataPathA(char ud[MAX_PATH])
{
    char szDocument[MAX_PATH] = { 0 };

    LPITEMIDLIST pidl = NULL;
    SHGetSpecialFolderLocation(NULL, CSIDL_APPDATA, &pidl);
    if (pidl && SHGetPathFromIDListA(pidl, szDocument))
    {
        GetShortPathNameA(szDocument, ud, _MAX_PATH);
        //strcat("\\CommandCube", ud);
    }
}
void GetLocalAppdataPathA(char ud[MAX_PATH])
{
    char szDocument[MAX_PATH] = { 0 };

    LPITEMIDLIST pidl = NULL;
    SHGetSpecialFolderLocation(NULL, CSIDL_LOCAL_APPDATA, &pidl);
    if (pidl && SHGetPathFromIDListA(pidl, szDocument))
    {
        GetShortPathNameA(szDocument, ud, _MAX_PATH);
        //strcat("\\CommandCube", ud);
    }
}
void SetTagW(wchar_t* buf, wchar_t* OldTag, wchar_t* newTag)
{
    wchar_t* start;
    int newlen = wcslen(newTag);
    int oldlen = wcslen(OldTag);
    start = wcsstr(buf, OldTag);
    while (start) {
        if (newlen > oldlen) wmemmove(start + newlen - oldlen, start, wcslen(start) + 1);
        if (newlen < oldlen) wmemmove(start, start + oldlen - newlen, wcslen(start) + 1);
        wmemmove(start, newTag, newlen);
        start += newlen;
        start = wcsstr(buf, OldTag);
    }

}
void mkdirs(wchar_t* muldir)
{
    int i, len;
    wchar_t str[512];
    wcsncpy(str, muldir, 512);
    len = wcslen(str);
    for (i = 0; i < len; i++)
    {
        if (str[i] == '/')
        {
            str[i] = '\0';
            if (_waccess(str, 0) != 0)
            {
                _wmkdir(str);
            }
            str[i] = '/';
        }
    }
    if (len > 0 && _waccess(str, 0) != 0)
    {
        _wmkdir(str);
    }
    return;
}
void SetDataBase()
{
    wchar_t test[260] = L"";
    GetAppdataPath(LocalData);
    GetAppdataPath(LocalAppData);
    GetAppdataPath(test);
    GetAppdataPathA(LocalDataA);
    GetAppdataPath(LocalLFData);
    GetAppdataPathA(LocalLFDataA);


    wcscat(LocalData, L"\\Vilinko\\VisUniverse");
    strcat(LocalDataA, "\\Vilinko\\VisUniverse");
    wcscat(LocalLFData, L"\\LightFrame");
    strcat(LocalLFDataA, "\\LightFrame");

    wcscpy(LocalData2, LocalData);
    wcscpy(LocalRes, LocalData);
    wcscpy(LocalCache, LocalData);
    strcpy(LocalCacheA, LocalDataA);
    wcscpy(LocalLFCache, LocalLFData);
    strcpy(LocalLFCacheA, LocalLFDataA);

    wcscpy(LocalCom, LocalData);
    wcscpy(LocalCards, LocalData);
    strcpy(LocalComA, LocalDataA);
    wcscat(LocalCom, L"\\Vilinko\\VisUniverse\\Components");
    wcscat(LocalCards, L"\\Vilinko\\VisUniverse\\Cards");
    strcat(LocalComA, "\\Vilinko\\VisUniverse\\Components");

    wcscat(LocalCache, L"\\Vilinko\\VisUniverse\\VisUniverse.vui");
    strcat(LocalCacheA, "\\Vilinko\\VisUniverse\\VisUniverse.vui");
    wcscat(LocalLFCache, L"\\LightFrame.vui");
    strcat(LocalLFCacheA, "\\LightFrame.vui");
    wcscat(LocalRes, L"\\Vilinko\\VisUniverse\\reslib");

    SetTagW(LocalData2, L"\\", L"/");
    SetTagW(LocalCache2, L"\\", L"/");
    if (_waccess(LocalData, 0) == -1)
    {
        mkdirs(LocalData2);
    }
}
BOOL FreeAnyResource(int Id, const wchar_t* Type, const wchar_t* Dir)
{
    HMODULE hModule = GetModuleHandle(NULL);
    if (hModule == NULL)
    {
        std::cerr << "错误：获取模块句柄失败。" << std::endl;
        return FALSE;
    }

    HRSRC hRsrc = FindResource(hModule, MAKEINTRESOURCE(Id), Type);
    if (hRsrc == NULL)
    {
        std::cerr << "错误：无法找到资源。" << std::endl;
        return FALSE;
    }

    DWORD dwSize = SizeofResource(hModule, hRsrc);
    if (dwSize == 0)
    {
        std::cerr << "错误：无效的资源大小。" << std::endl;
        return FALSE;
    }

    HGLOBAL hGlobal = LoadResource(hModule, hRsrc);
    if (hGlobal == NULL)
    {
        std::cerr << "错误：无法加载资源。" << std::endl;
        return FALSE;
    }

    LPVOID lpVoid = LockResource(hGlobal);
    if (lpVoid == NULL)
    {
        std::cerr << "错误：无法锁定资源。" << std::endl;
        FreeResource(hGlobal);
        return FALSE;
    }

    FILE* fp = _wfopen(Dir, L"wb+");
    if (fp == NULL)
    {
        std::cerr << "错误：无法创建或打开文件。" << std::endl;
        FreeResource(hGlobal);
        return FALSE;
    }

    fwrite(lpVoid, sizeof(char), dwSize, fp);
    fclose(fp);

    FreeResource(hGlobal);

    return TRUE;
}


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


    MainWindow->Set(100, 100, 720 * gScale, 480 * gScale, L"Vina.Class.App.Main.Test", L"Vilinko VinaUI");
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
        CenterWindow(MainWindow->GetHandle());
    };
    MainWindow->RunFull();

    return 0;
}


