#include "GoToLineColPanel.h"
#include "PreferencesDialog.h"

extern NppData nppData;
extern PreferencesIO _prefsIO;
extern GotoLineColPanel _gotoPanel;

void PreferencesDialog::doDialog(HINSTANCE hInst) {
   if (!isCreated()) {
      Window::init(hInst, nppData._nppHandle);
      create(IDD_PREFERENCES_DIALOG);

      if (_gLanguage != LANG_ENGLISH) localize();
   }

   goToCenter();
   SendMessage(_hParent, NPPM_DMMSHOW, 0, (LPARAM)_hSelf);

   hEdgeBuffer = GetDlgItem(_hSelf, IDC_PREFS_EDGE_BUFFER_SLIDER);
   SendMessage(hEdgeBuffer, TBM_SETRANGEMIN, FALSE, 1);
   SendMessage(hEdgeBuffer, TBM_SETRANGEMAX, FALSE, 20);

   hCaretFlash = GetDlgItem(_hSelf, IDC_PREFS_CARET_FLASH_SLIDER);
   SendMessage(hCaretFlash, TBM_SETRANGEMIN, FALSE, 1);
   SendMessage(hCaretFlash, TBM_SETRANGEMAX, FALSE, 10);

   loadPreferences(true);

   addTooltip(_hSelf, IDC_PREFS_TOOLTIP_SHOW, L"", PREFS_TIP_SHOW_TOOLTIPS);
   addTooltip(_hSelf, IDC_PREFS_TOOLTIP_DUR_LABEL, L"", PREFS_TIP_TOOLTIP_DURATION);
   addTooltip(_hSelf, IDC_PREFS_TOOLTIP_DURATION, L"", PREFS_TIP_TOOLTIP_DURATION);
}

void PreferencesDialog::refreshDarkMode() {
   NPPDM_AutoSubclassAndThemeChildControls(_hSelf);

   SendMessage(hEdgeBuffer, TBM_SETRANGEMIN, FALSE, 1);
   SendMessage(hCaretFlash, TBM_SETRANGEMIN, FALSE, 1);
}

void PreferencesDialog::localize() {
   SetWindowText(_hSelf, PREFS_DIALOG_TITLE);

   SetDlgItemText(_hSelf, IDC_PREFS_AF_ONFOCUS, PREFS_LABEL_AF_ONFOCUS);
   SetDlgItemText(_hSelf, IDC_PREFS_AF_ONTABCHANGE, PREFS_LABEL_AF_ONTABCHANGE);
   SetDlgItemText(_hSelf, IDC_PREFS_SHOW_CALLTIP, PREFS_LABEL_SHOW_CALLTIP);
   SetDlgItemText(_hSelf, IDC_PREFS_BRACE_HILITE, PREFS_LABEL_BRACE_HILITE);
   SetDlgItemText(_hSelf, IDC_PREFS_USE_BYTE_COL, PREFS_LABEL_USE_BYTE_COL);
   SetDlgItemText(_hSelf, IDC_PREFS_EDGE_BUFFER_LABEL, PREFS_LABEL_EDGE_BUFFER);
   SetDlgItemText(_hSelf, IDC_PREFS_CARET_FLASH_LABEL, PREFS_LABEL_CARET_FLASH);

   SetDlgItemText(_hSelf, IDOK, PREFS_BTN_LABEL_OK);
   SetDlgItemText(_hSelf, IDCANCEL, PREFS_BTN_LABEL_CANCEL);
   SetDlgItemText(_hSelf, IDC_PREFS_DEFAULTS, PREFS_BTN_LABEL_DEFAULTS);

   SetDlgItemText(_hSelf, IDC_PREFS_TOOLTIP_BOX, PREFS_LABEL_TOOLTIP_BOX);
   SetDlgItemText(_hSelf, IDC_PREFS_TOOLTIP_SHOW, PREFS_LABEL_TOOLTIP_SHOW);
   SetDlgItemText(_hSelf, IDC_PREFS_TOOLTIP_DUR_LABEL, PREFS_LABEL_TOOLTIP_DUR);
}

