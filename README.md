# GotoLineCol Notepad++ Plugin

![GitHub](https://img.shields.io/github/license/shriprem/Goto-Line-Col-NPP-Plugin)
![GitHub release (latest by date)](https://img.shields.io/github/v/release/shriprem/Goto-Line-Col-NPP-Plugin)
![GitHub all releases](https://img.shields.io/github/downloads/shriprem/Goto-Line-Col-NPP-Plugin/total)
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
![GitHub last commit (by committer)](https://img.shields.io/github/last-commit/shriprem/Goto-Line-Col-NPP-Plugin)
![GitHub Workflow Status (with event)](https://img.shields.io/github/actions/workflow/status/shriprem/Goto-Line-Col-NPP-Plugin/CI_build.yml)
![GitHub issues](https://img.shields.io/github/issues/shriprem/Goto-Line-Col-NPP-Plugin)

[Current Version: 2.4.3.0](https://github.com/shriprem/Goto-Line-Col-NPP-Plugin/blob/master/VersionHistory.md)

A plugin for navigating to a specified line and column position in a file. Depending on your requirement, the column positioning can be specified to use either byte counts or character counts.

It is also handy for quickly inspecting byte-level content in files. The plugin will display the byte value at the document's current cursor position. In addition, for multi-byte-based characters in documents with Unicode-based encoding, the plugin will display the Unicode code point and its corresponding UTF-8 byte sequence (see: [Display character code at destination](https://github.com/shriprem/Goto-Line-Col-NPP-Plugin/blob/master/docs/PreferencesDialog.md#display-character-code-at-destination-checked)).


## Plugin Panel

### Byte-based columns
![GotoLineCol Panel](https://raw.githubusercontent.com/shriprem/Goto-Line-Col-NPP-Plugin/master/images/PanelBytePos.png)

With the **_"Use byte count for column value computation"_** box checked:

* A TAB character will count as a single column.

* Each multi-byte UTF-8 character will be count as multiple columns.

For viewing files with fixed-width format data, use byte count for column value computation.

### Character-based columns
![GotoLineCol Panel](https://raw.githubusercontent.com/shriprem/Goto-Line-Col-NPP-Plugin/master/images/PanelCharPos.png)


With the **_Use byte count for column value computation_** unchecked:

* A TAB character on the destination line will be counted using its expanded width -- a number specified in Notepad++ Preferences/Language section. In fact, Notepad++ also expands TABs in its column computation.

* A multi-byte UTF-8 character will be counted as one column position when this option is unchecked.

### Spin controls:
The spin controls on the line and column fields provide quick navigation between adjacent lines or characters. The spin controls can be especially useful when inspecting character byte values (see: [Display character code at destination](https://github.com/shriprem/Goto-Line-Col-NPP-Plugin/blob/master/docs/PreferencesDialog.md#display-character-code-at-destination-checked)).

[*Since the line numbers increase downwards in a document, the spin control's down arrow increments the line or column number; and the up arrow decrements the line or column number. This orientation is a reversal of the typical spin control behavior in Windows; but it aligns with the document layout.*]

---

### See also:
1. [Preferences Dialog](https://github.com/shriprem/Goto-Line-Col-NPP-Plugin/blob/master/docs/PreferencesDialog.md)

2. [Command Line Options](https://github.com/shriprem/Goto-Line-Col-NPP-Plugin/blob/master/docs/CommandLineOptions.md)

3. [Dark Mode Rendering](https://github.com/shriprem/Goto-Line-Col-NPP-Plugin/blob/master/docs/DarkModeUI.md)

4. <a href="https://github.com/shriprem/Goto-Line-Col-NPP-Plugin/blob/master/docs/FAQs.md">Frequently Asked Questions</a>

5. <a href="https://github.com/shriprem/Goto-Line-Col-NPP-Plugin/blob/master/VersionHistory.md">Version History</a>

