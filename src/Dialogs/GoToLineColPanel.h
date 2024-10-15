#pragma once

#include "../CommandLineOptions.h"
#include "../NameBlocks.h"
#include "../Utils.h"
#include "../PreferencesIO.h"
#include "../NPP/DockingDlgInterface.h"

extern PreferencesIO _prefsIO;

static bool idemPotentKey {FALSE};
constexpr int BUFFER_500{ 500 };
constexpr int BUFFER_100{ 100 };
constexpr int BUFFER_20{ 20 };

class GotoLineColPanel : public DockingDlgInterface {
public :
   bool _newCmdLine{};

   GotoLineColPanel() :DockingDlgInterface(IDD_GOTOLINECOL_DOCKPANEL) {};

   void initPrefs();
   void initPanel();
   void scanCommandLine() { cmdOpt.scan(allPrefs); _newCmdLine = FALSE; };

   void onBufferActivated();
   void localize();
   virtual void display(bool toShow=true);
   void refreshDarkMode();
   void setParent(HWND parent2set);

   void showPreferencesDialog();
   void showAboutDialog();

   void reloadPanelPreferences();
   void updatePanelInfo();
   void clearCalltip();
   void loadCursorPosData();
   ALL_PREFERENCES getPrefs() const { return allPrefs; }

protected:
   HWND hFieldInfo{};
   ALL_PREFERENCES allPrefs{};
   char cursorPosData[BUFFER_500]{};
   CommandLineOptions cmdOpt{};
   NameBlocks nb{};

   virtual INT_PTR CALLBACK run_dlgProc(UINT message, WPARAM wParam, LPARAM lParam);
   static DWORD WINAPI threadPositionHighlighter(void*);

   static intptr_t getLineCount();
   static void setFocusOnEditor();
   void onPanelResize(LPARAM lParam);

   intptr_t getLineMaxPos(intptr_t line) const;
   intptr_t getDocumentColumn(HWND hScintilla, intptr_t pos, intptr_t line) const;
   intptr_t setDocumentColumn(HWND hScintilla, intptr_t line, intptr_t lineStartPos, intptr_t lineMaxPos, intptr_t column) const;
   intptr_t getInputLineValidated();
   int getInputColumn() const;
   void updateLineRangeText();
   void updateColumnRangeText(intptr_t line);
   void switchLine(bool bNext);
   void switchCol(bool bNext);
   int navigateToColPos();
   int navigateToColPos(intptr_t line, intptr_t column);
   void updatePanelColPos();
   void initCursorPosData(HWND hScintilla, intptr_t line, intptr_t column, intptr_t atPos);
};
