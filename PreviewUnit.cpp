//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PreviewUnit.h"
#include "OutputScreenUnit.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPreview *Preview;
//---------------------------------------------------------------------------
__fastcall TPreview::TPreview(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TPreview::Timer1Timer(TObject *Sender)
{
    if (!OutputScreen->ouptuScreenUpdated) return;
    TRect pictureSize = TRect(0,0,Image1->Width, Image1->Height);

    TImage *notActiveImage;
    if (Image1->Visible==true) notActiveImage =Image2;
    else                       notActiveImage= Image1;

    TImage *activeImage;
    if (OutputScreen->Image1->Visible==true) activeImage =OutputScreen->Image1;
    else                                     activeImage= OutputScreen->Image2;

    notActiveImage->Canvas->StretchDraw(pictureSize, activeImage->Picture->Graphic);
    if (Image1->Visible==true)
    {
                Image2->Visible=true;
                Image1->Visible=false;
    }
    else
    {
                Image1->Visible=true;
                Image2->Visible=false;
    }

}
//---------------------------------------------------------------------------


void __fastcall TPreview::FormCreate(TObject *Sender)
{
        DoubleBuffered = true;
}
//---------------------------------------------------------------------------

