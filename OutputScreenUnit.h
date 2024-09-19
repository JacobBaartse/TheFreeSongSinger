//---------------------------------------------------------------------------

#ifndef OutputScreenUnitH
#define OutputScreenUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ScreenSettingsUnit.h"
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <Graphics.hpp>
#include <iostream.h>
#include <fstream.h>
#include "utils.h"
#include <Dialogs.hpp>
#include <Menus.hpp>


//---------------------------------------------------------------------------
class TOutputScreen : public TForm
{
__published:	// IDE-managed Components
        TTimer *Timer1;
        TImage *Image1;
        TImage *Image2;
        TLabel *LabelMoveMessage;
        TImage *ImageScratchPad;
        TPopupMenu *PopupMenu1;
        TMenuItem *Exit1;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Exit1Click(TObject *Sender);

private:	// User declarations
        __int16 BrightnessAdjust;
        double ContrastAdjust;
        String BlinkMessage;
        String SlaveBlinkMessage;

public:		// User declarations
        bool LateRefesch;
        bool ouptuScreenUpdated;
        int leftMargin;
        int textReduction;
        bool calcMarginTextReduction;
        bool temporyHideLinePointer;
        int blinkcounter;
        TJPEGImage *JPEGImage;
        Graphics::TBitmap *BMPImage;
        TImage *notActiveImage;
        String iniFileName;

        ScreenSettings curScreenSettings;
        PictureAttribuut curPictureAttrib;

        __fastcall TOutputScreen(TComponent* Owner);
        void FreezeSize();
        void LoadPiture();
        void ResizePictureAndLoad();

        int CalculateLineYPosition(int ScreenLine);
        TPoint printLine(int songLine, int screenLine, bool showOldColor ,bool suppresOutline);
        TPoint printLineXY(String PrintText, int x, int yPos, bool showOldColor ,bool suppresOutline, int TextType, bool wrap, bool doTextReduction);
        TPoint printLineXYOutlineOrText(String PrintText, int x, int yPos, bool showOldColor ,bool suppresOutline, int TextType, bool wrap, bool doTextReduction);
        void writeSongTextLines();
        void refreshScreen();
        void setLeftMarginAndReduction();
        void ShowProgressBar();
        String UpdateLineIndicator(bool LinePointerOn);
        void Init(String BaseDir);
        void Recover();
        void setBlinkMessage(String s);
        void LoadSong(String filename);
        void setBrightnessAdjust(String s);
        void setContrastAdjust(String s);
        void SlaveMessage(String s);
        void SendToSlaves();
        void ReceiveAsSlave(String s);
        void SetText(const String s);


};
//---------------------------------------------------------------------------
extern PACKAGE TOutputScreen *OutputScreen;
//---------------------------------------------------------------------------
#endif
