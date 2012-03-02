/*
    Util.cpp
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
#include "Util.h"
#include <strsafe.h>

namespace NppPlugin {
    INT msgBox(const TCHAR *msg, TCHAR *title, UINT options)
    {
        return MessageBox(sys_getNppHwnd(), msg, title != NULL ? title : PLUGIN_FULL_NAME, options);
    }

    void createIfNotPresent(TCHAR *filename, const char *contents)
    {
        BOOL suc;
        HANDLE hFile;
        DWORD len, bytes;

        hFile = CreateFile(filename, GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile != INVALID_HANDLE_VALUE) {
            len = strlen(contents);
            suc = WriteFile(hFile, contents, len, &bytes, NULL);
            if (!suc || bytes != len) {
                TCHAR msg[MAX_PATH_1];
                StringCchCopy(msg, MAX_PATH, _T("Failed creating file: "));
                StringCchCat(msg, MAX_PATH, filename);
                msgBox(msg, M_ERR);
            }
            CloseHandle(hFile);
        }
    }

    namespace pth {
        // Append a backslash if it is not already present on the end of the string.
        bool addSlash(TCHAR *p)
        {
            size_t len;
            bool added = false;
            if (StringCchLength(p, MAX_PATH, &len) == S_OK) {
                TCHAR *s = p + len - 1;
                if (*s != _T('\\') && *s != _T('/')) {
                    StringCchCat(p, MAX_PATH, _T("\\"));
                    added = true;
                }
            }
            return added;
        }
    }
}
