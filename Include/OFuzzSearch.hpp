// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OFuzzSearch.hpp


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


// $Header:$

#ifndef OFUZZSRC_INCLUDED
  #define OFUZZSRC_INCLUDED


#ifndef OCLOBJECT_INCLUDED
  #include <OCLObject.hpp>
#endif

#ifndef OSTRING_INCLUDED
  #include <OString.hpp>
#endif

#ifndef OLIST_INCLUDED
  #include <OList.hpp>
#endif



// classes


typedef class  OFuzzSearch *pOFuzzSearch;
typedef struct OFuzzMatch  *pOFuzzMatch;
typedef class  OList<OFuzzMatch> OFuzzMatchList;

struct OFuzzMatch
{
 OString  text;
 float    similarity;
};


class __CPP_EXPORT__ OFuzzSearch
  : public OCLObject
{
 private:
   OString         file;    // text file to search
   ULONG           parLen;  // max paragraph length to search
   float           threshold;
   OString         searchFor;

   class __CPP_EXPORT__ OFuzzMatchPrint
     : public OConstIterator<OFuzzMatch>
     {
      public:
        void applyToElement(const OFuzzMatch* elem) const;
     };

   OFuzzMatchPrint  printer;


 protected:
   
   void
      fuzzyMatching ();

   LONG
      prepareString (PSZ  ConvStr,
                     PSZ  OriginStr);

   INT
      NGramMatch    (PSZ  TextPara,
                     PSZ  SearchStr,
                     INT  SearchStrLen,
                     INT  NGramLen,
                     INT* MaxMatch);


 public:
   OFuzzMatchList   matches;


   OFuzzSearch      (PCSZ  FileName,
                     PCSZ  SearchString,
                     float Threshold = 100.0, // exact match
                     ULONG MaxParLen = 0x0000ffffL); 

   virtual
     ~OFuzzSearch   ();

  virtual
     PSZ isOfType   () const;

   void
      startSearch   ();

   void
      printMatches  ();
};


#endif // OFUZZSRC_INCLUDED


// end of source
