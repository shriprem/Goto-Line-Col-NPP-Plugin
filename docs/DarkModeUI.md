## _GoToLineCol_ in Darkmode

Darkmode for the _GoToLineCol_ plugin is rendered by the [NPP_Plugin_Darkmode.dll](https://github.com/shriprem/NPP_Plugin_Darkmode). This DLL file can be shared by multiple plugins, thus reducing the overall memory footprint.

To verify the DLL sharing, if you have both the _[FWDataViz](https://github.com/shriprem/FWDataViz)_ and _[GotoLineCol](https://github.com/shriprem/Goto-Line-Col-NPP-Plugin)_ plugins installed, for instance, move the `NPP_Plugin_Darkmode.dll` file either from `<NPP_Plugins_folder>/FWDataViz` or `<NPP_Plugins_folder>/GotoLineCol` folder into the `<NPP_folder>`, and delete `NPP_Plugin_Darkmode.dll` in the other plugin folder.

##### _Restart of Notepad++ is necessary when darkmode settings are changed_
The _GoToLineCol_ plugin is able to render in darkmode based on the settings stored in the `config.xml` file for Notepad++. (The `config.xml` is located either in the `%APPDATA%\Notepad++` folder for full installations of NPP or the `<NPP_Portable>` folder for portable versions of NPP.)

When darkmode is enabled or disabled, or when darkmode tone settings are changed in Notepad++, those changes are only confined to the Notepad++ process memory. These setting changes remain inaccessible to the _GoToLineCol_ plugin until Notepad++ is closed. Only when Notepad++ is closed, the setting changes are saved to the `config.xml` file by the Notepad++ process.

Therefore, until the time when Notepad++ API is enhanced to provide these setting changes to the plugins dynamically, a restart of Notepad++ is necessary for the _GoToLineCol_ plugin to be able to reflect changes in the darkmode settings.


### Plugin Panel in dark mode (_in Cyan tone_)
![GotoLineCol Panel](https://raw.githubusercontent.com/shriprem/Goto-Line-Col-NPP-Plugin/master/images/PanelBytePos_dm.png)

### Preferences Dialog in dark mode (_in Green tone_)
![Preferences](https://raw.githubusercontent.com/shriprem/Goto-Line-Col-NPP-Plugin/master/images/Preferences_dm.png)

