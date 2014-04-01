# $Header: W:/Projects/OCL/Metaware/rcs/MLIB.MAK 1.50 1996/08/11 23:47:41 B.STEIN Release $

!include $(OCL)\COMMON.INC
!include $(OCL)\OCLOBJ.INC

# when compiling the debug version use these statements
# CFLAGS = $(HIGHCPP_COMPILE_DEBUG)

CFLAGS = $(HIGHCPP_COMPILE)

MAKEDEP = MLIB.MAK

.all: .\OCLM.LIB .\OCLM.DEF .\OCLMI.LIB .\OIPM.LIB .\OIPM.DEF

OCL: .\OCLM.LIB .\OCLM.DEF .\OCLMI.LIB
OIP: .\OIPM.LIB .\OIPM.DEF
ALL: OCL OIP

{$(OCL)\Source}.cpp.obj:
  @echo Compiling: $(@B)
  @hc $(CFLAGS) %s

.\OCLM.LIB: $(ALLOBJ) $(MAKEDEP)
 @if exist OCLM.LIB erase OCLM.LIB
 lib /nol /noi /p:1024 @<<
.\OCLM.LIB
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
.\OStdDialog.obj &
.\OFontDialog.obj &
.\OFileDialog.obj &
.\OColorDialog.obj &
.\ODragEntryField.obj &
.\ODynamicLib.obj &
.\OEditor.obj &
.\OEntryField.obj &
.\OException.obj &
.\OFcl.obj &
.\OFillButton.obj &
.\OFrame.obj &
.\OFuzzSearch.obj &
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
.\slOString.obj , .\OCLM.LST;
<<
  @copy OCLM.LIB $(OCL)\LIB\OCLM.LIB
  @del *.obj

#  lib @<<
# .\OCLM.LIB -create -add -replace -norepadd -pagesize 2048 @..\ALLOBJ.INC
# <<
#  @copy OCLM.LIB $(OCL)\LIB\OCLM.LIB

.\OCLM.DEF: .\OCLM.LIB
  @echo LIBRARY OCLM INITINSTANCE TERMINSTANCE >OCLM.DEF
  @echo DESCRIPTION 'OCL C++ Class Library 1.50 (HIGHCPP331) (c) 1996 by Cubus - All Rights reserved.' >>OCLM.DEF
  @echo DATA MULTIPLE NONSHARED LOADONCALL >>OCLM.DEF
  @echo IMPORTS >>OCLM.DEF
  @echo    DosQProcStatus   = DOSCALL1.154 >>OCLM.DEF
  @echo    DosQuerySysState = DOSCALLS.368 >>OCLM.DEF 
  @echo EXPORTS >>OCLM.DEF
  @pubdef -p -x -c -u -o OCLM.LIB >>OCLM.DEF


.\OIPM.LIB: $(OIPOBJ) $(MAKEDEP)
 @if exist OIPM.LIB erase OIPM.LIB
 lib /nol /noi /p:1024 @<<
.\OIPM.LIB
y
$(OIPLIBOBJ) , .\OIPM.LST;
<<
  @copy OIPM.LIB $(OCL)\LIB\OIPM.LIB
  @del *.obj

#  lib @<<
# .\OIPM.LIB -create -add -replace -norepadd -pagesize 2048 $(OIPLIBOBJ)
# <<
#  @copy OIPM.LIB $(OCL)\LIB\OIPM.LIB


.\OIPM.DEF: .\OIPM.LIB
  @echo LIBRARY OIPM INITINSTANCE TERMINSTANCE >OIPM.DEF
  @echo DESCRIPTION 'OIP C++ Class Library 1.50 (HIGHCPP331) (c) 1996 by Cubus - All Rights reserved.' >>OIPM.DEF
  @echo DATA MULTIPLE NONSHARED LOADONCALL >>OIPM.DEF
  @echo EXPORTS >>OIPM.DEF
  @pubdef -p -x -c -u -o OIPM.LIB >>OIPM.DEF


.\OCLMI.LIB: .\OCLM.DEF .\OIPM.DEF $(MAKEDEP)
  @implib .\OCLMI.LIB .\OCLM.DEF .\OIPM.DEF
  @copy OCLMI.LIB $(OCL)\LIB\OCLMI.LIB


!include $(OCL)\COMMON.DEP
