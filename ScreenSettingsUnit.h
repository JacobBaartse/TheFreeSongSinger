//---------------------------------------------------------------------------

#ifndef ScreenSettingsUnitH
#define ScreenSettingsUnitH
#include <Controls.hpp>
#include "SettingsDataUnit.h"
#include "SongDataUnit.h"



class ScreenSettings
{
private:	// User declarations
public:		// User declarations

        int CurLine;
        int startLine;
        int CurLinePointer;

        SettingsData CurSettings;
        SettingsData curPreviewSettings; // as a work-around put over here, should normaly be put in the globalUnit.h but this does not compile for some odd reason.
        SongData CurSongData;

        ScreenSettings();
        bool LoadSong(String filename);
        void toNextTextBlock();
        void toPrevTextBlock();
        void setOutdateline(String s);
        void ToBeginSong();
        void ToEndSong();
        void scrollOneLine(String s);
        void SendToSlaves();
        void ReceiveAsSlave(String s);
        void gotoStrofe(String s);
        void SetText(const String s);


};

//---------------------------------------------------------------------------
#endif
