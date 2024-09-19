/*
Open source not for commercial deployment
*/
//---------------------------------------------------------------------------


#pragma hdrstop

#include "SettingsDataUnit.h"

#include "Setup.h"

String SettingsBaseDir;
String BackGroundBaseDir;


SettingsData::SettingsData()
{
    oldMode             = Mode_SONG;
    LineDistance        = 20;
    NrOfLines           = 12;
    OneSongblock        = true;
    secondBlockBig      = false;
    LoadedFile          = "";
    LeftAllign          = true;
    ScreenElement[ALL_TEXT]=&AllText;
    ScreenElement[SONG_TEXT]=&SongText;
    ScreenElement[NORMAL_TEXT]=&NormalText;
    ScreenElement[OLD_COLOR]=&OldText;
    ScreenElement[HEADING2]=&Heading2;
    ScreenElement[HEADING3]=&Heading3;
    ScreenElement[HEADING4]=&Heading4;
    ScreenElement[TRANSLATION]=&Translation;
    ScreenElement[TONE_HEIGTH]=&ToneHeight;
    ScreenElement[TITLE_TEXT]=&SongTitle;
    ScreenElement[BLINK_MESSAGE]=&BlinkMessage;
    ScreenElement[LINE_POINTER]=&LinePointer;
    ScreenElement[CURRENT_SONG]=&CurrentSong;
    ScreenElement[COPY_RIGHT]=&CopyRight;
    ScreenElement[PAUSE_BLINK_MESSAGE]=&PauseBlinkMessage;

    PictureSettings[Mode_SONG]=&BackgroundPicture;
    PictureSettings[Mode_PICTURE]=&ShowPicture;
    PictureSettings[Mode_PAUSE]=&PausePicture;
    PictureSettings[Mode_BLACK]=&BlackPicture;
    curMode = Mode_SONG;
};
//---------------------------------------------------------------------------

bool SettingsData::LoadFile(String fileName)
{
    LoadedFileShort = fileName;
    char buffer[1024];
    if (fileName.Pos(":")==0) fileName =  SettingsBaseDir + fileName;
    if (fileName.UpperCase().Pos(".SET")==0) fileName = fileName + ".set";
    ifstream settingsFile(fileName.c_str());
    if (! settingsFile.is_open())
    {
       return false;
    }
    try
    {
        settingsFile.getline (buffer,1024);
        if (strstr(buffer,"Version 5"))
        {
                SendToSlaves();
                LoadedFile = fileName;
                LoadSettingsFile(&settingsFile);
                SetupScreen->StatusBar->SimpleText = fileName;
                if  (PictureSettings[Mode_SONG]->Active)
                    MainForm->previewImage->LoadPictureFromFile(PictureSettings[Mode_SONG]->FileName);
                else MainForm->previewImage->LoadPictureFromFile("");
        }
        else
        {
            MessageDlg("Wrong settings file can not be used. Redo the settings.", mtInformation, TMsgDlgButtons()<<mbOK , 0);
            return false;
        }
    }
    catch (exception e) { };
    settingsFile.close();
    return true;
};
//---------------------------------------------------------------------------

