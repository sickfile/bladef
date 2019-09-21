#include "wndshift.h"

extern mono, BlockClose;
extern DefEditProc;

int CreateControls (HINSTANCE hMainInstance, HWND hMainWindow)
{
	HWND hControl;
	int line1 = 20;
	int col1 = 20;
	int height1 = 25;
	
	CreateWindow ("STATIC", "SOURCE PATH:", WS_CHILD | WS_VISIBLE,
	col1, line1, 110, height1, hMainWindow, 0, hMainInstance, 0);
	CreateWindowEx (WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
	col1 + 120, line1, 310, height1, hMainWindow, (HMENU)IDC_SOURCEPATH, hMainInstance, 0);
	CreateWindow ("BUTTON", "BROWSE", WS_CHILD | WS_VISIBLE,
	col1 + 460, line1, 80, height1, hMainWindow, (HMENU)IDC_BROWSE, hMainInstance, 0);

	line1 += 40;
	CreateWindow ("STATIC", "DEST. PATH:", WS_CHILD | WS_VISIBLE,
	col1, line1, 110, height1, hMainWindow, 0, hMainInstance, 0);
	CreateWindowEx (WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
	col1 + 120, line1, 310, height1, hMainWindow, (HMENU)IDC_DESTPATH, hMainInstance, 0);
	CreateWindow ("BUTTON", "BROWSE", WS_CHILD | WS_VISIBLE,
	col1 + 460, line1, 80, height1, hMainWindow, (HMENU)IDC_BROWSEDEST, hMainInstance, 0);

	line1 += 40;
	CreateWindow ("BUTTON", "MODE", WS_CHILD | WS_VISIBLE | BS_GROUPBOX | BS_CENTER,
	col1, line1, 120, height1 + 75, hMainWindow, 0, hMainInstance, 0);	
	CreateWindow ("BUTTON", "FLAGS", WS_CHILD | WS_VISIBLE | BS_GROUPBOX | BS_CENTER,
	col1 + 130, line1, 270, height1 + 75, hMainWindow, 0, hMainInstance, 0);	
	CreateWindow ("BUTTON", "QUALITY", WS_CHILD | WS_VISIBLE | BS_GROUPBOX | BS_CENTER,
	col1 + 410, line1, 140, height1 + 75, hMainWindow, 0, hMainInstance, 0);	

	line1 += 30;
	hControl = CreateWindow ("BUTTON", "MONO", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON | WS_DISABLED,
	col1 + 20, line1, 80, height1, hMainWindow, (HMENU)IDC_MONO, hMainInstance, 0);
	SendMessage (hControl, BM_SETCHECK, (WPARAM)(mono ? BST_CHECKED : BST_UNCHECKED), 0);
	hControl = CreateWindow ("BUTTON", "COPYRIGHT", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
	col1 + 150, line1, 100, height1, hMainWindow, (HMENU)IDC_COPYRIGHT, hMainInstance, 0);
	SendMessage (hControl, BM_SETCHECK, (WPARAM)BST_UNCHECKED, 0);
	hControl = CreateWindow ("BUTTON", "CRC", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
	col1 + 290, line1, 100, height1, hMainWindow, (HMENU)IDC_CRC, hMainInstance, 0);
	SendMessage (hControl, BM_SETCHECK, (WPARAM)BST_UNCHECKED, 0);
/*	SendMessage (hControl, BM_SETCHECK, (WPARAM)(crc ? BST_CHECKED : BST_UNCHECKED), 0); */
	hControl = CreateWindow ("COMBOBOX", "BITRATE", WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
	col1 + 430, line1, 100, height1 + 140, hMainWindow, (HMENU)IDC_BITRATE, hMainInstance, 0);
	SendMessage (hControl, CB_ADDSTRING, (WPARAM)0, (LPARAM)"96  kbps");
	SendMessage (hControl, CB_ADDSTRING, (WPARAM)0, (LPARAM)"112 kbps");
	SendMessage (hControl, CB_ADDSTRING, (WPARAM)0, (LPARAM)"128 kbps");
	SendMessage (hControl, CB_ADDSTRING, (WPARAM)0, (LPARAM)"160 kbps");
	SendMessage (hControl, CB_ADDSTRING, (WPARAM)0, (LPARAM)"192 kbps");
	SendMessage (hControl, CB_ADDSTRING, (WPARAM)0, (LPARAM)"224 kbps");
	SendMessage (hControl, CB_ADDSTRING, (WPARAM)0, (LPARAM)"256 kbps");
	SendMessage (hControl, CB_SETITEMDATA, (WPARAM)0, (LPARAM)96);
	SendMessage (hControl, CB_SETITEMDATA, (WPARAM)1, (LPARAM)112);
	SendMessage (hControl, CB_SETITEMDATA, (WPARAM)2, (LPARAM)128);
	SendMessage (hControl, CB_SETITEMDATA, (WPARAM)3, (LPARAM)160);
	SendMessage (hControl, CB_SETITEMDATA, (WPARAM)4, (LPARAM)192);
	SendMessage (hControl, CB_SETITEMDATA, (WPARAM)5, (LPARAM)224);
	SendMessage (hControl, CB_SETITEMDATA, (WPARAM)6, (LPARAM)256);
	SendMessage (hControl, CB_SETCURSEL, (WPARAM)3, (LPARAM)0);
	
	line1 += 30;
	hControl = CreateWindow ("BUTTON", "STEREO", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
	col1 + 20, line1, 80, height1, hMainWindow, (HMENU)IDC_STEREO, hMainInstance, 0);
	SendMessage (hControl, BM_SETCHECK, (WPARAM)(mono ? BST_UNCHECKED : BST_CHECKED), 0);
	hControl = CreateWindow ("BUTTON", "ORIGINAL", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
	col1 + 150, line1, 100, height1, hMainWindow, (HMENU)IDC_ORIGINAL, hMainInstance, 0);
	SendMessage (hControl, BM_SETCHECK, (WPARAM)BST_UNCHECKED, 0);
	hControl = CreateWindow ("BUTTON", "PRIVATE", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
	col1 + 290, line1, 100, height1, hMainWindow, (HMENU)IDC_PRIVATE, hMainInstance, 0);
	SendMessage (hControl, BM_SETCHECK, (WPARAM)BST_UNCHECKED, 0);
	
	line1 += 60;
	hControl = CreateWindowEx (0, PROGRESS_CLASS, 0, WS_CHILD | WS_VISIBLE,
	col1, line1, 400, height1, hMainWindow, (HMENU)IDC_ENCODING, hMainInstance, 0);
	SendMessage (hControl, PBM_SETRANGE, 0, MAKELPARAM (0, 100));
	SendMessage (hControl, PBM_SETSTEP, (WPARAM)1, 0);
	CreateWindow ("STATIC", "000/100", WS_CHILD | WS_VISIBLE,
	col1 + 410, line1, 55, height1, hMainWindow, (HMENU)IDC_PROGRES, hMainInstance, 0);
	CreateWindow ("BUTTON", "ENCODE", WS_CHILD | WS_VISIBLE | WS_DISABLED,
	col1 + 470, line1, 80, height1, hMainWindow, (HMENU)IDC_ENCODE, hMainInstance, 0);

	line1 += 40;
	hControl = CreateWindowEx (0, PROGRESS_CLASS, 0, WS_CHILD | WS_VISIBLE,
	col1, line1, 400, height1, hMainWindow, (HMENU)IDC_ALLENCODING, hMainInstance, 0);
	SendMessage (hControl, PBM_SETRANGE, 0, MAKELPARAM (0, 100));
	SendMessage (hControl, PBM_SETSTEP, (WPARAM)1, 0);
	CreateWindow ("STATIC", "", WS_CHILD | WS_VISIBLE,
	col1 + 410, line1, 130, height1, hMainWindow, (HMENU)IDC_TOTALPROGRES, hMainInstance, 0);

	line1 += 40;
	CreateWindow ("LISTBOX", "", WS_CHILD | WS_BORDER | WS_VISIBLE | WS_VSCROLL | LBS_NOTIFY,
	col1, line1, 300, HIWORD (GetDialogBaseUnits ()) * 6, hMainWindow, (HMENU)IDC_LISTA, hMainInstance, 0);
	CreateWindow ("LISTBOX", "", WS_CHILD,
	col1 + 320, line1, 200, HIWORD (GetDialogBaseUnits ()) * 6, hMainWindow, (HMENU)IDC_ULISTA, hMainInstance, 0);
	CreateWindow ("COMBOBOX", "", WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
	col1 + 340, line1, 200, height1 + 140, hMainWindow, (HMENU)IDC_ENCLIST, hMainInstance, 0);
	
	line1 += 40;
	CreateWindow ("STATIC", "PRIORITY", WS_CHILD | WS_VISIBLE,
	col1 + 340, line1, 70, height1, hMainWindow, 0, hMainInstance, 0);
	hControl = CreateWindow ("COMBOBOX", "", WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
	col1 + 420, line1, 120, height1 + 140, hMainWindow, (HMENU)IDC_PRIORITY, hMainInstance, 0);
	SendMessage (hControl, CB_ADDSTRING, (WPARAM)0, (LPARAM)"HIGH");
	SendMessage (hControl, CB_ADDSTRING, (WPARAM)0, (LPARAM)"NORMAL");
	SendMessage (hControl, CB_ADDSTRING, (WPARAM)0, (LPARAM)"LOW");
	SendMessage (hControl, CB_ADDSTRING, (WPARAM)0, (LPARAM)"IDLE");
	SendMessage (hControl, CB_SETITEMDATA, (WPARAM)0, (LPARAM)4);
	SendMessage (hControl, CB_SETITEMDATA, (WPARAM)1, (LPARAM)3);
	SendMessage (hControl, CB_SETITEMDATA, (WPARAM)2, (LPARAM)2);
	SendMessage (hControl, CB_SETITEMDATA, (WPARAM)3, (LPARAM)0);
	SendMessage (hControl, CB_SETCURSEL, (WPARAM)3, (LPARAM)0);

	if (!hControl)
	{
		MessageBox (0, "Creating Controls", "Error", MB_OK);
		return 0;
	}

//	HFONT hFont = 0;
//	hFont = GetStockObject (ANSI_FIXED_FONT);
//	SendMessage (hEdit, WM_SETFONT, (WPARAM)hFont, MAKELPARAM (0, 0));

	return 1;
}


