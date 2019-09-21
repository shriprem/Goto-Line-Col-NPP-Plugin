#include "PluginDefinition.h"

void PreferencesIO::init() {
   ::SendMessage(nppData._nppHandle, NPPM_GETPLUGINSCONFIGDIR, MAX_PATH, (LPARAM)iniFilePath);

   // if config path doesn't exist, create it
   if (!PathFileExists(iniFilePath))
   {
      ::CreateDirectory(iniFilePath, NULL);
   }

   PathAppend(iniFilePath, configFileName);

   // if no config file doesn't exist, create it
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
   allPrefs.showCallTip = (getPref(showCallTipKey, TRUE) != FALSE);
   allPrefs.braceHilite = (getPref(braceHiliteKey, TRUE) != FALSE);
   allPrefs.expandTabs = (getPref(expandTabsKey, TRUE) != FALSE);

   int edgeBuffer = getPref(edgeBufferKey, 5);
   allPrefs.edgeBuffer = (edgeBuffer < 1) ? 1 : ((edgeBuffer > 10) ? 10 : edgeBuffer);

   int caretFlash = getPref(caretFlashSecondsKey, 3);
   allPrefs.caretFlashSeconds = (caretFlash < 1) ? 1 : ((caretFlash > 10) ? 10 : caretFlash);

   allPrefs.showTooltip = (getPref(showTooltipKey, TRUE) != FALSE);

   int tooltipSeconds = getPref(tooltipSecondsKey, 10);
   allPrefs.tooltipSeconds = (tooltipSeconds < 1) ? 1 : ((tooltipSeconds > 20) ? 20 : tooltipSeconds);

   return allPrefs;
}

ALL_PREFERENCES PreferencesIO::resetPreferences() {
   ALL_PREFERENCES defPrefs;
   defPrefs.fillOnFocus = TRUE;
   defPrefs.fillOnTabChange = TRUE;
   defPrefs.showCallTip = TRUE;
   defPrefs.braceHilite = TRUE;
   defPrefs.expandTabs = FALSE;
   defPrefs.edgeBuffer = 5;
   defPrefs.caretFlashSeconds = 3;
   defPrefs.showTooltip = TRUE;
   defPrefs.tooltipSeconds = 10;

   return defPrefs;
}

void PreferencesIO::savePreferences(ALL_PREFERENCES prefs) {
   allPrefs = prefs;

   setPref(autoFillOnFocusKey, prefs.fillOnFocus);
   setPref(autoFillOnTabChangeKey, prefs.fillOnTabChange);
   setPref(showCallTipKey, prefs.showCallTip);
   setPref(braceHiliteKey, prefs.braceHilite);
   setPref(expandTabsKey, prefs.expandTabs);

   setPref(edgeBufferKey, prefs.edgeBuffer);
   setPref(caretFlashSecondsKey, prefs.caretFlashSeconds);

   setPref(showTooltipKey, prefs.showTooltip);
   setPref(tooltipSecondsKey, prefs.tooltipSeconds);
}
