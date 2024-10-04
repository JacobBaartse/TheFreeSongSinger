/*
Open source not for commercial deployment
*/
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "OutputScreenUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TOutputScreen *OutputScreen;
//---------------------------------------------------------------------------

__fastcall TOutputScreen::TOutputScreen(TComponent* Owner)
        : TForm(Owner)
{

}
//---------------------------------------------------------------------------

void __fastcall TOutputScreen::FormCreate(TObject *Sender)
{
        DoubleBuffered = true;
        temporyHideLinePointer = false;
        JPEGImage = new TJPEGImage;
        BMPImage = new Graphics::TBitmap();

        BrightnessAdjust= 0;
        ContrastAdjust=1;
        BlinkMessage="";
        LateRefesch=false;
        textReduction=100;
        blinkcounter = 101;
        calcMarginTextReduction = true;
}
//---------------------------------------------------------------------------

void TOutputScreen::FreezeSize()
{
        OutputScreen->BorderStyle = bsNone;
}
//---------------------------------------------------------------------------

void __fastcall TOutputScreen::Timer1Timer(TObject *Sender)
{
        if (OutputScreen->BorderStyle != bsNone) return; // not started yet.

        //let the blink message blink 5 times.
        if (blinkcounter<101)
        {
           if ( (blinkcounter % 20) == 0 )
           {
              curScreenSettings.CurSettings.ScreenElement[SettingsData::BLINK_MESSAGE]->Active=true;
              curScreenSettings.CurSettings.ScreenElement[SettingsData::PAUSE_BLINK_MESSAGE]->Active=true;
              LateRefesch = true;
           }
           if ( (blinkcounter++ % 20) == 10 )
           {
              curScreenSettings.CurSettings.ScreenElement[SettingsData::BLINK_MESSAGE]->Active=false;
              curScreenSettings.CurSettings.ScreenElement[SettingsData::PAUSE_BLINK_MESSAGE]->Active=false;
              LateRefesch = true;
           }
        }

        if (!LateRefesch) return; //nothing new
        LateRefesch=false;
        MainForm->SendDataToSlaves("<LateRefesch/>");

        PictureAttribuut newPictureAttrib = *curScreenSettings.CurSettings.PictureSettings[curScreenSettings.CurSettings.curMode];

        if (newPictureAttrib.FileName.Length()>0)
        {
                newPictureAttrib.Brightness += BrightnessAdjust;
                newPictureAttrib.Contrast *= ContrastAdjust;
        }

        if (curPictureAttrib!=newPictureAttrib)
        {
                curPictureAttrib = newPictureAttrib;
                LoadPiture();
        }

        refreshScreen();

        ouptuScreenUpdated = true;
        if (Image1->Visible==true)
        {
                Image2->Visible=true;
                Image1->Visible=false;
        }
        else
        {
                Image1->Visible=true;
                Image2->Visible=false;
        }

}
//---------------------------------------------------------------------------

void TOutputScreen::ResizePictureAndLoad()
{
        //calculate the resize factor to let the piture fill the screen.
        double WidthOriginal = BMPImage->Width;
        double HeightOriginal = BMPImage->Height;
        double WidthMax = OutputScreen->Width;
        double HeightMax = OutputScreen->Height;
        double fraction;
        double ymargin=0;
        double xmargin=0;
        bool smallEdges=false;
        if ( WidthOriginal/HeightOriginal > WidthMax/HeightMax)
        {
                fraction =  WidthOriginal /  WidthMax;
                ymargin =  (HeightMax - HeightOriginal/fraction  )/2;
                if (ymargin <  HeightMax/30) smallEdges=true;
        }
        else
        {
                fraction =  HeightOriginal / HeightMax;
                xmargin = ( WidthMax - WidthOriginal/fraction) /2;
                if (xmargin <  WidthMax/30) smallEdges=true;
        }

        TRect maxPictureSize;
        if (smallEdges)
                maxPictureSize = TRect(0,0,WidthMax, HeightMax );  // full screen
        else
                maxPictureSize = TRect(xmargin,ymargin,xmargin+WidthOriginal/fraction, ymargin+HeightOriginal/fraction );

        // convert and resize to fill the screen, position the bmp on the Image object.
        notActiveImage->Canvas->StretchDraw(maxPictureSize, BMPImage);
}
//---------------------------------------------------------------------------

