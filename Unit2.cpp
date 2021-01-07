﻿//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
#include "Unit1.h"
#include <fstream>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
TButton ***Button;
House Board[9][9];
bool Solved = false;
int Operations = 0;
//---------------------------------------------------------------------------
void TForm2::GetInput()
{
	ifstream file("Templates/4.txt");
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			file >> Board[i][j].Tag, Board[i][j].Tag--;
	file.close();
}
//---------------------------------------------------------------------------
void TForm2::Clean()
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			if (Board[i][j].Tag != -1)
			{
				for (int k = 0; k < 9; k++)
					Board[k][j].H[Board[i][j].Tag] = Board[i][k].H[Board[i][j].Tag] = false;
				for (int k = 0; k < 9; k++)
					Board[i / 3 * 3 + k / 3][j / 3  * 3 + k % 3].H[Board[i][j].Tag] = false;
			}
}
//---------------------------------------------------------------------------
void TForm2::UnClean()
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			for (int k = 0; k < 9; k++)
				Board[i][j].H[k] = true;
	Clean();
}
//---------------------------------------------------------------------------
void TForm2::OutPut()
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			if (Board[i][j].Tag != -1)
				Button[i][j]->Caption = IntToStr(Board[i][j].Tag + 1);
			else
				Button[i][j]->Caption = "";
}
//---------------------------------------------------------------------------
void TForm2::Solve()
{
	Operations++;
	int x, y;
	bool check = false;
	for (int i = 0; i < 81; i++)
		if (Board[i / 9][i % 9].Tag == -1)
		{
			check = true;
			x = i / 9;
			y = i % 9;
			break;
		}
	if (!check)
	{
		Solved = true;
		OutPut();
		return;
	}
	for (int i = 0; i < 9; i++)
		if (Board[x][y].H[i])
		{
			int ll = Board[x][y].H[i];
			Board[x][y].Tag = i;
			Clean();
			Solve();
			if (Solved)
				return;
			Board[x][y].Tag = -1;
			UnClean();
		}
}
//---------------------------------------------------------------------------
bool TForm2::Right()
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			if (Board[i][j].Tag != -1)
			{
				for (int k = 0; k < 9; k++)
					if (Board[k][j].Tag == Board[i][j].Tag && k != i) return false;
				for (int k = 0; k < 9; k++)
					if (Board[i][k].Tag == Board[i][j].Tag && k != j) return false;
				for (int k = 0; k < 9; k++)
					if (Board[i / 3  * 3 + k / 3][j / 3 * 3 + k % 3].Tag == Board[i][j].Tag)
						if (i / 3  * 3 + k / 3 != i || j / 3 * 3 + k % 3 != j)
							return false;
			}
	return true;
}
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner): TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm2::ButtonKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	int x = dynamic_cast<TButton *>(Sender)->Tag / 9;
	int y = dynamic_cast<TButton *>(Sender)->Tag % 9;
	if (Key == VK_NUMPAD0)
		Board[x][y].Tag = -1;
	if (Key == VK_NUMPAD1)
		Board[x][y].Tag = 0;
	if (Key == VK_NUMPAD2)
		Board[x][y].Tag = 1;
	if (Key == VK_NUMPAD3)
		Board[x][y].Tag = 2;
	if (Key == VK_NUMPAD4)
		Board[x][y].Tag = 3;
	if (Key == VK_NUMPAD5)
		Board[x][y].Tag = 4;
	if (Key == VK_NUMPAD6)
		Board[x][y].Tag = 5;
	if (Key == VK_NUMPAD7)
		Board[x][y].Tag = 6;
	if (Key == VK_NUMPAD8)
		Board[x][y].Tag = 7;
	if (Key == VK_NUMPAD9)
		Board[x][y].Tag = 8;
	if (Board[x][y].Tag != -1)
		Button[x][y]->Caption = IntToStr(Board[x][y].Tag + 1);
	else
		Button[x][y]->Caption = "";
	if (Board[x][y].Tag != -1)
		Button[x][y]->Font->Size = Button[x][y]->Width / 9 * 5;
	else
		Button[x][y]->Font->Size = Button[x][y]->Width / 3;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormCreate(TObject *Sender)
{
	Button = new TButton**[9];
	int Gap = 60;
	Button1->Left = 9 * Gap + 13;
	Button2->Left = 9 * Gap + 13;
	Button3->Left = 9 * Gap + 13;
	Button1->Height = 3 * Gap;
	Button2->Height = 3 * Gap;
	Button3->Height = 3 * Gap;
	for (int i = 0; i < 9; i++) {
		Button[i] = new TButton*[9];
		for (int j = 0; j < 9; j++) {
			Button[i][j] = new TButton(this);
			Button[i][j]->Parent = this;
			Button[i][j]->Width = Gap;
			Button[i][j]->Height = Gap;
			Button[i][j]->Left = j * Button[i][j]->Width + j / 3 * 5;
			Button[i][j]->Top = i * Button[i][j]->Height + i / 3 * 5;
			Button[i][j]->Tag = i * 9 + j;
			Button[i][j]->OnKeyDown = ButtonKeyDown;
			Button[i][j]->Font->Size = Button[i][j]->Width / 3;
			Button[i][j]->Font->Quality = Button1->Font->Quality;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button1Click(TObject *Sender)
{
	if (Right())
	  UnClean(), Solve();
	else
		ShowMessage("!!SUDOKU DOROST NIST!!");
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormClose(TObject *Sender, TCloseAction &Action)
{
	Form1->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button2Click(TObject *Sender)
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			Board[i][j].Tag = -1;
	UnClean();
	Solved = false;
	OutPut();
}
//---------------------------------------------------------------------------


void __fastcall TForm2::FormActivate(TObject *Sender)
{
	UnClean();
	GetInput();
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			if (Board[i][j].Tag != -1)
				Button[i][j]->Font->Size = Button[i][j]->Width / 9 * 5;
	OutPut();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button3Click(TObject *Sender)
{
	Form1->Visible = true;
	Form2->Visible = false;
}
//---------------------------------------------------------------------------

