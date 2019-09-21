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

#include "GoToLineColPanel.h"
#include <time.h>

INT_PTR CALLBACK GotoLineColDlg::run_dlgProc(UINT message, WPARAM wParam, LPARAM lParam) {
   switch (message) {
   case WM_COMMAND :
   {
      switch LOWORD(wParam) {
      case IDC_GOLINE_EDIT:
         updateColumnRangeText(getInputLineValidated());
         break;

      case IDOK :
         navigateToColPos();
         break;

      case IDCANCEL:
      case IDCLOSE :
         setFocusOnEditor();
         ShowGotoLineColPanel(false);
         break;

      case IDC_GOLINECOL_PREFS:
         ::SetFocus(_hSelf);
         ShowPreferencesDialog();
         break;
      }

      break;
   }

   case WM_LBUTTONDOWN:
   case WM_MBUTTONDOWN:
   case WM_RBUTTONDOWN:
      ::SetFocus(_hSelf);
      break;

   case WM_SETFOCUS :
   {
      if (allPrefs.fillOnFocus)
         updatePanelColPos();
      break;
   }

   default :
      return DockingDlgInterface::run_dlgProc(message, wParam, lParam);
   }

   return FALSE;
}

void GotoLineColDlg::display(bool toShow) const {
   DockingDlgInterface::display(toShow);
   if (toShow) {
      ::SetFocus(::GetDlgItem(_hSelf, IDC_GOLINE_EDIT));
   }
};

void GotoLineColDlg::setParent(HWND parent2set) {
   _hParent = parent2set;
};

void GotoLineColDlg::loadPreferences() {
   allPrefs = _prefsIO.loadPreferences();
}

void GotoLineColDlg::updatePanelColPos() {
   HWND hScintilla = getCurrentScintilla();
   if (!hScintilla)
      return;

   int pos = (int)::SendMessage(hScintilla, SCI_GETCURRENTPOS, 0, 0);
   int line = (int)::SendMessage(hScintilla, SCI_LINEFROMPOSITION, pos, 0) + 1;
   int col = getDocumentColumn(hScintilla, pos, line);

   ::SetDlgItemText(_hSelf, IDC_GOLINE_EDIT, TO_LPCWSTR(line));
   updateLineRangeText();

   ::SetDlgItemText(_hSelf, IDC_GOCOL_EDIT, TO_LPCWSTR(col));
   updateColumnRangeText(line);

   // Clear Idem Potent key if it's still set from a premature program termination
   _prefsIO.setIdemPotentKey(FALSE);
}

void GotoLineColDlg::braceHighlight() {
   HWND hScintilla = getCurrentScintilla();
   if (!hScintilla)
      return;

   int pos = (int)::SendMessage(hScintilla, SCI_GETCURRENTPOS, 0, 0);
   ::SendMessage(hScintilla, SCI_BRACEHIGHLIGHT, pos, pos);
}

//
// Private Functions:
//

HWND GotoLineColDlg::getCurrentScintilla() {
   int which = -1;
   ::SendMessage(nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)& which);
   if (which < 0)
      return (HWND)FALSE;
   return (HWND)(which == 0) ? nppData._scintillaMainHandle : nppData._scintillaSecondHandle;
}

int GotoLineColDlg::getLineCount() {
   HWND hScintilla = getCurrentScintilla();
   if (!hScintilla)
      return -1;

   return (int)::SendMessage(hScintilla, SCI_GETLINECOUNT, 0, 0);
};

int GotoLineColDlg::setFocusOnEditor() {
   HWND hScintilla = getCurrentScintilla();
   if (!hScintilla)
      return -1;

   return (int)::SendMessage(hScintilla, SCI_GRABFOCUS, 0, 0);
};

int GotoLineColDlg::getLineMaxPos(int line) {
   HWND hScintilla = getCurrentScintilla();
   if (!hScintilla)
      return -1;

   int endPos = (int)::SendMessage(hScintilla, SCI_GETLINEENDPOSITION, line - 1, 0);

   int col = (allPrefs.expandTabs) ?
               (int)::SendMessage(hScintilla, SCI_GETCOLUMN, endPos, 0) :
               endPos - (int)::SendMessage(hScintilla, SCI_POSITIONFROMLINE, line - 1, 0);

   return col + 1;
};

int GotoLineColDlg::getDocumentColumn(HWND hScintilla, int pos, int line) {
   int col = (allPrefs.expandTabs) ?
               (int)::SendMessage(hScintilla, SCI_GETCOLUMN, pos, 0) :
               pos - (int)::SendMessage(hScintilla, SCI_POSITIONFROMLINE, line - 1, 0);

   return col + 1;
}

void GotoLineColDlg::setDocumentColumn(HWND hScintilla, int line, int lineStartPos, int lineMaxPos, int column) {
   column = (column < 1) ? 1 :
            (column > lineMaxPos) ? lineMaxPos : column;

   int gotoPos = (allPrefs.expandTabs) ?
                  (int)::SendMessage(hScintilla, SCI_FINDCOLUMN, line - 1, column - 1) :
                  lineStartPos + column - 1;

   ::SendMessage(hScintilla, SCI_GOTOPOS, gotoPos, 0);
}

