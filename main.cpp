#include "stdafx.h"

using namespace AutoIt;
using namespace Common;
using namespace core;
using namespace std;
using namespace utf;

int main()
{
	/*char line[100];

	FILE* file = fopen("test1.txt", "r");
	ReadBOM(file);
	while (fscanf(file, "%s", line)) {
		cout << line << endl;
	}

	fclose(file);
	*/

	string filePath = "test1.txt";
	int cnt = 1;
	// read File
	ifstream openFile(filePath.data());
	ofstream writeFile1("Result_text.txt");
	if (openFile.is_open()) {
		string line;
		string MU8;
		string MASCII;
		string MU16;
		string MU32;

		TextEncodingDetect textDetect;
		TextEncodingDetect::Encoding encoding = textDetect.DetectEncoding
		((const unsigned char*)(TEXT(line)).c_str(), line.size());

		while (getline(openFile, line)) {
			//line.erase(remove(line.begin(), line.end(), NULL), line.end()); // erase null character in string line
			encoding_type DTResult = detect_encoding(TEXT(line)); // int DTResult
			//cout << cnt << " = " << textDetect.CheckBOM((const unsigned char*)line.c_str(), line.size()) << endl;

			if (encoding == TextEncodingDetect::ANSI) {
				if (line.size() > 3) {
					cout << cnt << "     " << TEXT(line) << endl;
					writeFile1 << cnt << "     " << TEXT(line) << endl;
				}
			}
			if (encoding == TextEncodingDetect::ASCII) {
				if (DTResult == ENCODING_UTF8) { //encoding == TextEncodingDetect::UTF8_BOM || encoding == TextEncodingDetect::UTF8_NOBOM
					MU8 = MBSFromUTF8(TEXT(line));
					if (writeFile1.is_open() && !MU8.empty()) {
						if (MU8.size() > 3) {
							cout << cnt << "     " << MU8 << endl;
							writeFile1 << cnt << "     " << MU8 << endl;
						}
					}
				}
				else if (DTResult == ENCODING_UTF16LE || DTResult == ENCODING_UTF16BE) {
					MU16 = MBSFromUTF16((const WORD*)WORDFrom(TEXT(line)), line.size());
					if (writeFile1.is_open() && !MU16.empty()) {
						if (MU8.size() > 3) {
							cout << cnt << "     " << MU16 << endl;
							writeFile1 << cnt << "     " << MU16 << endl;
						}
					}
				}
				else if (DTResult == ENCODING_UTF32LE || DTResult == ENCODING_UTF32BE) {
					MU32 = MBSFromUTF32((const DWORD*)DWORDFrom(TEXT(line)), line.size());
					if (writeFile1.is_open() && !MU32.empty()) {
						if (MU8.size() > 3) {
							cout << cnt << "     " << MU32 << endl;
							writeFile1 << cnt << "     " << MU32 << endl;
						}
					}
				}
				else {
					MASCII = MBSFromASCII(TEXT(line));
					if (writeFile1.is_open() && !MASCII.empty()) {
						if (MASCII.size() > 3) {
							cout << cnt << "     " << MASCII << endl;
							writeFile1 << cnt << "     " << MASCII << endl;
						}
					}
				}
			}

			

			cnt++;
		}
		openFile.close();
		writeFile1.close();
	}
	return 0;
}
