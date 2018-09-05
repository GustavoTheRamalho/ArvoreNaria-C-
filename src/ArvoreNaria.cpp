#include "ArvoreNaria.h"
#include<stdio.h>
#include<string.h>
#include<math.h>
ArvoreNaria::ArvoreNaria(int n)
{
    this->raiz = NULL;
    this->n = n;
}

void ArvoreNaria::incluir(int i)
{
    if (this->raiz == NULL)
        this->raiz = new No(this->n);

    this->inserirEm(this->raiz, i, NULL, NULL);
}


void ArvoreNaria::inserirEm(No* ptr, int info, No* pai, int pos)
{
    if (ptr != this->raiz && ptr == NULL)
    {
          ptr = new No(this->n);
          pai->setPtr(pos, ptr);
    }


    if (ptr->temVaga())
        ptr->inserir(info);
    else
    if (info < ptr->getDado(0))
        this->inserirEm(ptr->getPtr(0), info, ptr, 0);
    else
    if (info > ptr->getDado(this->n-2))
        this->inserirEm(ptr->getPtr(n-1), info, ptr, n-1);
    else
    {
        for(int i=0; i<this->n-2; i++)
        {
            if (info > ptr->getDado(i) && info < ptr->getDado(i+1))
            {
                this->inserirEm(ptr->getPtr(i+1), info, ptr, i+1);
                break;
            }
        }
    }
}



int ArvoreNaria::qtsNiveis()
{
    return this->qtsNiveis(this->raiz, 0);
}

int ArvoreNaria::qtsNiveis(No* ptr, int nAtual)
{
    int* qtsNos = new int[this->n];

    for (int i=0; i<this->n; i++)
        if (ptr->getPtr(i) != NULL)
            if (ptr->getPtr(i)->ehFolha())
                qtsNos[i] = nAtual+1;
            else
                qtsNos[i] = this->qtsNiveis(ptr->getPtr(i), nAtual+1);
        else
            qtsNos[i] = 0;



    int omaior = -1;
    for (int i=0; i<this->n; i++)
        if (qtsNos[i] > omaior)
            omaior = qtsNos[i];

    return omaior;
}


char* ArvoreNaria::toString()
{
    char* buffer = new char[1000];
    strcpy(buffer, "");
    int niveis = this->qtsNiveis();
    for (int i=0; i<=niveis; i++)
    {
   //     sprintf(buffer, "%d: ", i);
        No** nosAtuais = this->getPtrsPorNivel(i);
        int qtsNos = (int)pow(this->n, i);

        for (int j=0; j<qtsNos; j++)
            if (nosAtuais[j] == NULL)
                strcat(buffer, " ");
            else
            {
                strcat(buffer, nosAtuais[j]->toString());
                strcat(buffer, "  ");
            }



         strcat(buffer, "\n");
    }

    return buffer;
}

No** ArvoreNaria::getPtrsPorNivel(int nivel)
{
     if (nivel == 0)
     {
         No** ptrs = new No*[1];
         ptrs[0] = this->raiz;
         return ptrs;
     }
     else
     {
         int qtsPtrs = (int)(pow(this->n, nivel));
         int qtsPtrsAnt = (int)(pow(this->n, nivel-1));

         No** ptrs = new No*[qtsPtrs];
         No** ptrsNivelAnterior = this->getPtrsPorNivel(nivel-1);

         int c = 0;

         for (int i=0; i<qtsPtrsAnt; i++)
            for (int j=0; j<this->n; j++)
            {
                if (ptrsNivelAnterior[i] == NULL)
                    ptrs[c] = NULL;
                else
                    ptrs[c] = ptrsNivelAnterior[i]->getPtr(j);
                c++;
            }

         return ptrs;


     }
}



