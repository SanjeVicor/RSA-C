#ifndef SYSTEM_H
#define SYSTEM_H
#include <iostream>
#include <random>
#include <functional>
#include <chrono>
#include "Keys.h"
#include <string>
#include <NTL/ZZ.h>
#include <limits>
#include <fstream>
#include <sstream>
using namespace NTL;

class System
{
    public:
        System();
        virtual ~System();
        void Menu();
        ZZ prime(ZZ nComp);
        ZZ coprime(ZZ nComp);
        bool isMCDone(ZZ a, ZZ b);
        ZZ calculateD(ZZ e, ZZ phi);
        void setMessage(std::string);
        std::string getMessage();
        void encryptMessage(std::string);
        void uncryptMessage(std::string);
    protected:

    private:
        Keys key;
        ZZ N, E, D,P,Q;
        std::string message;
};

#endif // SYSTEM_H
