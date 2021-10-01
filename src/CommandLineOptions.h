#pragma once

#include "PreferencesIO.h"
#include "Utils.h"

#include<filesystem>
#include<regex>
#include<vector>
#include <windows.h>

#define DEBUG_CMD_LINE_SCAN FALSE
#define DEBUG_PREF_VALUES FALSE

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
   void displayPrefs(ALL_PREFERENCES& allPrefs);

private:
   int cmdLineNum{ -1 }, cmdColNum{ -1 };

   struct FilePath {
      wstring path;
      bool has_root;
   };
   vector<FilePath> filePaths{};
};

