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
#include <wchar.h>

INT_PTR CALLBACK GotoLineColPanel::run_dlgProc(UINT message, WPARAM wParam, LPARAM lParam) {
   switch (message)
   {
      case WM_COMMAND :
         switch LOWORD(wParam)
         {
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

      case WM_LBUTTONDOWN:
      case WM_MBUTTONDOWN:
      case WM_RBUTTONDOWN:
         ::SetFocus(_hSelf);
         break;

      case WM_NOTIFY:
         switch (((LPNMHDR)lParam)->code)
         {
            case UDN_DELTAPOS:
               bool bNext{ ((LPNMUPDOWN)lParam)->iDelta > 0 };

               switch (((LPNMHDR)lParam)->idFrom)
               {
                  case IDC_GOLINE_SPIN:
                     switchLine(bNext);
                     break;

                  case IDC_GOCOL_SPIN:
                     switchCol(bNext);
                     break;
               }
               break;
         }

         break;

      case WM_SETFOCUS:
         if (allPrefs.fillOnFocus)
            updatePanelColPos();
         break;

      default :
         return DockingDlgInterface::run_dlgProc(message, wParam, lParam);
   }

   return FALSE;
}

void GotoLineColPanel::initPanel() {
   LOGFONT logFont { 0 };

   bool recentOS = (::SendMessage(nppData._nppHandle, NPPM_GETWINDOWSVERSION, NULL, NULL) >= WV_VISTA);

   const long nFontSize = recentOS ? 10 : 8;
   const TCHAR* fontName = recentOS ? L"Consolas" : L"Courier New";

   HDC hdc = GetDC(_hSelf);

   logFont.lfHeight = -MulDiv(nFontSize, GetDeviceCaps(hdc, LOGPIXELSY), 72);
   wcscpy(logFont.lfFaceName, fontName);

   HFONT hMonospaceFont = CreateFontIndirect(&logFont);

   ReleaseDC(_hSelf, hdc);

   ::SendDlgItemMessage(_hSelf, IDC_GOLINECOL_FIELD_INFO, WM_SETFONT,
      (WPARAM)hMonospaceFont, MAKELPARAM(true, 0));

   if (_gLanguage != LANG_ENGLISH) localize();
}

void GotoLineColPanel::localize() {
   ::SetDlgItemText(_hSelf, IDC_GOLINE_STATIC, GOLINECOL_LABEL_GOLINE);
   ::SetDlgItemText(_hSelf, IDC_GOCOL_STATIC, GOLINECOL_LABEL_BYTE_COL);
   ::SetDlgItemText(_hSelf, IDOK, GOLINECOL_LABEL_BTN_GO);
   ::SetDlgItemText(_hSelf, IDCLOSE, GOLINECOL_LABEL_BTN_CLOSE);
   ::SetDlgItemText(_hSelf, IDC_GOLINECOL_PREFS, MENU_PREFERENCES);
   ::SetDlgItemText(_hSelf, IDC_GOLINECOL_FIELD_LABEL, GOLINECOL_FIELD_LABEL);
}

void GotoLineColPanel::display(bool toShow) {
   DockingDlgInterface::display(toShow);

   if (toShow) {
      ::SetFocus(::GetDlgItem(_hSelf, IDC_GOLINE_EDIT));
   }
};

void GotoLineColPanel::setParent(HWND parent2set) {
   _hParent = parent2set;
};

void GotoLineColPanel::loadPreferences() {
   HWND hScintilla{ getCurrentScintilla() };
   if (!hScintilla) return;

   allPrefs = _prefsIO.loadPreferences();

   ::SetDlgItemText(_hSelf, IDC_GOCOL_STATIC,
      allPrefs.useByteCol ? GOLINECOL_LABEL_BYTE_COL : GOLINECOL_LABEL_CHAR_COL);

   wchar_t numColumns[BUFFER_20];
   wchar_t colCountNote[BUFFER_100];

   int tabWidth{ allPrefs.useByteCol ? 1 : static_cast<int>(::SendMessage(hScintilla, SCI_GETTABWIDTH, 0, 0)) };
   if (tabWidth > 1)
      swprintf(numColumns, BUFFER_20, GOLINECOL_NUM_COLS, tabWidth);

   swprintf(colCountNote, BUFFER_100, GOLINECOL_TAB_CHAR_NOTE,
      (tabWidth == 1) ? GOLINECOL_SINGLE_COL : numColumns);
   ::SetDlgItemText(_hSelf, IDC_GOCOL_TAB_CHAR_NOTE, colCountNote);

   swprintf(colCountNote, BUFFER_100, GOLINECOL_UTF8_CHAR_NOTE,
       allPrefs.useByteCol ? GOLINECOL_MULTI_COLS : GOLINECOL_SINGLE_COL);
   ::SetDlgItemText(_hSelf, IDC_GOCOL_UTF8_CHAR_NOTE, colCountNote);
}

void GotoLineColPanel::updatePanelColPos() {
   HWND hScintilla{ getCurrentScintilla() };
   if (!hScintilla) return;

   int pos = static_cast<int>(::SendMessage(hScintilla, SCI_GETCURRENTPOS, 0, 0));
   int line = static_cast<int>(::SendMessage(hScintilla, SCI_LINEFROMPOSITION, pos, 0)) + 1;
   int col = getDocumentColumn(hScintilla, pos, line);

   ::SetDlgItemText(_hSelf, IDC_GOLINE_EDIT, TO_LPCWSTR(line));
   updateLineRangeText();

   ::SetDlgItemText(_hSelf, IDC_GOCOL_EDIT, TO_LPCWSTR(col));
   updateColumnRangeText(line);

   // Clear Idem Potent key if it's still set from a premature program termination
   idemPotentKey = FALSE;
}

void GotoLineColPanel::clearCalltip() {
   HWND hScintilla{ getCurrentScintilla() };
   if (!hScintilla) return;

   ::SendMessage(hScintilla, SCI_CALLTIPCANCEL, NULL, NULL);
}

/// *** Private Functions: *** ///

HWND GotoLineColPanel::getCurrentScintilla() {
   int which = -1;
   ::SendMessage(nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)& which);
   if (which < 0)
      return (HWND)FALSE;
   return (HWND)(which == 0) ? nppData._scintillaMainHandle : nppData._scintillaSecondHandle;
}

