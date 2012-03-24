object Form6: TForm6
  Left = 0
  Top = 0
  Caption = 'Teste'
  ClientHeight = 374
  ClientWidth = 557
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -14
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  DesignSize = (
    557
    374)
  PixelsPerInch = 120
  TextHeight = 17
  object img: TImage
    Left = 9
    Top = 43
    Width = 537
    Height = 32
    Margins.Left = 4
    Margins.Top = 4
    Margins.Right = 4
    Margins.Bottom = 4
    Anchors = [akLeft, akTop, akRight]
  end
  object memo: TMemo
    Left = 9
    Top = 83
    Width = 537
    Height = 282
    Margins.Left = 4
    Margins.Top = 4
    Margins.Right = 4
    Margins.Bottom = 4
    Anchors = [akLeft, akTop, akRight, akBottom]
    Lines.Strings = (
      'memo')
    ScrollBars = ssVertical
    TabOrder = 0
  end
  object Edit1: TEdit
    Left = 16
    Top = 16
    Width = 457
    Height = 25
    Anchors = [akLeft, akTop, akRight]
    TabOrder = 1
  end
  object Button1: TButton
    Left = 471
    Top = 11
    Width = 75
    Height = 25
    Anchors = [akTop, akRight]
    Caption = 'Select'
    TabOrder = 2
    OnClick = Button1Click
  end
  object OpenDialog: TOpenDialog
    DefaultExt = '.bmp'
    Filter = 'Windows bitmap|*.bmp|*.*|*.*'
    Left = 464
    Top = 32
  end
end
