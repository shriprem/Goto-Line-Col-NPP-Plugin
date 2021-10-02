# Command Line Options

The command line options allows multiple files to be launched in Notepad++, and then instruct the **GotoLineCol** plugin to navigate to a specific line and character or byte-based column with optional post-navigation actions.

#### Sample Usage with all options specified:
```
     NPP_DIR\notepad++.exe DirA_File1 DirA_File2 DirB_File3 -n8 -c42 -z -GLCb1 -z -GLCc1 -z -GLCd1 -z -GLCe14  -GLCf1 -z -GLCh0 -z -GLCp1 -z -GLCq1
```
**In the above sample usage**:
* The **`-n`**, **`-c`** and **`-z`** options are native to Notepad++. For more info on these three, see: [Notepad++ Usage via the command prompt](https://npp-user-manual.org/docs/command-prompt/).

* All the other options are specific to the **GotoLineCol** plugin. These options start with a common **`-GLC`** prefix.

* The **`-GLC`** options need to be preceded by the **`-z`** option to suppress Notepad++ from treating these options as file names.


### GLC Options List
| Syntax | Mnemonic | Config File&dagger; Key | Description |
|---|---|---|
| **`-GLCb`** | **B**yte | *UseByteCol* | Column count will be based on bytes (`-GLCb1`) or characters (`-GLCb0`).  |
| **`-GLCc`** | **C**enter | *CenterCaret* | At the destination position, the caret will be centered (`-GLCc1`) or not (`-GLCc0`). |
| **`-GLCd`** | **D**isplay | *ShowCallTip* | At the destination position, a calltip will be displayed (`-GLCd1`) or not (`-GLCd0`). |
| **`-GLCe`** | **E**dge | *EdgeBuffer* | At the navigation destination, the caret will be positioned to be *`n`* spaces away from the closest left or right edge. Valid values for *`n`*: [1 - 20] |
| **`-GLCf`** | **F**lash | *FlashSeconds* | At the navigation destination, the caret will be flashed for *`n`* seconds. Valid values for *`n`*: [1 - 10] |
| **`-GLCh`** | **H**ighlight | *BraceHighlight* | At the destination position, the character will be highlighted (`-GLCh1`) or not (`-GLCh0`). |
| **`-GLCp`** | **P**ersist | *CmdProcPersist&Dagger;* | On each switch between document tabs, as long as the file was opened from the command line and its current line is the same as that specified by the `-n` option, persist with processing the command line options (`-GLCp1`) or not (`-GLCp0`). |
| **`-GLCq`** | **Q**uiet | *CmdProcHidden&Dagger;* | Even when the **GotoLineCol** plugin panel is hidden, process command line options (`-GLCq1`) or not (`-GLCq0`).  |

* &dagger; The Config file is: `NPP_PLUGINS_CONFIG_DIR/GotoLineCol.ini`.
   * For installed versions, the `NPP_PLUGINS_CONFIG_DIR` is usually: `%APPDATA%\Notepad++` folder. For example: `C:\Users\WIN_USER\AppData\Roaming\Notepad++`.
   * For portable versions, the `NPP_PLUGINS_CONFIG_DIR` is the same as the portable folder of `NPP_DIR/plugins/Config`.

* &Dagger; The *CmdProc...* options are not configurable via the [Preferences dialog](https://github.com/shriprem/Goto-Line-Col-NPP-Plugin/blob/master/docs/PreferencesDialog.md). For a durable setting of these options, they will need to be manually edited in the `NPP_PLUGINS_CONFIG_DIR/GotoLineCol.ini` file.

* When any of the listed (`-GLC`) options are not used in the command line, the values specified in the Config File&dagger; (see above) will be used instead.

#### Usage Tips:
1. The command line processing by the plugin is possible only with a fresh instance of Notepad++. If Notepad++ is already running, use the `-multiInst` option in the command line to launch a new instance. See: [Notepad++ Usage via the command prompt](https://npp-user-manual.org/docs/command-prompt/).

2. When launching files with identical names from the command line, specify their full paths.

3. The file and folder names are not case sensitive. However if the file path has spaces, enclose it with double quotes. For example: `"C:\Users\John Doe\My Documents\Sample File.txt"`

4. The `-GLC` options specified in the command line will be overridden if the [Preferences Dialog](https://github.com/shriprem/Goto-Line-Col-NPP-Plugin/blob/master/docs/PreferencesDialog.md) is opened, and its **OK** button is pressed.
