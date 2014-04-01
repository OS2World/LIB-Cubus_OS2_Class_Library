// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OFuzzSearch.cpp


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

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OFuzzSearch.hpp>
#include <ctype.h>


#if defined(__EMX__)
  template class OList<OFuzzMatch>;
  template class OConstIterator<OFuzzMatch>;
#endif

OFuzzSearch::OFuzzSearch(PCSZ  FileName,
                         PCSZ  SearchString,
                         float Threshold,
                         ULONG MaxParLen)
  : file(FileName),
    parLen(MaxParLen),
    threshold(Threshold),
    searchFor(SearchString)
{} 


OFuzzSearch::~OFuzzSearch()
{}


PSZ OFuzzSearch::isOfType() const
{
 return("OFuzzSearch");
}

void OFuzzSearch::startSearch()
{
 fuzzyMatching();
}


void OFuzzSearch::printMatches()
{
 matches.allElementsDo(printer);
}


void OFuzzSearch::fuzzyMatching()
{
 OString TextPara(parLen);
 OString TextBuffer(parLen);
 INT     TextLen,
         SearchStrLen,
         NGram1Len,
         NGram2Len,
         MatchCount1,
         MatchCount2,
         MaxMatch1,
         MaxMatch2;
 float   Similarity;
 FILE    *InFile;


 TextPara.getText()[0] = ' ';

 if((InFile = fopen(file.getText(),"r")) == NULL)
   throw OVioException(OCL::error(OCL_OFUZZ_OFILE),
                       0, OException::recoverable);

 SearchStrLen = prepareString(searchFor.getText(), searchFor.getText());
 NGram1Len = 3;
 NGram2Len = (SearchStrLen < 7) ? 2 : 5;

 fseek(InFile, 0L, SEEK_SET);
 while (fgets(TextBuffer.getText(), parLen - 1, InFile))
  {
   TextLen = prepareString(&TextPara.getText()[1], TextBuffer.getText());
   if (TextLen < parLen - 2)
     {
      MatchCount1 = NGramMatch(TextPara.getText(), searchFor.getText(),
                               SearchStrLen, NGram1Len, &MaxMatch1);
      MatchCount2 = NGramMatch(TextPara.getText(), searchFor.getText(),
                               SearchStrLen, NGram2Len, &MaxMatch2);

      Similarity = 100.0
                   * (float)(MatchCount1 + MatchCount2)
                   / (float)(MaxMatch1 + MaxMatch2);

      if(Similarity >= threshold)
       {
        OFuzzMatch *matchElement = new OFuzzMatch;
 
        matchElement->text << TextBuffer;
        matchElement->similarity = Similarity; 
        matches << matchElement;
       }
     }
   else
      throw OVioException(OCL::error(OCL_OFUZZ_PARLEN),
                          0, OException::recoverable);
  }
}


LONG OFuzzSearch::prepareString(PSZ  ConvStr,
                                PSZ  OriginStr)
{
 PSZ  TmpPtr;

 for (TmpPtr = ConvStr; *OriginStr; TmpPtr++, OriginStr++)
    {
      *TmpPtr = tolower(*OriginStr);
      if (*OriginStr < '0')
        *TmpPtr = ' ';
      else
        switch((unsigned char)*TmpPtr)
          {
            case 196: *TmpPtr = 228; break; /* ANSI-Umlaute  */
            case 214: *TmpPtr = 246; break;
            case 220: *TmpPtr = 252; break;
            case 142: *TmpPtr = 132; break; /* ASCII-Umlaute */
            case 153: *TmpPtr = 148; break;
            case 154: *TmpPtr = 129; break;
            case ':': *TmpPtr = ' '; break;
            case ';': *TmpPtr = ' '; break;
            case '<': *TmpPtr = ' '; break;
            case '>': *TmpPtr = ' '; break;
            case '=': *TmpPtr = ' '; break;
            case '?': *TmpPtr = ' '; break;
            case '[': *TmpPtr = ' '; break;
            case ']': *TmpPtr = ' '; break;
          }
    }
  *TmpPtr = '\0';
  return (TmpPtr - ConvStr);
}


INT OFuzzSearch::NGramMatch(PSZ  TextPara,
                            PSZ  SearchStr,
                            INT  SearchStrLen,
                            INT  NGramLen,
                            INT* MaxMatch)
{
 CHAR  NGram[8];
 INT   NGramCount;
 INT   i, Count;

 NGram[NGramLen] = '\0';
 NGramCount = SearchStrLen - NGramLen + 1;

 for(i = 0, Count = 0, *MaxMatch = 0; i < NGramCount; i++)
   {
    memcpy(NGram, &SearchStr[i], NGramLen);
      
    if (NGram[NGramLen - 2] == ' ' && NGram[0] != ' ')
      i += NGramLen - 3;
    else
      {
       *MaxMatch  += NGramLen;
       if(strstr(TextPara, NGram)) Count++;
      }
   }

 return Count * NGramLen;
}



void OFuzzSearch::OFuzzMatchPrint::applyToElement(const OFuzzMatch *elem) const
{
 cout << elem->similarity
      << "% in:"
      << endl
      << (PSZ) elem->text.getText()
      << endl
      << endl;
}

// end of source
