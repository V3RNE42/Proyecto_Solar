#include <iostream>
#include <stdio.h>
#include "libreria.h"
using namespace std;
int main() {
    SetConsoleOutputCP(CP_UTF8);
    cout<<"¡Bienvenido al sistema de elección de sitios para trayectos peninsulares!"<<endl;
    cout<<"Gracias por confiar en nuestro sistema para sus trayectos entre capitales de provincia :)"<<endl;
    cout<<"Este programa toma en consideración la latitud de las ciudades, la "<<endl;
    cout<<"hora del alba y del ocaso, las horas de salida y las de llegadas, así como "<<endl;
    cout<<"la preferencia del usuario sobre si quiere sol o sombra...  "<<endl;
    cout<<"Introduzca toda la información para poder obtener tu sitio: en el lado izquierdo o derecho del vehículo  "<<endl;
    system("pause");
    system("cls");
    
    string origen="";
    string destino="";
    while (origen=="") {
    cout<<"Introduzca la capital de provincia de ORIGEN"<<endl<<"(Respetando mayúsculas, sin tildes, sin Ñ, y con guiones en lugar de espacios)"<<endl;
    cin>>origen;
    }
    while (destino=="") {
    cout<<"Introduzca la capital de provincia de DESTINO"<<endl<<"(Respetando mayúsculas, sin tildes, sin Ñ, y con guiones en lugar de espacios)"<<endl;
    cin>>destino;
    }
    int ALTorigen=leeciudad(origen);
    int ALTdestino=leeciudad(destino);
    int horasalida=-1;
    while (horasalida<0){
        cout<<"Introduzca la HORA (en formato 24h) de salida desde "<<origen<<endl;
        cin>>horasalida;
    }
    int minutosalida=-1;
    while (minutosalida<0){
        cout<<"Introduzca el MINUTO de salida desde "<<origen<<endl;
        cin>>minutosalida;
    }
    int horallegada=-1;
    while (horallegada<0 || horallegada<horasalida){
        cout<<"Introduzca la HORA (en formato 24h) de llegada a "<<destino<<endl;
        cin>>horallegada;
    }
    int minutollegada=-1;
    while (minutollegada<0 || minutero(horallegada,minutollegada)<=minutero(horasalida,minutosalida)){
        cout<<"Introduzca el MINUTO de llegada a "<<destino<<endl;
        cin>>minutollegada;
    }
    int ano=-1;
    while (ano<0){
        cout<<"Introduzca el ANO del viaje"<<endl;
        cout<<"Tenga en cuenta que la aplicación solo cubre desde Marzo/22 hasta Febrero/23"<<endl;
        cout<<":-I";
        cin>>ano;
    }
    int mes=-1;
    while (mes<0){
        cout<<"Introduzca el número de MES de salida del viaje"<<endl;
        cin>>mes;
    }
    int dia=-1;
    while (dia<0){
        cout<<"Introduzca el DIA de salida del viaje"<<endl;
        cin>>dia;
    }
    int SALIDA, LLEGADA, AMANECER, ANOCHECER, MEDIODIA;
    SALIDA=minutero(horasalida, minutosalida);
    LLEGADA=minutero(horallegada, minutollegada);
    AMANECER=leeamanecer(ano, mes, dia);
    ANOCHECER=leeanochecer(ano, mes, dia);
    MEDIODIA=leemediodia(ano, mes, dia);
    bool proseguir=continuar(SALIDA, LLEGADA, AMANECER, ANOCHECER, ano, mes, dia);
    if (!proseguir) {
        cout<<"No te preocupes: vas a viajar de noche, como Batman";
        return 0;
    }
    bool cambio;
    cout<<"¿Es posible cambiar asiento una vez compraste el billete?"<<endl<<"\t 1-Sí"<<endl<<"\t 0-No"<<endl;
    cin>>cambio;
    if (cambio){
        if (SALIDA>MEDIODIA || LLEGADA<MEDIODIA){
            cout<<"Siéntate donde quieras, pero recuerda que a las "<<mediodiaBRUTO(ano,mes,dia)<<" deberías cambiarte al lado opuesto del vehículo";
        } else {
            cout<<"Siéntate donde quieras mi pana";
        return 0;
        }
    } else {
    bool sol;
    cout<<"¿Prefieres que te de el sol, o prefieres estar a la sombra?"<<endl<<"\t 1-Solito"<<endl<<"\t 0-Sombrita"<<endl;
    cin>>sol;
    bool AntesMDS=AMS(horasalida,minutosalida,horallegada,minutollegada,ano,mes,dia);
    int ORIGEN, DESTINO;
    ORIGEN=leeciudad(origen);
    DESTINO=leeciudad(destino);
    bool NorteASur=NaS(ORIGEN, DESTINO);
    bool sitio=izqda(AntesMDS,NorteASur,sol);
    if (sitio) {
        cout<<"Siéntate en el lado izquierdo, el del conductor";
    } else {
        cout<<"Siéntate en el lado derecho, el contrario al conductor";
    }
    return 0;
    }
}