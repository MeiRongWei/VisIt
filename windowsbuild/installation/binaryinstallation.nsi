; Script generated by the HM NIS Edit Script Wizard.

##############################################################################
#
# File: binaryinstallation.nsi
#
# Purpose: This file contains the instructions that the NSIS installer needs
#          in order to create an installation program for VisIt.
#
# Programmer: Brad Whitlock
# Date:       Mon, Dec 15 11:26:34 PDT 2003
#
# Modifications:
#   Brad Whitlock, Mon Feb 9 14:45:04 PST 2004
#   Updated for 1.2.7
#
#   Brad Whitlock, Fri Mar 5 09:40:50 PDT 2004
#   Updated for 1.2.8.
#
#   Brad Whitlock, Wed Apr 14 16:22:49 PST 2004
#   Updated for 1.3.
#
#   Brad Whitlock, Thu May 27 18:19:35 PST 2004
#   Updated for 1.3.1.
#
#   Brad Whitlock, Tue Jun 29 13:08:46 PST 2004
#   Updated for 1.3.2.
#
#   Brad Whitlock, Wed Jul 14 09:19:08 PDT 2004
#   Updated for 1.3.3 and made it save the registry keys that VisIt needs
#   in order to run to user-accessible registry keys so installing VisIt
#   without admin access does not prevent VisIt from running at all.
#
#   Brad Whitlock, Thu Aug 12 11:11:30 PDT 2004
#   Updated for 1.3.4.
#
#   Brad Whitlock, Thu Sep 23 09:39:32 PDT 2004
#   Updated for 1.3.5.
#
#   Brad Whitlock, Wed Nov 3 14:06:27 PST 2004
#   Updated for 1.4.
#
#   Brad Whitlock, Wed Jan 5 17:23:57 PST 2005
#   Updated for 1.4.1.
#
#   Brad Whitlock, Thu Feb 24 16:09:17 PST 2005
#   Updated for 1.4.2. I also added more configuration screens that allow
#   the user to pick a default database format.
#
#   Brad Whitlock, Tue May 10 14:13:57 PST 2005
#   Updated for 1.4.3.
#
#   Brad Whitlock, Mon Jun 6 17:01:48 PST 2005
#   Added support for setting VisIt's install location as a Java preference
#   using our VIkit plugin.
#
#   Brad Whitlock, Fri Jun 24 10:35:49 PDT 2005
#   Added support for saving movies at the resolution stored in the
#   session file.
#
#   Brad Whitlock, Fri Jul 8 15:40:16 PST 2005
#   Added code to move config files if there are any from older versions
#   of VisIt.
#
#   Brad Whitlock, Thu Aug 18 12:01:28 PDT 2005
#   Updated for 1.4.5.
#
#   Brad Whitlock, Tue Nov 22 13:40:59 PST 2005
#   Updated for 1.5.
#
#   Brad Whitlock, Wed Feb 1 11:48:25 PDT 2006
#   Updated for 1.5.1.
#
#   Brad Whitlock, Thu Mar 16 13:36:13 PST 2006
#   Updated for 1.5.2.
#
#   Brad Whitlock, Tue Jun 13 15:12:31 PST 2006
#   Updated for 1.5.3
#
##############################################################################

; HM NIS Edit Wizard helper defines
!define PRODUCT_NAME "VisIt"
!define PRODUCT_VERSION "1.5.3"
!define PRODUCT_PUBLISHER "LLNL"
!define PRODUCT_WEB_SITE "http://www.llnl.gov/visit"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\visit${PRODUCT_VERSION}.exe"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME} ${PRODUCT_VERSION}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"

# Define macros for Qt.
!define QTPATH "C:\Qt\3.0.2"
!define QTDLL  "qt-mt302.dll"

SetCompressor bzip2

; MUI 1.67 compatible ------
!include "MUI.nsh"

; MUI Settings
!define MUI_ABORTWARNING
!define MUI_ICON "..\resources\visit.ico"
!define MUI_UNICON "..\resources\visit.ico"
#!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"

ReserveFile "NetworkConfig.ini"
ReserveFile "WantDatabasePlugin.ini"
ReserveFile "DefaultDatabasePlugin.ini"
ReserveFile "ClickInstall.ini"

; Reserve files
!insertmacro MUI_RESERVEFILE_INSTALLOPTIONS

; Welcome page
!insertmacro MUI_PAGE_WELCOME
; License page
!insertmacro MUI_PAGE_LICENSE "copyright.txt"
; Directory page
!insertmacro MUI_PAGE_DIRECTORY
; Custom
page custom ChooseNetworkConfig
page custom WantDefaultDatabasePlugin
page custom ChooseDefaultDatabasePlugin

