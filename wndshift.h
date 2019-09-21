#pragma once

#include <windows.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <commctrl.h>


#define IDI_ICON_SM 101
#define IDI_ICON_LG 102
#define	IDC_PATH 1001
#define IDC_BROWSE 1002
#define IDC_ENCODE 1003
#define IDC_ENCODING 1004
#define IDC_PROGRES 1005
#define IDC_MARK 1006	/* the editbox slapped over the listbox's edited item */
#define IDC_MONO 1007
#define IDC_STEREO 1008
#define IDC_COPYRIGHT 1009
#define IDC_CRC 1010
#define IDC_PRIVATE 1011
#define IDC_ORIGINAL 1012
#define IDC_BITRATE 1013
#define IDC_DESTPATH 1014
#define IDC_SOURCEPATH 1015
#define IDC_BROWSEDEST 1016
#define IDC_LISTA 1017
#define IDC_ULISTA 1018
#define IDC_ENCLIST 1019
#define IDC_ALLENCODING 1020
#define IDC_TOTALPROGRES 1021
#define IDC_PRIORITY 1022

int CreateControls (HINSTANCE, HWND);
void BladeError (int);
int ReadDialogErr (void);
LRESULT CALLBACK EditProc (HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI OnEncodeThread (LPVOID);
int BladeEncoder (HWND, char *, char *);

void OnBrowseClick (HWND);
void OnBrowseDestClick (HWND);
void OnListaClick (HWND, WPARAM);
void OnMarkLostFocus (HWND, LPARAM);
void OnEncodeClick (HWND);
