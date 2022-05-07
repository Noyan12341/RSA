#ifndef UTRSAH
#define UTRSAH
//---------------------------------------------------------------------------
#include "UTNumber.h"
#include "UTHexString.h"

#define TRSA_ENCRYPTION_KEY   0
#define TRSA_DECRYPTION_KEY   1

#define TRSA_DEFAULT_BLOCK_LEN    64

//---------------------------------------------------------------------------
struct _INFO{
   int InfoP;
   int InfoQ;
   int InfoPhi;
};

class TRSA
{

private:
             TNumber    n;
             TNumber    e;
             TNumber    d;

             bool       HaveSecretKey;

             THexString FPlainText;
             THexString FCryptedText;

             int        BlockLength;
             void       Encrypt();
             void       Decrypt();

             void       SetPlainText(THexString Source);
             void       SetCryptedText(THexString Source);

             THexString GetPlainText();
             THexString GetCryptedText();
             TNumber    GetKeyModul();
             TNumber    GetOpenKey();
             TNumber    Getp();
             TNumber    GetSecretKey();

public:
                        TRSA(const unsigned int bl_len);
                        TRSA(TNumber KeyN, TNumber EKey, int bl_len);
                        TRSA(TNumber KeyN, TNumber EKey, TNumber DKey, int bl_len);

  __property THexString PlainText = {read = GetPlainText, write = SetPlainText};
  __property THexString CryptedText = {read = GetCryptedText, write = SetCryptedText};
  __property TNumber    KeyModul = {read = GetKeyModul};
  __property TNumber    OpenKey = {read = GetOpenKey};
  __property TNumber    SecretKey = {read = GetSecretKey};
};

#endif
