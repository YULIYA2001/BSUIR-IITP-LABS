//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Grids.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TMemo *ShowInfMemo;
	TTreeView *ShowTreeTreeView;
	TStringGrid *InitialStringGrid;
	TButton *CreateFromArrayButton;
	TLabel *Label1;
	TLabel *Label2;
	TButton *MakeBallanceButton;
	TButton *AddButton;
	TButton *SearchByKeyButton;
	TButton *DeleteByKeyButton;
	TButton *ShowInTreeViewButton;
	TButton *PrPrintButton;
	TButton *ObPrintButton;
	TButton *SimPrintButton;
	TLabel *Label3;
	TEdit *EnterKeyEdit;
	TButton *MyTaskButton;
	TButton *ExitButton;
	TLabel *Label4;
	TLabel *Label5;
	TEdit *EnterFioEdit;
	TLabel *Label6;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall InitialStringGridSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
	void __fastcall CreateFromArrayButtonClick(TObject *Sender);
	void __fastcall ExitButtonClick(TObject *Sender);
	void __fastcall ShowInTreeViewButtonClick(TObject *Sender);
	void __fastcall PrPrintButtonClick(TObject *Sender);
	void __fastcall ObPrintButtonClick(TObject *Sender);
	void __fastcall SimPrintButtonClick(TObject *Sender);
	void __fastcall AddButtonClick(TObject *Sender);
	void __fastcall DeleteByKeyButtonClick(TObject *Sender);
	void __fastcall SearchByKeyButtonClick(TObject *Sender);
	void __fastcall MyTaskButtonClick(TObject *Sender);
	void __fastcall MakeBallanceButtonClick(TObject *Sender);


private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