INT_PTR CALLBACK PreferencesDialog::run_dlgProc(UINT message, WPARAM wParam, LPARAM lParam) {
   switch (message) {
   case WM_COMMAND:
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
         BOOL bCenterCaret{ !getCheckedState(IDC_PREFS_CENTER_CARET) };
         redrawControl(IDC_PREFS_EDGE_BUFFER_LABEL);
         enableControl(IDC_PREFS_EDGE_BUFFER_SLIDER, bCenterCaret);
         enableControl(IDC_PREFS_EDGE_BUFFER_VALUE, bCenterCaret);
         break;
      }

      case IDC_PREFS_TOOLTIP_SHOW:
      {
         BOOL bShowTooltip{ getCheckedState(IDC_PREFS_TOOLTIP_SHOW) };
         redrawControl(IDC_PREFS_TOOLTIP_DUR_LABEL);
         enableControl(IDC_PREFS_TOOLTIP_DURATION, bShowTooltip);
         bShowTooltip ? createTooltips() : destroyTooltips();
         break;
      }

      case IDC_PREFS_TOOLTIP_DURATION:
         if (HIWORD(wParam) == EN_KILLFOCUS)
            setTooltipsDuration(getEditValue(IDC_PREFS_TOOLTIP_DURATION));
         break;
      }

      break;

   case WM_HSCROLL:
      if (lParam == (LPARAM)hEdgeBuffer)
         syncTbarToText(hEdgeBuffer, IDC_PREFS_EDGE_BUFFER_VALUE);
      else if (lParam == (LPARAM)hCaretFlash)
         syncTbarToText(hCaretFlash, IDC_PREFS_CARET_FLASH_VALUE);

      break;

   case WM_INITDIALOG:
      NPPDM_AutoSubclassAndThemeChildControls(_hSelf);
      break;

   case WM_CTLCOLORDLG:
   case WM_CTLCOLORLISTBOX:
      if (NPPDM_IsEnabled()) {
         return NPPDM_OnCtlColorDarker(reinterpret_cast<HDC>(wParam));
      }
      break;

   case WM_CTLCOLORSTATIC:
      switch (GetDlgCtrlID((HWND)lParam)) {
      case IDC_PREFS_EDGE_BUFFER_LABEL:
         return NPPDM_OnCtlColorIfEnabled(reinterpret_cast<HDC>(wParam), !getCheckedState(IDC_PREFS_CENTER_CARET));

      case IDC_PREFS_TOOLTIP_DUR_LABEL:
         return NPPDM_OnCtlColorIfEnabled(reinterpret_cast<HDC>(wParam), getCheckedState(IDC_PREFS_TOOLTIP_SHOW));

      default:
         if (NPPDM_IsEnabled()) {
            return NPPDM_OnCtlColorDarker(reinterpret_cast<HDC>(wParam));
         }
      }
      break;

   case WM_CTLCOLOREDIT:
      if (NPPDM_IsEnabled()) {
         return NPPDM_OnCtlColorSofter(reinterpret_cast<HDC>(wParam));
      }
      break;

   case WM_PRINTCLIENT:
      if (NPPDM_IsEnabled()) return TRUE;
      break;
   }

   return FALSE;
}

void PreferencesDialog::enableControl(int controlID, bool enabled) {
   EnableWindow(GetDlgItem(_hSelf, controlID), enabled);
}

void PreferencesDialog::redrawControl(int controlID) {
   InvalidateRect(GetDlgItem(_hSelf, controlID), NULL, TRUE);
}

bool PreferencesDialog::getCheckedState(int controlID) {
   return (IsDlgButtonChecked(_hSelf, controlID) == BST_CHECKED);
}

void PreferencesDialog::setCheckedState(int controlID, int val) {
   CheckDlgButton(_hSelf, controlID, (val != FALSE) ? BST_CHECKED : BST_UNCHECKED);
}

