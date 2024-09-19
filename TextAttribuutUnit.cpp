/*
Open source not for commercial deployment
*/
//---------------------------------------------------------------------------


#pragma hdrstop

#include "TextAttribuutUnit.h"
#include "OutputScreenUnit.h"

TextAttribuut::TextAttribuut()
{
        Active          = true;
        Font            = new TFont();
        Font->Color     = clYellow;
        Font->Size      = 12;
        Xpos            = 0;
        Ypos            = 0;
        OutlineThickness= 2;
        OutlineColor    = clBlack;
        RightMargin     = 10;

}
//---------------------------------------------------------------------------

void TextAttribuut::set(String s)
{
    OutputScreen->calcMarginTextReduction = true;

    if (s==">")             Xpos++;
    else if (s=="<")        Xpos--;
    else if (s=="^")        Ypos--;
    else if (s=="v")        Ypos++;
    else if (s=="><")       {Xpos=0; Ypos=0;}
    else if (s=="Active_On") Active=true;
    else if (s=="Active_Off") Active=false;
    else if (s=="Toggle")    Active=!Active;
    else if (s=="Color")
         {
             MainForm->ColorDialog->Color = Font->Color;
             if (MainForm->ColorDialog->Execute())
                 Font->Color = MainForm->ColorDialog->Color;
         }
    else if (s=="FontType")
         {
             MainForm->FontDialog->Font = Font;
             if (MainForm->FontDialog->Execute())
                 Font = MainForm->FontDialog->Font;
         }
    else if (s=="Reduce")  { if (Font->Size > 8) Font->Size--; }
    else if (s=="Enlarge") { if (Font->Size < 72) Font->Size++; }
    else if (s=="Outline_Color")
         {
             MainForm->ColorDialog->Color = OutlineColor;
             if (MainForm->ColorDialog->Execute())
                 OutlineColor = MainForm->ColorDialog->Color;
         }
    else if (s=="Outline_Less") {  if (OutlineThickness > 0) OutlineThickness--; }
    else if (s=="Outline_More") {  if (OutlineThickness < 3) OutlineThickness++; }
}

void TextAttribuut::setFont(TFont * t)
{
     Font->Name = t->Name;
     Font->Style = t->Style;
}

void TextAttribuut::setColor(TColor c)
{
     Font->Color= c;
}

void TextAttribuut::setOutlineColor(TColor c)
{
     OutlineColor= c;
}



#pragma package(smart_init)