void TOutputScreen::LoadPiture()
{
              if (curPictureAttrib.FileName.Length()==0) return;
              String fileName = expandPicutureFileName(curPictureAttrib.FileName);

              // first check if the picture file exist.
              ifstream pictureFile(fileName.c_str());
              if (!pictureFile.is_open()) return;
              pictureFile.close();

              bool BmpFile = fileName.UpperCase().Pos(".BMP")+3 == fileName.Length();

              if (BmpFile)
              {
                        // bmp file can just be loaded.
                        BMPImage->LoadFromFile(fileName);
              }
              else
              {
                        //convert the JPG file to a BMP
                        JPEGImage->LoadFromFile(fileName);
                        BMPImage->Assign ( JPEGImage );
              }

              //change brightness and contrast.
              {
                      Byte * bTemp = new Byte[256];
                      __int32 inverseContrast = (__int32)(0x0100/curPictureAttrib.Contrast);  //contrast value 1/200 ... 200
                      __int32 temp;
                      // calculate new contrast for every brightness value (create a conversion table)
                      for (int i=0; i<256; i++)
                      {
                                temp = (i<<8)/inverseContrast + curPictureAttrib.Brightness;
                                if (temp>255) temp = 255;
                                if (temp<0) temp = 0;
                                bTemp[i] =  (Byte)temp;
                      }

                      Byte * ptr;
                      __int32 x, y, imageWidth;
                      imageWidth =  BMPImage->Width *3;
                      for (y=0; y< BMPImage->Height ; y++)
                      {
                                  ptr = (Byte *)BMPImage->ScanLine[y];
                                  for (x=0; x<imageWidth; x++)
                                  {
                                       ptr[x] = bTemp[ptr[x]];
                                  }
                      }
                      delete bTemp;
              }
}
//---------------------------------------------------------------------------

int TOutputScreen::CalculateLineYPosition(int ScreenLine)
{
    return (int) ((ScreenLine) * curScreenSettings.CurSettings.LineDistance +
            curScreenSettings.CurSettings.ScreenElement[SettingsData::NORMAL_TEXT]->Font->Size)+
            curScreenSettings.CurSettings.ScreenElement[SettingsData::SONG_TEXT]->Ypos +
            Height/15;
}
//---------------------------------------------------------------------------

TPoint TOutputScreen::printLine(int songLine, int screenLine, bool showOldColor ,bool suppresOutline)
{
    int yPos = CalculateLineYPosition(screenLine);
    TPoint CurTextPos(leftMargin, yPos);

    if (curScreenSettings.CurSongData.getSongLength() == 0) return CurTextPos;

    return printLineXY(curScreenSettings.CurSongData.text[songLine], leftMargin, yPos, showOldColor ,suppresOutline, SettingsData::NORMAL_TEXT, false, true);
}
//---------------------------------------------------------------------------

TPoint TOutputScreen::printLineXY(String PrintText, int x, int yPos, bool showOldColor ,bool suppresOutline, int TextType, bool wrap, bool doTextReduction)
{
   if (!suppresOutline)
          printLineXYOutlineOrText(PrintText, x, yPos, showOldColor ,false, TextType, wrap, doTextReduction);

   return printLineXYOutlineOrText(PrintText, x, yPos, showOldColor , true, TextType, wrap, doTextReduction);
}
//---------------------------------------------------------------------------

