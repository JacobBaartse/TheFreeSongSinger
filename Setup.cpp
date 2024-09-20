/*
Open source not for commercial deployment
*/
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Setup.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSetupScreen *SetupScreen;
//---------------------------------------------------------------------------
__fastcall TSetupScreen::TSetupScreen(TComponent* Owner)
        : TForm(Owner)
{
}

void __fastcall TSetupScreen::ElementSelChange(TObject *Sender)
{
     UpdateFullGui();

     if (ElementSel->ItemIndex==14) MainForm->ProcessCommands("Pause_On");  // Pause blik message
     else MainForm->ProcessCommands("Pause_Off");
}
//---------------------------------------------------------------------------

void  TSetupScreen::UpdateFullGui()
{
    switch ( ElementSel->ItemIndex)
    {
    //       void adjustGui(type, color, smaler, larger, up, left, right, down, reset, outlineless, outlinemore, outlinecolor, active);
       case  0:  adjustGui(1,1,1,1,0,0,0,0,0,1,1,1,0); break;  // all text
       case  1:  adjustGui(1,1,1,1,1,1,1,1,1,1,1,1,0); break;  // song text
       case  2:  adjustGui(1,1,1,1,0,0,0,0,0,1,1,1,0); break;  // normal text
       case  3:  adjustGui(0,1,0,0,0,0,0,0,0,0,0,0,0); break;  // old text
       case  4:  adjustGui(0,1,1,1,0,0,0,0,0,0,0,0,0); break;  // Heading 2
       case  5:  adjustGui(0,1,1,1,0,0,0,0,0,0,0,0,0); break;  // Heading 3
       case  6:  adjustGui(0,1,1,1,0,0,0,0,0,0,0,0,0); break;  // Heading 4
       case  7:  adjustGui(1,1,1,1,1,1,1,1,1,1,1,1,0); break;  // Translation
       case  8:  adjustGui(1,1,1,1,1,1,1,1,1,1,1,1,1); break;  // Tone height
       case  9:  adjustGui(1,1,1,1,1,1,1,1,1,1,1,1,1); break;  // song Title
       case  10: adjustGui(1,1,1,1,1,1,1,1,1,1,1,1,0); break;  // Blink message
       case  11: adjustGui(1,1,1,1,1,1,1,1,1,1,1,1,1); break;  // Line pointer
       case  12: adjustGui(1,1,1,1,1,1,1,1,1,1,1,1,1); break;  // CurrentSong
       case  13: adjustGui(1,1,1,1,1,1,1,1,1,1,1,1,1); break;  // Copy right
       case  14: adjustGui(1,1,1,1,1,1,1,1,1,1,1,1,0); break;  // Pause blik message
    };
    UpdateButtons();

}

void TSetupScreen::Init(String s)
{
     NameList[0]="AllText";
     NameList[1]="SongText";
     NameList[2]="NormalText";
     NameList[3]="OldText";
     NameList[4]="Heading2";
     NameList[5]="Heading3";
     NameList[6]="Heading4";
     NameList[7]="Translation";
     NameList[8]="ToneHeight";
     NameList[9]="SongTitle";
     NameList[10]="BlinkMessage";
     NameList[11]="LinePointer";
     NameList[12]="CurrenSong";
     NameList[13]="CopyRight";
     NameList[14]="PauseBlinkMessage";

     PictureList[0]="BackGroundPicture";
     PictureList[1]="PausePicture";

     TIcon *Icone = new TIcon();
     SpeedButtonsIconList = new TImageList(this);

     Icone->LoadFromFile(s+"Icons\\ContrastHigh.ico");    SpeedButtonsIconList->AddIcon(Icone);
     Icone->LoadFromFile(s+"Icons\\Contrast.ico");        SpeedButtonsIconList->AddIcon(Icone);
     Icone->LoadFromFile(s+"Icons\\ContrastLow.ico");     SpeedButtonsIconList->AddIcon(Icone);
     Icone->LoadFromFile(s+"Icons\\BrightnessDark.ico");  SpeedButtonsIconList->AddIcon(Icone);
     Icone->LoadFromFile(s+"Icons\\Brightness.ico");      SpeedButtonsIconList->AddIcon(Icone);
     Icone->LoadFromFile(s+"Icons\\BrightnessLight.ico"); SpeedButtonsIconList->AddIcon(Icone);

     ToolBar->Images=SpeedButtonsIconList;
     delete Icone;
}
//---------------------------------------------------------------------------