int GotoLineColDlg::getInputLineValidated() {
   BOOL isSuccessful;

   int line = ::GetDlgItemInt(_hSelf, IDC_GOLINE_EDIT, &isSuccessful, FALSE);
   if (!isSuccessful)
      return 1;

   int lineCount = getLineCount();
   return ((line < 0) ? 1 : ((line > lineCount) ? lineCount : line));
};

int GotoLineColDlg::getInputColumn() const {
   BOOL isSuccessful;

   int col = ::GetDlgItemInt(_hSelf, IDC_GOCOL_EDIT, &isSuccessful, FALSE);
   return (isSuccessful ? col : 1);
};

void GotoLineColDlg::updateLineRangeText() {
   ::SetDlgItemText(_hSelf, IDC_GOLINE_RANGE, (L"Max for file:  " + TO_WSTR(getLineCount())).c_str());
}

void GotoLineColDlg::updateColumnRangeText(int line) {
   ::SetDlgItemText(_hSelf, IDC_GOCOL_RANGE, (L"Max for line:  " + TO_WSTR(getLineMaxPos(line))).c_str());
}

int GotoLineColDlg::navigateToColPos() {
   HWND hScintilla = getCurrentScintilla();
   if (!hScintilla)
      return FALSE;

   int line = getInputLineValidated();

   ::SendMessage(hScintilla, SCI_ENSUREVISIBLE, line - 1, 0);

   int lineMaxPos = getLineMaxPos(line);
   int lineStartPos = (int)::SendMessage(hScintilla, SCI_POSITIONFROMLINE, line - 1, 0);

   int column = getInputColumn();

   // Clear a buffer of edgebuffer positions on either side if possible so that
   // the cursor is not stuck aligned with the side margins
   setDocumentColumn(hScintilla, line, lineStartPos, lineMaxPos, column - allPrefs.edgeBuffer);
   setDocumentColumn(hScintilla, line, lineStartPos, lineMaxPos, column + allPrefs.edgeBuffer);
   setDocumentColumn(hScintilla, line, lineStartPos, lineMaxPos, column);

   // Switch focus from the dock to the editor
   setFocusOnEditor();

   // Display call tip
   if (allPrefs.showCallTip) {
      int currPos = (int)::SendMessage(hScintilla, SCI_GETCURRENTPOS, 0, 0);
      int currLine = (int)::SendMessage(hScintilla, SCI_LINEFROMPOSITION, currPos, 0) + 1;
      int currCol = getDocumentColumn(hScintilla, currPos, currLine);
      int posChar = (int)::SendMessage(hScintilla, SCI_GETCHARAT, currPos, 0);

      char callTip[100];
      sprintf(callTip, "     Line: %u\n   Column: %u\nChar Code: %u [0x%X]", currLine, currCol, posChar, posChar);
      ::SendMessage(hScintilla, SCI_CALLTIPSHOW, currPos, (LPARAM)callTip);
   }

   // Flash caret
   HANDLE hThread = ::CreateThread(NULL, 0, threadPositionHighlighter, 0, 0, NULL);
   if (hThread > 0)
      ::CloseHandle(hThread);

   return TRUE;
}

DWORD WINAPI GotoLineColDlg::threadPositionHighlighter(void*) {
   const int MEANING_OF_LIFE = 42;
   ALL_PREFERENCES allPrefs = _prefsIO.loadPreferences();

   // Get the current scintilla
   int which = -1;
   ::SendMessage(nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)& which);
   if (which == -1)
      return FALSE;

   HWND hScintilla = (which == 0) ? nppData._scintillaMainHandle : nppData._scintillaSecondHandle;

   // Get caret highlight duration
   bool idemPotentFail;

   // Look for Idem Potency Hold
   idemPotentFail = (_prefsIO.getIdemPotentKey() == MEANING_OF_LIFE);

   if (idemPotentFail)
      //  Idem Potency check failed. Another thread is processing this same function. Return immediately.
      return FALSE;
   else
      // OK to continue. Set Idem Potency Hold
      _prefsIO.setIdemPotentKey(MEANING_OF_LIFE);

   // Modify caret style briefly to highlight the new position
   int currCaret = (int)::SendMessage(hScintilla, SCI_GETCARETSTYLE, 0, 0);
   ::SendMessage(hScintilla, SCI_SETCARETSTYLE, CARETSTYLE_BLOCK, 0);
   Sleep(allPrefs.caretFlashSeconds * 1000);
   ::SendMessage(hScintilla, SCI_SETCARETSTYLE, currCaret, 0);

   if (allPrefs.braceHilite) {
      int pos = (int)::SendMessage(hScintilla, SCI_GETCURRENTPOS, 0, 0);
      ::SendMessage(hScintilla, SCI_BRACEHIGHLIGHT, pos, -1);
   }

   // Clear Idem Potency Hold
   _prefsIO.setIdemPotentKey(FALSE);

   return TRUE;
}
