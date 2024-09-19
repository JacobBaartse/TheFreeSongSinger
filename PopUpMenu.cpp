/*
Open source not for commercial deployment
*/
//---------------------------------------------------------------------------


#pragma hdrstop

#include "PopUpMenu.h"
#include "GlobalUnit.h"

//---------------------------------------------------------------------------
void PopUpMenu::init(TComponent * pParent)
{
     parent = pParent;
}

void __fastcall PopUpMenu::MenuItemClick(TObject *Sender)
{
    MainForm->recurcingDepth =0;
    MainForm->ProcessCommands( ((TMenuItem*)Sender)->Hint );
}

void PopUpMenu::CleanUpMenu()
{
         delete PopUpMenu;  //this will also automicily delete all menuItems.
         PopUpMenu = new TPopupMenu(parent);
         String t = parent->ClassName();
         if (t == "Picture") ((Picture *)parent)->PopupMenu = PopUpMenu;
         if (t == "TPanel") ((TPanel *)parent)->PopupMenu = PopUpMenu;

         MenuItemCount = 0;
}

void PopUpMenu::addMenuItem(String s)  // label_command|command
{
   if (s=="ClearAll")
   {
         CleanUpMenu();
         return;
   }
   else if (PopUpMenu == NULL)
   {
        CleanUpMenu();
   }

   if (MenuItemCount == MAX_MENU_ITEMS)
   {
        MessageDlg("Maximum number of menu items reached.", mtInformation, TMsgDlgButtons()<<mbOK , 0);
        return;
   }
   String Commands = getAfter(s,"_");
   Commands = replace(Commands, "|", ",");

   MenuItems[MenuItemCount] = new TMenuItem(PopUpMenu);
   MenuItems[MenuItemCount]->Caption =  getUntil(s,"_");
   MenuItems[MenuItemCount]->OnClick =  &MenuItemClick;
   MenuItems[MenuItemCount]->Hint =  Commands;

   PopUpMenu->Items->Add(MenuItems[MenuItemCount]);

   MenuItemCount++;
}

#pragma package(smart_init)
