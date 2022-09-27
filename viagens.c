#include "viagens.h"
#include <string.h>

// --- Cria o vetor viagem com as viagens no hor�rio do vetor de horas rio_sp e sp_rio das datas compreendidas entre dt_ini e dt_fim --
// --- Os assentos do onibus s�o inicializadas com 0 --
int inicializa_viagens(Viagem *viagem, Data dt_ini, Data dt_fim, Hora *rio_sp, Hora *sp_rio){
    int i;
    int j=0;
    Data dt_ini2;
    int contador=0;

    dt_ini2.dia = dt_ini.dia;
    dt_ini2.mes = dt_ini.mes;
    dt_ini2.ano = dt_ini.ano;

    for (i=0; !eh_igual(dt_ini,dt_fim); i++ ){
        viagem[i].data.dia = dt_ini.dia;
        viagem[i].data.mes = dt_ini.mes;
        viagem[i].data.ano = dt_ini.ano;
        viagem[i].hora.hs   = rio_sp[j].hs;
        viagem[i].hora.mnto = rio_sp[j].mnto;
        viagem[i].direcao   = RJ_SP;
        j++;
        if (j==5)
        {
                dt_ini = incrementa(dt_ini);
                j=0;
        }
        contador++;
        int k;
        for(k=0;k < TAM_ASSENTOS; k++)
        {
            viagem[i].assento[k] = NULL;
        }

    }

    for (  ; !eh_igual(dt_ini2,dt_fim); i++ ){
        viagem[i].data.dia = dt_ini2.dia;
        viagem[i].data.mes = dt_ini2.mes;
        viagem[i].data.ano = dt_ini2.ano;
        viagem[i].hora.hs   = sp_rio[j].hs;
        viagem[i].hora.mnto = sp_rio[j].mnto;
        viagem[i].direcao   = SP_RJ;
        j++;
        if (j==5){
                dt_ini2 = incrementa(dt_ini2);
                j=0;
        }
        contador++;
        int k;
        for(k=0;k < TAM_ASSENTOS; k++)
        {
            viagem[i].assento[k] = 0;
        }
    }
return contador;
}

//-----------------------------------------------
// Menu de op��es para o usu�rio escolher
//-----------------------------------------------
int obter_opcao(){
    int opcao;
    do{
        printf("\nMenu:");
        printf("\n1 - Comprar passagem");
        printf("\n2 - Total arrecadado para uma determinada viagem");
        printf("\n3 - Total arrecadado em um determinado mes");
        printf("\n4 - Nome do passageiro de uma  poltrona de uma determinada viagem");
        printf("\n5 - Horario de viagem mais rentavel");
        printf("\n6 - Media de idade dos passageiros");
        printf("\n7 - Terminar programa");
        printf("\nDigite a sua opcao: ");
        scanf("%d", &opcao);
        if ((opcao < 1) || (opcao >7)){
            printf("\n\n Opcao invalida. Digite um numero entre 1 e 7 por favor...\n");
        }   
    } while ((opcao < 1) || (opcao > 7));
    return opcao;
}

void compra_passagem(Viagem *viagem,Data di,Data df){
    int achou_viagem = 0;
    int assento_desejado;
    Data dt_viagem;
    int dia_viagem, mes_viagem, ano_viagem, direcao_viagem;
    int hr_viagem, minutos_viagem;
    Hora hora_viagem;
    int i, indice_viagem=0;
    char cpf[TAM_CPF], nome[TAM_NOME];
    int idade;
    Passageiro passageiro;
    int valido = 0, pulaF = 0, pulaC = 0;


    printf("\n---------------------------------------------------------");
    printf("\n    Compra de Passagem ");
    printf("\n---------------------------------------------------------");

    printf("\nDigite a data desejada (dd mm aaaa):");
    while (valido != 1){
        scanf("%d %d %d", &dia_viagem, &mes_viagem, &ano_viagem);
        valido = valida_data(dia_viagem, mes_viagem, ano_viagem);
        if(valido == 0){
            puts("Digite uma data valida:");
        }else{
            break;
        }
    }
    valido = 0;
    printf("\nDigite o horario (hr mn):");
    while (valido != 1){
        scanf("%d %d", &hr_viagem, &minutos_viagem);
        valido = valida_hora(hr_viagem, minutos_viagem);
        if(valido == 0){
            puts("Digite um horario valido:");
        }else{
            break;
        }
    }
    
    dt_viagem = cria(dia_viagem, mes_viagem, ano_viagem);
    hora_viagem = cria_hora(hr_viagem, minutos_viagem);

    printf("\nDigite a direcao (0 - RJ-SP, 1 - SP-RJ): ");
    scanf("%d",&direcao_viagem);

    while (!achou_viagem)
    {
        if (eh_igual(viagem[indice_viagem].data, dt_viagem) &&
            viagem[indice_viagem].direcao == direcao_viagem &&
            eh_igual_hora(viagem[indice_viagem].hora, hora_viagem))

            achou_viagem = 1; // verdadeiro
        else
            indice_viagem++;

        if(eh_igual(viagem[indice_viagem].data,df))

            achou_viagem = -1; // Viagem inv�lida - n�o est� no intervalo inicializado

    }

    if( achou_viagem == -1)
        printf("\nData Escolhida invalida, nao pertence ao ano corrente");
    else
    {
        printf("\n ---------- Assentos Disponiveis --------------------\n");
        puts("(Assentos com '@' representam os ocupados)");
        printf("\n");

        for(i=0; i<TAM_ASSENTOS; i++)
        {
            if(viagem[indice_viagem].assento[i] == NULL){
                printf("%d ", i+1);
                pulaF++;
                if(pulaF == 10){
                    pulaF = 0;
                    pulaC++;
                    if(pulaC == 2){
                        printf("\n\n");
                    }
                    printf("\n");
                }
            }else if(viagem[indice_viagem].assento[i] != NULL){
                printf("@ ");
                pulaF++;
                if(pulaF == 10){
                    pulaF = 0;
                    pulaC++;
                    if(pulaC == 2){
                        printf("\n\n");
                    }
                    printf("\n");
                }
            }
        }
      
        printf("\n\nQual assento deseja comprar?");
        scanf("%d",&assento_desejado);

        printf("\nDigite o CPF: ");
        scanf("%s", cpf);

        printf("\nDigite o Nome: ");
        scanf("%s", nome);
        fflush(stdin);
        printf("\nDigite o Idade: ");
        scanf("%d", &idade);

        viagem[indice_viagem].assento[assento_desejado-1] = (Passageiro*) malloc(sizeof(Passageiro));
        strcpy(viagem[indice_viagem].assento[assento_desejado-1]->cpf, cpf);
        strcpy(viagem[indice_viagem].assento[assento_desejado-1]->nome, nome);
        viagem[indice_viagem].assento[assento_desejado-1]->idade = idade;

        printf("\nPassageiro inserido com sucesso\n");

    }
}

int valida_direcao(int direcao){
    if(direcao == 0 || direcao == 1){
        return 1;
    }else{
        return 0;
    }
}

void tot_por_viagem(Viagem *viagem){
    int total = 0, i = 0,j = 0, valido = 0;
    int dia_viagem, mes_viagem, ano_viagem, direcao_viagem;
    int hr_viagem, minutos_viagem;
    int direcao;
    puts("Opcao escolhida: Total arrecadado para tal viagem.");   
    printf("\nDigite a data da viagem desejada (dd mm aaaa):");
   
    while (valido != 1){
        scanf("%d %d %d", &dia_viagem, &mes_viagem, &ano_viagem);
        valido = valida_data(dia_viagem, mes_viagem, ano_viagem);
        if(valido == 0){
            puts("Digite uma data valida:");
        }else{
            break;
        }
    }
    valido = 0;
    printf("\nDigite o horario da viagem desejada (hr mn):");
    while (valido != 1){
        scanf("%d %d", &hr_viagem, &minutos_viagem);
        valido = valida_hora(hr_viagem, minutos_viagem);
        if(valido == 0){
            puts("Digite um horario valido:");
        }else{
            break;
        }
    }
    valido = 0;
    printf("\nDigite a direcao da viagem (0 - RJ-SP, 1 - SP-RJ): ");
    
    while (valido != 1){
       scanf("%d", &direcao);
       valido = valida_direcao(direcao);
       if(valido == 0){
           puts("Digite uma direcao valida:");
       }else {
           break;
       }
    }
    
    valido = 0;

    for(i = 0; i < 10000;i++){
        if(viagem[i].data.dia == dia_viagem && viagem[i].data.mes == mes_viagem && viagem[i].hora.hs == hr_viagem && viagem[i].hora.mnto == minutos_viagem && viagem[i].direcao == direcao){
            for(j = 0; j < TAM_ASSENTOS; j++){
                if(viagem[i].assento[j] != NULL){
                  total++;
                }      
            }
            break;
        } 
    }
    printf("Total arrecadado pra viagem na data %d/%d/%d e no horario %d:%d = R$ %d\n", dia_viagem, mes_viagem, ano_viagem, hr_viagem, minutos_viagem, (total * PASS_PREÇO));
    
}

void tot_mes(Viagem *viagem){

    int total = 0, i, j;
    int mes, valido = 0;
    puts("Opcao escolhida: Total por mes.");
    printf("\nDigite um mes desejado: ");

    while (valido != 1){
        scanf("%d", &mes);
        valido = valida_mes(mes);
        if(valido == 0){
            puts("Digite um mes valido:");
        }else{
            break;
        }
    }
    
    for(i = 0; i < 10000;i++){
        if(viagem[i].data.mes == mes && viagem[i].direcao == RJ_SP){
            for(j = 0; j < TAM_ASSENTOS; j++){
                if(viagem[i].assento[j] != NULL){
                  total++;
                }      
            }
        } 
        if(viagem[i].data.mes == mes && viagem[i].direcao == SP_RJ){
            for(j = 0; j < TAM_ASSENTOS; j++){
                if(viagem[i].assento[j] != NULL){
                  total++;
                }      
            }
        } 
    }
    
    printf("Total arrecadado no mes %d eh = R$ %d\n", mes, (total * PASS_PREÇO));
}

