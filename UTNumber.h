//---------------------------------------------------------------------------
#ifndef UTNumberH
#define UTNumberH
//---------------------------------------------------------------------------
#include <assert.h>
#include <iostream.h>
#include <iomanip.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>

class TNumber
{
private:
       TNumber   multdigit(int) const;
       TNumber   mult10(int) const;

       char     *vlstr;                          
       int       vlen;                           
       int       vlsign;                         

public:

                 TNumber(const char* = NULL);    
                 TNumber(int);                   
                 TNumber(const TNumber &);       
                ~TNumber();                      

                 operator int() const;
                 operator long() const;
                 operator double() const;
                 operator char*() const;

  const TNumber& operator=(const TNumber&);

	 TNumber operator - () const;
	 TNumber operator ++ ();
	 TNumber operator ++ (int);
	 TNumber operator -- ();
	 TNumber operator -- (int);

         TNumber operator += (const TNumber &);
	 TNumber operator -= (const TNumber &);
	 TNumber operator *= (const TNumber &);
   	 TNumber operator /= (const TNumber &);
  	 TNumber operator %= (const TNumber &);

  friend TNumber operator + (const TNumber &, const TNumber &);
  friend TNumber operator - (const TNumber &, const TNumber &);
  friend TNumber operator * (const TNumber &, const TNumber &);
  friend TNumber operator / (const TNumber &, const TNumber &);
  friend TNumber operator % (const TNumber &, const TNumber &);

  friend int     operator == (const TNumber &, const TNumber &);
  friend int     operator != (const TNumber &, const TNumber &);
  friend int     operator < (const TNumber &, const TNumber &);
  friend int     operator <= (const TNumber &, const TNumber &);
  friend int     operator > (const TNumber &, const TNumber &);
  friend int     operator >= (const TNumber &, const TNumber &);

         char*   strrev(char *s) const;
  friend TNumber abs(const TNumber &);
  friend TNumber sqrt(const TNumber &);
  friend TNumber pow(const TNumber &, const TNumber &);
  friend double  div(const TNumber &, const TNumber &);

  friend ostream & operator << (ostream &, const TNumber &);
  friend istream & operator >> (istream &, TNumber &);

  friend TNumber rnd(const TNumber& from, const TNumber& to);
};

const TNumber zero = TNumber("0");
const TNumber one  = TNumber("1");
const TNumber two  = TNumber("2");

TNumber eae(TNumber u, TNumber v);             

#endif