int GotoLineColPanel::getLineCount() {
   HWND hScintilla{ getCurrentScintilla() };
   if (!hScintilla) return -1;

   return static_cast<int>(::SendMessage(hScintilla, SCI_GETLINECOUNT, 0, 0));
};

int GotoLineColPanel::setFocusOnEditor() {
   HWND hScintilla{ getCurrentScintilla() };
   if (!hScintilla) return -1;

   return static_cast<int>(::SendMessage(hScintilla, SCI_GRABFOCUS, 0, 0));
};

int GotoLineColPanel::getLineMaxPos(int line) {
   HWND hScintilla{ getCurrentScintilla() };
   if (!hScintilla) return -1;

   int endPos = static_cast<int>(::SendMessage(hScintilla, SCI_GETLINEENDPOSITION, line - 1, 0));

   int col = (allPrefs.useByteCol) ?
      endPos - static_cast<int>(::SendMessage(hScintilla, SCI_POSITIONFROMLINE, line - 1, 0)) :
      static_cast<int>(::SendMessage(hScintilla, SCI_GETCOLUMN, endPos, 0));

   return col + 1;
};

int GotoLineColPanel::getDocumentColumn(HWND hScintilla, int pos, int line) {
   int col = (allPrefs.useByteCol) ?
      pos - static_cast<int>(::SendMessage(hScintilla, SCI_POSITIONFROMLINE, line - 1, 0)) :
      static_cast<int>(::SendMessage(hScintilla, SCI_GETCOLUMN, pos, 0));

   return col + 1;
}

