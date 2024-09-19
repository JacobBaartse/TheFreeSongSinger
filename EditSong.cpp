/*
Open source not for commercial deployment
*/
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "EditSong.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TEditSongForm *EditSongForm;
//---------------------------------------------------------------------------
__fastcall TEditSongForm::TEditSongForm(TComponent* Owner)
        : TForm(Owner)
{
      changed = false;
      FontResize = true;
}
//---------------------------------------------------------------------------
void __fastcall TEditSongForm::FormActivate(TObject *Sender)
{
      MainForm->BlockFocus = true;
      LabelToneHeight->Caption = GetLanguageString("ToneHeight",LabelToneHeight->Caption);
      LabelSongTitle->Caption = GetLanguageString("SongTitle",LabelSongTitle->Caption);
      LabelSongText->Caption = GetLanguageString("SongText",LabelSongText->Caption);
      LabelCopyRight->Caption = GetLanguageString("CopyRight",LabelCopyRight->Caption);
      LabelAllowedTags->Caption = GetLanguageString("AllowedTags",LabelAllowedTags->Caption);
      File1->Caption   = GetLanguageString("File",File1->Caption);
      New1->Caption    = GetLanguageString("New",New1->Caption);
      OPen1->Caption   = GetLanguageString("Open",OPen1->Caption);
      Save1->Caption   = GetLanguageString("Save",Save1->Caption);
      Saveas1->Caption = GetLanguageString("SaveAs",Saveas1->Caption);
      Exit1->Caption   = GetLanguageString("Exit",Exit1->Caption);
}
//---------------------------------------------------------------------------

void __fastcall TEditSongForm::Saveas1Click(TObject *Sender)
{
      SaveSongAs();
}
//---------------------------------------------------------------------------

void TEditSongForm::SaveSongAs()
{
    if (OpenedFileName.Length()==0)
         SaveDialog1->FileName = MainForm->ProgramDir + "Data\\*";
    else SaveDialog1->FileName = OpenedFileName;

    SaveDialog1->InitialDir =  MainForm->ProgramDir + "Data\\";
    if (SaveDialog1->Execute())
    {
        OpenedFileName = SaveDialog1->FileName.c_str();
        SaveSong(OpenedFileName);
        StatusBar1->SimpleText = OpenedFileName;
        EditSongForm->Caption = OpenedFileName;
    }
}
//---------------------------------------------------------------------------

void TEditSongForm::SaveSong(String fileName)
{
    changed = false;
    ifstream testSongFile (fileName.c_str());
    if (testSongFile.is_open())
    {
      testSongFile.close(); // the file already exists.
      int answer = MessageDlgPos("Overwrite existing file?", mtInformation,  TMsgDlgButtons() << mbOK << mbCancel, 0, EditSongForm->Left, EditSongForm->Top);
      if (answer == 2)  return; // cancel pressed.
    }

    ofstream songFile (fileName.c_str());
    int lineNumber = 0;
    bool TitleDone = false;

    while ( (fullSongText[lineNumber].Pos("<tekst>") == 0) &&
            (lineNumber < fullSongLength) )
    {
        if (fullSongText[lineNumber].Pos("<titel>") > 0)
        {
                songFile.write("<titel>", 7);
                songFile.write(EditSongTitle->Text.c_str(), EditSongTitle->Text.Length());
                songFile.write("</titel>", 8);
                TitleDone=true;
        }
        else
                songFile.write(fullSongText[lineNumber].c_str(), fullSongText[lineNumber].Length());
        songFile.write("\n",1);
        lineNumber++;
    }
    if (!TitleDone)
    {
        songFile.write("<titel>", 7);
        songFile.write(EditSongTitle->Text.c_str(), EditSongTitle->Text.Length());
        songFile.write("</titel>", 8);
        songFile.write("\n",1);
    }
    while ((fullSongText[lineNumber].Pos("</tekst>")==0) &&
           (lineNumber < fullSongLength))
    {
        lineNumber++;
    }
    if (fullSongText[lineNumber].Pos("</tekst>")!=0) lineNumber++;

    songFile.write("<tekst>",7);

    // remove trailing empty lines
    int nrOfLines = MemoSongText->Lines->Count;
    while ((MemoSongText->Lines->operator [](nrOfLines-1).Length()==0)  &&  (nrOfLines>0))
             nrOfLines--;
             
    for (int i = 0; i<nrOfLines; i++)
    {
        AnsiString test;
        test.c_str();
        test.Length();
        songFile.write(MemoSongText->Lines->operator [](i).c_str(), MemoSongText->Lines->operator [](i).Length());
        if (i < (MemoSongText->Lines->Count -1) )
            songFile.write("\n",1);
    }
    songFile.write("</tekst>\n",9);
    while ((fullSongText[lineNumber].Pos("<copyrights>")==0) &&
           (lineNumber < fullSongLength))
    {
        songFile.write(fullSongText[lineNumber].c_str(), fullSongText[lineNumber].Length());
        songFile.write("\n",1);
        lineNumber++;
    }
    while ((fullSongText[lineNumber].Pos("</copyrights>")==0) &&
           (lineNumber < fullSongLength))
    {
        lineNumber++;
    }
    if (fullSongText[lineNumber].Pos("</copyrights>")!=0) lineNumber++;

    songFile.write("<copyrights>",12);
    songFile.write(EditCopyRight->Text.c_str(), EditCopyRight->Text.Length());
    songFile.write("</copyrights>\n",14);

    while ((fullSongText[lineNumber].Pos("<toonsoort1>")==0) &&
           (lineNumber < fullSongLength))
    {
        songFile.write(fullSongText[lineNumber].c_str(), fullSongText[lineNumber].Length());
        songFile.write("\n",1);
        lineNumber++;
    }
    while ((fullSongText[lineNumber].Pos("</toonsoort1>")==0) &&
           (lineNumber < fullSongLength))
    {
        lineNumber++;
    }
    if (fullSongText[lineNumber].Pos("</toonsoort1>")!=0) lineNumber++;
    songFile.write("<toonsoort1>",12);
    songFile.write(EditToneHeight->Text.c_str(), EditToneHeight->Text.Length());
    songFile.write("</toonsoort1>\n",14);
    while (lineNumber < fullSongLength)
    {
        songFile.write(fullSongText[lineNumber].c_str(), fullSongText[lineNumber].Length());
        songFile.write("\n",1);
        lineNumber++;
    }
}

