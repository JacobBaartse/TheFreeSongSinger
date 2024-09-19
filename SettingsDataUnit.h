//---------------------------------------------------------------------------

#ifndef SettingsDataUnitH
#define SettingsDataUnitH

#include <Graphics.hpp>
#include <iostream.h>
#include <fstream.h>

#include "TextAttribuutUnit.h"
#include "PictureAttribuutUnit.h"
#include "utils.h"

//---------------------------------------------------------------------------
class SettingsData
{
private:	// User declarations
public:		// User declarations
    SettingsData();
    bool LoadFile(String fileName);
    void LoadSettingsFile(ifstream * settingsFile);
    void SetBaseDir(String pBaseDir, bool pPreview);
    bool setBackgroud(String s);
    void setPause(String s);
    void setBlack(String s);
    void setTextBlock(String s);
    void setTextBlockSize(String s);
    void changeSetting(String s);
    void setLineDistance(String s);
    void setLineCount(String s);
    void doFile(String s);

    String settingToString(int itemIndex, int itemPart, bool value);
    String settingToString(int itemIndex, int itemPart, int value);
    String settingToString(int itemIndex, int itemPart, double value);
    String settingToString(int itemIndex, int itemPart, String value);
    String getSettings();


    void storeScreenSettings(String fileName);
    int getAttribuutIndex(String s);
    int getPictureIndex(String s);
    bool getTransparent(String s);
    bool getPitureActive(String s);
    bool getTextAttribuutActive(String s);
    void SendToSlaves();
    void ReceiveAsSlave(String s);

    int LineDistance;
    int NrOfLines;
    bool OneSongblock;
    bool secondBlockBig;
    String LoadedFile;
    String LoadedFileShort;
    bool LeftAllign;

    TextAttribuut NormalText,                               OldText ,
                  Heading2,                                 Heading3,
                  Heading4,                                 Translation,
                  ToneHeight,                               SongTitle,
                  BlinkMessage,                             LinePointer,
                  CurrentSong,                              CopyRight,
                  PauseBlinkMessage,                        AllText,
                  SongText;


    PictureAttribuut BackgroundPicture,
                     PausePicture,
                     ShowPicture,
                     BlackPicture;


    enum elementName {ALL_TEXT, SONG_TEXT,

                      NORMAL_TEXT, OLD_COLOR, HEADING2, HEADING3, HEADING4, TRANSLATION, LINE_POINTER,

                      TONE_HEIGTH, COPY_RIGHT, BLINK_MESSAGE, TITLE_TEXT,
                      PAUSE_BLINK_MESSAGE, CURRENT_SONG, NrOfScreenElements};
    TextAttribuut *ScreenElement[NrOfScreenElements];

    enum Mode { Mode_SONG, Mode_PICTURE, Mode_PAUSE, Mode_BLACK, NrOfScreenModes} curMode, oldMode;

    PictureAttribuut * PictureSettings[NrOfScreenModes];
    bool preview;


};
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#endif
