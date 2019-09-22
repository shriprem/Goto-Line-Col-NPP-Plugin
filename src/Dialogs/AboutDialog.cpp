#include "AboutDialog.h"

void AboutDialog::doDialog(HINSTANCE hInst)
{
   if (!isCreated()) {
      Window::init(hInst, nppData._nppHandle);
      create(IDD_ABOUT_DIALOG);
   }

   ::SetDlgItemText(_hSelf, IDC_ABOUT_NAME, PLUGIN_NAME);
   ::SetDlgItemText(_hSelf, IDC_ABOUT_VERSION, PLUGIN_VERSION);
   ::SetDlgItemText(_hSelf, IDC_ABOUT_ATTRIBUTION, PLUGIN_ATTRIBUTION);

   goToCenter();
   ::SendMessage(_hParent, NPPM_DMMSHOW, 0, (LPARAM)_hSelf);
}

INT_PTR CALLBACK AboutDialog::run_dlgProc(UINT message, WPARAM wParam, LPARAM lParam)
{
   switch (message)
   {
      case WM_COMMAND:
      {
         switch LOWORD(wParam)
         {
         case IDCLOSE:
         case IDCANCEL:
            display(FALSE);
            return TRUE;
         }
         return FALSE;
      }

      case WM_NOTIFY:
      {
         switch (((LPNMHDR)lParam)->code)
         {
         case NM_CLICK:
         case NM_RETURN:
            ::ShellExecute(NULL, L"open", PLUGIN_GITHUB_PAGE, NULL, NULL, SW_SHOW);
            display(FALSE);
            return TRUE;
         }
         return FALSE;
      }

      default:
         return FALSE;
      }
}
