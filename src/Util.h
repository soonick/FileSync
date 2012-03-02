/*
    Util.h
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

#ifndef NPP_PLUGIN_UTIL_H
#define NPP_PLUGIN_UTIL_H

namespace NppPlugin {
    #define EMPTY_STR _T("")
    #define SPACE_STR _T(" ")
    #define M_ERR  PLUGIN_FULL_NAME SPACE_STR _T("Error"), (MB_OK | MB_ICONERROR)

    INT msgBox(const TCHAR *m, TCHAR *title = NULL, UINT options = MB_OK);
    void createIfNotPresent(TCHAR *filename, const char *contents);

    namespace pth {
        bool addSlash(TCHAR *p);
    }
}

#endif
