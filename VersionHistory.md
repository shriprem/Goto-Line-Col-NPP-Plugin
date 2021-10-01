## Version History

### Version 2.1.0.0
#### Enhancements:
1. Command Line Option to load multiple documents and position them all at the same line and character/byte column.

See: [Command Line Options](https://github.com/shriprem/Goto-Line-Col-NPP-Plugin/blob/master/docs/CommandLineOptions.md)

---

### Version 2.0.0.0
#### Enhancements:
1. Darkmode rendering enabled for the plugin panel and dialog boxes.

#### `NOTE`
Notepad++ user configuration settings are saved into the config.xml file by Notepad++ only during the application closing event. The GotoLineCol plugin is only able to read these settings changes in the config.xml file during the next launch of Notepad++.

So, when Darkmode settings are changed, Notepad++ will need to be restarted for the plugin to reflect these settings changes.

See: [Sample screenshots of the plugin UI in dark mode.](https://github.com/shriprem/Goto-Line-Col-NPP-Plugin/blob/master/docs/DarkModeUI.md)

---

### Version 1.2.0.2
#### Enhancements:
1. Light & Dark mode Fluent UI toolbar icons added for the plugin.
2. Including ARM64 build. (_Please note that I am unable to test the ARM64 build since I don't have an ARM64 device, and it is being provided AS IS._)

##### _`ALERT!` This plugin release is only compatible with Notepad++ 8.0 and later releases._

#### Programming Note:
The Notepad++ 8.0 has introduced the Fluent UI icons in Small/Large, Light/Dark & Unfilled/Filled modes, making for a total of 8 possible combinations. But the newly added API function [`NPPM_ADDTOOLBARICON_FORDARKMODE`](https://github.com/notepad-plus-plus/notepad-plus-plus/commit/8a898bae3f84c03c44aaed25001e9fa1ddfa09aa) has allowed the plugins to supply images for only 4 Fluent UI images among the possible set of 8.

Due to the current NPP API limitation, this minor release for FWDataViz is only able to add Fluent UI icons for the Small/Large, Light/Dark Fluent UI modes but not the Filled/Unfilled Fluent UI modes. So the toolbar icons for this plugin will not change when switching between unfilled and filled Fluent UI selections in Notepad++ Preferences dialog.

---

### Version 1.2.0.1
#### Minor Update

Changed menu item text from "Show Panel" to "Show GotoLineColPanel" since this same text gets used to display balloon tip for the toolbar icon.

---

### Version 1.2.0.0
#### Enhancements:
1. Added real-time display of Cursor Position data, at a fixed spot, on the plugin panel. That means:
    * No more need for repetitive clicking of the Goto button
    * No more need to view this info within a calltip that jumps around the screen
2. Added toolbar icon to show & hide the plugin panel:
![Show_Panel_icon](https://raw.githubusercontent.com/shriprem/Goto-Line-Col-NPP-Plugin/master/images/show_panel_toolbutton.png)

---

### Version 1.1.0.0
#### Enhancements:
1. Added UTF-8 byte sequence and Unicode code point display in the calltip.
2. Added *Char Column* and *Byte Column* display in the calltip.
3. In the Preferences dialog, replaced option *'Expand TABS for column value computation (Unchecked)'* with *'Use byte count for column value computation (Checked)'*.
4. Added spin controls on the Line and Column input fields for quick navigation to adjacent line or column.

#### Fixed Issue:
1. The calltip was getting displayed only after clicking the *Go* button twice.

---

### Version 1.0.0.1
1. Increased Line and Column input fields to accept up to 8 digits.


