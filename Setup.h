//---------------------------------------------------------------------------

#ifndef SetupH
#define SetupH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "OutputScreenUnit.h"
#include "GlobalUnit.h"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ToolWin.hpp>
#include <Buttons.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TSetupScreen : public TForm
{
__published:	// IDE-managed Components
        TComboBox *ElementSel;
        TStatusBar *StatusBar;
        TPanel *Panel1;
        TGroupBox *FontGroupBox;
        TButton *FontTypeButton;
        TButton *FontColorButton;
        TButton *FontEnlargeButton;
        TButton *FontReduceButton;
        TGroupBox *PositionGroupBox;
        TGroupBox *OutlineGroupBox;
        TCheckBox *LeftAlignCheckBox;
        TButton *PositionUpButton;
        TButton *PostionLeftButton;
        TButton *PositionResetButton;
        TButton *PositionRightButton;
        TButton *PositionDownButton;
        TPanel *Panel2;
        TComboBox *PictureSel;
        TButton *PictureSelectButton;
        TToolBar *ToolBar;
        TToolButton *ToolButton1;
        TToolButton *ToolButton2;
        TToolButton *ToolButton3;
        TToolButton *ToolButton4;
        TToolButton *ToolButton5;
        TToolButton *ToolButton6;
        TToolButton *ToolButton7;
        TToolButton *ToolButton8;
        TCheckBox *ActiveCheckBox;
        TButton *OutlineLessButton;
        TButton *OutlineMoreButton;
        TButton *OutlineColorButton;
        TGroupBox *LineDistGroupBox;
        TButton *LineDistMoreButton;
        TButton *LineDistLessButton;
        TGroupBox *LineCountGroupBox;
        TButton *LineCountMoreButton;
        TButton *LineCountLessButton;
        TButton *ButtonBackgroundColor;
        TCheckBox *MoreTextBlocksCheck;
        TPanel *Panel3;
        TCheckBox *CheckBoxTransparent;
        TCheckBox *CheckBoxPicture;
        TMainMenu *MainMenu1;
        TMenuItem *File1;
        TMenuItem *Open1;
        TMenuItem *Save1;
        TMenuItem *Extra1;
        TMenuItem *Sampletext1;
        TMenuItem *Saveas1;
        TPanel *Panel4;
        TCheckBox *SecondBlockOneLineCheckBox;
        void __fastcall FontTypeButtonClick(TObject *Sender);
        void __fastcall PositionUpButtonClick(TObject *Sender);
        void __fastcall FontColorButtonClick(TObject *Sender);
        void __fastcall FontReduceButtonClick(TObject *Sender);
        void __fastcall FontEnlargeButtonClick(TObject *Sender);
        void __fastcall LeftAlignCheckBoxClick(TObject *Sender);
        void __fastcall ToolButton2Click(TObject *Sender);
        void __fastcall ToolButton3Click(TObject *Sender);
        void __fastcall ToolButton4Click(TObject *Sender);
        void __fastcall ToolButton6Click(TObject *Sender);
        void __fastcall ToolButton7Click(TObject *Sender);
        void __fastcall ToolButton8Click(TObject *Sender);
        void __fastcall PictureSelectButtonClick(TObject *Sender);
        void __fastcall CheckBoxPictureClick(TObject *Sender);
        void __fastcall CheckBoxTransparentClick(TObject *Sender);
        void __fastcall ActiveCheckBoxClick(TObject *Sender);
        void __fastcall Sampletext1Click(TObject *Sender);
        void __fastcall MoreTextBlocksCheckClick(TObject *Sender);
        void __fastcall OutlineLessButtonClick(TObject *Sender);
        void __fastcall OutlineMoreButtonClick(TObject *Sender);
        void __fastcall OutlineColorButtonClick(TObject *Sender);
        void __fastcall ButtonBackgroundColorClick(TObject *Sender);
        void __fastcall LineDistLessButtonClick(TObject *Sender);
        void __fastcall LineDistMoreButtonClick(TObject *Sender);
        void __fastcall LineCountLessButtonClick(TObject *Sender);
        void __fastcall LineCountMoreButtonClick(TObject *Sender);
        void __fastcall Open1Click(TObject *Sender);
        void __fastcall Save1Click(TObject *Sender);
        void __fastcall Saveas1Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall ElementSelChange(TObject *Sender);
        void __fastcall PictureSelChange(TObject *Sender);
        void __fastcall FormDeactivate(TObject *Sender);
        void __fastcall FormMouseWheelDown(TObject *Sender,
          TShiftState Shift, TPoint &MousePos, bool &Handled);
        void __fastcall FormMouseWheelUp(TObject *Sender,
          TShiftState Shift, TPoint &MousePos, bool &Handled);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall SecondBlockOneLineCheckBoxClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TSetupScreen(TComponent* Owner);
        
        void UpdateButtons();

        void Init(String s);
        void adjustGui(int type, int color, int smaler, int larger, int up, int left, int right, int down, int reset, int outlineless, int outlinemore, int outlinecolor, int active);
        void UpdateFullGui();

        String NameList[17];
        String PictureList[2];
        TImageList *SpeedButtonsIconList;
        int numberOfWheelMoves;
};
//---------------------------------------------------------------------------
extern PACKAGE TSetupScreen *SetupScreen;
//---------------------------------------------------------------------------
#endif
