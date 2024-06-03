#define _CRT_SECURE_NO_WARNINGS﻿
#include<Windows.h>		//<file> - компилятор будет искать file в системных каталогах Visual Studio
#include<CommCtrl.h>
#include"resource.h"	//"file" - компилятор будет искать file сначала в каталоге с проектом, а потом в системных каталогах Visual Studio
#include<cstdio>
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc, 0);
	return 0;
}
//ПРоцедура окна - это самая обычная функция, которая вызывается при запуске окна
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//Все принемаемые параметры - это числовые значения длинной 4 байта
	//HWND - HAndler to Windows(обработчик окна) - это числою которое индентифецирует окно
	//Любые обращения к окну можно выполнить тольок черерез его обработчик
	//uWsg(Message) - сообщения, которое отпровляется окну
	//wParam, IParam - параметры сообщения. Они ещё делятся на LOWORD и HIWORD
	//LOWORD - это младшее слово
	//HIWORD - старшее слово
	//WORD(Слово) - это два Байта
	int a = 2;
	{
		int a = 2;
	}
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hUpDown = GetDlgItem(hwnd, IDC_SPIN_PREFIX);
		// Функция GetDlgItem() получает HWND элемента итерфейса по его ID
		SendMessage(hUpDown, UDM_SETRANGE32, 0, 32);
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))//может понять что делает пользователь
		{
		case IDC_IPADDRESS:
		{
			CONST INT SIZE = 256;
			CHAR sz_info[SIZE]{};
			HWND hIPaddress = GetDlgItem(hwnd, IDC_IPADDRESS);
			HWND hStaticInfo = GetDlgItem(hwnd, IDC_STATIC_INFO);
			
			//EN_ - Edit notification(уведомление)
			if (HIWORD(wParam) == EN_CHANGE)
			{   
				//BYTE = 8 bit; CHAR
				//WORD = 2 Bytes(16 bit); SHORT
				//Dword - (Double Word - Двойное слово) = 4 Bytes(32 bit); INT
				//QWord - (Quad Word - Четверённое слово) = 8 Bytes(64 bit); LONG LONG
				//TBYTE (TEN Bytes - Десять байт) = 80 bit; 
				//DQWORD (Double Quad Word - Двайное учетверённое слово) = 128 bit
				DWORD dw_address;
				SendMessage(hIPaddress, IPM_GETADDRESS, 0, (LPARAM) & dw_address);
				INT first = FIRST_IPADDRESS(dw_address);
				INT second = SECOND_IPADDRESS(dw_address);
				INT third = THIRD_IPADDRESS(dw_address);
				INT forth = FOURTH_IPADDRESS(dw_address);
				sprintf_s(sz_info,SIZE, "Info:\nFirst: %i, Second %i, Third: %i, Forth: %i", first, second, third, forth);
				SendMessage(hStaticInfo,WM_SETTEXT,0,(LPARAM)sz_info);
			}
		}break;
		case IDOK:MessageBox(hwnd, "Была нажата кнопка ОК", "Info", MB_OK | MB_ICONEXCLAMATION); break;// MB_OK | MB_ICONEXCLAMATION - MB_OK or MB_ICONEXCLAMATION 
			// | - побитовое 'or' ; || - логическое 'or'
		case IDCANCEL:  EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}
	return FALSE;
}