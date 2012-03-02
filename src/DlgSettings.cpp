/*
    DlgSettings.cpp
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
#include "Util.h"
#include "res\resource.h"
#include <strsafe.h>

namespace NppPlugin {

    /**
     * dlgCfg_msgProc
     * Callback handler for configuration dialog
     *
     * @param   HWDN    hDlg.- Dialog window handler
     * @param   UINT    uMessage.- Message sent to the dialog
     * @param   WPARAM  wParam.- Id of clicked button
     * @param   LPARAM  lParam.- Extra information about the message
     *
     * @param   BOOLEAN TRUE if message was handled, FALSE otherwise
     */
    INT_PTR CALLBACK dlgCfg_msgProc(HWND hDlg, UINT uMessage, WPARAM wParam,
            LPARAM lParam)
    {
        // Fill source and destiny Edittexts when dialog is loaded
        if (uMessage == WM_INITDIALOG)
        {
            TCHAR source[255];
            TCHAR destiny[255];
            gCfg.readCurrent(source, _T("source"));
            gCfg.readCurrent(destiny, _T("destiny"));
            SetDlgItemText(
                hDlg,
                ID_CFG_DLG_SOURCE_EDT,
                source
            );
            SetDlgItemText(
                hDlg,
                ID_CFG_DLG_DESTINATION_EDT,
                destiny
            );

            return TRUE;
        }

        // Add event listeners
        if (uMessage == WM_COMMAND) {
            WORD ctrl = LOWORD(wParam);
            switch (ctrl) {
                case IDOK:
                    // Save the source and destiny paths to config file
                    TCHAR srcDir[255];
                    GetDlgItemText(
                        hDlg,
                        ID_CFG_DLG_SOURCE_EDT,
                        srcDir,
                        255
                    );
                    gCfg.saveCurrent(srcDir, _T("source"));

                    TCHAR destinyDir[255];
                    GetDlgItemText(
                        hDlg,
                        ID_CFG_DLG_DESTINATION_EDT,
                        destinyDir,
                        255
                    );
                    gCfg.saveCurrent(destinyDir, _T("destiny"));

                    // Close de dialog
                    EndDialog(hDlg, 1);

                    break;
                default:
                    EndDialog(hDlg, 0);
            }
            return TRUE;
        }

        return FALSE;
    }
}
