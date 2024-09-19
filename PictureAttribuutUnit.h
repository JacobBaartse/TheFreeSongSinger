//---------------------------------------------------------------------------

#ifndef PictureAttribuutUnitH
#define PictureAttribuutUnitH

#include <Classes.hpp>
#include <Graphics.hpp>
#include <Dialogs.hpp>
#include "Utils.h"
#include "GlobalUnit.h"


class PictureAttribuut
{
private:	// User declarations
public:		// User declarations
        PictureAttribuut();
        bool operator==(const PictureAttribuut pa);
        bool operator!=(const PictureAttribuut pa);
        void setTranparent(bool pb);
        void changeSetting(String s);
        void openFile(String s);
        void SetBaseDir(String s);


        String  FileName;
        __int16 Brightness;
        double Contrast;
        TColor BackGroundColor;
        bool Transparent;
        String BaseDir;
        bool Active;

};
//---------------------------------------------------------------------------
#endif
