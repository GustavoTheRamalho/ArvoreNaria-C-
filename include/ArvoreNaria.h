#ifndef ARVORENARIA_H
#define ARVORENARIA_H
#include "No.h"

#include <iostream>

class ArvoreNaria
{
    public:
        ArvoreNaria(int);
        void incluir(int);
        void remover(int);

        friend std::ostream &operator<<(std::ostream& out,  ArvoreNaria& arvnaria)
        {
            out << arvnaria.toString();
            return out;
        }

    protected:
    private:

        No* raiz;
        int n;
        int qtsNos;
        int qtsNiveis();

        void inserirEm(No*, int, No*, int);

        int getMaiorInfo(No*);
        int getMenorInfo(No*);
        int qtsNiveis(No*, int);

        No** getPtrsPorNivel(int);
        char* toString();





};

#endif // ARVORENARIA_H
