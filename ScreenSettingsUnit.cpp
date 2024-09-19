/*
Open source not for commercial deployment
*/
//---------------------------------------------------------------------------


#pragma hdrstop

#include "ScreenSettingsUnit.h"

ScreenSettings::ScreenSettings()
{
        CurLine=0;
        CurLinePointer=0;
        startLine=0;
};

bool ScreenSettings::LoadSong(String filename)
{
        if (CurSongData.LoadSong(filename)==false) return false;

        int lineNumber = 0;
        String s = getAfter(filename,"_");
        if (s.Pos("LineNr_")==1)  lineNumber=StrToInt(getAfter(s,"_"));

        CurLine=lineNumber;
        startLine=lineNumber;
        SendToSlaves();
        return true;
}

void ScreenSettings::toNextTextBlock()
{
    if (startLine>= CurSongData.getSongLength()) return;

    if (CurLine>startLine)
    {
       startLine = CurLine+1;
       CurLine = startLine;
       SendToSlaves();
       return;
    }

    int tmp = startLine;
    startLine++;
    while ((startLine<CurSongData.getSongLength()) &&
           (CurSongData.text[startLine].Length()>0) &&
           (startLine < (tmp + CurSettings.NrOfLines -2))) //check for long couplet
        startLine++;

    startLine++;
    if (CurSongData.text[startLine].Length()==0) startLine++;
    if (startLine>CurSongData.getSongLength())
       startLine = CurSongData.getSongLength();

    CurLine = startLine;
    SendToSlaves();
}

void ScreenSettings::toPrevTextBlock()
{
    if (startLine==0)return;

    startLine--;
    startLine--;
    while ((startLine>0) &&
           (CurSongData.text[startLine].Length()>1))
           startLine--;
    if (startLine>0) startLine++;
    if (startLine<0) startLine=0;
    CurLine = startLine;
    SendToSlaves();
}



void ScreenSettings::setOutdateline(String s) //up down arrow
{
     if (s=="Less")
     {
        if (CurLine > startLine) CurLine--;
     }
     else  if (s=="More")
     {
        if (CurLine < (startLine + CurSettings.NrOfLines)) CurLine++;
     }
     SendToSlaves();
}

void ScreenSettings::ToBeginSong()
{
     startLine = 0;
     CurLine = 0;
     SendToSlaves();
}
void ScreenSettings::ToEndSong()
{
     startLine = CurSongData.getSongLength();
     toPrevTextBlock();
     SendToSlaves();
}

void ScreenSettings::scrollOneLine(String s)
{
    if (s=="Down")
    {
       if (startLine>= CurSongData.getSongLength()) return;
       startLine++;
    }
    else
    {
      if (startLine==0)return;
      startLine--;
    }
    CurLine = startLine;
    SendToSlaves();
}


void ScreenSettings::SendToSlaves()
{
     if (CurSongData.shortFileNameAndVers.Length()>0)
         LogThisDay(replace(CurSongData.shortFileNameAndVers,","," ") + "," +
                    replace(CurSongData.text[ CurLine ]     ,","," "));

     String s = "<ScreenSettings>";
     s += "<curLine>" + IntToStr(CurLine) + "</curLine>\n";
     s += "<startLine>" + IntToStr(startLine) + "</startLine>\n";

     s += "</ScreenSettings>";
     MainForm->SendDataToSlaves(s);
}

//---------------------------------------------------------------------------
void ScreenSettings::ReceiveAsSlave(String s)
{
     if (s.Pos("<curLine>")==1) CurLine = StrToInt( getUntil(getAfter(s,">"),"<") );
     s = getAfter(s,"</curLine>\n");
     if (s.Pos("<startLine>")==1) startLine = StrToInt( getUntil(getAfter(s,">"),"<") );
     s = getAfter(s,"</startLine>\n");
}


void ScreenSettings::gotoStrofe(String s)
{
//todo find the strofe to be done
     int i = CurSongData.FindCoupletLinenr(s, false);
     startLine = i;
     CurLine = i;
}

void ScreenSettings::SetText(const String s)
{
    CurSongData.SetText(s);
    CurLine=0;
    CurLinePointer=0;
    startLine=0;
}

#pragma package(smart_init)
