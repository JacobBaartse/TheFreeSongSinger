//---------------------------------------------------------------------------
/*
Open source not for commercial deployment
*/

#include <vcl.h>
#pragma hdrstop

#include "GlobalUnit.h"
#include "OutputScreenUnit.h"
#include "DirectEdit.h"
#include "Setup.h"
#include "EditSong.h"
#include "EditPlaylist.h"
#include "PreviewUnit.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormShow(TObject *Sender)
{
//OutputScreen->curScreenSettings.CurSettings.SongTitle.Active
        RestartLog("Program started.");
        StartbuttonPressed =  false;
        BlockFocus = true;
        setLoggingOn(false);
        firstTimeOpenBackgroundDialog = true;

        DecimalSeparator = '.';
        UserInputLabel->Caption="";
        OutputScreen->Show();
        ProgramDir = ParamStr(0).SubString(1,ParamStr(0).Length()-15);
        setLogDir(ProgramDir);
        OutputScreen->Init(ProgramDir);
        keyHandling.setBaseDir(ProgramDir);
        SetupScreen->Init(ProgramDir);
        Picture::staticInit( ProgramDir);

        DirectEditForm->MainSpeedBar.init(DirectEditForm, ProgramDir);
        MainSpeedBar.init(PanelFullGui, ProgramDir);
        PlaylistSpeedBar.init(PanelPlayList, ProgramDir);
        PreviewSpeedBar.init(PanelSongPreview, ProgramDir);
        SearchResultBar.init(PanelSearchResult, ProgramDir);
        CommandsBar.init(PanelCommands, ProgramDir);
        searchInit(ProgramDir);

        MainPopUpMenu.init(PanelFullGui);
        PlayListPopUpMenu.init(PanelPlayList);
        PreviewPopUpMenu.init(PanelSongPreview);
        SearchResultPopUpMenu.init(PanelSearchResult);
        CommandsPopUpMenu.init(PanelCommands);
        previewImage = new Picture(PanelSongPreview,2,31,64,48,"PreviewPictureClick","PreviewPictureDubbleClick");
        PicturePopUpMenu.init(previewImage);

        CatchEnter->Width=0;
        CatchEscape->Width=0;
        EditCatchKeyInput->Width=0;
        ProcessCommands(ParamStr(1));
        SuppressSingleClick = false;

                   // from   http://www.codeguru.com/cpp/i-n/network/networkinformation/article.php/c2487/
                   // Get hostname and ip address of local computer,  by Jeff Lundgren February 9, 1999
                   WORD wVersionRequested;
                   WSADATA wsaData;
                   char name[255];
                   String ip;
                   PHOSTENT hostinfo;
                   wVersionRequested = MAKEWORD( 2, 0 );

                   if ( WSAStartup( wVersionRequested, &wsaData ) == 0 )
                   {

                      if( gethostname ( name, sizeof(name)) == 0)
                      {
                          if((hostinfo = gethostbyname(name)) != NULL)
                          {
                              ip = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);
                          }
                      }
                      WSACleanup( );
                   }
                   //---------------------------------------------------------------------------------------

        LabelHostIpNr->Caption = ip;
        PreviewSongData.previewSong=true;

        iniFileName = ProgramDir + "Settings\\Beamer.ini";
        PasswordEdit->Text = GetFromIniFile("BeamerScreen", "BiblePassword", /*default*/"", iniFileName);
        EditIpAddressHost->Text = GetFromIniFile("SlaveScreen", "HostIpAddress", /*default*/"10.0.0.1", iniFileName);
        LabelCommands->Caption = GetLanguageString("Commands",LabelCommands->Caption);
        LabelPlaylist->Caption = GetLanguageString("Playlist",LabelPlaylist->Caption);
        LabelSongPreview->Caption = GetLanguageString("SongPreview",LabelSongPreview->Caption);
        LabelSearchResult->Caption = GetLanguageString("SearchResult",LabelSearchResult->Caption);
        Start->Caption = GetLanguageString("Start",Start->Caption);
        CheckBoxRemoteScreen->Caption = GetLanguageString("UseAsRemoteScreen",CheckBoxRemoteScreen->Caption);
        LabelIpAddress->Caption = GetLanguageString("IpAddressHost",LabelIpAddress->Caption);
        GroupBoxHostScreen->Caption = GetLanguageString("HostScreen",GroupBoxHostScreen->Caption);
        RecoverOutputScreen->Caption = GetLanguageString("FindOutputScreen",RecoverOutputScreen->Caption);
        GroupBoxRemoteScreen->Caption = GetLanguageString("RemoteScreen",GroupBoxRemoteScreen->Caption);
        CheckBoxFullScreen->Caption = GetLanguageString("SingelScreen",CheckBoxFullScreen->Caption);
        MainForm->Caption =  GetLanguageString("MainTitle",MainForm->Caption);
        LabelPassword->Caption =  GetLanguageString("GiveBiblePassword",LabelPassword->Caption);
        BackgroundImageDialog->InitialDir = ProgramDir+ "data\\background\\";
}
//---------------------------------------------------------------------------

