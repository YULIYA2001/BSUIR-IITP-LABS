//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TEdit *QueueSizeEdit;
	TEdit *AddElementEdit;
	TLabel *Label1;
	TButton *CreateButton;
	TButton *PrintButton;
	TButton *AddToEndButton;
	TButton *TakeFromBeginButton;
	TButton *IsEmptyButton;
	TButton *CleanButton;
	TLabel *Label2;
	TLabel *Label3;
	TListBox *ShowListBox;
	TLabel *Label4;
	TMemo *AddQueueMemo;
	TLabel *Label5;
	TPanel *Panel1;
	TLabel *Label6;
	TLabel *Label7;
	TEdit *ListSizeEdit;
	TButton *MySolutionButton;
	TListBox *ShowMyTaskListBox;
	void __fastcall CreateButtonClick(TObject *Sender);
	void __fastcall PrintButtonClick(TObject *Sender);
	void __fastcall AddToEndButtonClick(TObject *Sender);
	void __fastcall TakeFromBeginButtonClick(TObject *Sender);
	void __fastcall IsEmptyButtonClick(TObject *Sender);
	void __fastcall CleanButtonClick(TObject *Sender);
	void __fastcall QueueSizeEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall MySolutionButtonClick(TObject *Sender);
	void __fastcall AddQueueMemoKeyPress(TObject *Sender, System::WideChar &Key);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