TPoint TOutputScreen::printLineXYOutlineOrText(String PrintText, int x, int yPos, bool showOldColor ,bool suppresOutline, int TextType, bool wrap, bool doTextReduction)
{
    TextAttribuut *textAttribuut = curScreenSettings.CurSettings.ScreenElement[TextType];
    TextAttribuut *SpecialAttribuut;
    int  currentOutlineThickness = textAttribuut->OutlineThickness;
    int finalTextReduction;

    if (doTextReduction) finalTextReduction = textReduction;
    else finalTextReduction = 100;

    if (finalTextReduction<10)
        finalTextReduction=10;

    TColor currentOutlineColor = textAttribuut->OutlineColor;
    const int NrOfTags=12;
    String Tags[NrOfTags];
    Tags[0]="<H2>";
    Tags[1]="</H2>";
    Tags[2]="<b>";
    Tags[3]="</b>";
    Tags[4]="<H3>";
    Tags[5]="</H3>";
    Tags[6]="<H4>";
    Tags[7]="</H4>";
    Tags[8]="<i>";
    Tags[9]="</i>";
    Tags[10]="<translation>";
    Tags[11]="</translation>";

    int TagHit[NrOfTags];
    for (int i=0; i<NrOfTags; i++) TagHit[i]=0;
    notActiveImage->Canvas->Font = textAttribuut->Font;

    notActiveImage->Canvas->Font->Size = textAttribuut->Font->Size * finalTextReduction / 100;

    TPoint CurTextPos(x, yPos);

    bool inTag=false;


    for (int i=1; i<=PrintText.Length(); i++)
    {
        for (int j=0; j<NrOfTags; j++)
            if (PrintText[i] == Tags[j][TagHit[j]+1])
        {
            TagHit[j]++;
            if (TagHit[j] == Tags[j].Length())
            {
                //perform the tags.
                TagHit[j]=0;
                switch (j)
                {
                    case 1:// end H2
                    case 5:// end H3
                    case 7:// end H4
                    case 11:// end translation
                        notActiveImage->Canvas->Font = textAttribuut->Font;
                        notActiveImage->Canvas->Font->Size = textAttribuut->Font->Size  * finalTextReduction / 100;;
                        CurTextPos.y = yPos;
                        currentOutlineThickness = textAttribuut->OutlineThickness;
                        currentOutlineColor = textAttribuut->OutlineColor;
                        break;
                    case 2:// bold
                        notActiveImage->Canvas->Font->Style = TFontStyles(notActiveImage->Canvas->Font->Style) << fsBold;
                        break;
                    case 3:// end bold
                        notActiveImage->Canvas->Font->Style = TFontStyles(notActiveImage->Canvas->Font->Style) >> fsBold;
                        break;
                    case 0:// H2
                        SpecialAttribuut = curScreenSettings.CurSettings.ScreenElement[SettingsData::HEADING2];
                        notActiveImage->Canvas->Font = SpecialAttribuut->Font;
                        notActiveImage->Canvas->Font->Size = SpecialAttribuut->Font->Size * finalTextReduction / 100;
                        CurTextPos.y = yPos + SpecialAttribuut->Ypos * finalTextReduction/100;
                        CurTextPos.x = CurTextPos.x + SpecialAttribuut->Xpos*finalTextReduction/100;
                        currentOutlineThickness = SpecialAttribuut->OutlineThickness;
                        currentOutlineColor = SpecialAttribuut->OutlineColor;
                        break;
                    case 4:// H3
                        SpecialAttribuut = curScreenSettings.CurSettings.ScreenElement[SettingsData::HEADING3];
                        notActiveImage->Canvas->Font = SpecialAttribuut->Font;
                        notActiveImage->Canvas->Font->Size = SpecialAttribuut->Font->Size * finalTextReduction / 100;
                        CurTextPos.y = yPos + SpecialAttribuut->Ypos*finalTextReduction/100;
                        CurTextPos.x = CurTextPos.x + SpecialAttribuut->Xpos*finalTextReduction/100;
                        currentOutlineThickness = SpecialAttribuut->OutlineThickness;
                        currentOutlineColor = SpecialAttribuut->OutlineColor;
                        break;
                    case 6:// H4
                        SpecialAttribuut = curScreenSettings.CurSettings.ScreenElement[SettingsData::HEADING4];
                        notActiveImage->Canvas->Font = SpecialAttribuut->Font;
                        notActiveImage->Canvas->Font->Size = SpecialAttribuut->Font->Size * finalTextReduction / 100;
                        CurTextPos.y = yPos + SpecialAttribuut->Ypos*finalTextReduction/100;
                        CurTextPos.x = CurTextPos.x + SpecialAttribuut->Xpos*finalTextReduction/100;
                        currentOutlineThickness = SpecialAttribuut->OutlineThickness;
                        currentOutlineColor = SpecialAttribuut->OutlineColor;
                        break;
                    case 8:// italic
                        notActiveImage->Canvas->Font->Style = TFontStyles(notActiveImage->Canvas->Font->Style) << fsItalic;
                        break;
                    case 9:// end italic
                        notActiveImage->Canvas->Font->Style = TFontStyles(notActiveImage->Canvas->Font->Style) >> fsItalic;
                        break;
                    case 10:// translation
                        SpecialAttribuut = curScreenSettings.CurSettings.ScreenElement[SettingsData::TRANSLATION];
                        notActiveImage->Canvas->Font = SpecialAttribuut->Font;
                        notActiveImage->Canvas->Font->Size = SpecialAttribuut->Font->Size * finalTextReduction / 100;
                        CurTextPos.y = yPos + SpecialAttribuut->Ypos*finalTextReduction/100;
                        CurTextPos.x = CurTextPos.x + SpecialAttribuut->Xpos*finalTextReduction/100;
                        currentOutlineThickness = SpecialAttribuut->OutlineThickness;
                        currentOutlineColor = SpecialAttribuut->OutlineColor;
                        break;
                    default:
                        SpecialAttribuut = curScreenSettings.CurSettings.ScreenElement[TextType];
                        notActiveImage->Canvas->Font = SpecialAttribuut->Font;
                        notActiveImage->Canvas->Font->Size = SpecialAttribuut->Font->Size * finalTextReduction / 100;
                        CurTextPos.y = yPos + SpecialAttribuut->Ypos*finalTextReduction/100;
                        CurTextPos.x = CurTextPos.x + SpecialAttribuut->Xpos*finalTextReduction/100;
                        currentOutlineThickness = SpecialAttribuut->OutlineThickness;
                        currentOutlineColor = SpecialAttribuut->OutlineColor;
                        break;
                }

            }
        }
        else
        {
            TagHit[j] = 0;
        }


        //suppres tags from screen
        if (PrintText[i] == '<') inTag=true;
        if (!inTag)
        {
            if (showOldColor)
            {
                notActiveImage->Canvas->Font->Color = curScreenSettings.CurSettings.ScreenElement[SettingsData::OLD_COLOR]->Font->Color;
            }
            if (wrap)
            {
                if ( PrintText[i] == ' ')
                {
                   if (CurTextPos.x > (Width - (Width / 8)) )
                     {
                        CurTextPos.x = x;
                        CurTextPos.y = CurTextPos.y + ( textAttribuut->Font->Size *1.8 );
                     }
                }
                else
                {
                   if (CurTextPos.x > (Width - Width / 25) )
                     {
                        CurTextPos.x = x;
                        CurTextPos.y = CurTextPos.y + ( textAttribuut->Font->Size *1.8 );
                     }
                }
            }
            SetBkMode(  notActiveImage->Canvas->Handle, TransparentColor );
            SetTextAlign(notActiveImage->Canvas->Handle, TA_BASELINE);

            if (!suppresOutline)
            {
                if (currentOutlineThickness>0)
                {
                   if (notActiveImage->Canvas->Font->Size > 9)
                    {
                      int HorVerOutline = currentOutlineThickness;
                      int diagOuline = (int) (HorVerOutline * 0.707 + 0.3);

                      TColor temp = notActiveImage->Canvas->Font->Color;
                      notActiveImage->Canvas->Font->Color = currentOutlineColor;
                      notActiveImage->Canvas->TextOutA(CurTextPos.x+HorVerOutline, CurTextPos.y, PrintText[i]);
                      notActiveImage->Canvas->TextOutA(CurTextPos.x-HorVerOutline, CurTextPos.y, PrintText[i]);
                      notActiveImage->Canvas->TextOutA(CurTextPos.x, CurTextPos.y+HorVerOutline, PrintText[i]);
                      notActiveImage->Canvas->TextOutA(CurTextPos.x, CurTextPos.y-HorVerOutline, PrintText[i]);
                      notActiveImage->Canvas->TextOutA(CurTextPos.x+diagOuline, CurTextPos.y+diagOuline, PrintText[i]);
                      notActiveImage->Canvas->TextOutA(CurTextPos.x-diagOuline, CurTextPos.y+diagOuline, PrintText[i]);
                      notActiveImage->Canvas->TextOutA(CurTextPos.x+diagOuline, CurTextPos.y-diagOuline, PrintText[i]);
                      notActiveImage->Canvas->TextOutA(CurTextPos.x-diagOuline, CurTextPos.y-diagOuline, PrintText[i]);
                      notActiveImage->Canvas->Font->Color = temp;
                    }
                    else if (PrintText.Length()>1)
                    {
                      // Make a outline color background block
                      // tempory select a different color so the next line will trigger to the new collor
                      notActiveImage->Canvas->Brush->Color = notActiveImage->Canvas->Font->Color;
                      notActiveImage->Canvas->Brush->Color = currentOutlineColor;
                    }
                }
            }
            notActiveImage->Canvas->TextOutA(CurTextPos.x, CurTextPos.y, PrintText[i]);
            CurTextPos = notActiveImage->Canvas->PenPos;
        }
        if (PrintText[i] == '>') inTag=false;
    }
    return CurTextPos;
}
//---------------------------------------------------------------------------

