/*
Open source not for commercial deployment
*/
//---------------------------------------------------------------------------


#pragma hdrstop

#include "Crypto.h"
#include "SongDataUnit.h"

int prevChar;

String DecryptString(String s)
{
   if (SongData::Password.Length()==0) return "protected.";

   String retval = "";
   for (int i=1; i<=s.Length();i++)
   {
       int t = s[i]&0xFF;
       t-=(prevChar + rand())%224;
       if (t<32) t+=224;
       retval += (char) t;
       prevChar = s[i]&0xFF;
   }
   return retval;
}


void initPseudoRandom()
{
 int t = 0;
 for (int i=1; i<=SongData::Password.Length(); i++)
 {
   t *=3;
   t += SongData::Password.operator [](i);
 }
 srand(t);
};

//---------------------------------------------------------------------------

#pragma package(smart_init)
 