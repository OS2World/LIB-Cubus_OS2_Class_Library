.* $Header: W:/Projects/OCL/Samples/NextHand/Source/rcs/nexthand.ipf 1.50 1996/08/11 23:48:46 B.STEIN Release $

:userdoc.
:title.NextHand 1.2 Online-Hilfe
:docprof  toc=123456.
:h1 id='PANEL_MAIN' res=10000.NextHand 1.2
:p.NextHand is a NeXT-like Toolbar for OS/2 Presentation Manager. You can can launch
your favourite programs an workplace shell objects from it.
:p.NextHand displays the icon of the selected program files on the button.
Simply drag another icon file or program file to the field "icon" in the
configuration dialog for that button to change the icon.
:p.Right-click on a button for configuration.
:h1 id='PANEL_CFGS' res=20000.NextHand Configuration
:p.This dialog supports drag and drop. Simply drag a program file from
the file system (not a WPS object!) to the dialog. The new button will be
configured automatically.
:p.For DOS- or OS/2 batches the field "program" must be free. Select the program
type and enter
:xmp.
/c my.batch
:exmp.
in the field "parameters". 
:p.:color fc='DarkGreen' bc='default'.Sample&colon.:color fc='Default' bc='Default'.
:p.:color fc='DarkRed' bc='default'.
:xmp.
/c c&colon.\temp\test.cmd
:exmp.
:color fc='Default' bc='Default'.
:p.or 
:p.:color fc='DarkRed' bc='default'.
:xmp.
/c test.bat
:exmp.
:color fc='Default' bc='Default'.
:p.
:p.Simply drag a batch file to the dialog and see what happens.
:p.
:euserdoc.
