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
//          Jeff Hamm - https://www.youtube.com/watch?v=PantVXVEVUg - Chain break video
//          ikari - freeBOOT
//          Xbox360Hub Discord #coding-corner
//          Eaton - Bad Storage
//          Anyone else who has contributed anything to the 360 scene. Apologies if any credits were missed.
// 
// Notes: 
//          This is basically what I came up with during initial testing so could prob be simplified & improved a lot.
//==========================================================================================================================

#include "stdafx.h"

FLOAT APP_VERS = 1.03;

const CHAR* g_strMovieName = "embed:\\VID";

// Get global access to the main D3D device
extern D3DDevice* g_pd3dDevice;
DWORD YellowText = 0xFFFFFF00;
DWORD WhiteText = 0xFFFFFFFF;
DWORD GreyText = 0xFF808080;
DOUBLE dDefaultAutoStartTimer = 2; // 2 seconds
DOUBLE dSavedAutoStartTimer = -1.0;
BOOL bShouldPlaySuccessVid = FALSE;
WCHAR wTitleHeaderBuf[100];
WCHAR wCPUKeyBuf[150];
WCHAR wDVDKeyBuf[50];
WCHAR wConTypeBuf[50];
WCHAR wBadStorageStatusBuf[21];

//--------------------------------------------------------------------------------------
// Name: class Sample
// Desc: Main class to run this application. Most functionality is inherited
//       from the ATG::Application base class.
//--------------------------------------------------------------------------------------
class XeUnshackle : public ATG::Application
{
    // Pointer to XMV player object.
    IXMedia2XmvPlayer* m_xmvPlayer;
    // Structure for controlling where the movie is played.
    XMEDIA_VIDEO_SCREEN m_videoScreen;

    
    // Tell XMV player about scaling and rotation parameters.
    VOID            InitVideoScreen();

    // Buffer for holding XMV data when playing from memory.
    VOID* m_movieBuffer;

    // XAudio2 object.
    IXAudio2* m_pXAudio2;

    ATG::Timer m_Timer;
    ATG::Font m_Font;
    ATG::Help m_Help;
    BOOL m_bDrawHelp;

    BOOL m_bFailed;

    // Countdown timer to app exiting when using Auto-Start
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
    m_xmvPlayer = 0;
    m_movieBuffer = 0;

    // Initialize the XAudio2 Engine. The XAudio2 Engine is needed for movie playback.
    UINT32 flags = 0;
#ifdef _DEBUG
    flags |= XAUDIO2_DEBUG_ENGINE;
#endif

    HRESULT hr = XAudio2Create(&m_pXAudio2, flags);
    if (FAILED(hr))
        ATG::FatalError("Error %#X calling XAudio2Create\n", hr);

    IXAudio2MasteringVoice* pMasteringVoice = NULL;
    hr = m_pXAudio2->CreateMasteringVoice(&pMasteringVoice);
    if (FAILED(hr))
        ATG::FatalError("Error %#X calling CreateMasteringVoice\n", hr);

    // Create the font
    if (FAILED(m_Font.Create("embed:\\FONT")))
        return ATGAPPERR_MEDIANOTFOUND;

    // Confine text drawing to the title safe area
    m_Font.SetWindow(ATG::GetTitleSafeArea());

    m_bFailed = FALSE;

    return S_OK;
}


//--------------------------------------------------------------------------------------
// Name: InitVideoScreen()
// Desc: Adjust how the movie is displayed on the screen. Horizontal and vertical
//      scaling and rotation are applied.
//--------------------------------------------------------------------------------------
VOID XeUnshackle::InitVideoScreen()
{
    const int width = m_d3dpp.BackBufferWidth;
    const int height = m_d3dpp.BackBufferHeight;
    const int hWidth = width / 2;
    const int hHeight = height / 2;

    // Parameters to control scaling and rotation of video.
    float m_angle = 0.0;
    float m_xScale = 1.0;
    float m_yScale = 1.0;

    // Scale the output width.
    float left = -hWidth * m_xScale;
    float right = hWidth * m_xScale;
    float top = -hHeight * m_yScale;
    float bottom = hHeight * m_yScale;

    float cosTheta = cos(m_angle);
    float sinTheta = sin(m_angle);

    // Apply the scaling and rotation.
    m_videoScreen.aVertices[0].fX = hWidth + (left * cosTheta - top * sinTheta);
    m_videoScreen.aVertices[0].fY = hHeight + (top * cosTheta + left * sinTheta);
    m_videoScreen.aVertices[0].fZ = 0;

    m_videoScreen.aVertices[1].fX = hWidth + (right * cosTheta - top * sinTheta);
    m_videoScreen.aVertices[1].fY = hHeight + (top * cosTheta + right * sinTheta);
    m_videoScreen.aVertices[1].fZ = 0;

    m_videoScreen.aVertices[2].fX = hWidth + (left * cosTheta - bottom * sinTheta);
    m_videoScreen.aVertices[2].fY = hHeight + (bottom * cosTheta + left * sinTheta);
    m_videoScreen.aVertices[2].fZ = 0;

    m_videoScreen.aVertices[3].fX = hWidth + (right * cosTheta - bottom * sinTheta);
    m_videoScreen.aVertices[3].fY = hHeight + (bottom * cosTheta + right * sinTheta);
    m_videoScreen.aVertices[3].fZ = 0;

    // Always leave the UV coordinates at the default values.
    m_videoScreen.aVertices[0].fTu = 0;
    m_videoScreen.aVertices[0].fTv = 0;
    m_videoScreen.aVertices[1].fTu = 1;
    m_videoScreen.aVertices[1].fTv = 0;
    m_videoScreen.aVertices[2].fTu = 0;
    m_videoScreen.aVertices[2].fTv = 1;
    m_videoScreen.aVertices[3].fTu = 1;
    m_videoScreen.aVertices[3].fTv = 1;

    // Tell the XMV player to use the new settings.
    // This locks the vertex buffer so it may cause stalls if called every frame.
    m_xmvPlayer->SetVideoScreen(&m_videoScreen);
}


