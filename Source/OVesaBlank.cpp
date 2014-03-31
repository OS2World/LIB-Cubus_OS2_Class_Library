// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// (c) 1994 B. Stein
// OVesaBlank.cpp

/*
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Neither the name Cubus nor the name Team OCL may be used to
 *    endorse or promote products derived from this software
 *    without specific prior written permission.
 * 3. See OCL.INF for a detailed copyright notice.
 *
 *              THIS SOFTWARE IS PROVIDED ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */


// $Header: W:/Projects/OCL/Source/rcs/OVesaBlank.cpp 1.50 1996/08/11 23:49:34 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>

#include <OVesaBlank.h>
#include <OVesaBlank.hpp>

OVesaBlank::mode OVesaBlank::currentState = OVesaBlank::on;
vga              OVesaBlank::vga_registers;


OVesaBlank::OVesaBlank()
  : blankSem(NULL)
{
 try  // this is not the first instance of this class in the system
   {
    blankSem = new OMuxSem("\\SEM32\\OVBlank.SEM", OMuxSem::open, FALSE);
   }
 catch(OVioException &ex)
   {
    blankSem = new OMuxSem("\\SEM32\\OVBlank.SEM", OMuxSem::create, FALSE);
   }

 if (OVesaBlank::currentState != OVesaBlank::on)
   unblank(); 
} 


OVesaBlank::~OVesaBlank()
{
 unblank();
 delete blankSem;
}


PSZ OVesaBlank::isOfType() const
{
 return("OVesaBlank");
} 


OVesaBlank& OVesaBlank::blank(OVesaBlank::mode _mode)
{
 if (!blankSem->requestMuxSem(OMuxSem::immediate))
   return(*this);

 if ((OVesaBlank::currentState == OVesaBlank::off) ||
     (_mode                    == OVesaBlank::on))
   return(*this);

 _portaccess(FIRST_PORT, LAST_PORT);

 vga_registers.SeqCtrlIndex = inb_p(seq_port_reg);
 vga_registers.CrtCtrlIndex = inb_p(video_port_reg);
 vga_registers.CrtMiscIO    = inb_p(video_misc_rd);

 if(_mode == OVesaBlank::off)
   { 
    outb_p(0x00,video_port_reg);      // HorizontalTotal
    vga_registers.HorizontalTotal   = inb_p(video_port_val);
    outb_p(0x01,video_port_reg);      // HorizDisplayEnd
    vga_registers.HorizDisplayEnd   = inb_p(video_port_val);
    outb_p(0x04,video_port_reg);      // StartHorizRetrace 
    vga_registers.StartHorizRetrace = inb_p(video_port_val);
    outb_p(0x05,video_port_reg);      // EndHorizRetrace
    vga_registers.EndHorizRetrace   = inb_p(video_port_val);
   }

 outb_p(0x07,video_port_reg);         // Overflow
 vga_registers.Overflow             = inb_p(video_port_val);
 outb_p(0x10,video_port_reg);         // StartVertRetrace
 vga_registers.StartVertRetrace     = inb_p(video_port_val);
 outb_p(0x11,video_port_reg);         // EndVertRetrace
 vga_registers.EndVertRetrace       = inb_p(video_port_val);
 outb_p(0x17,video_port_reg);         // ModeControl
 vga_registers.ModeControl          = inb_p(video_port_val);
 outb_p(0x01,seq_port_reg);           // ClockingMode
 vga_registers.ClockingMode         = inb_p(seq_port_val);
	
 // assure that video is enabled
 // "0x20" is VIDEO_ENABLE_bit in register 01 of sequencer

 outb_p(0x01,seq_port_reg);
 outb_p(vga_registers.ClockingMode | 0x20,seq_port_val);

 // test for vertical retrace in process....

 if ((vga_registers.CrtMiscIO & 0x80) == 0x80)
   outb_p(vga_registers.CrtMiscIO & 0xef,video_misc_wr);

 // Set <End of vertical retrace> to minimum (0) and
 // <Start of vertical Retrace> to maximum (incl. overflow)
 // Result: turn off vertical sync (VSync) pulse.

 outb_p(0x10,video_port_reg);         // StartVertRetrace 
 outb_p(0xff,video_port_val);         // maximum value 
 outb_p(0x11,video_port_reg);         // EndVertRetrace 
 outb_p(0x40,video_port_val);         // minimum (bits 0..3)  
 outb_p(0x07,video_port_reg);         // Overflow 
 outb_p(vga_registers.Overflow | 0x84,video_port_val);
                                      // bits 9,10 of 

 // vert. retrace
      
 if (_mode == OVesaBlank::off)
  {
   // Set <End of horizontal retrace> to minimum (0) and
   // <Start of horizontal Retrace> to maximum
   // Result: turn off horizontal sync (HSync) pulse.

   outb_p(0x04,video_port_reg);       // StartHorizRetrace 
   outb_p(0xff,video_port_val);       // maximum 
   outb_p(0x05,video_port_reg);       // EndHorizRetrace 
   outb_p(0x00,video_port_val);       // minimum (0) 
  }

 // restore both index registers

 outb_p(vga_registers.SeqCtrlIndex,seq_port_reg);
 outb_p(vga_registers.CrtCtrlIndex,video_port_reg);

 OVesaBlank::currentState = _mode;

 blankSem->releaseMuxSem();
 return(*this);
}



OVesaBlank& OVesaBlank::unblank()
{
 if (!blankSem->requestMuxSem(OMuxSem::immediate))
   return(*this);

 if (OVesaBlank::currentState == OVesaBlank::on)
   return(*this);

 _portaccess(FIRST_PORT, LAST_PORT);

 outb_p(vga_registers.CrtMiscIO,video_misc_wr);

 if (OVesaBlank::currentState == OVesaBlank::off)
   { 
    outb_p(0x00,video_port_reg);      // HorizontalTotal
    outb_p(vga_registers.HorizontalTotal,video_port_val);
    outb_p(0x01,video_port_reg);      // HorizDisplayEnd 
    outb_p(vga_registers.HorizDisplayEnd,video_port_val);
    outb_p(0x04,video_port_reg);      // StartHorizRetrace 
    outb_p(vga_registers.StartHorizRetrace,video_port_val);
    outb_p(0x05,video_port_reg);      // EndHorizRetrace 
    outb_p(vga_registers.EndHorizRetrace,video_port_val);
   }

 outb_p(0x07,video_port_reg);         // Overflow 
 outb_p(vga_registers.Overflow,video_port_val);
 outb_p(0x10,video_port_reg);         // StartVertRetrace 
 outb_p(vga_registers.StartVertRetrace,video_port_val);
 outb_p(0x11,video_port_reg);         // EndVertRetrace
 outb_p(vga_registers.EndVertRetrace,video_port_val);
 outb_p(0x17,video_port_reg);         // ModeControl
 outb_p(vga_registers.ModeControl,video_port_val);
 outb_p(0x01,seq_port_reg);           // ClockingMode
 outb_p(vga_registers.ClockingMode,seq_port_val);
	

 // restore index/control registers

 outb_p(vga_registers.SeqCtrlIndex,seq_port_reg);
 outb_p(vga_registers.CrtCtrlIndex,video_port_reg);

 OVesaBlank::currentState = OVesaBlank::on;
  
 blankSem->releaseMuxSem();
 return(*this);
}


OVesaBlank& OVesaBlank::sleep()
{
 return(blank(OVesaBlank::suspend));
}       

OVesaBlank& OVesaBlank::standby()
{
 return(blank(OVesaBlank::off));
}


// end of source