void __fastcall TSetupScreen::FontTypeButtonClick(TObject *Sender)
{
     MainForm->ProcessCommands("ChangeSetting_" + NameList[ElementSel->ItemIndex] + "_FontType");
}
//---------------------------------------------------------------------------
void __fastcall TSetupScreen::PositionUpButtonClick(TObject *Sender)
{
     MainForm->ProcessCommands("ChangeSetting_" + NameList[ElementSel->ItemIndex] + "_"+((TButton*)Sender)->Caption);
}
//---------------------------------------------------------------------------
void __fastcall TSetupScreen::FontColorButtonClick(TObject *Sender)
{
     MainForm->ProcessCommands("ChangeSetting_" + NameList[ElementSel->ItemIndex] + "_Color");
}
//---------------------------------------------------------------------------
void __fastcall TSetupScreen::FontReduceButtonClick(TObject *Sender)
{
     MainForm->ProcessCommands("ChangeSetting_" + NameList[ElementSel->ItemIndex] + "_Reduce");
}
//---------------------------------------------------------------------------
void __fastcall TSetupScreen::FontEnlargeButtonClick(TObject *Sender)
{
     MainForm->ProcessCommands("ChangeSetting_" + NameList[ElementSel->ItemIndex] + "_Enlarge");
}
//---------------------------------------------------------------------------
void __fastcall TSetupScreen::LeftAlignCheckBoxClick(TObject *Sender)
{
     if (LeftAlignCheckBox->Checked)
          MainForm->ProcessCommands("ChangeSetting_LeftAlign_On");
     else MainForm->ProcessCommands("ChangeSetting_LeftAlign_Off");
}
//---------------------------------------------------------------------------


void __fastcall TSetupScreen::ToolButton2Click(TObject *Sender)
{
     MainForm->ProcessCommands("ChangeSetting_" + PictureList[PictureSel->ItemIndex] + "_Contrast_1.1");
}
//---------------------------------------------------------------------------

void __fastcall TSetupScreen::ToolButton3Click(TObject *Sender)
{
     MainForm->ProcessCommands("ChangeSetting_" + PictureList[PictureSel->ItemIndex] + "_Contrast_Reset");

}
//---------------------------------------------------------------------------

void __fastcall TSetupScreen::ToolButton4Click(TObject *Sender)
{
     MainForm->ProcessCommands("ChangeSetting_" + PictureList[PictureSel->ItemIndex] + "_Contrast_0.909");
}
//---------------------------------------------------------------------------

void __fastcall TSetupScreen::ToolButton6Click(TObject *Sender)
{
     MainForm->ProcessCommands("ChangeSetting_" + PictureList[PictureSel->ItemIndex] + "_Brightness_Dec_10");
}
//---------------------------------------------------------------------------

void __fastcall TSetupScreen::ToolButton7Click(TObject *Sender)
{
     MainForm->ProcessCommands("ChangeSetting_" + PictureList[PictureSel->ItemIndex] + "_Brightness_Reset");
}
//---------------------------------------------------------------------------

void __fastcall TSetupScreen::ToolButton8Click(TObject *Sender)
{
     MainForm->ProcessCommands("ChangeSetting_" + PictureList[PictureSel->ItemIndex] + "_Brightness_Inc_10");
}
//---------------------------------------------------------------------------

void __fastcall TSetupScreen::PictureSelectButtonClick(TObject *Sender)
{
     MainForm->ProcessCommands("ChangeSetting_" + PictureList[PictureSel->ItemIndex] + "_OpenFile_");
}
//---------------------------------------------------------------------------


void __fastcall TSetupScreen::CheckBoxPictureClick(TObject *Sender)
{
   if (CheckBoxPicture->Checked)
        MainForm->ProcessCommands("ChangeSetting_" + PictureList[PictureSel->ItemIndex] + "_Active_On");
   else MainForm->ProcessCommands("ChangeSetting_" + PictureList[PictureSel->ItemIndex] + "_Active_Off");
   UpdateButtons();
}
//---------------------------------------------------------------------------


void TSetupScreen::UpdateButtons()
{
     SettingsData * setting =  &(OutputScreen->curScreenSettings.CurSettings);

     CheckBoxTransparent->Checked =  setting->getTransparent(PictureList[PictureSel->ItemIndex]);
     CheckBoxPicture->Checked     =  setting->getPitureActive(PictureList[PictureSel->ItemIndex]);
     ActiveCheckBox->Checked      =  setting->getTextAttribuutActive(NameList[ElementSel->ItemIndex]);
     MoreTextBlocksCheck->Checked =  !(setting->OneSongblock);
     SecondBlockOneLineCheckBox->Checked =  !(setting->secondBlockBig);
     LeftAlignCheckBox->Checked   =  setting->LeftAllign;



     if (CheckBoxTransparent->Checked)
     {
        ButtonBackgroundColor->Visible=false;
        CheckBoxPicture->Visible=false;
        PictureSelectButton->Visible=false;
        ToolBar->Visible=false;
     }
     else
     {
        ButtonBackgroundColor->Visible=true;
        CheckBoxPicture->Visible=true;
        if (CheckBoxPicture->Checked)
        {
            PictureSelectButton->Visible=true;
            ToolBar->Visible=true;
        }
        else
        {
            PictureSelectButton->Visible=false;
            ToolBar->Visible=false;
        }
     }
     Panel3->Visible =  ActiveCheckBox->Checked;
}
void __fastcall TSetupScreen::CheckBoxTransparentClick(TObject *Sender)
{
   if (CheckBoxTransparent->Checked)
        MainForm->ProcessCommands("ChangeSetting_" + PictureList[PictureSel->ItemIndex] + "_Transparent_On");
   else MainForm->ProcessCommands("ChangeSetting_" + PictureList[PictureSel->ItemIndex] + "_Transparent_Off");
   UpdateButtons();
}
//---------------------------------------------------------------------------

