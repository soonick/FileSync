/*
    System.cpp
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
#include "Config.h"
#include "Util.h"
#include <strsafe.h>


namespace NppPlugin {

    namespace {
        #define INI_FILE_NAME  _T("settings.ini")

        HWND _hNpp;
        HINSTANCE _hDll;
        TCHAR _cfgDir[MAX_PATH_1]; // includes trailing slash
        TCHAR _iniFile[MAX_PATH_1];
    }

    // The api namespace contains functions called only from DllMain.
    namespace api {
        void sys_onLoad(HINSTANCE hDLLInstance)
        {
            _hDll = hDLLInstance;
        }

        void sys_init(NppData nppd)
        {
            // Save NPP window handles
            _hNpp = nppd._nppHandle;

            // Get plugin config directory from NPP.
            SendMessage(_hNpp, NPPM_GETPLUGINSCONFIGDIR, MAX_PATH, (LPARAM)_cfgDir);

            // Get FileSync config directory and create it if not present.
            pth::addSlash(_cfgDir);
            StringCchCat(_cfgDir, MAX_PATH, PLUGIN_DLL_NAME);
            StringCchCat(_cfgDir, MAX_PATH, _T("\\"));
            CreateDirectory(_cfgDir, NULL);

            // Get ini file pathname.
            StringCchCopy(_iniFile, MAX_PATH, _cfgDir);
            StringCchCat(_iniFile, MAX_PATH, INI_FILE_NAME);

            // Load the config file.
            gCfg.load();
        }
    }

    TCHAR* sys_getIniFile()
    {
        return _iniFile;
    }

    HINSTANCE sys_getDllHwnd()
    {
        return _hDll;
    }

    HWND sys_getNppHwnd()
    {
        return _hNpp;
    }
}
