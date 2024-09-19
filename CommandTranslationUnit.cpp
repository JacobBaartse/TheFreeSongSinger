/*
Open source not for commercial deployment
*/
//---------------------------------------------------------------------------


#pragma hdrstop

#include "CommandTranslationUnit.h"

//---------------------------------------------------------------------------


void CommandTranslation::AddTranslation(String s)
{
     //replace translation
     for (int i=0; i<MAX_TRANSLATION_COMMANDS; i++)
     {
        if (Command[i] == getUntil(s,"|"))
        {
           Translation[i] = getAfter(s,"|");
           return;
        }
     }

     //add translation
     if (count == MAX_TRANSLATION_COMMANDS)
     {
        MessageDlg("Maximum number of translation commands reached.", mtInformation, TMsgDlgButtons()<<mbOK , 0);
        return;
     }
     Command[count] = getUntil(s,"|");
     Translation[count] = getAfter(s,"|");
     count++;
}

CommandTranslation::CommandTranslation()
{
    count  = 0;
}

String CommandTranslation::translate(String s)
{
    // new translation will be added so do not perform old translation   
    if (getUntil(s,"_")==("AddTranslation"))
       return s;

    for (int i= 0; i<count; i++)
    {
        int pos = s.Pos(Command[i]);
        if (pos>0)
        {
            String retval = s.SubString(0,pos-1) +
                            Translation[i] +
                            s.SubString(pos + Command[i].Length(), s.Length() - pos + Command[i].Length());
            retval = replace(retval, "|", ",");
            return retval;
        }
    }
    return s;
}

#pragma package(smart_init)
