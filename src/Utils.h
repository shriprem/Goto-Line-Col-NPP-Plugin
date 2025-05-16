#pragma once

#include "PluginDefinition.h"
#include <codecvt>

#define PREFS_TIP_MAX_WIDTH         400

namespace Utils {
   int StringtoInt(const string& str, int base = 10);
   int StringtoInt(const wstring& str, int base = 10);
   LPCWSTR ToUpper(LPWSTR str);
   string& LTrim(string& s, const char* t = " ");

   HWND addTooltip(HWND hDlg, int controlID, const wstring& pTitle, const wstring& pMessage, bool bBalloon = TRUE);
   HWND addTooltip(HWND hDlg, int controlID, const wstring& pTitle, const wstring& pMessage, int duration, bool bBalloon);
   void addToolbarIcon(int menuIndex, int std, int fluent, int dark);
   void checkMenuItem(int menuIndex, bool check);
   void showEditBalloonTip(HWND hEdit, LPCWSTR title, LPCWSTR text);
   bool checkBaseOS(winVer os);
   float getNPPVersion();
   wstring getVersionInfo(LPCWSTR key);
   void loadBitmap(HWND hDlg, int controlID, int resource);

   void setFont(HWND hDlg, int controlID, wstring& name, int height,
      int weight = FW_REGULAR, bool italic = FALSE, bool underline = FALSE);
   bool setFontRegular(HWND hDlg, int controlID);
   bool setFontBold(HWND hDlg, int controlID);
   bool setFontItalic(HWND hDlg, int controlID);
   bool setFontUnderline(HWND hDlg, int controlID);

   bool checkDirectoryExists(LPCWSTR lpDirPath);
   bool checkFileExists(LPCWSTR lpFilePath);
}
