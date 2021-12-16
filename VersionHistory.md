## Version History

### Version 2.2.0.0

1. Darkmode for the _GoToLineCol_ plugin is now rendered by a standalone DLL that can be shared by multiple plugins, thus reducing the overall memory footprint. Notepad++ will only load a copy of the `NPP_Plugin_Darkmode.dll` located either in:
   * The folder for the first plugin (_in alphabetical order_) that requires this DLL.
   * Or, in the common `<NPP_executable_folder>`.

   You can verify the singleton loading of the `NPP_Plugin_Darkmode.dll` using the [Process Explorer](https://docs.microsoft.com/en-us/sysinternals/downloads/process-explorer) utility.

**Plugin Developers**: For more information on using `NPP_Plugin_Darkmode.dll` in your plugins, please refer to the documentation at the [NPP_Plugin_Darkmode](https://github.com/shriprem/NPP_Plugin_Darkmode) repository.

**Release:** [2.2.0.0 Release](https://github.com/shriprem/Goto-Line-Col-NPP-Plugin/releases/tag/v2.2.0.0)

---

### Version 2.1.1.0
#### Enhancement: Consolidated GLC command line options.
 Sample GLC option usage in this version: **` -z -GLCb1;c0;d1;e18;f1;h1;p1;q1`**

Equivalent usage in version 2.1.0.0 was:
```
-z -GLCb1 -z -GLCc0 -z -GLCd1 -z -GLCe18  -z -GLCf1 -z -GLCh1 -z -GLCp1 -z -GLCq1
```
[*Although the kludgy syntax of v2.1.0.0 may still work in v2.1.1.0 and later versions, prefer to use the compact syntax.*]

See: [Command Line Options](https://github.com/shriprem/Goto-Line-Col-NPP-Plugin/blob/master/docs/CommandLineOptions.md)

**Release:** [2.1.1.0 Release](https://github.com/shriprem/Goto-Line-Col-NPP-Plugin/releases/tag/v2.1.1.0)

---

### Version 2.1.0.0
#### Enhancements:
1. Command Line Option to load multiple documents and position them all at the same line and character/byte column.

See: [Command Line Options](https://github.com/shriprem/Goto-Line-Col-NPP-Plugin/blob/master/docs/CommandLineOptions.md)

**Release:** [2.1.0.0 Release](https://github.com/shriprem/Goto-Line-Col-NPP-Plugin/releases/tag/v2.1.0.0)

---

### Version 2.0.0.0
#### Enhancements:
1. Darkmode rendering enabled for the plugin panel and dialog boxes.

#### `NOTE`
Notepad++ user configuration settings are saved into the config.xml file by Notepad++ only during the application closing event. The GotoLineCol plugin is only able to read these settings changes in the config.xml file during the next launch of Notepad++.

So, when Darkmode settings are changed, Notepad++ will need to be restarted for the plugin to reflect these settings changes.

See: [Sample screenshots of the plugin UI in dark mode.](https://github.com/shriprem/Goto-Line-Col-NPP-Plugin/blob/master/docs/DarkModeUI.md)

**Release:** [2.0.0.0 Release](https://github.com/shriprem/Goto-Line-Col-NPP-Plugin/releases/tag/v2.0.0.0)

---

### Version 1.2.0.2
#### Enhancements:
1. Light & Dark mode Fluent UI toolbar icons added for the plugin.
2. Including ARM64 build. (_Please note that I am unable to test the ARM64 build since I don't have an ARM64 device, and it is being provided AS IS._)

##### _`ALERT!` This plugin release is only compatible with Notepad++ 8.0 and later releases._

#### Programming Note:
The Notepad++ 8.0 has introduced the Fluent UI icons in Small/Large, Light/Dark & Unfilled/Filled modes, making for a total of 8 possible combinations. But the newly added API function [`NPPM_ADDTOOLBARICON_FORDARKMODE`](https://github.com/notepad-plus-plus/notepad-plus-plus/commit/8a898bae3f84c03c44aaed25001e9fa1ddfa09aa) has allowed the plugins to supply images for only 4 Fluent UI images among the possible set of 8.

Due to the current NPP API limitation, this minor release for FWDataViz is only able to add Fluent UI icons for the Small/Large, Light/Dark Fluent UI modes but not the Filled/Unfilled Fluent UI modes. So the toolbar icons for this plugin will not change when switching between unfilled and filled Fluent UI selections in Notepad++ Preferences dialog.

**Release:** [1.2.0.2 Release](https://github.com/shriprem/Goto-Line-Col-NPP-Plugin/releases/tag/1.2.0.2)

---

### Version 1.2.0.1
#### Minor Update

Changed menu item text from "Show Panel" to "Show GotoLineColPanel" since this same text gets used to display balloon tip for the toolbar icon.

**Release:** [1.2.0.1 Release](https://github.com/shriprem/Goto-Line-Col-NPP-Plugin/releases/tag/1.2.0.1)

---

### Version 1.2.0.0
#### Enhancements:
1. Added real-time display of Cursor Position data, at a fixed spot, on the plugin panel. That means:
    * No more need for repetitive clicking of the Goto button
    * No more need to view this info within a calltip that jumps around the screen
2. Added toolbar icon to show & hide the plugin panel:
![Show_Panel_icon](https://raw.githubusercontent.com/shriprem/Goto-Line-Col-NPP-Plugin/master/images/show_panel_toolbutton.png)

**Release:** [1.2.0.0 Release](https://github.com/shriprem/Goto-Line-Col-NPP-Plugin/releases/tag/1.2.0.0)

---

### Version 1.1.0.0
#### Enhancements:
1. Added UTF-8 byte sequence and Unicode code point display in the calltip.
2. Added *Char Column* and *Byte Column* display in the calltip.
3. In the Preferences dialog, replaced option *'Expand TABS for column value computation (Unchecked)'* with *'Use byte count for column value computation (Checked)'*.
4. Added spin controls on the Line and Column input fields for quick navigation to adjacent line or column.

#### Fixed Issue:
1. The calltip was getting displayed only after clicking the *Go* button twice.

**Release:** [1.1.0.0 Release](https://github.com/shriprem/Goto-Line-Col-NPP-Plugin/releases/tag/1.1.0.0)

---

### Version 1.0.0.1
1. Increased Line and Column input fields to accept up to 8 digits.

**Release:** [1.0.0.1 Release](https://github.com/shriprem/Goto-Line-Col-NPP-Plugin/releases/tag/v1.0.0.1)

---

### Version 1.0.0
First Release

**Release:** [1.0.0 Release](https://github.com/shriprem/Goto-Line-Col-NPP-Plugin/releases/tag/v1.0.0)


