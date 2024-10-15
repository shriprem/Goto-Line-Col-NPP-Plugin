#pragma once

#include "PluginDefinition.h"
#include "Utils.h"

#include <vector>
#include <filesystem>
#include <fstream>
#include <format>

#define NA "N/A"

using std::vector;

class NameBlocks {
private:
   struct nameblock {
      int begin{};
      int end{};
      string name{};
   };

   char blocksFilePath[MAX_PATH]{};
   char namesFilePath[MAX_PATH]{};
   vector<nameblock> nameBlocks{};

   int tokenize(string& text, vector<string>& results, const string& delim);

   void initNamesFilePath();
   void initBlocks();
   string findBlock(const int codepoint);

public:
   void init();
   int getUnicodeBlock(const int codepoint, char* block, int blocksize);
   int getUnicodeName(const int codepoint, char* name, int namesize);
   int getUnicodeBlockAndName(const int codepoint, char* block, int blocksize, char* name, int namesize);
};
