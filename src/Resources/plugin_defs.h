#ifndef PLUGIN_INFO_H
#define PLUGIN_INFO_H

#define PLUGIN_NAME           L"Goto Line, Column Plugin for Notepad++"
#define PLUGIN_VERSION        L"Version 1.0"
#define PLUGIN_ATTRIBUTION    L"(c) 2019, Shridhar Kumar"
#define PLUGIN_GITHUB_PAGE    L"https://github.com/shriprem/GotoLineCol-NPP-PythonScript"

#define PREFS_TIP_MAX_WIDTH         400
#define PREFS_TIP_AUTO_POP_SHORT 10000

#define PREFS_LABEL_AF_ONFOCUS      L"Auto-fill on Panel Focus"
#define PREFS_LABEL_AF_ONTABCHANGE  L"Auto-fill on Document Tab Change"
#define PREFS_LABEL_SHOW_CALLTIP L"Display character code at destination"
#define PREFS_LABEL_BRACE_HILITE L"Highlight character at destination"
#define PREFS_LABEL_EXPAND_TABS     L"Expand TABS for column value computation"
#define PREFS_LABEL_EDGE_BUFFER     L"Edge Buffer at destination"
#define PREFS_LABEL_CARET_FLASH     L"Cursor Flash duration (in seconds)"

#define PREFS_TIP_AF_ONFOCUS     L"Uncheck this box if your workflow needs the Goto panel's line and column values to stay fixed regardless of the changes in current document's cursor position."
#define PREFS_TIP_AF_ONTABCHANGE L"Uncheck this box if your workflow needs the Goto panel's line and column values to stay fixed between tab switches in Notepad++ to a different document."
#define PREFS_TIP_SHOW_CALLTIP      L"Uncheck this box if you do not wish to view, within a calltip, the hex code of the character at the destination position.\r\n\r\n[The calltip will disappear when the cursor is manually moved to a different line in the document.]"
#define PREFS_TIP_BRACE_HILITE      L"Uncheck this box if you do not wish to have the character highlighted (after the cursor flash -- see below)at the destination position.\r\n\r\n[The highlighting will disappear when the cursor is manually moved inside the document.]"
#define PREFS_TIP_EXPAND_TABS    L"When this box is checked, all TAB characters on the destination line will be counted using their expanded width -- a number specified in Notepad++ Preferences/Language section. In fact, Notepad++ also expands TABS in its column computation.\r\n\r\nHowever, if you are viewing files with fixed-width fields, you may want to leave this box unchecked."
#define PREFS_TIP_EDGE_BUFFER    L"When the destination character shows up with the cursor stuck at either the left or right edge of the Notepad++ document view area, it will be hard to spot the cursor and the character. Hence a buffer near the edges, when possible, is desirable.\r\n\nSpecify the number of characters to have as a buffer from either of the edges for the character at the destination position."
#define PREFS_TIP_CARET_FLASH    L"When the cursor is set at its default width of '1', it can be hard to spot the cursor at its new position. To aid quick spotting, the cursor is briefly set to block mode at the destination position.\r\n\r\nSpecify the number of seconds to have the cursor flashing in block mode at the destination position."
#endif
