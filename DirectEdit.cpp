/*
Open source not for commercial deployment
*/
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DirectEdit.h"
#include "OutputScreenUnit.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDirectEditForm *DirectEditForm;
//---------------------------------------------------------------------------
__fastcall TDirectEditForm::TDirectEditForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TDirectEditForm::FormActivate(TObject *Sender)
{
      MainForm->BlockFocus = true;
      TitleLabel->Caption = GetLanguageString("Title",TitleLabel->Caption);
      LineCountLabel->Caption = GetLanguageString("NumberOfLinesOnBeamer",TitleLabel->Caption);
      DirectEditForm->Caption = GetLanguageString("DirectEditTitle",TitleLabel->Caption);

}
//---------------------------------------------------------------------------
void __fastcall TDirectEditForm::FormShow(TObject *Sender)
{
    Left = MainForm->Left + 10;
    Top = MainForm->Top + 10;
    Height = MainForm->Height -20;        
}
//---------------------------------------------------------------------------
void __fastcall TDirectEditForm::TextMemoKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
    shiftDown = Shift.Contains(ssShift);
    controlDown = Shift.Contains(ssCtrl);
    altDown =  Shift.Contains(ssAlt);
    if (!shiftDown && !controlDown && !altDown)
        if ((Key == 13) || (Key == ' '))
            ShowOnScreen();

    if (shiftDown && !controlDown && !altDown)
        if (Key==186)
            ShowOnScreen();

    if (!shiftDown && controlDown && !altDown)
        if (Key==49)        //ctrl 1
          Hide();

}
//---------------------------------------------------------------------------
void __fastcall TDirectEditForm::TextMemoKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    shiftDown = Shift.Contains(ssShift);
    controlDown = Shift.Contains(ssCtrl);
    altDown =  Shift.Contains(ssAlt);

}
//---------------------------------------------------------------------------

void TDirectEditForm::ShowOnScreen()
{
    SongData *sd;
    sd =  &(OutputScreen->curScreenSettings.CurSongData);
    sd->TitleText = TitleEdit->Text;

    String tempText = TextMemo->Lines->Text;
    int i=0;
    while (tempText.Length()>0)
    {
        sd->text[i]= getUntil(tempText,"\r\n");
        tempText = getAfter(tempText,"\r\n");
        i++;
    }
    int startline = i-LineCountComboBox->ItemIndex-1;
    if (startline < 0) startline = 0;

    OutputScreen->curScreenSettings.startLine=startline;
    OutputScreen->curScreenSettings.CurLine = startline;
    sd->shortFileNameAndVers = "";
    sd->setSongLength(i);

    OutputScreen->LateRefesch=true;
}

void TDirectEditForm::Process_Command(String s)
{
     if (LoadedFile.Length()==0)
             LoadedFile = MainForm->ProgramDir + "DirectEdit\\*";
             
     if (s=="Open")
     {

        MainForm->FileOpenDialog->Filter="Text(*.txt)|*.txt";
        MainForm->FileOpenDialog->FileName = LoadedFile;
        MainForm->FileOpenDialog->DefaultExt=".txt";
        if (MainForm->FileOpenDialog->Execute())
        {
           Open(MainForm->FileOpenDialog->FileName);
        }
     }
     else if  (s=="SaveAs")
     {
        MainForm->FileSaveDialog->Filter="Text(*.txt)|*.txt";
        MainForm->FileSaveDialog->FileName = LoadedFile;
        MainForm->FileSaveDialog->DefaultExt=".txt";
        if (MainForm->FileSaveDialog->Execute())
        {
           SaveAs(MainForm->FileSaveDialog->FileName);
        }
     }
}

void TDirectEditForm::SaveAs(String s)
{
     //check if already exist
    ifstream testFile (s.c_str());
    if (testFile.is_open())
    {
      testFile.close(); // the file already exists.
      int answer = MessageDlgPos("Overwrite existing file?", mtInformation,  TMsgDlgButtons() << mbOK << mbCancel, 0, DirectEditForm->Left, DirectEditForm->Top);
      if (answer == 2)  return; // cancel pressed.
    }

    //save to the file.
    ofstream editFile (s.c_str());
    editFile.write(TitleEdit->Text.c_str(),TitleEdit->Text.Length());
    editFile.write("\r\n",2);
    editFile.write(TextMemo->Text.c_str(), TextMemo->Text.Length());
    editFile.close();
    LoadedFile = s;
}

void TDirectEditForm::Open(String s)
{
    char buffer[4096];
    ifstream editFile (s.c_str());
    if (editFile.is_open())
    {
      int data_len = editFile.readsome(buffer, 4096);
      buffer[data_len] = 0; // put a null terminator after the text read.
      TitleEdit->Text = getUntil(buffer,"\r\n");
      TextMemo->Text  = getAfter(buffer,"\r\n");
      editFile.close();
      LoadedFile = s;
    }
}


void __fastcall TDirectEditForm::FormDeactivate(TObject *Sender)
{
     MainForm->BlockFocus = false;
}
//---------------------------------------------------------------------------

