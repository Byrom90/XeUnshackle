#include "stdafx.h"



//=============================================================================================================================================
//		UART PRINTING
//		Prints will be sent directly to uart - Credit c0z - Dashlaunch 2.11 source
//=============================================================================================================================================
#pragma region UART_Print
DWORD g_spinvar;
DWORD g_oldIrql;

char xtoa(unsigned char inp)
{
    char ret;
    if (inp < 0xa) // 0-9 = 0x30-0x39 
        ret = inp + 0x30;
    else		// 0xa-f = 0x61-66
        ret = inp + 0x57;
    return ret;
}

VOID makeString(char* dest, void* inpt, unsigned long len, unsigned long maxlen)
{
    unsigned char* inp = (unsigned char*)inpt;
    unsigned long i, j = 0, k = 0;

    if (inp != NULL)
    {
        for (i = 0; i < len; i++)
        {
            dest[j] = xtoa((inp[i] & 0xF0) >> 4) & 0xFF;
            j++;
            dest[j] = xtoa(inp[i] & 0xF) & 0xFF;
            j++;
            k++;
            if (k == 4)
            {
                dest[j] = ' ';
                j++;
                k = 0;
            }
            if (j >= maxlen - 3)
                i = len;
        }
    }
    else
    {
        dest[j] = '!';
        j++;
    }
    dest[j] = 0;
}

#pragma warning(push)
#pragma warning(disable: 4100) // unreferenced formal param
#pragma warning(disable: 4996) // _s not used warning

VOID __declspec(naked) cygPut(char ch)
{
    __asm
    {
        // Function prologue. Set up a stack frame and
        // preserve r31, and the link register;
        mflr    r12
        stw     r12, -8(r1)
        std     r31, -0x10(r1)
        stwu    r1, -0x18(r1)
        //// Preserve r3 and r4 so their values aren't lost by
        //// the function call.
        mr      r31, r4

        lis 	r4, 0x7fea
        slwi 	r3, r3, 24
        stw 	r3, 0x1014(r4)
        waiter:
        lwz 	r3, 0x1018(r4)
            rlwinm.r3, r3, 0, 6, 6
            beq 	waiter

            // Function epilogue. Tear down the stack frame and
            // restore r30, r31, and the link register.
            mr      r4, r31
            addi    r1, r1, 0x18
            lwz     r12, -8(r1)
            mtlr    r12
            ld      r31, -10h(r1)
            blr
    }
}

VOID cprintf(const char* s, ...)
{
    //size_t Size = strlen(s);
    va_list argp;
    int i, j;
    char temp[512];
    BYTE irql;

    //char* temp = new char[Size + 1];  // +1 you probably want zero-termination

    va_start(argp, s);
    vsnprintf(temp, 512, s, argp);
    //vsnprintf(temp, Size + 1, s, argp);
    va_end(argp);

    irql = KfAcquireSpinLock(&g_spinvar);

    j = strlen(temp);
    //j = Size;
    for (i = 0; i < j; i++)
    {
        if (temp[i] == 0)
            break;
        else
            cygPut(temp[i]);
    }
    cygPut(0x0D);
    cygPut(0x0A);


    //delete[] temp;
    KfReleaseSpinLock(&g_spinvar, irql);
    //Sleep(20);
}

#pragma warning(pop)
#pragma endregion
//=============================================================================================================================================


#define OBJ_SYS_STRING	"\\System??\\%s"
#define OBJ_USR_STRING	"\\??\\%s"
#define OBJ_SYS_PATH	"\\System??\\"
#define OBJ_USR_PATH	"\\??\\"
char DEVICE_DYNAMIC[MAX_PATH];

// We only need Usb or Hdd for lhelper atm. Everything else can just use GAME:
#define MOUNT_USB "Usb:"
#define DEVICE_USB0 "\\Device\\Mass0"
#define MOUNT_HDD "Hdd:"
#define DEVICE_HDD "\\Device\\Harddisk0\\Partition1"

