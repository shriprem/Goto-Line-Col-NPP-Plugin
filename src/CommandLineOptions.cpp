#include "CommandLineOptions.h"

void CommandLineOptions::scan() {
   bool bQuoted{}, bExecFound{}, bLineNumFound{}, bColNumFound{};
   wstring quote{ L"\"" };
   wregex leadingSpaces{ L"^[ ]*" };
   wregex multiSpaces{ L"[ ]{2,}" };

   wstring cmdLine{}, cmdOption{};
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

      if (cmdOption.substr(0, 2) == L"-n") {
         if (!bLineNumFound) {
            cmdLineNum = Utils::StringtoInt(cmdOption.substr(2));
            bLineNumFound = TRUE;
         }
      }
      else if (cmdOption.substr(0, 2) == L"-c") {
         if (!bColNumFound) {
            cmdColNum = Utils::StringtoInt(cmdOption.substr(2));
            bColNumFound = TRUE;
         }
      }
      else {
         FilePath FP;

         if (fsp(cmdOption).has_root_path()) {
            FP.path = cmdOption;
            FP.has_root = TRUE;
         }
         else {
            FP.path = fsp(cmdOption).filename();
            FP.has_root = FALSE;
         }

         filePaths.emplace_back(FP);
      }
   }

#if DEBUG_CMD_LINE_SCAN
   wstring sVerify{ L"Line No: " + to_wstring(cmdLineNum) + L"\r\nCol No: " + to_wstring(cmdColNum) };

   for each (auto fPath in filePaths) {
      sVerify += L"\r\nPath: " + fPath.path;
   }

   MessageBox(nullptr, sVerify.c_str(), L"", MB_OK);
#endif
}

bool CommandLineOptions::gotoCol(int& lineNum, int& colNum) {
   if (cmdLineNum < 0) return FALSE;
   if (cmdColNum < 0) return FALSE;

   int fileCount{ static_cast<int>(filePaths.size()) };
   if (fileCount < 1) return FALSE;

   HWND hScintilla{ getCurrentScintilla() };
   if (!hScintilla) return FALSE;

   TCHAR filePath[MAX_PATH]{};
   nppMessage(NPPM_GETFULLCURRENTPATH, MAX_PATH, (LPARAM)filePath);
   wstring sFilePath{ filePath };

   TCHAR fileName[MAX_PATH]{};
   nppMessage(NPPM_GETFILENAME, MAX_PATH, (LPARAM)fileName);
   wstring sFileName{ fileName };

   int nMatchIndex{ -1 };
   for (int i{}; i < fileCount; i++) {
      if (filePaths[i].path == (filePaths[i].has_root ? sFilePath : sFileName)) {
         nMatchIndex = i;
         break;
      }
   }

   if (nMatchIndex < 0) return FALSE;

   int curPos = static_cast<int>(SendMessage(hScintilla, SCI_GETCURRENTPOS, NULL, NULL));
   int curLine = static_cast<int>(SendMessage(hScintilla, SCI_LINEFROMPOSITION, curPos, NULL));
   int curCol = static_cast<int>(SendMessage(hScintilla, SCI_GETCOLUMN, curPos, NULL));

   if (curLine + 1 == cmdLineNum && curCol + 1 == cmdColNum) {
      filePaths.erase(filePaths.begin() + nMatchIndex);
      lineNum = cmdLineNum;
      colNum = cmdColNum;
      return TRUE;
   }

   return FALSE;
}
