# $Header: W:/Projects/OCL/VA30/rcs/VA30.MAK 1.50 1996/08/11 23:49:38 B.STEIN Release $

!include $(OCL)\COMMON.INC
!include $(OCL)\OCLOBJ.INC


# when compiling the debug version use these statements
# CFLAGS = $(ICC_COMPILE_DEBUG)
# CDLLFLAGS = $(ICC_COMPILE_DLL_DEBUG)
# LFLAGS = $(ICC_LINK_DLL_DEBUG)

CFLAGS = $(ICC_COMPILE)
CDLLFLAGS = $(ICC_COMPILE_DLL)
LFLAGS = $(ICC_LINK_DLL)


MAKEDEP = VA30.MAK

.all: .\OCLVA.LIB .\OCLVA.DLL .\OIPVA.LIB .\OIPVA.DLL .\OCLVAI.LIB CLEAN

OCL: .\OCLVA.LIB .\OCLVA.DEF .\OCLVA.DLL .\OCLVAI.LIB CLEAN
OIP: .\OIPVA.LIB .\OIPVA.DEF .\OIPVA.DLL CLEAN
ALL: OCL OIP

.SUFFIXES:
.SUFFIXES: .cpp .cc

{$(OCL)\Source}.cpp.obj:
  @echo Compiling: $(@B)
  @icc $(CFLAGS) %s

{$(OCL)\Source}.cc.obj:
  @echo Compiling: $(@B)
  @icc $(CDLLFLAGS) %s

.\OCLVA.LIB: $(ALLOBJ) $(MAKEDEP)
 @if exist OCLVA.LIB erase OCLVA.LIB
 ilib /nol /noi @<<
.\OCLVA.LIB
y
.\OCL.obj &
.\OCLObject.obj &
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
.\slOString.obj , .\OCLVA.LST;
<<
  @copy OCLVA.LIB $(OCL)\LIB\OCLVA.LIB

.\OCLVA.DEF: .\OCLVA.LIB $(MAKEDEP)
  @echo Generating definition file...
  @echo LIBRARY OCLVA INITINSTANCE TERMINSTANCE > OCLVA.DEF
  @echo DESCRIPTION 'OCL C++ Class Library 1.50 (VACPP30) (c) 1996 by Cubus - All Rights reserved.' >> OCLVA.DEF
  @echo DATA MULTIPLE NONSHARED READWRITE LOADONCALL >> OCLVA.DEF
  @echo CODE LOADONCALL >> OCLVA.DEF
  @echo PROTMODE >> OCLVA.DEF
  @echo IMPORTS >> OCLVA.DEF
  @echo DosQuerySysState = DOSCALLS.368 >> OCLVA.DEF
  @echo EXPORTS >> OCLVA.DEF
  @cppfilt -b -p -q -n -o OCLVA.LIB >> OCLVA.DEF

.\OCLVA.DLL: OCL_Entry.obj $(ALLOBJ) .\OCLVA.DEF $(MAKEDEP)
  @echo Linking ...
  @icc @<<
$(LFLAGS) /Fe.\OCLVA.DLL OCL_Entry.obj $(ALLOBJ) .\OCLVA.DEF
<<
  @copy OCLVA.DLL $(OCL)\LIB\OCLVA.DLL


.\OIPVA.LIB: $(OIPOBJ) $(MAKEDEP)
  @if exist OIPVA.LIB erase OIPVA.LIB
  ilib /nol /noi @<<
.\OIPVA.LIB
y
$(OIPLIBOBJ) , .\OIPVA.LST;
<<
  @copy OIPVA.LIB $(OCL)\LIB\OIPVA.LIB


.\OIPVA.DEF: .\OIPVA.LIB $(MAKEDEP)
  @echo Generating definition file...
  @echo LIBRARY OIPVA INITINSTANCE TERMINSTANCE > OIPVA.DEF
  @echo DESCRIPTION 'OIP C++ Class Library 1.50 (VACPP30) (c) 1996 by Cubus - All Rights reserved.' >> OIPVA.DEF
  @echo DATA MULTIPLE NONSHARED READWRITE LOADONCALL >> OIPVA.DEF
  @echo CODE LOADONCALL >> OIPVA.DEF
  @echo PROTMODE >> OIPVA.DEF
  @echo EXPORTS >> OIPVA.DEF
  @cppfilt -b -p -q -n -o OIPVA.LIB >> OIPVA.DEF


.\OIPVA.DLL: OIP_Entry.obj $(OIPOBJ) .\OIPVA.DEF $(MAKEDEP)
  @echo Linking ...
  @icc @<<
$(LFLAGS) /Fe.\OIPVA.DLL OIP_Entry.obj $(OIPOBJ) OTCPIP.LIB OCLVA.LIB .\OIPVA.DEF
<<
  @copy OIPVA.DLL $(OCL)\LIB\OIPVA.DLL


.\OCLVAI.LIB: .\OCLVA.DEF .\OIPVA.DEF $(MAKEDEP)
  @if exist OCLVAI.LIB erase OCLVAI.LIB
  implib .\OCLVAI.LIB .\OCLVA.DEF .\OIPVA.DEF
  @copy OCLVAI.LIB $(OCL)\LIB\OCLVAI.LIB


CLEAN:
  @if exist OCLVA.LIB erase OCLVA.LIB
  @if exist OCLVA.DLL erase OCLVA.DLL
  @if exist OCLVAI.LIB erase OCLVAI.LIB
  @if exist OIPVA.LIB erase OIPVA.LIB
  @if exist OIPVA.DLL erase OIPVA.DLL

!include $(OCL)\COMMON.DEP
