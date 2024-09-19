object DirectEditForm: TDirectEditForm
  Left = 753
  Top = 160
  Width = 485
  Height = 492
  Caption = 'Direct edit'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnActivate = FormActivate
  OnDeactivate = FormDeactivate
  OnShow = FormShow
  DesignSize = (
    477
    458)
  PixelsPerInch = 96
  TextHeight = 13
  object TitleLabel: TLabel
    Left = 8
    Top = 40
    Width = 26
    Height = 13
    Caption = 'Title :'
  end
  object LineCountLabel: TLabel
    Left = 264
    Top = 40
    Width = 132
    Height = 13
    Caption = 'Number of lines on beamer :'
  end
  object TitleEdit: TEdit
    Left = 8
    Top = 55
    Width = 233
    Height = 21
    TabOrder = 0
    OnKeyDown = TextMemoKeyDown
    OnKeyUp = TextMemoKeyUp
  end
  object TextMemo: TMemo
    Left = 8
    Top = 80
    Width = 459
    Height = 377
    Anchors = [akLeft, akTop, akRight, akBottom]
    TabOrder = 2
    OnKeyDown = TextMemoKeyDown
    OnKeyUp = TextMemoKeyUp
  end
  object LineCountComboBox: TComboBox
    Left = 264
    Top = 56
    Width = 41
    Height = 19
    Style = csOwnerDrawFixed
    DropDownCount = 14
    ItemHeight = 13
    ItemIndex = 4
    TabOrder = 1
    Text = '5'
    OnKeyDown = TextMemoKeyDown
    OnKeyUp = TextMemoKeyUp
    Items.Strings = (
      '1'
      '2'
      '3'
      '4'
      '5'
      '6'
      '7'
      '8'
      '9'
      '10'
      '11'
      '12'
      '13'
      '14')
  end
end
