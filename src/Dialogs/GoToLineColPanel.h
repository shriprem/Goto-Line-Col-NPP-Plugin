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

#ifndef GOTOLINECOL_DLG_H
#define GOTOLINECOL_DLG_H

#include "../Utils.h"
#include "../NPP/DockingDlgInterface.h"

extern NppData nppData;
extern PreferencesIO _prefsIO;

static bool idemPotentKey {FALSE};
constexpr int BUFFER_500{ 500 };
constexpr int BUFFER_100{ 100 };
constexpr int BUFFER_20{ 20 };

class GotoLineColPanel : public DockingDlgInterface {
public :
   GotoLineColPanel() :DockingDlgInterface(IDD_GOTOLINECOL_DOCKPANEL) {};

   void initPanel();
   void localize();
   virtual void display(bool toShow=true);
   void setParent(HWND parent2set);
   void loadPreferences();
   void updatePanelColPos();
   void clearCalltip();
   void loadCursorPosData();

protected :
   virtual INT_PTR CALLBACK run_dlgProc(UINT message, WPARAM wParam, LPARAM lParam);
   static DWORD WINAPI threadPositionHighlighter(void*);

   static HWND getCurrentScintilla();
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
   void initCursorPosData(HWND hScintilla, int line, int column, int atPos);

   ALL_PREFERENCES allPrefs;
   char cursorPosData[BUFFER_500];
};

#endif //GOTOLINECOL_DLG_H
