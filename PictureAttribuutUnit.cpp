/*
Open source not for commercial deployment
*/
//---------------------------------------------------------------------------


#pragma hdrstop

#include "PictureAttribuutUnit.h"

PictureAttribuut::PictureAttribuut()
{
        FileName        = "";
        Brightness      = 0;
        Contrast        = 1;
        BackGroundColor = clBlack;
        Transparent     = false;
        Active          = true;
}

bool PictureAttribuut::operator==(const PictureAttribuut pa)
{
        if (FileName   != pa.FileName)   return false;
        if (Brightness != pa.Brightness) return false;
        if (Contrast   != pa.Contrast)   return false;
        if (Active     != pa.Active)     return false;
        if (Transparent!= pa.Transparent)return false;
        if (BackGroundColor!=pa.BackGroundColor) return false;
        return true;
}

bool PictureAttribuut::operator!=(const PictureAttribuut pa)
{
        return !(operator==(pa));
}

void PictureAttribuut::SetBaseDir(String s)
{
     BaseDir = s.UpperCase();
}

void PictureAttribuut::setTranparent(bool pb)
{
        Transparent = pb;
        if (pb) BackGroundColor = (TColor) 0x80807F;
}


void PictureAttribuut::openFile(String s)
{
     if (s.Length()==0) s = BaseDir;
     MainForm->BackgroundImageDialog->FileName = BaseDir+"*.jpg";
     if(MainForm->BackgroundImageDialog->Execute())
     {
           FileName = MainForm->BackgroundImageDialog->FileName;
           if (FileName.UpperCase().Pos(BaseDir)==1)
              FileName = getAfter(FileName,BaseDir);

     };
}

void PictureAttribuut::changeSetting(String s)
{
     if (s.Pos("Contrast_")==1)        Contrast = calcContrast(Contrast, getAfter(s,"_"));
     else if (s.Pos("Brightness_")==1) Brightness = calcBrightness(Brightness,getAfter(s,"_"));
     else if (s.Pos("OpenFile_")==1)   openFile(getAfter(s,"_"));
     else if (s=="Active_On")          Active=true;
     else if (s=="Active_Off")         Active=false;
     else if (s=="Transparent_On")     Transparent=true;
     else if (s=="Transparent_Off")    Transparent=false;
     else if (s=="Transparent_Toggle")    Transparent=!Transparent;
     else if (s=="Color")
         {
             MainForm->ColorDialog->Color = BackGroundColor;
             if (MainForm->ColorDialog->Execute())
                 BackGroundColor = MainForm->ColorDialog->Color;
         }

}

//---------------------------------------------------------------------------

#pragma package(smart_init)