void TMainForm::ProcessCommands(String commands)
{
        Log(commands);
        recurcingDepth++;
        String CurCommand;
        String FollowingCommands;

        if (commands.Pos("'")==1)
        {
                commands = getAfter(commands,"'");
                CurCommand = "'"+getUntil(commands,"'")+"'";
                FollowingCommands = getAfter(commands,"'");
                FollowingCommands = getAfter(FollowingCommands,",");
        }
        else if (commands.Pos("\"")==1)
        {
                commands = getAfter(commands,"\"");
                CurCommand = "\""+getUntil(commands,"\"")+"\"";
                FollowingCommands = getAfter(commands,"\"");
                FollowingCommands = getAfter(FollowingCommands,",");
        }
        else if (commands.Pos("|")==1)
        {
                commands = getAfter(commands,"|");
                CurCommand = "|"+getUntil(commands,"|")+"|";
                FollowingCommands = getAfter(commands,"|");
                FollowingCommands = getAfter(FollowingCommands,",");
        }
        else
        {
                CurCommand = getUntil(commands,",");
                FollowingCommands = getAfter(commands,",");
        }

        ProcessCommand(CurCommand);

        if ((recurcingDepth<500) && (FollowingCommands!=NULL) && (FollowingCommands.Length()>0))
        {
               ProcessCommands(FollowingCommands);
        }
        if  (recurcingDepth>=500)
        {
            Log("Too many commands in a loop stop looping.....");
        }
}
//---------------------------------------------------------------------------
void TMainForm::ProcessInput()
{
     if (UserInput==NULL || UserInput.Length()==0)
          ProcessCommands("Empty_input");
     else ProcessCommands(UserInput);
     UserInput = "";
}

void TMainForm::ProcessCommand(String s)
{

    //todo replace with some translate command.
    if (s.Pos("0")==1)                       s = "o"+ getAfter(s,"0"); //probably a typo so replace 0 with o



    if (s.Pos("?")==1)                       findText(getAfter(s,"?"));
    else if (s.SubString(1,1)=='"')          OutputScreen->setBlinkMessage(s.SubString(2,s.Length()-2));
    else if (s.SubString(1,1)=='\'')         return;   //Comment just skipp
    else
    {
        String newcommands = commandTranslation.translate(s);
        if (newcommands != s)                    { ProcessCommands(newcommands); return; };

        if (s.Pos("AddToInput_comma")==1)        UserInput = UserInput + ',';
        else if (s.Pos("AddToInput_")==1)        AddToInput(getAfter(s,"_"));
        else if (s.Pos("PasteClipboardBuffer")==1)  PasteClipboardBuffer();
        else if (s.Pos("CopyOutputText_editor")==1)  OutputScreen->curScreenSettings.CurSongData.TextToNotepad();
        else if (s.Pos("Backspace")==1)          AddToInput("Backspace");
        else if (s.Pos("ClearUserInput")==1)     AddToInput("ClearAll");
        else if (s.Pos("ProcessInput")==1)       ProcessInput();
        else if (s=="createSearchIndex")         createSearchIndex();
        else if (s=="ShowPreviewBeamer")         ShowPreviewBeamer();

        else if (s.Pos("SetupScreen")==1)        SetupScreen->Show();
        else if (s.Pos("EditScreen")==1)         EditSongForm->Show();
        else if (s.Pos("DirectScreen")==1)       DirectEditForm->Show();
        else if (s.Pos("EditPlaylist")==1)       FormEditPlaylist->Show();
        else if (s.Pos("LoadCommandFile_")==1)   LoadCommandFile(getAfter(s,"_"));

        else if (s.Pos("AddTranslation_")==1)    commandTranslation.AddTranslation(getAfter(s,"_"));
        else if (s.Pos("AddSpeedButton_")==1)    addSpeedButtonToPannel(getAfter(s,"_"));
        else if (s.Pos("AddPopUpMenu_")==1)      addMenuItemToPopup(getAfter(s,"_"));
        else if (s=="Process_Command")           Process_Command();
        else if (s.Pos("DirectEdit_")==1)        DirectEditForm->Process_Command(getAfter(s,"_"));


        else if (s.Pos("ScreenFont_")==1)        SetScreenFont(getAfter(s,"_"));
        else if (s.Pos("AddListCommand_")==1)    addListCommand(getAfter(s,"_"));
        else if (s.Pos("Playlist_")==1)          PlaylistCommand(getAfter(s,"_"));
        else if (s.Pos("Preview_")==1)           PreviewCommand(getAfter(s,"_"));
        else if (s.Pos("Output_")==1)            OutputCommand(getAfter(s,"_"));
        else if (s=="PlayListToScreen")          PlayListToScreen();


        else if (s.Pos("Start")==1)              StartUpBeamer();
        else if (s.Pos("Logging_")==1)           setLogging(getAfter(s,"_"));
        else if (s.Pos("ViewFile_")==1)          viewFile(getAfter(s,"_"));
        else if (s.Pos("LoadKeyFile_")==1)       keyHandling.LoadKeySettingsFile(getAfter(s,"_"));

        else if (s.Pos("CountDown_")==1)         CountDown(getAfter(s,"_"));
        else if (s.Pos("LoadSong_")==1)          OutputScreen->LoadSong(getAfter(s,"_"));
        else if (s.Pos("Transpose_")==1)         OutputScreen->curScreenSettings.CurSongData.Transpose(getAfter(s,"_"));
        else if (s.Pos("PevTextBlock")==1)       OutputScreen->curScreenSettings.toPrevTextBlock();
        else if (s.Pos("NextTextBlock")==1)      OutputScreen->curScreenSettings.toNextTextBlock();
        else if (s.Pos("OneLine_")==1)           OutputScreen->curScreenSettings.scrollOneLine(getAfter(s,"_"));
        else if (s.Pos("ToBeginSong")==1)        OutputScreen->curScreenSettings.ToBeginSong();
        else if (s.Pos("ToEndSong")==1)          OutputScreen->curScreenSettings.ToEndSong();
        else if (s.Pos("RemoveText")==1)         OutputScreen->curScreenSettings.CurSongData.SetText("");
        else if (s.Pos("MinimizeControlCenter")==1)   WindowState = wsMinimized;
        else if (s.Pos("MaximizeControlCenter")==1)   WindowState = wsMaximized;
        else if (s.Pos("Maximize")==1)           {OutputScreen->WindowState = wsNormal; SendDataToSlaves("<Maximize/>");}
        else if (s.Pos("Minimize")==1)           {OutputScreen->WindowState = wsMinimized; SendDataToSlaves("<Minimize/>");}
        else if (s.Pos("Pause_")==1)             OutputScreen->curScreenSettings.CurSettings.setPause(getAfter(s,"_"));
        else if (s.Pos("Black_")==1)             OutputScreen->curScreenSettings.CurSettings.setBlack(getAfter(s,"_"));
        else if (s.Pos("ChangeSetting_")==1)     OutputScreen->curScreenSettings.CurSettings.changeSetting(getAfter(s,"_"));
        else if (s.Pos("BrightnessAdjust_")==1)  OutputScreen->setBrightnessAdjust(getAfter(s,"_"));
        else if (s.Pos("ContrastAdjust_")==1)    OutputScreen->setContrastAdjust(getAfter(s,"_"));
        else if (s.UpperCase().Pos("BG_")==1)    { OutputScreen->curScreenSettings.CurSettings.setBackgroud(getAfter(s,"_"));
                                                   LoadPictureInPreview(getAfter(s,"_"));
                                                 }
        else if (s.Pos("PreviewBG_")==1)         LoadPictureInPreview(getAfter(s,"_"));
        else if (s.Pos("Setting_")==1)           OutputScreen->curScreenSettings.CurSettings.LoadFile(getAfter(s,"_"));
        else if (s.Pos("Picture_")==1)           Picture::command(getAfter(s,"_"));

        else if (s.Pos("ToSlaveScreen:")==1)     {OutputScreen->SlaveMessage(getAfter(s,":"));
                                                  IndexProgress->Caption = getAfter(s,":");}
                  // up down arrow
        else if (s.Pos("Outdateline_")==1)        OutputScreen->curScreenSettings.setOutdateline(getAfter(s,"_"));
        else if (s.Length()==0)                  return;   //no command just skipp
        else if (allNumbers(s))                  OutputScreen->curScreenSettings.gotoStrofe(s);
        else if (s=="UserInputSong")             return;   //unprocessed command prevent endless looping during startup
        else                                     {UserInputSongname = s; ProcessCommand("UserInputSong");}
        adjustPreviewActiveLine();

    }
    if (OutputScreen->LateRefesch == false)
    {
        recurcingDepth = 0;
        OutputScreen->LateRefesch = true;
    }
}
//---------------------------------------------------------------------------


