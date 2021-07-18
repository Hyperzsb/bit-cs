.386
.model flat,stdcall
option casemap:none

include msvcrt.inc
includelib msvcrt.lib
include user32.inc
includelib user32.lib
include kernel32.inc
includelib kernel32.lib
include windows.inc
includelib masm32.lib
include masm32.inc
includelib gdi32.lib
include gdi32.inc

MAX_LINE_LENGTH						equ		1024

; Const value
.const
gc_szWindowClass					byte	"win32app", 0
gc_szWindowTitle					byte	"Compare Two Files", 0
gc_szClassButton					byte	"BUTTON", 0
gc_szClassEdit						byte	"EDIT", 0
gc_szClassStatic					byte	"STATIC", 0
gc_szFileMode						byte	"r", 0
gc_szErrorTypeWindow				byte	"Window Error", 0
gc_szErrorTypeFile					byte	"File Error", 0
gc_szInfoTypeFile					byte	"Success", 0
gc_szRegisterFailureMsg				byte	"Unable to register class, please try again later", 0
gc_szCreateFailureMsg				byte	"Unable to create window, please try again later", 0
gc_szSourceFileEditTitle			byte	"Source file's path:", 0
gc_szDestinationFileEditTitle		byte	"Destination file's path:", 0
gc_szOutputStaticTitle				byte	"Result:", 0
gc_szCompareButtonText				byte	"Do Compare", 0
gc_szOpenSourceFileFailureMsg		byte	"Unable to open source file, please check your input", 0
gc_szOpenDestinationFileFailureMsg	byte	"Unable to open destination file, please check your input", 0
; Global variables
.data
; Handles for windows and widgets
g_hInstance							dword	0
g_hWindow							dword	0
g_hSourceFileEdit					dword	0
g_hDestinationFileEdit				dword	0
g_hCompareButton					dword	0
g_hOutputStatic						dword	0
; Files paths
; C:\Users\Hyperzsb\Desktop\1.txt
g_szSourceFilePath					byte	MAX_PATH dup(0)
; C:\Users\Hyperzsb\Desktop\2.txt
g_szDestinationFilePath				byte	MAX_PATH dup(0)
g_nSourceFileStatus					dword	0
g_nDestinationFileStatus			dword	0
; Differences counter
g_nCounter							dword	0
g_nLineNumber						dword	1
; File lines
g_szSourceLine						byte	MAX_LINE_LENGTH dup(0)
g_szDestinationLine					byte	MAX_LINE_LENGTH dup(0)
; Output msg format
g_szOutput							byte	1048576 dup(0)
g_szOutputTemp						byte	4096 dup(0)
g_szOutputTempFormat				byte	"No.%d: ", 0ah, "Line %d -> %s <-> %s", 0ah, 0
g_szCompareFinishedMsg				byte	128 dup(0)
g_szCompareFinishedMsgFormat		byte	"Comparsion finished, find %d differences", 0
g_szOutB							byte	"%s", 0ah, 0

.code
Compare proc
		LOCAL		pSourceFile:ptr FILE
		LOCAL		pDestinationFile:ptr FILE
	; Initialize global variables
	mov			g_nSourceFileStatus, 0
	mov			g_nDestinationFileStatus, 0
	mov			g_nCounter, 0
	mov			g_nLineNumber, 1
	invoke		crt_memset, offset g_szOutput, 0, sizeof g_szOutput
	; Open files
	invoke		crt_fopen, offset g_szSourceFilePath, offset gc_szFileMode
	mov			pSourceFile, eax
	invoke		crt_fopen, offset g_szDestinationFilePath, offset gc_szFileMode
	mov			pDestinationFile, eax
CheckSourceFileLabel:
	cmp			pSourceFile, 0
	jne			SourceFileValidLabel
	mov			g_nSourceFileStatus, 1
	invoke		MessageBox, NULL, offset gc_szOpenSourceFileFailureMsg, offset gc_szErrorTypeFile, MB_ICONERROR
	jmp			CheckDestinationFileLabel
SourceFileValidLabel:
	mov			g_nSourceFileStatus, 0