void TOutputScreen::writeSongTextLines()
{

    int songLength = curScreenSettings.CurSongData.getSongLength();
    if (songLength == 0) return;

    bool textFound=false;
    bool secondCoupletfound=false;
    int Count2ndCouplet=0;

    if (curScreenSettings.CurLine < 0) curScreenSettings.CurLine=0;
    if (curScreenSettings.startLine < 0) curScreenSettings.startLine=0;
    if (curScreenSettings.CurLine > (songLength-1)) curScreenSettings.CurLine=songLength;
    if (curScreenSettings.startLine > (songLength-1)) curScreenSettings.startLine=songLength;

    for (int i=curScreenSettings.startLine; i< curScreenSettings.startLine + curScreenSettings.CurSettings.NrOfLines; i++)
      if (i-curScreenSettings.startLine  >= 0)
        if (i < songLength)
            if ( i >= 0 )
            {
                 if (i<curScreenSettings.CurLine)   printLine(i, i-curScreenSettings.startLine+1, true, false);
                 else                               printLine(i, i-curScreenSettings.startLine+1, false, false);

                 if (curScreenSettings.CurSongData.text[i].Length()>1)
                      textFound=true;

                 if ( (textFound) && (curScreenSettings.CurSongData.text[i].Length()<1))
                      secondCoupletfound=true;

                 if  ( (curScreenSettings.CurSettings.OneSongblock) && secondCoupletfound ) return;

                 if (secondCoupletfound)
                 {
                   if (curScreenSettings.CurSettings.secondBlockBig) {/*do nothing*/}
                   else  Count2ndCouplet++;
                 }

                 if (Count2ndCouplet == 2 ) return;
            }
}
//---------------------------------------------------------------------------

