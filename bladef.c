#pragma comment(lib,"user32.lib")
#pragma comment(lib,"comctl32.lib")
#pragma comment(lib,"gdi32.lib")
#pragma comment(lib,"comdlg32.lib")

#define STRICT /* if not set you get problem with WNDPROC defined as FARPROC */

#include "wndshift.h"
#include "bladedll.h"

/* global mp3 flags */
int mono = 0;
BOOL BlockClose = FALSE;

int InitEncoders (HWND);

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

HINSTANCE hBladeInstance;
LONG DefEditProc;


char szClassName[] = "WindowsApp";
//Blade Encoder
//Blade internal errors

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArg, int nCmdShow)

{
    HWND hwind;
    MSG messages;
    WNDCLASS wincl;
    InitCommonControls();

	/*	wincl.cbSize = sizeof (WNDCLASSEX);	used only with WNDCLASSEX*/
    wincl.style = CS_DBLCLKS;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hInstance = hThisInstance;
    wincl.hIcon = LoadIcon(0, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	wincl.lpszMenuName = NULL;
	wincl.lpszClassName = szClassName;
/*	wincl.hIconSm = (HICON)LoadImage(hThisInstance, MAKEINTRESOURCE (IDI_ICON_SM), IMAGE_ICON, 16, 16, 0);	used only with WNDCLASSEX */

    if (!RegisterClass(&wincl))
    {
	    MessageBox (0, "Failed to register", "Fatal error", MB_OK);
		return 0;
	}

	    hwind = CreateWindowEx(
           WS_EX_WINDOWEDGE, szClassName, "BLADE FrontEnd",
           WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME,
           CW_USEDEFAULT, CW_USEDEFAULT, 600, 425, HWND_DESKTOP,
           NULL, hThisInstance, NULL);

    ShowWindow (hwind, nCmdShow);

        while(GetMessage(&messages, NULL, 0, 0))
    {
           TranslateMessage(&messages);
           DispatchMessage(&messages);
    }

    return messages.wParam;
}

/*--------------------------------------------------------------------------
New subclassed EditBox Window Procedure

when you click on the listbox IDC_LISTA you get the ability to edit the list item
an editbox IDC_MARK is placed on top of the selectd list item
this is the window procedure of that editbox
detects hitting ENTER key and sets the focus from the editbox to the listbox

then the main window procedure is notified by the listbox that it got focus
executing the subrutine OnMarkLostFocus to kill the editbox

if there is no keydown to process, call the default winapi procedure for editboxes
*/
LRESULT CALLBACK EditProc (HWND edwnd, UINT edmsg, WPARAM wEParam, LPARAM lEParam)
{
	if ((edmsg == WM_KEYDOWN) && ((int)wEParam == VK_RETURN))
	{
		HWND hControl;
		hControl = GetDlgItem (GetParent (edwnd), IDC_LISTA);
		SetFocus (hControl);
	}
	return CallWindowProc ((WNDPROC)DefEditProc, edwnd, edmsg, wEParam, lEParam);
}
/*------------------------------------------------------------------------*/


LRESULT CALLBACK WindowProcedure(HWND hwind, UINT messag, WPARAM wParam, LPARAM lParam)
{
	switch (messag)
    {
		case WM_COMMAND:
	    {
	    	switch (LOWORD (wParam)) /* the identifier of the child window that sends the message */
	    	{
		    	case IDC_MARK:
		    	{
			    	if (HIWORD (wParam) == EN_KILLFOCUS) OnMarkLostFocus (hwind, lParam);
		    	} /* HIWORD (wParam) the notification message being sent to our main window */
		    	break;
		    	case IDC_BROWSE:
		    		OnBrowseClick (hwind);
		    	break;
		    	case IDC_BROWSEDEST:
		    		OnBrowseDestClick (hwind);
		    	break;
		    	case IDC_ENCODE:
		    	{
			    	int Priority;
		    		HINSTANCE hThread;
			    	Priority = SendDlgItemMessage (hwind, IDC_PRIORITY, CB_GETCURSEL, 0, 0);
			    	Priority = SendDlgItemMessage (hwind, IDC_PRIORITY, CB_GETITEMDATA, (WPARAM)Priority, 0);
		    		hThread = CreateThread (0, 0, &OnEncodeThread, (LPVOID)hwind, 0, 0);
		    		switch (Priority)
		    		{
			    		case 4 : Priority = THREAD_PRIORITY_ABOVE_NORMAL;
			    		break;
			    		case 3 : Priority = THREAD_PRIORITY_NORMAL;
			    		break;
			    		case 2 : Priority = THREAD_PRIORITY_BELOW_NORMAL;
			    		break;
			    		default : Priority = THREAD_PRIORITY_IDLE;
		    		}
		    		SetThreadPriority (hThread, Priority);
		    		CloseHandle (hThread);
	    		}
		    	break;
		    	case IDC_LISTA:
					OnListaClick (hwind, wParam);
		    	break;
		    	case IDC_MONO:
		    	{
			    	SendMessage (GetDlgItem (hwind, IDC_MONO), (UINT)BM_SETCHECK, (WPARAM)BST_CHECKED, 0);
			    	SendMessage (GetDlgItem (hwind, IDC_STEREO), (UINT)BM_SETCHECK, (WPARAM)BST_UNCHECKED, 0);
			    	mono = 1;
		    	}
		    	break;
		    	case IDC_STEREO:
		    	{
			    	SendMessage (GetDlgItem (hwind, IDC_STEREO), (UINT)BM_SETCHECK, (WPARAM)BST_CHECKED, 0);
			    	SendMessage (GetDlgItem (hwind, IDC_MONO), (UINT)BM_SETCHECK, (WPARAM)BST_UNCHECKED, 0);
			    	mono = 0;
		    	}
		    	break;
		    	case IDC_COPYRIGHT:
		    	{
/*			    	copyright = copyright ? 0 : 1; */
		    	}
		    	break;
	    	}
	    }
	    break;
	    case WM_CTLCOLORSTATIC:
			SetBkColor ((HDC)wParam, GetSysColor (COLOR_BTNFACE));
			return (LRESULT)CreateSolidBrush (GetSysColor (COLOR_BTNFACE));
		case WM_DESTROY:
			PostQuitMessage(0);
		break;
	    case WM_CREATE:
	    {
		    if (!CreateControls (GetModuleHandle (0), hwind))
		    	PostQuitMessage (0);
		    InitEncoders (hwind);
	    }
	    break;
		default:
		{
			if ((messag == WM_SYSCOMMAND) && (wParam == SC_CLOSE))
			{
				if (BlockClose) return 0;
			}
			
			return DefWindowProc(hwind, messag, wParam, lParam);
		}
    }
    return 0;
}

/*--------BLADE ENCODER---------------------------------------------------*/

int BladeEncoder (HWND hwind, char *wavName, char *mp3Name)

{
	BEINITSTREAM beInitStream = (BEINITSTREAM) GetProcAddress(hBladeInstance, TEXT_BEINITSTREAM);
	BEENCODECHUNK beEncodeChunk = (BEENCODECHUNK) GetProcAddress(hBladeInstance, TEXT_BEENCODECHUNK);
	BEDEINITSTREAM beDeinitStream = (BEDEINITSTREAM) GetProcAddress(hBladeInstance, TEXT_BEDEINITSTREAM);
	BECLOSESTREAM beCloseStream	= (BECLOSESTREAM) GetProcAddress(hBladeInstance, TEXT_BECLOSESTREAM);
	BEVERSION beVersion = (BEVERSION) GetProcAddress(hBladeInstance, TEXT_BEVERSION);
	int inwav, outmp3;
	
	inwav = open (wavName, O_RDONLY | O_BINARY); /* #include <fcntl.h> */
	if (inwav == -1) return 2;
	outmp3 = open (mp3Name, O_WRONLY | O_BINARY | O_TRUNC | O_CREAT, S_IWRITE); /* #include <sys/stat.h> */
	if (outmp3 != -1)
	{
		DWORD Samples, mp3Buffer;
		long bitrate;
		HBE_STREAM beStream;
		BE_ERR err;
		BE_CONFIG BeConfig;

		bitrate = SendDlgItemMessage (hwind, IDC_BITRATE, CB_GETCURSEL, 0, 0);
		bitrate = SendDlgItemMessage (hwind, IDC_BITRATE, CB_GETITEMDATA, (WPARAM)bitrate, 0);
		bitrate = bitrate != CB_ERR ? bitrate : 160;

		BeConfig.dwConfig = BE_CONFIG_MP3;
		BeConfig.format.mp3.dwSampleRate	= 44100;
		BeConfig.format.mp3.byMode			= mono ? BE_MP3_MODE_MONO : BE_MP3_MODE_STEREO;
		BeConfig.format.mp3.wBitrate		= bitrate;
		BeConfig.format.mp3.bCopyright		= (SendDlgItemMessage (hwind, IDC_COPYRIGHT, BM_GETCHECK, 0, 0) == BST_CHECKED) ? TRUE : FALSE;
		BeConfig.format.mp3.bCRC			= (SendDlgItemMessage (hwind, IDC_CRC, BM_GETCHECK, 0, 0) == BST_CHECKED) ? TRUE : FALSE;
		BeConfig.format.mp3.bOriginal		= (SendDlgItemMessage (hwind, IDC_ORIGINAL, BM_GETCHECK, 0, 0) == BST_CHECKED) ? TRUE : FALSE;
		BeConfig.format.mp3.bPrivate		= (SendDlgItemMessage (hwind, IDC_PRIVATE, BM_GETCHECK, 0, 0) == BST_CHECKED) ? TRUE : FALSE;

		err = beInitStream(&BeConfig, &Samples, &mp3Buffer, &beStream);
		if (err == BE_ERR_SUCCESSFUL)
		{
			int grerror = 0;
			PBYTE pMP3Buffer = (PBYTE)malloc (mp3Buffer);
			PSHORT pBuffer = (PSHORT)malloc (sizeof (Samples) * Samples);
			DWORD length = filelength(inwav);
			DWORD done = 0;
			DWORD dwWrite;
			DWORD toread;
			DWORD towrite;
			MSG qmsg;
			float encoding = 100 * (float)done/(float)length;
			setbuf (stdout, 0);
			/* start encoding */
			while (done < length)
			{
				if (done + Samples * 2 < length)
				{
					toread = Samples * 2;
				}
				else
				{
					toread = length - done;
				}
				if (read (inwav, pBuffer, toread) == -1)
				{
					grerror = 5;
					break;
				}		 
				err = beEncodeChunk (beStream, toread/2, pBuffer, pMP3Buffer, &towrite);
				if (err != BE_ERR_SUCCESSFUL)
				{
					grerror = 6;
					break;
				}
				if (write (outmp3, pMP3Buffer, towrite) == -1)
				{
					grerror = 7;
					break;
				}
				done += toread;
				if ((100 * (float)done/(float)length) - encoding > 3) /* step react on 3*/
				{
					char outstr[10];
					float t = 100 * (float)done/(float)length - encoding;
					SendMessage (GetDlgItem (hwind, IDC_ENCODING), PBM_DELTAPOS, (WPARAM)(int)t, 0);
					encoding = 100 * (float)done/(float)length;
					sprintf (outstr, "%03d/100", (int)encoding);
					SetDlgItemText (hwind, IDC_PROGRES, outstr);
				}
			}
			if (grerror) goto onerror;
			SendMessage (GetDlgItem (hwind, IDC_ENCODING), PBM_SETPOS, (WPARAM)100, 0);
			SetDlgItemText (hwind, IDC_PROGRES, "100/100");
			err = beDeinitStream(beStream, pMP3Buffer, &dwWrite);
			if (err != BE_ERR_SUCCESSFUL)
			{
				grerror = 8;
				goto onerror;
			}
			if(dwWrite)
			{
				if (write (outmp3, pMP3Buffer, dwWrite) == -1)
					grerror = 9;
			}
onerror:
			beCloseStream(beStream);
			free (pMP3Buffer); free (pBuffer);
			close (inwav); close (outmp3);
			if (grerror) return grerror;
		}
		else
		{
			close (inwav); close (outmp3);
			return 4;
		}
	}
	else
	{
		close (inwav);
		return 3;
	}
return 0;
}

int InitEncoders (HWND hwind)
{
	int x = 0;
	HWND hControl = GetDlgItem (hwind, IDC_ENCLIST);
	hBladeInstance = LoadLibrary ("bladeenc.dll");
	if (hBladeInstance)
	{
		x = SendMessage (hControl, CB_ADDSTRING, (WPARAM)0, (LPARAM)"Blade Encoder");
		SendMessage (hControl, CB_SETITEMDATA, (WPARAM)x, (LPARAM)1);
	}

	if (SendMessage (hControl, CB_GETCOUNT, 0, 0))
	{
		SendMessage (hControl, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
	}
	else
	{
		PostQuitMessage (0);
	}
	return x;
}
