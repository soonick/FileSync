/*
    Config.cpp
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

namespace NppPlugin
{
    // The global configuration/settings object.
    Config gCfg;

    namespace {
        #define INI_SESSION _T("config")
        // Initial content of FileSync Configuration file
        #define DEFAULT_INI_CONTENTS "[config]\r\nsource=\r\ndestiny=\r\n"
    }

    /**
     * load
     * Created ini file if it doesn't exist.
     *
     * @return void
     */
    void Config::load()
    {
        TCHAR *iniFile = sys_getIniFile();
        createIfNotPresent(iniFile, DEFAULT_INI_CONTENTS);
    }

    /**
     * readCurrent
     * Gets value from ini file
     *
     * @param   TCHAR*  storage.- Pointer to variable where value is going to be
     *                  stored after retrieval
     * @param   TCHAR*  index.- Index to retrieve from ini file
     *
     * @return  void
     */
    void Config::readCurrent(TCHAR *storage, TCHAR *index)
    {
        GetPrivateProfileString(INI_SESSION, index, EMPTY_STR, storage, MAX_PATH,
                sys_getIniFile());
    }

    /* Write current session name s to ini file. */
    /**
     * saveCurrent
     * Save value to ini file
     *
     * @param   TCHAR*  value.- Value to store in ini file
     * @param   TCHAR*  index.- Index for the value
     *
     * @return  void
     */
    BOOL Config::saveCurrent(TCHAR *value, TCHAR *index)
    {
        BOOL status = WritePrivateProfileString(INI_SESSION, index, value,
                sys_getIniFile());
        return status;
    }
}

