#pragma once

#include "../CommandLineOptions.h"
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
   GotoLineColPanel() :DockingDlgInterface(IDD_GOTOLINECOL_DOCKPANEL) {};

   void initPrefs();
   void initPanel();

   void onBufferActivated();
   void localize();
   virtual void display(bool toShow=true);
   void setParent(HWND parent2set);
   void loadPreferences();
   void clearCalltip();
   void loadCursorPosData();

protected :
   ALL_PREFERENCES allPrefs{};
   char cursorPosData[BUFFER_500];
   CommandLineOptions cmdOpt{};

   virtual INT_PTR CALLBACK run_dlgProc(UINT message, WPARAM wParam, LPARAM lParam);
   static DWORD WINAPI threadPositionHighlighter(void*);

   static int getLineCount();
   static void setFocusOnEditor();
   int getLineMaxPos(int line);
   int getDocumentColumn(HWND hScintilla, int pos, int line);
   int setDocumentColumn(HWND hScintilla, int line, int lineStartPos, int lineMaxPos, int column);
   int getInputLineValidated();
   int getInputColumn() const;
   void updateLineRangeText();
   void updateColumnRangeText(int line);
   void switchLine(bool bNext);
   void switchCol(bool bNext);
   int navigateToColPos();
   int navigateToColPos(int line, int column);
   void updatePanelColPos();
   void initCursorPosData(HWND hScintilla, int line, int column, int atPos);
};
