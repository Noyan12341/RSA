//---------------------------------------------------------------------------
#pragma hdrstop
#include "UTNumber.h"
#include <sysutils.hpp>
#pragma package(smart_init)

//---------------------------------------------------------------------------
TNumber::TNumber(const char *value)
{
if (value)
  {
  vlsign = (*value == '-') ? 1:0;

  if(ispunct(*value))
    {
    vlen  = strlen(value)-1;
    vlstr = new char[vlen + 1];
    strcpy(vlstr, value+1);
    }
  else
    {
    vlen = strlen(value);
    vlstr = new char[vlen + 1];
    strcpy(vlstr, value);
    }

  strrev(vlstr);
  }
else                                   
  {                                    
  vlstr = new char[2];
  *vlstr = '0';
  *(vlstr+1)= '\0';
  vlen = 1;
  vlsign = 0;
  }
}

//---------------------------------------------------------------------------
TNumber::TNumber(int n)
{
int i;
if (n < 0)
  {
  vlsign = 1;
  n = (-n);
  }
else vlsign = 0;

if (n)
  {
  i = (int)log10(n)+2;
  vlstr = new char[i];
  vlen = i-1;
  i = 0;

  while (n >= 1)
    {
    vlstr[i] = n%10 + '0';
    n /= 10;
    i++;
    }
  vlstr[i] = '\0';
  }
else
  {
  vlstr = new char[2];
  *vlstr = '0'; *(vlstr+1) = '\0';
  vlen = 1;
  }
}

//---------------------------------------------------------------------------
TNumber::TNumber(const TNumber& x):vlen(x.vlen),vlsign(x.vlsign)
{
vlstr = new char[x.vlen + 1];
strcpy(vlstr, x.vlstr);
}

//---------------------------------------------------------------------------
TNumber::~TNumber()
{delete [] vlstr;}

//---------------------------------------------------------------------------
TNumber::operator int() const
{
static TNumber max0(INT_MAX);
static TNumber min0(INT_MIN+1);

int number, factor = 1;
//if (*this > max0)
//  throw Exception("Error: convert TNumber->integer incredible");
//if (*this < min0)
//  throw Exception("Error: convert TNumber->integer incredible");

number = vlstr[0] - '0';
for (int j = 1; j < vlen; j++)
  {
  factor *= 10;
  number += (vlstr[j] - '0') * factor;
  }

if (vlsign) return -number;
return number;
}

//---------------------------------------------------------------------------
TNumber::operator long() const
{
static TNumber max0(INT_MAX);
static TNumber min0(INT_MIN+1);
long number, factor = 1;

if (*this > max0)
  throw Exception("Error: convert TNumber->integer incredible");
if (*this < min0)
  throw Exception("Error: convert TNumber->integer incredible");

number = vlstr[0] - '0';
for (long j = 1; j < vlen; j++)
  {
  factor *= 10;
  number += (vlstr[j] - '0') * factor;
  }

if (vlsign) return -number;
return number;
}

//---------------------------------------------------------------------------
TNumber::operator double() const
{
double sum, factor = 1.0;
sum = double(vlstr[0] - '0');

for (int i = 1; i < vlen; i++)
  {
  factor *= 10.0;
  sum += double(vlstr[i] - '0') * factor;
  }
return sum;
}

//---------------------------------------------------------------------------
TNumber::operator char * () const
{
char *temp = new char[vlen + 1];
char *s;

if (vlen > 0)
  {
  strcpy(temp, vlstr);
  if (vlsign)
    {
    s = new char[vlen + 2];
    strcpy(s,"-");
    }
  else
    {
    s = new char[vlen + 1];
    strcpy(s,"");
    }
  strcat(s,strrev(temp));
  }
else
  {
  s = new char[2];
  strcpy(s,"0");
  }
delete [] temp;
return s;
}

//---------------------------------------------------------------------------
const TNumber & TNumber::operator = (const TNumber &rhs)
{
if (this == &rhs) return *this;

delete [] vlstr;
vlstr = new char [rhs.vlen + 1];
strcpy(vlstr, rhs.vlstr);
vlen = rhs.vlen;
vlsign = rhs.vlsign;
return *this;
}

//---------------------------------------------------------------------------
TNumber TNumber::operator -() const
{
TNumber temp(*this);
if (temp != zero) temp.vlsign = !vlsign;

return temp;
}

//---------------------------------------------------------------------------
TNumber TNumber::operator ++()
{
return *this = *this + one;
}

//---------------------------------------------------------------------------
TNumber TNumber::operator ++ (int)
{
TNumber result(*this);

*this = *this + one;
return result;
}

//---------------------------------------------------------------------------
TNumber TNumber::operator -- ()
{
return *this = *this - one;
}

