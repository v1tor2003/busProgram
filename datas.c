#include "datas.h"

int valida_mes(int mes){
    if(mes > 0 && mes <= 12){
        return 1;
    }else{
        return 0;
    }
}

int valida_data(int dia_viagem, int mes_viagem, int ano_viagem){
    if ((dia_viagem > 0 && dia_viagem <= 31) && (mes_viagem == 1 || mes_viagem == 3 || mes_viagem == 5 || mes_viagem == 7 || mes_viagem == 8 || mes_viagem == 10 || mes_viagem == 12) && (ano_viagem == 2022)){
        return 1;
    }
    else if ((dia_viagem > 0 && dia_viagem <= 30) && (mes_viagem == 4 || mes_viagem == 6 || mes_viagem == 9 || mes_viagem == 11) && (ano_viagem == 2022)){
        return 1;
    }
    else if((dia_viagem > 0 && dia_viagem <= 29) && (mes_viagem == 2)){

    }else{
        return 0;
    }
}

int valida_hora(int hr_viagem, int minutos_viagem){
    if((hr_viagem == 12 || hr_viagem == 13 || hr_viagem == 14|| hr_viagem == 15 || hr_viagem == 16) && (minutos_viagem == 30)){
       return 1; 
    }else{
       return 0;
    }
}

// Se a data d1 for iguala data d2 retorna verdadeiro (1) sen�o retorna falso (0)
int eh_igual(Data d1, Data d2){
    if ((d1.ano == d2.ano) && (d1.mes == d2.mes) && (d1.dia == d2.dia)) // verifica se datas s�o iguais.
        return 1; // verdadeiro
    return 0;     // falso
}

int eh_igual_hora(Hora d1, Hora d2){
    if ((d1.hs == d2.hs) && (d1.mnto == d2.mnto))
        return 1;
    return 0;
}

// ---- verifica se um ano � bisexto ------------------------
int bisexto(int ano){
    if(ano%4==0 && (ano%400==0 || ano%100!=0))
        return 1;
    return 0;
}

Data cria(int dia, int mes, int ano){
    Data data;
    data.dia = dia;
    data.mes = mes;
    data.ano = ano;
    return data;
}

Hora cria_hora(int hr, int min){
    Hora hora;
    hora.hs = hr;
    hora.mnto = min;
    return hora;
}

// Incrementa em um dia a data d
Data incrementa(Data d){
    Data novo_d;
    int max_dias[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int max_meses = 12;
    //----- Considera o ano bisexto ------------------------
    if (bisexto(d.ano)){
        max_dias[1]=29;
    }
    //------------------------------------------------------------

    // Incrementa s� precisa mudar o dia. Os meses e anos continuam inalterados.
    if (d.dia < max_dias[d.mes-1]){
        novo_d.dia = d.dia+1;
        novo_d.mes = d.mes;
        novo_d.ano = d.ano;
    }
    else
    {
        // Al�m do dia, o m�s � alterado para o pr�ximo m�s pois chegou ao fim.
        if (d.mes < max_meses){
            novo_d.dia = 1;
            novo_d.mes = d.mes+1;
            novo_d.ano = d.ano;
        }
        else{ // chegou no fim do ano, precisa alterar o dia, o m�s e o ano.
            novo_d.dia = 1;
            novo_d.mes = 1;
            novo_d.ano = d.ano+1;
        }
    }
    return novo_d;
}
