/*
Open source not for commercial deployment
*/
//---------------------------------------------------------------------------


#pragma hdrstop

#include "KeyHandling.h"

String KeyfileBaseDir;

KeyHandling::KeyHandling()
{
    shiftDown = false;
    controlDown = false;
    altDown = false;
    inputData = "";
    showKey = true;
}


String KeyHandling::ProcessKeyDown(WORD &Key, TShiftState Shift)
{
    String tmp = "";
    if (Shift.Contains(ssAlt))   { altDown     = true; tmp = "1"+tmp; } else { altDown     = false; tmp = "0"+tmp; }
    if (Shift.Contains(ssShift)) { shiftDown   = true; tmp = "1"+tmp; } else { shiftDown   = false; tmp = "0"+tmp; }
    if (Shift.Contains(ssCtrl))  { controlDown = true; tmp = "1"+tmp; } else { controlDown = false; tmp = "0"+tmp; }

    Log("Key pressed: " + tmp + "," + Key);
    return ProcessKeyDown(Key);
}

String KeyHandling::ProcessKeyDown(WORD Key)
{
    int KeyNumber = Key&0xFF;
    if (altDown) KeyNumber+=256;
    if (shiftDown) KeyNumber+=512;
    if (controlDown) KeyNumber+=1024;
    return KeyCommand[KeyNumber];
}

void KeyHandling::ProcessKeyUp(WORD &Key, TShiftState Shift)
{
    shiftDown = Shift.Contains(ssShift);
    controlDown = Shift.Contains(ssCtrl);
    altDown =  Shift.Contains(ssAlt);
}

void KeyHandling::LoadKeySettingsFile(String fileName)
{
     if (fileName.Pos(":")==0)
        fileName = KeyfileBaseDir + fileName;
   ifstream keyFile (fileName.c_str());
    if (! keyFile.is_open())
    {
       MessageDlg("Could not load the key file: "+ fileName, mtInformation, TMsgDlgButtons()<<mbOK , 0);
       return;
    }
    char buffer[1024];
    while (!keyFile.eof())
    {
        keyFile.getline(buffer,1024);
        String temp = buffer;
        if ( (temp.Length()>7) && (temp[4]==',') && (temp[8]==',') )
        {
                int C = StrToInt(temp.SubString(1,1));
                int S = StrToInt(temp.SubString(2,1));
                int A = StrToInt(temp.SubString(3,1));
                int KeyNr = StrToInt(temp.SubString(5,3));
                if ((KeyNr>255) || (C>1) || (S>1) || (A>1))
                {
                       MessageDlg("Error in keyfile key value to high max: (111,255) :"+temp, mtInformation, TMsgDlgButtons()<<mbOK , 0);
                }
                KeyCommand[(A*256)+(S*512)+(C*1024) + KeyNr]=temp.SubString(9,temp.Length()-8);
        }
    }
    keyFile.close();
}

void KeyHandling::setBaseDir( String BaseDir)
{
            KeyfileBaseDir = BaseDir + "Settings\\";
}

//---------------------------------------------------------------------------

#pragma package(smart_init)