void SettingsData::LoadSettingsFile(ifstream * settingsFile)
{
    int settingsScreenHeight;
    char buffer[1024];
    OutputScreen->calcMarginTextReduction = true;
    while (!settingsFile->eof())
    {
        settingsFile->getline(buffer,1024);
        String lineBuffer = String(buffer);
        int commaPos = lineBuffer.Pos(",");
        if (commaPos == 0) return;
        int itemIndex = StrToInt(lineBuffer.SubString(0,commaPos-1));
        lineBuffer = lineBuffer.SubString(commaPos+1,lineBuffer.Length());
        commaPos = lineBuffer.Pos(",");
        int itemPart = StrToInt(lineBuffer.SubString(0,commaPos-1));
        lineBuffer = lineBuffer.SubString(commaPos+1,lineBuffer.Length());
        if (itemIndex<50)
        {
                switch (itemPart)
                {
                        case 1: ScreenElement[itemIndex]->Font->Name = lineBuffer; break;
                        case 2: ScreenElement[itemIndex]->Font->Color = (TColor) StrToInt(lineBuffer); break;
                        case 3: ScreenElement[itemIndex]->Xpos = StrToInt(lineBuffer); break;
                        case 4: ScreenElement[itemIndex]->Ypos = StrToInt(lineBuffer); break;
                        case 5: ScreenElement[itemIndex]->Font->Size = StrToInt(lineBuffer);
                                if (ScreenElement[itemIndex]->Font->Size<7)
                                        ScreenElement[itemIndex]->Font->Size = 7;
                                break;
                        case 6: ScreenElement[itemIndex]->Font->Style = TFontStyles();
                                if (lineBuffer=="T") ScreenElement[itemIndex]->Font->Style = TFontStyles(ScreenElement[itemIndex]->Font->Style) << fsBold; break;
                        case 7: if (lineBuffer=="T") ScreenElement[itemIndex]->Font->Style = TFontStyles(ScreenElement[itemIndex]->Font->Style) << fsItalic; break;
                        case 8: if (lineBuffer=="T") ScreenElement[itemIndex]->Font->Style = TFontStyles(ScreenElement[itemIndex]->Font->Style) << fsStrikeOut; break;
                        case 9: if (lineBuffer=="T") ScreenElement[itemIndex]->Font->Style = TFontStyles(ScreenElement[itemIndex]->Font->Style) << fsUnderline; break;
                        case 10: ScreenElement[itemIndex]->Active =  (lineBuffer == "T"); break;
                        case 11: ScreenElement[itemIndex]->OutlineColor = (TColor)  StrToInt(lineBuffer); break;
                        case 12: ScreenElement[itemIndex]->OutlineThickness =  StrToInt(lineBuffer);//*screenResizeRatio/100;
                                        //if (ScreenElement[itemIndex]->OutlineThickness>4) ScreenElement[itemIndex]->OutlineThickness=4; break;
                }
        }
        else if (itemIndex<100)
        {
                switch (itemPart)
                {
                        case 1: PictureSettings[itemIndex-50]->FileName = lineBuffer; break;
                        case 2: PictureSettings[itemIndex-50]->Brightness = MyStrToFloat(lineBuffer); break;
                        case 3: PictureSettings[itemIndex-50]->Contrast = MyStrToFloat(lineBuffer); break;
                        case 4: PictureSettings[itemIndex-50]->BackGroundColor = (TColor) StrToInt(lineBuffer); break;
                        case 5: PictureSettings[itemIndex-50]->Transparent = (lineBuffer == "T"); break;
                        case 6: PictureSettings[itemIndex-50]->Active = (lineBuffer == "T"); break;
                }
        }
        else
        {
                switch (itemPart)
                {
                        case 1: NrOfLines = StrToInt(lineBuffer); break;
                        case 2: LineDistance = StrToInt(lineBuffer); break;
                        case 3: OneSongblock =  (lineBuffer == "T"); break;
                        case 4: //screen size not used anymore
                                break;
                        case 5: LeftAllign = (lineBuffer == "T"); break;
                        case 6: secondBlockBig = (lineBuffer == "T"); break;
                }
        }
    }
}
//---------------------------------------------------------------------------

void SettingsData::SetBaseDir(String pBaseDir, bool pPreview)
{
        preview = pPreview;
        SettingsBaseDir=pBaseDir+"Settings\\";
        BackGroundBaseDir=pBaseDir+"data\\background\\";
        for (int i=0; i<NrOfScreenModes; i++)
                PictureSettings[i]->SetBaseDir(BackGroundBaseDir);
};
//---------------------------------------------------------------------------

bool SettingsData::setBackgroud(String s)
{
     if (s.Length()==0)
     {
       BackgroundPicture.Active = false;
       SendToSlaves();
       return true;
     }
     String temp = expandPicutureFileName(s);

     ifstream songFile (temp.c_str());
     if (! songFile.is_open()) return false;
     songFile.close();

     BackgroundPicture.FileName = s;
     BackgroundPicture.Active = true;
     SendToSlaves();
     return true;
}
//---------------------------------------------------------------------------

