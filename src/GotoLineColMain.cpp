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

#include "PluginDefinition.h"
#include "Dialogs/GoToLineColPanel.h"
#include "Darkmode/NPP_Plugin_Darkmode.h"

extern FuncItem pluginMenuItems[MI_COUNT];
extern NppData nppData;

extern GotoLineColPanel _gotoPanel;

BOOL APIENTRY DllMain(HANDLE hModule, DWORD  reasonForCall, LPVOID /*lpReserved*/) {
    switch (reasonForCall) {
      case DLL_PROCESS_ATTACH:
        pluginInit(hModule);
        break;

      case DLL_PROCESS_DETACH:
        pluginCleanUp();
        break;

      case DLL_THREAD_ATTACH:
        break;

      case DLL_THREAD_DETACH:
        break;
    }

    return TRUE;
}


extern "C" __declspec(dllexport) void setInfo(NppData notpadPlusData)
{
   nppData = notpadPlusData;
   commandMenuInit();
}

extern "C" __declspec(dllexport) const TCHAR * getName()
{
   return MENU_PANEL_NAME;
}

extern "C" __declspec(dllexport) FuncItem * getFuncsArray(int *nbF)
{
   *nbF = MI_COUNT;
   return pluginMenuItems;
}


extern "C" __declspec(dllexport) void beNotified(SCNotification *notifyCode) {
   switch (notifyCode->nmhdr.code) {
      case NPPN_BUFFERACTIVATED:
         _gotoPanel.onBufferActivated();
         break;

      case NPPN_TBMODIFICATION:
         Utils::addToolbarIcon(MI_GOTO_PANEL, IDB_GOTO_TOOL_BTN_STD,
            IDI_GOTO_TOOL_BTN_FLUENT, IDI_GOTO_TOOL_BTN_DARK);
         break;

      case NPPN_DARKMODECHANGED:
         NPPDM_QueryNPPDarkmode();
         refreshDarkMode();
         break;

      case SCN_UPDATEUI:
         _gotoPanel.clearCalltip();
         _gotoPanel.loadCursorPosData();
         break;

      case NPPN_SHUTDOWN:
         commandMenuCleanUp();
         break;

      default:
         return;
   }
}


extern "C" __declspec(dllexport) LRESULT messageProc(UINT /*Message*/, WPARAM /*wParam*/, LPARAM /*lParam*/)
{
   return TRUE;
}

#ifdef UNICODE
extern "C" __declspec(dllexport) BOOL isUnicode()
{
    return TRUE;
}
#endif //UNICODE