; Instfiles page
!insertmacro MUI_PAGE_INSTFILES
; Finish page
!define MUI_FINISHPAGE_RUN "$INSTDIR\visit.exe"
!insertmacro MUI_PAGE_FINISH

; Uninstaller pages
!insertmacro MUI_UNPAGE_INSTFILES

; Language files
!insertmacro MUI_LANGUAGE "English"


; MUI end ------

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "..\installation\visit${PRODUCT_VERSION}-win98.exe"
InstallDir "$PROGRAMFILES\LLNL\VisIt ${PRODUCT_VERSION}"
InstallDirRegKey HKLM "${PRODUCT_DIR_REGKEY}" ""
ShowInstDetails show
ShowUnInstDetails show

Var CreatedPythonLinks
Var DefaultDatabase
Var SelectingDefaultDatabase

###############################################################################
#
# Functions
#
###############################################################################

Function .onInit
  ;Extract InstallOptions INI files
  !insertmacro MUI_INSTALLOPTIONS_EXTRACT "NetworkConfig.ini"
  !insertmacro MUI_INSTALLOPTIONS_EXTRACT "WantDatabasePlugin.ini"
  !insertmacro MUI_INSTALLOPTIONS_EXTRACT "DefaultDatabasePlugin.ini"
  !insertmacro MUI_INSTALLOPTIONS_EXTRACT "ClickInstall.ini"
  Strcpy $SelectingDefaultDatabase "no"
  Strcpy $DefaultDatabase ""
FunctionEnd

#
# This function is called when we show the Network configuration screen.
#
Function ChooseNetworkConfig
  !insertmacro MUI_HEADER_TEXT "Network configuration" "Select the desired network configuration."
  !insertmacro MUI_INSTALLOPTIONS_DISPLAY "NetworkConfig.ini"
FunctionEnd

#
# This function is called when we show the WantDatabasePlugin screen. We read whether
# the user chose yes or no and use that to set a variable that we use to determine the
# look of the next page.
#
Function WantDefaultDatabasePlugin
  !insertmacro MUI_HEADER_TEXT "Select default database reader plugin" "Do you want to select a default database reader plugin?"
  !insertmacro MUI_INSTALLOPTIONS_DISPLAY "WantDatabasePlugin.ini"

  # Get whether or not the user selected a default file format.
  !insertmacro MUI_INSTALLOPTIONS_READ $0 "WantDatabasePlugin.ini" "Field 1" "State"
  # If $0=="1" then we're going to have a networkconfig
  Strcmp $0 "1" NoDefaultDatabase PickedDefaultDatabase
PickedDefaultDatabase:
    # We got here because we picked a default database. Enable the database plugin combobox.
    Strcpy $SelectingDefaultDatabase "yes"
    Goto EndWantDefaultDatabasePlugin
NoDefaultDatabase:
    # We got here because we picked no default database.
    Strcpy $SelectingDefaultDatabase "no"
EndWantDefaultDatabasePlugin:
FunctionEnd

#
# This function is called when we want to actually choose a database reader plugin. If the
# user chose not to set up a database reader plugin then we show the "Click install"
# screen instead.
#
Function ChooseDefaultDatabasePlugin
  Strcmp $SelectingDefaultDatabase "yes" YesPickDatabase NoPickDatabase
YesPickDatabase:
  !insertmacro MUI_HEADER_TEXT "Select default database reader plugin" "Select the database reader plugin that VisIt will try first when opening a database."
  !insertmacro MUI_INSTALLOPTIONS_DISPLAY "DefaultDatabasePlugin.ini"
  !insertmacro MUI_INSTALLOPTIONS_READ $0 "DefaultDatabasePlugin.ini" "Field 1" "State"
   Strcpy $DefaultDatabase "-default_format $0"
   Goto EndChooseDefaultDatabasePlugin
NoPickDatabase:
  !insertmacro MUI_HEADER_TEXT "Install VisIt now" "Click the Install button to install VisIt."
  !insertmacro MUI_INSTALLOPTIONS_DISPLAY "ClickInstall.ini"
EndChooseDefaultDatabasePlugin:
FunctionEnd

###############################################################################
#
# Sections
#
###############################################################################

