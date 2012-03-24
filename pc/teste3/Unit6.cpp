//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit6.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//#pragma link "JvExMask"
//#pragma link "JvToolEdit"
#pragma resource "*.dfm"
TForm6 *Form6;
//---------------------------------------------------------------------------
__fastcall TForm6::TForm6(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm6::Button1Click(TObject *Sender)
{
	if (OpenDialog->Execute() == false) {
		return;
	}

	AnsiString AName = OpenDialog->FileName;
	Edit1->Text = AName;

	img->Picture->Bitmap->LoadFromFile(AName);

	Graphics::TBitmap * bmp = img->Picture->Bitmap;

	bmp->PixelFormat = pf24bit;


	memo->Lines->Clear();

	int size = bmp->Width * bmp->Height * 3;
	memo->Lines->Add("#define INVERT_DATA           1");
	memo->Lines->Add("#define NUM_LINES             " + IntToStr(bmp->Height));
	memo->Lines->Add("#define NUM_COLS              " + IntToStr(bmp->Width));
	memo->Lines->Add("#define NUM_PIXELS            " + IntToStr(size));

	AnsiString txt = "unsigned char img_data[NUM_PIXELS] = {";
	AnsiString virg = "";


	memo->Lines->Add(txt);
	txt = "    ";

	for (int x = 0; x < bmp->Width; x++) {
		for (int y = 0; y < bmp->Height; y++) {
			TColor color = bmp->Canvas->Pixels[x][y];
			unsigned char b = (color & 0xFF0000) >> 16;
			unsigned char g = (color & 0xFF00) >> 8;
			unsigned char r = color & 0xFF;
			txt += virg + IntToStr(r);
			virg = ",";
			txt += virg + IntToStr(g);
			txt += virg + IntToStr(b) + " ";
		}
		memo->Lines->Add(txt);
		txt = "    ";

	}
	memo->Lines->Add(txt + "};");
	memo->SelectAll();
	memo->CopyToClipboard();

}
//---------------------------------------------------------------------------

