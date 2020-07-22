// dllmain.cpp : Определяет точку входа для приложения DLL.
#include <Windows.h>
#include <sstream> 
#include <fstream>
#include <string>
#include <thread>

inline std::string rjust(std::string text, size_t width, char fillchar = '0') {
	if (text.size() >= width) {
		return text;
	}
	std::string returnString = text;
	returnString.insert(0, width - text.size(), fillchar);
	return returnString;
}

inline void myLog(std::string text) {
	
	//std::wstring messageW(text.begin(), text.end());
	//WCHAR_T* wsData = messageW.data();
	std::string LOG_FILE_PATH = "E:/1LOG/log.txt";
	std::ofstream outfile;
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


/*
INT APIENTRY DllMain(HMODULE hDLL, DWORD Reason, LPVOID Reserved) {

	FILE* file;
	fopen_s(&file, "C:\\temp.txt", "a+");

	switch (Reason) {
	case DLL_PROCESS_ATTACH:
		fprintf(file, "DLL attach function called.\n");
		break;
	case DLL_PROCESS_DETACH:
		fprintf(file, "DLL detach function called.\n");
		break;
	case DLL_THREAD_ATTACH:
		fprintf(file, "DLL thread attach function called.\n");
		break;
	case DLL_THREAD_DETACH:
		fprintf(file, "DLL thread detach function called.\n");
		break;
	}

	fclose(file);

	return TRUE;
}
*/

void foreverThread() {
	while (1) {
		myLog("I am alive.");
		Sleep(5000);
	}
}
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
	myLog("start.");
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }

	std::thread t1(foreverThread);
	t1.detach();
    return TRUE;
}

