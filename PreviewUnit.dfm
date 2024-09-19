object Preview: TPreview
  Left = 847
  Top = 131
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = 'Preview'
  ClientHeight = 277
  ClientWidth = 350
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Image1: TImage
    Left = 0
    Top = 0
    Width = 350
    Height = 277
    Align = alClient
  end
  object Image2: TImage
    Left = 0
    Top = 0
    Width = 350
    Height = 277
    Align = alClient
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 50
    OnTimer = Timer1Timer
    Left = 296
    Top = 32
  end
end
