#include "PreferencesDialog.h"

void PreferencesDialog::doDialog(HINSTANCE hInst) {
   if (!isCreated()) {
      Window::init(hInst, nppData._nppHandle);
      create(IDD_PREFERENCES_DIALOG);

      if (_prefsIO.allPrefs.language != LANG_ENGLISH)
         localize();
   }

   goToCenter();
   ::SendMessage(_hParent, NPPM_DMMSHOW, 0, (LPARAM)_hSelf);

   hEdgeBuffer = ::GetDlgItem(_hSelf, IDC_PREFS_EDGE_BUFFER_SLIDER);
   ::SendMessage(hEdgeBuffer, TBM_SETRANGEMIN, FALSE, 1);
   ::SendMessage(hEdgeBuffer, TBM_SETRANGEMAX, FALSE, 10);

   hCaretFlash = ::GetDlgItem(_hSelf, IDC_PREFS_CARET_FLASH_SLIDER);
   ::SendMessage(hCaretFlash, TBM_SETRANGEMIN, FALSE, 1);
   ::SendMessage(hCaretFlash, TBM_SETRANGEMAX, FALSE, 10);

   loadPreferences(true);

   if (getCheckedState(IDC_PREFS_TOOLTIP_SHOW)) {
      createTooltips();
      setTooltipsDuration(getEditValue(IDC_PREFS_TOOLTIP_DURATION));
   }
}

void PreferencesDialog::localize()
{
   ::SetWindowText(_hSelf, PREFS_DIALOG_TITLE);

   ::SetDlgItemText(_hSelf, IDC_PREFS_AF_ONFOCUS, PREFS_LABEL_AF_ONFOCUS);
   ::SetDlgItemText(_hSelf, IDC_PREFS_AF_ONTABCHANGE, PREFS_LABEL_AF_ONTABCHANGE);
   ::SetDlgItemText(_hSelf, IDC_PREFS_SHOW_CALLTIP, PREFS_LABEL_SHOW_CALLTIP);
   ::SetDlgItemText(_hSelf, IDC_PREFS_BRACE_HILITE, PREFS_LABEL_BRACE_HILITE);
   ::SetDlgItemText(_hSelf, IDC_PREFS_EXPAND_TABS, PREFS_LABEL_EXPAND_TABS);
   ::SetDlgItemText(_hSelf, IDC_PREFS_EDGE_BUFFER_LABEL, PREFS_LABEL_EDGE_BUFFER);
   ::SetDlgItemText(_hSelf, IDC_PREFS_CARET_FLASH_LABEL, PREFS_LABEL_CARET_FLASH);

   ::SetDlgItemText(_hSelf, IDOK, PREFS_BTN_LABEL_OK);
   ::SetDlgItemText(_hSelf, IDCANCEL, PREFS_BTN_LABEL_CANCEL);
   ::SetDlgItemText(_hSelf, IDC_PREFS_DEFAULTS, PREFS_BTN_LABEL_DEFAULTS);

   ::SetDlgItemText(_hSelf, IDC_PREFS_TOOLTIP_BOX, PREFS_LABEL_TOOLTIP_BOX);
   ::SetDlgItemText(_hSelf, IDC_PREFS_TOOLTIP_SHOW, PREFS_LABEL_TOOLTIP_SHOW);
   ::SetDlgItemText(_hSelf, IDC_PREFS_TOOLTIP_DUR_LABEL, PREFS_LABEL_TOOLTIP_DUR);
}

INT_PTR CALLBACK PreferencesDialog::run_dlgProc(UINT message, WPARAM wParam, LPARAM lParam) {
   switch (message) {
   case WM_COMMAND:
   {
      switch LOWORD(wParam) {
      case IDOK:
         savePreferences();
         display(FALSE);
         break;

      case IDCANCEL:
         display(FALSE);
         break;

      case IDC_PREFS_DEFAULTS:
         loadPreferences(false);
         break;

      case IDC_PREFS_CENTER_CARET:
      {
         BOOL enabled = !getCheckedState(IDC_PREFS_CENTER_CARET);
         enableControl(IDC_PREFS_EDGE_BUFFER_LABEL, enabled);
         enableControl(IDC_PREFS_EDGE_BUFFER_SLIDER, enabled);
         enableControl(IDC_PREFS_EDGE_BUFFER_VALUE, enabled);
         break;
      }

      case IDC_PREFS_TOOLTIP_SHOW:
         enableControl(IDC_PREFS_TOOLTIP_DURATION, getCheckedState(IDC_PREFS_TOOLTIP_SHOW));
         getCheckedState(IDC_PREFS_TOOLTIP_SHOW) ? createTooltips() : destroyTooltips();
         break;

      case IDC_PREFS_TOOLTIP_DURATION:
         if (HIWORD(wParam) == EN_KILLFOCUS)
            setTooltipsDuration(getEditValue(IDC_PREFS_TOOLTIP_DURATION));
         break;
      }

      return FALSE;
   }

   case WM_HSCROLL:
   {
      if (lParam == (LPARAM)hEdgeBuffer)
         syncTbarToText(hEdgeBuffer, IDC_PREFS_EDGE_BUFFER_VALUE);
      else if (lParam == (LPARAM)hCaretFlash)
         syncTbarToText(hCaretFlash, IDC_PREFS_CARET_FLASH_VALUE);

      return FALSE;
   }

   default:
      return 0;
   }
}

