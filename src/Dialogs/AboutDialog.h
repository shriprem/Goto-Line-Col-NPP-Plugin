#ifndef _ABOUTDIALOG_H
#define _ABOUTDIALOG_H

#include "../PluginDefinition.h"
#include "../NPP/StaticDialog.h"

extern NppData nppData;

class AboutDialog : public StaticDialog
{
public:
   AboutDialog() : StaticDialog() {};
   void doDialog(HINSTANCE hInst);

protected:
   INT_PTR CALLBACK run_dlgProc(UINT Message, WPARAM wParam, LPARAM lParam);

};

#endif // _ABOUTDIALOG_H
