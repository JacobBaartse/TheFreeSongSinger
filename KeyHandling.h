//---------------------------------------------------------------------------

#ifndef KeyHandlingH
#define KeyHandlingH

#include <iostream.h>
#include <fstream.h>
#include <Classes.hpp>
#include <Dialogs.hpp>
#include "Utils.h"
#define NUMBER_OF_KEYS 2048
class KeyHandling
{
private:	// User declarations
public:		// User declarations

    KeyHandling();
    bool shiftDown;
    bool controlDown;
    bool altDown;
    String inputData;

    String ProcessKeyDown(WORD &Key, TShiftState Shift);
    String ProcessKeyDown(WORD Key);
    void setBaseDir(String BaseDir);

    void ProcessKeyUp(WORD &Key, TShiftState Shift);
    void LoadKeySettingsFile(String FileName);
    String KeyCommand[NUMBER_OF_KEYS];
    bool showKey;




};

//---------------------------------------------------------------------------
#endif
