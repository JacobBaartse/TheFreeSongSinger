//---------------------------------------------------------------------------

#ifndef SearchH
#define SearchH
#include <Classes.hpp>
#include "string.h"
#include "SongDataUnit.h"

#define         MAX_SEARCH_WORDS 30


//---------------------------------------------------------------------------
void findText(String searchString);
void searchInit(String s);
void createSearchIndex();
String converToUpperOnly(String s);


//---------------------------------------------------------------------------
#endif