void __fastcall TSetupScreen::ActiveCheckBoxClick(TObject *Sender)
{
   if (ActiveCheckBox->Checked)
        MainForm->ProcessCommands("ChangeSetting_" + NameList[ElementSel->ItemIndex] + "_Active_On");
   else MainForm->ProcessCommands("ChangeSetting_" + NameList[ElementSel->ItemIndex] + "_Active_Off");

   UpdateButtons();
}
//---------------------------------------------------------------------------

void __fastcall TSetupScreen::Sampletext1Click(TObject *Sender)
{
     PictureSel->ItemIndex=0;
     MainForm->ProcessCommands("Pause_Off,A100,Output_Load_FromPreviewWithLineNr,Outdateline_More,\"Blink Message\"");

}
//---------------------------------------------------------------------------

void __fastcall TSetupScreen::MoreTextBlocksCheckClick(TObject *Sender)
{
    if (MoreTextBlocksCheck->Checked)
          MainForm->ProcessCommands("ChangeSetting_TextBlock_Multiple");
    else  MainForm->ProcessCommands("ChangeSetting_TextBlock_One");
}
//---------------------------------------------------------------------------

void __fastcall TSetupScreen::OutlineLessButtonClick(TObject *Sender)
{
     MainForm->ProcessCommands("ChangeSetting_" + NameList[ElementSel->ItemIndex] + "_Outline_Less");
}
//---------------------------------------------------------------------------

void __fastcall TSetupScreen::OutlineMoreButtonClick(TObject *Sender)
{
     MainForm->ProcessCommands("ChangeSetting_" + NameList[ElementSel->ItemIndex] + "_Outline_More");
}
//---------------------------------------------------------------------------

void __fastcall TSetupScreen::OutlineColorButtonClick(TObject *Sender)
{
     MainForm->ProcessCommands("ChangeSetting_" + NameList[ElementSel->ItemIndex] + "_Outline_Color");

}
//---------------------------------------------------------------------------

void __fastcall TSetupScreen::ButtonBackgroundColorClick(TObject *Sender)
{
        MainForm->ProcessCommands("ChangeSetting_" + PictureList[PictureSel->ItemIndex] + "_Color");
}
//---------------------------------------------------------------------------

void __fastcall TSetupScreen::LineDistLessButtonClick(TObject *Sender)
{
        MainForm->ProcessCommands("ChangeSetting_Linedistance_Less");
}
//---------------------------------------------------------------------------

void __fastcall TSetupScreen::LineDistMoreButtonClick(TObject *Sender)
{
        MainForm->ProcessCommands("ChangeSetting_Linedistance_More");
}
//---------------------------------------------------------------------------

void __fastcall TSetupScreen::LineCountLessButtonClick(TObject *Sender)
{
        MainForm->ProcessCommands("ChangeSetting_Linecount_Less");
}
//---------------------------------------------------------------------------

void __fastcall TSetupScreen::LineCountMoreButtonClick(TObject *Sender)
{
        MainForm->ProcessCommands("ChangeSetting_Linecount_More");
}
//---------------------------------------------------------------------------

void __fastcall TSetupScreen::Open1Click(TObject *Sender)
{
        MainForm->ProcessCommands("ChangeSetting_File_Open");
}
//---------------------------------------------------------------------------

void __fastcall TSetupScreen::Save1Click(TObject *Sender)
{
        MainForm->ProcessCommands("ChangeSetting_File_Save");
}
//---------------------------------------------------------------------------

void __fastcall TSetupScreen::Saveas1Click(TObject *Sender)
{
        MainForm->ProcessCommands("ChangeSetting_File_SaveAs");
}
//---------------------------------------------------------------------------

