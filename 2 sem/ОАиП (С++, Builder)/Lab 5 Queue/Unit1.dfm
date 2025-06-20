object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Queue'
  ClientHeight = 323
  ClientWidth = 550
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 81
    Height = 13
    Caption = #1056#1072#1079#1084#1077#1088' '#1086#1095#1077#1088#1077#1076#1080
  end
  object Label2: TLabel
    Left = 88
    Top = 38
    Width = 210
    Height = 14
    Caption = #1054#1089#1085#1086#1074#1085#1099#1077' '#1086#1087#1077#1088#1072#1094#1080#1080' '#1089' '#1086#1095#1077#1088#1077#1076#1100#1102' '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = [fsBold, fsItalic]
    ParentFont = False
  end
  object Label3: TLabel
    Left = 128
    Top = 120
    Width = 129
    Height = 13
    Caption = #1069#1083#1077#1084#1077#1085#1090' '#1076#1083#1103' '#1076#1086#1073#1072#1074#1083#1077#1085#1080#1103
  end
  object Label4: TLabel
    Left = 8
    Top = 54
    Width = 61
    Height = 16
    Caption = #1054#1095#1077#1088#1077#1076#1100' '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = [fsBold, fsItalic]
    ParentFont = False
  end
  object Label5: TLabel
    Left = 315
    Top = 13
    Width = 70
    Height = 16
    Caption = #1055#1088#1086#1089#1084#1086#1090#1088' '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = [fsBold, fsItalic]
    ParentFont = False
  end
  object QueueSizeEdit: TEdit
    Left = 9
    Top = 27
    Width = 73
    Height = 21
    NumbersOnly = True
    TabOrder = 0
    Text = '0'
    OnKeyPress = QueueSizeEditKeyPress
  end
  object AddElementEdit: TEdit
    Left = 159
    Top = 136
    Width = 73
    Height = 21
    NumbersOnly = True
    TabOrder = 1
  end
  object CreateButton: TButton
    Left = 120
    Top = 58
    Width = 153
    Height = 25
    Hint = #1055#1088#1080' '#1087#1086#1074#1090#1086#1088#1085#1086#1084' '#1089#1086#1079#1076#1072#1085#1080#1080' '#1089#1090#1072#1088#1072#1103' '#1086#1095#1077#1088#1077#1076#1100' '#1091#1076#1072#1083#1103#1077#1090#1089#1103
    Caption = #1057#1086#1079#1076#1072#1090#1100
    ParentShowHint = False
    ShowHint = True
    TabOrder = 2
    OnClick = CreateButtonClick
  end
  object PrintButton: TButton
    Left = 120
    Top = 89
    Width = 153
    Height = 25
    Caption = #1055#1077#1095#1072#1090#1100
    TabOrder = 3
    OnClick = PrintButtonClick
  end
  object AddToEndButton: TButton
    Left = 120
    Top = 163
    Width = 153
    Height = 25
    Caption = #1044#1086#1073#1072#1074#1080#1090#1100' ('#1074' '#1082#1086#1085#1077#1094')'
    TabOrder = 4
    OnClick = AddToEndButtonClick
  end
  object TakeFromBeginButton: TButton
    Left = 120
    Top = 194
    Width = 153
    Height = 25
    Caption = #1048#1079#1074#1083#1077#1095#1100' ('#1080#1079' '#1085#1072#1095#1072#1083#1072')'
    TabOrder = 5
    OnClick = TakeFromBeginButtonClick
  end
  object IsEmptyButton: TButton
    Left = 120
    Top = 225
    Width = 153
    Height = 25
    Caption = #1055#1088#1086#1074#1077#1088#1080#1090#1100' '#1087#1091#1089#1090#1086#1090#1091
    TabOrder = 6
    OnClick = IsEmptyButtonClick
  end
  object CleanButton: TButton
    Left = 120
    Top = 256
    Width = 153
    Height = 25
    Caption = #1054#1095#1080#1089#1090#1080#1090#1100
    TabOrder = 7
    OnClick = CleanButtonClick
  end
  object ShowListBox: TListBox
    Left = 304
    Top = 35
    Width = 89
    Height = 280
    Columns = 1
    ItemHeight = 13
    TabOrder = 8
  end
  object AddQueueMemo: TMemo
    Left = 8
    Top = 76
    Width = 73
    Height = 239
    ScrollBars = ssVertical
    TabOrder = 9
    OnKeyPress = AddQueueMemoKeyPress
  end
  object Panel1: TPanel
    Left = 413
    Top = 8
    Width = 129
    Height = 307
    Color = clSilver
    ParentBackground = False
    TabOrder = 10
    object Label6: TLabel
      Left = 33
      Top = 5
      Width = 70
      Height = 16
      Caption = #1042#1072#1088#1080#1072#1085#1090' 6 '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold, fsItalic]
      ParentFont = False
    end
    object Label7: TLabel
      Left = 31
      Top = 27
      Width = 72
      Height = 13
      Caption = #1056#1072#1079#1084#1077#1088' '#1089#1087#1080#1089#1082#1072
    end
    object ListSizeEdit: TEdit
      Left = 38
      Top = 39
      Width = 59
      Height = 21
      NumbersOnly = True
      TabOrder = 0
      Text = '0'
    end
    object MySolutionButton: TButton
      Left = 19
      Top = 66
      Width = 92
      Height = 25
      Caption = #1056#1077#1096#1077#1085#1080#1077
      TabOrder = 1
      OnClick = MySolutionButtonClick
    end
    object ShowMyTaskListBox: TListBox
      Left = 19
      Top = 97
      Width = 92
      Height = 200
      ItemHeight = 13
      TabOrder = 2
    end
  end
end