void SettingsData::setPause(String s)
{
     if ((curMode == Mode_SONG) || (curMode == Mode_PICTURE)) oldMode = curMode;

     if (s=="On") curMode = Mode_PAUSE;
     else if (s=="Off") curMode = oldMode;
     else if (s=="Toggle")
     {
          if ((curMode == Mode_PAUSE) || (curMode == Mode_BLACK))
             curMode = oldMode;
          else
             curMode = Mode_PAUSE;
     }
    SendToSlaves();
}
//---------------------------------------------------------------------------

void SettingsData::setBlack(String s)
{
     if ((curMode == Mode_SONG) || (curMode == Mode_PICTURE)) oldMode = curMode;

     if (s=="On") curMode = Mode_BLACK;
     else if (s=="Off") curMode = oldMode;
     else if (s=="Toggle")
     {
          if (curMode == Mode_BLACK)   curMode = oldMode;
          else                         curMode = Mode_BLACK;
     }
    SendToSlaves();
}
//---------------------------------------------------------------------------

void SettingsData::setTextBlock(String s)
{
     if (s=="One")           OneSongblock = true;
     else if (s=="Multiple") OneSongblock = false;
     else if (s=="Toggle")   OneSongblock = !OneSongblock;
    SendToSlaves();
}
//---------------------------------------------------------------------------
void SettingsData::setTextBlockSize(String s)
{
     if (s=="One")           secondBlockBig = false;
     else if (s=="Multiple") secondBlockBig = true;
     else if (s=="Toggle")   secondBlockBig = !secondBlockBig;
     SendToSlaves();
}
//---------------------------------------------------------------------------

void SettingsData::changeSetting(String s)
{
     OutputScreen->calcMarginTextReduction = true;
     if (s.Pos("TextBlock_")==1)              setTextBlock(getAfter(s,"_"));
     else if (s.Pos("TextBlockSize_")==1)     setTextBlockSize(getAfter(s,"_"));
     else if (s.Pos("Linedistance_")==1)      setLineDistance(getAfter(s,"_"));
     else if (s.Pos("Linecount_")==1)         setLineCount(getAfter(s,"_"));
     else if (s.Pos("File_")==1)              doFile(getAfter(s,"_"));
     else if (s.Pos("LeftAlign")==1)          LeftAllign = (s=="LeftAlign_On");
     
     else if (s.Pos("BackGroundPicture_")==1) BackgroundPicture.changeSetting(getAfter(s,"_"));
     else if (s.Pos("PausePicture_")==1)      PausePicture.changeSetting(getAfter(s,"_"));
     else if (s.Pos("AllText_")==1)
     {
          s = getAfter(s,"_");
          if (s=="FontType")
          {
             if (MainForm->FontDialog->Execute())
                 for (int i= NORMAL_TEXT; i<NrOfScreenElements; i++)
                     ScreenElement[i]->setFont(MainForm->FontDialog->Font);
          }
          else if (s=="Outline_Color")
          {
             if (MainForm->ColorDialog->Execute())
                 for (int i= NORMAL_TEXT; i<NrOfScreenElements; i++)
                     ScreenElement[i]->setOutlineColor(MainForm->ColorDialog->Color);
          }
          else if (s=="Color")
          {
             if (MainForm->ColorDialog->Execute())
                 for (int i= NORMAL_TEXT; i<NrOfScreenElements; i++)
                     ScreenElement[i]->setColor(MainForm->ColorDialog->Color);
          }
          else
              for (int i= NORMAL_TEXT; i<NrOfScreenElements; i++)
                  ScreenElement[i]->set(s);
     }
     else if (s.Pos("SongText_")==1)
     {
          s = getAfter(s,"_");
          if (s=="FontType")
          {
             if (MainForm->FontDialog->Execute())
                 for (int i= NORMAL_TEXT; i<=LINE_POINTER; i++)
                     ScreenElement[i]->setFont(MainForm->FontDialog->Font);
          }
          else if (s=="Outline_Color")
          {
             if (MainForm->ColorDialog->Execute())
                 for (int i= NORMAL_TEXT; i<=LINE_POINTER; i++)
                     ScreenElement[i]->setOutlineColor(MainForm->ColorDialog->Color);
          }
          else if (s=="Color")
          {
             if (MainForm->ColorDialog->Execute())
                 for (int i= NORMAL_TEXT; i<=LINE_POINTER; i++)
                     ScreenElement[i]->setColor(MainForm->ColorDialog->Color);
          }
          else  if ((s=="Reduce") || (s=="Enlarge") || (s=="Outline_Less") || (s=="Outline_More"))
          {
              for (int i= NORMAL_TEXT; i<=LINE_POINTER; i++)
                  ScreenElement[i]->set(s);
          }
          else  if ((s=="<") || (s==">") || (s=="^") || (s=="v")|| (s=="><"))
          {
              ScreenElement[SONG_TEXT]->set(s);
          }
     }
     else
     {
           int attributtIndex = getAttribuutIndex(getUntil(s,"_"));
           if ( attributtIndex< NrOfScreenElements)
                 ScreenElement[attributtIndex]->set(getAfter(s,"_"));
     }
    SendToSlaves();
}
//---------------------------------------------------------------------------