Section "Executable Components" SEC01
  SetOutPath "$INSTDIR"
  SetOverwrite ifnewer
  File "..\bin\Release\*.dll"
  File "..\bin\Release\*.exe"
  File "..\bin\Release\visit-config-closed.ini"
  File "..\bin\Release\visit-config-open.ini"
  File "..\bin\Release\xml2plugin.bat"
  File "..\bin\Release\makemovie.py"
  File "..\bin\Release\makemoviemain.py"
        
  CreateDirectory "$SMPROGRAMS\VisIt ${PRODUCT_VERSION}"
  CreateShortCut "$SMPROGRAMS\VisIt ${PRODUCT_VERSION}\VisIt ${PRODUCT_VERSION}.lnk"     "$INSTDIR\visit.exe" ""     "" 0 SW_SHOWMINIMIZED "" "VisIt allows you to visualize simulation data."
  CreateShortCut "$DESKTOP\VisIt ${PRODUCT_VERSION}.lnk"                                 "$INSTDIR\visit.exe" ""     "" 0 SW_SHOWMINIMIZED "" "VisIt allows you to visualize simulation data."
  CreateShortCut "$SMPROGRAMS\VisIt ${PRODUCT_VERSION}\VisIt Command Line Interface.lnk" "$INSTDIR\visit.exe" "-cli" "" 0 SW_SHOWNORMAL    "" "VisIt's command line interface allows you to visualize simulation data via Python scripting."
  CreateShortCut "$SMPROGRAMS\VisIt ${PRODUCT_VERSION}\Silex.lnk"                        "$INSTDIR\silex.exe" ""     "" 0 SW_SHOWNORMAL    "" "Silex allows you to browse the contents of Silo files."
  # Icon files
  File "..\resources\*.ico"
  # Qt DLL
  File "${QTPATH}\lib\${QTDLL}"
SectionEnd

Section "Database plugins" SEC02
  SetOutPath "$INSTDIR\databases"
  File "..\bin\Release\databases\libI*.dll"
  File "..\bin\Release\databases\libE*.dll"
  File "..\bin\Release\databases\libM*.dll"
SectionEnd

Section "Plot plugins" SEC03
  SetOutPath "$INSTDIR\plots"
  File "..\bin\Release\plots\libI*.dll"
  File "..\bin\Release\plots\libE*.dll"
  File "..\bin\Release\plots\libG*.dll"
  File "..\bin\Release\plots\libS*.dll"
  File "..\bin\Release\plots\libV*.dll"
SectionEnd

Section "Operator plugins" SEC04
  SetOutPath "$INSTDIR\operators"
  File "..\bin\Release\operators\libI*.dll"
  File "..\bin\Release\operators\libE*.dll"
  File "..\bin\Release\operators\libG*.dll"
  File "..\bin\Release\operators\libS*.dll"
  File "..\bin\Release\operators\libV*.dll"
SectionEnd

