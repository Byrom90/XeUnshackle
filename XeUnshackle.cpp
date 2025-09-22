//==========================================================================================================================
//
//											- XeUnshackle BETA -
//			A simple app designed to apply a full set of freeboot/xebuild kernel & HV patches to a running system
//			after running the Xbox360BadUpdate HV exploit. Sets up & loads a version of launch.xex (Dashlaunch)
//          designed to run from hdd or usb root rather than flash (nand).
//
// Created by: Byrom
// 
// Credits: 
//          grimdoomer - Xbox360BadUpdate exploit.
//          cOz - Dashlaunch, xeBuild patches and much more.
//          Visual Studio / GoobyCorp
//          Diamond
//          InvoxiPlayGames - FreeMyXe, Usbdsec patches, RoL restore and general help.
//          ikari - freeBOOT
//          Xbox360Hub Discord #coding-corner
//          Anyone else who has contributed anything to the 360 scene. Apologies if any credits were missed.
// 
// Notes: 
//          This is basically what I came up with during initial testing so could prob be simplified & improved a lot.
//==========================================================================================================================

#include "stdafx.h"

FLOAT APP_VERS = 1.04;

// Get global access to the main D3D device
extern D3DDevice* g_pd3dDevice;
DWORD YellowText = 0xFFFFFF00;
DWORD WhiteText = 0xFFFFFFFF;
DWORD GreyText = 0xFF808080;
DOUBLE dDefaultAutoStartTimer = 0; // 0 seconds (will skip the app completely)
DOUBLE dSavedAutoStartTimer = -1.0;
BOOL bShouldPlaySuccessVid = FALSE;
WCHAR wTitleHeaderBuf[100];
WCHAR wCPUKeyBuf[150];
WCHAR wDVDKeyBuf[50];
WCHAR wConTypeBuf[50];

//--------------------------------------------------------------------------------------
// Name: class Sample
// Desc: Main class to run this application. Most functionality is inherited
//       from the ATG::Application base class.
//--------------------------------------------------------------------------------------
class XeUnshackle : public ATG::Application
{
    ATG::Timer m_Timer;
    ATG::Font m_Font;
    ATG::Help m_Help;
    BOOL m_bDrawHelp;

    BOOL m_bFailed;

    // Countdown timer to app exiting when using Auto Start
    DOUBLE m_autoStartExitTimer;

public:
    VOID SetAutoStartExitTimer(DOUBLE timerValue)
    {
        if (timerValue >= 0.0)
        {
            bShouldPlaySuccessVid = FALSE;
            m_Timer.GetElapsedTime(); // Prime the timer to reset the value since last call
        }
        m_autoStartExitTimer = timerValue;
    }

private:
    virtual HRESULT Initialize();
    virtual HRESULT Update();
    virtual HRESULT Render();
};


//--------------------------------------------------------------------------------------
// Name: Initialize()
// Desc: This creates all device-dependent display objects.
//--------------------------------------------------------------------------------------
HRESULT XeUnshackle::Initialize()
{
    // Create the font
    if (FAILED(m_Font.Create("embed:\\FONT")))
        return ATGAPPERR_MEDIANOTFOUND;

    // Confine text drawing to the title safe area
    m_Font.SetWindow(ATG::GetTitleSafeArea());

    m_bFailed = FALSE;

    return S_OK;
}


//--------------------------------------------------------------------------------------
// Name: Update()
// Desc: Called once per frame, the call is the entry point for animating the scene.
//--------------------------------------------------------------------------------------
HRESULT XeUnshackle::Update()
{
    // Get the current gamepad state
    ATG::GAMEPAD* pGamepad = ATG::Input::GetMergedInput();

    // If the Auto Start timer is active, count it down
    if(m_autoStartExitTimer >= 0.0)
    {
        if (!DisableButtons)
        {
            if (pGamepad->wPressedButtons & XINPUT_GAMEPAD_B)
            {
                SetAutoStartExitTimer(-1.0);
                return S_OK;
            }
        }
        
        m_autoStartExitTimer -= m_Timer.GetElapsedTime();

        // When the timer runs out, launch the default app
        if(m_autoStartExitTimer <= 0.0)
        {
            XLaunchNewImage(XLAUNCH_KEYWORD_DEFAULT_APP, 0);
        }

        // Return here so button presses are not processed when using Auto Start
        return S_OK;
    }

    if (!DisableButtons)
    {
        if (pGamepad->wPressedButtons & XINPUT_GAMEPAD_BACK)
        {
            XLaunchNewImage(XLAUNCH_KEYWORD_DEFAULT_APP, 0);
        }
        else if (pGamepad->wPressedButtons & XINPUT_GAMEPAD_START)
        {
            if (dSavedAutoStartTimer >= 0.0)
            {
                SetAutoStartExitTimer(dSavedAutoStartTimer);
            }
            else
            {
                SaveAutoStart(dDefaultAutoStartTimer);
                SetAutoStartExitTimer(dDefaultAutoStartTimer);
            }
        }
        else if (pGamepad->wPressedButtons & XINPUT_GAMEPAD_X)
        {
            SaveConsoleDataToFile();
        }
        else if (pGamepad->wPressedButtons & XINPUT_GAMEPAD_Y)
        {
            Dump1blRomToFile();
        }
    }

    return S_OK;
}


