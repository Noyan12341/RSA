//---------------------------------------------------------------------------
#pragma hdrstop
#include "UTRSA.h"
#include "UTSimpleNum.h"
#include <sysutils.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
_INFO Info;
//---------------------------------------------------------------------------
TRSA::TRSA(const unsigned int bl_len = TRSA_DEFAULT_BLOCK_LEN) //ГЕНЕРАЦИЯ КЛЮЧЕЙ
{

if (bl_len % 8 != 0)
  throw Exception("Длина блоков должна быть кратна 8");
BlockLength = bl_len;

HaveSecretKey = true;
TSimpleNum *p = new TSimpleNum(bl_len/2),
           *q = new TSimpleNum(bl_len/2 + 8);
TNumber p1 = *(TNumber*)p,    //генерация p
        q1 = *(TNumber*)q;    //генерация q
Info.InfoP=p1;
Info.InfoQ=q1;
n = p1 * q1;                  //произведение N=p*q

TNumber phi = (p1 - TNumber(1)) * (q1 - TNumber(1));  //функция Эйлера
Info.InfoPhi=phi;
e = TNumber(2);                    // Поиск наименьшего числа, взаимно простого
while (phi % e == TNumber(0)) e++; // с фи.

d = eae(phi,e);                    // Поиск секретного ключа
if (d < TNumber(0)) d = phi + d;
}

//---------------------------------------------------------------------------
TRSA::TRSA(TNumber KeyN, TNumber EKey, int bl_len = TRSA_DEFAULT_BLOCK_LEN)
{
if (bl_len % 8 != 0)
  throw Exception("Длина блоков должна быть кратна 8");
BlockLength = bl_len;

HaveSecretKey = false;
n = KeyN;
e = EKey;
}

//---------------------------------------------------------------------------
TRSA::TRSA(TNumber KeyN, TNumber EKey, TNumber DKey, int bl_len = TRSA_DEFAULT_BLOCK_LEN)
{
if (bl_len % 8 != 0)
  throw Exception("Длина блоков должна быть кратна 8");
BlockLength = bl_len;

HaveSecretKey = true;
n = KeyN;
e = EKey;
d = DKey;
}

//---------------------------------------------------------------------------
void TRSA::Encrypt()
{
int bl_len_bytes = BlockLength / 8;


while (FPlainText.Count % bl_len_bytes != 0)
  FPlainText.AsCharString = FPlainText.AsCharString + " ";


FCryptedText.AsCharString = "";
for (int i = 0; i < FPlainText.Count / bl_len_bytes; i++)
  for (int j = 0; j <= bl_len_bytes; j++)
    FCryptedText.AsCharString = FCryptedText.AsCharString + " ";

for (int i = 0; i < FPlainText.Count / bl_len_bytes; i++)
  {
  TNumber bl = 0;


  bl += TNumber(FPlainText[i * bl_len_bytes]);
  for (int j = 1; j < bl_len_bytes; j++)
    {
    bl *= TNumber(256);
    bl += TNumber(FPlainText[i * bl_len_bytes + j]);
    }


  if (bl >= n)
    throw Exception("Ошибка шифрования! Длина ключа не соответствует ключу N");  

 
  AnsiString e_bin = "";                 
  TNumber e_rest = e;
  while (e_rest != TNumber(0))   //Преобразование E в X2 систему счисления (e_bin)
    {
    if (e_rest%TNumber(2) == TNumber(1)) e_bin = "1" + e_bin;
                                    else e_bin = "0" + e_bin;
    e_rest = e_rest/TNumber(2);
    }

  TNumber ebl = 1;
  for (int j = 1; j <= e_bin.Length(); j++)
    {
    ebl = (ebl*ebl)%n;
    if (e_bin[j] == '1')
      ebl = (ebl*bl)%n;
    }

 for (int j = bl_len_bytes; j >= 0; j--)
    {
    FCryptedText[i * (bl_len_bytes + 1) + j] = (int) (ebl % TNumber(256));
    ebl = ebl / TNumber(256);
    }
  }
}

//---------------------------------------------------------------------------
void TRSA::Decrypt()
{
if (!HaveSecretKey)
  throw Exception("Декодирование невозможно! Нет секретного ключа!");

int bl_len_bytes = BlockLength / 8 + 1;         // Длина блока кодир. текста больше
if (FCryptedText.Count % (bl_len_bytes) != 0)
  throw Exception("Декодирование невозможно! Длина ключа не соответствует!");


FPlainText.AsCharString = "";
for (int i = 0; i < FCryptedText.Count / bl_len_bytes; i++)
  for (int j = 0; j < bl_len_bytes - 1; j++)
    FPlainText.AsCharString = FPlainText.AsCharString + " ";


for (int i = 0; i < FCryptedText.Count / bl_len_bytes; i++)
  {
  TNumber bl = 0;


  bl += TNumber(FCryptedText[i * bl_len_bytes]);
  for (int j = 1; j < bl_len_bytes; j++)
    {
    bl *= TNumber(256);
    bl += TNumber(FCryptedText[i * bl_len_bytes + j]);
    }


  AnsiString d_bin = "";
  TNumber d_rest = d;
  while (d_rest != TNumber(0))
    {
    TNumber mod = d_rest%TNumber(2);
    bool comp = mod == TNumber(1);
    if (comp) d_bin = "1" + d_bin;
                                      else d_bin = "0" + d_bin;
    d_rest = d_rest/TNumber(2);
    }

  TNumber dbl = 1;
  for (int j = 1; j <= d_bin.Length(); j++)
    {
    dbl = (dbl*dbl)%n;
    if (d_bin[j] == '1')
      dbl = (dbl*bl)%n;
    }


  for (int j = bl_len_bytes - 2; j >= 0; j--)
    {
    FPlainText[i * (bl_len_bytes-1) + j] = (int) (dbl % TNumber(256));
    dbl = dbl / TNumber(256);
    }
  }
}

//---------------------------------------------------------------------------
void TRSA::SetPlainText(THexString Source)
{
FPlainText = Source;
Encrypt();
}

//---------------------------------------------------------------------------
void TRSA::SetCryptedText(THexString Source)
{
if (!HaveSecretKey)
  throw Exception("Декодирование невозможно! Секретный ключ ложный!");
FCryptedText = Source;
Decrypt();
}

//---------------------------------------------------------------------------
THexString TRSA::GetPlainText()
{return FPlainText;}

//---------------------------------------------------------------------------
THexString TRSA::GetCryptedText()
{return FCryptedText;}

//---------------------------------------------------------------------------
TNumber TRSA::GetKeyModul()
{return n;}

//---------------------------------------------------------------------------
TNumber TRSA::GetOpenKey()
{return e;}

//---------------------------------------------------------------------------

TNumber TRSA::GetSecretKey()
{
if (!HaveSecretKey)
  throw Exception("Секретного ключа не существует!");
return d;
}
//---------------------------------------------------------------------------