void TOutputScreen::refreshScreen()
{
    TextAttribuut * si;

    if (Image1->Visible==true) notActiveImage =Image2;
    else                       notActiveImage= Image1;

    //clean the image with the background color
    if (curPictureAttrib.Transparent)
    {
      OutputScreen->TransparentColor = true;
      //OutputScreen->FormStyle = fsStayOnTop;
      notActiveImage->Canvas->Brush->Color = OutputScreen->TransparentColorValue;
    }
    else
    {
      OutputScreen->TransparentColor = false;
      //OutputScreen->FormStyle = fsNormal;
      notActiveImage->Canvas->Brush->Color = curPictureAttrib.BackGroundColor;
    }
    notActiveImage->Canvas->FillRect(TRect(0,0,Width,Height));

    //Load background picture
    if (curPictureAttrib.FileName.Length()>0)
       if (curPictureAttrib.Active)
          if (!curPictureAttrib.Transparent)
              ResizePictureAndLoad();

    setLeftMarginAndReduction();

    if (curScreenSettings.CurSettings.curMode == SettingsData::Mode_SONG)
    {
      // suppress all text on screen if songtext is done
      if (curScreenSettings.CurLine < curScreenSettings.CurSongData.getSongLength())
      {
          //Tone height
          si = curScreenSettings.CurSettings.ScreenElement[SettingsData::TONE_HEIGTH];
          if (si->Active)
                printLineXY(curScreenSettings.CurSongData.ToneHeightText, si->Xpos, si->Ypos +  si->Font->Size, false ,false, SettingsData::TONE_HEIGTH, false, true);

          //copy right
          si = curScreenSettings.CurSettings.ScreenElement[SettingsData::COPY_RIGHT];
          if (si->Active)
                printLineXY(curScreenSettings.CurSongData.copyRightText, si->Xpos + (Width/6), Height - (si->Font->Size * 3) + si->Ypos, false ,false, SettingsData::COPY_RIGHT, true, false);

          //song title
          si = curScreenSettings.CurSettings.ScreenElement[SettingsData::TITLE_TEXT];
          if (si->Active)
              printLineXY(curScreenSettings.CurSongData.TitleText, si->Xpos + leftMargin, si->Ypos + si->Font->Size, false ,false, SettingsData::TITLE_TEXT, false, false);

          //line pointer
          si = curScreenSettings.CurSettings.ScreenElement[SettingsData::LINE_POINTER];
          int yPos = CalculateLineYPosition(curScreenSettings.CurLine - curScreenSettings.startLine  + 1 ) + si->Ypos;
          String LinePointerChar = UpdateLineIndicator(si->Active);
          if (si->Active)
              printLineXY(LinePointerChar, si->Xpos + leftMargin - si->Font->Size, yPos, false ,false, SettingsData::LINE_POINTER, false, true);

          // current song
          si = curScreenSettings.CurSettings.ScreenElement[SettingsData::CURRENT_SONG];
          String curSong=curScreenSettings.CurSongData.shortFileNameAndVers;
          if ((si->Active) && (curSong.Length()>0) && (curSong[1]!='|'))
              printLineXY(curSong, si->Xpos, Height - (si->Font->Size) + si->Ypos, false ,false, SettingsData::CURRENT_SONG, false, false);

          writeSongTextLines();
      }
      //blink message (do at the end so it always stays on top)
      si = curScreenSettings.CurSettings.ScreenElement[SettingsData::BLINK_MESSAGE];
      if (si->Active)
            printLineXY(BlinkMessage, si->Xpos, si->Ypos +  si->Font->Size, false ,false, SettingsData::BLINK_MESSAGE, true, false);
    }
    else if (curScreenSettings.CurSettings.curMode == SettingsData::Mode_PAUSE)
    {
      // pause blink message
      si = curScreenSettings.CurSettings.ScreenElement[SettingsData::PAUSE_BLINK_MESSAGE];
      if (si->Active)
            printLineXY(BlinkMessage, si->Xpos, si->Ypos +  si->Font->Size, false ,false, SettingsData::PAUSE_BLINK_MESSAGE, true, true);
    }
}
//---------------------------------------------------------------------------

