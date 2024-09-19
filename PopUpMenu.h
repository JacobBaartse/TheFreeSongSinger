//---------------------------------------------------------------------------

#ifndef PopUpMenuH
#define PopUpMenuH

#include <ComCtrls.hpp>
#include "utils.h"


#define MAX_MENU_ITEMS 20

//---------------------------------------------------------------------------
class PopUpMenu
{
private:	// User declarations
public:		// User declarations
        TPopupMenu * PopUpMenu;

        void init(TComponent* pParent);
        void __fastcall MenuItemClick(TObject* Sender);
        void addMenuItem(String s);
        void CleanUpMenu();

        TMenuItem* MenuItems[MAX_MENU_ITEMS];

        int MenuItemCount;
        TComponent* parent;
        String ProgramDir;

};

//---------------------------------------------------------------------------
#endif
