//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm2(TComponent* Owner);
	void __fastcall ButtonKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void Solve();
	bool Right();
	void Clean();
	void UnClean();
	void OutPut();
	void GetInput();
};
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
class House
{
	public :
		bool H[9];
		int Tag;
};

//---------------------------------------------------------------------------
#endif
