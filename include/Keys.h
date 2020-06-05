#ifndef KEYS_H
#define KEYS_H
#include <iostream>
#include <NTL/ZZ.h>
using namespace NTL;
class Keys
{
    public:
        Keys();
        virtual ~Keys();

        void setq(ZZ value);
        void setp(ZZ value);
        void setn(ZZ value);
        void setphi(ZZ value);
        void sete(ZZ value);
        void setd(ZZ value);
        ZZ getp();
        ZZ getq();
        ZZ getn();
        ZZ getphi();
        ZZ gete();
        ZZ getd();

    protected:

    private:
       ZZ p, q, n, phi, e, d;
};

#endif // KEYS_H
