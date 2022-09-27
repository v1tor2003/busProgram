/*
Uma empresa de �nibus faz diariamente 5 viagens de ida e 5 viagens de
volta entre as cidades do Rio de Janeiro e S�o Paulo. Cada �nibus tem 40
assentos para serem preenchidos por passageiros. A empresa costuma
vender as passagens antecipadamente, e para cada passagem vendida �
anotado o n�mero do assento, a data e hora, o CPF, o nome e a idade do
passageiro. As passagens s�o vendidas por 80 reais cada.
Fa�a um programa para gerenciar a venda de passagens de �nibus. O
programa deve possibilitar obter as seguintes informa��es:
1. Qual o total arrecadado para uma determinada viagem.
2. Qual o total arrecadado em um determinado m�s.
3. Qual o nome do passageiro de uma determinada poltrona P de uma
determinada viagem.
4. Qual o hor�rio de viagem mais rent�vel.
5. Qual a m�dia de idade dos passageiros.
*/
#include "viagens.c"
#include "datas.c"

Viagem viagem[10000];

int main(){
    Data di, df;  // data inicial e data final
    //-------------- Especifica os hor�rios das viagens de Onibus do rio para s�o paulo e vice-versa ------
    Hora rio_sp[5], sp_rio[5];
    rio_sp[0].hs = 12;
    rio_sp[0].mnto = 30;
    rio_sp[1].hs = 13;
    rio_sp[1].mnto = 30;
    rio_sp[2].hs = 14;
    rio_sp[2].mnto = 30;
    rio_sp[3].hs = 15;
    rio_sp[3].mnto = 30;
    rio_sp[4].hs = 16;
    rio_sp[4].mnto = 30;

    sp_rio[0].hs = 12;
    sp_rio[0].mnto = 30;
    sp_rio[1].hs = 13;
    sp_rio[1].mnto = 30;
    sp_rio[2].hs = 14;
    sp_rio[2].mnto = 30;
    sp_rio[3].hs = 15;
    sp_rio[3].mnto = 30;
    sp_rio[4].hs = 16;
    sp_rio[4].mnto = 30;

    //---  Cria uma data inicial e final para inicializar as viagens do sistema -------
    di.dia = 1;
    di.mes = 1;
    di.ano = 2022;

    df.dia = 31;
    df.mes = 12;
    df.ano = 2022;

    int cont; // contador que especifica o tamanho do vetor de viagens.

    cont = inicializa_viagens(viagem, di, df, rio_sp, sp_rio );  // Cria o vetor viagem com todas as viagens programadas
    int opcao;

    while (opcao != 7){
        opcao = obter_opcao();
        if (opcao == 1){
            compra_passagem(viagem,di,df);
        }else if (opcao == 2){
            tot_por_viagem(viagem);                   
        }else if (opcao == 3){
            tot_mes(viagem);                        
        }else if (opcao ==4){
            obter_passageiro_poltrona(viagem);     
        }else if (opcao == 5){
            obter_horario_mais_retavel(viagem);    //nao consegui resolver
        }else if (opcao == 6){
            obter_media_idade(viagem);            
        }
    }
    printf("\n\n--------  F   I   M     D  O    P  R  O  G  R  A  M  A  ------------------\n ");
    return 0;
}
