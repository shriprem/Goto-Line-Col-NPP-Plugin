@ECHO OFF

SET PLUGIN_NAME=GotoLineCol
SET BIN_DIR=arm64\
REM SET NOTEPAD_DIR=C:\Portable\Notepad++\
REM SET PLUGINS_DIR=%NOTEPAD_DIR%\plugins\%PLUGIN_NAME%\

COPY LICENSE %BIN_DIR%
COPY src\UnicodeData\UnicodeBlocks.csv %BIN_DIR%
COPY src\UnicodeData\UnicodeData.ini %BIN_DIR%

REM COPY src\UnicodeData\UnicodeBlocks.csv "%PLUGINS_DIR%"
REM COPY src\UnicodeData\UnicodeData.ini "%PLUGINS_DIR%"
REM COPY %BIN_DIR%\%PLUGIN_NAME%.dll "%PLUGINS_DIR%"

REM START /D "%NOTEPAD_DIR%" notepa~1.exe
EXIT 0
