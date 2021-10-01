#include "CommandLineOptions.h"

void CommandLineOptions::scan(ALL_PREFERENCES& allPrefs) {
   bool bQuoted{}, bExecFound{}, bLineNumFound{}, bColNumFound{};
   wstring quote{ L"\"" };
   wregex leadingSpaces{ L"^[ ]*" };
   wregex multiSpaces{ L"[ ]{2,}" };

   wstring cmdLine{}, cmdOption{}, prefix2{}, prefix5{};
   std::size_t nOptEnd{}, nQuoteOffset{};

   cmdLine = GetCommandLine();

   // Strip any leading spaces in the command line
   cmdLine = regex_replace(cmdLine, leadingSpaces, L"");
   cmdLine = regex_replace(cmdLine, multiSpaces, L" ");

   filePaths.clear();

   while (cmdLine.length() > 0) {
      bQuoted = (cmdLine.substr(0, 1) == quote);
      nOptEnd = cmdLine.find(bQuoted ? quote : L" ", 1);
      nQuoteOffset = bQuoted ? 1 : 0;

      if (nOptEnd == wstring::npos) {
         cmdOption = cmdLine.substr(nQuoteOffset);
         cmdLine = L"";
      }
      else {
         cmdOption = cmdLine.substr(nQuoteOffset, nOptEnd - nQuoteOffset);
         cmdLine = regex_replace(cmdLine.substr(nOptEnd + 1), leadingSpaces, L"");
      }

      if (!bExecFound) {
         bExecFound = TRUE;
         continue;
      }

      prefix2 = cmdOption.substr(0, 2);
      prefix5 = cmdOption.substr(0, 5);

      if (prefix2 == L"-n") {
         if (!bLineNumFound) {
            cmdLineNum = Utils::StringtoInt(cmdOption.substr(2));
            bLineNumFound = TRUE;
         }
      }
      else if (prefix2 == L"-c") {
         if (!bColNumFound) {
            cmdColNum = Utils::StringtoInt(cmdOption.substr(2));
            bColNumFound = TRUE;
         }
      }
      else if (prefix2 == L"-z") {
         continue;
      }
      else if (prefix5 == L"-GLCb") {
         allPrefs.useByteCol = Utils::StringtoInt(cmdOption.substr(5)) != FALSE;
      }
      else if (prefix5 == L"-GLCc") {
         allPrefs.centerCaret = Utils::StringtoInt(cmdOption.substr(5)) != FALSE;
      }
      else if (prefix5 == L"-GLCd") {
         allPrefs.showCalltip = Utils::StringtoInt(cmdOption.substr(5)) != FALSE;
      }
      else if (prefix5 == L"-GLCe") {
         int edgeBuffer = Utils::StringtoInt(cmdOption.substr(5));
         allPrefs.edgeBuffer = (edgeBuffer < 1) ? 1 : ((edgeBuffer > 20) ? 20 : edgeBuffer);
      }
      else if (prefix5 == L"-GLCf") {
         int caretFlash = Utils::StringtoInt(cmdOption.substr(5));
         allPrefs.caretFlashSeconds = (caretFlash < 1) ? 1 : ((caretFlash > 10) ? 10 : caretFlash);
      }
      else if (prefix5 == L"-GLCh") {
         allPrefs.braceHilite = Utils::StringtoInt(cmdOption.substr(5)) != FALSE;
      }
      else if (prefix5 == L"-GLCp") {
         allPrefs.cmdProcPersist = Utils::StringtoInt(cmdOption.substr(5)) != FALSE;
      }
      else if (prefix5 == L"-GLCq") {
         allPrefs.cmdProcHidden = Utils::StringtoInt(cmdOption.substr(5)) != FALSE;
      }
      else {
         FilePath FP;
         TCHAR path[MAX_PATH + 1];

         if (fsp(cmdOption).has_root_path()) {
            wcsncpy(path, cmdOption.c_str(), MAX_PATH);
            FP.has_root = TRUE;
         }
         else {
            wcsncpy(path, fsp(cmdOption).filename().c_str(), MAX_PATH);
            FP.has_root = FALSE;
         }

         Utils::ToUpper(path);
         FP.path = path;
         filePaths.emplace_back(FP);
      }
   }

#if DEBUG_CMD_LINE_SCAN
   wstring sVerify{ L"Line No: " + to_wstring(cmdLineNum) + L"\r\nCol No: " + to_wstring(cmdColNum) };

   for each (auto FP in filePaths) {
      sVerify += L"\r\nPath: " + FP.path;
   }

   MessageBox(nullptr, sVerify.c_str(), L"", MB_OK);
#endif // DEBUG_CMD_LINE_SCAN
}

bool CommandLineOptions::gotoCol(int& lineNum, int& colNum, bool bPersist) {
   if (cmdLineNum < 0) return FALSE;
   if (cmdColNum < 0) return FALSE;

   int fileCount{ static_cast<int>(filePaths.size()) };
   if (fileCount < 1) return FALSE;

   HWND hScintilla{ getCurrentScintilla() };
   if (!hScintilla) return FALSE;

   TCHAR filePath[MAX_PATH]{};
   nppMessage(NPPM_GETFULLCURRENTPATH, MAX_PATH, (LPARAM)filePath);
   Utils::ToUpper(filePath);

   TCHAR fileName[MAX_PATH]{};
   nppMessage(NPPM_GETFILENAME, MAX_PATH, (LPARAM)fileName);
   Utils::ToUpper(fileName);

   int nMatchIndex{ -1 };
   for (int i{}; i < fileCount; i++) {
      if (filePaths[i].path == (filePaths[i].has_root ? filePath : fileName)) {
         nMatchIndex = i;
         break;
      }
   }

   if (nMatchIndex < 0) return FALSE;

   int curPos = static_cast<int>(SendMessage(hScintilla, SCI_GETCURRENTPOS, NULL, NULL));
   int curLine = static_cast<int>(SendMessage(hScintilla, SCI_LINEFROMPOSITION, curPos, NULL));

   if (curLine + 1 == cmdLineNum) {
      if (!bPersist)
         filePaths.erase(filePaths.begin() + nMatchIndex);

      lineNum = cmdLineNum;
      colNum = cmdColNum;
      return TRUE;
   }

   return FALSE;
}

void CommandLineOptions::displayPrefs(ALL_PREFERENCES& allPrefs) {
   wstring prefs{};

   prefs = L"UseByteCount: " + to_wstring(allPrefs.useByteCol) +
      L"\r\nCenterCaret: " + to_wstring(allPrefs.centerCaret) +
      L"\r\nDisplayCalltip: " + to_wstring(allPrefs.showCalltip) +
      L"\r\nEdgeBuffer: " + to_wstring(allPrefs.edgeBuffer) +
      L"\r\nFlashSeconds: " + to_wstring(allPrefs.caretFlashSeconds) +
      L"\r\nHighlightCharacter: " + to_wstring(allPrefs.braceHilite) +
      L"\r\nPersistGoto: " + to_wstring(allPrefs.cmdProcPersist) +
      L"\r\nQuietProc: " + to_wstring(allPrefs.cmdProcHidden);

#if DEBUG_PREF_VALUES
   MessageBox(NULL, prefs.c_str(), L"", MB_OK);
#endif // DEBUG_PREF_VALUES
}
