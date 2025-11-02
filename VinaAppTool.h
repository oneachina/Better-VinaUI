#pragma once
#include <ShlObj.h>
#include <iostream>
#pragma warning(disable : 4996)
#pragma warning(disable : 6031)

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