Section "Python modules" SEC05
  SetOutPath "$INSTDIR\Python\DLLs"
  File "..\bin\Release\Python\DLLs\_socket.pyd"
  File "..\bin\Release\Python\DLLs\xmltok.dll"
  File "..\bin\Release\Python\DLLs\xmlparse.dll"
  File "..\bin\Release\Python\DLLs\winsound.pyd"
  File "..\bin\Release\Python\DLLs\unicodedata.pyd"
  File "..\bin\Release\Python\DLLs\select.pyd"
  File "..\bin\Release\Python\DLLs\pyexpat.pyd"
  File "..\bin\Release\Python\DLLs\parser.pyd"
  File "..\bin\Release\Python\DLLs\mmap.pyd"
  File "..\bin\Release\Python\DLLs\bsddb.pyd"
  File "..\bin\Release\Python\DLLs\_winreg.pyd"
  File "..\bin\Release\Python\DLLs\_tkinter.pyd"
  File "..\bin\Release\Python\DLLs\_testcapi.pyd"
  File "..\bin\Release\Python\DLLs\_symtable.pyd"
  File "..\bin\Release\Python\DLLs\_sre.pyd"
  File "..\bin\Release\Python\DLLs\zlib.pyd"
  SetOutPath "$INSTDIR\Python\Lib"
  File "..\bin\Release\Python\Lib\__future__.py"
  File "..\bin\Release\Python\Lib\xmllib.py"
  File "..\bin\Release\Python\Lib\xdrlib.py"
  File "..\bin\Release\Python\Lib\whrandom.py"
  File "..\bin\Release\Python\Lib\whichdb.py"
  File "..\bin\Release\Python\Lib\webbrowser.py"
  File "..\bin\Release\Python\Lib\weakref.py"
  File "..\bin\Release\Python\Lib\wave.py"
  File "..\bin\Release\Python\Lib\warnings.py"
  File "..\bin\Release\Python\Lib\uu.py"
  File "..\bin\Release\Python\Lib\UserString.py"
  File "..\bin\Release\Python\Lib\UserList.py"
  File "..\bin\Release\Python\Lib\UserDict.pyc"
  File "..\bin\Release\Python\Lib\UserDict.py"
  File "..\bin\Release\Python\Lib\user.py"
  File "..\bin\Release\Python\Lib\urlparse.py"
  File "..\bin\Release\Python\Lib\urllib2.py"
  File "..\bin\Release\Python\Lib\urllib.py"
  File "..\bin\Release\Python\Lib\unittest.py"
  File "..\bin\Release\Python\Lib\tzparse.py"
  File "..\bin\Release\Python\Lib\types.py"
  File "..\bin\Release\Python\Lib\tty.py"
  File "..\bin\Release\Python\Lib\traceback.py"
  File "..\bin\Release\Python\Lib\tokenize.py"
  File "..\bin\Release\Python\Lib\token.py"
  File "..\bin\Release\Python\Lib\toaiff.py"
  File "..\bin\Release\Python\Lib\threading.py"
  File "..\bin\Release\Python\Lib\this.py"
  File "..\bin\Release\Python\Lib\TERMIOS.py"
  File "..\bin\Release\Python\Lib\tempfile.py"
  File "..\bin\Release\Python\Lib\telnetlib.py"
  File "..\bin\Release\Python\Lib\tabnanny.py"
  File "..\bin\Release\Python\Lib\symtable.py"
  File "..\bin\Release\Python\Lib\symbol.py"
  File "..\bin\Release\Python\Lib\sunaudio.py"
  File "..\bin\Release\Python\Lib\sunau.py"
  File "..\bin\Release\Python\Lib\stringold.py"
  File "..\bin\Release\Python\Lib\StringIO.py"
  File "..\bin\Release\Python\Lib\string.pyc"
  File "..\bin\Release\Python\Lib\string.py"
  File "..\bin\Release\Python\Lib\statvfs.py"
  File "..\bin\Release\Python\Lib\statcache.py"
  File "..\bin\Release\Python\Lib\stat.pyc"
  File "..\bin\Release\Python\Lib\stat.py"
  File "..\bin\Release\Python\Lib\sre_parse.py"
  File "..\bin\Release\Python\Lib\sre_constants.py"
  File "..\bin\Release\Python\Lib\sre_compile.py"
  File "..\bin\Release\Python\Lib\sre.py"
  File "..\bin\Release\Python\Lib\SocketServer.py"
  File "..\bin\Release\Python\Lib\socket.py"
  File "..\bin\Release\Python\Lib\sndhdr.py"
  File "..\bin\Release\Python\Lib\smtplib.py"
  File "..\bin\Release\Python\Lib\smtpd.py"
  File "..\bin\Release\Python\Lib\site.pyc"
  File "..\bin\Release\Python\Lib\site.py"
  File "..\bin\Release\Python\Lib\SimpleHTTPServer.py"
  File "..\bin\Release\Python\Lib\shutil.py"
  File "..\bin\Release\Python\Lib\shlex.py"
  File "..\bin\Release\Python\Lib\shelve.py"
  File "..\bin\Release\Python\Lib\sgmllib.py"
  File "..\bin\Release\Python\Lib\sched.py"
  File "..\bin\Release\Python\Lib\robotparser.py"
  File "..\bin\Release\Python\Lib\rlcompleter.py"
  File "..\bin\Release\Python\Lib\rfc822.py"
  File "..\bin\Release\Python\Lib\rexec.py"
  File "..\bin\Release\Python\Lib\repr.py"
  File "..\bin\Release\Python\Lib\regsub.py"
  File "..\bin\Release\Python\Lib\regex_syntax.py"
  File "..\bin\Release\Python\Lib\reconvert.py"
  File "..\bin\Release\Python\Lib\re.py"
  File "..\bin\Release\Python\Lib\random.py"
  File "..\bin\Release\Python\Lib\quopri.py"
  File "..\bin\Release\Python\Lib\Queue.py"
  File "..\bin\Release\Python\Lib\pydoc.py"
  File "..\bin\Release\Python\Lib\pyclbr.py"
  File "..\bin\Release\Python\Lib\py_compile.py"
  File "..\bin\Release\Python\Lib\pty.py"
  File "..\bin\Release\Python\Lib\pstats.py"
  File "..\bin\Release\Python\Lib\profile.py"
  File "..\bin\Release\Python\Lib\pre.py"
  File "..\bin\Release\Python\Lib\pprint.py"
  File "..\bin\Release\Python\Lib\posixpath.py"
  File "..\bin\Release\Python\Lib\posixfile.py"
  File "..\bin\Release\Python\Lib\poplib.py"
  File "..\bin\Release\Python\Lib\popen2.py"
  File "..\bin\Release\Python\Lib\pipes.py"
  File "..\bin\Release\Python\Lib\pickle.py"
  File "..\bin\Release\Python\Lib\pdb.py"
  File "..\bin\Release\Python\Lib\os.pyc"
  File "..\bin\Release\Python\Lib\os.py"
  File "..\bin\Release\Python\Lib\nturl2path.py"
  File "..\bin\Release\Python\Lib\ntpath.pyc"
  File "..\bin\Release\Python\Lib\ntpath.py"
  File "..\bin\Release\Python\Lib\nntplib.py"
  File "..\bin\Release\Python\Lib\netrc.py"
  File "..\bin\Release\Python\Lib\mutex.py"
  File "..\bin\Release\Python\Lib\multifile.py"
  File "..\bin\Release\Python\Lib\mimify.py"
  File "..\bin\Release\Python\Lib\MimeWriter.py"
  File "..\bin\Release\Python\Lib\mimetypes.py"
  File "..\bin\Release\Python\Lib\mimetools.py"
  File "..\bin\Release\Python\Lib\mhlib.py"
  File "..\bin\Release\Python\Lib\mailcap.py"
  File "..\bin\Release\Python\Lib\mailbox.py"
  File "..\bin\Release\Python\Lib\macurl2path.py"
  File "..\bin\Release\Python\Lib\macpath.py"
  File "..\bin\Release\Python\Lib\locale.py"
  File "..\bin\Release\Python\Lib\linecache.py"
  File "..\bin\Release\Python\Lib\knee.py"
  File "..\bin\Release\Python\Lib\keyword.py"
  File "..\bin\Release\Python\Lib\inspect.py"
  File "..\bin\Release\Python\Lib\imputil.py"
  File "..\bin\Release\Python\Lib\imghdr.py"
  File "..\bin\Release\Python\Lib\imaplib.py"
  File "..\bin\Release\Python\Lib\ihooks.py"
  File "..\bin\Release\Python\Lib\httplib.py"
  File "..\bin\Release\Python\Lib\htmllib.py"
  File "..\bin\Release\Python\Lib\htmlentitydefs.py"
  File "..\bin\Release\Python\Lib\gzip.py"
  File "..\bin\Release\Python\Lib\gopherlib.py"
  File "..\bin\Release\Python\Lib\glob.py"
  File "..\bin\Release\Python\Lib\gettext.py"
  File "..\bin\Release\Python\Lib\getpass.py"
  File "..\bin\Release\Python\Lib\getopt.py"
  File "..\bin\Release\Python\Lib\ftplib.py"
  File "..\bin\Release\Python\Lib\fpformat.py"
  File "..\bin\Release\Python\Lib\formatter.py"
  File "..\bin\Release\Python\Lib\fnmatch.py"
  File "..\bin\Release\Python\Lib\fileinput.py"
  File "..\bin\Release\Python\Lib\filecmp.py"
  File "..\bin\Release\Python\Lib\dumbdbm.py"
  File "..\bin\Release\Python\Lib\dospath.py"
  File "..\bin\Release\Python\Lib\doctest.py"
  File "..\bin\Release\Python\Lib\dis.py"
  File "..\bin\Release\Python\Lib\dircache.py"
  File "..\bin\Release\Python\Lib\difflib.py"
  File "..\bin\Release\Python\Lib\dbhash.py"
  File "..\bin\Release\Python\Lib\copy_reg.py"
  File "..\bin\Release\Python\Lib\copy.py"
  File "..\bin\Release\Python\Lib\Cookie.py"
  File "..\bin\Release\Python\Lib\ConfigParser.py"
  File "..\bin\Release\Python\Lib\compileall.py"
  File "..\bin\Release\Python\Lib\commands.py"
  File "..\bin\Release\Python\Lib\colorsys.py"
  File "..\bin\Release\Python\Lib\codeop.py"
  File "..\bin\Release\Python\Lib\codecs.py"
  File "..\bin\Release\Python\Lib\code.py"
  File "..\bin\Release\Python\Lib\cmd.py"
  File "..\bin\Release\Python\Lib\chunk.py"
  File "..\bin\Release\Python\Lib\CGIHTTPServer.py"
  File "..\bin\Release\Python\Lib\cgi.py"
  File "..\bin\Release\Python\Lib\calendar.py"
  File "..\bin\Release\Python\Lib\bisect.py"
  File "..\bin\Release\Python\Lib\binhex.py"
  File "..\bin\Release\Python\Lib\bdb.py"
  File "..\bin\Release\Python\Lib\Bastion.py"
  File "..\bin\Release\Python\Lib\BaseHTTPServer.py"
  File "..\bin\Release\Python\Lib\base64.py"
  File "..\bin\Release\Python\Lib\audiodev.py"
  File "..\bin\Release\Python\Lib\atexit.py"
  File "..\bin\Release\Python\Lib\asyncore.py"
  File "..\bin\Release\Python\Lib\asynchat.py"
  File "..\bin\Release\Python\Lib\anydbm.py"
  File "..\bin\Release\Python\Lib\aifc.py"
  File "..\bin\Release\Python\Lib\zipfile.py"
  SetOutPath "$INSTDIR\Python\Lib\lib-tk"
  File "..\bin\Release\Python\Lib\lib-tk\Canvas.py"
  File "..\bin\Release\Python\Lib\lib-tk\tkSimpleDialog.py"
  File "..\bin\Release\Python\Lib\lib-tk\tkMessageBox.py"
  File "..\bin\Release\Python\Lib\lib-tk\Tkinter.py"
  File "..\bin\Release\Python\Lib\lib-tk\tkFont.py"
  File "..\bin\Release\Python\Lib\lib-tk\tkFileDialog.py"
  File "..\bin\Release\Python\Lib\lib-tk\Tkdnd.py"
  File "..\bin\Release\Python\Lib\lib-tk\Tkconstants.py"
  File "..\bin\Release\Python\Lib\lib-tk\tkCommonDialog.py"
  File "..\bin\Release\Python\Lib\lib-tk\tkColorChooser.py"
  File "..\bin\Release\Python\Lib\lib-tk\Tix.py"
  File "..\bin\Release\Python\Lib\lib-tk\SimpleDialog.py"
  File "..\bin\Release\Python\Lib\lib-tk\ScrolledText.py"
  File "..\bin\Release\Python\Lib\lib-tk\FixTk.py"
  File "..\bin\Release\Python\Lib\lib-tk\FileDialog.py"
  File "..\bin\Release\Python\Lib\lib-tk\Dialog.py"
  File "..\bin\Release\Python\Lib\lib-tk\turtle.py"
