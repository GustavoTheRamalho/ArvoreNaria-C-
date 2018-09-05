#ifndef ARVORENARIA_H
#define ARVORENARIA_H
#include "No.h"



class ArvoreNaria
{
    public:
        ArvoreNaria(int);
        void incluir(int);
        char* toString();
        int qtsNiveis();
        void remover(int);


        void test();

    protected:
    private:
        No* raiz;
        void inserirEm(No*, int, No*, int);
        int n;
        char* toString(char*, No*);
        int qtsNiveis(No*, int);
        No** getPtrsPorNivel(int);

        int getMaiorInfo(No*);
        int getMenorInfo(No*);



};

#endif // ARVORENARIA_H
