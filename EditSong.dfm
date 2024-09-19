object EditSongForm: TEditSongForm
  Left = 517
  Top = 240
  Width = 579
  Height = 525
  Caption = 'Edit song'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu
  OldCreateOrder = False
  OnActivate = FormActivate
  OnDeactivate = FormDeactivate
  OnHide = FormHide
  OnResize = FormResize
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object PanelBottom: TPanel
    Left = 0
    Top = 397
    Width = 571
    Height = 50
    Align = alBottom
    TabOrder = 2
    DesignSize = (
      571
      50)
    object LabelAllowedTags: TLabel
      Left = 8
      Top = 32
      Width = 497
      Height = 13
      Caption = 
        'Allowed  HTML tags in song text : <b> </b> <i> </i> <H2> </H2> <' +
        'H3> </H3> <H4> </H4> <translation>'
    end
    object LabelCopyRight: TLabel
      Left = 18
      Top = 12
      Width = 50
      Height = 13
      Alignment = taRightJustify
      Caption = 'Copy right:'
    end
    object EditCopyRight: TEdit
      Left = 72
      Top = 8
      Width = 491
      Height = 21
      Anchors = [akLeft, akTop, akRight, akBottom]
      TabOrder = 0
      OnChange = EditChange
    end
  end
  object PanelTop: TPanel
    Left = 0
    Top = 0
    Width = 571
    Height = 89
    Align = alTop
    TabOrder = 0
    object LabelSongText: TLabel
      Left = 8
      Top = 64
      Width = 48
      Height = 13
      Caption = 'Song text:'
    end
    object LabelSongTitle: TLabel
      Left = 21
      Top = 33
      Width = 47
      Height = 13
      Alignment = taRightJustify
      Caption = 'Song title:'
    end
    object LabelToneHeight: TLabel
      Left = 11
      Top = 10
      Width = 60
      Height = 13
      Alignment = taRightJustify
      Caption = 'Tone height:'
    end
    object EditToneHeight: TEdit
      Left = 75
      Top = 6
      Width = 121
      Height = 21
      TabOrder = 0
      OnChange = EditChange
    end
    object EditSongTitle: TEdit
      Left = 75
      Top = 32
      Width = 297
      Height = 21
      TabOrder = 1
      OnChange = EditChange
    end
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 447
    Width = 571
    Height = 24
    Panels = <>
    SimplePanel = True
  end
  object PanelMiddle: TPanel
    Left = 0
    Top = 89
    Width = 571
    Height = 308
    Align = alClient
    TabOrder = 1
    object MemoSongText: TMemo
      Left = 1
      Top = 1
      Width = 569
      Height = 306
      Align = alClient
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -35
      Font.Name = 'Times New Roman'
      Font.Style = []
      ParentFont = False
      ScrollBars = ssBoth
      TabOrder = 0
      OnChange = EditChange
      OnDblClick = MemoSongTextDblClick
    end
  end
  object MainMenu: TMainMenu
    Left = 387
    Top = 1
    object File1: TMenuItem
      Caption = 'File'
      object New1: TMenuItem
        Caption = 'New'
        OnClick = New1Click
      end
      object OPen1: TMenuItem
        Caption = 'Open'
        OnClick = OPen1Click
      end
      object Save1: TMenuItem
        Caption = 'Save'
        OnClick = Save1Click
      end
      object Saveas1: TMenuItem
        Caption = 'Save as'
        OnClick = Saveas1Click
      end
      object Exit1: TMenuItem
        Caption = 'Exit'
        OnClick = Exit1Click
      end
    end
    object Font1: TMenuItem
      Caption = 'Font'
      object Selectfont1: TMenuItem
        Caption = 'Select font'
        OnClick = Selectfont1Click
      end
      object CourierNew1: TMenuItem
        Caption = 'Courier New 16'
        OnClick = CourierNew1Click
      end
    end
    object Tags1: TMenuItem
      Caption = 'Tags'
      object Addacc1: TMenuItem
        Caption = 'Add <acc>'
        OnClick = Addacc1Click
      end
      object Removeacc1: TMenuItem
        Caption = 'Remove <acc>'
        OnClick = Removeacc1Click
      end
    end
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = 'txt'
    Filter = 'Song text(*.txt)|*.txt;'
    Left = 424
  end
  object OpenDialog1: TOpenDialog
    DefaultExt = 'txt'
    Filter = 'Song text(*.txt)|*.txt;'
    Left = 456
  end
  object FontDialog1: TFontDialog
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    MinFontSize = 0
    MaxFontSize = 0
    Left = 496
  end
end