void BladeError (int x)
{
	switch (x)
	{
		case 1:
			MessageBox (0, "Unable to load bladeenc.dll", "ERROR", MB_ICONSTOP);
		break;
		case 2:
		{
			MessageBox (0, "Unable to open .wav file", "Run Time Error", MB_ICONSTOP);
		}
		break;
		case 3:
			MessageBox (0, "Unable to open .mp3 file", "Run Time Error", MB_ICONSTOP);
		break;
		case 4:
			MessageBox (0, "BladeDll init stream error", "Blade Encoder", MB_ICONASTERISK);		
		break;
		case 5:
			MessageBox (0, "Write error", "Run Time Error", MB_ICONASTERISK);		
		break;
		case 6:
			MessageBox (0, "Stream error", "Run Time Error", MB_OK);
		break;
		case 7:
			MessageBox (0, "Write mp3 error", "Run Time Error", MB_ICONASTERISK);		
		break;
		case 8:
			MessageBox (0, "Exit stream failed", "Eroore", MB_OK);
		break;
		case 9:
			MessageBox (0, "Write error", "Eroore", MB_OK);
		break;
		default:
			MessageBox (0, "Unknown BladeDll Error", "Blade Encoder", MB_ICONASTERISK);
	}
}


int ReadDialogErr ()
{

	DWORD Errata = CommDlgExtendedError ();
	switch (Errata)
	{
		case CDERR_FINDRESFAILURE:
			MessageBox (0, "CDERR_FINDRESFAILURE", "GetOpenFileName Error", MB_OK);
		break;
		case CDERR_INITIALIZATION:
			MessageBox (0, "CDERR_INITIALIZATION", "GetOpenFileName Error", MB_OK);
		break;
		case CDERR_LOCKRESFAILURE:
			MessageBox (0, "CDERR_LOCKRESFAILURE", "GetOpenFileName Error", MB_OK);
		break;
		case CDERR_LOADRESFAILURE:
			MessageBox (0, "CDERR_LOADRESFAILURE", "GetOpenFileName Error", MB_OK);
		break;
		case CDERR_LOADSTRFAILURE:
			MessageBox (0, "CDERR_LOADSTRFAILURE", "GetOpenFileName Error", MB_OK);
		break;
		case CDERR_MEMALLOCFAILURE:
			MessageBox (0, "CDERR_MEMALLOCFAILURE", "GetOpenFileName Error", MB_OK);
		break;
		case CDERR_MEMLOCKFAILURE:
			MessageBox (0, "CDERR_LOADRESFAILURE", "GetOpenFileName Error", MB_OK);
		break;
		case CDERR_NOHINSTANCE:
			MessageBox (0, "CDERR_NOHINSTANCE", "GetOpenFileName Error", MB_OK);
		break;
		case CDERR_NOHOOK:
			MessageBox (0, "CDERR_NOHOOK", "GetOpenFileName Error", MB_OK);
		break;
		case CDERR_NOTEMPLATE:
			MessageBox (0, "CDERR_NOTEMPLATE", "GetOpenFileName Error", MB_OK);
		break;
		case CDERR_STRUCTSIZE:
			MessageBox (0, "CDERR_STRUCTSIZE", "GetOpenFileName Error", MB_OK);
		break;
		case FNERR_BUFFERTOOSMALL:
			MessageBox (0, "FNERR_BUFFERTOOSMALL", "GetOpenFileName Error", MB_OK);
		break;
		case FNERR_INVALIDFILENAME:
			MessageBox (0, "FNERR_INVALIDFILENAME", "GetOpenFileName Error", MB_OK);
		break;
		case FNERR_SUBCLASSFAILURE:
			MessageBox (0, "FNERR_SUBCLASSFAILURE", "GetOpenFileName Error", MB_OK);
		break;
		default:
		{
			MessageBox (0, "NO FILE SELECTED", "GetOpenFileName Error", MB_OK);
			return -404;
		}
	}
	return 1;
}


