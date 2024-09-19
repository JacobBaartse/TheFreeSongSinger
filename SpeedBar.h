//---------------------------------------------------------------------------

#ifndef SpeedBarH
#define SpeedBarH

#include <ComCtrls.hpp>
#include "utils.h"

#define MAX_SPEEDBUTTONS 50

//---------------------------------------------------------------------------
class SpeedBar
{
private:	// User declarations
        TToolBar *ToolBar;
public:		// User declarations

        void init(TWinControl * pParent, String programDir);
        void __fastcall ToolButtonClick(TObject *Sender);
        void addSpeedButton(String s);
        void CleanUpToolBar();

        String SpeedButtonCommand[MAX_SPEEDBUTTONS];
        TToolButton * ToolButton[MAX_SPEEDBUTTONS];

        int SpeedButtonCount;
        int IconCount;
        TImageList *SpeedButtonsIconList;
        TWinControl * parent;
        String ProgramDir;

};

//---------------------------------------------------------------------------
#endif