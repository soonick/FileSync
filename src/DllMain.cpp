/*
    DllMain.cpp
    Copyright 2012 Adrian Ancona (https://github.com/soonick/filesync)

    This file is part of FileSync, A Plugin for Notepad++.

    FileSync is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "System.h"
#include "FileSync.h"
#include "Menu.h"

using namespace NppPlugin::api;

/**
 * DllMain
 * Dll entry point. This is the first thing that gets executed when the system starts
 *
 * @param   HINSTANCE   hInstance.- A handle to the DLL module. The value is the base
 *                      address of the DLL.
 * @param   DWORD       dwReason.- Contains the reason why this function is being
 *                      called.
 * @param   LPVOID      lpReserved.- Tells if this is a static or dynamic load
 *
 * @return  BOOLEAN     Always TRUE
 */
BOOL APIENTRY DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason) {
        case DLL_PROCESS_ATTACH:
            sys_onLoad(hInstance);
            break;
    }

    return TRUE;
}

extern "C" __declspec(dllexport) void setInfo(NppData nppd)
{
    sys_init(nppd);
}

extern "C" __declspec(dllexport) const TCHAR* getName()
{
    return app_getName();
}

extern "C" __declspec(dllexport) FuncItem* getFuncsArray(INT *pnbFuncItems)
{
    return mnu_getItems(pnbFuncItems);
}

extern "C" __declspec(dllexport) void beNotified(SCNotification *pscn)
{
    app_onNotify(pscn);
}

extern "C" __declspec(dllexport) LRESULT messageProc(UINT Message, WPARAM wParam, LPARAM lParam)
{
    return 1;
}

#ifdef UNICODE
extern "C" __declspec(dllexport) BOOL isUnicode()
{
    return TRUE;
}
#endif