HRESULT CreateMount(const char* szDrive, const char* szDevice, BOOL System) {
	STRING DeviceName, LinkName;
	CHAR szDestinationDrive[MAX_PATH];
	sprintf_s(szDestinationDrive, MAX_PATH, System ? OBJ_SYS_STRING : OBJ_USR_STRING, szDrive);
	RtlInitAnsiString(&DeviceName, szDevice);
	RtlInitAnsiString(&LinkName, szDestinationDrive);
	ObDeleteSymbolicLink(&LinkName);
	return (HRESULT)ObCreateSymbolicLink(&LinkName, &DeviceName);
}

HRESULT DeleteMount(const char* szDrive, BOOL System)
{
	// Setup our path
	CHAR szDestinationDrive[MAX_PATH];
	sprintf_s(szDestinationDrive, MAX_PATH, System ? OBJ_SYS_STRING : OBJ_USR_STRING, szDrive);

	// Setup our string
	STRING LinkName;
	RtlInitAnsiString(&LinkName, szDestinationDrive);

	// Delete finally
	NTSTATUS status = ObDeleteSymbolicLink(&LinkName);
	return (status >= 0) ? S_OK : S_FALSE;
}

BOOL MountUsb()
{
	// Non-system access
	if (!CreateMount(MOUNT_USB, DEVICE_USB0, FALSE)) return TRUE; // Success

	return FALSE; // Failed
}
BOOL DelMountUsb()
{
	// Non-system access
	if (!DeleteMount(MOUNT_USB, FALSE)) return TRUE; // Success

	return FALSE; // Failed
}

BOOL MountHdd()
{
	// Non-system access
	if (!CreateMount(MOUNT_HDD, DEVICE_HDD, FALSE)) return TRUE; // Success

	return FALSE; // Failed
}
BOOL DelMountHdd()
{
	// Non-system access
	if (!DeleteMount(MOUNT_HDD, FALSE)) return TRUE; // Success

	return FALSE; // Failed
}

BOOL DoesDriveExist(string Mountpoint)
{
	string strDrive = Mountpoint + "\\";
	if (GetFileAttributes(strDrive.c_str()) != 0xFFFFFFFF)
	{
		return TRUE;
	}
	return FALSE;
}


//BOOL FileExists(LPCSTR lpFileName)
//{
//	// Try and get the file attributes
//	if (GetFileAttributes(lpFileName) == -1)
//	{
//		DWORD lastError = GetLastError();
//		if (lastError == ERROR_FILE_NOT_FOUND || lastError == ERROR_PATH_NOT_FOUND)
//			return FALSE;
//	}
//
//	// The file must exist if we got this far...
//	return TRUE;
//}

