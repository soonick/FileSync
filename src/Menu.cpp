/*
    Menu.cpp
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
#include "DlgSettings.h"
#include "Menu.h"
#include "Util.h"
#include "res\resource.h"
#include <strsafe.h>

namespace NppPlugin
{
    namespace {
        #define PLUGIN_ABOUT     PLUGIN_FULL_NAME SPACE_STR PLUGIN_VERSION _T("\nA plugin for Notepad++")

        // Menu callback functions
        extern "C" {
            void cbConfigure();
            void cbAbout();
        };

        // Menu items
        const INT _mnuItmCnt = 3;
        FuncItem _mnuItems[] = {
            { _T("&Configure..."), cbConfigure, 0, false, NULL },
            { EMPTY_STR,          NULL,       0, false, NULL },
            { _T("&About..."),    cbAbout,    0, false, NULL }
        };
    }

    // The api namespace contains functions called only from DllMain.
    namespace api {
        FuncItem* mnu_getItems(INT *pNum)
        {
            *pNum = _mnuItmCnt;
            return _mnuItems;
        }
    }

    namespace {
        /**
         * cbConfigure
         * Shows dialog to configure plugin
         *
         * @return void
         */
        extern "C" void cbConfigure()
        {
            DialogBox(sys_getDllHwnd(), MAKEINTRESOURCE(ID_CFG_DLG), sys_getNppHwnd(), dlgCfg_msgProc);
        }

        /**
         * cbAbout
         * Shows dialog with information about the plugin
         *
         * @return void
         */
        extern "C" void cbAbout()
        {
            const size_t s = 6 * MAX_PATH;
            TCHAR m[s + 1];
            StringCchCopy(m, s, PLUGIN_ABOUT);
            msgBox(m);
        }
    }
}
