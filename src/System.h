/*
    System.h
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

#ifndef NPP_PLUGIN_SYSTEM_H
#define NPP_PLUGIN_SYSTEM_H

#define MAX_PATH_1 (MAX_PATH + 1)

#include <windows.h>
#include <tchar.h>
#include "npp\PluginInterface.h"

namespace NppPlugin {
    // The api namespace contains functions called only from DllMain.
    namespace api {
        void sys_onLoad(HINSTANCE hDLLInstance);
        void sys_init(NppData nppd);
    }

    TCHAR* sys_getIniFile();
    HINSTANCE sys_getDllHwnd();
    HWND sys_getNppHwnd();
}

#endif