//--------------------------------------------------------------------------------------
// Name: Update()
// Desc: Called once per frame, the call is the entry point for animating the scene.
//       The movie is played from here.
//--------------------------------------------------------------------------------------
HRESULT XeUnshackle::Update()
{
    // Get the current gamepad state
    ATG::GAMEPAD* pGamepad = ATG::Input::GetMergedInput();

    // If the Auto-Start timer is active, count it down
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

        // Return here so video playback and button presses are not processed when using Auto-Start
        return S_OK;
    }

    if (m_xmvPlayer)
    {
        // 'B' means cancel the movie.
        if (pGamepad->wPressedButtons & XINPUT_GAMEPAD_B)
        {
            m_xmvPlayer->Stop(XMEDIA_STOP_IMMEDIATE);
        }
    }
    else
    {
        // Play the movie if required
        if (bShouldPlaySuccessVid)  //(pGamepad->wPressedButtons & XINPUT_GAMEPAD_A)
        {
            XMEDIA_XMV_CREATE_PARAMETERS XmvParams;

            ZeroMemory(&XmvParams, sizeof(XmvParams));

            // Use the default audio and video streams.
            // If using a wmv file with multiple audio or video streams
            // (such as different audio streams for different languages)
            // the dwAudioStreamId & dwVideoStreamId parameters can be used 
            // to select which audio (or video) stream will be played back

            XmvParams.dwAudioStreamId = XMEDIA_STREAM_ID_USE_DEFAULT;
            XmvParams.dwVideoStreamId = XMEDIA_STREAM_ID_USE_DEFAULT;

            // Play the movie if required
            //if (bShouldPlaySuccessVid)  //(pGamepad->wPressedButtons & XINPUT_GAMEPAD_A)
            //{
            bShouldPlaySuccessVid = FALSE; // Reset so we don't play again
            // Start a movie playing from a file.
            m_bFailed = FALSE;

            // Set the parameters to load the movie from a file.
            //XmvParams.createType = XMEDIA_CREATE_FROM_FILE;
            //XmvParams.createFromFile.szFileName = g_strMovieName;

            // Create from embedded resource
            VOID* pSectionData;
            DWORD dwSectionSize;
            HMODULE hModule = GetModuleHandle(NULL);
            if (XGetModuleSection(hModule, "VID", &pSectionData, &dwSectionSize))
            {

                XmvParams.createType = XMEDIA_CREATE_FROM_MEMORY;
                XmvParams.createFromMemory.pvBuffer = pSectionData;
                XmvParams.createFromMemory.dwBufferSize = dwSectionSize;
                /// Additional fields can be set to control how file IO is done.

                HRESULT hr = XMedia2CreateXmvPlayer(m_pd3dDevice, m_pXAudio2, &XmvParams, &m_xmvPlayer);
                if (SUCCEEDED(hr))
                {
                    InitVideoScreen();
                }
                else
                {
                    m_bFailed = TRUE;
                }
            }
            else
                m_bFailed = TRUE;
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

    // If we are currently playing a movie.
    if (m_xmvPlayer)
    {
        // If RenderNextFrame does not return S_OK then the frame was not
        // rendered (perhaps because it was cancelled) so a regular frame
        // buffer should be rendered before calling present.
        HRESULT hr = m_xmvPlayer->RenderNextFrame(0, NULL);

        // Reset our cached view of what pixel and vertex shaders are set, because
        // it is no longer accurate, since XMV will have set their own shaders.
        // This avoids problems when the shader cache thinks it knows what shader
        // is set and it is wrong.
        m_pd3dDevice->SetVertexShader(0);
        m_pd3dDevice->SetPixelShader(0);
        m_pd3dDevice->SetVertexDeclaration(0);

        if (FAILED(hr) || hr == (HRESULT)XMEDIA_W_EOF)
        {
            // Release the movie object
            m_xmvPlayer->Release();
            m_xmvPlayer = 0;
            // Movie playback changes various D3D states, so you should reset the
            // states that you need after movie playback is finished.
            m_pd3dDevice->SetRenderState(D3DRS_VIEWPORTENABLE, TRUE);

            // Free up any memory allocated for playing from memory.
            if (m_movieBuffer)
            {
                free(m_movieBuffer);
                m_movieBuffer = 0;
            }
        }

    }

    else
    {
        ATG::RenderBackground(0xFF000032, 0xFF000032);
        m_Font.Begin();
        m_Font.SetScaleFactors(1.5f, 1.5f);
        m_Font.DrawText(0, 0, YellowText, wTitleHeaderBuf);

        // Pre-Release Build Identifier
        //m_Font.DrawText(840, 0, WhiteText, L"[TEST BUILD]");
        //

        m_Font.SetScaleFactors(1.0f, 1.0f);

        // General info
        m_Font.DrawText(0, 70, YellowText, currentLocalisation->MainInfo);

		// Bad Storage info
		m_Font.DrawText(0, 260, YellowText, wBadStorageStatusBuf);

        // Dashlaunch Info
        m_Font.DrawText(0, 290, YellowText, wDLStatusBuf);
        if (bDLisLoaded)
        {
            m_Font.DrawText(0, 320, YellowText, currentLocalisation->MainScrDL);
        }

        // Console Info
        m_Font.DrawText(0, 460, YellowText, wConTypeBuf);
        m_Font.DrawText(0, 490, YellowText, wCPUKeyBuf);
        m_Font.DrawText(0, 520, YellowText, wDVDKeyBuf);

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
    }

    
    

    // Present the scene
    m_pd3dDevice->Present(NULL, NULL, NULL, NULL);

    return S_OK;
}

typedef BOOLEAN (*pfnBadStorageExecute)(PBOOLEAN RetailFormatted);

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

	//Execute Bad Storage. Must happen before loading Dashlaunch. This gives people the ability to use internal drives up to 2 TB.
	//If something unusual happens, Bad Storage will pop an XNotify with more details and return FALSE.
	//In cases where it is run with a retail-formatted drive, FALSE is returned, no XNotify is shown, and IsRetailFormatted is set to TRUE. FATXplorer 3.0 beta 36 has the Bad Storage formatting feature.
	//TRUE is returned on successful execution. Bad Storage also checks for repeated executions internally, so there is no problem executing multiple times.
	HMODULE bstorDLL = LoadLibrary("GAME:\\BadStorage.xex.dll");
	ZeroMemory(wBadStorageStatusBuf, sizeof(wBadStorageStatusBuf));
	if (bstorDLL != NULL)
	{
		BOOLEAN bstorIsRetailFormatted;
		if (((pfnBadStorageExecute)GetProcAddress(bstorDLL, (LPCSTR)1))(&bstorIsRetailFormatted))
		{
			swprintf_s(wBadStorageStatusBuf, L"Bad Storage: Applied");
			cprintf("[XeUnshackle] Bad Storage executed successfully");
		}
		else
		{
			swprintf_s(wBadStorageStatusBuf, L"Bad Storage: %s", bstorIsRetailFormatted ? L"Skipped" : L"Failed");
			cprintf("[XeUnshackle] Bad Storage executed unsuccessfully");
		}
		FreeLibrary(bstorDLL);
	}
	else
	{
		swprintf_s(wBadStorageStatusBuf, L"Bad Storage: Missing");
		cprintf("[XeUnshackle] BadStorage.xex.dll not found");
	}

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

    // Run the ui portion of the app with video etc...
    XeUnshackle atgApp;

    // For movie playback we want to synchronize to the monitor.
    atgApp.m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
    ATG::GetVideoSettings(&atgApp.m_d3dpp.BackBufferWidth, &atgApp.m_d3dpp.BackBufferHeight);
    bShouldPlaySuccessVid = TRUE;

    // Load the saved Auto-Start timer, will return negative value when not saved, so it doesn't trigger countdown
    dSavedAutoStartTimer = LoadAutoStart();
    atgApp.SetAutoStartExitTimer(dSavedAutoStartTimer);
    
    atgApp.Run();
}
