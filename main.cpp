#include <iostream>
#include "No.h"
#include "ArvoreNaria.h"
using namespace std;

int main()
{
    ArvoreNaria arvore = ArvoreNaria(4);

    arvore.incluir(3);
    arvore.incluir(2);
    arvore.incluir(4);
    arvore.incluir(1);
    arvore.incluir(7);
    arvore.incluir(5);
    arvore.incluir(6);

    arvore.remover(3);

    cout << arvore << endl;

    return 0;
}
