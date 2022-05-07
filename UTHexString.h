#ifndef UTHexStringH
#define UTHexStringH
#include <system.hpp>
//---------------------------------------------------------------------------

class THexString
  {
  private:
               unsigned int *el;
               int           dim;

               int         HexCharToInt(const char &h);
               char        IntToHexChar(unsigned int digit);

               AnsiString  GetHexString();
               void        SetHexString(AnsiString Source);
               int         GetDim();
               AnsiString  GetCharString();
               void        SetCharString(AnsiString Source);
               AnsiString  GetBinString();
               void        SetBinString(AnsiString Source);

  public:
                           THexString();
                           THexString(const AnsiString Source);
                           THexString(const THexString &Source);
                          ~THexString();

               void        XOR(const THexString &op);
               void        AddWOExtend(const THexString &op);  
               THexString& operator = (THexString &a);
               THexString& operator + (THexString &a);  
               unsigned int& operator[] (int index);

               THexString& SubString(int pos, int count);

    __property AnsiString  AsHexString = {read = GetHexString, write = SetHexString};
    __property int         Count = {read = GetDim};
    __property AnsiString  AsCharString = {read = GetCharString, write = SetCharString};
    __property AnsiString  AsBinString = {read = GetBinString, write = SetBinString};
  };

#endif