//---------------------------------------------------------------------------
void __fastcall TEditSongForm::OPen1Click(TObject *Sender)
{
    if (OpenedFileName.Length()==0)
         OpenDialog1->FileName = MainForm->ProgramDir + "Data\\*";
    else OpenDialog1->FileName = OpenedFileName;

    OpenDialog1->InitialDir =  MainForm->ProgramDir + "Data\\";
    if (OpenDialog1->Execute())
    {
        LoadSongFromFile(OpenDialog1->FileName);
    }
}
//---------------------------------------------------------------------------


void TEditSongForm::LoadSongFromFile(String SongFileName)
{
    String screenText[1024];
    int songLength = 0;

    OpenedFileName = SongFileName.c_str();
    char buffer[1024];

    ifstream songFile (SongFileName.c_str());

    if (! songFile.is_open()) return;

    StatusBar1->SimpleText = OpenedFileName;
        EditSongForm->Caption = OpenedFileName;

    bool allTextRead= false;
    bool inTextArea = false;
    bool inCopyRightArea = false;
    String copyRightText = "";
    EditSongTitle->Text="";

    fullSongLength = 0;
    while (! allTextRead )
    {
        songFile.getline (buffer,1024);
        String lineBuffer = buffer;

        //Store the full song text
        fullSongText[fullSongLength]= lineBuffer;
        fullSongLength++;

        if (lineBuffer.Pos("<encrypted>")>0)
        {
                screenText[0]= "Text can not be changed";
                screenText[1]= "send the change request to:";
                screenText[2]= " j.baartse@gmail.com";
                songLength=3;
                break;
        }
        //remove tabs from the lineBuffer
        lineBuffer = replace(lineBuffer, "\t", "");

        int textTagPos = lineBuffer.Pos("<tekst>");
        if (textTagPos != 0)
        {
            lineBuffer= getAfter(lineBuffer, "<tekst>");
            screenText[songLength]=lineBuffer;
            inTextArea=true;
        }
        textTagPos = lineBuffer.Pos("</tekst>");
        if (textTagPos != 0)
        {
            lineBuffer=getUntil(lineBuffer, "</tekst>");
            screenText[songLength]=lineBuffer;
            inTextArea=false;
            songLength++;
        }
        if (inTextArea)
        {
            screenText[songLength]=lineBuffer;
            songLength++;
        }
        textTagPos = lineBuffer.Pos("<copyrights>");
        if (textTagPos != 0)
        {
            lineBuffer=getAfter(lineBuffer,"<copyrights>");
            inCopyRightArea=true;
        }
        textTagPos = lineBuffer.Pos("</copyrights>");
        if (textTagPos != 0)
        {
            lineBuffer=getUntil(lineBuffer,"</copyrights>");
            copyRightText =  lineBuffer + " " + copyRightText;
            inCopyRightArea=false;
        }
        if (inCopyRightArea)
        {
            copyRightText =  copyRightText + lineBuffer;
        }

        textTagPos = lineBuffer.Pos("<toonsoort1>");
        if (textTagPos != 0)
        {
            lineBuffer=getAfter(lineBuffer,"<toonsoort1>");
        }
        textTagPos = lineBuffer.Pos("</toonsoort1>");
        if (textTagPos != 0)
        {
            lineBuffer=getUntil(lineBuffer,"</toonsoort1>");
            EditToneHeight->Text = lineBuffer;
        }

        textTagPos = lineBuffer.Pos("<titel>");
        if (textTagPos != 0)
        {
            lineBuffer=getAfter(lineBuffer,"<titel>");
        }
        textTagPos = lineBuffer.Pos("</titel>");
        if (textTagPos != 0)
        {
            lineBuffer=getUntil(lineBuffer,"</titel>");
            EditSongTitle->Text = lineBuffer;
        }

        if (songFile.eof()) allTextRead=true;
    }
    fullSongLength--;

    songFile.close();

    MemoSongText->Clear();
    TStrings * song = new TStringList();
    for (int i=0; i< songLength; i++)
    {
        song->Add(screenText[i]);
    }
    MemoSongText->Lines = song;   //copy constructor used of TStrings
    delete song;

    EditCopyRight->Text = copyRightText;
    changed = false;
}
//---------------------------------------------------------------------------