int SettingsData::getAttribuutIndex(String s)
{
      if (s=="NormalText")        return NORMAL_TEXT;
      if (s=="SongText")          return SONG_TEXT;
      if (s=="OldText")           return OLD_COLOR;
      if (s=="Heading2")          return HEADING2;
      if (s=="Heading3")          return HEADING3;
      if (s=="LinePointer")       return LINE_POINTER;
      if (s=="AllText")           return ALL_TEXT;
      if (s=="Heading4")          return HEADING4;
      if (s=="Translation")       return TRANSLATION;
      if (s=="ToneHeight")        return TONE_HEIGTH;
      if (s=="SongTitle")         return TITLE_TEXT;
      if (s=="BlinkMessage")      return BLINK_MESSAGE;
      if (s=="CurrenSong")        return CURRENT_SONG;
      if (s=="CopyRight")         return COPY_RIGHT;
      if (s=="PauseBlinkMessage") return PAUSE_BLINK_MESSAGE;
                                  return NrOfScreenElements;
}
//---------------------------------------------------------------------------

int SettingsData::getPictureIndex(String s)
{
      if (s=="BackGroundPicture")   return Mode_SONG;
      if (s=="ShowPicture")         return Mode_PICTURE;
      if (s=="PausePicture")        return Mode_PAUSE;
      if (s=="BlackPicture")        return Mode_BLACK;
                                    return NrOfScreenModes;
}
//---------------------------------------------------------------------------

void SettingsData::setLineDistance(String s)
{
     if (s=="Less")      { if (LineDistance>13) LineDistance--; }
     else if (s=="More") { if (LineDistance<72) LineDistance++; }
}
//---------------------------------------------------------------------------

void SettingsData::setLineCount(String s)
{
     if (s=="Less")      { if (NrOfLines>1) NrOfLines--; }
     else if (s=="More") { if (NrOfLines<90) NrOfLines++; }
}
//---------------------------------------------------------------------------

void SettingsData::doFile(String s)
{
     if (LoadedFile.Length()==0) LoadedFile=SettingsBaseDir+"*.set";
     
     if (s=="Open")
     {
        MainForm->FileOpenDialog->Filter="SettingsFile(*.set)|*.set";
        MainForm->FileOpenDialog->DefaultExt=".set";
        MainForm->FileOpenDialog->FileName = LoadedFile;
        if (MainForm->FileOpenDialog->Execute())
        {
           LoadFile(MainForm->FileOpenDialog->FileName);
        }
     }
     else if  (s=="SaveAs")
     {
        MainForm->FileSaveDialog->Filter="SettinsFile(*.set)|*.set";
        MainForm->FileSaveDialog->DefaultExt=".set";
        MainForm->FileSaveDialog->FileName = LoadedFile;
        if (MainForm->FileSaveDialog->Execute())
        {
           storeScreenSettings(MainForm->FileSaveDialog->FileName);
        }
     }
     else if  (s=="Save")
     {
           storeScreenSettings(LoadedFile);
     }
}
//---------------------------------------------------------------------------

