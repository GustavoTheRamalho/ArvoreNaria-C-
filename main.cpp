#include <iostream>
#include "No.h"
#include "ArvoreNaria.h"
using namespace std;

int main()
{
    cout << "Hello world!" << endl;

    ArvoreNaria arvore = ArvoreNaria(3);
    arvore.incluir(3);
    arvore.incluir(2);
    arvore.incluir(4);
    arvore.incluir(1);
    arvore.incluir(7);
    arvore.incluir(5);
    arvore.remover(7);

  // arvore.test();
  //printf("%d", arvore.qtsNiveis());
    cout << arvore.toString() << endl;
    arvore.test();




    //cout << arvore.toString() << endl;

    return 0;
}
