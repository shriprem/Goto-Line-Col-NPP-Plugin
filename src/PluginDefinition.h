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

#pragma once

#define WIN32_LEAN_AND_MEAN      // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <string>

#include <windows.h>
#include <CommCtrl.h>
#include <shellapi.h>
#include <Shlwapi.h>

#include "NPP/PluginInterface.h"
#include "Resources/resource.h"
#include "Resources/control_ids.h"
#include "Resources/localization.h"

using std::string;
using std::string_view;
using std::wstring;
using std::to_string;
using std::to_wstring;

static int _gLanguage = LANG_ENGLISH;

const enum MenuIndex {
   MI_GOTO_PANEL,
   MI_PREFS_DIALOG,
   MI_SEPARATOR,
   MI_ABOUT_DIALOG,
   MI_COUNT
};

void pluginInit(HANDLE hModule);
void pluginCleanUp();
void commandMenuInit();
void commandMenuCleanUp();
bool setCommand(size_t index, const wstring& cmdName, PFUNCPLUGINCMD pFunc, ShortcutKey* sk = NULL, bool checkOnInit = false);

HWND getCurrentScintilla();
LRESULT nppMessage(UINT messageID, WPARAM wparam, LPARAM lparam);

// Plugin Command Functions
void ToggleGotoLineColPanel();
void ShowGotoLineColPanel(bool show);

void ShowPreferencesDialog();
void ShowAboutDialog();

void RegisterDockPanelIcon();
void RefreshDarkMode();
