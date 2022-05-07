//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UTForm.h"
#include "UTRSA.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
extern _INFO Info;
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
randomize();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
History->Lines->Add(TimeToStr(Time())+" =====��������� ������ ������=====");
TRSA a(Edit4->Text.ToInt());

char* tmp = a.KeyModul;
KEY_N->Text = AnsiString(tmp);
tmp = a.OpenKey;
KEY_E->Text = AnsiString(tmp);
tmp = a.SecretKey;
KEY_D->Text = AnsiString(tmp);

History->Lines->Add("��������� ������������: N=p*q="+(IntToStr(Info.InfoP))+"*"+IntToStr(Info.InfoQ)+"="+KEY_N->Text);
History->Lines->Add("��������� ������� ������: phi(N)=(p-1)*(q-1)="+FloatToStr(Info.InfoPhi));
History->Lines->Add("�������� �������� ����������: E="+KEY_E->Text);
History->Lines->Add("��������� ��������� ����������: D*E=1 mod phi(N);");
History->Lines->Add("D*"+KEY_E->Text+"=1 mod "+Info.InfoPhi+"; D="+KEY_D->Text);
History->Lines->Add("���� E, N - �������� ���� RSA (public key): "+KEY_E->Text+"; "+KEY_N->Text);
History->Lines->Add("���� D, N - ��������� ���� RSA (private key): "+KEY_D->Text+"; "+KEY_N->Text);
History->Lines->Add(TimeToStr(Time())+" =====��������� ������ ���������=====");
Button2->Enabled=True;
Export_Publ->Enabled=True;
Export_Priv->Enabled=True;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
if(Memo1->Text != "")
{
if (KEY_N->Text !="" || KEY_E->Text !="")
{
History->Lines->Add(TimeToStr(Time())+" =====������� ���������� �����=====");
TNumber n(KEY_N->Text.c_str());
TNumber e(KEY_E->Text.c_str());
TNumber d(KEY_D->Text.c_str());

THexString text;
text.AsCharString = Memo1->Text;

  TRSA a(n,e,Edit4->Text.ToInt());
  a.PlainText = text;
  Memo3->Text = a.CryptedText.AsHexString;
  Button6->Enabled = True;
  Button4->Enabled=True;

  History->Lines->Add(TimeToStr(Time())+" =====������� ���������� ��������=====");
}
else
ShowMessage("����������� �������� ����");
}
else
ShowMessage("����������� ����� ��� ����������");
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Button4Click(TObject *Sender)
{
if(Memo3->Text != "")
{
if (KEY_N->Text !="" || KEY_D->Text !="")
{
History->Lines->Add(TimeToStr(Time())+" =====������� ������������� �����=====");
TNumber n(KEY_N->Text.c_str());
TNumber e(KEY_E->Text.c_str());
TNumber d(KEY_D->Text.c_str());

THexString text;
text.AsHexString = Memo3->Text;

  TRSA a(n,e,d,Edit4->Text.ToInt());
  a.CryptedText = text;
  Memo2->Text = a.PlainText.AsCharString;
  Button5->Enabled = True;

  History->Lines->Add(TimeToStr(Time())+" =====������� ������������� ��������=====");
  }
else
ShowMessage("����������� �������� ����");

}
else
ShowMessage("����������� ����� ��� �������������");
}

//---------------------------------------------------------------------------