void SettingsData::storeScreenSettings(String fileName)
{
    if (fileName.Pos(":")==0)
    {
        fileName = SettingsBaseDir + fileName;
    }
    if (fileName.UpperCase().Pos(".SET")==0)
    {
        fileName = fileName + ".set";
    }
    ofstream settingsFile( (fileName).c_str());
    String s =getSettings();
    settingsFile.write(s.c_str(), s.Length());
    settingsFile.close();
    LoadedFile = fileName;
    SetupScreen->StatusBar->SimpleText = LoadedFile;
}
//---------------------------------------------------------------------------


bool SettingsData::getTransparent(String s)
{
     return PictureSettings[getPictureIndex(s)]->Transparent;
}
//---------------------------------------------------------------------------

bool SettingsData::getPitureActive(String s)
{
     return PictureSettings[getPictureIndex(s)]->Active;
}
//---------------------------------------------------------------------------

bool SettingsData::getTextAttribuutActive(String s)
{
     return ScreenElement[getAttribuutIndex(s)]->Active;
}
//---------------------------------------------------------------------------

String SettingsData::settingToString(int itemIndex, int itemPart, bool value)
{
   String sValue=   value ? "T" : "F";
   return settingToString(itemIndex, itemPart, sValue);
}
//---------------------------------------------------------------------------

String SettingsData::settingToString(int itemIndex, int itemPart, int value)
{        return settingToString(itemIndex, itemPart, IntToStr(value));  }
//---------------------------------------------------------------------------

String SettingsData::settingToString(int itemIndex, int itemPart, double value)
{        return settingToString(itemIndex, itemPart, FloatToStr(value));  }
//---------------------------------------------------------------------------

String SettingsData::settingToString(int itemIndex, int itemPart, String value)
{
    return IntToStr(itemIndex) + "," + IntToStr(itemPart)  + "," + value+ "\n";
}
//---------------------------------------------------------------------------

String SettingsData::getSettings()
{
    String s = "Version 5\n";

    s += settingToString( 100, 4, OutputScreen->Height);

    for (int i=0; i< NrOfScreenElements; i++)
    {
            s += settingToString( i, 1, ScreenElement[i]->Font->Name);
            s += settingToString( i, 2, ScreenElement[i]->Font->Color);
            s += settingToString( i, 3, ScreenElement[i]->Xpos);
            s += settingToString( i, 4, ScreenElement[i]->Ypos);
            s += settingToString( i, 5, ScreenElement[i]->Font->Size);
            s += settingToString( i, 6, ScreenElement[i]->Font->Style.Contains(fsBold));
            s += settingToString( i, 7, ScreenElement[i]->Font->Style.Contains(fsItalic));
            s += settingToString( i, 8, ScreenElement[i]->Font->Style.Contains(fsStrikeOut));
            s += settingToString( i, 9, ScreenElement[i]->Font->Style.Contains(fsUnderline));
            s += settingToString( i, 10, ScreenElement[i]->Active);
            s += settingToString( i, 11, ScreenElement[i]->OutlineColor);
            s += settingToString( i, 12, ScreenElement[i]->OutlineThickness);
    }
    for (int i=0; i< (NrOfScreenModes); i++)
    {
            s += settingToString( i+50, 1, PictureSettings[i]->FileName);
            s += settingToString( i+50, 2, PictureSettings[i]->Brightness);
            s += settingToString( i+50, 3, PictureSettings[i]->Contrast);
            s += settingToString( i+50, 4, PictureSettings[i]->BackGroundColor);
            s += settingToString( i+50, 5, PictureSettings[i]->Transparent);
            s += settingToString( i+50, 6, PictureSettings[i]->Active);
    }
    s += settingToString( 100, 1, NrOfLines);
    s += settingToString( 100, 2, LineDistance);
    s += settingToString( 100, 3, OneSongblock);
    s += settingToString( 100, 5, LeftAllign);
    s += settingToString( 100, 6, secondBlockBig);

    return s;
}
//---------------------------------------------------------------------------