//--------------------------------------------------------------------------------------
// Name: Render()
// Desc: Sets up render states, clears the viewport, and renders the scene.
//--------------------------------------------------------------------------------------
HRESULT XeUnshackle::Render()
{
    // Draw a gradient filled background
    //ATG::RenderBackground(0xff0000ff, 0xff000000);

    ATG::RenderBackground(0xFF000032, 0xFF000032);
    m_Font.Begin();
    m_Font.SetScaleFactors(1.5f, 1.5f);
    m_Font.DrawText(0, 0, YellowText, wTitleHeaderBuf);

    // Pre-Release Build Identifier
    //m_Font.DrawText(840, 0, YellowText, L"[TEST BUILD]");
    //

    m_Font.SetScaleFactors(1.0f, 1.0f);

    // General Info
    m_Font.DrawText(0, 70, YellowText, currentLocalisation->MainInfo);

    // Dashlaunch Info
    m_Font.DrawText(0, 240, YellowText, wDLStatusBuf);
    if (bDLisLoaded)
    {
        m_Font.DrawText(0, 270, YellowText, currentLocalisation->MainScrDL);
    }

    // Console Info
    m_Font.DrawText(0, 370, YellowText, wConTypeBuf);
    m_Font.DrawText(0, 400, YellowText, wCPUKeyBuf);
    m_Font.DrawText(0, 430, YellowText, wDVDKeyBuf);

    // Credits
    m_Font.DrawText(0, 540, YellowText, L"https://github.com/rezbouchabou/XeUnshackle");
    m_Font.DrawText(0, 570, YellowText, L"https://github.com/Byrom90/XeUnshackle");
    m_Font.DrawText(0, 600, YellowText, L"https://byrom.uk");

    // If the timer is not active, draw the normal button prompts, otherwise draw the countdown text
    if (m_autoStartExitTimer < 0.0)
    {
        // User input with buttons - Make these white so they display correctly and stand out to the user
        m_Font.DrawText(740, 490, WhiteText, currentLocalisation->MainScrBtnSaveInfo);// X button icon with text 
        m_Font.DrawText(740, 520, WhiteText, currentLocalisation->MainScrBtnDump1BL);// Y button icon with text

        m_Font.DrawText(740, 560, WhiteText, currentLocalisation->MainScrBtnExit);// Back button icon with text
        m_Font.DrawText(740, 600, WhiteText, currentLocalisation->MainScrBtnAutoStartSet);// Start button icon with text
    }
    else
    {
        // Format the string to include countdown value
        WCHAR szCountdown[150];
        swprintf_s(szCountdown, currentLocalisation->MainScrAutoStartRunning, m_autoStartExitTimer);

        // Draw the countdown text where the button prompts would normally be
        m_Font.DrawText(740, 570, GreyText, szCountdown);
        m_Font.DrawText(740, 600, WhiteText, currentLocalisation->MainScrBtnAutoStartCancel);// B button icon with text
    }

    m_Font.End();

    // Present the scene
    m_pd3dDevice->Present(NULL, NULL, NULL, NULL);

    return S_OK;
}

