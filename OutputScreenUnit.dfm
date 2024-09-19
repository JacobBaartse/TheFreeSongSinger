object OutputScreen: TOutputScreen
  Left = 294
  Top = 125
  Width = 556
  Height = 350
  BorderIcons = [biSystemMenu, biMinimize, biMaximize, biHelp]
  Caption = 'Output screen'
  Color = clNavy
  TransparentColorValue = clNavy
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PopupMenu = PopupMenu1
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Image1: TImage
    Left = 0
    Top = 185
    Width = 548
    Height = 131
    Align = alClient
  end
  object Image2: TImage
    Left = 0
    Top = 185
    Width = 548
    Height = 131
    Align = alClient
  end
  object LabelMoveMessage: TLabel
    Left = 8
    Top = 8
    Width = 292
    Height = 32
    Caption = 
      'Move this screen to the beamer output, resize it to the correct ' +
      'size and press start.'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWhite
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    WordWrap = True
  end
  object ImageScratchPad: TImage
    Left = 0
    Top = 0
    Width = 548
    Height = 185
    Align = alTop
    Visible = False
  end
  object Timer1: TTimer
    Interval = 50
    OnTimer = Timer1Timer
    Left = 8
    Top = 48
  end
  object PopupMenu1: TPopupMenu
    Left = 64
    Top = 48
    object Exit1: TMenuItem
      Caption = 'Exit'
      OnClick = Exit1Click
    end
  end
end
