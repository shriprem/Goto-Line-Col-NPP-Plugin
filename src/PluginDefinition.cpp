//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either
//version 2 of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.


#include "PluginDefinition.h"
#include <stdlib.h>
#include "NPP/menuCmdID.h"

#include "Dialogs/GoToLineColPanel.h"
#include "Dialogs/PreferencesDialog.h"
#include "Dialogs/AboutDialog.h"

#ifdef UNICODE
   #define generic_itoa _itow
#else
   #define generic_itoa itoa
#endif

#define INDEX_GOTO_PANEL 0
#define INDEX_PREFS_DIALOG 1
#define INDEX_ABOUT_DIALOG 3

FuncItem funcItem[nbFunc];

NppData nppData;
HINSTANCE _gModule;

PreferencesIO _prefsIO;
GotoLineColDlg _goToLine;
PreferencesDialog _prefsDlg;
AboutDialog _aboutDlg;

void pluginInit(HANDLE hModule) {
   _gModule = (HINSTANCE)hModule;
   _goToLine.init(_gModule, NULL);
}

void pluginCleanUp(){}

void commandMenuInit() {
   _prefsIO.init();

   ShortcutKey *shKeyOpen = new ShortcutKey;
   shKeyOpen->_isAlt = false;
   shKeyOpen->_isCtrl = true;
   shKeyOpen->_isShift = false;
   shKeyOpen->_key = VK_F7;

   ShortcutKey *shKeyPrefs = new ShortcutKey;
   shKeyPrefs->_isAlt = false;
   shKeyPrefs->_isCtrl = true;
   shKeyPrefs->_isShift = false;
   shKeyPrefs->_key = VK_F8;

   ShortcutKey *shKeyAbout = new ShortcutKey;
   shKeyAbout->_isAlt = false;
   shKeyAbout->_isCtrl = true;
   shKeyAbout->_isShift = false;
   shKeyAbout->_key = VK_F9;

   setCommand(INDEX_GOTO_PANEL, TEXT("Show Panel"), ToggleGotoLineColPanel, shKeyOpen, _goToLine.isVisible());
   setCommand(INDEX_PREFS_DIALOG, TEXT("Preferences"), ShowPreferencesDialog, shKeyPrefs, 0);
   setCommand(2, TEXT("-"), NULL, NULL, false);
   setCommand(INDEX_ABOUT_DIALOG, TEXT("About"), ShowAboutDialog, shKeyAbout, 0);
}


void commandMenuCleanUp() {
   delete funcItem[INDEX_GOTO_PANEL]._pShKey;
   delete funcItem[INDEX_PREFS_DIALOG]._pShKey;
   delete funcItem[INDEX_ABOUT_DIALOG]._pShKey;
}

// Initialize plugin commands
bool setCommand(size_t index, TCHAR *cmdName, PFUNCPLUGINCMD pFunc, ShortcutKey *sk, bool checkOnInit) {
    if (index >= nbFunc)
        return false;

    if (!pFunc)
        return false;

    lstrcpy(funcItem[index]._itemName, cmdName);
    funcItem[index]._pFunc = pFunc;
    funcItem[index]._init2Check = checkOnInit;
    funcItem[index]._pShKey = sk;

    return true;
}

HWND createToolTip(HWND hDlg, int toolID, LPWSTR pTitle, LPWSTR pMessage) {
   if (!toolID || !hDlg || !pMessage)
      return FALSE;

   // Get the window of the tool.
   HWND hwndTool = GetDlgItem(hDlg, toolID);

   // Create the tooltip.
   HWND hwndTip = CreateWindowEx(NULL, TOOLTIPS_CLASS, NULL,
      WS_POPUP | TTS_ALWAYSTIP | TTS_BALLOON,
      CW_USEDEFAULT, CW_USEDEFAULT,
      CW_USEDEFAULT, CW_USEDEFAULT,
      hDlg, NULL,
      _gModule, NULL);

   if (!hwndTool || !hwndTip)
      return (HWND)NULL;

   // Associate the tooltip with the tool.
   TOOLINFO toolInfo = { 0 };
   toolInfo.cbSize = sizeof(toolInfo);
   toolInfo.hwnd = hDlg;
   toolInfo.uFlags = TTF_IDISHWND | TTF_SUBCLASS;
   toolInfo.uId = (UINT_PTR)hwndTool;
   toolInfo.lpszText = pMessage;
   ::SendMessage(hwndTip, TTM_ADDTOOL, 0, (LPARAM)& toolInfo);
   ::SendMessage(hwndTip, TTM_SETTITLE, TTI_INFO, (LPARAM)pTitle);
   ::SendMessage(hwndTip, TTM_SETMAXTIPWIDTH, 0, (LPARAM)PREFS_TIP_MAX_WIDTH);

   return hwndTip;
}

// Dockable GotoLineCol Dialog
void ToggleGotoLineColPanel() {
   bool hidden = !_goToLine.isVisible();

   if (hidden) {
      _goToLine.setParent(nppData._nppHandle);
      tTbData  data = { 0 };

      if (!_goToLine.isCreated()) {
         _goToLine.create(&data);

         data.uMask = DWS_DF_CONT_RIGHT;
         data.pszModuleName = _goToLine.getPluginFileName();
         data.dlgID = INDEX_GOTO_PANEL;

         ::SendMessage(nppData._nppHandle, NPPM_DMMREGASDCKDLG, 0, (LPARAM)& data);
      }
   }
   ShowGotoLineColPanel(hidden);
}

void ShowGotoLineColPanel(bool show) {
   _goToLine.display(show);
   if (show)
      _goToLine.loadPreferences();

   ::CheckMenuItem(::GetMenu(nppData._nppHandle), funcItem[INDEX_GOTO_PANEL]._cmdID,
               MF_BYCOMMAND | (show ? MF_CHECKED : MF_UNCHECKED));
}

void GotoLineColDlgLoadPreferences() {
   if (_goToLine.isVisible())
      _goToLine.loadPreferences();
}

void ShowPreferencesDialog() {
   _prefsDlg.doDialog((HINSTANCE)_gModule);
}

void ShowAboutDialog() {
   _aboutDlg.doDialog((HINSTANCE)_gModule);
}
