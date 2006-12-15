/*
	NSIS2 install script for OpenGUI
	Author: Eric Shorkey
	Initial creation by: HM NIS Editor
*/


!define BUILD_DIR "tmp"
!define PRODUCT_NAME "OpenGUI SDK"
!define PRODUCT_VERSION "0.8"
!define PRODUCT_CODENAME "Kunzite"
!define PRODUCT_WEB_SITE "http://opengui.sourceforge.net/"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\OpenGUI_SDK"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"

;SetCompressor zlib ;only used for build testing because it's much faster
SetCompressor /FINAL /SOLID lzma ;used for finals because it's much better

#########  INCLUDES  #########
; Include Environment Management Functions
!define ALL_USERS
!include WriteEnvStr.nsh
; MUI because we're lazy
!include "MUI.nsh"

## MUI Settings
!define MUI_ABORTWARNING
!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\modern-install.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"
; Header image settings
!define MUI_HEADERIMAGE
!define MUI_HEADERIMAGE_BITMAP "header.bmp"
!define MUI_HEADERIMAGE_RIGHT
; Don't call it a "Readme"
!define MUI_FINISHPAGE_SHOWREADME_TEXT "View Relesae Notes?"
!define MUI_FINISHPAGE_SHOWREADME "$INSTDIR\RELEASE_NOTES.txt"


; Welcome page
!insertmacro MUI_PAGE_WELCOME
; License page
;!insertmacro MUI_PAGE_LICENSE "OpenGUI\LICENSE.TXT"
; Components page
!insertmacro MUI_PAGE_COMPONENTS
; Directory page
!insertmacro MUI_PAGE_DIRECTORY
; Instfiles page
!insertmacro MUI_PAGE_INSTFILES
; Finish page
!insertmacro MUI_PAGE_FINISH

; Uninstaller pages
!insertmacro MUI_UNPAGE_INSTFILES

; Language files
!insertmacro MUI_LANGUAGE "English"

; Reserve files
!insertmacro MUI_RESERVEFILE_INSTALLOPTIONS



Name "${PRODUCT_NAME} v${PRODUCT_VERSION} [${PRODUCT_CODENAME}]"
OutFile "OpenGUI_SDK_${PRODUCT_VERSION}.exe"
InstallDir "c:\OpenGUI_SDK"
InstallDirRegKey HKLM "${PRODUCT_DIR_REGKEY}" ""
ShowInstDetails hide
ShowUnInstDetails hide



#########  FUNCTIONS  #########
Function AddEnvVars
; OPENGUI_HOME
; OPENGUI_INCLUDE
; OPENGUI_VC8
; OPENGUI_VC71
	Push "OPENGUI_HOME"
	Push $INSTDIR
	Call WriteEnvStr
	Push "OPENGUI_INCLUDE"
	Push "$INSTDIR\OpenGUI\include"
	Call WriteEnvStr
	Push "OPENGUI_VC8"
	Push "$INSTDIR\OpenGUI\vc8"
	Call WriteEnvStr
	Push "OPENGUI_VC71"
	Push "$INSTDIR\OpenGUI\vc71"
	Call WriteEnvStr
FunctionEnd
Function un.RemoveEnvVars
; OPENGUI_HOME
; OPENGUI_INCLUDE
; OPENGUI_VC8
; OPENGUI_VC71
	Push MyEnvVar
	Push "OPENGUI_HOME"
	Call un.DeleteEnvStr
	Push "OPENGUI_INCLUDE"
	Call un.DeleteEnvStr
	Push "OPENGUI_VC8"
	Call un.DeleteEnvStr
	Push "OPENGUI_VC71"
	Call un.DeleteEnvStr
FunctionEnd

#########  INSTALL SECTIONS  #########
Section -AdditionalIcons
	SetOutPath "$INSTDIR"
	File "${BUILD_DIR}\src\CHANGELOG.txt"
	File "${BUILD_DIR}\src\RELEASE_NOTES.txt"
	CreateDirectory "$SMPROGRAMS\OpenGUI SDK"
	WriteIniStr "$INSTDIR\OpenGUI_Website.url" "InternetShortcut" "URL" "${PRODUCT_WEB_SITE}"
	CreateShortCut "$SMPROGRAMS\OpenGUI SDK\OpenGUI Website.lnk" "$INSTDIR\OpenGUI_Website.url"
	CreateShortCut "$SMPROGRAMS\OpenGUI SDK\Uninstall.lnk" "$INSTDIR\uninst.exe"
	CreateShortCut "$SMPROGRAMS\OpenGUI SDK\Change Log.lnk" "$INSTDIR\CHANGELOG.txt"
	CreateShortCut "$SMPROGRAMS\OpenGUI SDK\Release Notes.lnk" "$INSTDIR\RELEASE_NOTES.txt"
	CreateShortCut "$SMPROGRAMS\OpenGUI SDK\Open Directory.lnk" "$INSTDIR"
SectionEnd


Section "Precompiled SDKs" SEC01
	SetOutPath "$INSTDIR"
	File /r "${BUILD_DIR}\Demos"
	File /r "${BUILD_DIR}\OpenGUI"
	CreateShortCut "$SMPROGRAMS\OpenGUI SDK\OpenGUI API Documentation.lnk" "$INSTDIR\OpenGUI\OpenGUI.chm"  
	File /r "${BUILD_DIR}\Renderer_Ogre"
	CreateShortCut "$SMPROGRAMS\OpenGUI SDK\Ogre Documentation.lnk" "$INSTDIR\Renderer_Ogre\Renderer_Ogre.chm"
	File /r "${BUILD_DIR}\Renderer_OpenGL"
	
	CreateShortCut "$SMPROGRAMS\OpenGUI SDK\Amethyst Documentation.lnk" "$INSTDIR\Amethyst\Amethyst.chm"
	File /r "${BUILD_DIR}\Amethyst"
	Call AddEnvVars
SectionEnd


Section "Install Source" SEC02
	SetOutPath "$INSTDIR"
	File /r "${BUILD_DIR}\src"
SectionEnd


Section -Post
	WriteUninstaller "$INSTDIR\uninst.exe"
	WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR"
	WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
	WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
	WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
	WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
SectionEnd

; Section descriptions
!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
!insertmacro MUI_DESCRIPTION_TEXT ${SEC01} "Precompiled SDKs for Visual Studio 2005 and Visual Studio.NET 2003"
!insertmacro MUI_DESCRIPTION_TEXT ${SEC02} "Compilable Source. Requires SCons. Ogre is required to build the Ogre renderer."
!insertmacro MUI_FUNCTION_DESCRIPTION_END


#########  UNINSTALL SECTIONS  #########
Function un.onUninstSuccess
	HideWindow
	MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) was successfully removed from your computer."
FunctionEnd

Function un.onInit
	MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "Are you sure you want to completely remove $(^Name) and all of its components?" IDYES +2
	Abort
FunctionEnd


Section Uninstall
	ReadRegStr $0 HKLM "${PRODUCT_DIR_REGKEY}" ""
	StrCmpS $0 "" 0 +2 ;If we can't get the last known install location, abort
		Abort "Cannot uninstall properly. Registry is missing previous installation information."
	
	RMDir /r "$SMPROGRAMS\OpenGUI SDK"
	RMDir /r $0
	
	Call un.RemoveEnvVars

	DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
	DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
	SetAutoClose true
SectionEnd