int valida_poltrona(int poltrona){
    if(poltrona > 0 && poltrona <= 40){
        return 1;
    }else{
        return 0;
    }
}

void obter_passageiro_poltrona(Viagem *viagem){
    int i = 0,j = 0, valido = 0;
    int dia_viagem, mes_viagem, ano_viagem;
    int hr_viagem, minutos_viagem;
    int direcao, poltrona;
    
    puts("Opcao escolhida: Obter passageiro em tal poltrona em uma determinada viagem.");   
    printf("\nDigite a data da viagem desejada (dd mm aaaa):");
   
    while (valido != 1){
        scanf("%d %d %d", &dia_viagem, &mes_viagem, &ano_viagem);
        valido = valida_data(dia_viagem, mes_viagem, ano_viagem);
        if(valido == 0){
            puts("Digite uma data valida:");
        }else{
            break;
        }
    }
    valido = 0;
    printf("\nDigite o horario da viagem desejada (hr mn):");
    while (valido != 1){
        scanf("%d %d", &hr_viagem, &minutos_viagem);
        valido = valida_hora(hr_viagem, minutos_viagem);
        if(valido == 0){
            puts("Digite um horario valido:");
        }else{
            break;
        }
    }
    valido = 0;
    
    printf("\nDigite a direcao da viagem (0 - RJ-SP, 1 - SP-RJ): ");
    
    while (valido != 1){
       scanf("%d", &direcao);
       valido = valida_direcao(direcao);
       if(valido == 0){
           puts("Digite uma direcao valida:");
       }else {
           break;
       }
    }
    
    valido = 0;

    printf("Digite a poltrona desejada:");

    while (valido != 1){
       scanf("%d", &poltrona);
       valido = valida_poltrona(poltrona);
       if(valido == 0){
           puts("Digite uma poltrona valida:");
       }else {
           break;
       }
    }
    
    poltrona = poltrona -1;

    for(i = 0; i < 10000;i++){
        if(viagem[i].data.dia == dia_viagem && viagem[i].data.mes == mes_viagem && viagem[i].hora.hs == hr_viagem && viagem[i].hora.mnto == minutos_viagem && viagem[i].direcao == direcao){
            for(j = 0; j < TAM_ASSENTOS; j++){
                if(viagem[i].assento[j] != NULL && j == poltrona){
                    printf("O passageiro na poltrona %d eh %s\n", poltrona + 1, viagem[i].assento[j]->nome);
                    break;
                }else if(viagem[i].assento[j] == NULL && j == poltrona){
                    printf("A poltrona %d esta vazia\n", poltrona + 1);
                    break;
                }
            }
        } 
    }
}

void obter_horario_mais_retavel(Viagem *viagem){
    // nao consegui fazer essa funcao, embaixo segue uma tentativa da solucao
    int i,j, k = 0;
    int maior, hora = 12, horario_posicao, arrecadacao_parcial = 0;
    int arrecadacoes[5] = {0};
    int horarios[5] = {12, 13, 14, 15, 16};
    
    puts("Opcao escolhida: Horario mais rentavel.");
    
    for(i = 0; i < 10000; i++){                               // 12   12  12  12
        if(viagem[i].hora.hs == hora){                        // 40   50  60  80 
            for(j = 0; j < TAM_ASSENTOS; j++){
                if(viagem[i].assento[j] != NULL){
                    arrecadacao_parcial++;
                }
            }
            arrecadacoes[k] = arrecadacao_parcial;
            arrecadacao_parcial = 0;
        }if(viagem[i].hora.hs != hora){
            k++;
            hora++;
        }
    }
    maior = arrecadacoes[0];
    for(i = 0; i < 5; i++){
        if(maior > arrecadacoes[i]){
            maior = arrecadacoes[i];
            horario_posicao = i;
        }
    }
    printf("O horario mais rentavel eh %d:30 com uma arrecadacao de R$ %d\n", horarios[horario_posicao], (maior*PASS_PREÇO));
}

void obter_media_idade(Viagem *viagem){
    int i, j;
    int soma = 0;
    int qntd_passageiros = 0;
    int media;
    puts("Opcao escolhida: Media de idade dos passageiros.");
    for(i = 0; i < 10000; i++){
        for(j = 0; j < TAM_ASSENTOS; j++){
            if(viagem[i].assento[j] != NULL){
                qntd_passageiros++;
                soma += viagem[i].assento[j]->idade;
            }
        } 
    }
    media = soma / qntd_passageiros;
    printf("A media de idade dos passageiros cadastrados eh %d anos\n", media);
}    