//---------------------------------------------------------------------------
TNumber TNumber::operator -- (int)
{
TNumber result(*this);
*this = *this - one;

return result;
}

//---------------------------------------------------------------------------
TNumber TNumber::operator += (const TNumber& v)
{
return *this = *this + v;
}

//---------------------------------------------------------------------------
TNumber TNumber::operator -= (const TNumber& v)
{
return *this = *this - v;
}

//---------------------------------------------------------------------------
TNumber TNumber::operator *= (const TNumber& v)
{
return *this = *this * v;
}

//---------------------------------------------------------------------------
TNumber TNumber::operator /= (const TNumber& v)
{
return *this = *this / v;
}

//---------------------------------------------------------------------------
TNumber TNumber::operator %= (const TNumber& v)
{
return *this = *this % v;
}

//---------------------------------------------------------------------------
TNumber operator + (const TNumber &u, const TNumber &v)
{
if (u.vlsign ^ v.vlsign)
  {
  if (u.vlsign == 0)
    {
    TNumber t1 = u - abs(v);
    return t1;
    }
  else
    {
    TNumber t2 = v - abs(u);
    return t2;
    }
  }

int j,
    d1,
    d2,
    digitsum,
    carry = 0,
    maxlen = (u.vlen > v.vlen) ? u.vlen:v.vlen;
char *temp = new char[maxlen + 2];

for (j = 0; j < maxlen; j++)
  {
  d1 = (j > u.vlen - 1) ? 0 : u.vlstr[j] - '0';
  d2 = (j > v.vlen - 1) ? 0 : v.vlstr[j] - '0';
  digitsum = d1 + d2 + carry;

  if (digitsum >= 10)
    {
    digitsum -= 10;
    carry = 1;
    }
  else
    carry = 0;

  temp[j] = digitsum + '0';
  }

if (carry) temp[j++] = '1';

if (u.vlsign) temp [j++] = '-';

temp[j] = '\0';
u.strrev(temp);
TNumber result(temp);

delete [] temp;
return result;
}

//---------------------------------------------------------------------------
TNumber operator - (const TNumber &u, const TNumber &v)
{
if (u.vlsign ^ v.vlsign)
  {
  if (u.vlsign == 0)
    {
    TNumber t1 = u + abs(v);
    return t1;
    }
  else
    {
    TNumber t2 = -(v + abs(u));
    return t2;
    }
  }

int maxlen = (u.vlen > v.vlen) ? u.vlen:v.vlen,
    d,
    d1,
    d2,
    i,
    negative,
    borrow = 0;
char *temp = new char[maxlen + 1];

TNumber w,y;

if (u.vlsign == 0)
  if (u < v)
    {
    w = v;
    y = u;
    negative = 1;
    }
  else
    {
    w = u;
    y = v;
    negative = 0;
    }
else
  if (u < v)
    {
    w = u;
    y = v;
    negative = 1;
    }
  else
    {
    w = v;
    y = u;
    negative = 0;
    }

for (i = 0; i < maxlen; i++)
  {
  d1 = (i > w.vlen - 1) ? 0 : w.vlstr[i] - '0';
  d2 = (i > y.vlen - 1) ? 0 : y.vlstr[i] - '0';
  d = d1 - d2 - borrow;

  if (d < 0)
    {
    d += 10;
    borrow = 1;
    }
  else
    borrow = 0;

  temp[i] = d + '0';
  }

while (i - 1 > 0 && temp[i - 1] == '0')
  --i;

if (negative) temp[i++] = '-';
temp[i] = '\0';
u.strrev(temp);

TNumber result(temp);
delete [] temp;
return result;
}

//---------------------------------------------------------------------------
TNumber operator * (const TNumber &u, const TNumber &v)
{
TNumber pprod("1"), tempsum("0");

for (int j = 0; j < v.vlen; j++)
  {
  int digit = v.vlstr[j] - '0';
  pprod = u.multdigit(digit);
  pprod = pprod.mult10(j);

  tempsum += pprod;
  }

tempsum.vlsign = u.vlsign ^ v.vlsign;
return tempsum;
}

//---------------------------------------------------------------------------
TNumber operator / (const TNumber &u, const TNumber &v)
{
TNumber w, y, b, c, d, quotient = TNumber("0");
int len = u.vlen - v.vlen;

if (v == TNumber("0"))
  throw Exception("Error: divide by zero");

w = abs(u); y = abs(v);
if (w < y) return TNumber("0");

char *temp = new char[w.vlen+1];
strcpy(temp, w.vlstr + len);
b.strrev(temp);
c = TNumber(temp);
delete [] temp;

for (int i = 0; i <= len; i++)
  {
  quotient = quotient.mult10(1);
  b = d = TNumber("0");

  while (b < c)
    {
    b = b + y;
    d = d + TNumber("1");
    }

  if (c < b)
    {
    b = b - y;
    d = d - TNumber("1");
    }

  quotient = quotient + d;

  if (i < len)
    {
    c = (c-b).mult10(1);
    c = c + TNumber(w.vlstr[len-i-1]-'0');
    }
  }

quotient.vlsign = u.vlsign^v.vlsign;
return quotient;
}

