#ifndef _PREFERENCESDIALOG_H
#define _PREFERENCESDIALOG_H

#include "../PluginDefinition.h"
#include "../NPP/StaticDialog.h"

extern NppData nppData;
extern PreferencesIO _prefsIO;

class PreferencesDialog : public StaticDialog
{
public:
   PreferencesDialog() : StaticDialog() {};
   void doDialog(HINSTANCE hInst);

protected:
   HWND hEdgeBuffer, hCaretFlash, hTooltips[11];

   INT_PTR CALLBACK run_dlgProc(UINT Message, WPARAM wParam, LPARAM lParam);

   int getCheckedState(int controlID);
   void setCheckedState(int controlID, int val);
   int getEditValue(int controlID);
   int getTbarPosition(HWND hTBar);
   void setTbarPosition(HWND hTBar, int controlID, int val);
   void syncTbarToText(HWND hTBar, int controlID, int optVal=FALSE);

   void loadPreferences(bool iniFile);
   void savePreferences();

   void createTooltips();
   void setTooltipsDuration(int duration);
   void destroyTooltips();
};

#endif // _PREFERENCESDIALOG_H
