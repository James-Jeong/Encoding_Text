#include <iostream>
#include <fstream>
#include <string>

#include "Define.h"
#include "Type.h"
#include "UnicodeEncoding.h"
#include "Unicode.h"
#include "utf.h"
#include "unicode_data.h"
#include "text_encoding_detect.h"

using namespace AutoIt;
using namespace Common;
using namespace core;
using namespace std;
using namespace utf;

int main()
{
	string filePath = "test1.txt";
	int cnt = 1;

	// read File
	ifstream openFile(filePath.data());
	ofstream writeFile1("Result_text.txt");
	if (openFile.is_open()) {
		string line;
		string MU8;

		TextEncodingDetect textDetect;
		TextEncodingDetect::Encoding encoding = textDetect.DetectEncoding
		((const unsigned char*)line.c_str(), line.size());

		while (getline(openFile, line)) {
			encoding_type DTResult = detect_encoding(line); // int DTResult
			if (DTResult == 0) cout << cnt << "     " << "ENCODING_UNKNOWN" << endl;
			else if (DTResult == 1) cout << cnt << "     " << "ENCODING_ASCII" << endl;
			else if (DTResult == 2) cout << cnt << "     " << "ENCODING_UTF8" << endl;
			else if (DTResult == 3) cout << cnt << "     " << "ENCODING_UTF16BE" << endl;
			else if (DTResult == 4) cout << cnt << "     " << "ENCODING_UTF16LE" << endl;
			else if (DTResult == 5) cout << cnt << "     " << "ENCODING_UTF32BE" << endl;
			else if (DTResult == 6) cout << cnt << "     " << "ENCODING_UTF32LE" << endl;

			//else if (encoding == TextEncodingDetect::UTF16_LE_BOM || encoding == TextEncodingDetect::UTF16_LE_NOBOM)
			//	wprintf(L"UTF-16 Little Endian");
			//else if (encoding == TextEncodingDetect::UTF16_BE_BOM || encoding == TextEncodingDetect::UTF16_BE_NOBOM)
			//	wprintf(L"UTF-16 Big Endian");
			
			if (encoding == TextEncodingDetect::ANSI) {
				//wprintf(L"ANSI (chars in the range 0-255 range)");
				if (line.size() > 3) {
					cout << cnt << "     " << line << endl;
					writeFile1 << cnt << "     " << line << endl;
				}
			}
			
			if (encoding == TextEncodingDetect::UTF8_BOM || encoding == TextEncodingDetect::UTF8_NOBOM) MU8 = MBSFromUTF8(line);
			if (writeFile1.is_open() && !MU8.empty()) {
				if (MU8.size() > 3) {
					cout << cnt << "     " << MU8 << endl; // 11
					writeFile1 << cnt << "     " << MU8 << endl;
				}
			}
			cnt++;
		}
		openFile.close();
		writeFile1.close();
	}
	return 0;
}