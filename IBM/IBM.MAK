# $Header: W:/Projects/OCL/IBM/rcs/IBM.MAK 1.50 1996/08/11 23:47:12 B.STEIN Release $

!include $(OCL)\COMMON.INC
!include $(OCL)\OCLOBJ.INC


# when compiling the debug version use these statements
# CFLAGS = $(ICC_COMPILE_DEBUG)
# CDLLFLAGS = $(ICC_COMPILE_DLL_DEBUG)
# LFLAGS = $(ICC_LINK_DLL_DEBUG)

CFLAGS = $(ICC_COMPILE)
CDLLFLAGS = $(ICC_COMPILE_DLL)
LFLAGS = $(ICC_LINK_DLL)


MAKEDEP = IBM.MAK

.all: .\OCLI.LIB .\OCLI.DLL .\OIPI.LIB .\OIPI.DLL .\OCLII.LIB CLEAN

OCL: .\OCLI.LIB .\OCLI.DLL .\OCLII.LIB CLEAN
OIP: .\OIPI.LIB .\OIPI.DLL CLEAN
ALL: OCL OIP

.SUFFIXES:
.SUFFIXES: .cpp .cc

{$(OCL)\Source}.cpp.obj:
  @echo Compiling: $(@B)
  @icc $(CFLAGS) %s

{$(OCL)\Source}.cc.obj:
  @echo Compiling: $(@B)
  @icc $(CDLLFLAGS) %s

.\OCLI.LIB: $(ALLOBJ) $(MAKEDEP)
 @if exist OCLI.LIB erase OCLI.LIB
 lib /nol /noi /p:1024 @<<
.\OCLI.LIB
y
.\clOString.obj &
.\O3State.obj & 
.\OApp.obj &
.\OAppBase.obj &
.\OAuto3State.obj &
.\OAutoCheckBox &
.\OAutoRadioButton &
.\OBitmap.obj &
.\OBuffer.obj &
.\OButton.obj &
.\OButtonBar.obj &
.\OBook.obj &
.\OBookPage.obj &
.\OCheckBox.obj &
.\OCircSlider.obj &
.\OCollection.obj &
.\OCommand.obj &
.\OContainerBase.obj &
.\OCreate.obj &
.\OCriticalSec.obj &
.\ODate.obj &
.\ODialog.obj &
.\ODragEntryField.obj &
.\ODynamicLib.obj &
.\OEditor.obj &
.\OEntryField.obj &
.\OException.obj &
.\OFcl.obj &
.\OFillButton.obj &
.\OFrame.obj &
.\OGraphicsButton.obj &
.\OHelp.obj &
.\OHelpPopup.obj &
.\OIcon.obj &
.\OIndicator.obj &
.\OListBox.obj &
.\OLogo.obj &
.\OMemu.obj &
.\OMenu.obj &
.\OMenuItem.obj &
.\OMessage.obj &
.\OMLE.obj &
.\OMsgs.obj &
.\OMuxSem.obj &
.\OMuxWaitSem.obj &
.\ONPipe.obj &
.\ONSem.obj &
.\OOrderedCollection.obj &
.\OPicture.obj &
.\OPipe_istream.obj &
.\OPipe_ostream.obj &
.\OPipe_streamable.obj &
.\OPipeCli.obj &
.\OPipeSvr.obj &
.\OPipeTool.obj &
.\OPMException.obj &
.\OPMinit.obj &
.\OPMPipeTool.obj &
.\OProcStat.obj &
.\OProfile.obj &
.\OPushButton.obj &
.\ORadioButton.obj &
.\ORiffPlay.obj &
.\OScan.obj &
.\OSlider.obj &
.\OSpinBtn.obj &
.\OStatusLine.obj &
.\OString.obj &
.\OSysInfo.obj &
.\OSysInfoVio.obj &
.\OSysLevel.obj &
.\OThreadBase.obj &
.\OTimer.obj &
.\OUserButton.obj &
.\OValueSet.obj &
.\OVioApp.obj &
.\OVioException.obj &
.\OWinDefDlg.obj &
.\OWinDefWindow.obj &
.\OWindow.obj &
.\OXApp.obj &
.\OXcptBase.obj &
.\OXcptPM.obj &
.\OXcptVio.obj &
.\slOProcRecord.obj &
.\slOString.obj &
.\OCL.obj , .\OCLI.LST;
<<
  @copy OCLI.LIB $(OCL)\LIB\OCLI.LIB