void OnBrowseClick (HWND hwind)
{
	OPENFILENAME LoadFile;
	char wavFile[MAX_PATH];
	strcpy (wavFile, "");
	ZeroMemory (&LoadFile, sizeof (LoadFile));
	LoadFile.lStructSize = 76; //OPENFILENAME_SIZE_VERSION_400;
	LoadFile.hwndOwner = hwind;
	LoadFile.lpstrFilter = "Wave Files (*.wav)\0*.wav\0CD tracks (*.cda)\0*.cda\0";
	LoadFile.lpstrFile = wavFile;
	LoadFile.nMaxFile = MAX_PATH;
	LoadFile.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT;
	if (GetOpenFileName (&LoadFile))
	{
		int i = strlen (wavFile); //the length of: the full path of the selected file or just the path if 2+ files selected
		SetDlgItemText (hwind, IDC_SOURCEPATH, wavFile);
		SendMessage (GetDlgItem (hwind, IDC_ENCODING), PBM_SETPOS, (WPARAM)0, 0);
		SendMessage (GetDlgItem (hwind, IDC_ALLENCODING), PBM_SETPOS, (WPARAM)0, 0);
		SetDlgItemText (hwind, IDC_TOTALPROGRES, "");
		SetDlgItemText (hwind, IDC_PROGRES, "000/100");
		SendMessage (GetDlgItem (hwind, IDC_LISTA), LB_RESETCONTENT, 0, 0);
		SendMessage (GetDlgItem (hwind, IDC_ULISTA), LB_RESETCONTENT, 0, 0);
		if (i < LoadFile.nFileOffset) //the offset of the first file > the length of just the path
		{ // 2+ files selected, wavFile is multiple zero terminated strings and the last string is double zero terminated
			int CharIndex, ItemIndex = 0;
			char sFile[MAX_PATH];
			HWND hList = GetDlgItem (hwind, IDC_LISTA);
			HWND hUList = GetDlgItem (hwind, IDC_ULISTA);
			if ('\\' != wavFile[i-1])
			{ // if the path doesn't end with '\', make it so
				strcpy(sFile, wavFile);
				strcat(sFile, "\\");
				SetDlgItemText (hwind, IDC_SOURCEPATH, sFile);
				SetDlgItemText (hwind, IDC_DESTPATH, sFile);
			}
			else
				SetDlgItemText (hwind, IDC_DESTPATH, wavFile);
			i = LoadFile.nFileOffset;
			while (wavFile[i])
			{
				for (CharIndex = 0; wavFile[i]; i++, CharIndex++) sFile[CharIndex] = wavFile[i];
				sFile[CharIndex] = '\0';
				SendMessage (hUList, LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)sFile); /* to the invisible listbox */
				sFile[CharIndex - 4] = '\0';
				SendMessage (hList, LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)sFile); /* to the user listbox without .wav */
				SendMessage (hList, LB_SETITEMDATA, (WPARAM)ItemIndex, (LPARAM)1); /* mark item data with ONEs */
				ItemIndex++;
				i++;
			}
		}
		else
		{
			i = strlen (wavFile);
			wavFile[i-1] = '3'; wavFile[i-2] = 'p'; wavFile[i-3] = 'm';
			SetDlgItemText (hwind, IDC_DESTPATH, wavFile);
		}
		EnableWindow (GetDlgItem (hwind, IDC_ENCODE), TRUE);
	}
	else
	{
		ReadDialogErr ();
		EnableWindow (GetDlgItem (hwind, IDC_ENCODE), FALSE);
	}
}