SectionEnd

Section HelpFiles
  SetOutPath "$INSTDIR\help"
  File "..\bin\Release\help\*.html"
  File "..\bin\Release\help\visit.helpml"
  SetOutPath "$INSTDIR"
SectionEnd

Section DataFiles
  SetOutPath "$INSTDIR\data"
  #
  # This references Files that are on my local C:\ drive since I don't want to have to
  # make the source distribution have projects to build the test data programs.
  #
  File "..\..\VisItData\*.silo"
  File "..\..\VisItData\wave.visit"
  File "..\..\VisItData\PDB\db*.pdb"
  File "..\..\VisItData\ANALYZE_test_data\*.hdr"
  File "..\..\VisItData\ANALYZE_test_data\*.img"
  File "..\..\VisItData\ANALYZE_test_data\*.visit"
SectionEnd

Section MyImageDirectory
  # This will hopefully create an image storage directory that VisIt can use.
  SetOutPath "$INSTDIR\My images"

  # Set the out path so the system will hopefully give VisIt a working directory
  # that contains the program DLLs.
  SetOutPath "$INSTDIR"
SectionEnd

Section AddVisItRegKeys
#
# This section installs the VISIT<version> key, which tells visit.exe where
# to find the rest of the VisIt components. Note that we put keys in 
# HKEY_LOCAL_MACHINE and in HKEY_CURRENT_USER.
#
  WriteRegStr HKCR "VISIT${PRODUCT_VERSION}" "" ""
  WriteRegStr HKCU "VISIT${PRODUCT_VERSION}" "" ""
  WriteRegStr HKCR "VISIT${PRODUCT_VERSION}" "VISITHOME" "$INSTDIR"
  WriteRegStr HKCU "VISIT${PRODUCT_VERSION}" "VISITHOME" "$INSTDIR"

  # Write the system config that the user chose.
  !insertmacro MUI_INSTALLOPTIONS_READ $0 "NetworkConfig.ini" "Field 1" "State"
  # If $0=="" then we're going to have a networkconfig
  Strcmp $0 "0" HaveNetworkConfig SkipNetworkConfig
