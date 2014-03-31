// GTakPM
// (c) Benjamin Stein 1994
// All Rights Reserved
// Tape.cpp

//  $Header: W:/Projects/OCL/Samples/GTakPM/Source/rcs/Tape.cpp 1.50 1996/08/11 23:48:13 B.STEIN Release $

#include "..\Source\GTakPM.hpp"



Tape::Tape(pOPMPipeTool currentTool, PSZ tape_description, ULONG tape_blocksize)
  : tool(currentTool),
    bsize(tape_blocksize),
    device(tape_description)
  {}

Tape::~Tape()
  {}


void Tape::prepare()
{
 throw GTPMException(ERROR_NOT_YET_SUPPORTED);

/*
 system("TAPE.EXE ST >NUL 2>&1");
*/
}

void Tape::blocksize(ULONG size)
{
 throw GTPMException(ERROR_NOT_YET_SUPPORTED);

/*

 CHAR    str[10];
 OString command("TAPE.EXE BLOCKSIZE=");

 _itoa(size, str, 10);
 command + str;
 command + " >NUL 2>&1";
 system(command);
*/
}


void Tape::status()
{
 throw GTPMException(ERROR_NOT_YET_SUPPORTED);

/*
 prepare();
 tool->childName  << "TAPE.EXE";
 tool->childParms << "ST";
 tool->detachChild();
*/
}

void Tape::load()
{
 throw GTPMException(ERROR_NOT_YET_SUPPORTED);

/*
 tool->childName  << "TAPE.EXE";
 tool->childParms << "ST LOAD";
 tool->detachChild();
*/
}

void Tape::unload()
{
 throw GTPMException(ERROR_NOT_YET_SUPPORTED);

/*
 tool->childName  << "TAPE.EXE";
 tool->childParms << "ST UNLOAD";
 tool->detachChild();
*/
}

void Tape::rewind()
{
 throw GTPMException(ERROR_NOT_YET_SUPPORTED);

/*
 tool->childName  << "TAPE.EXE";
 tool->childParms << "ST REW";
 tool->detachChild();
*/
}

void Tape::part(OString& command)
{
 throw GTPMException(ERROR_NOT_YET_SUPPORTED);

/*
 tool->childName  << "TAPE.EXE";
 tool->childParms << "ST ";
 tool->childParms + command;
 tool->detachChild();
*/
}

void Tape::format()
{
 throw OPMException("Tape: operation not supported for SCSI-devices", 0);
}

void Tape::erase()
{
 throw GTPMException(ERROR_NOT_YET_SUPPORTED);

/*
 tool->childName  << "TAPE.EXE";
 tool->childParms << "ST ERASE";
 tool->detachChild();
*/
}

void Tape::eraseq()
{
 throw GTPMException(ERROR_NOT_YET_SUPPORTED);

/*
 tool->childName  << "TAPE.EXE";
 tool->childParms << "ST ERASEQ";
 tool->detachChild();
*/
}

void Tape::lock()
{
 throw GTPMException(ERROR_NOT_YET_SUPPORTED);

/*
 tool->childName  << "TAPE.EXE";
 tool->childParms << "ST RESERVE";
 tool->detachChild();
*/
}

void Tape::unlock()
{
 throw GTPMException(ERROR_NOT_YET_SUPPORTED);

/*
 tool->childName  << "TAPE.EXE";
 tool->childParms << "ST RELEASE";
 tool->detachChild();
*/
}

void Tape::batch(PSZ batchfile)
{
 throw GTPMException(ERROR_NOT_YET_SUPPORTED);

/*
 tool->childName  << "CMD.EXE";
 tool->childParms << "/c ";
 tool->childParms  + batchfile;
 tool->detachChild();
*/
}

// end of source