CheckDestinationFileLabel:
	cmp			pDestinationFile, 0
	jne			DestinatioFileValidLabel
	mov			g_nDestinationFileStatus, 1
	invoke		MessageBox, NULL, offset gc_szOpenDestinationFileFailureMsg, offset gc_szErrorTypeFile, MB_ICONERROR
	jmp			CheckFileLabel
DestinatioFileValidLabel:
	mov			g_nDestinationFileStatus, 0
CheckFileLabel:
	mov			eax, g_nSourceFileStatus
	or			eax, g_nDestinationFileStatus
	cmp			eax, 1
	je			ReturnLabel
CompareLoop:
	invoke		crt_feof, pSourceFile
	mov			ecx, eax
	invoke		crt_feof, pDestinationFile
	and			ecx, eax
	cmp			ecx, 0
	jne			CompareFinishedLabel
	invoke		crt_memset, offset g_szSourceLine, 0, sizeof g_szSourceLine
	invoke		crt_memset, offset g_szDestinationLine, 0, sizeof g_szDestinationLine
	invoke		crt_fgets, offset g_szSourceLine, 1024, pSourceFile
	invoke		crt_strlen, offset g_szSourceLine
	mov			g_szSourceLine[eax - 1], 0
	invoke		crt_fgets, offset g_szDestinationLine, 1024, pDestinationFile
	invoke		crt_strlen, offset g_szDestinationLine
	mov			g_szDestinationLine[eax - 1], 0
	invoke		crt_strcmp, offset g_szSourceLine, offset g_szDestinationLine
	cmp			eax, 0
	je			CompareLoopEnd
	add			g_nCounter, 1
	invoke		crt_sprintf, offset g_szOutputTemp, offset g_szOutputTempFormat, g_nCounter, g_nLineNumber, offset g_szSourceLine, offset g_szDestinationLine
	invoke		crt_strcat, offset g_szOutput, offset g_szOutputTemp
	invoke		SetWindowTextA, g_hOutputStatic, offset g_szOutput
CompareLoopEnd:
	add			g_nLineNumber, 1
	jmp			CompareLoop
CompareFinishedLabel:
	invoke		SetWindowTextA, g_hOutputStatic, offset g_szOutput
	invoke		crt_sprintf, offset g_szCompareFinishedMsg, offset g_szCompareFinishedMsgFormat, g_nCounter
	invoke		MessageBox, NULL, offset g_szCompareFinishedMsg, offset gc_szInfoTypeFile, MB_ICONINFORMATION
ReturnLabel:
	xor			eax, eax
	ret
Compare endp

; WinMain function
WinMain proc		hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPSTR, nCmdShow:DWORD
		LOCAL		wcex:WNDCLASSEX
		LOCAL		msg:MSG
	; Initialize wcex for creating window
	mov			wcex.cbSize, sizeof WNDCLASSEX
	mov			wcex.style, CS_HREDRAW or CS_VREDRAW
	mov			wcex.lpfnWndProc, offset WndProc
	mov			wcex.cbClsExtra, 0
	mov			wcex.cbWndExtra, 0
	push		hInstance
	pop			wcex.hInstance
	; Set icon of window
	invoke		LoadIcon, hInstance, IDI_APPLICATION
	mov			wcex.hIcon, eax
	mov			wcex.hIconSm, eax
	; Set cursor of window
	invoke		LoadCursor, NULL, IDC_ARROW
	mov			wcex.hCursor, eax
	mov			wcex.hbrBackground, COLOR_WINDOW + 1
	mov			wcex.lpszMenuName, NULL
	mov			wcex.lpszClassName, offset gc_szWindowClass
	; Register window class
	invoke		RegisterClassEx, addr wcex
	cmp			eax, 0
	jne			CreateWindowLabel
	invoke		MessageBox, NULL, offset gc_szRegisterFailureMsg, offset gc_szErrorTypeWindow, MB_ICONERROR
	ret
	; Create window
CreateWindowLabel:
	invoke		CreateWindowEx, NULL, offset gc_szWindowClass, offset gc_szWindowTitle, \
					WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, \
					500, 600, NULL, NULL, hInstance, NULL
	mov			g_hWindow, eax
	cmp			eax, 0
	jne			ShowWindowLabel
	invoke		MessageBox, NULL, offset gc_szCreateFailureMsg, offset gc_szErrorTypeWindow, MB_ICONERROR
	ret
	; Show window