BOOL FileExists(PCHAR path)
{
	OBJECT_ATTRIBUTES obAtrib;
	FILE_NETWORK_OPEN_INFORMATION netInfo;
	STRING filePath;
	RtlInitAnsiString(&filePath, path); //  = 0x10
	InitializeObjectAttributes(&obAtrib, &filePath, 0x40, NULL);
	if (path[0] != '\\')
		obAtrib.RootDirectory = (HANDLE)0xFFFFFFFD;
	if (NT_SUCCESS(NtQueryFullAttributesFile(&obAtrib, &netInfo)))
	{
		// filter out directories from the result
		if ((netInfo.FileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
			return TRUE;
	}
	return FALSE;
}

BOOL CReadFile(const CHAR* FileName, MemoryBuffer& pBuffer)
{
	HANDLE hFile; DWORD dwFileSize, dwNumberOfBytesRead;
	hFile = CreateFile(FileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		cprintf("CReadFile - CreateFile failed");
		return FALSE;
	}

	dwFileSize = GetFileSize(hFile, NULL);
	PBYTE lpBuffer = (BYTE*)malloc(dwFileSize);
	if (lpBuffer == NULL)
	{
		CloseHandle(hFile);
		cprintf("CReadFile - malloc failed");
		return FALSE;
	}

	if (ReadFile(hFile, lpBuffer, dwFileSize, &dwNumberOfBytesRead, NULL) == FALSE)
	{
		free(lpBuffer);
		CloseHandle(hFile);
		cprintf("CReadFile - ReadFile failed");
		return FALSE;
	}

	else if (dwNumberOfBytesRead != dwFileSize)
	{
		free(lpBuffer);
		CloseHandle(hFile);
		cprintf("CReadFile - Failed to read all the bytes");
		return FALSE;
	}

	CloseHandle(hFile);
	pBuffer.Add(lpBuffer, dwFileSize);
	free(lpBuffer);
	return TRUE;
}

BOOL CWriteFile(const CHAR* FilePath, const VOID* Data, DWORD Size)
{
	HANDLE fHandle = CreateFile(FilePath, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (fHandle == INVALID_HANDLE_VALUE)
	{
		cprintf("[CWriteFile] CreateFile failed. Error: %X", GetLastError());
		return FALSE;
	}

	DWORD writeSize = Size;
	if (WriteFile(fHandle, Data, writeSize, &writeSize, NULL) != TRUE)
	{
		cprintf("[CWriteFile] WriteFile failed. Error: %X", GetLastError());
		return FALSE;
	}
	CloseHandle(fHandle);

	return TRUE;
}

CRITICAL_SECTION patchsec;
// Going by what I've seen used elsewhere here
// Change later if required
#define MAX_SPINS_DEFAULT		65280
BOOL bCritSecInit = FALSE;
DWORD ApplyPatches(CHAR* FilePath, const VOID* DefaultPatches)
{
	// Init the critical section with spincount if we haven't already
	if (!bCritSecInit)
	{
		RtlInitializeCriticalSectionAndSpinCount(&patchsec, MAX_SPINS_DEFAULT);
		bCritSecInit = TRUE;
	}

	// Read our file
	DWORD patchCount = 0;
	MemoryBuffer mbPatches;
	DWORD* patchData = (DWORD*)DefaultPatches;

	// Check if we have our override patches
	if (FilePath != NULL && FileExists(FilePath))
	{
		if (!CReadFile(FilePath, mbPatches))
		{
			cprintf("ApplyPatches - CReadFile failed");
			return patchCount;
		}

		// Set our patch data now
		patchData = (DWORD*)mbPatches.GetData();
	}

	// Make sure we have patches...
	if (patchData == NULL)
	{
		return 0;
	}

	RtlEnterCriticalSection(&patchsec);
	// Apply our patches	
	while (*patchData != 0xFFFFFFFF)
	{
		BOOL inHvMode = (patchData[0] < 0x40000);
		QWORD patchAddr = inHvMode ? (0x200000000 * (patchData[0] / 0x10000)) + patchData[0] : (QWORD)patchData[0];

		if (inHvMode)
		{
			cprintf("Applying HV patch at %X", patchAddr);
			Hvx::HvPokeBytes(patchAddr, &patchData[2], patchData[1] * sizeof(DWORD));

		}
		else
		{
			cprintf("Applying Kernel patch at %X", patchAddr);
			memcpy((VOID*)patchData[0], &patchData[2], patchData[1] * sizeof(DWORD));

			__dcbst(0, (VOID*)patchData[0]);
			__sync();
			__isync();
		}

		patchData += (patchData[1] + 2);
		patchCount++;
	}
	RtlLeaveCriticalSection(&patchsec);
	return patchCount;
}

//static LPCWSTR buttons[1] = { L"Understood" };
static MESSAGEBOX_RESULT result;
static XOVERLAPPED overlapped;
VOID ShowErrorAndExit(int Stage)
{
	LPCWSTR buttons[1] = { currentLocalisation->ExitConfirm };
	WCHAR maintext[100];
	swprintf_s(maintext, currentLocalisation->ErrorandExit, Stage);

	if (XShowMessageBoxUI(0, L"XeUnshackle - Error", maintext, 1, buttons, 0, XMB_ERRORICON, &result, &overlapped) == ERROR_IO_PENDING)
	{
		while (!XHasOverlappedIoCompleted(&overlapped))
			Sleep(50);
	}
	XLaunchNewImage(XLAUNCH_KEYWORD_DEFAULT_APP, 0);

}


#define NAME_XAM "xam.xex"
#define XNotifyQueueUI_ORD 656
typedef VOID(*XNotifyQueueUI)(int type, DWORD dwUserIndex, ULONGLONG qwAreas, PWCHAR displayText, PVOID contextData);
XNotifyQueueUI XNotify = NULL;

VOID ShowNotify(PWCHAR NotifyText) // DO NOT CALL THIS FROM SYSTEM THREADS
{
	if (!XNotify)
	{
		XNotify = (XNotifyQueueUI)GetProcAddress(GetModuleHandle(NAME_XAM), (LPCSTR)XNotifyQueueUI_ORD);
		if (!XNotify) return;
	}
	XNotify(14, 0, 2, NotifyText, NULL);
}

#define XamLoaderLaunchTitleEx_ORD 421
typedef NTSTATUS(*XamLoaderLaunchTitleEx)(LPCSTR szLaunchPath, LPCSTR szMountPath, LPCSTR szCmdLine, DWORD dwFlags);
XamLoaderLaunchTitleEx LaunchT = NULL;

VOID LaunchTitle(LPCSTR szLaunchPath, LPCSTR szMountPath, LPCSTR szCmdLine, DWORD dwFlags)
{
	if (!LaunchT)
	{
		LaunchT = (XamLoaderLaunchTitleEx)GetProcAddress(GetModuleHandle(NAME_XAM), (LPCSTR)XamLoaderLaunchTitleEx_ORD);
		if (!LaunchT) return;
	}

	LaunchT(szLaunchPath, szMountPath, szCmdLine, dwFlags);
}

VOID RelaunchApp() // Relaunch this app
{
	LaunchTitle(ExLoadedImageName);
}

#define CONSOLE_TYPE_XENON			0x00000000
#define CONSOLE_TYPE_ZEPHYR			0x10000000
#define CONSOLE_TYPE_FALCON			0x20000000
#define CONSOLE_TYPE_JASPER			0x30000000
#define CONSOLE_TYPE_TRINITY		0x40000000
#define CONSOLE_TYPE_CORONA			0x50000000
#define CONSOLE_TYPE_WINCHESTER		0x60000000

#define CONSOLE_TYPE_FLAGS_MASK 	(0xF0000000)
#define CONSOLE_TYPE_FROM_FLAGS 	(XboxHardwareInfo->Flags & CONSOLE_TYPE_FLAGS_MASK)
#define IS_CONSOLE_TYPE_SLIM		(CONSOLE_TYPE_FROM_FLAGS > CONSOLE_TYPE_JASPER)

string GetMoboByHWFlags()
{
	switch (CONSOLE_TYPE_FROM_FLAGS)
	{
	case CONSOLE_TYPE_XENON:
		return "Xenon";
	case CONSOLE_TYPE_ZEPHYR:
		return "Zephyr";
	case CONSOLE_TYPE_FALCON:
		return "Falcon";
	case CONSOLE_TYPE_JASPER:
		return "Jasper";
	case CONSOLE_TYPE_TRINITY:
		return "Trinity";
	case CONSOLE_TYPE_CORONA:
		return "Corona";
	case CONSOLE_TYPE_WINCHESTER:
		return "Winchester";
	default:
		return "Unknown";
	}
}

BOOL DisableButtons = FALSE;
VOID Dump1blRomToFile()
{
	DisableButtons = TRUE;
	BYTE RomBuf[MEM_1BL_SZ];
	memset(RomBuf, 0, 0x100);

	HRESULT res = Hvx::HvDump1blRom(RomBuf);

	if (res != 0)
	{
		cprintf("[Dump1blRomToFile] FAILED! Non-zero result...");
		ShowNotify(currentLocalisation->D1bl_Fail_Nonzero);
	}
	else
	{
		string MoboType = GetMoboByHWFlags();
		string blSavePath = "GAME:\\" + MoboType + "-1bl.bin";

		if (CWriteFile(blSavePath.c_str(), &RomBuf, sizeof(RomBuf)) == TRUE)
		//if (CWriteFile("GAME:\\1bl.bin", &RomBuf, sizeof(RomBuf)) == TRUE)
		{
			cprintf("[Dump1blRomToFile] SUCCESS! Dumped to %s", blSavePath.c_str());
			WCHAR w1blnoti[50];
			ZeroMemory(w1blnoti, sizeof(w1blnoti));
			swprintf_s(w1blnoti, currentLocalisation->D1bl_Savedto, MoboType.c_str());
			ShowNotify(w1blnoti);
		}
		else
		{
			cprintf("[Dump1blRomToFile] FAILED! Failed to write file...");
			ShowNotify(currentLocalisation->D1bl_Fail_Write);
		}
	}
	DisableButtons = FALSE;
}

extern WCHAR wCPUKeyBuf[];
extern WCHAR wDVDKeyBuf[];
extern WCHAR wConTypeBuf[];
// TODO: Handle this better. Dumps buffer whitespace into file. Good enough for now
VOID SaveConsoleDataToFile()
{
	DisableButtons = TRUE;
	char ConsoleInfoBuf[160];
	ZeroMemory(ConsoleInfoBuf, sizeof(ConsoleInfoBuf));
	sprintf_s(ConsoleInfoBuf, "%ws\n%ws\n%ws\n", wConTypeBuf, wCPUKeyBuf, wDVDKeyBuf);

	if (CWriteFile("GAME:\\ConsoleInfo.txt", ConsoleInfoBuf, sizeof(ConsoleInfoBuf)))
		ShowNotify(currentLocalisation->SaveConInfo_Success);
	else
		ShowNotify(currentLocalisation->SaveConInfo_Failed);

	DisableButtons = FALSE;
}

// User is expected to have already taken a full nand backup so this is just an extra precaution.
// Grab and store the original mac address contained within the consoles secure config. 
// Stealth servers can and do modify this. It could already be too late if they loaded one previously.
// Obviously we want to only store this the very first time the app has been loaded.
// If the user chooses to ignore and delete this backup then it's on them.

WORD XCONFIG_SECURED_CATEGORY = 0x2;
WORD XCONFIG_SECURED_MAC_ADDRESS = 0x1;
#define MACFilePath "GAME:\\OriginalMACAddress.bin"
VOID BackupOrigMAC()
{
	if (FileExists(MACFilePath))
	{
		cprintf("[BackupOrigMAC] MAC backup already exists. Skipping...");
		return;
	}

	BYTE OrigMACAddress[6];
	if (NT_SUCCESS(ExGetXConfigSetting(XCONFIG_SECURED_CATEGORY, XCONFIG_SECURED_MAC_ADDRESS, OrigMACAddress, 6, NULL)))
	{

		if (CWriteFile(MACFilePath, OrigMACAddress, sizeof(OrigMACAddress)))
			ShowNotify(currentLocalisation->Dump_MAC_Success);
		else
			ShowNotify(currentLocalisation->Dump_MAC_Fail);
	}
}

// Using .txt file instead of .ini so user can delete this easily in XeXMenu/Aurora
#define AutoStartFilePath "GAME:\\XeUnshackleAutoStart.txt"

// Saves the Auto-Start file with the specified timer value.
VOID SaveAutoStart(DOUBLE timerValue)
{
	DisableButtons = TRUE;

	// Convert the double to a string representation (e.g., "2.00")
	char szTimerValue[32];
	sprintf_s(szTimerValue, sizeof(szTimerValue), "%.2f", timerValue);

	// Write the string to the file
	if (CWriteFile(AutoStartFilePath, szTimerValue, strlen(szTimerValue)))
		ShowNotify(currentLocalisation->SaveAutoStart_Success);
	else
		ShowNotify(currentLocalisation->SaveAutoStart_Fail);

	DisableButtons = FALSE;
}

// Checks if the Auto-Start file exists and loads the timer value from it.
// Returns the timer value (e.g., 2.0) on success, or -1.0 if the file doesn't exist or is invalid.
DOUBLE LoadAutoStart()
{
	if (!FileExists(AutoStartFilePath))
	{
		return -1.0; // Auto-Start is not enabled.
	}

	// The file exists, read and validate its content.
	MemoryBuffer mb;
	if (!CReadFile(AutoStartFilePath, mb) || mb.GetDataLength() == 0)
	{
		cprintf("[Auto-Start] File exists but is empty or could not be read.");
		return -1.0; // Treat as disabled.
	}

	// Convert the file content to a double.
	const char* fileContent = (const char*)mb.GetData();
	char szBuffer[33] = { 0 };
	strncpy_s(szBuffer, sizeof(szBuffer), fileContent, mb.GetDataLength());
	DOUBLE timerValue = atof(szBuffer);

	// Validate the parsed value. It must be a non-negative number.
	if (timerValue >= 0.0)
	{
		return timerValue;
	}
	else
	{
		cprintf("[Auto-Start] File content '%s' is not a valid timer value.", szBuffer);
		return -1.0; // The file is corrupt or invalid, treat as disabled.
	}
}