/*
Open source not for commercial deployment
*/
//---------------------------------------------------------------------------


#pragma hdrstop

#include "SpeedBar.h"
#include "GlobalUnit.h"


//---------------------------------------------------------------------------

void SpeedBar::init(TWinControl * pParent, String programDir)
{
     parent = pParent;
     ProgramDir = programDir;
}

void SpeedBar::CleanUpToolBar()
{
         delete SpeedButtonsIconList;
         SpeedButtonsIconList = new TImageList(parent);
         delete ToolBar;  //this will also automicily delete all buttons.
         ToolBar = new TToolBar(parent);
         ToolBar->Parent = parent;
         ToolBar->Color = clBtnShadow;
         ToolBar->ShowHint = true;
         SpeedButtonCount = 0;
         IconCount=0;
}


void SpeedBar::addSpeedButton(String s)
{
   if (s=="ClearAll")
   {
         CleanUpToolBar();
         return;
   }
   else if (ToolBar == NULL)
   {
        CleanUpToolBar();
   }

   if (SpeedButtonCount == MAX_SPEEDBUTTONS)
   {
        MessageDlg("Maximum number of speed buttons reached.", mtInformation, TMsgDlgButtons()<<mbOK , 0);
        return;
   }
   String PictureName = getUntil(s,"_");
   s =   getAfter(s,"_");
   String ButtonHint = getUntil(s,"_");
   String Commands = getAfter(s,"_");
   Commands = replace(Commands, "|", ",");

   SpeedButtonCommand[IconCount] =  Commands;
   ToolButton[SpeedButtonCount] = new TToolButton(ToolBar);
   ToolButton[SpeedButtonCount]->Parent = ToolBar;
   ToolButton[SpeedButtonCount]->ImageIndex = IconCount;
   ToolButton[SpeedButtonCount]->OnClick =  &ToolButtonClick;
   ToolButton[SpeedButtonCount]->Hint = ButtonHint;
   TIcon *Icone = new TIcon();

   if (PictureName=="Separator")
   {
        ToolButton[SpeedButtonCount]->Style = tbsSeparator;
        ToolButton[SpeedButtonCount]->Width = 7;
   }
   else
   {
        Icone->LoadFromFile(ProgramDir+"Icons\\"+PictureName);
        IconCount++;
   }
   SpeedButtonsIconList->AddIcon(Icone);
   ToolBar->Images=SpeedButtonsIconList;
   delete Icone;
   SpeedButtonCount++;
}

void __fastcall SpeedBar::ToolButtonClick(TObject *Sender)
{
    MainForm->recurcingDepth =0;
    MainForm->ProcessCommands( SpeedButtonCommand[((TToolButton*)Sender)->ImageIndex] );
}


#pragma package(smart_init)