//---------------------------------------------------------------------------
TNumber operator % (const TNumber &u, const TNumber &v)
{
return (u - v * (u / v));
}

//---------------------------------------------------------------------------
int operator == (const TNumber &u, const TNumber &v)
{
return (u.vlsign == v.vlsign && !strcmp(u.vlstr, v.vlstr));
}

//---------------------------------------------------------------------------
int operator != (const TNumber &u, const TNumber &v)
{
return !(u==v);
}

//---------------------------------------------------------------------------
int operator < (const TNumber &u, const TNumber &v)
{
if  (u.vlsign < v.vlsign) return 0;
else if	(u.vlsign > v.vlsign) return 1;

if  (u.vlen < v.vlen) return (1^u.vlsign);
else if	(u.vlen > v.vlen) return (0^u.vlsign);

int temp;
char *temp1 = new char[u.vlen + 1],
     *temp2 = new char[v.vlen + 1];

strcpy(temp1, u.vlstr);
strcpy(temp2, v.vlstr);
u.strrev(temp1);
u.strrev(temp2);

temp = strcmp(temp1, temp2);
delete [] temp1;
delete [] temp2;

if (temp < 0) return (1^u.vlsign);
else if (temp > 0) return (0^u.vlsign);
     else return 0;
}

//---------------------------------------------------------------------------
int operator <= (const TNumber &u, const TNumber &v)
{
return (u < v || u == v);
}

//---------------------------------------------------------------------------
int operator > (const TNumber &u, const TNumber &v)
{
return (!(u<v) && u!=v);
}

//---------------------------------------------------------------------------
int operator >= (const TNumber &u, const TNumber &v)
{
return (u>v || u==v);
}

//---------------------------------------------------------------------------
TNumber abs(const TNumber &v)
{
TNumber u(v);
if (u.vlsign) u.vlsign = 0;
return u;
}

//---------------------------------------------------------------------------
TNumber sqrt(const TNumber &v)
{
if (v.vlsign)
  throw Exception("NaN");

int j, k = v.vlen + 1, num = k >> 1;
TNumber y, z, sum, tempsum, digitsum;

char *temp = new char[num + 1],
     *w = new char[k];

strcpy(w, v.vlstr);
k = v.vlen - 1;
j = 1;

if (v.vlen % 2)
  digitsum = TNumber(w[k--] - '0');
else
  {
  digitsum = TNumber((w[k] - '0')*10 + w[k-1] - '0');
  k -= 2;
  }

sum = z = TNumber(int(sqrt(double(digitsum))));

temp[0] = int(z) + '0';
digitsum -= z*z;

for(; j < num; j++)
  {
  digitsum = digitsum.mult10(1) + TNumber(w[k--] - '0');
  y = z + z;
  z = digitsum/y;
  tempsum = digitsum.mult10(1) + TNumber(w[k] - '0');
  digitsum = -y*z.mult10(1) + tempsum - z*z;

  while (digitsum < zero)
    {
    --z;
    digitsum = -y*z.mult10(1) + z;
    }
  --k;

  temp[j] = int(z) + '0';
  z = sum = sum.mult10(1) + z;
  }

temp[num] = '\0';
TNumber result(temp);
delete [] temp; delete [] w;
return result;
}

//---------------------------------------------------------------------------
TNumber pow(const TNumber &X, const TNumber& degree)
{                                        
TNumber N(degree), Y("1"), x(X);         
if (N == TNumber("0")) return TNumber("1");
if (N < TNumber("0")) return TNumber("0");

while(1)
  {
  if (N%TNumber("2") != TNumber("0"))
    {
    Y = Y * x;
    N = N / TNumber("2");
    if (N == TNumber("0")) return Y;
    }
  else
    N = N / TNumber("2");

  x = x * x;
  }
}

