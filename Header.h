#pragma once
#include <Windows.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
void start();
int Init(HINSTANCE hInstance);
LRESULT CALLBACK MyWndProc(HWND, UINT, UINT, LONG);
LRESULT CALLBACK MyLowLevelKeyBoardProc(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK workWith_WM_KEYDOWN(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK workWith_WM_KEYUP(int nCode, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK workWith_WM_SYSKEYDOWN(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK workWith_WM_SYSKEYUP(int nCode, WPARAM wParam, LPARAM lParam);

void sendInputText(std::string text);

inline std::string LOG_FILE_PATH = "E:/log.txt";

inline std::string rjust(std::string text, size_t width, char fillchar = '0') {
	if (text.size() >= width) {
		return text;
	}
	std::string returnString = text;
	returnString.insert(0, width - text.size(), fillchar);
	return returnString;
}

inline void myLog(std::string text) {



	SYSTEMTIME st;
	GetLocalTime(&st);
	std::stringstream buf;
	buf << st.wYear << "." <<
		rjust(std::to_string(st.wMonth), 2) << "." <<
		rjust(std::to_string(st.wDay), 2) << " " <<
		rjust(std::to_string(st.wHour), 2) << ":" <<
		rjust(std::to_string(st.wMinute), 2) << ":" <<
		rjust(std::to_string(st.wSecond), 2) << "_" <<
		rjust(std::to_string(st.wMilliseconds), 3);
	auto now = buf.str();
	std::ofstream logfile;
	logfile.open(LOG_FILE_PATH, std::ios_base::app);
	logfile << now << " | " << text << std::endl;
	logfile.close();

}