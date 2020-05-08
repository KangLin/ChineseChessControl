
!include x64.nsh

Var /GLOBAL MSVC_VERSION

Function InstallRedistributables2019

	messageBox MB_YESNO|MB_ICONQUESTION "$(^Name) needs Visual Studio 2019 Redistributable packages.$\nDo you want to download and install them?" IDNO notinstall2019

    ${If} ${RunningX64}
        NSISdl::download https://aka.ms/vs/16/release/VC_redist.x86.exe $TEMP\vcredist_x64.exe
        Pop $R0 ; Get the return value
        StrCmp $R0 "success" 0 +3
        ExecWait "$TEMP\vcredist_x64.exe /norestart"
        Goto +2
        MessageBox MB_OK "vcredist_x64.exe download failed: $R0"
    ${Else}
        NSISdl::download https://aka.ms/vs/16/release/VC_redist.x64.exe $TEMP\vcredist_x86.exe
        Pop $R0 ; Get the return value
        StrCmp $R0 "success" 0 +3
        ExecWait "$TEMP\vcredist_x86.exe /norestart"
        Goto +2
        MessageBox MB_OK "vcredist_x86.exe download failed: $R0"
    ${EndIf}

	notinstall2019:

FunctionEnd

Function InstallRedistributables2017

	messageBox MB_YESNO|MB_ICONQUESTION "$(^Name) needs Visual Studio 2017 Redistributable packages.$\nDo you want to download and install them?" IDNO notinstall2017

    ${If} ${RunningX64}
        NSISdl::download https://aka.ms/vs/15/release/VC_redist.x64.exe $TEMP\vcredist_x64.exe
        Pop $R0 ; Get the return value
        StrCmp $R0 "success" 0 +3
        ExecWait "$TEMP\vcredist_x64.exe /norestart"
        Goto +2
        MessageBox MB_OK "vcredist_x64.exe download failed: $R0"
    ${Else}
        NSISdl::download https://aka.ms/vs/15/release/VC_redist.x86.exe $TEMP\vcredist_x86.exe
        Pop $R0 ; Get the return value
        StrCmp $R0 "success" 0 +3
        ExecWait "$TEMP\vcredist_x86.exe /norestart"
        Goto +2
        MessageBox MB_OK "vcredist_x86.exe download failed: $R0"
    ${EndIf}

	strCpy $0 "Success"
	Return

	notinstall2017:
FunctionEnd

Function InstallRedistributables2015
 # Check if it is necessary to install to x64VS2015
    ${If} ${RunningX64}
            SetRegView 64
            ReadRegStr $0 HKLM "SOFTWARE\Classes\Installer\Dependencies\{3ee5e5bb-b7cc-4556-8861-a00a82977d6c}" "Version"
            IfErrors 0 notinstall2015
    ${Else}
            ReadRegStr $0 HKLM "SOFTWARE\Classes\Installer\Dependencies\{23daf363-3020-4059-b3ae-dc4ad39fed19}" "Version"
            IfErrors 0 notinstall2015
       
    ${EndIf}

	messageBox MB_YESNO|MB_ICONQUESTION "$(^Name) needs Visual Studio 2015 Redistributable packages.$\nDo you want to download and install them?" IDNO notinstall2015
	${If} ${RunningX64}
        NSISdl::download http://download.microsoft.com/download/C/E/5/CE514EAE-78A8-4381-86E8-29108D78DBD4/VC_redist.x64.exe $TEMP\vcredist_x64.exe
        Pop $R0 ; Get the return value
        StrCmp $R0 "success" 0 +3
        ExecWait "$TEMP\vcredist_x64.exe /norestart"
        Goto +2
        MessageBox MB_OK "vcredist_x64.exe download failed: $R0"
    ${Else}
        NSISdl::download http://download.microsoft.com/download/C/E/5/CE514EAE-78A8-4381-86E8-29108D78DBD4/VC_redist.x86.exe $TEMP\vcredist_x86.exe
        Pop $R0 ; Get the return value
        StrCmp $R0 "success" 0 +3
        ExecWait "$TEMP\vcredist_x86.exe /norestart"
        Goto +2
        MessageBox MB_OK "vcredist_x86.exe download failed: $R0"
    ${EndIf}

	notinstall2015:

FunctionEnd