//---------------------------------------------------------------------------
double div(const TNumber &u, const TNumber &v)
{
double qq=0.0, qqscale = 1.0;
TNumber w, y, b, c;
int d, count, decno = 16;

if (v == TNumber("0"))
  throw Exception("??????! ??????? ?? 0!");

if (u == TNumber("0")) return 0.0;

w = abs(u); y = abs(v);
while(w < y)
  {
  w = w.mult10(1);
  qqscale *= 0.1;
  }

int len = w.vlen - y.vlen;
char *temp = new char[w.vlen + 1];

strcpy(temp, w.vlstr + len);
w.strrev(temp);
c = TNumber(temp);
delete [] temp;

for (int i = 0; i <= len; i++)
  {
  qq *= 10.0;
  b = TNumber("0"); d = 0;

  while (b < c)
    {
    b += y;
    d += 1;
    }

  if (c < b)
    {
    b -= y;
    d -= 1;
    }

  qq += double(d);
  c = (c-b).mult10(1);

  if (i < len)
    c += TNumber(w.vlstr[len - i - 1] - '0');
  }

qq *= qqscale; count = 0;

while (c != TNumber("0") && count < decno)
  {
  qqscale *= 0.1;

  b = TNumber("0"); d = 0;

  while (b < c)
    {
    b += y;
    d += 1;
    }

  if (c < b)
    {
    b -= y;
    d -= 1;
    }

  qq += double(d)*qqscale;

  c = (c-b).mult10(1);
  count++;
  }

if (u.vlsign^v.vlsign) qq *= (-1.0);
  return qq;
}

//---------------------------------------------------------------------------
ostream & operator << (ostream &s, const TNumber &v)
{
char *temp = new char[v.vlen + 1];
if (v.vlen > 0)
  {
  strcpy(temp, v.vlstr);
  if (v.vlsign) s << "-";
  s << v.strrev(temp);
  }
else s << "0";
delete [] temp;
return s;
}

//---------------------------------------------------------------------------
istream & operator >> (istream &s, TNumber &v)
{
char* temp;
s >> temp;

delete [] v.vlstr;
v.vlen = strlen(temp);
v.strrev(temp);
v.vlstr = new char[v.vlen + 1];
strcpy(v.vlstr, temp);
return s;
}

//---------------------------------------------------------------------------
char * TNumber::strrev(char *s) const      
{                                          
int len = strlen(s),                       
    len1 = len - 1,
    index,
    limit = len >> 1;
char t;

for (int i = 0; i < limit; i++)
  {
  index = len1 - i;
  t = s[index];
  s[index] = s[i];
  s[i] = t;
  }
return s;
}

//---------------------------------------------------------------------------
TNumber TNumber::multdigit(int num) const
{
int j, carry = 0;

if (num)
  {
  char *temp = new char[vlen + 2];

  for(int j = 0; j < vlen; j++)
    {
    int d1 = vlstr[j] - '0',
        digitprod = d1*num + carry;

    if (digitprod >= 10)
      {
      carry = digitprod/10;
      digitprod -= carry*10;
      }
    else carry = 0;
    temp[j] = digitprod + '0';
    }
  j = vlen;

  if (carry)
    {
    temp[j] = carry + '0';
    j++;
    }
  temp[j] = '\0';

  strrev(temp);
  TNumber result(temp);
  delete [] temp;
  return result;
  }
else
  return zero;
}

//---------------------------------------------------------------------------
TNumber TNumber::mult10(int num) const
{
if (*this != zero)
  {
  int j, dd = vlen + num, bb = vlen - 1;
  char *temp = new char [dd + 1];

  for (j = 0; j < vlen; j++)
    temp[j] = vlstr[bb-j];
  for (j = vlen; j < dd; j++)
    temp[j] = '0';

  temp[dd] = '\0';
  TNumber result(temp);
  delete [] temp;
  return result;
  }
else
  return zero;
}

//---------------------------------------------------------------------------
TNumber rnd(const TNumber& from, const TNumber& to)
{                                 
int res_length;                   
                                  

while ((res_length = random(to.vlen) + 1) < from.vlen);

char *res_str = new char[res_length + 1];
TNumber res;
while (1)
  {
  for (int i = 0; i < res_length; i++)
    {
    int digit = random(10);

    if (i == 0)
      while (digit == 0) digit = random(10);
      
    res_str[i] = '0' + digit;
    }
  res_str[res_length] = '\0';

  res = TNumber(res_str);
  if (res >= from && res <= to) break;
  }

return res;
}

//---------------------------------------------------------------------------
TNumber eae(TNumber u, TNumber v)             // ???????? ???????
{
TNumber u1, u2, u3,                   
        v1, v2, v3,                  
        t1, t2, t3,                  
        q;                          

u1 = TNumber(1); u2 = TNumber(0); u3 = u;
v1 = TNumber(0); v2 = TNumber(1); v3 = v;

while (v3 != TNumber(0))
  {
  q = u3/v3;

  t1 = (u1 - v1*q);  t2 = (u2 - v2*q);  t3 = (u3 - v3*q);
  u1 = v1;           u2 = v2;           u3 = v3;
  v1 = t1;           v2 = t2;           v3 = t3;
  }

return u2;
}

