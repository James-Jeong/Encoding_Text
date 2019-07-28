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
		while (getline(openFile, line)) {
			encoding_type DTResult = detect_encoding(line); // int DTResult
			if (DTResult == 0) cout << cnt << "     " << "ENCODING_UNKNOWN" << endl;
			else if (DTResult == 1) cout << cnt << "     " << "ENCODING_ASCII" << endl;
			else if (DTResult == 2) cout << cnt << "     " << "ENCODING_UTF8" << endl;
			else if (DTResult == 3) cout << cnt << "     " << "ENCODING_UTF16BE" << endl;
			else if (DTResult == 4) cout << cnt << "     " << "ENCODING_UTF16LE" << endl;
			else if (DTResult == 5) cout << cnt << "     " << "ENCODING_UTF32BE" << endl;
			else if (DTResult == 6) cout << cnt << "     " << "ENCODING_UTF32LE" << endl;

			TextEncodingDetect textDetect;
			TextEncodingDetect::Encoding encoding = textDetect.DetectEncoding
			((const unsigned char*)line.c_str(), line.size());

			//if (encoding == TextEncodingDetect::None)
			//	wprintf(L"Binary");
			//else if (encoding == TextEncodingDetect::ASCII)
			//	wprintf(L"ASCII (chars in the 0-127 range)");
			//else 

			//else if (encoding == TextEncodingDetect::UTF8_BOM || encoding == TextEncodingDetect::UTF8_NOBOM)
			//	wprintf(L"UTF-8");
			//else if (encoding == TextEncodingDetect::UTF16_LE_BOM || encoding == TextEncodingDetect::UTF16_LE_NOBOM)
			//	wprintf(L"UTF-16 Little Endian");
			//else if (encoding == TextEncodingDetect::UTF16_BE_BOM || encoding == TextEncodingDetect::UTF16_BE_NOBOM)
			//	wprintf(L"UTF-16 Big Endian");

			/*if (is_valid(line, ENCODING_UTF8)) {
				string CVResult = convert_encoding(line, DTResult, ENCODING_UTF8, false);
				if (!CVResult.empty())
					cout << CVResult << endl;
			}*/
			string MU8 = MBSFromUTF8(line);
			if (encoding == TextEncodingDetect::ANSI) {
				//wprintf(L"ANSI (chars in the range 0-255 range)");
				if (line.size() > 3) {
					cout << cnt << "     " << line << endl;
					writeFile1 << cnt << "     " << line << endl;
				}
			}
			
			if (writeFile1.is_open()) {
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

//char* temp_line = (char*)line.c_str();
			//DWORD* dest = new DWORD[sizeof(temp_line)];
			//UTF8_TO_UTF32(temp_line, sizeof(temp_line), dest, sizeof(dest));
			//cout << temp_line << endl;
			/*wcout << "3 : " << WCSFromMBS(line) << endl; // 3
			cout << "6 : " <<  UTF8FromMBS(line) << endl; // 6

			wcout << "10 : " << WCSFromASCII(line) << endl; // 10
			cout << "14 : " << MBSFromASCII(line) << endl; // 14
			cout << "15 : " << ASCIIFromMBS(line) << endl; // 15
			cout << "17 : " << ASCIIFromUTF8(line) << endl; // 17
			cout << "18 : " << UTF8FromASCII(line) << endl; // 18
			cout << endl << endl;*/

/*// write File
ofstream writeFile(filePath.data());
if (writeFile.is_open()) {
	writeFile << "Hello World!\n";
	writeFile << "This is C++ File Contents.\n";
	writeFile.close();
}*/
