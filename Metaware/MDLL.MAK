# $Header: W:/Projects/OCL/Metaware/rcs/MDLL.MAK 1.50 1996/08/11 23:47:41 B.STEIN Release $

!include $(OCL)\COMMON.INC
!include $(OCL)\OCLOBJ.INC

# when compiling the debug version use these statements
# CFLAGS = $(HIGHCPP_COMPILE_DLL_DEBUG)
# LFLAGS = $(HIGHCPP_LINK_DLL_DEBUG)

CFLAGS = $(HIGHCPP_COMPILE_DLL)
LFLAGS = $(HIGHCPP_LINK_DLL)


MAKEDEP = MDLL.MAK

.all: .\OCLM.DLL .\OIPM.DLL

OCL: .\OCLM.DLL
OIP: .\OIPM.DLL
ALL: OCL OIP

.SUFFIXES:
.SUFFIXES: .cpp .cc


{$(OCL)\Source}.cpp.obj:
  @echo Compiling: $(@B)
  @hc $(CFLAGS) %s

{$(OCL)\Source}.cc.obj:
  @echo Compiling: $(@B)
  @hc $(CFLAGS) %s

.\OCLM.DLL: $(ALLOBJ) OCL_Entry.obj $(MAKEDEP)
  @echo Linking OCLM.DLL ...
  @link386 @<<
     /NOE /NOI /NOLOGO +
     .\OCL_Entry.obj + 
     .\OCL.obj +
     .\OCLObject.obj +
     .\clOString.obj +
     .\O3State.obj +
     .\OAuto3State.obj +
     .\OAutoCheckBox.obj +
     .\OAutoRadioButton.obj +
     .\OApp.obj +
     .\OAppBase.obj +
     .\OBitmap.obj +
     .\OBook.obj +
     .\OBookPage.obj +
     .\OBuffer.obj +
     .\OButton.obj +
     .\OButtonBar.obj +
     .\OCheckBox.obj +
     .\OCircSlider.obj +
     .\OCollection.obj +
     .\OCommand.obj +
     .\OContainerBase.obj +
     .\OCreate.obj +
     .\OCriticalSec.obj +
     .\ODate.obj +
     .\ODialog.obj +
     .\ODragEntryField.obj +
     .\ODynamicLib.obj +
     .\OEditor.obj +
     .\OEntryField.obj +
     .\OException.obj +
     .\OFcl.obj +
     .\OFillButton.obj +
     .\OFrame.obj +
     .\OGraphicsButton.obj +
     .\OHelp.obj +
     .\OHelpPopup.obj +
     .\OIcon.obj +
     .\OIndicator.obj +
     .\OListBox.obj +
     .\OLogo.obj +
     .\OMemu.obj +
     .\OMenu.obj +
     .\OMenuItem.obj +
     .\OMessage.obj +
     .\OMLE.obj +
     .\OMsgs.obj +
     .\OMuxSem.obj +
     .\OMuxWaitSem.obj +
     .\ONPipe.obj +
     .\ONSem.obj +
     .\OOrderedCollection.obj +
     .\OPicture.obj +
     .\OPipe_istream.obj +
     .\OPipe_ostream.obj +
     .\OPipe_streamable.obj +
     .\OPipeCli.obj +
     .\OPipeSvr.obj +
     .\OPipeTool.obj +
     .\OPMException.obj +
     .\OPMinit.obj +
     .\OPMPipeTool.obj +
     .\OProcStat.obj +
     .\OProfile.obj +
     .\OPushButton.obj +
     .\ORadioButton.obj +
     .\ORiffPlay.obj +
     .\OScan.obj +
     .\OSlider.obj +
     .\OSpinBtn.obj +
     .\OStatusLine.obj +
     .\OString.obj +
     .\OSysInfo.obj +
     .\OSysInfoVio.obj +
     .\OSysLevel.obj +
     .\OThreadBase.obj +
     .\OTimer.obj +
     .\OUserButton.obj +
     .\OValueSet.obj +
     .\OVioApp.obj +
     .\OVioException.obj +
     .\OWinDefDlg.obj +
     .\OWinDefWindow.obj +
     .\OWindow.obj +
     .\OXApp.obj +
     .\OXcptBase.obj +
     .\OXcptPM.obj +
     .\OXcptVio.obj +
     .\slOProcRecord.obj +
     .\slOString.obj +
     E:\HCOS2\LIB\STARTUPD.OBJ
     .\OCLM.DLL 
        
     OS2386.LIB +
     HCNA.LIB +
     HCT.LIB +
     HCCT.LIB
     OCLM.DEF
  ;
<<
  @copy OCLM.DLL $(OCL)\LIB\OCLM.DLL
  @del *.obj
  
.\OIPM.DLL: $(OIPOBJ) OIP_Entry.obj $(MAKEDEP)
  @echo Linking OIPM.DLL ...
  @link386 @<<
     /NOE /NOI /NOLOGO +
     .\OIP_Entry.obj + 
     .\OIP.obj +
     .\OIP_Address.obj +
     .\OIP_CliSocket.obj +
     .\OIP_Host.obj +
     .\OIP_SockAddress.obj +
     .\OIP_Socket.obj +
     .\OIP_SrvSocket.obj +
     .\OIP_Server.obj +
     .\OIP_Client.obj +
     E:\HCOS2\LIB\STARTUPD.OBJ
     .\OIPM.DLL 
        
     OS2386.LIB +
     HCNA.LIB +
     HCT.LIB +
     HCCT.LIB +
     OTCPIP.LIB +
     OCLM.LIB
     OIPM.DEF
  ;
<<
  @copy OIPM.DLL $(OCL)\LIB\OIPM.DLL
  @del *.obj

!include $(OCL)\COMMON.DEP