void PreferencesDialog::enableControl(int controlID, bool enabled) {
   ::EnableWindow(::GetDlgItem(_hSelf, controlID), enabled);
}

int PreferencesDialog::getCheckedState(int controlID) {
   return (::IsDlgButtonChecked(_hSelf, controlID) == BST_CHECKED);
}

void PreferencesDialog::setCheckedState(int controlID, int val) {
   ::CheckDlgButton(_hSelf, controlID, (val != FALSE) ? BST_CHECKED : BST_UNCHECKED);
}

int PreferencesDialog::getEditValue(int controlID) {
   int val = ::GetDlgItemInt(_hSelf, controlID, NULL, FALSE);
   return (val < 1) ? 1 : ((val > 20) ? 20 : val);
}

int PreferencesDialog::getTbarPosition(HWND hTBar) {
   return (int)::SendMessage(hTBar, TBM_GETPOS, 0, 0);
}

void PreferencesDialog::setTbarPosition(HWND hTBar, int controlID, int val) {
   ::SendMessage(hTBar, TBM_SETPOS, TRUE, val);
   syncTbarToText(hTBar, controlID, val);
}

void PreferencesDialog::syncTbarToText(HWND hCtrl, int controlID, int optVal) {
   ::SetDlgItemInt(_hSelf, controlID, (optVal ? optVal : getTbarPosition(hCtrl)), FALSE);
}

void PreferencesDialog::loadPreferences(bool iniFile) {
   ALL_PREFERENCES tPrefs = (iniFile) ? _prefsIO.loadPreferences() : _prefsIO.resetPreferences();

   setCheckedState(IDC_PREFS_AF_ONFOCUS, tPrefs.fillOnFocus);
   setCheckedState(IDC_PREFS_AF_ONTABCHANGE, tPrefs.fillOnTabChange);
   setCheckedState(IDC_PREFS_SHOW_CALLTIP, tPrefs.showCallTip);
   setCheckedState(IDC_PREFS_BRACE_HILITE, tPrefs.braceHilite);
   setCheckedState(IDC_PREFS_EXPAND_TABS, tPrefs.expandTabs);
   setCheckedState(IDC_PREFS_CENTER_CARET, tPrefs.centerCaret);

   enableControl(IDC_PREFS_EDGE_BUFFER_LABEL, !tPrefs.centerCaret);
   enableControl(IDC_PREFS_EDGE_BUFFER_SLIDER, !tPrefs.centerCaret);
   enableControl(IDC_PREFS_EDGE_BUFFER_VALUE, !tPrefs.centerCaret);

   setTbarPosition(hEdgeBuffer, IDC_PREFS_EDGE_BUFFER_VALUE, tPrefs.edgeBuffer);
   setTbarPosition(hCaretFlash, IDC_PREFS_CARET_FLASH_VALUE, tPrefs.caretFlashSeconds);

   setCheckedState(IDC_PREFS_TOOLTIP_SHOW, tPrefs.showTooltip);
   ::SetDlgItemInt(_hSelf, IDC_PREFS_TOOLTIP_DURATION, tPrefs.tooltipSeconds, FALSE);
}

