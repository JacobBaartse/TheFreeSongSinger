//---------------------------------------------------------------------------

#ifndef PictureH
#define PictureH

#include <ExtCtrls.hpp>
#include <Classes.hpp>
#include <iostream.h>
#include <fstream.h>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <Graphics.hpp>
#include "PopUpMenu.h"


class Picture :public TImage
{

private:	// User declarations

    TJPEGImage *JPEGImage;
    Graphics::TBitmap *BMPImage;
    String imageName;

public:		// User declarations
    static String ImageDir;

    static Picture *  LastClickedPicture;

    static void staticInit(String dir);
    bool LoadPictureFromFile(String FileName);

    Picture(TWinControl* Owner, int left, int top, int width, int height, String clickCommand, String dblClickCommand);
    void __fastcall ImageClick(TObject *Sender);
    void __fastcall ImageDblClick(TObject *Sender);
    void __fastcall ImageMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    static void command(String s);
    void SelectNewPicture();
    void Clear();
    String getImageName();
    void setImageName(String s);



    String OnClickCommand;
    String OnDubbleClickCommand;

};

String  Picture::ImageDir;
Picture * Picture::LastClickedPicture;

//---------------------------------------------------------------------------
#endif
