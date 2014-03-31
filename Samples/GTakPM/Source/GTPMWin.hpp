// GTakPM
// (c) Benjamin Stein 1994
// All Rights Reserved
// GTPMWin.hpp

// $Header: W:/Projects/OCL/Samples/GTakPM/Source/rcs/GTPMWin.hpp 1.50 1996/08/11 23:48:08 B.STEIN Release $

#ifndef GTPMWIN_HPP_INCLUDED
  #define GTPMWIN_HPP_INCLUDED

#ifndef GTAKPM_HPP_INCLUDED
  #include "..\Source\GTakPM.hpp"
#endif

struct DirItem
{
 OString fullName;
 OString name;
};

typedef DirItem FileItem ;
typedef FileItem *pFileItem;

struct DirInfo
{
 RECORDCORE rc;          // base information
 pDirItem   dirItem;
 BOOL       selected;    // directory is selected
 BOOL       expanded;    // expanded subdirectory?
 BOOL       wasExpanded;
};


class DrivesCnr : public OContainer<DirInfo, RECORDCORE>
{
 protected:
   pGTPMWin ParentWindow;

   lOString           DriveList;
   OList<DirItem>     DirList;

 public:
   OThread<DrivesCnr> populate;
   OThread<DrivesCnr> select;

   OIcon              hd_ico;
   OIcon              hdS_ico;
   OIcon              cd_ico;
   OIcon              cdS_ico;
   OIcon              folder_ico;
   OIcon              folderS_ico;
   OIcon              openfolder_ico;
   OIcon              openfolderS_ico;
   OIcon              dontKnow_ico;

     DrivesCnr       (pGTPMWin Parent);

   virtual
     ~DrivesCnr      ();

   virtual  
      PSZ isOfType   () const 
      { return("DrivesCnr"); }

   BOOL
      setupDetails   (),
      setupItems     ();

   void
      collectDirectories (),

      getDirectories     (pDirInfo Parent,
                          PSZ Directory,
                          BOOL recursive = TRUE,
                          BOOL selected = FALSE),

      insertDirs         (pDirInfo Parent,
                          PSZ Directory,
                          PFILEFINDBUF3 pffb,
                          ULONG cFiles,
                          BOOL selected = FALSE),

      recurse            (pDirInfo Parent,
                          BOOL recursive = TRUE,
                          BOOL selected = FALSE),

      selectDirRecord    (pDirInfo Parent),

      beginSelect        ();
};


struct FileInfo
{
 MINIRECORDCORE rc;       // base information
 pFileItem      fileItem;     
 CDATE          date;     // date of file
 CTIME          time;     // time of file
 ULONG          cbFile;   // file size
 BOOL           selected; // file is selected
};


class FilesCnr : public OContainer<FileInfo, MINIRECORDCORE>
{
 protected:
   pGTPMWin          ParentWindow;
   OList<FileItem>   FileList;

 public:
   OThread<FilesCnr> populate; 
   OString           scanDirectory;
   OIcon             file_ico;
   OIcon             fileS_ico;

      FilesCnr       (pGTPMWin Parent);

   virtual
      ~FilesCnr      ();

   virtual  
      PSZ isOfType      () const 
      { return("FilesCnr"); }

   BOOL
      setupDetails   (),
      setupItems     ();

   void
      getFiles       (), 
      insertFiles    (PFILEFINDBUF3 pffb,
                      ULONG cFiles);
};




class GTPMWin 
  : public OFrame 
{
 protected:
   BOOL             wasOutOfContainer;
   BOOL             processing;
   BOOL             showMonitor;
   HWND             frameMenu;
   OThread<GTPMWin> expander;
   OThread<GTPMWin> backupThr;
   OThread<GTPMWin> restoreThr;

   OBitmap          bmp_monitor;
   OBitmap          bmp_rescan;
   OBitmap          bmp_procedures;
   OBitmap          bmp_tape;
   OBitmap          bmp_backup;
   OBitmap          bmp_restore;
   OBitmap          bmp_compare;
   OBitmap          bmp_settings;
   OBitmap          bmp_quit;
   OBitmap          bmp_load;
   OBitmap          bmp_unload;
   OBitmap          bmp_rewind;
   OBitmap          bmp_erase;
   OBitmap          bmp_eraseq;
   OBitmap          bmp_lock;
   OBitmap          bmp_unlock;
   OBitmap          bmp_stop_asap;

   OGraphicsButton  btn_monitor;
   OGraphicsButton  btn_rescan;
   OGraphicsButton  btn_procedures;
   OGraphicsButton  btn_tape;
   OGraphicsButton  btn_backup;
   OGraphicsButton  btn_restore;
   OGraphicsButton  btn_compare;
   OGraphicsButton  btn_settings;
   OGraphicsButton  btn_quit;
   OGraphicsButton  btn_load;
   OGraphicsButton  btn_unload;
   OGraphicsButton  btn_rewind;
   OGraphicsButton  btn_erase;
   OGraphicsButton  btn_eraseq;
   OGraphicsButton  btn_lock;
   OGraphicsButton  btn_unlock;
   OGraphicsButton  btn_stop_asap;

 public:
   pTape         tape;

   pOStatusLine  statline;
   pOButtonBar   toolbar;
   pOButtonBar   tapebar;
   pDrivesCnr    Drives;
   pFilesCnr     Files;
   pOListBox     Includes;
   pOListBox     Excludes;
   pOListBox     monitor;

   OPMPipeTool   pmpipe;


     GTPMWin        ();

   virtual
     ~GTPMWin       ();

   virtual
     PSZ isOfType() const
     { return("GTPMWin"); }

   void
     expandFolder   (),
     backup         (),
     restore        (),
     addExclude     (PSZ str),
     addInclude     (PSZ str),
     updateListbox  (PSZ str),
     printout       (),
     resizeClients  (MPARAM sizeparms);  // processes WM_SIZE

   BOOL
     control        (MPARAM mp1, MPARAM mp2),  // process WM_CONTROL
     command        (MPARAM mp1, MPARAM mp2),  // process WM_COMMAND
     OCommand       (ULONG msg, MPARAM mp1, MPARAM mp2); 
};

#endif // GTPMWIN_HPP_INCLUDED

// end of source
