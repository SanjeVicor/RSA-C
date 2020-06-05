#include "System.h"

using namespace std;
using namespace NTL;

System::System()
{
    //ctor
}

System::~System()
{
    //dtor
}

void System::Menu()
{
    char option;
    string fileName, aux;
    const int LEN_KEYS = 1024;
    do
    {
        cout<< endl<< endl << "1) Generar llaves" << endl
            << "2) Encriptar" << endl
            << "3) Desencriptar" << endl
            << "4) Salir" << endl
            << "Elegir opcion : ";
        cin>>option;

        switch(option)
        {
        case '1':
            do
            {
                do
                {
                    NTL::GenPrime(P, LEN_KEYS);
                    NTL::GenPrime(Q, LEN_KEYS);
                }
                while(P==Q);
                key.setp(P);
                key.setq(Q);
                cout << "p: " << key.getp() << endl
                     << "q: " << key.getq() << endl;
                key.setn(key.getp() * key.getq());
                cout << "n: " << key.getn() << endl;
                key.setphi((key.getp() - 1)*(key.getq() - 1));
                cout << "phi: " << key.getphi() << endl;
            }
            while (key.getphi() == 0 or (key.getp() < 0 or key.getq() < 0 or key.getphi() < 0));
            NTL::GenPrime(E, LEN_KEYS);
            key.sete(E);
            cout << "e: " << key.gete() << endl;
            NTL::InvMod(D,key.gete(), key.getphi());
            key.setd(D);
            cout << "d: " << key.getd() << endl;
            break;


        case '2':
            cin.ignore();
            cout << "Ingresa llave publica" << endl << endl;
            do
            {
                cout << "Ingresa N : ";
                cin >> N;
            }
            while(N <= 0);

            do
            {
                cout << "Ingresa E : ";
                cin >> E;
            }
            while(E <= 0);

            key.setn(N);
            key.sete(E);
            cout << endl << endl << endl
                 << "Ingresa el mensaje" << endl << endl;

            cin.ignore();
            getline(cin,message);
            setMessage(message);

            encryptMessage(getMessage());
            break;
        case '3':
            cin.ignore();
            cout << "Ingresa llave publica" << endl << endl;
            do
            {
                cout << "Ingresa N : ";
                cin >> N;
            }
            while(N <= 0);
            do
            {
                cout << "Ingresa D : ";
                cin >> D;
            }
            while(D <= 0);

            key.setn(N);
            key.setd(D);
            cin.ignore();
            cout << "Ingresa nombre del archivo : ";
            getline(cin,fileName);
            uncryptMessage(fileName);
            break;
        }
    }
    while(option!='4');

}



void System::uncryptMessage(std::string fileName)
{
    ifstream fin(fileName);
    string line;
    std::stringstream  x;
    if(!fin.good())
    {
        cout << "Error abriendo archivo.. " << endl;
    }
    else
    {

        cout << "DESENCRIPTANDO " << endl << endl;
        ZZ y;
        int i = (0), k = conv<int>(y);

        while(!fin.eof())
        {
            getline(fin,line);
            if(fin.eof() or line.length() == 0)
                break;
            NTL::ZZ number(NTL::INIT_VAL, line.c_str());
            y = PowerMod(number, key.getd(), key.getn());
            int w = conv<int>(y);
            cout<< char(w);
        }
    }
    fin.close();
}

void System::setMessage(std::string value)
{
    message = value;
}

string System::getMessage()
{
    return message;
}

void System::encryptMessage(std::string value)
{
    string fileName;
    cout << "Nombre del archivo : " ;
    getline(cin,fileName);
    fileName+=".txt";
    ofstream fout(fileName);
    if(!fout.good())
    {
        cout << "Error abriendo archivo.. " << endl;
    }
    else
    {

        cout << "ENCRIPTANDO " << value;
        ZZ y;
        int i = (0), k = conv<int>(y);

        while(value[i] != '\0')
        {
            cout << "char to int " << int(value[i]) << endl;


            y = PowerMod(conv<ZZ>(int(value[i])), key.gete(), key.getn());
            cout << y << endl;
            fout << y << endl;
            //y = PowerMod(y, key.getd(), key.getn());
            // cout << y << endl;


            i++;
        }
    }
    fout.close();
}
