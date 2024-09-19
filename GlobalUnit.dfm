object MainForm: TMainForm
  Left = 303
  Top = 321
  Width = 940
  Height = 611
  BorderIcons = [biSystemMenu, biMaximize]
  Caption = 'The Free Song Singer 2'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDefaultPosOnly
  OnClose = FormClose
  OnResize = FormResize
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object LabelPassword: TLabel
    Left = 240
    Top = 120
    Width = 246
    Height = 13
    Caption = 'Fill in the password to be able to open the bible texts'
  end
  object PasswordEdit: TEdit
    Left = 238
    Top = 134
    Width = 419
    Height = 21
    TabOrder = 6
  end
  object GroupBoxRemoteScreen: TGroupBox
    Left = 0
    Top = 32
    Width = 145
    Height = 121
    Caption = 'Remote screen'
    TabOrder = 2
    Visible = False
    object LabelIpAddress: TLabel
      Left = 8
      Top = 48
      Width = 78
      Height = 13
      Caption = 'Ip address host: '
    end
    object LabelClientSocketStatus: TLabel
      Left = 8
      Top = 97
      Width = 3
      Height = 13
      Caption = '-'
    end
    object EditIpAddressHost: TEdit
      Left = 24
      Top = 64
      Width = 97
      Height = 21
      TabOrder = 1
      Text = '127.0.0.1'
    end
    object CheckBoxFullScreen: TCheckBox
      Left = 8
      Top = 16
      Width = 97
      Height = 17
      Caption = 'Single screen'
      TabOrder = 0
    end
  end
  object CheckBoxRemoteScreen: TCheckBox
    Left = 8
    Top = 8
    Width = 185
    Height = 17
    Caption = 'Use as remote screen'
    TabOrder = 0
    OnClick = CheckBoxRemoteScreenClick
  end
  object GroupBoxHostScreen: TGroupBox
    Left = 8
    Top = 40
    Width = 113
    Height = 57
    Caption = 'Host screen'
    TabOrder = 1
    object LabelIpAddressHost: TLabel
      Left = 8
      Top = 16
      Width = 75
      Height = 13
      Caption = 'Ip address host:'
    end
    object LabelHostIpNr: TLabel
      Left = 40
      Top = 32
      Width = 39
      Height = 13
      Caption = '10.0.0.1'
    end
  end
  object Start: TButton
    Left = 240
    Top = 75
    Width = 108
    Height = 24
    Caption = 'Start'
    TabOrder = 4
    OnClick = StartClick
  end
  object RecoverOutputScreen: TButton
    Left = 240
    Top = 42
    Width = 105
    Height = 25
    Caption = 'Find output screen'
    TabOrder = 3
    OnClick = RecoverOutputScreenClick
  end
  object PanelFullGui: TPanel
    Left = 0
    Top = 0
    Width = 932
    Height = 577
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 5
    Visible = False
    DesignSize = (
      932
      577)
    object IndexProgress: TLabel
      Left = 8
      Top = 69
      Width = 5
      Height = 13
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object PanelPlayList: TPanel
      Left = 154
      Top = 88
      Width = 153
      Height = 490
      Anchors = [akLeft, akTop, akBottom]
      TabOrder = 2
      object LabelPlaylist: TLabel
        Left = 8
        Top = 40
        Width = 32
        Height = 13
        Caption = 'Playlist'
      end
      object PlayList: TListBox
        Left = 1
        Top = 56
        Width = 151
        Height = 433
        Hint = 'Reorder with drag and drop'
        Align = alBottom
        Anchors = [akLeft, akTop, akRight, akBottom]
        Color = clSkyBlue
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Arial'
        Font.Style = []
        ItemHeight = 14
        ParentFont = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
        OnDblClick = PlayListDblClick
        OnMouseDown = PlayListMouseDown
        OnMouseUp = PlayListMouseUp
      end
    end
    object PanelSongPreview: TPanel
      Left = 317
      Top = 88
      Width = 156
      Height = 490
      Anchors = [akLeft, akTop, akBottom]
      TabOrder = 3
      object LabelSongPreview: TLabel
        Left = 80
        Top = 48
        Width = 65
        Height = 13
        Caption = 'Song preview'
      end
      object LabelCurrentSong: TLabel
        Left = 80
        Top = 32
        Width = 3
        Height = 13
      end
      object SongPreview: TListBox
        Left = 1
        Top = 80
        Width = 154
        Height = 409
        Align = alBottom
        Anchors = [akLeft, akTop, akRight, akBottom]
        Color = clSkyBlue
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Arial'
        Font.Style = []
        ItemHeight = 14
        ParentFont = False
        TabOrder = 0
        OnClick = SongPreviewClick
        OnDblClick = SongPreviewDblClick
      end
      object ButtonPlay: TButton
        Left = 80
        Top = 64
        Width = 17
        Height = 17
        Caption = '4'
        Font.Charset = SYMBOL_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Webdings'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        Visible = False
        OnClick = ButtonPlayClick
        OnEnter = ButtonEnter
      end
      object ButtonPause: TButton
        Left = 96
        Top = 64
        Width = 17
        Height = 17
        Caption = ';'
        Font.Charset = SYMBOL_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'Webdings'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 2
        Visible = False
        OnClick = ButtonPauseClick
        OnEnter = ButtonEnter
      end
      object ButtonStop: TButton
        Left = 112
        Top = 64
        Width = 17
        Height = 17
        Caption = '<'
        Font.Charset = SYMBOL_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Webdings'
        Font.Style = []
        ParentFont = False
        TabOrder = 3
        Visible = False
        OnClick = ButtonStopClick
        OnEnter = ButtonEnter
      end
    end
    object EditCatchKeyInput: TEdit
      Left = 48
      Top = 0
      Width = 57
      Height = 21
      TabOrder = 0
      OnKeyDown = EditCatchKeyInputKeyDown
      OnKeyUp = EditCatchKeyInputKeyUp
    end
    object CatchEscape: TButton
      Left = 272
      Top = 0
      Width = 75
      Height = 17
      Cancel = True
      Caption = 'CatchEscape'
      TabOrder = 4
      TabStop = False
      OnClick = CatchEscapeClick
    end
    object CatchEnter: TButton
      Left = 192
      Top = 0
      Width = 75
      Height = 17
      Caption = 'CatchEnter'
      Default = True
      TabOrder = 5
      TabStop = False
      OnClick = CatchEnterClick
    end
    object UserInputLabel: TPanel
      Left = 8
      Top = 40
      Width = 209
      Height = 25
      Alignment = taLeftJustify
      BevelOuter = bvNone
      BorderStyle = bsSingle
      Caption = 'UserInput'
      Color = clWindow
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 6
      OnClick = UserInputLabelClick
    end
    object PanelSearchResult: TPanel
      Left = 480
      Top = 88
      Width = 156
      Height = 490
      Anchors = [akLeft, akTop, akBottom]
      TabOrder = 7
      object LabelSearchResult: TLabel
        Left = 8
        Top = 40
        Width = 62
        Height = 13
        Caption = 'Search result'
      end
      object SearchResult: TListBox
        Left = 1
        Top = 56
        Width = 154
        Height = 433
        Align = alBottom
        Anchors = [akLeft, akTop, akRight, akBottom]
        Color = clSkyBlue
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Arial'
        Font.Style = []
        ItemHeight = 14
        ParentFont = False
        TabOrder = 0
        OnClick = SearchResultClick
        OnDblClick = SearchResultDblClick
      end
    end
    object PanelCommands: TPanel
      Left = 8
      Top = 88
      Width = 137
      Height = 490
      Anchors = [akLeft, akTop, akBottom]
      TabOrder = 8
      object LabelCommands: TLabel
        Left = 8
        Top = 40
        Width = 52
        Height = 13
        Caption = 'Commands'
      end
      object ListBoxCommands: TListBox
        Left = 1
        Top = 56
        Width = 135
        Height = 433
        Align = alBottom
        Anchors = [akLeft, akTop, akRight, akBottom]
        Color = clSkyBlue
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Arial'
        Font.Style = []
        ItemHeight = 14
        ParentFont = False
        TabOrder = 0
        OnClick = ListBoxCommandsClick
        OnDblClick = ListBoxCommandsDblClick
      end
    end
    object CatchTab: TButton
      Left = 112
      Top = 0
      Width = 75
      Height = 17
      Caption = 'CatchTab'
      TabOrder = 1
      OnEnter = CatchTabEnter
    end
    object MediaPlayer: TMediaPlayer
      Left = 664
      Top = 0
      Width = 85
      Height = 25
      EnabledButtons = []
      VisibleButtons = [btPlay, btPause, btStop]
      Visible = False
      TabOrder = 9
      OnNotify = MediaPlayerNotify
    end
  end
  object Timer1: TTimer
    Interval = 100
    OnTimer = Timer1Timer
    Left = 632
  end
  object BackgroundImageDialog: TOpenDialog
    Filter = 'Image files|*.jpg;*.bmp;'
    Options = [ofHideReadOnly, ofFileMustExist, ofEnableSizing]
    OptionsEx = [ofExNoPlacesBar]
    OnSelectionChange = BackgroundImageDialogSelectionChange
    Left = 480
  end
  object ColorDialog: TColorDialog
    Ctl3D = True
    Left = 536
  end
  object FontDialog: TFontDialog
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    MinFontSize = 0
    MaxFontSize = 0
    Left = 600
  end
  object FileOpenDialog: TOpenDialog
    Options = [ofHideReadOnly, ofFileMustExist, ofEnableSizing]
    Left = 512
  end
  object FileSaveDialog: TSaveDialog
    DefaultExt = 'txt'
    Left = 568
  end
  object ClientSocket1: TClientSocket
    Active = False
    Address = '192.18.1.33'
    ClientType = ctNonBlocking
    Port = 54321
    OnLookup = ClientSocket1Lookup
    OnConnecting = ClientSocket1Connecting
    OnConnect = ClientSocket1Connect
    OnDisconnect = ClientSocket1Disconnect
    OnRead = ClientSocket1Read
    OnError = ClientSocket1Error
    Left = 416
  end
  object ServerSocket1: TServerSocket
    Active = False
    Port = 54321
    ServerType = stNonBlocking
    OnClientRead = ServerSocket1ClientRead
    Left = 448
  end
end
