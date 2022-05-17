#pragma once

#include "PreferencesIO.h"
#include "Utils.h"

#include<filesystem>
#include<regex>
#include<vector>
#include <windows.h>

#define DEBUG_CMD_LINE_SCAN FALSE
#define NPP_MIN_VERSION_WITH_CURRENTCMDLINE      8.41f

using std::regex_replace;
using std::wregex;
using std::wstring;
using std::vector;
using fsp = std::filesystem::path;

class CommandLineOptions
{
public:
   void scan(ALL_PREFERENCES& allPrefs);
   bool gotoCol(int& lineNum, int& colNum, bool bPersist);

private:
   int cmdLineNum{ -1 }, cmdColNum{ -1 };

   struct FilePath {
      wstring path;
      bool has_root;
   };
   vector<FilePath> filePaths{};

   void scanPluginMessage(ALL_PREFERENCES& allPrefs, wstring pluginMessage);
   void scanGLC(ALL_PREFERENCES& allPrefs, wstring glcOptions);
   wstring getAllPrefsList(ALL_PREFERENCES& allPrefs);
};