void OnBrowseDestClick (HWND hwind)
{
	char mp3File[MAX_PATH];
	OPENFILENAME SaveFile;
	if (SendDlgItemMessage (hwind, IDC_LISTA, LB_GETCOUNT, 0, 0) == 0)
		GetDlgItemText (hwind, IDC_DESTPATH, mp3File, MAX_PATH);
	else strcpy (mp3File, "file.mp3");
	ZeroMemory (&SaveFile, sizeof (SaveFile));
	SaveFile.lStructSize = 76; //OPENFILENAME_SIZE_VERSION_400;
	SaveFile.hwndOwner = hwind;
	SaveFile.lpstrFilter = "mp3 Files (*.mp3)\0*.mp3\0";
	SaveFile.lpstrFile = mp3File;
	SaveFile.nMaxFile = MAX_PATH;
	SaveFile.Flags = OFN_EXPLORER;

	if (GetSaveFileName (&SaveFile))
	{
		if (SendDlgItemMessage (hwind, IDC_LISTA, LB_GETCOUNT, 0, 0) > 0)
		{
			mp3File[SaveFile.nFileOffset] = '\0';
			SetDlgItemText (hwind, IDC_DESTPATH, mp3File);
		}
		else SetDlgItemText (hwind, IDC_DESTPATH, mp3File);
	}
	else
	{
		ReadDialogErr ();
		EnableWindow (GetDlgItem (hwind, IDC_ENCODE), FALSE);
	}
}


