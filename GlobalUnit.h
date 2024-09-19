//---------------------------------------------------------------------------

#ifndef GlobalUnitH
#define GlobalUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <MPlayer.hpp>
#include <Graphics.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <Graphics.hpp>
#include <Menus.hpp>
#include <ScktComp.hpp>

#include "KeyHandling.h"
#include "CommandTranslationUnit.h"
#include "SpeedBar.h"
#include "PopUpMenu.h"
#include "SongDataUnit.h"
#include "utils.h"
#include "Search.h"
#include "Picture.h"
#include "Sound.h"



#define MAX_LIST_COMMANDS 20
#define MaxCollection 16





//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
        TEdit *EditCatchKeyInput;
        TButton *CatchEnter;
        TButton *CatchEscape;
        TPanel *UserInputLabel;
        TButton *Start;
        TButton *RecoverOutputScreen;
        TTimer *Timer1;
        TOpenDialog *BackgroundImageDialog;
        TColorDialog *ColorDialog;
        TFontDialog *FontDialog;
        TOpenDialog *FileOpenDialog;
        TSaveDialog *FileSaveDialog;
        TListBox *ListBoxCommands;
        TListBox *PlayList;
        TListBox *SongPreview;
        TPanel *PanelPlayList;
        TPanel *PanelSongPreview;
        TPanel *PanelFullGui;
        TPanel *PanelSearchResult;
        TListBox *SearchResult;
        TLabel *LabelPlaylist;
        TLabel *LabelSongPreview;
        TLabel *LabelSearchResult;
        TPanel *PanelCommands;
        TLabel *LabelCommands;
        TCheckBox *CheckBoxRemoteScreen;
        TEdit *EditIpAddressHost;
        TLabel *LabelIpAddress;
        TGroupBox *GroupBoxRemoteScreen;
        TCheckBox *CheckBoxFullScreen;
        TClientSocket *ClientSocket1;
        TServerSocket *ServerSocket1;
        TGroupBox *GroupBoxHostScreen;
        TLabel *LabelIpAddressHost;
        TLabel *LabelHostIpNr;
        TLabel *LabelClientSocketStatus;
        TButton *CatchTab;
        TLabel *IndexProgress;
        TLabel *LabelCurrentSong;
        TLabel *LabelPassword;
        TEdit *PasswordEdit;
        TButton *ButtonPlay;
        TButton *ButtonPause;
        TButton *ButtonStop;
        TMediaPlayer *MediaPlayer;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall EditCatchKeyInputKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall EditCatchKeyInputKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall CatchEnterClick(TObject *Sender);
        void __fastcall CatchEscapeClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall StartClick(TObject *Sender);
        void __fastcall RecoverOutputScreenClick(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall UserInputLabelClick(TObject *Sender);
        void __fastcall BackgroundImageDialogSelectionChange(TObject *Sender);
        void __fastcall ListBoxCommandsClick(TObject *Sender);
        void __fastcall PlayListMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall PlayListMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall PlayListDblClick(TObject *Sender);
        void __fastcall SongPreviewClick(TObject *Sender);
        void __fastcall SongPreviewDblClick(TObject *Sender);
        void __fastcall SearchResultClick(TObject *Sender);
        void __fastcall SearchResultDblClick(TObject *Sender);
        void __fastcall CheckBoxRemoteScreenClick(TObject *Sender);
        void __fastcall ClientSocket1Read(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ClientSocket1Connect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ClientSocket1Connecting(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ClientSocket1Disconnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ClientSocket1Error(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
        void __fastcall ClientSocket1Lookup(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ServerSocket1ClientRead(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall CatchTabEnter(TObject *Sender);
        void __fastcall ListBoxCommandsDblClick(TObject *Sender);
        void __fastcall ButtonPlayClick(TObject *Sender);
        void __fastcall ButtonEnter(TObject *Sender);
        void __fastcall ButtonPauseClick(TObject *Sender);
        void __fastcall ButtonStopClick(TObject *Sender);
        void __fastcall MediaPlayerNotify(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TMainForm(TComponent* Owner);
        void ProcessCommands(String command);
        void ProcessCommand(String curCommand);
        void AddToInput(String s);

        void LoadCommandFile(String s);
        void StartUpBeamer();
        void setLogging(String s);
        void CleanUpToolBar();
        void viewFile(String s);
        void PasteClipboardBuffer();
        void addListCommand(String s);
        void PlaylistCommand(String s);
        void PreviewCommand(String s);
        void OutputCommand(String s);
        String LoadFrom(String s);

        void addSpeedButtonToPannel(String s);
        void addMenuItemToPopup(String s);
        void SendDataToSlaves(String s);
        bool StartIp();
        void SavePicturePreview(String fileName);
        void LoadPicturePreview(String fileName);
        void LoadPictureInPreview(String fileName);
        void adjustPreviewActiveLine();
        void ProcessInput();
        void Process_Command();
        void SetScreenFont(String s);
        bool checkSongFile(String s);
        void SetPlayButtonForNewSong();
        void PlayListToScreen();
        void CountDown(String s);
        void ShowPreviewBeamer();


        KeyHandling keyHandling;
        CommandTranslation commandTranslation;
        String UserInput;
        int recurcingDepth;
        int BlinkCursorCount;

        String ListCommand[MAX_LIST_COMMANDS];

        SpeedBar MainSpeedBar,
                 PlaylistSpeedBar,
                 PreviewSpeedBar,
                 SearchResultBar,
                 CommandsBar;

        PopUpMenu MainPopUpMenu,
                  PlayListPopUpMenu,
                  PreviewPopUpMenu,
                  SearchResultPopUpMenu,
                  CommandsPopUpMenu,
                  PicturePopUpMenu;

        bool firstTimeOpenBackgroundDialog;
        int PlaylistMouseDownIndex;
        bool SuppressSingleClick;
        SongData PreviewSongData;
        String PreviewBackGround;
        String UserInputSongname;
        bool BlockFocus;
        String slaveRecieveData;
        bool ClientSocket1Connected;
        String iniFileName;
        String ProgramDir;
        Picture * previewImage;
        Picture * collectionPitures[MaxCollection];
        bool StartbuttonPressed;
        String LastUsed;
        TPoint currentMousePos;
        int MouseNotMovedCounter;
        String additionalCommandsInPreview;
        String settingInPreview;
        bool loopMusic;
        bool doCountDown;
        int countDownUntilHour;
        int countDownUntilMinute;
        int prevSecToGo;
        int rightMouseButtonClicked;

};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif




