#ifndef NO_H
#define NO_H



class No
{
    public:
        No(int);
        void inserir(int);
        int temVaga();
        void ordenar();
        char* toString();
        int getDado(int);
        void setDado(int, int);
        No* getPtr(int);
        void setPtr(int, No*);
        int ehFolha();
        int indiceDe(int);
        int qtsDados();

        ~No();




    protected:
    private:
        int* infos;
        No**  ptrs;
        int n;
};

#endif // NO_H