HaveNetworkConfig:
    !insertmacro MUI_INSTALLOPTIONS_READ $0 "NetworkConfig.ini" "Field 2" "State"
    # If $0=="" then we're going to use the closed config
    Strcmp $0 "1" OpenNetworkConfig ClosedNetworkConfig
OpenNetworkConfig:
         WriteRegStr HKCR "VISIT${PRODUCT_VERSION}" "VISITSYSTEMCONFIG" "visit-config-open"
         WriteRegStr HKCU "VISIT${PRODUCT_VERSION}" "VISITSYSTEMCONFIG" "visit-config-open"
         Goto SkipNetworkConfig
ClosedNetworkConfig:
         WriteRegStr HKCR "VISIT${PRODUCT_VERSION}" "VISITSYSTEMCONFIG" "visit-config-closed"
         WriteRegStr HKCU "VISIT${PRODUCT_VERSION}" "VISITSYSTEMCONFIG" "visit-config-closed"
SkipNetworkConfig:

  # Write any additional arguments, like the default database format, to the VISITARGS key.
  Strcmp $SelectingDefaultDatabase "yes" HaveDefaultDatabase NoDefaultDatabase
HaveDefaultDatabase:
     WriteRegStr HKCR "VISIT${PRODUCT_VERSION}" "VISITARGS" $DefaultDatabase
     WriteRegStr HKCU "VISIT${PRODUCT_VERSION}" "VISITARGS" $DefaultDatabase
