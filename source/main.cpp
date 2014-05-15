/*
 *  Autor: Zoé Magalhães (zr.magal@gmail.com)
 *  Mestrando do PPMEC-Unb, matrícula 170172767
 *  Disciplina: Controle Preditivo 01/2018
 *  Professor: André Murilo
 *
 *  Controle de estabilidade veicular lateral
 *  pela aplicacao de um controle preditivo
 *  baseado em modelo linear. Aplicacao
 *  desenvolvida para simulacao HIL  
 */

#include "mpc.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <signal.h>
#include <sys/time.h>
#include <stdlib.h>

#define UPDATE_TIME_US ( 500000 ) 

using namespace std;

void catch_alarm_setitimer (int sig_num)
{
    cout << sig_num << "\n";
}

void intFinalize(int sig_num) 
{
    cout << "Done.\n";
    exit(0);
}

int main()
{
    MPC mpc;
    signal(SIGALRM, catch_alarm_setitimer);
    signal(SIGINT, intFinalize);
    cout << "\r\nPressione alguma tecla para comecar";
    getchar();
    ualarm(UPDATE_TIME_US, UPDATE_TIME_US);
    while(1){usleep(10);}
    return 0;
}
