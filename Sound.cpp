/*
Open source not for commercial deployment
*/
//---------------------------------------------------------------------------


#pragma hdrstop

#include "Sound.h"
#include "GlobalUnit.h"



void TMainForm::SetPlayButtonForNewSong()
{
     if ( checkSongFile(PreviewSongData.fileName))
     {
        ButtonPlay->Visible = true;
     }
     ButtonStop->Visible = ButtonPause->Visible;
}



void __fastcall TMainForm::ButtonPlayClick(TObject *Sender)
{
     bool FileFound=false;
     String s = PreviewSongData.fileName;
//     if (s.Pos(":")==0)        s = BaseDir + s;

     {
       s = replace(s,".txt", ".mp3");
       ifstream songfile(s.c_str());
       if (songfile.is_open())
       {
          FileFound=true;
          songfile.close();
       }
     }
     if (!FileFound)
     {
       s = replace(s, ".mp3", ".mid");
       ifstream songfile(s.c_str());
       if (songfile.is_open())
       {
          FileFound=true;
          songfile.close();
       }
     }

     if (FileFound)
     {
       if (MediaPlayer->FileName != s)
       {
         MediaPlayer->FileName = s;
         MediaPlayer->Open();
       }
       ButtonPlay->Visible=false;
       ButtonPause->Visible=true;
       ButtonStop->Visible=true;
       MediaPlayer->Play();
     }

     MediaPlayer->Notify=true;
     loopMusic=true;
     BlockFocus=false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ButtonEnter(TObject *Sender)
{
   BlockFocus=true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ButtonPauseClick(TObject *Sender)
{
   loopMusic=false;
   if (ButtonPlay->Visible)
      ButtonStop->Visible=false;
   else
       ButtonStop->Visible = checkSongFile(PreviewSongData.fileName);

   ButtonPause->Visible=false;
   ButtonPlay->Visible= checkSongFile(PreviewSongData.fileName);
   MediaPlayer->Pause();
   BlockFocus=false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ButtonStopClick(TObject *Sender)
{
   loopMusic=false;
   ButtonStop->Visible=false;
   ButtonPause->Visible=false;
   ButtonPlay->Visible= checkSongFile(PreviewSongData.fileName);
   MediaPlayer->FileName = "";
   MediaPlayer->Stop();
   BlockFocus=false;
}
//---------------------------------------------------------------------------

bool TMainForm::checkSongFile(String s)
{
     s = replace(s,".txt", ".mp3");
     {
       ifstream songfile(s.c_str());
       if (songfile.is_open())
       {
           songfile.close();
           return true;
       }
     }
     s = replace(s, ".mp3", ".mid");
     {
       ifstream songfile(s.c_str());
       if (songfile.is_open())
       {
           songfile.close();
           return true;
       }
     }
     return false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::MediaPlayerNotify(TObject *Sender)
{
/*  if (MediaPlayer->NotifyValue ==  nvSuccessful)
    if (loopMusic)
    {
      MediaPlayer->Play();
      MediaPlayer->Notify=true;
    }
    */
    TMainForm::ButtonStopClick(Sender);

}
//---------------------------------------------------------------------------

#pragma package(smart_init)