void SettingsData::SendToSlaves()
{
     if (preview) return;

     String s = "<SettingsData>";
     s += "<FileName>" + LoadedFileShort + "</FileName>\n";
     s += "<curMode>" + IntToStr(curMode) + "</curMode>\n";
     s += "<bgPicture>" + PictureSettings[curMode]->FileName + "</bgPicture>\n";
     s += "<bgPictureActive>" + BoolToStr(PictureSettings[curMode]->Active,true) + "</bgPictureActive>\n";
     s += "<Transparent>" + BoolToStr(PictureSettings[curMode]->Transparent,true) + "</Transparent>\n";
     s += "<OneSongblock>" + BoolToStr(OneSongblock,true) + "</OneSongblock>\n";
     s += "<secondBlockBig>" + BoolToStr(secondBlockBig,true) + "</secondBlockBig>\n";
     s += "<LeftAllign>" + BoolToStr(LeftAllign,true) + "</LeftAllign>\n";
     s += "<LinePointer>" + BoolToStr(LinePointer.Active,true) + "</LinePointer>\n";
     s += "<SongTitle>" + BoolToStr(SongTitle.Active,true) + "</SongTitle>\n";
     s += "</SettingsData>";
     MainForm->SendDataToSlaves(s);
}

void SettingsData::ReceiveAsSlave(String s)
{
     if (s.Pos("<FileName>")==1)
     {
          LoadFile( getUntil(getAfter(s,">"),"<"));
          s = getAfter(s,"</FileName>\n");
     }
     if (s.Pos("<curMode>")==1)
     {
        curMode = (Mode) StrToInt(getUntil(getAfter(s,">"),"<"));
        s = getAfter(s,"</curMode>\n");
     }
     if (s.Pos("<bgPicture>")==1)
     {
        PictureSettings[curMode]->FileName = getUntil(getAfter(s,">"),"<");
        s = getAfter(s,"</bgPicture>\n");
     }
     if (s.Pos("<bgPictureActive>")==1)
     {
        PictureSettings[curMode]->Active = StrToBool( getUntil(getAfter(s,">"),"<") );
        s = getAfter(s,"</bgPictureActive>\n");
     }
     if (s.Pos("<Transparent>")==1)
     {
        PictureSettings[curMode]->Transparent = StrToBool( getUntil(getAfter(s,">"),"<") );
        s = getAfter(s,"</Transparent>\n");
     }
     if (s.Pos("<OneSongblock>")==1)
     {
        OneSongblock = StrToBool( getUntil(getAfter(s,">"),"<") );
        s = getAfter(s,"</OneSongblock>\n");
     }
     if (s.Pos("<secondBlockBig>")==1)
     {
        secondBlockBig = StrToBool( getUntil(getAfter(s,">"),"<") );
        s = getAfter(s,"</secondBlockBig>\n");
     }
     if (s.Pos("<LeftAllign>")==1)
     {
        LeftAllign = StrToBool( getUntil(getAfter(s,">"),"<") );
        s = getAfter(s,"</LeftAllign>\n");
     }
     if (s.Pos("<LinePointer>")==1)
     {
        LinePointer.Active = StrToBool( getUntil(getAfter(s,">"),"<") );
        s = getAfter(s,"</LinePointer>\n");
     }
     if (s.Pos("<SongTitle>")==1)
     {
        SongTitle.Active = StrToBool( getUntil(getAfter(s,">"),"<") );
        s = getAfter(s,"</SongTitle>\n");
     }

}



#pragma package(smart_init)




