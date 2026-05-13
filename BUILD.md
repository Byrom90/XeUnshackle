# How to build?

## Requirements

To build XeUnshackle, you need a development environment on Windows, with:
* Visual Studio 2010
  * VS 2010 Professional ([installer here](https://archive.org/details/en_visual_studio_2010_professional_x86_dvd_509727)), install at minimum these features:
    * Visual C++
    * Visual C#
    * Graphics Library
  * VS 2010 SP1 ([installer here](https://archive.org/details/vs-2010-sp-1dvd-1))
* Install Xbox 360 SDK
  * [Download here.](https://archive.org/details/xdkcollection)
  * Use `XDKSetupXenon21256.3.exe` or `XDKSetupXenon21256.17.exe`, choose Full install
  * Install this **after** VS 2010 and VS 2010 SP1
* Visual Studio 2019 ([installer here](https://archive.org/download/vs_community__e8aae2bc1239469a8cb34a7eeb742747/vs_community_2019.exe)) or Visual Studio 2022

## Build in IDE

### VS 2019
Open the [`XeUnshackle.sln`](XeUnshackle.sln) file and Build Solution (F7).

### VS 2022
When you run Buld Solution in VS 2022, it will fail on this error:
```
...
error MSB4062: The "CL" task could not be loaded from the assembly C:\Program Files (x86)\Microsoft Xbox 360 SDK\bin\win32\Microsoft.Xna.Xbox360.Build.dll
...
An attempt was made to load a program with an incorrect format.
...
```

The build fails because Visual Studio 2022 is a 64-bit application, while the old Xbox 360 XDK and its build tools (like Microsoft.Xna.Xbox360.Build.dll) are 32-bit. A 64-bit process cannot load 32-bit DLLs, which causes the "incorrect format" error. Visual Studio 2019 and all prior versions are 32-bit applications, so they are compatible with the 32-bit XDK toolchain.

To work around this issue, you can use a custom [`build.bat`](build.bat) script to build using the 32-bit MSBuild. You can run the [`build.bat`](build.bat) file directly from Visual Studio's Tools menu. This lets you trigger custom build process with a single click. Here’s how to set it up:

1. VS 2022 > `Tools` > `External Tools...` > `Add`
2. Fill in the field as follows:
   * Title: `Build Solution 32-bit`
   * Command: `cmd.exe`
   * Arguments: `/c "$(SolutionDir)build.bat"`
   * Initial directory: `$(SolutionDir)`
3. Check the `Use Output window` box. This is important because it will show the script's output directly in Visual Studio's `Output` panel, so you can see the build progress and any errors.
4. Click OK

To run it simply click `Tools` > `Build Solution 32-bit`, the output will appear in the `Output` window (you may need to change the `Show output from:` dropdown to `Build Solution 32-bit`).

### JetBrains Rider

[Rider](https://www.jetbrains.com/rider/) allows to select a custom version of MSBuild, so the setup is much easier than VS 2022 and fully integrated into the IDE.

1. Open the [`XeUnshackle.sln`](XeUnshackle.sln) file.
2. Open `Settings` > `Build, Execution, Deployment` > `Toolset and Build` and click on `Custom...` next to `MSBuild version`
3. Select the 32-bit `Bin\MSBuild.exe` of your installed modern VS (2019+). Note this must **not** be `Bin\amd64\MSBuild.exe` as that would be the incompatible 64-bit version. Example of the correct path: `C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe`
4. Build Solution (Ctrl+F9)