int PreferencesDialog::getEditValue(int controlID) {
   int val = GetDlgItemInt(_hSelf, controlID, NULL, FALSE);
   return (val < 1) ? 1 : ((val > 60) ? 60 : val);
}

int PreferencesDialog::getTbarPosition(HWND hTBar) {
   return static_cast<int>(SendMessage(hTBar, TBM_GETPOS, 0, 0));
}

void PreferencesDialog::setTbarPosition(HWND hTBar, int controlID, int val) {
   SendMessage(hTBar, TBM_SETPOS, TRUE, val);
   syncTbarToText(hTBar, controlID, val);
}

void PreferencesDialog::syncTbarToText(HWND hCtrl, int controlID, int optVal) {
   SetDlgItemInt(_hSelf, controlID, (optVal ? optVal : getTbarPosition(hCtrl)), FALSE);
}

void PreferencesDialog::loadPreferences(bool iniFile) {
   ALL_PREFERENCES tPrefs = (iniFile) ? _prefsIO.loadPreferences() : _prefsIO.resetPreferences();

   setCheckedState(IDC_PREFS_AF_ONFOCUS, tPrefs.fillOnFocus);
   setCheckedState(IDC_PREFS_AF_ONTABCHANGE, tPrefs.fillOnTabChange);
   setCheckedState(IDC_PREFS_SHOW_CALLTIP, tPrefs.showCalltip);
   setCheckedState(IDC_PREFS_BRACE_HILITE, tPrefs.braceHilite);
   setCheckedState(IDC_PREFS_USE_BYTE_COL, tPrefs.useByteCol);
   setCheckedState(IDC_PREFS_CENTER_CARET, tPrefs.centerCaret);

   setTbarPosition(hEdgeBuffer, IDC_PREFS_EDGE_BUFFER_VALUE, tPrefs.edgeBuffer);
   setTbarPosition(hCaretFlash, IDC_PREFS_CARET_FLASH_VALUE, tPrefs.caretFlashSeconds);

   setCheckedState(IDC_PREFS_TOOLTIP_SHOW, tPrefs.showTooltip);
   SetDlgItemInt(_hSelf, IDC_PREFS_TOOLTIP_DURATION, tPrefs.tooltipSeconds, FALSE);

   redrawControl(IDC_PREFS_EDGE_BUFFER_LABEL);
   enableControl(IDC_PREFS_EDGE_BUFFER_SLIDER, !tPrefs.centerCaret);
   enableControl(IDC_PREFS_EDGE_BUFFER_VALUE, !tPrefs.centerCaret);
   redrawControl(IDC_PREFS_TOOLTIP_DUR_LABEL);
   enableControl(IDC_PREFS_TOOLTIP_DURATION, tPrefs.showTooltip);

   if (tPrefs.showTooltip) {
      createTooltips();
      setTooltipsDuration(tPrefs.tooltipSeconds);
   }
}

void PreferencesDialog::savePreferences() {
   // First, fill in stored/default values for non-GUI keys like CmdProc***
   ALL_PREFERENCES tPrefs{ _prefsIO.loadPreferences() };

   tPrefs.fillOnFocus = getCheckedState(IDC_PREFS_AF_ONFOCUS);
   tPrefs.fillOnTabChange = getCheckedState(IDC_PREFS_AF_ONTABCHANGE);
   tPrefs.showCalltip = getCheckedState(IDC_PREFS_SHOW_CALLTIP);
   tPrefs.braceHilite = getCheckedState(IDC_PREFS_BRACE_HILITE);
   tPrefs.useByteCol = getCheckedState(IDC_PREFS_USE_BYTE_COL);
   tPrefs.centerCaret = getCheckedState(IDC_PREFS_CENTER_CARET);

   tPrefs.edgeBuffer = getTbarPosition(hEdgeBuffer);
   tPrefs.caretFlashSeconds = getTbarPosition(hCaretFlash);

   tPrefs.showTooltip = getCheckedState(IDC_PREFS_TOOLTIP_SHOW);
   tPrefs.tooltipSeconds = getEditValue(IDC_PREFS_TOOLTIP_DURATION);

   _prefsIO.savePreferences(tPrefs);
   _gotoPanel.loadPreferencesToPanel(TRUE);
}

