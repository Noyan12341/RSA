//---------------------------------------------------------------------------
#pragma hdrstop
#include "UTHexString.h"
#include <sysutils.hpp>
#include <math.hpp>
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
THexString::THexString()                   // 
{
el = new unsigned int[1];
dim = 0;
}

//---------------------------------------------------------------------------
THexString::THexString(const AnsiString Source)
{                                          // 
el = new unsigned int[1];
AsHexString = Source;
}

//---------------------------------------------------------------------------
THexString::THexString(const THexString &Source)
{                                          // 
dim = Source.dim;
el = new unsigned int[dim];
for (int i = 0; i < dim; i++)
  el[i] = Source.el[i];
}

//---------------------------------------------------------------------------
THexString::~THexString()                  // 
{
delete[] el;
}

//---------------------------------------------------------------------------
int THexString::HexCharToInt(const char &h)
{                                          // 
if (h == '0') return 0;
if (h == '1') return 1;
if (h == '2') return 2;
if (h == '3') return 3;
if (h == '4') return 4;
if (h == '5') return 5;
if (h == '6') return 6;
if (h == '7') return 7;
if (h == '8') return 8;
if (h == '9') return 9;
if (h == 'A' || h == 'a') return 10;
if (h == 'B' || h == 'b') return 11;
if (h == 'C' || h == 'c') return 12;
if (h == 'D' || h == 'd') return 13;
if (h == 'E' || h == 'e') return 14;
if (h == 'F' || h == 'f') return 15;
return -1;
}

//---------------------------------------------------------------------------
char THexString::IntToHexChar(unsigned int digit)
{                                          // 1
if (digit > 15)
throw Exception("hex must be [0:15]");
if (digit <=  9) return AnsiString(digit)[1];
if (digit == 10) return 'A';
if (digit == 11) return 'B';
if (digit == 12) return 'C';
if (digit == 13) return 'D';
if (digit == 14) return 'E';
return 'F';
}

//---------------------------------------------------------------------------
void THexString::SetHexString(AnsiString Source)
{                                          // Запись как 16-ричная строка
Source = Source.Trim();
if ((Source.Length() + 1)%3 != 0)
  throw Exception("Длина строки не соответствует формату");

delete[] el;
dim = (Source.Length() + 1)/3;
el = new unsigned int[dim];

unsigned int digit1,digit2;
for (int i = 1; i <= dim; i++)
  {
  digit1 = HexCharToInt(Source[3*i-2]);
  digit2 = HexCharToInt(Source[3*i-1]);

  if (digit1 == -1 || digit2 == -1)
    throw Exception("'"+Source+"' is not string of hex.");

  if (i*3 <= Source.Length())
    if (Source[i*3] != ' ')
      throw Exception("'"+Source+"' is not string of hex.");
  el[i-1] = digit1*16 + digit2;
  }
}

//---------------------------------------------------------------------------
AnsiString THexString::GetHexString()      //Перевод исходного текста в HEX-код 
{
AnsiString result;
result = "";

int digit1,digit2;
for (int i = 0; i < dim; i++)
  {
  digit2 = el[i]%16;
  digit1 = (el[i] - el[i]%16) / 16;
  result += IntToHexChar(digit1);
  result += IntToHexChar(digit2);
  result += " ";
  }
result = result.Trim();
return result;
}

//---------------------------------------------------------------------------
AnsiString THexString::GetCharString()     // 
{
AnsiString result = "";
for (int i = 0; i < dim; i++)
  result += (char)el[i];
return result;
}

//---------------------------------------------------------------------------
void THexString::SetCharString(AnsiString Source)
{                                          // 
dim = Source.Length();
delete[] el;
el = new unsigned int[dim];

for (int i = 0; i < dim; i++)
  el[i] = (unsigned char)Source[i+1];
}

//---------------------------------------------------------------------------
int THexString::GetDim()                   // 
{return dim;}

//---------------------------------------------------------------------------
void THexString::XOR(const THexString &op) // 
{
if (dim != op.dim)
  throw Exception("Ошибка!");

for (int i = 0; i < dim; i++)
  el[i] = el[i]^op.el[i];
}

//---------------------------------------------------------------------------
void THexString::AddWOExtend(const THexString &op)
{                                          //
if (dim != op.dim)
  throw Exception("Ошибка!");

int rem = 0;
for (int i = 0; i < dim; i++)
  {
  el[i] = op.el[i] + el[i] + rem;
  rem = (el[i] - el[i] % 256)/256;
  el[i] = el[i] % 256;
  }
}

//---------------------------------------------------------------------------
THexString& THexString::operator = (THexString &a)
{                                          // 
AsHexString = a.AsHexString;
return *this;
}

//---------------------------------------------------------------------------
AnsiString  THexString::GetBinString()
{
AnsiString Result = "";
for (int i = 0; i < dim; i++)
  {
  AnsiString res;
  int todiv = el[i];
  int rem;

  for (int j = 0; j < 8; j++)
    {
    rem = todiv%2;
    todiv = Floor(todiv/2);
    res = AnsiString(rem) + res;
    }

  Result += res;
  }

return Result;
}

//---------------------------------------------------------------------------
void THexString::SetBinString(AnsiString Source)
{
if (Source.Length() % 8 != 0)
  throw Exception("Ошибка!");

dim = Source.Length() / 8;
delete[] el;
el = new unsigned int[dim];

for (int i = 0; i < dim; i++)
  {
  unsigned int value = 0;

  for (int j = 0; j < 8; j++)
    {
    if (Source[i*8 + j + 1] != '0' && Source[i*8 + j + 1] != '1')
      throw Exception("Строка должна состоять из 0 и 1");

    if (Source[i*8 + j + 1] == '0')
      value = value * 2;
    else
      value = value * 2 + 1;
    }

  el[i] = value;
  }
}

//---------------------------------------------------------------------------
THexString& THexString::SubString(int pos, int count)
{
AnsiString ResStr;
ResStr = this->AsCharString;
ResStr = ResStr.SubString(pos,count);

THexString *Result;
Result = new THexString();
Result->AsCharString = ResStr;

return *Result;
}

//---------------------------------------------------------------------------
THexString& THexString::operator + (THexString &a)
{
AnsiString res = this->AsCharString;
res += a.AsCharString;

THexString *Result;
Result = new THexString();
Result->AsCharString = res;

return *Result;
}

//---------------------------------------------------------------------------
unsigned int& THexString::operator[] (int index)
{
return el[index];
}

//---------------------------------------------------------------------------

