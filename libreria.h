#include <iostream>
#include <fstream>
#include <stdio.h> //system('cls'), system ('pause'), 
#include <windows.h> //Sleep(5000) - el programa espera 5 segundos - o 5000ms
#include <cmath>
#include <limits.h> //INT_MIN, INT_MAX
#include <string>
using namespace std;
int leeciudad (string ciudad);
bool izqda (bool AMS, bool NaS, bool sol);
bool NaS (int ciudad1, int ciudad2);
bool AMS (int horasalida, int minutosalida, int horallegada, int minutollegada, int ano, int mes, int dia);
int minutero (int hora, int minuto);
bool continuar (int salida, int llegada, int amanecer, int anochecer, int ano, int mes, int dia);
int leeamanecer (int ano, int mes, int dia);
int leeanochecer (int ano, int mes, int dia);
int leemediodia (int ano, int mes, int dia);
string mediodiaBRUTO (int ano, int mes, int dia);

bool izqda (bool AMS, bool NaS, bool sol) {
        /* izqda - Izquierda: True-Izquierda, False-Derecha 
            AMS - Antes del Mediodía Solar: True-Antes, False-Después
            NaS - Norte a Sur: True-Dirección Norte a Sur, False-Dirección Sur a Norte
            sol - True: el usuario quiere sol, False: el usuario quiere sombra*/ 
    bool IZQDA=true;
    if (!AMS) IZQDA=!IZQDA;
    if (!sol) IZQDA=!IZQDA;
    if (!NaS) IZQDA=!IZQDA;
    return IZQDA;
};
bool AMS (int horasalida, int minutosalida,
        int horallegada, int minutollegada,
        int ano, int mes, int dia){
    int mediodia=leemediodia(ano, mes, dia);
    int llegada=minutero(horallegada, minutollegada);
    int salida=minutero(horasalida, minutosalida);
    if (llegada<mediodia) return true;
    if (salida>mediodia)  return false;
    return (mediodia-salida)>(llegada-mediodia);
};
int minutero (int hora, int minuto) {
    return (hora*60)+minuto;
};
/* Esto devuelve la latitud de la ciudad.
Dicho dato nos sirve después para saber si vamos en dirección Norte-Sur o al revés */
int leeciudad (string ciudad) {
    int latitud=0;
    while (latitud==0){
        ifstream lectura;
        lectura.open("ciudades.txt");
        if (lectura.is_open()) {
            string buscada;
            while (!lectura.eof()) {
            lectura>>buscada;
                if (ciudad==buscada){
                    lectura>>ciudad;
                    latitud=stoi(ciudad);
                    return latitud;
                }
            }
        } else {
            cout<<"ERROR! No se encuentra el archivo de texto 'ciudades.txt'"<<endl;
        }
            lectura.close();
    }
};
/* Aqui comparamos */
bool NaS (int ciudad1, int ciudad2) {
    return ciudad1<ciudad2;
};
/* La siguiente función determina si tiene sentido continuar con todo el proceso, 
o si por el contrario podemos decirle al usuario que no se preocupe,
que no le va a dar el sol (porque ni siquiera va a ser de dia)*/
bool continuar (int horasalida, int minutosalida,
              int horallegada, int minutollegada,
              int ano, int mes, int dia){
    int salida=minutero(horasalida, minutosalida);
    int llegada=minutero(horallegada, minutollegada);
    int amanecer=leeamanecer(ano, mes, dia);
    int anochecer=leeanochecer(ano, mes, dia);
    return llegada<amanecer || salida>anochecer;
};
/* Las siguientes funciones obtienen las horas requeridas del fichero */
int leeamanecer (int ano, int mes, int dia) {
    int DATO[365][9];
    ifstream lectura;
    lectura.open("solito.txt");
    if (lectura.is_open()){
        for (int i = 0; i < 365; i++) {
            for (int j = 0; j < 9; j++) {
                lectura>>DATO[i][j];
            }
        }
    } else {
        cout<<"ERROR! No se encuentra el archivo de texto 'solito.txt'"<<endl;
    }
    lectura.close();
        for (int i = 0; i < 365; i++) {
            for (int j = 0; j < 9; j++) {
                if (DATO[i][j]==ano && DATO[i][j+1]==mes && DATO[i][j+2]==dia) {
                    int hora=DATO[i][j+3];
                    int minuto=DATO[i][j+4];
                    return minutero(hora, minuto);
                }
            }
        }
};
int leeanochecer (int ano, int mes, int dia) {
    int DATO[365][9];
    ifstream lectura;
    lectura.open("solito.txt");
    if (lectura.is_open()){
        for (int i = 0; i < 365; i++) {
            for (int j = 0; j < 9; j++) {
                lectura>>DATO[i][j];
            }
        }
    } else {
        cout<<"ERROR! No se encuentra el archivo de texto 'solito.txt'"<<endl;
    }
    lectura.close();
        for (int i = 0; i < 365; i++) {
            for (int j = 0; j < 9; j++) {
                if (DATO[i][j]==ano && DATO[i][j+1]==mes && DATO[i][j+2]==dia) {
                    int hora=DATO[i][j+5];
                    int minuto=DATO[i][j+6];
                    return minutero(hora, minuto);
                }
            }
        }
};
int leemediodia (int ano, int mes, int dia) {
    int DATO[365][9];
    ifstream lectura;
    lectura.open("solito.txt");
    if (lectura.is_open()){
        for (int i = 0; i < 365; i++) {
            for (int j = 0; j < 9; j++) {
                lectura>>DATO[i][j];
            }
        }
    } else {
        cout<<"ERROR! No se encuentra el archivo de texto 'solito.txt'"<<endl;
    }
    lectura.close();
        for (int i = 0; i < 365; i++) {
            for (int j = 0; j < 9; j++) {
                if (DATO[i][j]==ano && DATO[i][j+1]==mes && DATO[i][j+2]==dia) {
                    int hora=DATO[i][j+7];
                    int minuto=DATO[i][j+8];
                    return minutero(hora, minuto);
                }
            }
        }
};
/* Esta funcion sólo es invocada en circunstancias muy concretas:
para imprimir el mediodia solar como string */
string mediodiaBRUTO (int ano, int mes, int dia) {
    int DATO[365][9];
    ifstream lectura;
    lectura.open("solito.txt");
    if (lectura.is_open()){
        for (int i = 0; i < 365; i++) {
            for (int j = 0; j < 9; j++) {
                lectura>>DATO[i][j];
            }
        }
    } else {
        cout<<"ERROR! No se encuentra el archivo de texto 'solito.txt'"<<endl;
    }
    lectura.close();
        for (int i = 0; i < 365; i++) {
            for (int j = 0; j < 9; j++) {
                if (DATO[i][j]==ano && DATO[i][j+1]==mes && DATO[i][j+2]==dia) {
                    int hora=DATO[i][j+7];
                    int minuto=DATO[i][j+8];
                    string mediodia=to_string(hora);
                    mediodia+=":";
                    mediodia+=to_string(minuto);
                    return mediodia;
                }
            }
        }
};

/* Funcion REPETIDA pero que desarrollé por no saber que ya existía,
 y ahí queda como testigo de mi ignorancia e inventiva */

/* int STOI (string cadena); */
/* int STOI (string cadena) {
    int num=0;
    for (int i = 0; i < cadena.length(); i++){
                    switch (cadena[i]){
                    case '1':
                        num+=pow(10, (cadena.length()-i));
                        break;
                    case '2':
                        num+=2*pow(10, (cadena.length()-i));
                        break;
                    case '3':
                        num+=3*pow(10, (cadena.length()-i));
                        break;
                    case '4':
                        num+=4*pow(10, (cadena.length()-i));
                        break;
                    case '5':
                        num+=5*pow(10, (cadena.length()-i));
                        break;
                    case '6':
                        num+=6*pow(10, (cadena.length()-i));
                        break;
                    case '7':
                        num+=7*pow(10, (cadena.length()-i));
                        break;
                    case '8':
                        num+=8*pow(10, (cadena.length()-i));
                        break;
                    case '9':
                        num+=9*pow(10, (cadena.length()-i));
                        break;
                    default:
                        break;
                    }
                }
                return num;
}; */
