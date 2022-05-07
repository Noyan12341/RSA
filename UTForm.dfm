object Form1: TForm1
  Left = 233
  Top = 202
  BorderStyle = bsSingle
  Caption = 'RSA'
  ClientHeight = 565
  ClientWidth = 451
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Group_Keys: TGroupBox
    Left = 5
    Top = 45
    Width = 441
    Height = 105
    Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1099' '#1082#1083#1102#1095#1072
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    object Label2: TLabel
      Left = 8
      Top = 21
      Width = 8
      Height = 13
      Caption = 'N'
    end
    object Label3: TLabel
      Left = 8
      Top = 70
      Width = 7
      Height = 13
      Caption = 'E'
    end
    object Label4: TLabel
      Left = 8
      Top = 46
      Width = 8
      Height = 13
      Caption = 'D'
    end
    object Label5: TLabel
      Left = 149
      Top = 73
      Width = 67
      Height = 13
      Caption = #1044#1083#1080#1085#1072' '#1082#1083#1102#1095#1072
    end
    object KEY_N: TEdit
      Left = 24
      Top = 19
      Width = 160
      Height = 21
      TabOrder = 0
    end
    object KEY_E: TEdit
      Left = 24
      Top = 68
      Width = 41
      Height = 21
      TabOrder = 1
    end
    object KEY_D: TEdit
      Left = 24
      Top = 44
      Width = 160
      Height = 21
      TabOrder = 2
    end
    object Edit4: TEdit
      Left = 220
      Top = 70
      Width = 49
      Height = 21
      ReadOnly = True
      TabOrder = 3
      Text = '16'
      OnChange = Edit4Change
    end
    object UpDown1: TUpDown
      Left = 269
      Top = 70
      Width = 16
      Height = 21
      Associate = Edit4
      Min = 8
      Max = 512
      Increment = 8
      Position = 16
      TabOrder = 4
      Wrap = False
      OnClick = UpDown1Click
    end
    object Button1: TButton
      Left = 193
      Top = 16
      Width = 92
      Height = 49
      Caption = #1043#1077#1085#1077#1088#1072#1094#1080#1103
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 5
      OnClick = Button1Click
    end
    object Export_Publ: TButton
      Left = 296
      Top = 62
      Width = 140
      Height = 17
      Caption = #1069#1082#1089#1087#1086#1088#1090' '#1086#1090#1082#1088#1099#1090#1086#1075#1086' '#1082#1083#1102#1095#1072
      Enabled = False
      TabOrder = 6
      OnClick = Export_PublClick
    end
    object Export_Priv: TButton
      Left = 296
      Top = 81
      Width = 140
      Height = 17
      Caption = #1069#1082#1089#1087#1086#1088#1090' '#1079#1072#1082#1088#1099#1090#1086#1075#1086' '#1082#1083#1102#1095#1072
      Enabled = False
      TabOrder = 7
      OnClick = Export_PrivClick
    end
    object Import_Publ: TButton
      Left = 296
      Top = 9
      Width = 140
      Height = 17
      Caption = #1048#1084#1087#1086#1088#1090' '#1086#1090#1082#1088#1099#1090#1086#1075#1086' '#1082#1083#1102#1095#1072
      TabOrder = 8
      OnClick = Import_PublClick
    end
    object Import_Priv: TButton
      Left = 296
      Top = 28
      Width = 140
      Height = 17
      Caption = #1048#1084#1087#1086#1088#1090' '#1079#1072#1082#1088#1099#1090#1086#1075#1086' '#1082#1083#1102#1095#1072
      TabOrder = 9
      OnClick = Import_PrivClick
    end
  end
  object Group_Code: TGroupBox
    Left = 5
    Top = 160
    Width = 441
    Height = 126
    Caption = #1064#1080#1092#1088#1086#1074#1072#1085#1080#1077
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    object Memo1: TMemo
      Left = 8
      Top = 37
      Width = 425
      Height = 81
      TabOrder = 0
    end
    object Button3: TButton
      Left = 8
      Top = 17
      Width = 80
      Height = 17
      Caption = #1048#1084#1087#1086#1088#1090' '#1080#1079' .txt'
      TabOrder = 1
      OnClick = Button3Click
    end
  end
  object Group_Decode: TGroupBox
    Left = 5
    Top = 320
    Width = 441
    Height = 125
    Caption = #1056#1072#1089#1096#1080#1092#1088#1086#1074#1072#1085#1080#1077
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    Visible = False
    object Memo2: TMemo
      Left = 8
      Top = 37
      Width = 424
      Height = 81
      TabOrder = 0
    end
    object Button5: TButton
      Left = 350
      Top = 17
      Width = 80
      Height = 17
      Caption = #1069#1082#1089#1087#1086#1088#1090' '#1074' .txt'
      Enabled = False
      TabOrder = 1
      OnClick = Button5Click
    end
  end
  object History: TMemo
    Left = 5
    Top = 454
    Width = 441
    Height = 105
    ReadOnly = True
    ScrollBars = ssBoth
    TabOrder = 3
  end
  object RadioGroup1: TRadioGroup
    Left = 5
    Top = 5
    Width = 241
    Height = 41
    Caption = #1056#1077#1078#1080#1084
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 4
    OnClick = RadioGroup1Click
  end
  object RadioButton1: TRadioButton
    Left = 21
    Top = 21
    Width = 89
    Height = 17
    Caption = #1064#1080#1092#1088#1086#1074#1072#1085#1080#1077
    Checked = True
    TabOrder = 5
    TabStop = True
    OnClick = RadioButton1Click
  end
  object RadioButton2: TRadioButton
    Left = 133
    Top = 21
    Width = 105
    Height = 17
    Caption = #1056#1072#1089#1096#1080#1092#1088#1086#1074#1072#1085#1080#1077
    TabOrder = 6
    OnClick = RadioButton2Click
  end
  object Group_Shifr: TGroupBox
    Left = 5
    Top = 320
    Width = 441
    Height = 125
    Caption = #1047#1072#1096#1080#1092#1088#1086#1074#1072#1085#1085#1099#1081' '#1090#1077#1082#1089#1090
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 7
    object Memo3: TMemo
      Left = 8
      Top = 37
      Width = 425
      Height = 81
      TabOrder = 0
    end
    object Button6: TButton
      Left = 350
      Top = 17
      Width = 80
      Height = 17
      Caption = #1069#1082#1089#1087#1086#1088#1090' '#1074' .txt'
      Enabled = False
      TabOrder = 1
      OnClick = Button7Click
    end
    object Button8: TButton
      Left = 8
      Top = 17
      Width = 80
      Height = 17
      Caption = #1048#1084#1087#1086#1088#1090' '#1080#1079' .txt'
      TabOrder = 2
      Visible = False
      OnClick = Button8Click
    end
  end
  object Button2: TButton
    Left = 168
    Top = 293
    Width = 113
    Height = 25
    Caption = #1047#1072#1096#1080#1092#1088#1086#1074#1072#1090#1100
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 8
    OnClick = Button2Click
  end
  object Button4: TButton
    Left = 168
    Top = 293
    Width = 113
    Height = 25
    Caption = #1056#1072#1089#1096#1080#1092#1088#1086#1074#1072#1090#1100
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 9
    Visible = False
    OnClick = Button4Click
  end
  object OpenDialog1: TOpenDialog
    Left = 413
    Top = 5
  end
  object SaveDialog1: TSaveDialog
    Left = 373
    Top = 5
  end
end
