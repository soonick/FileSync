/*
    FileSync.cpp
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
#include "Menu.h"
#include <strsafe.h>
#include <time.h>
#include <vector>

using std::vector;

namespace NppPlugin {
    namespace {
        #define PLUGIN_MENU_NAME _T("&") PLUGIN_FULL_NAME
    }

    // The api namespace contains functions called only from DllMain.
    namespace api {
        /**
         * app_getName
         * Returns name of plugin
         *
         * @return  const TCHAR*    Plugin name
         */
        const TCHAR* app_getName()
        {
            return PLUGIN_MENU_NAME;
        }

        /* Handle Notepad++ notifications. */
        /**
         * app_onNotify
         * Handles all notifications sent to the dll
         *
         * @param   SCNotification* pscn.- Pointer to Scintilla notification object
         *
         * @return  void
         */
        void app_onNotify(SCNotification *pscn)
        {
            // Currently this plugin only cares about when a file is saved
            if (pscn->nmhdr.code == NPPN_FILESAVED)
            {
                int savedFileLength;
                int savedFileLongitud;
                int sourceFolderLongitud;
                TCHAR *savedFile;
                TCHAR *source;

                // Get the full path of the saved file
                savedFileLength = SendMessage(
                    sys_getNppHwnd(),
                    NPPM_GETFULLPATHFROMBUFFERID,
                    (WPARAM)pscn->nmhdr.idFrom,
                    (LPARAM)NULL
                );
                savedFile = new TCHAR[savedFileLength + 1];
                savedFileLength = SendMessage(
                    sys_getNppHwnd(),
                    NPPM_GETFULLPATHFROMBUFFERID,
                    (WPARAM)pscn->nmhdr.idFrom,
                    (LPARAM)savedFile
                );

                source = new TCHAR[255];
                gCfg.readCurrent(source, _T("source"));
                savedFileLongitud = _tcslen(savedFile);
                sourceFolderLongitud = _tcslen(source);

                // If the complete path of the saved file is shorter than the path
                // of the source folder then we know that the file isn't inside that
                // folder
                if (sourceFolderLongitud < savedFileLongitud)
                {
                    // Verify that the first characters of the path of the saved file
                    // match with the source directory
                    TCHAR *savedFilePathBeginning;
                    savedFilePathBeginning = new TCHAR[sourceFolderLongitud + 1];
                    _tcsncpy(savedFilePathBeginning, savedFile, sourceFolderLongitud);
                    savedFilePathBeginning[sourceFolderLongitud] = '\0';

                    if (!_tcscmp(savedFilePathBeginning, source))
                    {
                        const TCHAR *destinyFile = 0;
                        TCHAR *destiny;

                        destiny = new TCHAR[255];
                        gCfg.readCurrent(destiny, _T("destiny"));

                        std::wstring stringDestiny(destiny);
                        std::wstring stringTheFullPath(savedFile);

                        stringTheFullPath.replace(0, sourceFolderLongitud, stringDestiny);

                        destinyFile = stringTheFullPath.data();
                        CopyFile(
                            savedFile,
                            destinyFile,
                            false
                        );

                        delete[] destiny;
                    }

                    delete[] savedFilePathBeginning;
                }

                delete[] savedFile;
                delete[] source;
            }
        }
    }
}
