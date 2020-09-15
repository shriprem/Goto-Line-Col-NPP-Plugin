#ifndef DIALOG_DEFS_H
#define DIALOG_DEFS_H


// Common
#define MENU_PANEL_NAME             L"Goto Line, Column"
#define MENU_SHOW_PANEL             L"&Show Panel"
#define MENU_PREFERENCES            L"&Preferences"
#define MENU_ABOUT                  L"&About"


// Goto Line, Column Panel
#define GOLINECOL_LABEL_GOLINE      L"Goto line:"
#define GOLINECOL_LABEL_BYTE_COL    L"Byte column:"
#define GOLINECOL_LABEL_CHAR_COL    L"Char column:"
#define GOLINECOL_LABEL_BTN_GO      L"&Go"
#define GOLINECOL_LABEL_BTN_CLOSE   L"&Close"

#define GOLINECOL_MAX_FOR_FILE      L"[Max for file: "
#define GOLINECOL_MAX_FOR_LINE      L"[Max for line: "
#define GOLINECOL_TAB_SINGLE_COL    L"Each TAB char will count as single column"
#define GOLINECOL_TAB_MULTI_COL     L"Each TAB char will count as "
#define GOLINECOL_TAB_COLUMNS       L" columns"
#define GOLINECOL_UTF8_SINGLE_COL   L"Each multibyte UTF-8 char will count as single column"
#define GOLINECOL_UTF8_MULTI_COL    L"Each multibyte UTF-8 char will count as multiple columns"
#define GOLINECOL_FIELD_LABEL       L"Cursor Position Data:"

#define CUR_POS_DATA_LINE           "       Line: "
#define CUR_POS_DATA_CHAR_COL       "Char Column: "
#define CUR_POS_DATA_BYTE_COL       "Byte Column: "
#define CUR_POS_DATA_ANSI_BYTE      "  ANSI Byte: "
#define CUR_POS_DATA_INVALID_UTF8   "Invalid UTF-8 Byte Sequence!"
#define CUR_POS_DATA_UTF8_BYTES     "UTF-8 Bytes: "
#define CUR_POS_DATA_UNICODE        "    Unicode: "


// Preferences Dialog
#define PREFS_DIALOG_TITLE          L"Preferences"
#define PREFS_LABEL_AF_ONFOCUS      L"Auto-fill on Panel Focus"
#define PREFS_LABEL_AF_ONTABCHANGE  L"Auto-fill on Document Tab Change"
#define PREFS_LABEL_SHOW_CALLTIP    L"Display character code at destination"
#define PREFS_LABEL_BRACE_HILITE    L"Highlight character at destination"
#define PREFS_LABEL_USE_BYTE_COL    L"Use byte count for column value computation"
#define PREFS_LABEL_CENTER_CARET    L"Cursor is centered in the editor at destination"
#define PREFS_LABEL_EDGE_BUFFER     L"Edge Buffer at destination:"
#define PREFS_LABEL_CARET_FLASH     L"Cursor Flash duration (in seconds)"

#define PREFS_BTN_LABEL_OK          L"&OK"
#define PREFS_BTN_LABEL_CANCEL      L"&Cancel"
#define PREFS_BTN_LABEL_DEFAULTS    L"&Defaults"
#define PREFS_LABEL_TOOLTIP_BOX     L"Tooltips (for this dialog only)"
#define PREFS_LABEL_TOOLTIP_SHOW    L"Show"
#define PREFS_LABEL_TOOLTIP_DUR     L"Duration (in seconds):"


// Preferences Dialog Tooltips
#define PREFS_TIP_MAX_WIDTH         400
#define PREFS_TIP_AF_ONFOCUS        L"When the Goto panel regains focus, the line and column fields in it will be refreshed with the current document's current cursor position.\r\n\r\nEffective only when the focus-changing click is on the panel's title bar or a blank area in the panel or the Preferences button. This refresh is suppressed when the focus-changing click is within the Goto Line/Column input fields or on the Go button.\r\n\r\nUncheck this option if your workflow needs the Goto panel's line and column values to stay fixed regardless of changes in the current document's cursor position."
#define PREFS_TIP_AF_ONTABCHANGE    L"When a different document becomes active either via a tab switch or file open or close actions, the line and column fields in the Goto panel will be refreshed with the newly active document's current cursor position.\r\n\r\nIn some situations -- when perhaps inspecting similar datafiles, it may be preferrable to have the line and column values stay fixed across the files. Uncheck this option for such workflows."
#define PREFS_TIP_SHOW_CALLTIP      L"Uncheck this option if you do not wish to view a calltip listing the line, column and byte code of the character at the destination position.\r\n\r\n[The calltip will disappear when the document cursor position shifts.]"
#define PREFS_TIP_BRACE_HILITE      L"Uncheck this option if you do not wish to have the character highlighted (after the cursor flash -- see its preference setting below).\r\n\r\n[The highlighting will disappear when the document cursor position shifts.]"
#define PREFS_TIP_USE_BYTE_COL      L"When this option is unchecked:\r\n\r\n1. A TAB character will be counted using its expanded width -- a number specified in Notepad++ Preferences/Language section. In fact, Notepad++ also expands TABs in its column computation.\r\n\r\n2. A multi-byte UTF-8 character will be counted as one column position.\r\n\r\nFor viewing files with fixed-width format data, leave this option checked."
#define PREFS_TIP_CENTER_CURSOR     L"When this option is checked, the cursor will try to position as close as possible to the center of the editor view area.\r\n\r\nIf the destination position is already within the prior view area, there will likely be no centering."
#define PREFS_TIP_EDGE_BUFFER       L"[Effective only when Centered Cursor option is unchecked]\r\n\r\nWhen the destination character shows up with the cursor stuck at either the left or right edge of the Notepad++ document view area, it will be hard to spot the cursor and the character. Hence, when possible, a buffer margin near the edges is desirable.\r\n\nSpecify the number of characters to have as a buffer margin from either of the edges for the character at the destination position."
#define PREFS_TIP_CARET_FLASH       L"When the cursor is set at its default width of '1', it can be hard to spot the cursor at its new position. To aid quick spotting, the cursor is briefly set to block mode at the destination position.\r\n\r\nSpecify the number of seconds to have the cursor flashing in block mode at the destination position."

#define PREFS_TIP_SHOW_TOOLTIPS     L"A change to this setting will be effective immediately for this Preference dialog session.\r\n\r\nThe setting will be saved for future sessions only when OK is clicked."
#define PREFS_TIP_TOOLTIP_DURATION  L"A change to this setting will be effective for this Preference dialog session only after tabbing out of the input field.\r\n\r\nThe setting will be saved for future sessions only when OK is clicked."


// About Dialog
#define ABOUT_DIALOG_TITLE          L"About"
#define ABOUT_PLUGIN_NAME           L"Goto Line, Column Plugin for Notepad++"

#endif