void OnListaClick (HWND hwind, WPARAM wParam)
/*
called when the listbox IDC_LISTA is clicked
it's item clicked will be marked by setting it's itemdata to ZERO, all others are ONEs
then slap an editbox on top of the item clicked so you can edit the text of the item
set focus to the editbox and subclass it's window procedure with EditProc, deffined in bladef.c
save the default winapi editbox procedure so the subclass can call the superclass
*/
{
	int i;
	char tFile[MAX_PATH];
	i = SendDlgItemMessage (hwind, IDC_LISTA, LB_GETCURSEL, 0, 0);
	if ((i >= 0) && (HIWORD (wParam) == LBN_SELCHANGE))
	{
		HWND hControl;
		RECT tR;
		SendMessage (GetDlgItem (hwind, IDC_LISTA), LB_GETITEMRECT, (WPARAM)i, (LPARAM)&tR);
		SendDlgItemMessage (hwind, IDC_LISTA, LB_SETITEMDATA, (WPARAM)i, (LPARAM)0);
		hControl = CreateWindow ("EDIT", "", WS_CHILD | WS_BORDER | WS_VISIBLE,
		tR.left + 20, tR.top + 300, tR.right - tR.left, tR.bottom - tR.top, hwind, (HMENU)IDC_MARK, GetModuleHandle (0), 0);
		SendDlgItemMessage (hwind, IDC_LISTA, LB_GETTEXT, (WPARAM)i, (LPARAM)(LPCTSTR)tFile);
		SetDlgItemText (hwind, IDC_MARK, tFile);
		SetFocus (hControl);
		SendMessage (hControl, EM_SETSEL, (WPARAM)0, (LPARAM)-1);
		DefEditProc = SetWindowLong (hControl, GWL_WNDPROC, (LONG)EditProc);
	}
}


void OnMarkLostFocus (HWND hwind, LPARAM lParam)
/*
called when the IDC_MARK editbox losts focus
find the index of the item that was to be edited
it's item data was set to ZERO, returned by SendDlgItemMessage
replace that entry with a new one, text = IDC_MARK editbox
destroy the editbox child window by the HWND in lParam
*/
{
	int ItemIndex = 0;
	char sFile[MAX_PATH];
	HWND hControl = (HWND)lParam;
	while (SendDlgItemMessage (hwind, IDC_LISTA, LB_GETITEMDATA, (WPARAM)ItemIndex, 0)) ItemIndex++;
	GetDlgItemText (hwind, IDC_MARK, sFile, MAX_PATH);
	SendDlgItemMessage (hwind, IDC_LISTA, LB_DELETESTRING, (WPARAM)ItemIndex, 0);
	SendDlgItemMessage (hwind, IDC_LISTA, LB_INSERTSTRING, (WPARAM)ItemIndex, (LPARAM)(LPCTSTR)sFile);
	SendDlgItemMessage (hwind, IDC_LISTA, LB_SETITEMDATA, (WPARAM)ItemIndex, (LPARAM)1);
	SetWindowLong (hControl, GWL_WNDPROC, (LONG)DefEditProc);
	DestroyWindow (hControl);
}


