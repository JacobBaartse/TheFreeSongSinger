//---------------------------------------------------------------------------

#ifndef EditSongH
#define EditSongH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include "GlobalUnit.h"
#include <ComCtrls.hpp>
#include <Dialogs.hpp>

//---------------------------------------------------------------------------
class TEditSongForm : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu;
        TMenuItem *File1;
        TMenuItem *New1;
        TMenuItem *OPen1;
        TMenuItem *Saveas1;
        TMenuItem *Exit1;
        TLabel *LabelToneHeight;
        TEdit *EditToneHeight;
        TLabel *LabelSongTitle;
        TEdit *EditSongTitle;
        TMenuItem *Save1;
        TMemo *MemoSongText;
        TPanel *PanelBottom;
        TLabel *LabelAllowedTags;
        TEdit *EditCopyRight;
        TPanel *PanelTop;
        TLabel *LabelCopyRight;
        TSaveDialog *SaveDialog1;
        TStatusBar *StatusBar1;
        TOpenDialog *OpenDialog1;
        TLabel *LabelSongText;
        TPanel *PanelMiddle;
        TFontDialog *FontDialog1;
        TMenuItem *Font1;
        TMenuItem *Selectfont1;
        TMenuItem *CourierNew1;
        TMenuItem *Tags1;
        TMenuItem *Addacc1;
        TMenuItem *Removeacc1;
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall Saveas1Click(TObject *Sender);
        void __fastcall OPen1Click(TObject *Sender);
        void __fastcall New1Click(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall Save1Click(TObject *Sender);
        void __fastcall Exit1Click(TObject *Sender);
        void __fastcall EditChange(TObject *Sender);
        void __fastcall FormHide(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall Selectfont1Click(TObject *Sender);
        void __fastcall CourierNew1Click(TObject *Sender);
        void __fastcall Removeacc1Click(TObject *Sender);
        void __fastcall Addacc1Click(TObject *Sender);
        void __fastcall MemoSongTextDblClick(TObject *Sender);
        void __fastcall FormDeactivate(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TEditSongForm(TComponent* Owner);
        void SaveSong(String fileName);
        void LoadSongFromFile(String SongFileName);
        void SaveSongAs();



        String fullSongText[1024];
        int fullSongLength;
        String OpenedFileName;
        bool changed;
        int fontScale;
        bool FontResize;

};
//---------------------------------------------------------------------------
extern PACKAGE TEditSongForm *EditSongForm;
//---------------------------------------------------------------------------
#endif