.\OCLI.DLL: OCL_Entry.obj $(ALLOBJ) $(MAKEDEP)
  @echo Generating definition file...
  @echo LIBRARY OCLI INITINSTANCE TERMINSTANCE > OCLI.DEF
  @echo DESCRIPTION 'OCL C++ Class Library 1.50 (ICPP21) (c) 1996 by Cubus - All Rights reserved.' >> OCLI.DEF
  @echo DATA MULTIPLE NONSHARED READWRITE LOADONCALL >> OCLI.DEF
  @echo CODE LOADONCALL >> OCLI.DEF
  @echo PROTMODE >> OCLI.DEF
  @echo IMPORTS >> OCLI.DEF
  @echo DosQuerySysState = DOSCALLS.368 >> OCLI.DEF
  @echo EXPORTS >> OCLI.DEF
  @cppfilt -b -p -q -n -o OCLI.LIB >> OCLI.DEF
  @echo Linking ...
  @icc @<<
$(LFLAGS) /Fe.\OCLI.DLL OCL_Entry.obj $(ALLOBJ) .\OCLI.DEF
<<
  @copy OCLI.DLL $(OCL)\LIB\OCLI.DLL


.\OIPI.LIB: $(OIPOBJ) $(MAKEDEP)
  @if exist OIPI.LIB erase OIPI.LIB
  lib /nol /noi /p:1024 @<<
.\OIPI.LIB
y
$(OIPLIBOBJ) , .\OIPI.LST;
<<
  @copy OIPI.LIB $(OCL)\LIB\OIPI.LIB

.\OIPI.DLL: \
  OIP_Entry.obj \
  $(OIPOBJ) \
  $(MAKEDEP)
  @echo Generating definition file...
  @echo LIBRARY OIPI INITINSTANCE TERMINSTANCE > OIPI.DEF
  @echo DESCRIPTION 'OIP C++ Class Library 1.50 (ICPP21) (c) 1996 by Cubus - All Rights reserved.' >> OIPI.DEF
  @echo DATA MULTIPLE NONSHARED READWRITE LOADONCALL >> OIPI.DEF
  @echo CODE LOADONCALL >> OIPI.DEF
  @echo PROTMODE >> OIPI.DEF
  @echo EXPORTS >> OIPI.DEF
  @cppfilt -b -p -q -n -o OIPI.LIB >> OIPI.DEF
  @echo Linking ...
  @icc @<<
$(LFLAGS) /Fe.\OIPI.DLL OIP_Entry.obj $(OIPOBJ) OCLI.LIB OTCPIP.LIB .\OIPI.DEF
<<
  @copy OIPI.DLL $(OCL)\LIB\OIPI.DLL

.\OCLII.LIB: .\OCLI.DLL .\OIPI.DLL $(MAKEDEP)
  @if exist OCLII.LIB erase OCLII.LIB
  implib .\OCLII.LIB .\OCLI.DEF .\OIPI.DEF
  @copy OCLII.LIB $(OCL)\LIB\OCLII.LIB

CLEAN:
  @if exist OCLI.LIB erase OCLI.LIB
  @if exist OCLI.DLL erase OCLI.DLL
  @if exist OCLII.LIB erase OCLII.LIB
  @if exist OIPI.LIB erase OIPI.LIB
  @if exist OIPI.DLL erase OIPI.DLL

!include $(OCL)\COMMON.DEP
