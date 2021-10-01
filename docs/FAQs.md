## Frequently Asked Questions

#### 1. Why does the *GotoLineCol* plugin claim to support only  documents with ANSI and UTF-8 encodings? Why not UCS-2 documents?
Internally, the GotoLineCol plugin supports just the files in ANSI and UTF-8 encodings. The plugin is also able to support files encoded in UCS-2, but only by extension thanks to the seamless conversion of UCS-2 files into UTF-8 in the buffer memory during the file load in Notepad++.

##### Additional Info
The Scintilla core component used by Notepad++ only supports <a href="https://www.scintilla.org/ScintillaDoc.html#SCI_SETCODEPAGE">UTF-8 in the Unicode mode</a>.

When Notepad++ loads a UCS-2 file, it seamlessly converts the UCS-2 character stream into UTF-8, and only then loads it into the Scintilla memory buffer.

You can see this in action by opening an actual file, saved in one of the UCS-2 encodings, into Notepad++. For example, you could load the README.MD file found in this repo into Notepad++; change its encoding from its current UTF-8 into one of the UCS-2 encodings; and save the changed file into your local file system; note its file size in the File Explorer; reopen the file in Notepad++; and check the reported byte length in the status bar in Notepad++.

With the version of the README file at the time of this writing, the file length in the original UTF-8 version was 7,222 bytes; and the corresponding length for the UCS-2 file version was 14,438 bytes [*Not exactly double in size in the UCS-2 version since the smart quotes present in the README file require 3 bytes each in the UTF-8 encoding versus just two bytes in the UCS-2 encoding*]. However, when the UCS-2 version of README file is reopened in Notepad++, the reported byte length will be only 7,222 – as if the file is still encoded in UTF-8.


#### 2. My document has accented Latin characters. But the *GotoLineCol* is not displaying the UTF-8 byte sequence and the Unicode code point for it.

Check the current encoding setting for the file (under menu item *Encoding* in Notepad++). If the current encoding is *ANSI*, the plugin will ony display the ANSI byte value.
