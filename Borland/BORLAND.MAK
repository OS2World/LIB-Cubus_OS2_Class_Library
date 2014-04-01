# $Header: E:/Projects/OCL/Borland/rcs/BORLAND.MAK 1.19 1996/01/25 03:46:31 B.STEIN Exp B.STEIN $

!include $(OCL)\COMMON.INC
!include $(OCL)\OCLOBJ.INC

# when compiling the debug version use these statements
# CFLAGS = $(BORLAND_COMPILE_DLL_DEBUG)
# LFLAGS = $(BORLAND_LINK_DLL_DEBUG)

CFLAGS = $(BORLAND_COMPILE_DLL)
LFLAGS = $(BORLAND_LINK_DLL)

MAKEDEP = BORLAND.MAK

.all: .\OCLB.LIB .\OCLB.DLL .\OCLBI.LIB .\OIPB.LIB .\OIPB.DLL CLEAN

OCL: .\OCLB.LIB .\OCLB.DLL .\OCLBI.LIB CLEAN
OIP: .\OIPB.LIB .\OIPB.DLL CLEAN
ALL: OCL OIP


.SUFFIXES:
.SUFFIXES: .cpp .cc


{$(OCL)\Source}.cpp.obj:
  @echo Compiling: $(@B)
  @bcc $(CFLAGS) %s

{$(OCL)\Source}.cc.obj:
  @echo Compiling: $(@B)
  @bcc -P $(CFLAGS) %s

.\OCLB.LIB: $(ALLOBJ) $(MAKEDEP)
  tlib @<<
.\OCLB.LIB /E /C &
+.\OCL.obj &
+.\OCLObject.obj &
+.\clOString.obj &
+.\O3State.obj & 
+.\OApp.obj &
+.\OAppBase.obj &
+.\OAuto3State.obj &
+.\OAutoCheckBox &
+.\OAutoRadioButton &
+.\OBitmap.obj &
+.\OBuffer.obj &
+.\OButton.obj &
+.\OButtonBar.obj &
+.\OBook.obj &
+.\OBookPage.obj &
+.\OCheckBox.obj &
+.\OCircSlider.obj &
+.\OCollection.obj &
+.\OCommand.obj &
+.\OContainerBase.obj &
+.\OCreate.obj &
+.\OCriticalSec.obj &
+.\ODate.obj &
+.\OStdDialog.obj &
+.\OFileDialog.obj &
+.\OFontDialog.obj &
+.\OColorDialog.obj &
+.\ODragEntryField.obj &
+.\ODynamicLib.obj &
+.\OEditor.obj &
+.\OEntryField.obj &
+.\OException.obj &
+.\OFcl.obj &
+.\OFillButton.obj &
+.\OFrame.obj &
+.\OFuzzSearch.obj &
+.\OGraphicsButton.obj &
+.\OHelp.obj &
+.\OHelpPopup.obj &
+.\OIcon.obj &
+.\OIndicator.obj &
+.\OListBox.obj &
+.\OLogo.obj &
+.\OMemu.obj &
+.\OMenu.obj &
+.\OMenuItem.obj &
+.\OMLE.obj &
+.\OMessage.obj &
+.\OMsgs.obj &
+.\OMuxSem.obj &
+.\OMuxWaitSem.obj &
+.\ONPipe.obj &
+.\ONSem.obj &
+.\OOrderedCollection.obj &
+.\OPicture.obj &
+.\OPipe_istream.obj &
+.\OPipe_ostream.obj &
+.\OPipe_streamable.obj &
+.\OPipeCli.obj &
+.\OPipeSvr.obj &
+.\OPipeTool.obj &
+.\OPMException.obj &
+.\OPMinit.obj &
+.\OPMPipeTool.obj &
+.\OProcStat.obj &
+.\OProfile.obj &
+.\OPushButton.obj &
+.\ORadioButton.obj &
+.\ORiffPlay.obj &
+.\OScan.obj &
+.\OSlider.obj &
+.\OSpinBtn.obj &
+.\OStatusLine.obj &
+.\OString.obj &
+.\OSysInfo.obj &
+.\OSysInfoVio.obj &
+.\OSysLevel.obj &
+.\OThreadBase.obj &
+.\OTimer.obj &
+.\OUserButton.obj &
+.\OValueSet.obj &
+.\OVioApp.obj &
+.\OVioException.obj &
+.\OWinDefDlg.obj &
+.\OWinDefWindow.obj &
+.\OWindow.obj &
+.\OXApp.obj &
+.\OXcptBase.obj &
+.\OXcptPM.obj &
+.\OXcptVio.obj &
+.\slOProcRecord.obj &
+.\slOString.obj ,
.\OCLB.LST;
<<
  @copy OCLB.LIB $(OCL)\LIB\OCLB.LIB
 
.\OCLB.DLL: $(ALLOBJ) OCL_Entry.obj $(MAKEDEP)
  @echo Linking OCLB.DLL ...
  @tlink @<< 
$(LFLAGS) OCL_Entry.obj $(ALLOBJ) , OCLB.DLL ,, C2MT OS2, OCLB.DEF
<<
  @copy OCLB.DLL $(OCL)\LIB\OCLB.DLL

.\OCLBI.LIB: .\OCLB.DLL $(MAKEDEP)
  @implib -c .\OCLBI.LIB .\OCLB.DEF .\OIPB.DEF
  @copy OCLBI.LIB $(OCL)\LIB\OCLBI.LIB


.\OIPB.LIB: $(OIPOBJ) $(MAKEDEP)
  tlib @<<
.\OIPB.LIB /E /C &
+.\OIP.obj &
+.\OIP_Address.obj &
+.\OIP_CliSocket.obj &
+.\OIP_Host.obj &
+.\OIP_SockAddress.obj &
+.\OIP_Socket.obj &
+.\OIP_SrvSocket.obj &
+.\OIP_Server.obj &
+.\OIP_Client.obj
.\OIPB.LST;
<<
  @copy OIPB.LIB $(OCL)\LIB\OIPB.LIB

.\OIPB.DLL: $(OIPOBJ) OIP_Entry.obj $(MAKEDEP)
  @echo Linking OIPB.DLL ...
  @tlink @<< 
$(LFLAGS) OIP_Entry.obj $(OIPOBJ) , OIPB.DLL ,, OTCPIP OCLB C2MT OS2, OIPB.DEF
<<
  @copy OIPB.DLL $(OCL)\LIB\OIPB.DLL

CLEAN:
  @if exist OCLB.LIB erase OCLB.LIB
  @if exist OCLB.DLL erase OCLB.DLL
  @if exist OCLBI.LIB erase OCLBI.LIB
  @if exist OIPB.LIB erase OIPB.LIB
  @if exist OIPB.DLL erase OIPB.DLL


!include $(OCL)\COMMON.DEP