int GotoLineColPanel::setDocumentColumn(HWND hScintilla, int line, int lineStartPos, int lineMaxPos, int column) {
   column = (column < 1) ? 1 :
            (column > lineMaxPos) ? lineMaxPos : column;

   int gotoPos = (allPrefs.useByteCol) ?
      lineStartPos + column - 1 :
      static_cast<int>(::SendMessage(hScintilla, SCI_FINDCOLUMN, line - 1, column - 1));

   ::SendMessage(hScintilla, SCI_GOTOPOS, gotoPos, 0);
   return gotoPos;
}

int GotoLineColPanel::getInputLineValidated() {
   BOOL isSuccessful;

   int line = ::GetDlgItemInt(_hSelf, IDC_GOLINE_EDIT, &isSuccessful, FALSE);
   if (!isSuccessful)
      return 1;

   int lineCount = getLineCount();
   return ((line < 0) ? 1 : ((line > lineCount) ? lineCount : line));
};

int GotoLineColPanel::getInputColumn() const {
   BOOL isSuccessful;

   int col = ::GetDlgItemInt(_hSelf, IDC_GOCOL_EDIT, &isSuccessful, FALSE);
   return (isSuccessful ? col : 1);
};

void GotoLineColPanel::updateLineRangeText() {
   ::SetDlgItemText(_hSelf, IDC_GOLINE_RANGE, (GOLINECOL_MAX_FOR_FILE + TO_WSTR(getLineCount()) + L"]").c_str());
}

void GotoLineColPanel::updateColumnRangeText(int line) {
   ::SetDlgItemText(_hSelf, IDC_GOCOL_RANGE, (GOLINECOL_MAX_FOR_LINE + TO_WSTR(getLineMaxPos(line)) + L"]").c_str());
}

void GotoLineColPanel::switchLine(bool bNext)
{
   int inputLine{ getInputLineValidated() };

   if (bNext) {
      if (inputLine + 1 > getLineCount()) {
         clearCalltip();
         return;
      }
      inputLine++;
   }
   else {
      if (inputLine == 1) {
         clearCalltip();
         return;
      }
      inputLine--;
   }

   ::SetDlgItemText(_hSelf, IDC_GOLINE_EDIT, TO_LPCWSTR(inputLine));
   updateColumnRangeText(inputLine);
   navigateToColPos();
}

void GotoLineColPanel::switchCol(bool bNext)
{
   int inputCol{ getInputColumn() };

   if (bNext) {
      if (inputCol + 1 > getLineMaxPos(getInputLineValidated())) {
         clearCalltip();
         return;
      }
      inputCol++;
   }
   else {
      if (inputCol == 1) {
         clearCalltip();
         return;
      }
      inputCol--;
   }

   ::SetDlgItemText(_hSelf, IDC_GOCOL_EDIT, TO_LPCWSTR(inputCol));
   navigateToColPos();
}