void __fastcall TSetupScreen::FormShow(TObject *Sender)
{
        Left = MainForm->Left + 10;
        Top = MainForm->Top + 10;
        if (OutputScreen->curScreenSettings.CurSettings.curMode == SettingsData::Mode_PAUSE)
        {
            PictureSel->ItemIndex=1;
            ElementSel->ItemIndex=15;
        }
        else
        {
            PictureSel->ItemIndex=0;
            if (ElementSel->ItemIndex==15) ElementSel->ItemIndex=1;
        }

        UpdateFullGui();
}
//---------------------------------------------------------------------------
void __fastcall TSetupScreen::PictureSelChange(TObject *Sender)
{
        if (PictureSel->ItemIndex==0)
        MainForm->ProcessCommands("Pause_Off");
        else if (PictureSel->ItemIndex==1) MainForm->ProcessCommands("Pause_On");
        UpdateButtons();
}
//---------------------------------------------------------------------------


void TSetupScreen::adjustGui(int type, int color, int smaler, int larger, int up, int left, int right,
                   int down, int reset, int outlineless, int outlinemore, int outlinecolor, int active)
{
     FontTypeButton->Visible = (type==1);
     FontColorButton->Visible = (color==1);
     FontReduceButton->Visible = (smaler==1);
     FontEnlargeButton->Visible = (larger==1);
     PositionUpButton->Visible = (up==1);
     PostionLeftButton->Visible = (left==1);
     PositionRightButton->Visible = (right==1);
     PositionDownButton->Visible = (down==1);
     PositionResetButton->Visible = (reset==1);
     OutlineLessButton->Visible = (outlineless==1);
     OutlineMoreButton->Visible = (outlinemore==1);
     OutlineColorButton->Visible = (outlinecolor==1);
     ActiveCheckBox->Visible = (active==1);
}


void __fastcall TSetupScreen::FormDeactivate(TObject *Sender)
{
      MainForm->BlockFocus = false;
      Hide();
}
//---------------------------------------------------------------------------

void __fastcall TSetupScreen::FormMouseWheelDown(TObject *Sender,
      TShiftState Shift, TPoint &MousePos, bool &Handled)
{
  if      (PositionUpButton->Focused())     PositionDownButton->SetFocus();
  else if (PositionDownButton->Focused())   /*nothing*/;
  else if (PostionLeftButton->Focused())    PositionRightButton->SetFocus();
  else if (PositionRightButton->Focused())  /*nothing*/;
  else if (LineDistLessButton->Focused())   LineDistMoreButton->SetFocus();
  else if (LineDistMoreButton->Focused())   /*nothing*/;
  else if (LineCountLessButton->Focused())  LineCountMoreButton->SetFocus();
  else if (LineCountMoreButton->Focused())  /*nothing*/;
  else if (FontReduceButton->Focused())     FontEnlargeButton->SetFocus();
  else if (FontEnlargeButton->Focused())    /*nothing*/;
  else return;
  numberOfWheelMoves++;
  if (numberOfWheelMoves>3)
  {
    numberOfWheelMoves =0;
    keybd_event(0x20, 0, 0, 0);      // simulate space bar is pressed
    keybd_event(0x20, 0, KEYEVENTF_KEYUP, 0);
  }
        
}
//---------------------------------------------------------------------------


void __fastcall TSetupScreen::FormMouseWheelUp(TObject *Sender,
      TShiftState Shift, TPoint &MousePos, bool &Handled)
{
  if      (PositionUpButton->Focused())     /*nothing*/;
  else if (PositionDownButton->Focused())   PositionUpButton->SetFocus();
  else if (PostionLeftButton->Focused())    /*nothing*/;
  else if (PositionRightButton->Focused())  PostionLeftButton->SetFocus();
  else if (LineDistLessButton->Focused())   /*nothing*/;
  else if (LineDistMoreButton->Focused())   LineDistLessButton->SetFocus();
  else if (LineCountLessButton->Focused())  /*nothing*/;
  else if (LineCountMoreButton->Focused())  LineCountLessButton->SetFocus();
  else if (FontReduceButton->Focused())     /*nothing*/;
  else if (FontEnlargeButton->Focused())    FontReduceButton->SetFocus();
  else return;
  numberOfWheelMoves++;
  if (numberOfWheelMoves>3)
  {
    numberOfWheelMoves =0;
    keybd_event(0x20, 0, 0, 0);      // simulate space bar is pressed
    keybd_event(0x20, 0, KEYEVENTF_KEYUP, 0);
  }
        
        
}
//---------------------------------------------------------------------------

void __fastcall TSetupScreen::FormActivate(TObject *Sender)
{
      MainForm->BlockFocus = true;
}
//---------------------------------------------------------------------------


void __fastcall TSetupScreen::SecondBlockOneLineCheckBoxClick(
      TObject *Sender)
{
    if (SecondBlockOneLineCheckBox->Checked)
          MainForm->ProcessCommands("ChangeSetting_TextBlockSize_One");
    else  MainForm->ProcessCommands("ChangeSetting_TextBlockSize_Multiple");

}
//---------------------------------------------------------------------------

