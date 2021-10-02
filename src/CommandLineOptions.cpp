#include "CommandLineOptions.h"

void CommandLineOptions::scan(ALL_PREFERENCES& allPrefs) {
   bool bQuoted{}, bExecFound{}, bLineNumFound{}, bColNumFound{};
   wstring quote{ L"\"" };
   wregex leadingSpaces{ L"^[ ]*" };
   wregex multiSpaces{ L"[ ]{2,}" };

   wstring cmdLine{}, cmdOption{}, prefix2{};
   std::size_t nOptEnd{}, nQuoteOffset{};

   cmdLine = GetCommandLine();

   // Strip any leading spaces & adjacent multiple spaces in the command line
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
      else if (cmdOption.substr(0, 4) == L"-GLC") {
         scanGLC(allPrefs, cmdOption.substr(4));
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

   sVerify += L"\r\n\r\n=== PREFERENCES ===\r\n" + getAllPrefsList(allPrefs);
   MessageBox(nullptr, sVerify.c_str(), L"", MB_OK);
#endif // DEBUG_CMD_LINE_SCAN
}

void CommandLineOptions::scanGLC(ALL_PREFERENCES& allPrefs, wstring glcOptions) {
   std::size_t nOptEnd{};
   int nOptVal{};
   wstring sOption{}, sOptKey{};

   while (glcOptions.length() > 0) {
      nOptEnd = glcOptions.find(L";", 1);

      if (nOptEnd == wstring::npos) {
         sOption = glcOptions.substr(0);
         glcOptions = L"";
      }
      else {
         sOption = glcOptions.substr(0, nOptEnd);
         glcOptions = glcOptions.substr(nOptEnd + 1);
      }

      sOptKey = sOption.substr(0, 1);
      nOptVal = Utils::StringtoInt(sOption.substr(1));

      if (sOptKey == L"b")
         allPrefs.useByteCol = (nOptVal != FALSE);
      else if (sOptKey == L"c")
         allPrefs.centerCaret = (nOptVal != FALSE);
      else if (sOptKey == L"d")
         allPrefs.showCalltip = (nOptVal != FALSE);
      else if (sOptKey == L"e")
         allPrefs.edgeBuffer = (nOptVal < 1) ? 1 : ((nOptVal > 20) ? 20 : nOptVal);
      else if (sOptKey == L"f")
         allPrefs.caretFlashSeconds = (nOptVal < 1) ? 1 : ((nOptVal > 10) ? 10 : nOptVal);
      else if (sOptKey == L"h")
         allPrefs.braceHilite = (nOptVal != FALSE);
      else if (sOptKey == L"p")
         allPrefs.cmdProcPersist = (nOptVal != FALSE);
      else if (sOptKey == L"q")
         allPrefs.cmdProcHidden = (nOptVal != FALSE);
   }
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

wstring CommandLineOptions::getAllPrefsList(ALL_PREFERENCES& allPrefs) {
   wstring prefs{};

   prefs = L"UseByteCount: " + to_wstring(allPrefs.useByteCol) +
      L"\r\nCenterCaret: " + to_wstring(allPrefs.centerCaret) +
      L"\r\nDisplayCalltip: " + to_wstring(allPrefs.showCalltip) +
      L"\r\nEdgeBuffer: " + to_wstring(allPrefs.edgeBuffer) +
      L"\r\nFlashSeconds: " + to_wstring(allPrefs.caretFlashSeconds) +
      L"\r\nHighlightCharacter: " + to_wstring(allPrefs.braceHilite) +
      L"\r\nPersistGoto: " + to_wstring(allPrefs.cmdProcPersist) +
      L"\r\nQuietProc: " + to_wstring(allPrefs.cmdProcHidden);

   return prefs;
}

