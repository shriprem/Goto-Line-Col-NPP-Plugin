#include "NameBlocks.h"

int NameBlocks::tokenize(string& text, vector<string>& results, const string& delim) {
   results.clear();
   if (text.empty()) return 0;

   char* token = std::strtok(text.data(), delim.c_str());
   while (token) {
      results.emplace_back(token);
      token = std::strtok(nullptr, delim.c_str());
   }

   return static_cast<int>(results.size());
}

void NameBlocks::initNamesFilePath() {
   char modulePath[MAX_PATH];
   HMODULE hm{};

   GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCWSTR)&isUnicode, &hm);
   GetModuleFileNameA(hm, modulePath, MAX_PATH);
   string parentDir{ std::filesystem::path(modulePath).parent_path().string() };

   PathCombineA(blocksFilePath, parentDir.c_str(), "UnicodeBlocks.csv");
   PathCombineA(namesFilePath, parentDir.c_str(), "UnicodeData.ini");
}

void NameBlocks::initBlocks() {
   std::ifstream ss(blocksFilePath);

   string line(MAX_PATH, '\0');
   nameBlocks.clear();

   while (getline(ss, line, '\n')) {
      vector<string>words{};

      if (tokenize(line, words, ",") >= 3) {
         nameblock nb{Utils::StringtoInt(words[0], 16), Utils::StringtoInt(words[1], 16), Utils::LTrim(words[2])};
         nameBlocks.emplace_back(nb);
      }
   }
}

string NameBlocks::findBlock(const int codepoint) {
   for (size_t index{ 0 }; index < nameBlocks.size(); index++) {
      if (codepoint >= nameBlocks[index].begin && codepoint <= nameBlocks[index].end)
         return nameBlocks[index].name;
   }
   return "";
}

void NameBlocks::init() {
   initNamesFilePath();
   initBlocks();
}

int NameBlocks::getUnicodeBlock(const int codepoint, char* block, int blocksize) {
   string blockName{ findBlock(codepoint) };
   return snprintf(block, blocksize, "%s", blockName.empty() ? NA : blockName.c_str());
}

int NameBlocks::getUnicodeName(const int codepoint, char* name, int namesize) {
   char blockName[MAX_PATH]{};
   return getUnicodeBlockAndName(codepoint, blockName, MAX_PATH, name, namesize);
}

int NameBlocks::getUnicodeBlockAndName(const int codepoint, char* block, int blocksize, char* name, int namesize) {
   string blockName{ findBlock(codepoint) };

   if (blockName.empty()) {
      snprintf(block, blocksize, "%s", NA);
      snprintf(name, namesize, "%s", NA);
      return 0;
   }

   snprintf(block, blocksize, "%s", blockName.c_str());

   char cp[10]{};
   snprintf(cp, 10, (codepoint > 0xFFFF ? "%06x" : "%04x"), static_cast<unsigned int>(codepoint));

   char uName[MAX_PATH]{};
   GetPrivateProfileStringA(blockName.c_str(), cp, NA, uName, MAX_PATH, namesFilePath);

   string codeName{ uName };
   codeName = ((codeName.length() < 24) ? string("            ").substr(0, (24 - codeName.length()) / 2) : "") + codeName;
   snprintf(name, namesize, "%s", codeName.c_str());

   return static_cast<int>(string(name).length());
}
