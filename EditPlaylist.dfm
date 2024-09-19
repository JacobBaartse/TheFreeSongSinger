object FormEditPlaylist: TFormEditPlaylist
  Left = 481
  Top = 655
  Width = 277
  Height = 334
  BorderIcons = [biSystemMenu]
  Caption = 'Edit playlist'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnActivate = FormActivate
  OnDeactivate = FormDeactivate
  PixelsPerInch = 96
  TextHeight = 13
  object PlayListEdit: TMemo
    Left = 0
    Top = 0
    Width = 269
    Height = 300
    Align = alClient
    TabOrder = 0
    WordWrap = False
  end
end
