// GTakPM
// (c) Benjamin Stein 1994
// All Rights Reserved
// Backup.cpp

// $Header: W:/Projects/OCL/Samples/GTakPM/Source/rcs/Backup.cpp 1.50 1996/08/11 23:48:05 B.STEIN Release $

#include "..\Source\GTakPM.hpp"


void GTPMWin::backup()
{
#ifdef __TK21__
 PSZ   tempEnv;
#else
 PCSZ  tempEnv;
#endif 
 PSZ      pstr;
 ULONG    item, items;
 OString  path;
 OString  includes;
 OString  excludes;
 OString  batch;
 OString  dirfile;
 OString  str;
 ofstream incfile;
 ofstream excfile;
 ofstream batchfile;
 
 if ((DosScanEnv("TEMP", &tempEnv)) &&
     (DosScanEnv("TMP", &tempEnv)))
  {
   path << GTPMApp::GTakPM->callName;
   path.rightCut('\\');
  }
 else
   path << (PSZ)tempEnv;

 if (path.getText()[strlen(path) - 1] != '\\')
   path + "\\";

 includes << path;
 includes + "gtmp.inc";
 excludes << path;
 excludes + "gtmp.exc";
 batch << path;
 batch + "gtmp.cmd";
 dirfile << path;
 dirfile + "gtmp.dir";

 path << "Cannot open: ";

 incfile.open(includes);
 if (!incfile) {
   path + includes;
   throw OPMException(path, 0); }

 excfile.open(excludes);
 if (!excfile) {
   path + excludes;
   throw OPMException(path, 0); }

 batchfile.open(batch);
 if (!batchfile) {
   path + batch;
   throw OPMException(path, 0); }

// write includes-file 
 items = Includes->queryItemCount();
 for(item = 0; item < items; item++)
   if (Includes->queryItemText(str, item)) {
     pstr = str.getText();
     while((pstr = strchr(pstr, '\\'))!=NULL)
       pstr[0] = '/';
     incfile << ((PSZ)(strchr(str, ' ')+1)) << endl; }
 incfile.close();

// write excludes-file 
 items = Excludes->queryItemCount();
 for(item = 0; item < items; item++)
   if (Excludes->queryItemText(str, item)) {
     pstr = str.getText();
     while((pstr = strchr(pstr, '\\'))!=NULL)
       pstr[0] = '/';
     excfile << ((PSZ)(strchr(str, ' ')+1)) << endl; }
 excfile.close();

// write batchfile
 batchfile << "@ECHO OFF\n"
           << "echo Initializing Tape\n"
           << "tape stat >NUL 2>NUL\n"
           << "tape blocksize 0 stat sel 0 eraseq tell\n"
           << "echo Backup in progress\ntar -cEppP @"
           << (PSZ) includes
           << " --totals --exclude-from "
           << (PSZ) excludes
           << " -D "
           << (PSZ) dirfile
           << "\ntape stat\n"
           << "echo Compare in progress\n"
           << "tape rew >NUL 2>NUL\n"
           << "tar -dEppP\n"
           << "tape stat\n"
           << "echo Operation completed.\n";
 batchfile.close();
 tape->batch(batch);
}


// end of source
