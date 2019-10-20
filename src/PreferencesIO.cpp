#include "PluginDefinition.h"

void PreferencesIO::init() {
   ::SendMessage(nppData._nppHandle, NPPM_GETPLUGINSCONFIGDIR, MAX_PATH, (LPARAM)iniFilePath);

   // if no existing config path, create it
   if (!PathFileExists(iniFilePath))
   {
      ::CreateDirectory(iniFilePath, NULL);
   }

   PathAppend(iniFilePath, configFileName);

   // if no existing config file, create it
   if (!PathFileExists(iniFilePath)) {
      loadPreferences();
      savePreferences(allPrefs);
   }

   setIdemPotentKey(FALSE);
}

int PreferencesIO::getPref(LPCWSTR key, int default) {
   return ::GetPrivateProfileInt(sectionName, key, default, iniFilePath);
}

void PreferencesIO::setPref(LPCWSTR key, int val) {
   ::WritePrivateProfileString(sectionName, key, TO_LPCWSTR(val), iniFilePath);
}

int PreferencesIO::getIdemPotentKey() {
   return getPref(caretIdemPotentKey, FALSE);
}

void PreferencesIO::setIdemPotentKey(int val) {
   setPref(caretIdemPotentKey, val);
}

ALL_PREFERENCES PreferencesIO::loadPreferences() {
   allPrefs.fillOnFocus = (getPref(autoFillOnFocusKey, TRUE) != FALSE);
   allPrefs.fillOnTabChange = (getPref(autoFillOnTabChangeKey, TRUE) !=FALSE);
   allPrefs.showCalltip = (getPref(showCallTipKey, TRUE) != FALSE);
   allPrefs.braceHilite = (getPref(braceHiliteKey, TRUE) != FALSE);
   allPrefs.expandTabs = (getPref(expandTabsKey, FALSE) != FALSE);
   allPrefs.centerCaret = (getPref(centerCaretKey, TRUE) != FALSE);

   int edgeBuffer = getPref(edgeBufferKey, 10);
   allPrefs.edgeBuffer = (edgeBuffer < 1) ? 1 : ((edgeBuffer > 10) ? 10 : edgeBuffer);

   int caretFlash = getPref(caretFlashSecondsKey, 3);
   allPrefs.caretFlashSeconds = (caretFlash < 1) ? 1 : ((caretFlash > 10) ? 10 : caretFlash);

   allPrefs.showTooltip = (getPref(showTooltipKey, TRUE) != FALSE);

   int tooltipSeconds = getPref(tooltipSecondsKey, 20);
   allPrefs.tooltipSeconds = (tooltipSeconds < 1) ? 1 : ((tooltipSeconds > 20) ? 20 : tooltipSeconds);

   return allPrefs;
}

ALL_PREFERENCES PreferencesIO::resetPreferences() {
   ALL_PREFERENCES defPrefs;
   defPrefs.fillOnFocus = TRUE;
   defPrefs.fillOnTabChange = TRUE;
   defPrefs.showCalltip = TRUE;
   defPrefs.braceHilite = TRUE;
   defPrefs.expandTabs = FALSE;
   defPrefs.centerCaret = TRUE;
   defPrefs.edgeBuffer = 10;
   defPrefs.caretFlashSeconds = 3;
   defPrefs.showTooltip = TRUE;
   defPrefs.tooltipSeconds = 20;

   return defPrefs;
}

void PreferencesIO::savePreferences(ALL_PREFERENCES prefs) {
   allPrefs = prefs;

   setPref(autoFillOnFocusKey, prefs.fillOnFocus);
   setPref(autoFillOnTabChangeKey, prefs.fillOnTabChange);
   setPref(showCallTipKey, prefs.showCalltip);
   setPref(braceHiliteKey, prefs.braceHilite);
   setPref(expandTabsKey, prefs.expandTabs);
   setPref(centerCaretKey, prefs.centerCaret);

   setPref(edgeBufferKey, prefs.edgeBuffer);
   setPref(caretFlashSecondsKey, prefs.caretFlashSeconds);

   setPref(showTooltipKey, prefs.showTooltip);
   setPref(tooltipSecondsKey, prefs.tooltipSeconds);
}
