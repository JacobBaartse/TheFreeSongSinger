//---------------------------------------------------------------------------

#ifndef PreviewUnitH
#define PreviewUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TPreview : public TForm
{
__published:	// IDE-managed Components
        TImage *Image1;
        TTimer *Timer1;
        TImage *Image2;
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TPreview(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TPreview *Preview;
//---------------------------------------------------------------------------
#endif
