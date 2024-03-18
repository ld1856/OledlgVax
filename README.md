# OledlgVax
Vax patch and keygen
supported x64 and win32.

patch base on [OLEDLG-for-Visual-Assist-X](https://github.com/lvtx/OLEDLG-for-Visual-Assist-X.git)

keygen fork from [VisualAssist-keygen-demo](https://github.com/DoubleLabyrinth/VisualAssist-keygen-demo.git)

using:
1. rundll32.exe oledlgvax.dll,GenerateKey -renew *[UserName] 255[Count] 2099/12/12[Expire date]
2. vs2019(Win32 build): Rename vcruntime140.dll to vcruntime140_r.dll,rename OledlgVax.dll to vcruntime140.dll
   vs2022(x64 build): rename msenv.dll to msenv_r.dll and rename OledlgVax to msenv.dll
