#ifndef DATAS_H_INCLUDED
#define DATAS_H_INCLUDED

//--------------- Estrutura de Data --------------------------
typedef struct{
    int dia;
    int mes;
    int ano;
} Data;

//----------------------- Estrutura de Hora -----------------------------------
typedef struct{
    int hs;
    int mnto;
} Hora;

// ---- verifica se um ano � bisexto ------------------------
int bisexto(int ano);

//------------------ Incrementa a Data em um dia---------------------------------
Data incrementa(Data d);

//---------------- Verifica se duas dadas s�o iguais ---------------------------
int eh_igual(Data d1, Data d2);

//---------------- Verifica se duas horas s�o iguais ---------------------------
int eh_igual_hora(Hora d1, Hora d2);

//-------------  Cria uma nova data -------------------------
Data cria(int dia, int mes, int ano);

//-------------  Cria uma nova hora -------------------------
Hora cria_hora(int hr, int min);

int valida_data(int dia_viagem, int mes_viagem, int ano_viagem);
int valida_hora(int hr_viagem, int minutos_viagem);
int valida_mes(int mes);
#endif // DATAS_H_INCLUDED