void PreferencesDialog::savePreferences() {
   ALL_PREFERENCES tPrefs;

   tPrefs.fillOnFocus = getCheckedState(IDC_PREFS_AF_ONFOCUS);
   tPrefs.fillOnTabChange = getCheckedState(IDC_PREFS_AF_ONTABCHANGE);
   tPrefs.showCallTip = getCheckedState(IDC_PREFS_SHOW_CALLTIP);
   tPrefs.braceHilite = getCheckedState(IDC_PREFS_BRACE_HILITE);
   tPrefs.expandTabs = getCheckedState(IDC_PREFS_EXPAND_TABS);
   tPrefs.centerCaret = getCheckedState(IDC_PREFS_CENTER_CARET);

   tPrefs.edgeBuffer = getTbarPosition(hEdgeBuffer);
   tPrefs.caretFlashSeconds = getTbarPosition(hCaretFlash);

   tPrefs.showTooltip = getCheckedState(IDC_PREFS_TOOLTIP_SHOW);
   tPrefs.tooltipSeconds = getEditValue(IDC_PREFS_TOOLTIP_DURATION);

   _prefsIO.savePreferences(tPrefs);
   GotoLineColDlgLoadPreferences();
}

void PreferencesDialog::createTooltips() {
   if (!hTooltips[0])
      hTooltips[0] = createToolTip(_hSelf, IDC_PREFS_AF_ONFOCUS, PREFS_LABEL_AF_ONFOCUS, PREFS_TIP_AF_ONFOCUS);
   if (!hTooltips[1])
      hTooltips[1] = createToolTip(_hSelf, IDC_PREFS_AF_ONTABCHANGE, PREFS_LABEL_AF_ONTABCHANGE, PREFS_TIP_AF_ONTABCHANGE);
   if (!hTooltips[2])
      hTooltips[2] = createToolTip(_hSelf, IDC_PREFS_SHOW_CALLTIP, PREFS_LABEL_SHOW_CALLTIP, PREFS_TIP_SHOW_CALLTIP);
   if (!hTooltips[3])
      hTooltips[3] = createToolTip(_hSelf, IDC_PREFS_BRACE_HILITE, PREFS_LABEL_BRACE_HILITE, PREFS_TIP_BRACE_HILITE);
   if (!hTooltips[4])
      hTooltips[4] = createToolTip(_hSelf, IDC_PREFS_EXPAND_TABS, PREFS_LABEL_EXPAND_TABS, PREFS_TIP_EXPAND_TABS);
   if (!hTooltips[5])
      hTooltips[5] = createToolTip(_hSelf, IDC_PREFS_CENTER_CARET, PREFS_LABEL_CENTER_CARET, PREFS_TIP_CENTER_CURSOR);

   if (!hTooltips[6])
      hTooltips[6] = createToolTip(_hSelf, IDC_PREFS_EDGE_BUFFER_LABEL, PREFS_LABEL_EDGE_BUFFER, PREFS_TIP_EDGE_BUFFER);
   if (!hTooltips[7])
      hTooltips[7] = createToolTip(_hSelf, IDC_PREFS_EDGE_BUFFER_SLIDER, PREFS_LABEL_EDGE_BUFFER, PREFS_TIP_EDGE_BUFFER);
   if (!hTooltips[8])
      hTooltips[8] = createToolTip(_hSelf, IDC_PREFS_EDGE_BUFFER_VALUE, PREFS_LABEL_EDGE_BUFFER, PREFS_TIP_EDGE_BUFFER);

   if (!hTooltips[9])
      hTooltips[9] = createToolTip(_hSelf, IDC_PREFS_CARET_FLASH_LABEL, PREFS_LABEL_CARET_FLASH, PREFS_TIP_CARET_FLASH);
   if (!hTooltips[10])
      hTooltips[10] = createToolTip(_hSelf, IDC_PREFS_CARET_FLASH_SLIDER, PREFS_LABEL_CARET_FLASH, PREFS_TIP_CARET_FLASH);
   if (!hTooltips[11])
      hTooltips[11] = createToolTip(_hSelf, IDC_PREFS_CARET_FLASH_VALUE, PREFS_LABEL_CARET_FLASH, PREFS_TIP_CARET_FLASH);
}

void PreferencesDialog::setTooltipsDuration(int duration) {
   for (int i = 0; i < TOOLTIPS_COUNT; i++) {
      if (hTooltips[i])
         ::SendMessage(hTooltips[i], TTM_SETDELAYTIME, TTDT_AUTOPOP, (LPARAM)(duration * 1000));
   }
}

void PreferencesDialog::destroyTooltips() {
   for (int i = 0; i < TOOLTIPS_COUNT; i++) {
      if (hTooltips[i]) {
         ::DestroyWindow(hTooltips[i]);
         hTooltips[i] = (HWND)NULL;
      }
   }
}