void ArvoreNaria::remover(int info)
{
    No* atual = this->raiz;
    No* anterior = NULL;
    int indice;

    while(atual->indiceDe(info) == -1)
    {
        anterior = atual;

        if (info > atual->getDado(this->n-2))
        {
            atual = atual->getPtr(this->n-1);
            indice = this->n-1;
        }
        else
        if (info < atual->getDado(0))
        {
            atual = atual->getPtr(0);
            indice = 0;
        }
        else
        {
            for (int i=0; i<this->n-1; i++)
                if (info > atual->getDado(i) && info < atual->getDado(i+1))
                {
                    atual = atual->getPtr(i+1);
                    indice = i+1;
                    break;
                }
        }
    }
    //printf("%s - %s - %d", atual->toString(), anterior->toString(), indice);

    if (atual->ehFolha())
    {
        if (atual->qtsDados() == 1)
        {
            anterior->setPtr(indice, NULL);
            delete atual;
        }
        else
        {
            atual->setDado(atual->indiceDe(info), NULL);
            atual->ordenar();
        }
    }
    else
    {
        int index = atual->indiceDe(info);
        if (atual->getPtr(index) != NULL && atual->getPtr(index + 1) != NULL)
        {
            int esq = this->qtsNiveis(atual->getPtr(index), 0);
            int dir = this->qtsNiveis(atual->getPtr(index+1),0);

            if (esq >= dir)
            {
                int maior = this->getMaiorInfo(atual->getPtr(index));
                this->remover(maior);
                atual->setDado(index, maior);
            }
            else
            {
                int menor = this->getMenorInfo(atual->getPtr(index+1));
                this->remover(menor);
                atual->setDado(index, menor);
            }
        }
        else
        if (atual->getPtr(index) != NULL)
        {
            int maior = this->getMaiorInfo(atual->getPtr(index));
            this->remover(maior);
            atual->setDado(index, maior);
        }
        else
        if (atual->getPtr(index + 1) != NULL)
        {
            int menor = this->getMenorInfo(atual->getPtr(index+1));
            this->remover(menor);
            atual->setDado(index, menor);
        }
        else
        {
            int esq = -1, dir = -1;
            int indEsq, indDir = 0;

            for (int i=index; i>=0; i--)
                if (atual->getPtr(i) != NULL)
                {
                    esq = this->qtsNiveis(atual->getPtr(i), 0);
                    indEsq = i;
                    break;
                }

            for (int i=index+1; i<this->n; i++)
                if (atual->getPtr(i) != NULL)
                {
                    dir = this->qtsNiveis(atual->getPtr(i), 0);
                    indDir = i;
                    break;
                }

            if (esq >= dir)
            {
                int maior = this->getMaiorInfo(atual->getPtr(indEsq));
                this->remover(maior);
                atual->setDado(index, maior);
                atual->ordenar();
            }
            else
            {
                int menor = this->getMenorInfo(atual->getPtr(indDir));
                this->remover(menor);
                atual->setDado(index, menor);
                atual->ordenar();

            }
        }
    }
}


int ArvoreNaria::getMaiorInfo(No* ptr)
{
    No* atual = ptr;
    while (atual->getPtr(this->n-1) != NULL)
         atual = atual->getPtr(this->n-1);

    for (int i=this->n-2; i >= 0; i--)
        if (atual->getDado(i) != NULL)
            return atual->getDado(i);

    return NULL;
}


int ArvoreNaria::getMenorInfo(No* ptr)
{
    No* atual = ptr;
    while(atual->getPtr(0) != NULL)
        atual = atual->getPtr(0);

    for (int i=0; i<this->n-1; i++)
        if (atual->getDado(i) != NULL)
            return atual->getDado(i);

    return NULL;
}









void ArvoreNaria::test()
{
  /*  No* teste = this->raiz;
      for (int i=0; i<this->n; i++)
            if (teste->getPtr(i) != NULL)
                printf(" naoNUlo ");
            else
                printf(" tanulo ");*//*
      No** vet = this->getPtrsPorNivel(3);

      for (int i=0; i<27; i++)
        if (vet[i] != NULL)
         printf("%s\n", vet[i]->toString());
        else
         printf("NULO\n");*/

        printf("%d", this->getMenorInfo(this->raiz));

}





