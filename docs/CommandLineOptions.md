# Command Line Options

The command line options allow multiple files to be launched in Notepad++, and then instruct the **GotoLineCol** plugin to navigate to a specific line and character or byte-based column with optional post-navigation actions.

#### Sample Usage with all options specified:
```
NPP_DIR\notepad++.exe DirPathA_File1 DirPathA_File2 DirPathB_File3 -n8 -c42 -pluginMessage=GLCb1;c0;d1;e18;f1;h1;p1;q1
```
**In the above sample usage**:
* The **`-n`** and **`-c`** options are native to Notepad++.
   * **`-n<line_number>`** will cause all files specified on the command prompt to be positioned at the specified line.
   * **`-c<column_number>`** will cause all files specified on the command prompt to be positioned at the specified column. **GotoLineCol** plugin will use this value to reposition using byte counts, if **`b1`** was specified.
   * For example: `NPP_DIR\notepad++.exe Sample.txt `**`-n148 -c861`** will open the *Sample.txt* file at line *148* and column *861*.
   * For more info on these Notepad++ native options, see: [Notepad++ - Usage via the command prompt](https://npp-user-manual.org/docs/command-prompt/).

* The **`-pluginMessage=GLCb1;c0;d1;e18;f1;h1;p1;q1`** option is for the **GotoLineCol** plugin. Each sub-option that follows the `GLC` prefix has a single-letter key, followed by its value. The sub-options are separated by just a semicolon. There shall be no space between the semicolon and the next sub-option.


### GLC Sub-options List
| Key | Mnemonic | Config File&dagger; Key | Description |
|---|---|---|---|
| **`b`** | **B**yte | *UseByteCol* | Column count will be based on bytes (`b1`) or characters (`b0`). [More Info](https://github.com/shriprem/Goto-Line-Col-NPP-Plugin/blob/master/docs/PreferencesDialog.md#use-byte-count-for-column-value-computation-checked).  |
| **`c`** | **C**enter | *CenterCaret* | At the destination position, the caret will be centered (`c1`) or not (`c0`). [More Info](https://github.com/shriprem/Goto-Line-Col-NPP-Plugin/blob/master/docs/PreferencesDialog.md#cursor-is-centered-in-the-editor-at-destination-checked). |
| **`d`** | **D**isplay | *ShowCallTip* | At the destination position, a calltip will be displayed (`d1`) or not (`d0`). [More Info](https://github.com/shriprem/Goto-Line-Col-NPP-Plugin/blob/master/docs/PreferencesDialog.md#display-character-code-at-destination-checked). |
| **`e`** | **E**dge | *EdgeBuffer* | At the navigation destination, the caret will be positioned to be specified spaces away from the closest left or right edge. [More Info](https://github.com/shriprem/Goto-Line-Col-NPP-Plugin/blob/master/docs/PreferencesDialog.md#edge-buffer-at-destination-10). Valid values: [1 - 20] |
| **`f`** | **F**lash | *FlashSeconds* | At the navigation destination, the caret will be flashed for specified seconds. [More Info](https://github.com/shriprem/Goto-Line-Col-NPP-Plugin/blob/master/docs/PreferencesDialog.md#cursor-flash-duration-3-seconds). Valid values: [1 - 10] |
| **`h`** | **H**ighlight | *BraceHighlight* | At the destination position, the character will be highlighted (`h1`) or not (`h0`). [More Info](https://github.com/shriprem/Goto-Line-Col-NPP-Plugin/blob/master/docs/PreferencesDialog.md#highlight-character-at-destination-checked). |
| **`p`** | **P**ersist | *CmdProcPersist&Dagger;* | On each switch between document tabs, as long as the file was opened from the command prompt and its current line is the same as that specified by the `-n` option, persist with processing the command prompt options (`p1`) or not (`p0`). [More Info](https://github.com/shriprem/Goto-Line-Col-NPP-Plugin/blob/master/docs/CommandLineOptions.md#persistent-mode). |
| **`q`** | **Q**uiet | *CmdProcHidden&Dagger;* | Even when the **GotoLineCol** plugin panel is hidden, process command line options (`q1`) or not (`q0`).  |

* &dagger; The Config File is: `NPP_PLUGINS_CONFIG_DIR/GotoLineCol.ini`.
   * For installed versions, the `NPP_PLUGINS_CONFIG_DIR` is usually the `%APPDATA%\Notepad++` folder. For example: `C:\Users\WIN_USER\AppData\Roaming\Notepad++`.
   * For portable versions, the `NPP_PLUGINS_CONFIG_DIR` is co-located at `NPP_DIR/plugins/Config`.

* &Dagger; The *CmdProc...* options are not configurable via the [Preferences dialog](https://github.com/shriprem/Goto-Line-Col-NPP-Plugin/blob/master/docs/PreferencesDialog.md). For a durable setting of these options, they will need to be manually edited in the `NPP_PLUGINS_CONFIG_DIR/GotoLineCol.ini` file.

* When any of the listed `GLC` sub-options are not used in the command line, the values specified in the Config File&dagger; (see above) or their defaults (see: [Preferences dialog](https://github.com/shriprem/Goto-Line-Col-NPP-Plugin/blob/master/docs/PreferencesDialog.md)) will be used instead.

### Persistent Mode
To understand the role of the **CmdProcPersist** sub-option, consider a situation where two files were launched with the following command line option:
```
NPP_DIR\notepad++.exe File1 File2 -n8 -c42 -pluginMessage=GLCb1;d1;f2;h1;p1
```
Notepad++ will open the two files in two tabs. The second tab will be the active tab. In this active tab, the **`-n`** and **`-c`** options will cause the caret to be positioned on line 8 and _character_ column 42. The **`b1`** sub-option will reposition the caret, if necessary, to _byte_ column 42. The other **`GLC`** sub-options will then cause these post-navigational actions: a calltip to be displayed, the caret to flash in block mode for 2 seconds, and the character at this position to be highlighted.

If you then switch to the first tab, the same sequence of navigation and post-navigation actions will be performed afresh on this tab.

With the persistent mode OFF (`p0`), the navigation and post-navigation actions will be performed only once per file tab. Therefore, if `p0` was specified and if you were to switch back to the second tab, there will be no navigation and post-navigation actions this time since it will not be the first visit to this tab.

With the persistent mode ON (`p1`), the navigation and post-navigation actions will be repeated on each visit to the file tabs, as long as the current line number of the file matches the value specified with the `-n` option. If only the column position has changed, the caret will be pulled back to the column position specified with the `-c` option. The match of the current line number will act as a trigger for the persistent mode on a per-file basis.

### Usage Tips:
1. When launching files with identical names from the command line, specify their full paths.

2. The file and folder names are not case sensitive. However if the file path has spaces, enclose it with double quotes. For example: `"C:\Users\John Doe\My Documents\Sample File.txt"`

3. Demarcate the **`GLC`** sub-options with just a semicolon each. Ensure that there is no space between the semicolon and the next sub-option.

4. The **`GLC`** sub-option values will be overridden if the [Preferences Dialog](https://github.com/shriprem/Goto-Line-Col-NPP-Plugin/blob/master/docs/PreferencesDialog.md) is opened, and its **OK** button is pressed.

5. Trying to specify the **`-n`** or **`-c`** or **`-pluginMessage=`** more than once will cause Notepad++ to treat the repeats as filenames.

6. If you need to specify command line options for other plugins, use quotes and separate the options for the plugins with spaces. Like so: `-pluginMessage="GLCb1;c0;d1;e18;f1;h1;p1;q1 PLUGINa... PLUGINb... PLUGINc..."`.