Function InstallRedistributables2013

    # Check if it is necessary to install to x64VS2013
    ${If} ${RunningX64}
            SetRegView 64
            ReadRegStr $0 HKLM "SOFTWARE\Classes\Installer\Dependencies\{050d4fc8-5d48-4b8f-8972-47c82c46020f}" "Version"
            IfErrors 0 notinstall2013
    ${Else}
            ReadRegStr $0 HKLM "SOFTWARE\Classes\Installer\Dependencies\{f65db027-aff3-4070-886a-0d87064aabb1}" "Version"
            IfErrors 0 notinstall2013
    ${EndIf}

	messageBox MB_YESNO|MB_ICONQUESTION "$(^Name) needs Visual Studio 2013 Redistributable packages.$\nDo you want to download and install them?" IDNO notinstall2013

    ${If} ${RunningX64}
        NSISdl::download http://download.microsoft.com/download/2/E/6/2E61CFA4-993B-4DD4-91DA-3737CD5CD6E3/vcredist_x64.exe $TEMP\vcredist_x64.exe
        Pop $R0 ; Get the return value
        StrCmp $R0 "success" 0 +3
        ExecWait "$TEMP\vcredist_x64.exe /norestart"
        Goto +2
        MessageBox MB_OK "vcredist_x64.exe download failed: $R0"
    ${Else}
        NSISdl::download http://download.microsoft.com/download/2/E/6/2E61CFA4-993B-4DD4-91DA-3737CD5CD6E3/vcredist_x86.exe $TEMP\vcredist_x86.exe
        Pop $R0 ; Get the return value
        StrCmp $R0 "success" 0 +3
        ExecWait "$TEMP\vcredist_x86.exe /norestart"
        Goto +2
        MessageBox MB_OK "vcredist_x86.exe download failed: $R0"
    ${EndIf}

	notinstall2013:

FunctionEnd

Function InstallRedistributables2010

	${If} ${RunningX64}
            SetRegView 64
            ReadRegDword $0 HKLM "SOFTWARE\Classes\Installer\Products\1926E8D15D0BCE53481466615F760A7F" "Version"
            IfErrors 0 notinstall2010
    ${Else}
            ReadRegDword $0 HKLM "SOFTWARE\Classes\Installer\Products\1D5E3C0FEDA1E123187686FED06E995A" "Version"
            IfErrors 0 notinstall2010
    ${EndIf}

	messageBox MB_YESNO|MB_ICONQUESTION "$(^Name) needs Visual Studio 2010 Redistributable packages.$\nDo you want to download and install them?" IDNO notinstall2010

    ${If} ${RunningX64}
        NSISdl::download https://download.microsoft.com/download/1/6/5/165255E7-1014-4D0A-B094-B6A430A6BFFC/vcredist_x64.exe $TEMP\vcredist_x64.exe
        Pop $R0 ; Get the return value
        StrCmp $R0 "success" 0 +3
        ExecWait "$TEMP\vcredist_x64.exe /norestart"
        Goto +2
        MessageBox MB_OK "vcredist_x64.exe download failed: $R0"
    ${Else}
        NSISdl::download https://download.microsoft.com/download/1/6/5/165255E7-1014-4D0A-B094-B6A430A6BFFC/vcredist_x86.exe $TEMP\vcredist_x86.exe
        Pop $R0 ; Get the return value
        StrCmp $R0 "success" 0 +3
        ExecWait "$TEMP\vcredist_x86.exe /norestart"
        Goto +2
        MessageBox MB_OK "vcredist_x86.exe download failed: $R0"
    ${EndIf}

    notinstall2010:

FunctionEnd

Function InstallRedistributables

	;MSVC_VERSION È¡Öµ£º
    ;1200      = VS  6.0
    ;1300      = VS  7.0
    ;1310      = VS  7.1
	;1400      = VS  8.0 (v80 toolset)
	;1500      = VS  9.0 (v90 toolset)
	;1600      = VS 10.0 (v100 toolset) MS2010
	;1700      = VS 11.0 (v110 toolset) MS2012
	;1800      = VS 12.0 (v120 toolset) MS2013
	;1900      = VS 14.0 (v140 toolset) MS2015
	;1910-1919 = VS 15.0 (v141 toolset) MS2017
	;1920-1929 = VS 16.0 (v142 toolset) MS2019

    IntCmp $MSVC_VERSION 1600 0 InstallRedistributablesEND +3
	call InstallRedistributables2010
    Goto InstallRedistributablesEND

	IntCmp $MSVC_VERSION 1800 0 InstallRedistributablesEND +3
	call InstallRedistributables2013
	Goto InstallRedistributablesEND

	IntCmp $MSVC_VERSION 1900 0 InstallRedistributablesEND +3
	call InstallRedistributables2015
	Goto InstallRedistributablesEND

	IntCmp $MSVC_VERSION 1920 +3 0 +3
	call InstallRedistributables2017
	Goto InstallRedistributablesEND

	IntCmp $MSVC_VERSION 1930 +3 0 +3
	call InstallRedistributables2019
	Goto InstallRedistributablesEND

	InstallRedistributablesEND:
FunctionEnd
