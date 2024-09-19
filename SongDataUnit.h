//---------------------------------------------------------------------------

#ifndef SongDataUnitH
#define SongDataUnitH


#include <Classes.hpp>
#include <iostream.h>
#include <fstream.h>
#include "Utils.h"
#include "Crypto.h" 

#define MAX_SONG_LENGTH 1024

class SongData
{
private:	// User declarations
    int songLength;
public:		// User declarations
    SongData();
    bool LoadSong(String FileName);
    void SetBaseDir(String pBaseDir);
    String getFileName(String book);
    void getSpecificVerses(String verses);
    String Decrypt(String lineBuffer);
    String getBeginOfText();
    void SendToSlaves();
    void ReceiveAsSlave(String s);
    void copySongText(String startVers, String endVers, String versSeparator);
    int FindCoupletLinenr(String CoupletNumber, bool untilVerse);
    int getSongLength();
    void  setSongLength(int i);
    void SetText(String s);
    void Transpose(String s);
    void TextToNotepad();


    String text[MAX_SONG_LENGTH];

    String textCopy[MAX_SONG_LENGTH];
    int songLengthCopy;

    String copyRightText;
    String ToneHeightText;
    String fileName;
    String shortFileNameAndVers;
    String TitleText;
    bool doDecrypt;
    bool previewSong;
    bool protectedSong;

    static String Password;
    String Tones;
};
String  SongData::Password;

//---------------------------------------------------------------------------
#endif