ShowWindowLabel:
	invoke		ShowWindow, g_hWindow, nCmdShow
	invoke		UpdateWindow, g_hWindow
GetMessageLoop:
	invoke		GetMessage, addr msg, NULL, 0, 0
	cmp			eax, 0
	je			ReturnLabel	
	invoke		TranslateMessage, addr msg
	invoke		DispatchMessage, addr msg
	jmp			GetMessageLoop
ReturnLabel:
	mov			eax, msg.wParam
	ret
WinMain endp
; WinProc function
WndProc proc		hWindow:HWND, unMessage:UINT, wParam:WPARAM, lParam:LPARAM
		LOCAL		ps:PAINTSTRUCT
		LOCAL		hdc:HDC
WMCREATELabel:
	cmp			unMessage, WM_CREATE
	jne			WMPAINTLabel
	invoke		CreateWindowEx, NULL, offset gc_szClassEdit, NULL, WS_CHILD or WS_VISIBLE or WS_BORDER or WS_TABSTOP, \
					20, 25, 300, 20, hWindow, NULL, NULL, NULL
	mov			g_hSourceFileEdit, eax 
	invoke		CreateWindowEx, NULL, offset gc_szClassEdit, NULL, WS_CHILD or WS_VISIBLE or WS_BORDER or WS_TABSTOP, \
					20, 70, 300, 20, hWindow, NULL, NULL, NULL
	mov			g_hDestinationFileEdit, eax
	invoke		CreateWindowEx, NULL, offset gc_szClassStatic, NULL, WS_CHILD or WS_VISIBLE or WS_BORDER , \
					20, 115, 442, 425, hWindow, NULL, NULL, NULL
	mov			g_hOutputStatic, eax
	invoke		CreateWindowEx, NULL, offset gc_szClassButton, offset gc_szCompareButtonText, WS_CHILD or WS_VISIBLE or WS_TABSTOP or BS_DEFPUSHBUTTON, \
					350, 25, 110, 65, hWindow, NULL, NULL, NULL
	mov			g_hCompareButton, eax
	jmp			ReturnLabel
WMPAINTLabel:
	cmp			unMessage, WM_PAINT
	jne			WMCOMMANDLabel
	invoke		BeginPaint, hWindow, addr ps
	mov			hdc, eax
	invoke		crt_strlen, offset gc_szSourceFileEditTitle
	invoke		TextOutA, hdc, 20, 10, offset gc_szSourceFileEditTitle, eax
	invoke		crt_strlen, offset gc_szDestinationFileEditTitle
	invoke		TextOutA, hdc, 20, 55, offset gc_szDestinationFileEditTitle, eax
	invoke		crt_strlen, offset gc_szOutputStaticTitle
	invoke		TextOutA, hdc, 20, 100, offset gc_szOutputStaticTitle, eax
	invoke		EndPaint, hWindow, addr ps
	jmp			ReturnLabel
WMCOMMANDLabel:
	cmp			unMessage, WM_COMMAND
	jne			WMDESTROYLabel
	mov			eax, lParam
CommandCompareButtonLabel:
	cmp			eax, g_hCompareButton
	jne			CommandEndLabel
	invoke		GetWindowTextA, g_hSourceFileEdit, offset g_szSourceFilePath, sizeof g_szSourceFilePath
	invoke		GetWindowTextA, g_hDestinationFileEdit, offset g_szDestinationFilePath, sizeof g_szDestinationFilePath
	invoke		Compare
CommandEndLabel:
	jmp			ReturnLabel
WMDESTROYLabel:
	cmp			unMessage, WM_DESTROY
	jne			WMOTHERLabel
	invoke		PostQuitMessage, 0
	ret
WMOTHERLabel:
	invoke		DefWindowProc, hWindow, unMessage, wParam, lParam
	ret
ReturnLabel:
	xor			eax, eax
	ret
WndProc endp

start:
	invoke		GetModuleHandle, NULL
	mov			g_hInstance, eax
	invoke		WinMain, g_hInstance, NULL, NULL, SW_SHOWDEFAULT
	ret
end start