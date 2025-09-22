#pragma once
#include "stdafx.h"

// IMPORTANT NOTE!!!
// The standard font used by this app DOES NOT support the characters required for some languages.
// Unfortunately I have no idea how to create a new font that does.

// Localised language support - Credit FreeMyXe, this is how it's handled there.

typedef struct _LocalisationMessages_t
{
    // Error Messagebox 
    wchar_t* ErrorandExit;
    wchar_t* ExitConfirm;
    // Dashlaunch load status
    wchar_t* DL_Loaded;
    wchar_t* DL_Mode_Hdd;
    wchar_t* DL_Mode_Usb;
    wchar_t* DL_Fail_SecData;
    wchar_t* DL_Fail_Mount;
    wchar_t* DL_Fail_Write;
    wchar_t* DL_Fail_Launch_SecData;
    wchar_t* DL_Fail_Status;
    // Dump 1BL Notify
    wchar_t* D1bl_Fail_Nonzero;
    wchar_t* D1bl_Savedto;
    wchar_t* D1bl_Fail_Write;
    // Save Console Info Notify
    wchar_t* SaveConInfo_Success;
    wchar_t* SaveConInfo_Failed;
    // Save Orig MAC
    wchar_t* Dump_MAC_Success;
    wchar_t* Dump_MAC_Fail;
    // Save Auto-Start
    wchar_t* SaveAutoStart_Success;
    wchar_t* SaveAutoStart_Fail;
    // Main Screen Text
    wchar_t* MainInfo;
    wchar_t* MainScrDL;
    wchar_t* MainScrBtnSaveInfo;
    wchar_t* MainScrBtnDump1BL;
    wchar_t* MainScrBtnExit;
    wchar_t* MainScrBtnAutoStartSet;
    wchar_t* MainScrAutoStartRunning;
    wchar_t* MainScrBtnAutoStartCancel;

} LocalisationMessages_t;


extern LocalisationMessages_t* currentLocalisation;

VOID SetLocale();