void TMainForm::adjustPreviewActiveLine()
{
     if (PreviewSongData.shortFileNameAndVers == OutputScreen->curScreenSettings.CurSongData.shortFileNameAndVers)
          SongPreview->ItemIndex = OutputScreen->curScreenSettings.CurLine;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::EditCatchKeyInputKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
        keyHandling.ProcessKeyDown(Key, Shift);
        EditCatchKeyInput->Text="";
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::EditCatchKeyInputKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
        String command = keyHandling.ProcessKeyDown(Key, Shift);
        if (command.Length()>0)
                ProcessCommands(command);
        EditCatchKeyInput->Text="";
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CatchEnterClick(TObject *Sender)
{
        String command = keyHandling.ProcessKeyDown(13);
        if (command.Length()>0)
                ProcessCommands(command);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CatchEscapeClick(TObject *Sender)
{
        String command = keyHandling.ProcessKeyDown(27);
        if (command.Length()>0)
                ProcessCommands(command);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
     if (StartbuttonPressed)
     {
        PlayList->Items->SaveToFile(ProgramDir+"Playlist.txt");
        SavePicturePreview(ProgramDir+"Playlist.txt.plst");
        PutInIniFile("BeamerScreen", "BiblePassword",PasswordEdit->Text ,iniFileName);
     }
     OutputScreen->Close();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::StartClick(TObject *Sender)
{
     StartbuttonPressed=true;
     if (StartIp())
         ProcessCommand("LoadCommandFile_start.cmdf");

     for (int i=0; i<MaxCollection; i++)
     {
         collectionPitures[i] = new Picture(PanelFullGui,i*66 + 222,34,64,48,"CollectionPictureClick","CollectionPictureDubbleClick");
         collectionPitures[i]->PopupMenu =  previewImage->PopupMenu;
     }
     try {
       PlayList->Items->LoadFromFile(ProgramDir+"Playlist.txt");
     } catch (Exception &exception) {}
     LoadPicturePreview(ProgramDir+"Playlist.txt.plst");
     recurcingDepth = 0;
     SongData::Password = PasswordEdit->Text;
}
//---------------------------------------------------------------------------

void TMainForm::StartUpBeamer()
{
        OutputScreen->FreezeSize();
        OutputScreen->curScreenSettings.CurSettings.LoadFile( "1");
        OutputScreen->LabelMoveMessage->Visible=false;
        OutputScreen->LateRefesch = true;
        PanelFullGui->Visible=true;
        if (CheckBoxFullScreen->Checked)
            OutputScreen->WindowState = wsMaximized;
        else
            BlockFocus=false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::RecoverOutputScreenClick(TObject *Sender)
{
     OutputScreen->Recover();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Timer1Timer(TObject *Sender)
{
   try
   {
        BlinkCursorCount++;
        BlinkCursorCount = BlinkCursorCount % 10;

        TDateTime now = Now();
        unsigned short hour, min, sec, msec;
        now.DecodeTime(&hour, &min, &sec, &msec);
        int SecToGo = countDownUntilHour*60*60 + countDownUntilMinute*60 - hour*60*60 -min*60 - sec;
        if (SecToGo<0) SecToGo += 24*60*60;
        if (doCountDown)
        if (prevSecToGo != SecToGo)
        {
            prevSecToGo = SecToGo;
            sec =  SecToGo % 60;
            min =  SecToGo/60 %60;
            hour = SecToGo/60/60 %60;
            String s="__";
            ProcessCommands("Logging_Off");
            if (hour>0)
            {
                s+=IntToStr(hour)+":";
                if (min<10) s+="0";
            }
            s+=IntToStr(min)+":";
            if (sec<10) s+="0";
            s+=IntToStr(sec);
            OutputScreen->SetText(s);
            if (SecToGo==0)
            {
               doCountDown=false;
               ProcessCommands("Logging_On");
            }
        }

        if (BlinkCursorCount==0)
        {
             if (CheckBoxRemoteScreen->Checked)
                 ClientSocket1->Socket->SendBuf(".",1); // send a harth beat to check the connection.
        }

        if ((OutputScreen->LateRefesch==false) && !BlockFocus)
             EditCatchKeyInput->SetFocus();

        if (EditCatchKeyInput->Focused())
        {
             if (BlinkCursorCount==5) UserInputLabel->Caption = UserInput;
             else if (BlinkCursorCount==0) UserInputLabel->Caption = UserInput+"|";
        }

        // if beamer screen active
        if (OutputScreen->WindowState!=wsMinimized)
        //check mouse is on the beamer screen
        if ((Mouse->CursorPos.x >= OutputScreen->Left) &&
            (Mouse->CursorPos.y >= OutputScreen->Top) &&
            (Mouse->CursorPos.x <= OutputScreen->Left + OutputScreen->Width) &&
            (Mouse->CursorPos.y < OutputScreen->Top + OutputScreen->Height))
        //check the mouse is not moved.
        if ((Mouse->CursorPos.x == currentMousePos.x) &&
            (Mouse->CursorPos.y == currentMousePos.y))
        {
                 MouseNotMovedCounter++;
                 if (MouseNotMovedCounter>20)
                 {
                    MouseNotMovedCounter=0;
                    if(CheckBoxFullScreen->Checked)
                       Mouse->CursorPos = TPoint(OutputScreen->Height, OutputScreen->Width);
                    else
                      Mouse->CursorPos = TPoint(Left+60, Top+80);
                 }
        }
        else
                MouseNotMovedCounter=0;

        currentMousePos = Mouse->CursorPos;
   }catch (...)
   {
   }

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::UserInputLabelClick(TObject *Sender)
{
     BlockFocus = false;
     EditCatchKeyInput->SetFocus();
}
//---------------------------------------------------------------------------

void TMainForm::LoadCommandFile(String s)
{
     if (s.Length()==0) return;

     if (s.Pos(":")==0) s = ProgramDir + "Settings\\" + s;

     char buffer[1024];
     ifstream commandFile(s.c_str());
     if (!commandFile.is_open()) return;

     while (!commandFile.eof())
     {
        commandFile.getline(buffer,1024);
        ProcessCommands(buffer);
     }
     commandFile.close();
}
//---------------------------------------------------------------------------

void TMainForm::addSpeedButtonToPannel(String s)
{
   // s: <panelName>_<picture_name>_<Additional text>_<command1|command2|....|command>
   String panelName = getUntil(s,"_");
   s = getAfter(s,"_");
   if (panelName=="Main") MainSpeedBar.addSpeedButton(s);
   else if (panelName=="PlayList") PlaylistSpeedBar.addSpeedButton(s);
   else if (panelName=="Preview") PreviewSpeedBar.addSpeedButton(s);
   else if (panelName=="SearchResult") SearchResultBar.addSpeedButton(s);
   else if (panelName=="Commands") CommandsBar.addSpeedButton(s);
   else if (panelName=="DirectEdit") DirectEditForm->MainSpeedBar.addSpeedButton(s);
}
//---------------------------------------------------------------------------

void TMainForm::addMenuItemToPopup(String s)
{
   // s: <panelName>_<menutext>_<command1|command2|....|command>
   String panelName = getUntil(s,"_");
   s = getAfter(s,"_");
   if (panelName=="Main") MainPopUpMenu.addMenuItem(s);
   else if (panelName=="PlayList") PlayListPopUpMenu.addMenuItem(s);
   else if (panelName=="Preview") PreviewPopUpMenu.addMenuItem(s);
   else if (panelName=="SearchResult") SearchResultPopUpMenu.addMenuItem(s);
   else if (panelName=="Commands") CommandsPopUpMenu.addMenuItem(s);
   else if (panelName=="Picture") PicturePopUpMenu.addMenuItem(s);
}
//---------------------------------------------------------------------------

void TMainForm::setLogging(String s)
{
     setLoggingOn(s=="On");
}
//---------------------------------------------------------------------------

void TMainForm::viewFile(String s)
{
     String action = getUntil(s,"_");
     String filename = getAfter(s,"_");

     if (filename.Pos(":")==0)
        filename= ProgramDir + filename;

     ShellExecuteA(this, action.c_str(), filename.c_str(), NULL, NULL, SW_NORMAL);
}
//---------------------------------------------------------------------------

void TMainForm::AddToInput(String c)
{
     if (c=="Backspace")         UserInput = UserInput.SubString(0,UserInput.Length()-1);
     else if (c=="ClearAll")     UserInput = "";
     else if (c.Length()!=1)     UserInput += c;
     else if (c.Length()==1)
     {
          if ( (GetKeyState(VK_CAPITAL) & 1) != 0)//caps lock = on?
          {
                if ((c[1]>='a')&&(c[1]<='z'))      c=c.UpperCase();
                else if ((c[1]>='A')&&(c[1]<='Z')) c=c.LowerCase();
          }
          UserInput = UserInput + c;
     }
     if (BlinkCursorCount>=5) UserInputLabel->Caption = UserInput;
     else if (BlinkCursorCount<5) UserInputLabel->Caption = UserInput+"|";
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BackgroundImageDialogSelectionChange(TObject *Sender)
{
	// Note; the real dialog is BackgroundImageDialog it's parent
        HWND  pshell = GetDlgItem(GetParent(BackgroundImageDialog->Handle) , /*ID_LISTVIEW*/0x0461);
	if (pshell)
        {
		// SHELLDLL_DefView window found: send it the command.
		SendMessage(pshell, WM_COMMAND, /*ODM_VIEW_THUMBS*/0x702d, NULL);
                if (firstTimeOpenBackgroundDialog)
                {
                  firstTimeOpenBackgroundDialog=false;
                  MoveWindow(
                    GetParent(BackgroundImageDialog->Handle),   // handle of window
                    MainForm->Left+5,                           // horizontal position
                    MainForm->Top+5,                            // vertical position
                    MainForm->Width-10,                         // width
                    MainForm->Height-10,	                // height
                    true                                        // repait flag
                    );
                }
	}
}
//---------------------------------------------------------------------------

void TMainForm::PasteClipboardBuffer()
{
      HGLOBAL hglb;
      LPSTR lpstr;

      OpenClipboard(NULL);
      if (!IsClipboardFormatAvailable(CF_TEXT))     return;

      hglb = GetClipboardData(CF_TEXT);
      if (hglb != NULL)
      {
         lpstr = (LPSTR) GlobalLock(hglb);
         if (lpstr != NULL)
         {
             UserInput = UserInput + lpstr;
             GlobalUnlock(hglb);
         }
      }
      CloseClipboard();
}
//---------------------------------------------------------------------------

void TMainForm::addListCommand(String s)
{
     if(s=="ClearAll")
     {
          ListBoxCommands->Clear();
          return;
     }

     if (ListBoxCommands->Count == MAX_LIST_COMMANDS)
     {
        MessageDlg("Maximum number of AddListCommand reached.", mtInformation, TMsgDlgButtons()<<mbOK , 0);
        return;
     }
     ListBoxCommands->ItemIndex = ListBoxCommands->Count -1;
     ListBoxCommands->AddItem(getUntil(s,"_"),NULL);

     s = getAfter(s,"_");
     s = replace(s,"|",",");
     ListCommand[ListBoxCommands->Count - 1] = s;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ListBoxCommandsClick(TObject *Sender)
{
     ProcessCommands("Commands_Click");
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ListBoxCommandsDblClick(TObject *Sender)
{
     ProcessCommands("Commands_DoubleClick");
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PlayListMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
     if (Shift.Contains(ssRight))
     {
         rightMouseButtonClicked = 2;
         mouse_event(MOUSEEVENTF_LEFTDOWN, X, Y, 0, NULL);      // simulate left mouse click down
         mouse_event(MOUSEEVENTF_LEFTUP, X, Y, 0, NULL);      // simulate left mouse click up
         return;
     }
     else rightMouseButtonClicked = false;
     PlaylistMouseDownIndex = PlayList->ItemIndex;
     BlockFocus=true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PlayListMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
     if (rightMouseButtonClicked>0)
     {
        rightMouseButtonClicked--;
        return;
     }
     int PlayListMouseUpIndex = PlayList->ItemIndex;
     if (PlaylistMouseDownIndex != PlayListMouseUpIndex)
     {
        PlayList->Items->Move(PlaylistMouseDownIndex, PlayListMouseUpIndex);
        PlayList->ItemIndex = PlayListMouseUpIndex;
     }
     else if (SuppressSingleClick)  SuppressSingleClick=false;
     else ProcessCommands("PlayList_Click");
     BlockFocus=false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PlayListDblClick(TObject *Sender)
{
     if (rightMouseButtonClicked>0)
             return;

     SuppressSingleClick=true;
     ProcessCommands("PlayList_DoubleClick");
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SongPreviewDblClick(TObject *Sender)
{
     ProcessCommands("SongPreview_DoubleClick");
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SongPreviewClick(TObject *Sender)
{
        ProcessCommands("SongPreview_Click");
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SearchResultClick(TObject *Sender)
{
     ProcessCommands("SearchResult_Click");
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SearchResultDblClick(TObject *Sender)
{
     ProcessCommands("SearchResult_DoubleClick");
}
//---------------------------------------------------------------------------

void TMainForm::PlaylistCommand(String s)
{
     if (s=="DeleteOne")  PlayList->Items->Delete(PlayList->ItemIndex);
     else if (s=="DeleteAll")  PlayList->Items->Clear();
     else if (s.Pos("Load_")==1)
     {
          String newItem = LoadFrom(getAfter(s,"_"));
          if (newItem==",''") ; // do nothing no song in preview
          else if ((PlayList->ItemIndex==-1) ||
                     (newItem.UpperCase() != PlayList->Items->operator [](PlayList->ItemIndex).UpperCase())&&
                     (newItem.UpperCase() != PlayList->Items->operator [](PlayList->Count-1).UpperCase()))
          {
             PlayList->Items->Add(newItem);
             PlayList->ItemIndex = PlayList->Count-1;
          }
     }
     else if (s=="NextLine") { if (PlayList->ItemIndex <PlayList->Count) PlayList->ItemIndex++; }
     else if (s=="PrevLine") { if (PlayList->ItemIndex >0) PlayList->ItemIndex--; }
     else if (s=="AddPicture")
     {
       if (PlayList->ItemIndex >=0)
       {
          BackgroundImageDialog->FileName = ProgramDir+ "data\\background\\*.jpg";
          if(MainForm->BackgroundImageDialog->Execute())
          {
               String FileName = MainForm->BackgroundImageDialog->FileName;
               FileName = getAfter(FileName, ProgramDir+ "data\\background\\");
               String CurCommand = PlayList->Items->Strings[PlayList->ItemIndex];

               //remove current background
               CurCommand = getUntil(CurCommand,",BG_");

               //add new background
               PlayList->Items->Strings[PlayList->ItemIndex] = CurCommand + ",BG_" +FileName;

               LoadPictureInPreview(FileName);
          };
       }
     }
     else if(s=="RemovePicture")
     {
         if (PlayList->ItemIndex>=0)
         {
               String CurCommand = PlayList->Items->Strings[PlayList->ItemIndex];

               //remove current background
               CurCommand = getUntil(CurCommand,",BG_");

               //add new background
               PlayList->Items->Strings[PlayList->ItemIndex] = CurCommand;
         }
     }
     else if (s=="SaveAs")
     {
          FileSaveDialog->FileName = ProgramDir + "playlist\\*.txt";
          FileSaveDialog->Filter="Playlist(*.txt)|*.txt";
          FileSaveDialog->DefaultExt=".txt";
          if (FileSaveDialog->Execute())
          {

               PlayList->Items->SaveToFile(FileSaveDialog->FileName);
               SavePicturePreview(FileSaveDialog->FileName + ".plst");
          }
     }
     else if (s=="Open")
     {
          FileOpenDialog->FileName = ProgramDir + "playlist\\*.txt";
          FileOpenDialog->Filter="Playlist(*.txt)|*.txt";
          FileOpenDialog->DefaultExt=".txt";
          if (FileOpenDialog->Execute())
          {
               PlayList->Items->LoadFromFile(FileOpenDialog->FileName);
               LoadPicturePreview(FileOpenDialog->FileName+".plst");
          }
     }
}
//---------------------------------------------------------------------------


void TMainForm::PreviewCommand(String s)
{
     if (s.Pos("Load_")==1)
     {
         s = getAfter(s,"_");
         String command = LoadFrom(s);
         additionalCommandsInPreview = ",";
         while (command.Length()>0)
         {
             //remove comments 'comment'
             if (command.Pos("'")==1)
               command = getAfter(getAfter(getAfter(command,"'"),"'"),",");

             String part_command = getUntil(command, ",");
             command = getAfter(command, ",");
             if (part_command.Length()>0)
                if (part_command.UpperCase().Pos("BG_")==1)
                {
                   previewImage->LoadPictureFromFile(getAfter(part_command,"_"));
                }
                else
                {
                   if (PreviewSongData.LoadSong(part_command))
                   {
                      TStrings * song = new TStringList();
                      for (int i=0; i<PreviewSongData.getSongLength(); i++)
                      {
                            song->Add(removeTags(PreviewSongData.text[i]));
                      }
                      song->Add("");
                      SongPreview->Items = song;   //copy constructor used of TStrings
                      delete song;
                      LabelCurrentSong->Caption = PreviewSongData.shortFileNameAndVers;
                      SetPlayButtonForNewSong();
                      ButtonPlay->Visible =  checkSongFile(PreviewSongData.fileName);
                   }
                   else if (part_command.Pos("Setting_")==1)
                   {
                       OutputScreen->curScreenSettings.curPreviewSettings.LoadFile(getAfter(part_command,"_"));
                       if (OutputScreen->curScreenSettings.curPreviewSettings.BackgroundPicture.Active)
                           previewImage->LoadPictureFromFile(OutputScreen->curScreenSettings.curPreviewSettings.BackgroundPicture.FileName);
                       else  previewImage->LoadPictureFromFile("");
                       settingInPreview =  part_command;
                   }
                   else
                   {
                       if (part_command.Pos("ViewFile_")==1)
                       {
                          LabelCurrentSong->Caption = getAfter(part_command,"ViewFile_");
                          SongPreview->Clear();
                          SongPreview->Items->Add(getAfter(part_command,"ViewFile_"));
                       }
                       additionalCommandsInPreview +=  part_command;
                       additionalCommandsInPreview += ",";
                   }
               }
         }
         LastUsed = "PreviewWithLineNr";
     }
     else if ("Picture_OpenFile")
     {
          previewImage->SelectNewPicture();
     }
}
//---------------------------------------------------------------------------

void TMainForm::OutputCommand(String s)
{
     if (s.Pos("Load_")==1)
     {
         s = LoadFrom(getAfter(s,"_"));
         OutputScreen->LoadSong(getUntil(s,','));
         ProcessCommands(getAfter(s,','));
     }
}
//---------------------------------------------------------------------------

String TMainForm::LoadFrom(String s)
{
  if (s.Pos("FromLastUsed")==1)   s = "From" + LastUsed;

  String retval="";

  if (s.Pos("FromOutput")==1)
  {
      retval = OutputScreen->curScreenSettings.CurSongData.shortFileNameAndVers;
  }
  else if (s.Pos("FromPlaylist")==1)
  {
       if (PlayList->ItemIndex>=0)
           retval = PlayList->Items->operator [](PlayList->ItemIndex);
  }
  else if (s.Pos("FromSearchResult")==1)
  {
       if (SearchResult->Count==0) return "";

       if (SearchResult->ItemIndex<0)   SearchResult->ItemIndex=0;
       retval = SearchResult->Items->operator [](SearchResult->ItemIndex);
  }
  else if (s.Pos("FromUserInput")==1)
  {
       retval = UserInputSongname;
  }
  else if (s.Pos("FromPreviewWithLineNr")==1)
  {
     if (SongPreview->Count==0) return "";


     if (SongPreview->ItemIndex<0)  SongPreview->ItemIndex=0;

     if (SongPreview->Items->operator [](SongPreview->ItemIndex).Pos("command ·")>0)
          ProcessCommands(getUntil(getAfter(SongPreview->Items->operator [](SongPreview->ItemIndex),"·"),"]"));
     else if (SongPreview->Items->operator [](0).Pos("command ·")>0)
     {}// do nothing this is a menu file do not show on screen.
     else
     {
          retval = PreviewSongData.shortFileNameAndVers;

          if  (PreviewSongData.shortFileNameAndVers.Length()>0 && PreviewSongData.shortFileNameAndVers[1]=='|') {/*do nothing*/}
          else   retval += ("_LineNr_" + IntToStr(SongPreview->ItemIndex));

          retval += "," + settingInPreview;
          settingInPreview = "";
          retval += ",BG_" + previewImage->getImageName();
          retval += additionalCommandsInPreview;
     }
  }
  else if (s.Pos("FromPreviewWithText")==1)
  {
       retval = PreviewSongData.shortFileNameAndVers + ",'" + replace(PreviewSongData.getBeginOfText(),"'","") + "'";
       retval += additionalCommandsInPreview;
  }
  else if (s.Pos("FromPreview")==1)
  {
        retval = PreviewSongData.shortFileNameAndVers;
        retval += additionalCommandsInPreview;
  }
  else if (s.Pos("FileDialog_")==1)
  {
        FileOpenDialog->Filter =  "Powerpoint|*.pp*";
        FileOpenDialog->FileName = ProgramDir + "ppt\\*.pp*";
        if (MainForm->FileOpenDialog->Execute())
        {
           String smallFilename = MainForm->FileOpenDialog->FileName;
           String fileName = smallFilename;
           if (fileName.UpperCase().Pos(ProgramDir.UpperCase())>0)
              fileName = getAfter(fileName, ProgramDir);
           while (smallFilename.Pos("\\")>0) smallFilename = getAfter(smallFilename,"\\");
           smallFilename = getUntil(smallFilename,".");
           return "'" + smallFilename + "',ViewFile_open_" + fileName;
        }
        else return "";
  }
  else
  {
       return s;
  }

  if (s.Pos("_Next")>0)     return NextPrevSong(retval, true);
  if (s.Pos("_Prev")>0)     return NextPrevSong(retval, false);

  return retval;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormResize(TObject *Sender)
{
   PanelCommands->Width = (Width - 55)/4;
   PanelPlayList->Left = PanelCommands->Width + PanelCommands->Left + 10;
   PanelPlayList->Width = (Width - 55)/4;
   PanelSongPreview->Left = PanelPlayList->Width + PanelPlayList->Left + 10;
   PanelSongPreview->Width = (Width - 55)/4;
   PanelSearchResult->Left = PanelSongPreview->Width +PanelSongPreview->Left + 10;
   PanelSearchResult->Width = (Width - 55)/4;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CheckBoxRemoteScreenClick(TObject *Sender)
{
     GroupBoxHostScreen->Visible = !CheckBoxRemoteScreen->Checked;
     GroupBoxRemoteScreen->Visible = CheckBoxRemoteScreen->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ClientSocket1Read(TObject *Sender, TCustomWinSocket *Socket)
{
      int byteCount;
      char * buf;
      try
      {
        byteCount = Socket->ReceiveLength();
        buf = new byte[byteCount+1];
        if (byteCount>0)
        {
            int tmp = Socket->ReceiveBuf(buf, byteCount);
            if (tmp!= byteCount)
                MessageDlg("TCP ip comm count read error.", mtInformation, TMsgDlgButtons()<<mbOK , 0);
            buf[byteCount]=0;
            slaveRecieveData += buf;
        }
      }
      catch (...)
      {
        Log("ClientSocket1Read.exception");
      }
      delete buf;
      while (slaveRecieveData.Pos("\x17")>0)
      {
           String s = getUntil(slaveRecieveData, "\x17");
           slaveRecieveData = getAfter(slaveRecieveData, "\x17");
           if (s.Pos("<OutputScreen>")==1) OutputScreen->ReceiveAsSlave(getUntil(getAfter(s,"<OutputScreen>"),"</OutputScreen>"));
           else if (s.Pos("<SongText>")==1)
                   {
                        OutputScreen->curScreenSettings.CurSongData.ReceiveAsSlave(getUntil(getAfter(s,"<SongText>"),"</SongText>"));
                        OutputScreen->calcMarginTextReduction=true;
                   }
           else if (s.Pos("<ScreenSettings>")==1) OutputScreen->curScreenSettings.ReceiveAsSlave(getUntil(getAfter(s,"<ScreenSettings>"),"</ScreenSettings>"));
           else if (s.Pos("<LateRefesch/>")==1) OutputScreen->LateRefesch=true;
           else if (s.Pos("<Maximize/>")==1) OutputScreen->WindowState = wsNormal;
           else if (s.Pos("<Minimize/>")==1) OutputScreen->WindowState = wsMinimized;
           else if (s.Pos("<SettingsData>")==1) OutputScreen->curScreenSettings.CurSettings.ReceiveAsSlave(getUntil(getAfter(s,"<SettingsData>"),"</SettingsData>"));
      }
}


//---------------------------------------------------------------------------

void TMainForm::SendDataToSlaves(String s)
{
     s += "\x17"; // add end of transmission block character
     if (ServerSocket1->Active==true)
     {
          for (int i=0; i<ServerSocket1->Socket->ActiveConnections; i++)
          {
               String t=s;
               while (t.Length()>0)
               {
                     int bytesSend = ServerSocket1->Socket->Connections[i]->SendBuf(t.c_str(),t.Length());
                     t = t.SubString(bytesSend, t.Length()-bytesSend);
               }
          }
     }
}

void __fastcall TMainForm::ClientSocket1Connect(TObject *Sender,
      TCustomWinSocket *Socket)
{
     LabelClientSocketStatus->Caption = "Connected";
     ProcessCommand("LoadCommandFile_start.cmdf"); // only perform the first time.
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ClientSocket1Connecting(TObject *Sender,
      TCustomWinSocket *Socket)
{
     LabelClientSocketStatus->Caption = "Connecting";
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ClientSocket1Disconnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
     LabelClientSocketStatus->Caption = "Disconnect";
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ClientSocket1Error(TObject *Sender,
      TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
     LabelClientSocketStatus->Caption = "Error code: " + IntToStr(ErrorCode);
     MessageDlg("Connection lost restart program.", mtInformation, TMsgDlgButtons()<<mbOK , 0);
     exit(1);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ClientSocket1Lookup(TObject *Sender,
      TCustomWinSocket *Socket)
{
     LabelClientSocketStatus->Caption = "LookUp";
}
//---------------------------------------------------------------------------

bool  TMainForm::StartIp()
{
        if (CheckBoxRemoteScreen->Checked)
        {
            PutInIniFile("SlaveScreen", "HostIpAddress", EditIpAddressHost->Text ,iniFileName);
            ClientSocket1->Address = EditIpAddressHost->Text;
            ClientSocket1->Open();
            return false; // on connect will continue the startup process
        }
        else
        {
          try
          {
                ServerSocket1->Active=true;
          }
          catch (...)
          {
             MessageDlg("Warning TCP port not available, remote screen will not be supported.", mtInformation, TMsgDlgButtons()<<mbOK , 0);
          }
        }
        return true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ServerSocket1ClientRead(TObject *Sender, TCustomWinSocket *Socket)
{
    Socket->Read(Socket->ReceiveLength()); // flush incomming harthbeat.
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CatchTabEnter(TObject *Sender)
{
        String command = keyHandling.ProcessKeyDown(9);
        if (command.Length()>0)
                ProcessCommands(command);
}
//---------------------------------------------------------------------------



void TMainForm::SavePicturePreview(String fileName)
{
    ofstream pictureListFile;
    pictureListFile.open(fileName.c_str());
    String s = previewImage->getImageName();
    pictureListFile.write(s.c_str(),s.Length());
    pictureListFile.write("\n",1);

    for (int i=0; i<MaxCollection; i++)
    {
        if (collectionPitures[i]->getImageName()!=NULL)
        {
                s = collectionPitures[i]->getImageName();
                pictureListFile.write(s.c_str(),s.Length());
                pictureListFile.write("\n",1);
        }
    }
    pictureListFile.close();
}
//---------------------------------------------------------------------------


void TMainForm::LoadPicturePreview(String fileName)
{
       try
       {
            char buffer[1024];
            int imagecount = 0;
            ifstream pictureFile(fileName.c_str());

            pictureFile.getline(buffer,1024);
            AnsiString lineBuffer = buffer;
            previewImage->LoadPictureFromFile(lineBuffer);

            if (pictureFile.is_open())
            {
               while (!pictureFile.eof())
               {
                  pictureFile.getline(buffer,1024);
                  lineBuffer = buffer;
                  if (lineBuffer.Length()>0)
                  {
                       if (collectionPitures[imagecount]->LoadPictureFromFile(lineBuffer))
                            imagecount++;
                  }
               }
               pictureFile.close();
            }
        } catch ( ... ){}
}

void TMainForm::LoadPictureInPreview(String fileName)
{
       try
       {
            previewImage->LoadPictureFromFile(fileName);
       } catch ( ... ){}
}

void TMainForm::Process_Command()
{
     ProcessCommands(ListCommand[ListBoxCommands->ItemIndex]);
}

void TMainForm::SetScreenFont(String s)
{
     int i=0;
     if (s=="Reduce")
        if (ListBoxCommands->Font->Size > 8)
           i=-1;

     if (s=="Increase")
        i=1;

     ListBoxCommands->Font->Size +=i;
     PlayList->Font->Size +=i;
     SongPreview->Font->Size +=i;
     SearchResult->Font->Size +=i;
}


void TMainForm::PlayListToScreen()
{  //lithurgy mode
   int curPlaylistLine = PlayList->ItemIndex +1;
   String screenData="";

   for (int i= curPlaylistLine; i< PlayList->Count; i++)
   {
       String PlaylistLine = getUntil(PlayList->Items->operator [](i), ",");
       if (PlaylistLine.Length()>0)
       {
         switch (PlaylistLine[1])
         {
              case '|' :   PlaylistLine = getUntil(getAfter(PlaylistLine,"|"),"|"); break;
              case '\'':   PlaylistLine = getUntil(getAfter(PlaylistLine,"'"),"'"); break;
         }
         screenData += PlaylistLine;
         screenData += "_";
       }
   }
   OutputScreen->SetText(screenData);
}



void TMainForm::CountDown(String s)
{
     if (s.Length()>0)
     {
       String sHour = getUntil(s,":");
       String sMinute = getAfter(s,":");
       countDownUntilHour = StrToInt(sHour);
       countDownUntilMinute = StrToInt(sMinute);
       doCountDown = true;
     }
     else
     {
       doCountDown = false;
       OutputScreen->SetText("");
       ProcessCommands("Logging_On");
     }

}


void TMainForm::ShowPreviewBeamer()
{
      Preview->Show();
      Preview->Timer1->Enabled=true;
};
