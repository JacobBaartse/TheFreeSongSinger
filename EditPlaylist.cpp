/*
Open source not for commercial deployment
*/
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "EditPlaylist.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormEditPlaylist *FormEditPlaylist;
//---------------------------------------------------------------------------
__fastcall TFormEditPlaylist::TFormEditPlaylist(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormEditPlaylist::FormActivate(TObject *Sender)
{
      Top = MainForm->Top + MainForm->PanelPlayList->Top + 20;
      Left = MainForm->Left + MainForm->PanelPlayList->Left;
      Width = MainForm->PanelPlayList->Width + 5;
      Height = MainForm->PanelPlayList->Height + 5;
      PlayListEdit->Clear();
      PlayListEdit->Lines = MainForm->PlayList->Items;
      MainForm->BlockFocus = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormEditPlaylist::FormDeactivate(TObject *Sender)
{
     MainForm->PlayList->Clear();
     MainForm->PlayList->Items =  PlayListEdit->Lines;
     MainForm->BlockFocus = false;
     Hide();
}
//---------------------------------------------------------------------------
