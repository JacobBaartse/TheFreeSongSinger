//---------------------------------------------------------------------------

#ifndef CommandTranslationUnitH
#define CommandTranslationUnitH
#define MAX_TRANSLATION_COMMANDS 2048

#include <iostream.h>
#include <fstream.h>
#include <Classes.hpp>
#include <Dialogs.hpp>
#include "Utils.h"


class CommandTranslation
{
private:	// User declarations
public:		// User declarations

    String Command[MAX_TRANSLATION_COMMANDS];
    String Translation[MAX_TRANSLATION_COMMANDS];

    void AddTranslation(String s);
    CommandTranslation();
    String translate(String s);


    int count;




};


//---------------------------------------------------------------------------
#endif
