//---------------------------------------------------------------------------
#pragma hdrstop
#include "UTSimpleNum.h"
#include <sysutils.hpp>
#include <math.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
TSimpleNum::TSimpleNum(int bl)
{
BitLength = bl;

TNumber from = pow(TNumber(2),TNumber(bl - 1)) + TNumber(1),
        to   = pow(TNumber(2),TNumber(bl));
*this = rnd(from,to);
while (!SmallSNCheck() || !RabinMiller())
  *this = rnd(from,to);
}

//---------------------------------------------------------------------------
TSimpleNum::TSimpleNum(TNumber& newnum) : TNumber(newnum)
{
BitLength = 1;
while (newnum >= pow(TNumber(2),TNumber(BitLength)))
  BitLength++;
}

//---------------------------------------------------------------------------
bool TSimpleNum::SmallSNCheck()
{
for (int i = 0; i < SmallSNCount; i++)
  if ((*this % TNumber(SmallSN[i])) == TNumber(0) && *this != TNumber(SmallSN[i]))
    return false;

return true;
}

//---------------------------------------------------------------------------
bool TSimpleNum::RabinMiller()
{
TNumber p = *this;
TNumber p1 = p - TNumber(1);

TNumber b = 0;
while (p1%TNumber(2) == TNumber(0) && p1 > TNumber(0))
  {
  p1 = p1/TNumber(2);
  b++;
  }
TNumber m = p1;

AnsiString m_bin = "";
TNumber m_rest = m;
while (m_rest != TNumber(0))
  {
  if (m_rest%TNumber(2) == TNumber(1)) m_bin = "1" + m_bin;
                else m_bin = "0" + m_bin;
  m_rest = m_rest/TNumber(2);
  }

bool might_be_simple = true;
int iter = 0;

while (might_be_simple && iter < TSN_DEFAULT_RMTIMES)
  {
  iter++;
  might_be_simple = false;

  TNumber a;
  while (a >= p || a == TNumber(0))
    a = rnd(TNumber(1),pow(TNumber(2),TNumber(BitLength)));

  TNumber z = 1;
  for (int i = 1; i <= m_bin.Length(); i++)
    {
    z = (z*z)%p;
    if (m_bin[i] == '1')
      z = (z*a)%p;
    }

  if (z == TNumber(1) || z == p - TNumber(1)) might_be_simple = true;

  TNumber j = 0;
  while (b > TNumber(0) && j < b - TNumber(1))
    {
    j++;
    z = (z*z) % p;

    if (z == p - TNumber(1))
      {
      might_be_simple = true;
      break;
      }
    }
  }
  
return might_be_simple;
}

//---------------------------------------------------------------------------
bool TSimpleNum::FullCheck()
{
TNumber i;

for (i = 2; *this > i; i++)
  if ((*this % i) == TNumber(0))
    return false;

return true;
}

//---------------------------------------------------------------------------
AnsiString TSimpleNum::ToStr()
{
char* res_str = *this;
AnsiString res(res_str);
return res;
}

//---------------------------------------------------------------------------

