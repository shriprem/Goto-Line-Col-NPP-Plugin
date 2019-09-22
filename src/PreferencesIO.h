#pragma once

#ifndef _PREFERENCES_INI_H
#define _PREFERENCES_INI_H

#include "NPP/PluginInterface.h"

extern NppData nppData;

#define TO_STR(str) std::to_string(str)
#define TO_WSTR(str) std::to_wstring(str)
#define TO_LPCSTR(str) std::to_string(str).c_str()
#define TO_LPCWSTR(str) std::to_wstring(str).c_str()

struct ALL_PREFERENCES{
   int language = LANG_ENGLISH;
   int fillOnFocus = TRUE;
   int fillOnTabChange = TRUE;
   int showCallTip = TRUE;
   int braceHilite = TRUE;
   int expandTabs = FALSE;
   int edgeBuffer = 5;
   int caretFlashSeconds = 3;
   int showTooltip = TRUE;
   int tooltipSeconds = 10;
};

const int PREFS_STR_MAX_LEN = 20;

class PreferencesIO {
public:
   ALL_PREFERENCES allPrefs;

   void init();
   int getPref(LPCWSTR key, int default);
   void setPref(LPCWSTR key, int val);
   int getIdemPotentKey();
   void setIdemPotentKey(int val);
   ALL_PREFERENCES loadPreferences();
   ALL_PREFERENCES resetPreferences();
   void savePreferences(ALL_PREFERENCES prefs);

protected:
   TCHAR iniFilePath[MAX_PATH];
   const TCHAR sectionName[PREFS_STR_MAX_LEN]            = L"Preferences";
   const TCHAR configFileName[PREFS_STR_MAX_LEN]         = L"GotoLineCol.ini";

   const TCHAR autoFillOnFocusKey[PREFS_STR_MAX_LEN]     = L"FillOnFocus";
   const TCHAR autoFillOnTabChangeKey[PREFS_STR_MAX_LEN] = L"FillOnTabChange";
   const TCHAR showCallTipKey[PREFS_STR_MAX_LEN]         = L"ShowCallTip";
   const TCHAR braceHiliteKey[PREFS_STR_MAX_LEN]         = L"BraceHighlight";
   const TCHAR expandTabsKey[PREFS_STR_MAX_LEN]       = L"ExpandTabs";

   const TCHAR edgeBufferKey[PREFS_STR_MAX_LEN]       = L"EdgeBuffer";
   const TCHAR caretFlashSecondsKey[PREFS_STR_MAX_LEN]      = L"FlashSeconds";

   const TCHAR showTooltipKey[PREFS_STR_MAX_LEN]         = L"ShowTooltip";
   const TCHAR tooltipSecondsKey[PREFS_STR_MAX_LEN]      = L"TooltipSeconds";
   const TCHAR caretIdemPotentKey[PREFS_STR_MAX_LEN]     = L"IdemPotencyCheck";
};

#endif //_PREFERENCES_INI_H