void __fastcall TForm1::Button3Click(TObject *Sender)
{
TOpenDialog *od = new TOpenDialog(this);
od->Filter = "��������� �����|*.txt";
if (od->Execute()) {
  Memo1->Lines->LoadFromFile(od->FileName);
 
}
History->Lines->Add("������ ��������� �����: "+od->FileName);
delete od;
od = NULL;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
TSaveDialog *od = new TSaveDialog(this);
od->Filter = "��������� �����|*.txt";
if( od ->Execute())
 {
      Memo2->Lines->SaveToFile(od ->FileName + ".txt");
      History->Lines->Add("������� ��������������� �����: "+od->FileName);
 }
delete od;
od = NULL;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button6Click(TObject *Sender)
{
TSaveDialog *od = new TSaveDialog(this);
od->Filter = "��������� �����|*.txt";
if(od ->Execute())
 {
      Memo3->Lines->SaveToFile(od ->FileName + ".txt");
      History->Lines->Add("������� �������������� �����: "+od->FileName);
 }
delete od;
od = NULL;
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Export_PublClick(TObject *Sender)
{
if (KEY_N->Text !="" || KEY_E->Text !="")
{
TStringList*s=new TStringList;
s->Add(KEY_E->Text);
s->Add(KEY_N->Text);
s->Add(Edit4->Text); //����� �����
TSaveDialog *od = new TSaveDialog(this);
od->Filter = "�������� �������� �����|*.pubkey";
if(od ->Execute())
 {
      s->SaveToFile(od ->FileName + ".pubkey");
      delete s;
      History->Lines->Add("������� ��������� �����: "+od->FileName+".pubkey");
 }
delete od;
od = NULL;
}
else
ShowMessage("�������� N � E ������!");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Export_PrivClick(TObject *Sender)
{
if (KEY_N->Text !="" || KEY_D->Text !="")
{
TStringList*s=new TStringList;
s->Add(KEY_D->Text);
s->Add(KEY_N->Text);
s->Add(Edit4->Text); //����� �����
TSaveDialog *od = new TSaveDialog(this);
od->Filter = "�������� �������� �����|*.privkey";
if(od ->Execute())
 {
      s->SaveToFile(od ->FileName + ".privkey");
      delete s;
      History->Lines->Add("������� ��������� �����: "+od->FileName+".privkey");
 }
delete od;
od = NULL;
}
else
ShowMessage("�������� N � D ������!");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Import_PublClick(TObject *Sender)
{
TStringList*s=new TStringList;
TOpenDialog *od = new TOpenDialog(this);
od->Filter = "�������� �������� �����|*.pubkey";
if (od->Execute()) {
  s->LoadFromFile(od->FileName);
  KEY_E->Text=s->Strings[0];    //������� �������� E
  KEY_N->Text=s->Strings[1];    //������� �������� N
  Edit4->Text=s->Strings[2];    //������� �������� ����� �����
  delete s;
  Button2->Enabled=True;
}
History->Lines->Add("������ ��������� �����: "+od->FileName);
delete od;
od = NULL;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Import_PrivClick(TObject *Sender)
{
TStringList*s=new TStringList;
TOpenDialog *od = new TOpenDialog(this);
od->Filter = "�������� �������� �����|*.privkey";
if (od->Execute()) {
  s->LoadFromFile(od->FileName);
  KEY_D->Text=s->Strings[0];    //������� �������� D
  KEY_N->Text=s->Strings[1];    //������� �������� N
  Edit4->Text=s->Strings[2];    //������� �������� ����� �����
  delete s;
  Button4->Enabled=true;
}
History->Lines->Add("������ ��������� �����: "+od->FileName);
delete od;
od = NULL;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button7Click(TObject *Sender)
{
TSaveDialog *od = new TSaveDialog(this);
od->Filter = "��������� �����|*.txt";
if( od ->Execute())
 {
      Memo3->Lines->SaveToFile(od ->FileName + ".txt");
      History->Lines->Add("������� �������������� ������: "+od->FileName);
 }
delete od;
od = NULL;
}
//---------------------------------------------------------------------------






void __fastcall TForm1::RadioGroup1Click(TObject *Sender)
{
if (RadioGroup1->ItemIndex==0)
{
ShowMessage("������");
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton1Click(TObject *Sender)
{
if (RadioButton1->Checked)
{
Group_Decode->Visible=False;
Group_Code->Visible=True;
Button4->Visible=False;
Button3->Visible=True;
Button2->Visible=True;
Button8->Visible=False;
Group_Shifr->Top=320;
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton2Click(TObject *Sender)
{
if (RadioButton2->Checked)
{
Group_Decode->Visible=True;
Group_Decode->Top=320;
Group_Code->Visible=False;
Button3->Visible=False;
Button4->Visible=True;
Button2->Visible=False;
Button8->Visible=True;
Group_Shifr->Top=160;
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button8Click(TObject *Sender)
{
 TOpenDialog *od = new TOpenDialog(this);
od->Filter = "��������� �����|*.txt";
if (od->Execute()) {
  Memo3->Lines->LoadFromFile(od->FileName);
   Button4->Enabled=True;
}
History->Lines->Add("������ �������������� �����: "+od->FileName);
delete od;
od = NULL;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit4Change(TObject *Sender)
{
Button2->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
History->Lines->Add(TimeToStr(Time())+" =====������ ���������=====");        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::UpDown1Click(TObject *Sender, TUDBtnType Button)
{
KEY_N->Text="";
KEY_D->Text="";        
}
//---------------------------------------------------------------------------