void PreferencesDialog::createTooltips() {
   if (!hTooltips[0])
      hTooltips[0] = addTooltip(_hSelf, IDC_PREFS_AF_ONFOCUS, PREFS_LABEL_AF_ONFOCUS, PREFS_TIP_AF_ONFOCUS);
   if (!hTooltips[1])
      hTooltips[1] = addTooltip(_hSelf, IDC_PREFS_AF_ONTABCHANGE, PREFS_LABEL_AF_ONTABCHANGE, PREFS_TIP_AF_ONTABCHANGE);
   if (!hTooltips[2])
      hTooltips[2] = addTooltip(_hSelf, IDC_PREFS_SHOW_CALLTIP, PREFS_LABEL_SHOW_CALLTIP, PREFS_TIP_SHOW_CALLTIP);
   if (!hTooltips[3])
      hTooltips[3] = addTooltip(_hSelf, IDC_PREFS_BRACE_HILITE, PREFS_LABEL_BRACE_HILITE, PREFS_TIP_BRACE_HILITE);
   if (!hTooltips[4])
      hTooltips[4] = addTooltip(_hSelf, IDC_PREFS_USE_BYTE_COL, PREFS_LABEL_USE_BYTE_COL, PREFS_TIP_USE_BYTE_COL);
   if (!hTooltips[5])
      hTooltips[5] = addTooltip(_hSelf, IDC_PREFS_CENTER_CARET, PREFS_LABEL_CENTER_CARET, PREFS_TIP_CENTER_CURSOR);

   if (!hTooltips[6])
      hTooltips[6] = addTooltip(_hSelf, IDC_PREFS_EDGE_BUFFER_LABEL, PREFS_LABEL_EDGE_BUFFER, PREFS_TIP_EDGE_BUFFER);
   if (!hTooltips[7])
      hTooltips[7] = addTooltip(_hSelf, IDC_PREFS_EDGE_BUFFER_SLIDER, PREFS_LABEL_EDGE_BUFFER, PREFS_TIP_EDGE_BUFFER);
   if (!hTooltips[8])
      hTooltips[8] = addTooltip(_hSelf, IDC_PREFS_EDGE_BUFFER_VALUE, PREFS_LABEL_EDGE_BUFFER, PREFS_TIP_EDGE_BUFFER);

   if (!hTooltips[9])
      hTooltips[9] = addTooltip(_hSelf, IDC_PREFS_CARET_FLASH_LABEL, PREFS_LABEL_CARET_FLASH, PREFS_TIP_CARET_FLASH);
   if (!hTooltips[10])
      hTooltips[10] = addTooltip(_hSelf, IDC_PREFS_CARET_FLASH_SLIDER, PREFS_LABEL_CARET_FLASH, PREFS_TIP_CARET_FLASH);
   if (!hTooltips[11])
      hTooltips[11] = addTooltip(_hSelf, IDC_PREFS_CARET_FLASH_VALUE, PREFS_LABEL_CARET_FLASH, PREFS_TIP_CARET_FLASH);
}

void PreferencesDialog::setTooltipsDuration(int duration) {
   for (int i = 0; i < TOOLTIPS_COUNT; i++) {
      if (hTooltips[i])
         SendMessage(hTooltips[i], TTM_SETDELAYTIME, TTDT_AUTOPOP, (LPARAM)(duration * 1000));
   }
}

void PreferencesDialog::destroyTooltips() {
   for (int i = 0; i < TOOLTIPS_COUNT; i++) {
      if (hTooltips[i]) {
         DestroyWindow(hTooltips[i]);
         hTooltips[i] = (HWND)NULL;
      }
   }
}