int GotoLineColPanel::navigateToColPos() {
   HWND hScintilla{ getCurrentScintilla() };
   if (!hScintilla) return FALSE;

   int line = getInputLineValidated();

   ::SendMessage(hScintilla, SCI_ENSUREVISIBLE, line - 1, 0);

   int lineMaxPos = getLineMaxPos(line);
   int lineStartPos = static_cast<int>(::SendMessage(hScintilla, SCI_POSITIONFROMLINE, line - 1, 0));

   int column = getInputColumn();

   if (allPrefs.centerCaret) {
      ::SendMessage(hScintilla, SCI_SETXCARETPOLICY, CARET_JUMPS | CARET_EVEN, (LPARAM)0);
      ::SendMessage(hScintilla, SCI_SETYCARETPOLICY, CARET_JUMPS | CARET_EVEN, (LPARAM)0);
   }
   else {
      // Clear a buffer of edgebuffer positions on either side if possible so that
      // the cursor is not stuck while being aligned with the side margins
      ::SendMessage(hScintilla, SCI_SETXCARETPOLICY, 0, (LPARAM)0);
      ::SendMessage(hScintilla, SCI_SETYCARETPOLICY, 0, (LPARAM)0);
      setDocumentColumn(hScintilla, line, lineStartPos, lineMaxPos, column - allPrefs.edgeBuffer);
      setDocumentColumn(hScintilla, line, lineStartPos, lineMaxPos, column + allPrefs.edgeBuffer);
   }

   int atPos = setDocumentColumn(hScintilla, line, lineStartPos, lineMaxPos, column);
   setFocusOnEditor();

   // Display call tip
   if (allPrefs.showCalltip) {
      // No need to call initCursorPosData() here.
      // cursorPosData will be populated in loadCursorPosData via SCN_UPDATEUI
      //initCursorPosData(hScintilla, line, (atPos - lineStartPos + 1), atPos);
      ::PostMessage(hScintilla, SCI_CALLTIPSHOW, atPos, (LPARAM)cursorPosData);
   }

   // Flash caret
   HANDLE hThread = ::CreateThread(NULL, 0, threadPositionHighlighter, 0, 0, NULL);
   if (hThread > 0)
      ::CloseHandle(hThread);

   return TRUE;
}

void GotoLineColPanel::initCursorPosData(HWND hScintilla, int line, int column, int atPos) {
   UCHAR atChar;
   int colPos;

   colPos = static_cast<int>(::SendMessage(hScintilla, SCI_GETCOLUMN, atPos, 0)) + 1;
   atChar = static_cast<UCHAR>(::SendMessage(hScintilla, SCI_GETCHARAT, atPos, 0));

   snprintf(cursorPosData, BUFFER_500,
      "       Line: %u\nChar Column: %u\nByte Column: %u\n\n  ANSI Byte: 0x%X [%u]",
      line, colPos, column, atChar, atChar);

   if ((atChar & 0x80) == 0 ||
      ::SendMessage(nppData._nppHandle, NPPM_GETBUFFERENCODING,
         ::SendMessage(nppData._nppHandle, NPPM_GETCURRENTBUFFERID, 0, 0), 0) == 0)
      return;

   int utf8StartPos{ atPos };
   UCHAR utf8StartChar{ atChar };

   while ((utf8StartChar & 0xC0) == 0x80 && atPos - utf8StartPos < 3) {
      utf8StartPos--;
      utf8StartChar = static_cast<UCHAR>(::SendMessage(hScintilla, SCI_GETCHARAT, utf8StartPos, 0));
   }

   if ((utf8StartChar & 0x40) == 0) {
      snprintf(cursorPosData, BUFFER_500, "%s\nInvalid UTF-8 Byte Sequence!", cursorPosData);
      return;
   }

   UCHAR utf8ByteChar;
   int utf8BytePos{ utf8StartPos };
   int unicodeHead{ 0 }, unicodeTail{ 0 };
   bool atMark;
   char utf8Text[BUFFER_100];

   atMark = (utf8StartPos == atPos);
   snprintf(utf8Text, BUFFER_100, "UTF-8 Bytes: %s0x%X%s",
      (atMark ? "<" : ""), utf8StartChar, (atMark ? ">" : ""));

   if ((utf8StartChar & 0xC0) == 0xC0) {
      atMark = (++utf8BytePos == atPos);
      utf8ByteChar = static_cast<UCHAR>(::SendMessage(hScintilla, SCI_GETCHARAT, utf8BytePos, 0));

      snprintf(utf8Text, BUFFER_100, "%s %s0x%X%s", utf8Text,
         (atMark ? "<" : ""), utf8ByteChar, (atMark ? ">" : ""));

      unicodeHead = (utf8StartChar & 31) << 6;
      unicodeTail = (utf8ByteChar & 63);
   }

   if ((utf8StartChar & 0xE0) == 0xE0) {
      atMark = (++utf8BytePos == atPos);
      utf8ByteChar = static_cast<UCHAR>(::SendMessage(hScintilla, SCI_GETCHARAT, utf8BytePos, 0));

      snprintf(utf8Text, BUFFER_100, "%s %s0x%X%s", utf8Text,
         (atMark ? "<" : ""), utf8ByteChar, (atMark ? ">" : ""));

      unicodeHead = (utf8StartChar & 15) << 12;
      unicodeTail = (unicodeTail << 6) + (utf8ByteChar & 63);
   }

   if ((utf8StartChar & 0xF0) == 0xF0) {
      atMark = (++utf8BytePos == atPos);
      utf8ByteChar = static_cast<UCHAR>(::SendMessage(hScintilla, SCI_GETCHARAT, utf8BytePos, 0));

      atMark = (utf8BytePos == atPos);
      snprintf(utf8Text, BUFFER_100, "%s %s0x%X%s", utf8Text,
         (atMark ? "<" : ""), utf8ByteChar, (atMark ? ">" : ""));

      unicodeHead = (utf8StartChar & 7) << 18;
      unicodeTail = (unicodeTail << 6) + (utf8ByteChar & 63);
   }

   if (atPos > utf8BytePos) {
      snprintf(cursorPosData, BUFFER_100, "%s\nInvalid UTF-8 Byte Sequence!", cursorPosData);
      return;
   }

   char unicodePoint[BUFFER_20];

   snprintf(unicodePoint, BUFFER_20, "%X", (unicodeHead + unicodeTail));
   snprintf(cursorPosData, BUFFER_500, "%s\n%s\n    Unicode: U+%s%s", cursorPosData,
      utf8Text, ((strlen(unicodePoint) % 2 == 0) ? "" : "0"), unicodePoint);
}

