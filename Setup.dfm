object SetupScreen: TSetupScreen
  Left = 1260
  Top = 190
  Width = 430
  Height = 500
  Caption = 'Setup'
  Color = clAppWorkSpace
  Constraints.MaxHeight = 500
  Constraints.MaxWidth = 430
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poDefaultPosOnly
  OnActivate = FormActivate
  OnDeactivate = FormDeactivate
  OnMouseWheelDown = FormMouseWheelDown
  OnMouseWheelUp = FormMouseWheelUp
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object StatusBar: TStatusBar
    Left = 0
    Top = 418
    Width = 414
    Height = 23
    Panels = <>
    SimplePanel = True
  end
  object Panel1: TPanel
    Left = 8
    Top = 8
    Width = 185
    Height = 401
    TabOrder = 1
    object ElementSel: TComboBox
      Left = 8
      Top = 8
      Width = 169
      Height = 21
      DropDownCount = 18
      ItemHeight = 13
      ItemIndex = 1
      TabOrder = 0
      Text = 'Song text'
      OnChange = ElementSelChange
      Items.Strings = (
        'All text'
        'Song text'
        'Normal text'
        'Old text'
        'Heading 2'
        'Heading 3'
        'Heading 4'
        'Translation'
        'Tone Height'
        'Song title'
        'Blink message'
        'Line pointer'
        'Current song'
        'Copy right'
        'Pause blink message')
    end
    object ActiveCheckBox: TCheckBox
      Left = 16
      Top = 40
      Width = 97
      Height = 17
      Caption = 'Active'
      TabOrder = 1
      OnClick = ActiveCheckBoxClick
    end
    object Panel3: TPanel
      Left = 8
      Top = 64
      Width = 169
      Height = 329
      TabOrder = 2
      object OutlineGroupBox: TGroupBox
        Left = 8
        Top = 224
        Width = 153
        Height = 97
        Caption = 'Outline'
        TabOrder = 2
        object OutlineLessButton: TButton
          Left = 8
          Top = 24
          Width = 65
          Height = 25
          Caption = 'Less'
          TabOrder = 0
          OnClick = OutlineLessButtonClick
        end
        object OutlineMoreButton: TButton
          Left = 80
          Top = 24
          Width = 65
          Height = 25
          Caption = 'More'
          TabOrder = 1
          OnClick = OutlineMoreButtonClick
        end
        object OutlineColorButton: TButton
          Left = 8
          Top = 56
          Width = 65
          Height = 25
          Caption = 'Color'
          TabOrder = 2
          OnClick = OutlineColorButtonClick
        end
      end
      object FontGroupBox: TGroupBox
        Left = 8
        Top = 8
        Width = 153
        Height = 81
        Caption = 'Font'
        TabOrder = 0
        object FontTypeButton: TButton
          Left = 8
          Top = 16
          Width = 65
          Height = 25
          Caption = 'Type'
          TabOrder = 0
          OnClick = FontTypeButtonClick
        end
        object FontColorButton: TButton
          Left = 80
          Top = 16
          Width = 65
          Height = 25
          Caption = 'Color'
          TabOrder = 1
          OnClick = FontColorButtonClick
        end
        object FontEnlargeButton: TButton
          Left = 80
          Top = 48
          Width = 65
          Height = 25
          Caption = 'Enlage'
          TabOrder = 3
          OnClick = FontEnlargeButtonClick
        end
        object FontReduceButton: TButton
          Left = 8
          Top = 48
          Width = 65
          Height = 25
          Caption = 'Reduce'
          TabOrder = 2
          OnClick = FontReduceButtonClick
        end
      end
      object PositionGroupBox: TGroupBox
        Left = 8
        Top = 96
        Width = 153
        Height = 121
        Caption = 'Position'
        TabOrder = 1
        object PositionUpButton: TButton
          Left = 62
          Top = 19
          Width = 25
          Height = 25
          Caption = '^'
          TabOrder = 0
          OnClick = PositionUpButtonClick
        end
        object PostionLeftButton: TButton
          Left = 30
          Top = 51
          Width = 25
          Height = 25
          Caption = '<'
          TabOrder = 1
          OnClick = PositionUpButtonClick
        end
        object PositionResetButton: TButton
          Left = 62
          Top = 51
          Width = 25
          Height = 25
          Caption = '><'
          TabOrder = 2
          OnClick = PositionUpButtonClick
        end
        object PositionRightButton: TButton
          Left = 94
          Top = 51
          Width = 25
          Height = 25
          Caption = '>'
          TabOrder = 3
          OnClick = PositionUpButtonClick
        end
        object PositionDownButton: TButton
          Left = 62
          Top = 83
          Width = 25
          Height = 25
          Caption = 'v'
          TabOrder = 4
          OnClick = PositionUpButtonClick
        end
      end
    end
  end
  object Panel2: TPanel
    Left = 208
    Top = 8
    Width = 185
    Height = 145
    TabOrder = 2
    object PictureSel: TComboBox
      Left = 8
      Top = 8
      Width = 169
      Height = 21
      ItemHeight = 13
      ItemIndex = 0
      TabOrder = 0
      Text = 'Back ground picture'
      OnChange = PictureSelChange
      Items.Strings = (
        'Back ground picture'
        'Pause picture')
    end
    object PictureSelectButton: TButton
      Left = 96
      Top = 80
      Width = 81
      Height = 25
      Caption = 'Select picture'
      TabOrder = 4
      OnClick = PictureSelectButtonClick
    end
    object ToolBar: TToolBar
      Left = 9
      Top = 113
      Width = 160
      Height = 29
      Align = alNone
      Caption = 'ToolBar'
      EdgeBorders = []
      ParentShowHint = False
      ShowHint = True
      TabOrder = 5
      object ToolButton1: TToolButton
        Left = 0
        Top = 2
        Width = 8
        Caption = 'ToolButton1'
        Style = tbsSeparator
      end
      object ToolButton2: TToolButton
        Left = 8
        Top = 2
        Hint = 'More contrast'
        Caption = 'ToolButton2'
        ImageIndex = 0
        OnClick = ToolButton2Click
      end
      object ToolButton3: TToolButton
        Left = 31
        Top = 2
        Hint = 'Reset contrast'
        Caption = 'ToolButton3'
        ImageIndex = 1
        OnClick = ToolButton3Click
      end
      object ToolButton4: TToolButton
        Left = 54
        Top = 2
        Hint = 'Less contrast'
        Caption = 'ToolButton4'
        ImageIndex = 2
        OnClick = ToolButton4Click
      end
      object ToolButton5: TToolButton
        Left = 77
        Top = 2
        Width = 8
        Caption = 'ToolButton5'
        ImageIndex = 2
        Style = tbsSeparator
      end
      object ToolButton6: TToolButton
        Left = 85
        Top = 2
        Hint = 'Less brightness'
        Caption = 'ToolButton6'
        ImageIndex = 3
        OnClick = ToolButton6Click
      end
      object ToolButton7: TToolButton
        Left = 108
        Top = 2
        Hint = 'Reset Brightness'
        Caption = 'ToolButton7'
        ImageIndex = 4
        OnClick = ToolButton7Click
      end
      object ToolButton8: TToolButton
        Left = 131
        Top = 2
        Hint = 'More brightness'
        Caption = 'ToolButton8'
        ImageIndex = 5
        OnClick = ToolButton8Click
      end
    end
    object ButtonBackgroundColor: TButton
      Left = 96
      Top = 40
      Width = 81
      Height = 25
      Caption = 'Color'
      TabOrder = 2
      OnClick = ButtonBackgroundColorClick
    end
    object CheckBoxTransparent: TCheckBox
      Left = 8
      Top = 40
      Width = 81
      Height = 17
      Caption = 'Transparent'
      TabOrder = 1
      OnClick = CheckBoxTransparentClick
    end
    object CheckBoxPicture: TCheckBox
      Left = 8
      Top = 80
      Width = 73
      Height = 17
      Caption = 'Picture'
      TabOrder = 3
      OnClick = CheckBoxPictureClick
    end
  end
  object Panel4: TPanel
    Left = 208
    Top = 168
    Width = 185
    Height = 241
    Caption = 'Panel4'
    TabOrder = 3
    object LineDistGroupBox: TGroupBox
      Left = 8
      Top = 8
      Width = 169
      Height = 65
      Caption = 'Line distance'
      TabOrder = 0
      object LineDistMoreButton: TButton
        Left = 88
        Top = 24
        Width = 65
        Height = 25
        Caption = 'More'
        TabOrder = 1
        OnClick = LineDistMoreButtonClick
      end
      object LineDistLessButton: TButton
        Left = 16
        Top = 24
        Width = 65
        Height = 25
        Caption = 'Less'
        TabOrder = 0
        OnClick = LineDistLessButtonClick
      end
    end
    object LineCountGroupBox: TGroupBox
      Left = 8
      Top = 80
      Width = 169
      Height = 65
      Caption = 'Line count'
      TabOrder = 1
      object LineCountMoreButton: TButton
        Left = 96
        Top = 24
        Width = 65
        Height = 25
        Caption = 'More'
        TabOrder = 1
        OnClick = LineCountMoreButtonClick
      end
      object LineCountLessButton: TButton
        Left = 16
        Top = 24
        Width = 65
        Height = 25
        Caption = 'Less'
        TabOrder = 0
        OnClick = LineCountLessButtonClick
      end
    end
    object MoreTextBlocksCheck: TCheckBox
      Left = 8
      Top = 152
      Width = 97
      Height = 17
      Caption = 'More text blocks'
      TabOrder = 2
      OnClick = MoreTextBlocksCheckClick
    end
    object LeftAlignCheckBox: TCheckBox
      Left = 8
      Top = 200
      Width = 97
      Height = 17
      Caption = 'Aling left'
      TabOrder = 3
      OnClick = LeftAlignCheckBoxClick
    end
    object SecondBlockOneLineCheckBox: TCheckBox
      Left = 8
      Top = 176
      Width = 169
      Height = 17
      Caption = 'Second block one line'
      TabOrder = 4
      OnClick = SecondBlockOneLineCheckBoxClick
    end
  end
  object MainMenu1: TMainMenu
    Left = 192
    Top = 192
    object File1: TMenuItem
      Caption = '&File'
      object Open1: TMenuItem
        Caption = '&Open'
        OnClick = Open1Click
      end
      object Save1: TMenuItem
        Caption = '&Save'
        OnClick = Save1Click
      end
      object Saveas1: TMenuItem
        Caption = 'Save &as'
        OnClick = Saveas1Click
      end
    end
    object Extra1: TMenuItem
      Caption = '&Extra'
      object Sampletext1: TMenuItem
        Caption = 'Sample text'
        OnClick = Sampletext1Click
      end
    end
  end
end
