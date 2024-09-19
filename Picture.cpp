/*
Open source not for commercial deployment
*/
//---------------------------------------------------------------------------


#pragma hdrstop

#include "Picture.h"
#include "GlobalUnit.h"
#include "OutputScreenUnit.h"

void Picture::staticInit(String dir)
{
     Picture::ImageDir = dir + "Data\\background\\";
     Picture::ImageDir = Picture::ImageDir.UpperCase();
}

Picture::Picture(TWinControl* Owner, int left, int top, int width, int height, String clickCommand, String dblClickCommand):
TImage(Owner)
{
     Parent = Owner;
     Left = left;
     Top = top;
     Width = width;
     Height = height;
     OnClick = &ImageClick;
     OnDblClick = &ImageDblClick;
     OnMouseDown = &ImageMouseDown;

     OnClickCommand = clickCommand;
     OnDubbleClickCommand = dblClickCommand;
     Clear();
}

void Picture::Clear()
{
     Canvas->Brush->Color =  OutputScreen->curScreenSettings.CurSettings.BackgroundPicture.BackGroundColor;
     Canvas->FillRect(TRect(0,0,Width,Height));
     imageName = "";
}

bool Picture::LoadPictureFromFile( String s)
{
     Clear();

     String FileName = expandPicutureFileName(s);

     if (FileName.Length()==0) return false;

     // first check if the picture file exist.
     ifstream pictureFile(FileName.c_str());
     if (!pictureFile.is_open()) return false;
     pictureFile.close();

     setImageName(s);

     bool BmpFile = FileName.UpperCase().Pos(".BMP")+3 == FileName.Length();

     JPEGImage = new TJPEGImage;
     BMPImage = new Graphics::TBitmap();
     if (BmpFile)
     {
          // bmp file can just be loaded.
          BMPImage->LoadFromFile(FileName);
     }
     else
     {
          //convert the JPG file to a BMP
          JPEGImage->LoadFromFile(FileName);
          BMPImage->Assign ( JPEGImage );
     }

     //calculate the resize factor to let the piture fill the screen.
     double WidthOriginal = BMPImage->Width;
     double HeightOriginal = BMPImage->Height;
     double fraction;
     double ymargin=0;
     double xmargin=0;
     bool smallEdges=false;
     if ( WidthOriginal/HeightOriginal > Width/Height)
     {
          fraction =  WidthOriginal /  Width;
          ymargin =  (Height - HeightOriginal/fraction  )/2;
          if (ymargin <  Height/30) smallEdges=true;
     }
     else
     {
          fraction =  HeightOriginal / Height;
          xmargin = ( Width - WidthOriginal/fraction) /2;
          if (xmargin <  Width/30) smallEdges=true;
     }

     TRect maxPictureSize;
     if (smallEdges)
           maxPictureSize = TRect(0,0,Width, Height );  // full screen
     else
           maxPictureSize = TRect(xmargin,ymargin,xmargin+WidthOriginal/fraction, ymargin+HeightOriginal/fraction );

     // convert and resize to fill the screen, position the bmp on the Image object.
     Canvas->StretchDraw(maxPictureSize, BMPImage);

     delete BMPImage;
     delete JPEGImage;
     return true;
}
//---------------------------------------------------------------------------

void __fastcall Picture::ImageClick(TObject *Sender)
{
     Picture::LastClickedPicture =  this;
     MainForm->ProcessCommands(OnClickCommand);
}
//---------------------------------------------------------------------------

void __fastcall Picture::ImageDblClick(TObject *Sender)
{
     Picture::LastClickedPicture = this;
     MainForm->ProcessCommands(OnDubbleClickCommand);
}

void Picture::SelectNewPicture()
{
     if (MainForm->BackgroundImageDialog->Execute())
     {
          String s = MainForm->BackgroundImageDialog->FileName;
          int pos = s.UpperCase().Pos(Picture::ImageDir);
          if (pos==1)
             s = s.SubString(Picture::ImageDir.Length()+1,s.Length());
          LoadPictureFromFile(s);

     }
}

void Picture::command(String s)
{
     if (s=="ToOutput") MainForm->ProcessCommands("BG_"+Picture::LastClickedPicture->imageName);
     else if (s=="ToPreview") MainForm->ProcessCommands("Preview_Load_BG_"+Picture::LastClickedPicture->imageName);
     else if (s=="OpenFile") Picture::LastClickedPicture->SelectNewPicture();
     else if (s=="Clear") Picture::LastClickedPicture->Clear();
}
//---------------------------------------------------------------------------

void __fastcall Picture::ImageMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
       String t = Sender->ClassName();
       Picture::LastClickedPicture = this;
}
//---------------------------------------------------------------------------


String Picture::getImageName()
{
   return imageName;
}

void Picture::setImageName(String s)
{
     if (s.UpperCase().Pos(ImageDir)==1)
          imageName = getAfter(s,ImageDir);
     else imageName = s;
}


#pragma package(smart_init)
