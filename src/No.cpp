#include "No.h"
#include<stdio.h>
#include<string>
#include<string.h>
No::No(int n)
{
    this->n = n;
    this->infos = new int[n-1];
    this->ptrs  = new No*[n];

    int i=0;
    for (i; i<n; i++)
    {
       if(i != n)
          this->infos[i] = NULL;
       this->ptrs[i] = NULL;
    }
}


No::~No()
{
    delete []infos;
    for (int i=0; i<this->n; i++)
        if (ptrs[i] != NULL)
        delete ptrs[i];
    delete []ptrs;
}

int No::temVaga()
{
    int ret = 0;
    for (int i=0; i<this->n - 1; i++)
        if (this->infos[i] == NULL)
        {
           ret++;
        }

    return ret;
}

int No::ehFolha()
{
    int ret = 0;
    for (int i=0; i<this->n; i++)
        if (this->ptrs[i] == NULL)
        {
           ret++;
        }

    if (ret == this->n)
        return 1;
    else
        return 0;
}



void No::inserir(int info)
{
    for (int i=0; i<this->n-1; i++)
        if(this->infos[i] == NULL)
        {
            this->infos[i] = info;
            break;
        }

    this->ordenar();
}


void No::ordenar()
{
    for (int i=0; i<this->n-1; i++)
        for (int j=i+1; j<this->n-1; j++)
            if (this->infos[i] > this->infos[j])
            {
                int aux = this->infos[i];
                this->infos[i] = this->infos[j];
                this->infos[j] = aux;
            }
}

char* No::toString()
{
    char* inteiro = new char[10];
    strcpy(inteiro, "");
    char* ret = new char[10];
    strcpy(ret, "");

    for(int i=0; i<this->n-1; i++)
    {
        if (this->infos[i] != NULL)
            sprintf(inteiro, "|%d|", this->infos[i]);
        else
            sprintf(inteiro, "| |");
        strcat(ret, inteiro);
    }

    return ret;
}


int No::getDado(int i)
{
    return this->infos[i];
}

void No::setDado(int i, int dado)
{
    this->infos[i] = dado;
}

No* No::getPtr(int i)
{
    return this->ptrs[i];
}

void No::setPtr(int i, No* ptr)
{
    this->ptrs[i] = ptr;

}

int No::indiceDe(int info)
{
    for (int i=0; i<this->n-1; i++)
        if (this->infos[i] == info)
            return i;
    return -1;
}


int No::qtsDados()
{
    int qts = 0;
    for (int i=0; i<this->n-1; i++)
        if (this->infos[i] != NULL)
           qts++;

    return qts;
}