void OnEncodeClick (HWND hwind)
{
	int encoder;
	char mp3File[MAX_PATH];
	char wavFile[MAX_PATH];
	EnableWindow (GetDlgItem (hwind, IDC_ENCODE), FALSE);
	BlockClose = TRUE;
	encoder = SendDlgItemMessage (hwind, IDC_ENCLIST, CB_GETCURSEL, 0, 0);
	encoder = SendDlgItemMessage (hwind, IDC_ENCLIST, CB_GETITEMDATA, (WPARAM)encoder, 0);
	if (SendDlgItemMessage (hwind, IDC_LISTA, LB_GETCOUNT, 0, 0) > 0)
	{
		int i, x;
		char wavTemp[MAX_PATH];
		double TotalPercent, TotalLength = 0, TotalDone = 0; int inwav; /* just to calc TotalLength */
		HWND hList = GetDlgItem (hwind, IDC_LISTA);
		HWND hUList = GetDlgItem (hwind, IDC_ULISTA);
		x = SendMessage (hUList, LB_GETCOUNT, 0, 0);
		i = x - 1;
		while (i != -1) /*count the TotalLength */
		{
			GetDlgItemText (hwind, IDC_SOURCEPATH, wavFile, MAX_PATH);
			SendMessage (hUList, LB_GETTEXT, (WPARAM)i, (LPARAM)(LPCTSTR)wavTemp);
			strcat (wavFile, wavTemp);
			inwav = open (wavFile, O_RDONLY | O_BINARY);
			TotalLength += filelength (inwav);
			SendMessage (hUList, LB_SETITEMDATA, (WPARAM)i, (LPARAM)filelength (inwav));
			close (inwav);
			i--;
		}
		wsprintf (wavTemp, "FINISHED 00 OF %02d", x);
		SetDlgItemText (hwind, IDC_TOTALPROGRES, wavTemp);
		SendDlgItemMessage (hwind, IDC_ALLENCODING, PBM_SETPOS, (WPARAM)0, 0);
		i = 0;
		while (i < x)
		{
			GetDlgItemText (hwind, IDC_SOURCEPATH, wavFile, MAX_PATH);
			GetDlgItemText (hwind, IDC_DESTPATH, mp3File, MAX_PATH);
			SendMessage (hUList, LB_GETTEXT, (WPARAM)i, (LPARAM)(LPCTSTR)wavTemp);
			strcat (wavFile, wavTemp);
			SendMessage (hList, LB_GETTEXT, (WPARAM)i, (LPARAM)(LPCTSTR)wavTemp);
			strcat (mp3File, wavTemp);
			strcat (mp3File, ".mp3");
			SendMessage (GetDlgItem (hwind, IDC_ENCODING), PBM_SETPOS, (WPARAM)0, 0);
			switch (encoder)
			{
				case 1:
				{
					int e = BladeEncoder (hwind, wavFile, mp3File);
					if (e) BladeError (e);
				}
				break;
			}
			TotalDone += SendMessage (hUList, LB_GETITEMDATA, (WPARAM)i, 0);
			TotalPercent = 100 * TotalDone / TotalLength;
			wsprintf (wavTemp, "FINISHED %02d OF %02d", 1+i, x);
			SetDlgItemText (hwind, IDC_TOTALPROGRES, wavTemp);
			SendDlgItemMessage (hwind, IDC_ALLENCODING, PBM_SETPOS, (WPARAM)(int)TotalPercent, 0);
			i++;
		}
	}
	else
	{
		int x;
		GetDlgItemText (hwind, IDC_SOURCEPATH, wavFile, MAX_PATH);
		GetDlgItemText (hwind, IDC_DESTPATH, mp3File, MAX_PATH);
		switch (encoder)
		{
			case 1:
			{
		    	x = BladeEncoder (hwind, wavFile, mp3File);
				if (x) BladeError (x);
			}
			break;
		}
	}
	EnableWindow (GetDlgItem (hwind, IDC_ENCODE), TRUE);
	BlockClose = FALSE;
}


DWORD WINAPI OnEncodeThread (LPVOID MainWindow)

{
	HWND hwind = (HWND)MainWindow;
	OnEncodeClick (hwind);
	return 0;
}