NoDefaultDatabase:

  # If the Python installation path for Python 2.1 does not exist then create it.
#  ReadRegStr $CreatedPythonLinks HKCU "Software\Python\PythonCore\2.1\InstallPath"
#  Strcmp $CreatedPythonLinks "" CreatePythonLinks SkipAddingVisItKeys
#CreatePythonLinks:
  WriteRegStr HKCU "Software\Python\PythonCore\2.1\InstallPath" "" "$INSTDIR"
  WriteRegStr HKCU "Software\Python\PythonCore\2.1\PythonPath"  "" "$INSTDIR\Python\Lib;$INSTDIR\Python\DLLs;$INSTDIR\Python\Lib\lib-tk"
#  WriteRegStr HKCR "VISIT${PRODUCT_VERSION}" "CreatedPythonLinks"  "yes"
#SkipAddingVisItKeys:
SectionEnd

Section AddFileAssociations
  # Associate the Silo file format with VisIt and Silex.
  WriteRegStr HKCR ".silo" "" "siloFile"
  WriteRegStr HKCR "siloFile" "" "Silo File"
  WriteRegStr HKCR "siloFile\DefaultIcon" "" "$INSTDIR\silo.ico"
  WriteRegStr HKCR "siloFile\shell\Explore\command" "" '$INSTDIR\silex.exe "%1"'
  WriteRegStr HKCR "siloFile\shell\open\command" "" '$INSTDIR\visit.exe -o "%1"'

  # Associate the VisIt file format with VisIt.
  WriteRegStr HKCR ".visit" "" "visitFile"
  WriteRegStr HKCR "visitFile" "" "VisIt File"
  WriteRegStr HKCR "visitFile\DefaultIcon" "" "$INSTDIR\visitfile.ico"
  WriteRegStr HKCR "visitFile\shell\open\command" "" '$INSTDIR\visit.exe -o "%1"'

  # Associate the VisIt session file format with VisIt.
  WriteRegStr HKCR ".vses" "" "visitSessionFile"
  WriteRegStr HKCR "visitSessionFile" "" "VisIt Session File"
  WriteRegStr HKCR "visitSessionFile\DefaultIcon" "" "$INSTDIR\visitsessionfile.ico"
  WriteRegStr HKCR "visitSessionFile\shell\Make movie\command"          "" '$INSTDIR\visit.exe -movie -format tiff -sessionfile "%1"'
  WriteRegStr HKCR "visitSessionFile\shell\Make 480x480 movie\command"  "" '$INSTDIR\visit.exe -movie -format tiff -geometry 480x480 -sessionfile "%1"'
  WriteRegStr HKCR "visitSessionFile\shell\Make 640x480 movie\command"  "" '$INSTDIR\visit.exe -movie -format tiff -geometry 640x480 -sessionfile "%1"'
  WriteRegStr HKCR "visitSessionFile\shell\Make 800x600 movie\command"  "" '$INSTDIR\visit.exe -movie -format tiff -geometry 800x600 -sessionfile "%1\'
  WriteRegStr HKCR "visitSessionFile\shell\Make 1024x768 movie\command" "" '$INSTDIR\visit.exe -movie -format tiff -geometry 1024x768 -sessionfile "%1"'
  WriteRegStr HKCR "visitSessionFile\shell\Edit\command" "" 'notepad.exe "%1"'
  WriteRegStr HKCR "visitSessionFile\shell\open\command" "" '$INSTDIR\visit.exe -sessionfile "%1"'
