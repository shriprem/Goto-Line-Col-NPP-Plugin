#pragma once

#include "PluginDefinition.h"

struct ALL_PREFERENCES {
   int fillOnFocus = TRUE;
   int fillOnTabChange = TRUE;
   int showCalltip = TRUE;
   int braceHilite = TRUE;
   int useByteCol = TRUE;
   int centerCaret = TRUE;
   int edgeBuffer = 10;
   int caretFlashSeconds = 3;
   int showTooltip = TRUE;
   int tooltipSeconds = 20;
   int cmdProcHidden = TRUE;
   int cmdProcPersist = FALSE;
};

const int PREFS_STR_MAX_LEN = 30;

class PreferencesIO {
public:
   ALL_PREFERENCES allPrefs;

   void init();
   int getPref(LPCWSTR key, int default);
   void setPref(LPCWSTR key, int val);
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
   const TCHAR useByteColKey[PREFS_STR_MAX_LEN]          = L"UseByteCol";
   const TCHAR centerCaretKey[PREFS_STR_MAX_LEN]         = L"CenterCaret";

   const TCHAR edgeBufferKey[PREFS_STR_MAX_LEN]          = L"EdgeBuffer";
   const TCHAR caretFlashSecondsKey[PREFS_STR_MAX_LEN]   = L"FlashSeconds";

   const TCHAR showTooltipKey[PREFS_STR_MAX_LEN]         = L"ShowTooltip";
   const TCHAR tooltipSecondsKey[PREFS_STR_MAX_LEN]      = L"TooltipSeconds";

   const TCHAR cmdProcHiddenKey[PREFS_STR_MAX_LEN]       = L"CmdProcHidden";
   const TCHAR cmdProcPersistKey[PREFS_STR_MAX_LEN]      = L"CmdProcPersist";
};
