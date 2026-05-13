# XeUnshackle
![XeUnshackle_Banner](https://github.com/user-attachments/assets/af37d4ae-4ff6-4175-8f81-47869ff63ed6)

Custom Xbox 360 application designed to be used with the [Xbox360BadUpdate](https://github.com/grimdoomer/Xbox360BadUpdate) exploit.  

> [!IMPORTANT]  
> **THIS APP IS RELEASED AS IS.**  
> **YOU ARE RESPONSIBLE FOR WHAT YOU CHOOSE TO LOAD AND ANY NEGATIVE EFFECTS THAT MAY COME AS A RESULT.**  
> **THIS IS NOT A PERMANENT SOFTMOD!** Your console will return to an unmodified state when powered off or rebooted.

> [!CAUTION]
> * **BACKUP YOUR NAND!** This should be the first thing you do.
> * **DO NOT FLASH MODIFIED NAND IMAGES!** You will **brick** your console.
> * **DO NOT REPLACE FILES IN FLASH!** This includes things like replacing the bootanim.
> * Avoid using homebrew or plugins that make changes to FLASH (the nand).
> * Read the **README - IMPORTANT.txt** in the release files for important notes regarding the use of Stealth Servers.

Utilises the _alternate_ method of using a specially crafted PeekPoke HV expansion to apply **temporary** HV patches.  
This is usually the preferred method of HV access used by Stealth servers.  
Access via the Syscall0 backdoor is also available upon completion for apps requiring it (Simple 360 NAND Flasher for example).  

Nothing here is particularly new. It's simply a collection of existing code that has been adapted and packaged for use with this exploit.

## Build / video conversion
See BUILD.md and VideoFormatGuide.MD

## Features
- Applies a full complete patchset of both HV & Kernel patches. These are the same exact patches that are usually applied when building a modified nand image using xeBuild for RGH/JTAG consoles.
- Support for both Retail & Devkit signed xex files. Essentially any plugins or executables that run natively on RGH/JTAG modified consoles _should_ work.
- Reverts any patches applied by the [Xbox360BadUpdate](https://github.com/grimdoomer/Xbox360BadUpdate) exploit we no longer need.
- Restores the default state of the Ring of Light and allows controller syncing to function as normal. Thanks [InvoxiPlayGames](https://github.com/InvoxiPlayGames)
- Loads a slightly modified version of launch.xex (Dashlaunch). Due to it not being stored within the nands filesystem it is loaded from app memory and lhelper.xex is copied to either Hdd or Usb root depending on what's available at load time.
- Simple GUI consisting of a short boot animation video followed by a page displaying both the CPUKey and DVDKey of the console.
- Ability to dump 1BL to file via button press. This may be particularly useful for those wanting to use the Low Level [Xenon](https://github.com/xenon-emu/xenon) Emulator.
- Automatic dumping of the current MAC address on first load. This is often changed by stealth servers during the initial KV spoofing. Only other way to retrieve the original is from a nand backup taken BEFORE loading a stealth.
- Applies Usbdsec patches to allow non-360 XInput controllers. Thanks [InvoxiPlayGames](https://github.com/InvoxiPlayGames)
- Xbox 360 Bad Storage support for unlocking up to 2 TB internal storage. Read the official release notes [Here](https://fatxplorer.eaton-works.com/bad-storage/) for setup instructions. Thanks [EatonZ](https://github.com/EatonZ)

## Usage
#### Dashlaunch Plugin Loading:
1. Add the plugins you want to load to the [Plugins] section of the launch.ini provided and copy it to the root of the usb. 
2. Copy any plugin files to the usb.  
Upon successful exploit XeUnshackle will run and attempt to load launch.xex (Dashlaunch) in the background.  
Dashlaunch will then attempt to load any plugins set when exiting the app and returning to the dashboard.

#### Save / Dump Options:
Any files saved/dumped can be found in the BadUpdatePayload folder of the usb.

## Credits
- [grimdoomer](https://github.com/grimdoomer) - [Xbox360BadUpdate](https://github.com/grimdoomer/Xbox360BadUpdate) exploit
- cOz - xeBuild patches, Dashlaunch & much more
- [Visual Studio / Goobycorp](https://github.com/GoobyCorp)
- Diamond
- [InvoxiPlayGames / Emma](https://github.com/InvoxiPlayGames) - [FreeMyXe](https://github.com/FreeMyXe), [Usbdsec patches](https://github.com/InvoxiPlayGames/UsbdSecPatch), Ring of Light fix, [DaTArrest save exploit](https://github.com/RBEnhanced/DaTArrest) & general help
- [ihatecompvir](https://github.com/ihatecompvir) - [DaTArrest save exploit](https://github.com/RBEnhanced/DaTArrest)
- ikari - freeBOOT
- [Jeff Hamm](https://www.youtube.com/watch?v=PantVXVEVUg) - Chain break video
- [EatonZ](https://github.com/EatonZ) - [Xbox 360 Bad Storage](https://github.com/EatonZ/BadStorage)
- [Xbox360Hub Discord #coding-corner](https://xbox360hub.com/)
- Anyone else who has contributed anything to the 360 scene. Apologies if any credits were missed.

## Community Translations
- Spanish - [CiberStore](https://github.com/CiberStore)
- Portuguese (Brazil) - [ronniegchagas](https://github.com/ronniegchagas)
