/*
Open source not for commercial deployment
*/
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("GlobalUnit.cpp", MainForm);
USEFORM("OutputScreenUnit.cpp", OutputScreen);
USEFORM("Setup.cpp", SetupScreen);
USEFORM("EditSong.cpp", EditSongForm);
USEFORM("DirectEdit.cpp", DirectEditForm);
USEFORM("EditPlaylist.cpp", FormEditPlaylist);
USEFORM("PreviewUnit.cpp", Preview);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "The Free Song Singer 2";
                 Application->CreateForm(__classid(TMainForm), &MainForm);
                 Application->CreateForm(__classid(TOutputScreen), &OutputScreen);
                 Application->CreateForm(__classid(TSetupScreen), &SetupScreen);
                 Application->CreateForm(__classid(TEditSongForm), &EditSongForm);
                 Application->CreateForm(__classid(TDirectEditForm), &DirectEditForm);
                 Application->CreateForm(__classid(TFormEditPlaylist), &FormEditPlaylist);
                 Application->CreateForm(__classid(TPreview), &Preview);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 //Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         //Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------
