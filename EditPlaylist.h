//---------------------------------------------------------------------------

#ifndef EditPlaylistH
#define EditPlaylistH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "GlobalUnit.h"
//---------------------------------------------------------------------------
class TFormEditPlaylist : public TForm
{
__published:	// IDE-managed Components
        TMemo *PlayListEdit;
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall FormDeactivate(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormEditPlaylist(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormEditPlaylist *FormEditPlaylist;
//---------------------------------------------------------------------------
#endif
