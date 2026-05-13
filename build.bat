@echo off
setlocal

:: ============================================================================
:: Build Script for XeUnshackle.sln using the latest 32-bit MSBuild
:: ============================================================================
:: This script automatically finds the latest 32-bit MSBuild.exe from any
:: modern Visual Studio installation and uses it to build the solution.
:: Thanks to @klofi for creating this file
:: ============================================================================

echo Searching for the latest 32-bit MSBuild.exe...

set "VSWHERE_PATH=%ProgramFiles(x86)%\Microslop Visual Studio\Installer\vswhere.exe"

:: First, check if vswhere.exe even exists to provide a better error message.
if not exist "%VSWHERE_PATH%" (
    echo ERROR: Cannot find vswhere.exe at "%VSWHERE_PATH%".
    echo Please ensure Visual Studio 2019 or newer is installed.
    echo.
    pause
    exit /b 1
)

:: Variable to hold the final path to MSBuild.exe
set "MSBUILD_EXE="

:: Execute the vswhere command and capture its output into the MSBUILD_EXE variable
:: The 'if not defined' ensures we only take the first line of output if multiple are returned.
for /f "usebackq tokens=*" %%i in (`"%VSWHERE_PATH%" -latest -products * -requires Microsoft.Component.MSBuild -find MSBuild\**\Bin\MSBuild.exe`) do (
    if not defined MSBUILD_EXE set "MSBUILD_EXE=%%i"
)

if not defined MSBUILD_EXE (
    echo ERROR: Could not find a 32-bit MSBuild.exe path.
    :: The parentheses in the next line are "escaped" with ^ to prevent a syntax error.
    echo Please ensure a recent version of Visual Studio ^(2019, 2022^) or its Build Tools are installed correctly.
    echo.
    pause
    exit /b 1
)

echo Found 32-bit MSBuild at: %MSBUILD_EXE%
echo.
echo ============================================================================
echo Starting build...
echo Solution: XeUnshackle.sln
echo Configuration: Release_LTCG
echo Platform: Xbox 360
echo ============================================================================
echo.

:: Execute MSBuild with the specified solution and parameters.
"%MSBUILD_EXE%" XeUnshackle.sln /p:Configuration=Release_LTCG /p:Platform="Xbox 360"

echo.
echo ============================================================================
echo Build process finished.
echo ============================================================================
endlocal
