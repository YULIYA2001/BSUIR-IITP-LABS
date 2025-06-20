//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TImage *Image1;
	TRadioGroup *RadioGroup1;
	TButton *Button1;
	TTimer *Timer1;
	TTimer *Timer2;
	TTimer *Timer3;
	TTimer *Timer4;
	TPanel *Panel3;
	TButton *Button8;
	TButton *Button9;
	TButton *Button10;
	TTimer *Timer5;
	TTimer *Timer6;
	TPanel *Panel4;
	TLabel *Label8;
	TButton *Button11;
	TButton *Button12;
	TLabel *Label6;
	TPanel *Panel5;
	TLabel *Label3;
	TEdit *Edit1;
	TLabel *Label4;
	TButton *Button2;
	TLabel *Label5;
	TEdit *Edit2;
	TPanel *Panel6;
	TLabel *Label1;
	TPanel *Panel1;
	TPanel *Panel7;
	TLabel *Label2;
	TPanel *Panel2;
	TPanel *Panel8;
	TLabel *Label7;
	TButton *Button3;
	TButton *Button7;
	TButton *Button4;
	TButton *Button6;
	TButton *Button5;
	TTimer *Timer7;
	TPanel *Panel9;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label11;
	TEdit *Edit3;
	TButton *Button13;
	TEdit *Edit4;
	TEdit *Edit5;
	TEdit *Edit6;
	TEdit *Edit7;
	TLabel *Label12;
	TLabel *Label13;
	TLabel *Label14;
	TLabel *Label15;
	TLabel *Label16;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Image1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall Image1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall Timer2Timer(TObject *Sender);
	void __fastcall Timer3Timer(TObject *Sender);
	void __fastcall Timer4Timer(TObject *Sender);
	void __fastcall Button8Click(TObject *Sender);
	void __fastcall Button10Click(TObject *Sender);
	void __fastcall Timer5Timer(TObject *Sender);
	void __fastcall Timer6Timer(TObject *Sender);
	void __fastcall Button9Click(TObject *Sender);
	void __fastcall Button11Click(TObject *Sender);
	void __fastcall Button12Click(TObject *Sender);
	void __fastcall Timer7Timer(TObject *Sender);
	void __fastcall Button13Click(TObject *Sender);
	void __fastcall RadioGroup1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