void __fastcall TEditSongForm::New1Click(TObject *Sender)
{
    EditCopyRight->Text = "©";
    EditToneHeight->Text = "";
    EditSongTitle->Text = "";
    MemoSongText->Lines->Clear();
    OpenedFileName = "";
    changed = false;
}
//---------------------------------------------------------------------------

void __fastcall TEditSongForm::FormResize(TObject *Sender)
{
   if (!FontResize) return;

   if (fontScale==0) fontScale = 30;
   MemoSongText->Font->Size =  MemoSongText->Width / fontScale;
}
//---------------------------------------------------------------------------

void __fastcall TEditSongForm::Save1Click(TObject *Sender)
{
    if (OpenedFileName != "") SaveSong(OpenedFileName);
    else SaveSongAs();
}
//---------------------------------------------------------------------------

void __fastcall TEditSongForm::Exit1Click(TObject *Sender)
{
     EditSongForm->Hide();
}
//---------------------------------------------------------------------------

void __fastcall TEditSongForm::EditChange(TObject *Sender)
{
     changed = true;
}
//---------------------------------------------------------------------------

void __fastcall TEditSongForm::FormHide(TObject *Sender)
{
    if (changed ==true)
    {
        int answer = MessageDlgPos("Save changes?", mtInformation,  TMsgDlgButtons() << mbYes <<mbNo, 0, Left+30, Top+30);
        if (answer == 6) // Yes
           SaveSong(OpenedFileName);
        if (answer == 7) // No
           changed = false;
    }
}
//---------------------------------------------------------------------------

void __fastcall TEditSongForm::FormShow(TObject *Sender)
{
    fontScale = 30;
    Left = MainForm->Left + 10;
    Top = MainForm->Top + 10;
    Height = MainForm->Height -20;
    if (changed ==false)   LoadSongFromFile(MainForm->PreviewSongData.fileName);

}
//---------------------------------------------------------------------------




void __fastcall TEditSongForm::Selectfont1Click(TObject *Sender)
{
      FontDialog1->Font = MemoSongText->Font;
      FontDialog1->Execute();
      MemoSongText->Font = FontDialog1->Font;
      fontScale =    MemoSongText->Width / MemoSongText->Font->Size;
      FontResize=true;
}
//---------------------------------------------------------------------------

void __fastcall TEditSongForm::CourierNew1Click(TObject *Sender)
{
     MemoSongText->Font->Name = "Courier new";
     MemoSongText->Font->Size = 16;
     FontResize=false;
}
//---------------------------------------------------------------------------



void __fastcall TEditSongForm::Removeacc1Click(TObject *Sender)
{
    String screenText[1024];
    for (int i=0; i<MemoSongText->Lines->Count; i++)
    {
      screenText[i] = MemoSongText->Lines->operator [](i);
      screenText[i] = replace(screenText[i], "<acc>", "");
      screenText[i] = replace(screenText[i], "<--->", "");
    }
    TStrings * song = new TStringList();
    for (int i=0; i< MemoSongText->Lines->Count; i++)
    {
        song->Add(screenText[i]);
    }
    MemoSongText->Clear();
    MemoSongText->Lines = song;   //copy constructor used of TStrings
    delete song;
}
//---------------------------------------------------------------------------

void __fastcall TEditSongForm::Addacc1Click(TObject *Sender)
{
    Removeacc1Click(Sender);
    String screenText[1024];
    for (int i=0; i<MemoSongText->Lines->Count; i++)
    {
      screenText[i] = MemoSongText->Lines->operator [](i);
      String t =  replace(screenText[i]," ","");
      if (t.Length()>0)
      {
         if (( screenText[i].Length()*10 / t.Length()) >15)
             screenText[i] = "<acc>" + screenText[i] ;
         else
             screenText[i] = "<--->" + screenText[i] ;
      }
    }
    TStrings * song = new TStringList();
    for (int i=0; i< MemoSongText->Lines->Count; i++)
    {
        song->Add(screenText[i]);
    }
    MemoSongText->Clear();
    MemoSongText->Lines = song;   //copy constructor used of TStrings
    delete song;
}
//---------------------------------------------------------------------------


void __fastcall TEditSongForm::MemoSongTextDblClick(TObject *Sender)
{
      MemoSongText->SelectAll();
}
//---------------------------------------------------------------------------

void __fastcall TEditSongForm::FormDeactivate(TObject *Sender)
{
      MainForm->BlockFocus = false;
}
//---------------------------------------------------------------------------