void TOutputScreen::setLeftMarginAndReduction()
{
    if (!calcMarginTextReduction) return;
    else calcMarginTextReduction=false;
    textReduction = 100;
    int sizeLargestLine = 0;
    int largestLineNumber = 0;
    // keep track of the minimum marge and the progress indicator.
    leftMargin = (int) ( (curScreenSettings.CurSettings.ScreenElement[SettingsData::SONG_TEXT]->Xpos * 2) + 5 );

    notActiveImage = ImageScratchPad;
    for (int i=0; i<curScreenSettings.CurSongData.getSongLength(); i++)
    {
        // print the line ousite of the screen to get the longest line
        int sizeCurrLine = printLine( /*songLine*/i, /*position*/1, true, true ).x;
        if (sizeCurrLine > sizeLargestLine)
        {
            sizeLargestLine = sizeCurrLine;
            largestLineNumber = i;
        }
    }
    while ((textReduction>10) & (sizeLargestLine > Width) )
    {
        //reduce the font size so the text will fit on the screen
        textReduction = textReduction - 10;
        // print the line ousite of the screen to check the length of the line
        sizeLargestLine = printLine( largestLineNumber, /*out of screen*/-12, true, true ).x;
    }
    if (curScreenSettings.CurSettings.LeftAllign)
        leftMargin = curScreenSettings.CurSettings.ScreenElement[SettingsData::SONG_TEXT]->Xpos;
    else
        leftMargin = ( ( Width -  sizeLargestLine ) / 2 ) + curScreenSettings.CurSettings.ScreenElement[SettingsData::SONG_TEXT]->Xpos;

    if (Image1->Visible==true) notActiveImage =Image2;
    else                       notActiveImage= Image1;
}
//---------------------------------------------------------------------------


String TOutputScreen::UpdateLineIndicator(bool LinePointerOn)
{
        if (curScreenSettings.CurSongData.getSongLength() == 0)
             return "";

        if (curScreenSettings.CurLine<0)
             return "";

        if (LinePointerOn)
        {
            if ((curScreenSettings.CurSongData.text[curScreenSettings.CurLine].Length() < 1 )
                ||(curScreenSettings.CurLine == curScreenSettings.CurSongData.getSongLength())
                ||(temporyHideLinePointer) )
                    return "-";
            else
                    return ">";
        }
        return "";
};
//---------------------------------------------------------------------------

