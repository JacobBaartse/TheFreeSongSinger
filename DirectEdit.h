//---------------------------------------------------------------------------

#ifndef DirectEditH
#define DirectEditH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "GlobalUnit.h"
#include "SpeedBar.h"
#include "Utils.h"

//---------------------------------------------------------------------------
class TDirectEditForm : public TForm
{
__published:	// IDE-managed Components
        TEdit *TitleEdit;
        TLabel *TitleLabel;
        TMemo *TextMemo;
        TComboBox *LineCountComboBox;
        TLabel *LineCountLabel;
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall TextMemoKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall TextMemoKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormDeactivate(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TDirectEditForm(TComponent* Owner);
        void ShowOnScreen();
        void Process_Command(String s);
        void SaveAs(String s);
        void Open(String s);



        bool shiftDown;
        bool controlDown;
        bool altDown;
        SpeedBar MainSpeedBar;
        String LoadedFile;
};
//---------------------------------------------------------------------------
extern PACKAGE TDirectEditForm *DirectEditForm;
//---------------------------------------------------------------------------
#endif