SectionEnd

Section AddJavaInstallPath
   # Call our VIkit DLL to get the $INSTDIR variable formatted as a Java preference.
   VIkit::GetInstallPathFormattedForJava
   Pop $R0
   # Write the reformatted string as a Java preference.
   WriteRegStr HKLM "SOFTWARE\JavaSoft\Prefs\llnl\visit" "/V/I/S/I/T/H/O/M/E" $R0
SectionEnd

Section MigrateConfigFiles
   # Call our VIkit DLL to get see if there are config files to migrate.
   Push ${PRODUCT_VERSION}
   VIkit::GetPathToOlderConfigFiles
   # Install path
   Pop $R1
   # Message box prompt
   Pop $R0

   # If $R1 == "" then no config files
   Strcmp $R1 "" NoMoveConfigs HaveConfigs
HaveConfigs:
   # Ask if the user wants to move the configs
   MessageBox MB_YESNO $R0 IDYES YesMoveConfigs IDNO NoMoveConfigs
YesMoveConfigs:
   # Call our VIkit DLL to migrate the config files.
   Push $R1
   VIKit::MigrateConfigFiles
NoMoveConfigs:
SectionEnd

Section -AdditionalIcons
  WriteIniStr "$INSTDIR\${PRODUCT_NAME}.url" "InternetShortcut" "URL" "${PRODUCT_WEB_SITE}"
  CreateShortCut "$SMPROGRAMS\VisIt ${PRODUCT_VERSION}\VisIt Home Page.lnk" "$INSTDIR\${PRODUCT_NAME}.url"
  CreateShortCut "$SMPROGRAMS\VisIt ${PRODUCT_VERSION}\Uninstall VisIt ${PRODUCT_VERSION}.lnk" "$INSTDIR\uninst.exe"
SectionEnd

Section -Post
  WriteUninstaller "$INSTDIR\uninst.exe"
  WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\visit.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\visit.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
SectionEnd


Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) was successfully removed from your computer."
FunctionEnd

Function un.onInit
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "Are you sure you want to completely remove $(^Name) and all of its components?" IDYES +2
  Abort
FunctionEnd

Section Uninstall
  Delete "$SMPROGRAMS\VisIt ${PRODUCT_VERSION}\Uninstall VisIt ${PRODUCT_VERSION}.lnk"
  Delete "$SMPROGRAMS\VisIt ${PRODUCT_VERSION}\VisIt Home Page.lnk"
  Delete "$SMPROGRAMS\VisIt ${PRODUCT_VERSION}\Silex.lnk"
  Delete "$SMPROGRAMS\VisIt ${PRODUCT_VERSION}\VisIt Command Line Interface.lnk"
  Delete "$DESKTOP\VisIt ${PRODUCT_VERSION}.lnk"
  Delete "$SMPROGRAMS\VisIt ${PRODUCT_VERSION}\VisIt ${PRODUCT_VERSION}.lnk"

  RMDir "$SMPROGRAMS\VisIt ${PRODUCT_VERSION}"

  # Remove all of the VisIt software components
  RMDir /r "$INSTDIR"

  # Delete the Silo file type from the registry.
  DeleteRegKey HKCR ".silo"
  DeleteRegKey HKCR "siloFile"
  # Delete the VisIt session file type from the registry.
  DeleteRegKey HKCR ".vses"
  DeleteRegKey HKCR "visitSessionFile"
  # Delete the VisIt file type from the registry.
  DeleteRegKey HKCR ".visit"
  DeleteRegKey HKCR "visitFile"

  # If we created links for Python, remove them when we remove VisIt.
#  ReadRegStr $CreatedPythonLinks HKCR "VISIT${PRODUCT_VERSION}" "CreatedPythonLinks"
#  Strcmp $CreatedPythonLinks "yes" RemovePythonLinks SkipRemovingPythonLinks
#RemovePythonLinks:
#  DeleteRegKey HKCU "Software\Python\PythonCore\2.1\InstallPath"
#  DeleteRegKey HKCU "Software\Python\PythonCore\2.1\PythonPath"
#SkipRemovingPythonLinks:

  # Delete the VisIt <version> key registry.
  DeleteRegKey HKCR "VISIT${PRODUCT_VERSION}"
  DeleteRegKey HKCU "VISIT${PRODUCT_VERSION}"

  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"

  DeleteRegKey HKLM "SOFTWARE\JavaSoft\Prefs\llnl"

  SetAutoClose true
SectionEnd