void TOutputScreen::Init(String BaseDir)
{
        curScreenSettings.CurSettings.SetBaseDir(BaseDir, false);
        curScreenSettings.curPreviewSettings.SetBaseDir(BaseDir, true);
        curScreenSettings.CurSongData.SetBaseDir(BaseDir);
        iniFileName = BaseDir + "Settings\\Beamer.ini";

        Left =   StrToInt(GetFromIniFile("BeamerScreen", "Left",  "100", iniFileName));
        Width =  StrToInt(GetFromIniFile("BeamerScreen", "Width", "300", iniFileName));
        Top =    StrToInt(GetFromIniFile("BeamerScreen", "Top",   "100", iniFileName));
        Height = StrToInt(GetFromIniFile("BeamerScreen", "Height","100", iniFileName));

        LabelMoveMessage->Caption =  GetLanguageString("MoveMessage",LabelMoveMessage->Caption);
        OutputScreen->Caption =  GetLanguageString("TitleOutputScreen",OutputScreen->Caption);
}
//---------------------------------------------------------------------------

void __fastcall TOutputScreen::FormClose(TObject *Sender, TCloseAction &Action)
{
        PutInIniFile("BeamerScreen", "Left"  , IntToStr(Left)    ,iniFileName);
        PutInIniFile("BeamerScreen", "Width" , IntToStr(Width)   ,iniFileName);
        PutInIniFile("BeamerScreen", "Top"   , IntToStr(Top)     ,iniFileName);
        PutInIniFile("BeamerScreen", "Height", IntToStr(Height)  ,iniFileName);

        ClipCursor(NULL);
}
//---------------------------------------------------------------------------

void TOutputScreen::Recover()
{
        Left = 0;
        Width = 350;
        Top = 0;
        Height = 100;
}
//---------------------------------------------------------------------------

void TOutputScreen::setBlinkMessage(String s)
{
     BlinkMessage = s;
     blinkcounter = 0;
     SendToSlaves();
}
//---------------------------------------------------------------------------

void TOutputScreen::LoadSong(String filename)
{
     curScreenSettings.LoadSong(filename);
     calcMarginTextReduction=true;
}
//---------------------------------------------------------------------------

void TOutputScreen::setBrightnessAdjust(String s)
{
     BrightnessAdjust = calcBrightness(BrightnessAdjust,s);
     SendToSlaves();
}
//---------------------------------------------------------------------------

void TOutputScreen::setContrastAdjust(String s)
{
     ContrastAdjust = calcContrast(ContrastAdjust, s);
     SendToSlaves();
}
//---------------------------------------------------------------------------
void TOutputScreen::SlaveMessage(String s)
{
      SlaveBlinkMessage = s;
      blinkcounter = 0;
      SendToSlaves();
}

void TOutputScreen::SendToSlaves()
{
     String s = "<OutputScreen>";
     s += "<BrightnessAdjust>" + IntToStr(BrightnessAdjust) + "</BrightnessAdjust>\n";
     s += "<ContrastAdjust>" + FloatToStr(ContrastAdjust) + "</ContrastAdjust>\n";
     if (SlaveBlinkMessage.Length()>0)   s += "<BlinkMessage>" + SlaveBlinkMessage + "</BlinkMessage>\n";
     else  s += "<BlinkMessage>" + BlinkMessage + "</BlinkMessage>\n";
     s += "<blinkcounter>" + IntToStr(blinkcounter) + "</blinkcounter>\n";
     s += "</OutputScreen>";
     MainForm->SendDataToSlaves(s);
}

void TOutputScreen::ReceiveAsSlave(String s)
{
     if (s.Pos("<BrightnessAdjust>")==1)
     {
       BrightnessAdjust = StrToInt(getUntil(getAfter(s,">"),"<"));
       s = getAfter(s,"</BrightnessAdjust>\n");
     }
     if (s.Pos("<ContrastAdjust>")==1)
     {
        ContrastAdjust = StrToFloat(getUntil(getAfter(s,">"),"<"));
        s = getAfter(s,"</ContrastAdjust>\n");
     }
     if (s.Pos("<BlinkMessage>")==1)
     {
        BlinkMessage = getUntil(getAfter(s,">"),"<");
        s = getAfter(s,"</BlinkMessage>\n");
     }
     if (s.Pos("<blinkcounter>")==1)
     {
        blinkcounter = StrToInt(getUntil(getAfter(s,">"),"<"));
        s = getAfter(s,"</blinkcounter>\n");
     }
}


void TOutputScreen::SetText(const String s)
{
   curScreenSettings.SetText(s);
   calcMarginTextReduction=true;
   LateRefesch=true;
}
void __fastcall TOutputScreen::Exit1Click(TObject *Sender)
{
    MainForm->Close();
}
//---------------------------------------------------------------------------


