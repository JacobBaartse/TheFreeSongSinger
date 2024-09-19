//---------------------------------------------------------------------------

#ifndef TextAttribuutUnitH
#define TextAttribuutUnitH

#include <Graphics.hpp>
#include "GlobalUnit.h"


class TextAttribuut
{
private:	// User declarations
public:		// User declarations
    TextAttribuut();
    void set(String s);
    void setFont(TFont * t);
    void setColor(TColor c);
    void setOutlineColor(TColor c);


    bool Active;
    TFont * Font;
    int Xpos;
    int Ypos;
    int OutlineThickness;
    TColor OutlineColor;
    int RightMargin;


};
//---------------------------------------------------------------------------
#endif