//--------------------------------------------------------------------------------------
// Name: main()
// Desc: Entry point to the program
//--------------------------------------------------------------------------------------
VOID __cdecl main()
{
    SetLocale(); // Set the correct locale so text will be displayed in the correct language

    // Part 1 - We apply the HV patches here (if required)
    if (!Hvx::CheckPPExpHVAccess()) // If we have pp access then assume we have done this previously
    {
        if (!Hvx::DisableExpChecks()) // Stage 1 - Apply HV patches to disable checks on expansions. If this fails do not proceed
        {
            cprintf("[XeUnshackle] Stage 1 failed!");
            ShowErrorAndExit(1);
        }
        cprintf("[XeUnshackle] Stage 1 success!");
        if (!Hvx::SetupPPExpHVAccess()) // Stage 2 - Install the peek poke expansion. If this fails do not proceed
        {
            cprintf("[XeUnshackle] Stage 2 failed!");
            ShowErrorAndExit(2);
        }
        cprintf("[XeUnshackle] Stage 2 success!");
        if (!Hvx::CheckPPExpHVAccess()) // Stage 3 - Check if we now have HV access via Peek Poke expansion. If this fails do not proceed
        {
            cprintf("[XeUnshackle] Stage 3 failed!");
            ShowErrorAndExit(3);
        }
        cprintf("[XeUnshackle] Stage 3 success!");
        if (!ApplyFreebootHVPatches())
        {
            cprintf("[XeUnshackle] Stage 4 failed!");
            ShowErrorAndExit(4);
        }
        cprintf("[XeUnshackle] Stage 4 success!");

        //cprintf("[XeUnshackle] Relaunching before proceeding with Stage 5!"); // NO LONGER REQUIRED
        //RelaunchApp();

        // No more relaunching
        cprintf("[XeUnshackle] Calling KeFlushEntireTb");
        KeFlushEntireTb(); // This is called in XexpTitleTerminateNotification. Maybe this is why relaunching works???

    }
    // Part 2 - We end up here if part 1 succeeded in gaining HV access via expansions
    cprintf("[XeUnshackle] Checking kernel patch state");
    if (*(DWORD*)0x80108E70 != 0x48003134) // This is the last freeboot kernel patch applied. This determines whether we have applied them yet
    {
        if (!ApplyFreebootKernPatches())
        {
            cprintf("[XeUnshackle] Stage 5 failed!");
            ShowErrorAndExit(5);
        }
        ApplyAdditionalPatches(); // Other patches for general fixes

        RestoreRoL(); // Restore the default RoL state

        cprintf("[XeUnshackle] Calling KeFlushEntireTb");
        KeFlushEntireTb();

        cprintf("[XeUnshackle] Stage 5 success!");
    }
    // Part 3 - We should only ever begin here for any subsequent launches of the app

    // If Dashlaunch loaded successfully we can revert the patches done by BadUpdate. 
    // Needs to be like this due to Dashlaunch fixing Retail signed xex files that have been patched.
    // BadUpdate patches also allow this but prevent the Freeboot patches from functioning correctly
    // IMPORTANT NOTE: Dashlaunch doesn't appear to load the plugins until you exit to dash aka the next executable load.
    // 0 = FAILED
    // 1 = SUCCESS
    // 2 = Already loaded
    
    if (SysLoadDashlaunch() == 1) // We always call this here since it also sets up the wchar buffer to display in the app for Dashlaunch load status
    {

        RevertBadExploitPatches(); // Restore changes made by the exploit
    }

    cprintf("[XeUnshackle] All patches have been applied! Proceeding to init the ui...");

    // Grab some stuff for display in the ui
    ZeroMemory(wTitleHeaderBuf, sizeof(wTitleHeaderBuf));
    swprintf_s(wTitleHeaderBuf, L"%ls XeUnshackle v%.2f BETA %ls", GLYPH_RIGHT_TICK, APP_VERS, GLYPH_LEFT_TICK);
    // Motherboard type
    ZeroMemory(wConTypeBuf, sizeof(wConTypeBuf));
    swprintf_s(wConTypeBuf, L"Console type: %S", GetMoboByHWFlags().c_str());
    // cpu key
    QWORD fuse3 = Hvx::HvGetFuseline(3);
    QWORD fuse5 = Hvx::HvGetFuseline(5);
    ZeroMemory(wCPUKeyBuf, sizeof(wCPUKeyBuf));
    swprintf_s(wCPUKeyBuf, L"CPUKey: %08X%08X%08X%08X", fuse3 >> 32, fuse3 & 0xffffffff, fuse5 >> 32, fuse5 & 0xffffffff);
    // dvd key
    BYTE DVDKeyBytes[16];
    QWORD kvAddress = Hvx::HvPeekQWORD(0x00000002000163C0);
    Hvx::HvPeekBytes(kvAddress + 0x100, DVDKeyBytes, 16);
    ZeroMemory(wDVDKeyBuf, sizeof(wDVDKeyBuf));
    swprintf_s(wDVDKeyBuf, L"DVDKey: %08X%08X%08X%08X", *(DWORD*)(DVDKeyBytes), *(DWORD*)(DVDKeyBytes + 4), *(DWORD*)(DVDKeyBytes + 8), *(DWORD*)(DVDKeyBytes + 12));

    BackupOrigMAC(); // This will cause a notify to pop before the video has played completely but only if it hasn't been dumped previously

    // Run the ui portion of the app
    XeUnshackle atgApp;

    // For direct UI rendering we want to synchronize to the monitor.
    atgApp.m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
    ATG::GetVideoSettings(&atgApp.m_d3dpp.BackBufferWidth, &atgApp.m_d3dpp.BackBufferHeight);
    
    // SKIP THE VIDEO - Go straight to UI
    bShouldPlaySuccessVid = FALSE;

    // Load the saved Auto Start timer, will return negative value when not saved, so it doesn't trigger countdown
    dSavedAutoStartTimer = LoadAutoStart();
    atgApp.SetAutoStartExitTimer(dSavedAutoStartTimer);
    
    atgApp.Run();
}