void GotoLineColPanel::loadCursorPosData() {
   HWND hScintilla{ getCurrentScintilla() };
   if (!hScintilla) return;

   int curPos = static_cast<int>(::SendMessage(hScintilla, SCI_GETCURRENTPOS, NULL, NULL));
   int curLine = static_cast<int>(::SendMessage(hScintilla, SCI_LINEFROMPOSITION, curPos, NULL));
   int lineStart = static_cast<int>(::SendMessage(hScintilla, SCI_POSITIONFROMLINE, curLine, NULL));

   initCursorPosData(hScintilla, (curLine + 1), (curPos - lineStart + 1), curPos);

   ::SetDlgItemTextA(_hSelf, IDC_GOLINECOL_FIELD_INFO, cursorPosData);
}

DWORD WINAPI GotoLineColPanel::threadPositionHighlighter(void*) {
   ALL_PREFERENCES allPrefs = _prefsIO.loadPreferences();

   // Get the current scintilla
   int which = -1;
   ::SendMessage(nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)& which);
   if (which == -1)
      return FALSE;

   HWND hScintilla = (which == 0) ? nppData._scintillaMainHandle : nppData._scintillaSecondHandle;

   // Look for Idem Potency Hold
   if (idemPotentKey)
      //  Idem Potency check failed. Another thread is processing this same function. Return immediately.
      return FALSE;
   else
      // OK to continue. Set Idem Potency Hold
      idemPotentKey = TRUE;

   // Modify caret style briefly to highlight the new position
   int currCaret = static_cast<int>(::SendMessage(hScintilla, SCI_GETCARETSTYLE, 0, 0));
   ::SendMessage(hScintilla, SCI_SETCARETSTYLE, CARETSTYLE_BLOCK, 0);
   Sleep(allPrefs.caretFlashSeconds * 1000);
   ::SendMessage(hScintilla, SCI_SETCARETSTYLE, currCaret, 0);

   if (allPrefs.braceHilite) {
      int pos = static_cast<int>(::SendMessage(hScintilla, SCI_GETCURRENTPOS, 0, 0));
      ::SendMessage(hScintilla, SCI_BRACEHIGHLIGHT, pos, -1);
   }

   // Clear Idem Potency Hold
   idemPotentKey = FALSE;

   return TRUE;
}
