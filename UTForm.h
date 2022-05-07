//---------------------------------------------------------------------------

#ifndef UTFormH
#define UTFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <Grids.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TOpenDialog *OpenDialog1;
        TSaveDialog *SaveDialog1;
        TGroupBox *Group_Keys;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TEdit *KEY_N;
        TEdit *KEY_E;
        TEdit *KEY_D;
        TEdit *Edit4;
        TUpDown *UpDown1;
        TButton *Button1;
        TGroupBox *Group_Code;
        TMemo *Memo1;
        TButton *Button3;
        TGroupBox *Group_Decode;
        TMemo *Memo2;
        TButton *Button5;
        TMemo *History;
        TButton *Export_Publ;
        TButton *Export_Priv;
        TButton *Import_Publ;
        TButton *Import_Priv;
        TRadioGroup *RadioGroup1;
        TRadioButton *RadioButton1;
        TRadioButton *RadioButton2;
        TGroupBox *Group_Shifr;
        TMemo *Memo3;
        TButton *Button6;
        TButton *Button8;
        TButton *Button2;
        TButton *Button4;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
                   void __fastcall Button4Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall Export_PublClick(TObject *Sender);
        void __fastcall Export_PrivClick(TObject *Sender);
        void __fastcall Import_PublClick(TObject *Sender);
        void __fastcall Import_PrivClick(TObject *Sender);
        void __fastcall Button7Click(TObject *Sender);
        void __fastcall RadioGroup1Click(TObject *Sender);
        void __fastcall RadioButton1Click(TObject *Sender);
        void __fastcall RadioButton2Click(TObject *Sender);
        void __fastcall Button8Click(TObject *Sender);
        void __fastcall Edit4Change(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall UpDown1Click(TObject *Sender, TUDBtnType Button);

public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
