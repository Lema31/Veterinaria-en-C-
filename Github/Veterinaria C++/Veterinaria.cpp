/*Proyecto de Datos 4: Registros
Integrantes:
Arismendi, Juan Diego CI 29.655.485
Mata, Luis Eduardo CI 29.655.551
Seccion: 0500*/

#include<iostream>
#include<string.h>
#include<conio.h>
#include<sstream>
using namespace std;

struct Fecha{
    int Anio;
    int Mes;
    int Dia;
}FechaHoy[100],FechaCitaPrevia,CitasPrevias[100];
struct DatosPerro{
    char Raza[15];
    float Tamanio;
    int Anios;
    int Meses;
    char EstadoEntrada[10];
    char EstadoSalida[10];
    struct Fecha FechaCita;
    char ObservacionDoctor[50];
};
struct DatosCliente{
    char Nombre[30];
    long Cedula;
    int Edad;
    int MascotasRegistradas=0;
    int MascotasRegistradasPrevias=0;
    struct DatosPerro Mascotas[5];
}Clientes[15];

void TransformarFechaHoy(char []);
void TransformarFechaCita(char []);
void PedirDatosCliente();
void PedirDatosMascotas();
void EstadoEntrada_Salida();

void OpcionCita(char []);
int ComprobarFechaMayor(Fecha,Fecha);
int ComprobarEstructuraFecha(Fecha);
void ComprobarOpc(char []);
void MostrarMascotasRegistradas();
int ComprobarFechaConsulta();

void MostrarMascotasGraves();
int TotalMascotasRecuperadas();

int i,j,k,l,OpcConsulta,ContClientes=0,EstadoIncorrecto,ContCitas=0,PrimerRecorrido=0,ContFechaHoy=0,AuxContclientes=0;
char Opc[10];
char OpcCita[10];
int main(){
    char FechaCadena[15];
    for(i=0;i<100;i++){
        if(PrimerRecorrido==1){
            cout<<"Si desea cambiar la fecha del dia de hoy presione '0', si desea mantener la misma fecha, presione cualquier otro numero"<<endl;
            cin>>PrimerRecorrido;
            if(PrimerRecorrido==0){
                ContFechaHoy++;
            }
        }
        if(PrimerRecorrido==0){
            fflush(stdin);
            cout<<"Indica la fecha del dia de hoy, recuerde utilizar un '-' para separar los numeros: ";cin.getline(FechaCadena,15,'\n');
            TransformarFechaHoy(FechaCadena);
            while(ComprobarEstructuraFecha(FechaHoy[ContFechaHoy])<3){
                cout<<"Recuerde que la fecha se debe entregar en el formato YYYY-MM-DD, por favor ingresela nuevamente: ";
                cin.getline(FechaCadena,15,'\n');
                TransformarFechaHoy(FechaCadena);
            }
        }
        if(ContFechaHoy>0){
            fflush(stdin);
            while(ComprobarFechaMayor(FechaHoy[ContFechaHoy],FechaHoy[ContFechaHoy-1])==0){
                cout<<"La fecha debe ser mayor a la introducida anteriormente,por favor ingresela nuevamente: ";
                cin.getline(FechaCadena,15,'\n');
                TransformarFechaHoy(FechaCadena);
                while(ComprobarEstructuraFecha(FechaHoy[ContFechaHoy])<3){
                    cout<<"Recuerde que la fecha se debe entregar en el formato YYYY-MM-DD, por favor ingresela nuevamente: ";
                    cin.getline(FechaCadena,15,'\n');
                    TransformarFechaHoy(FechaCadena);
                }
            }
        }
        fflush(stdin);
        PrimerRecorrido=1;
        cout<<"\nEscriba 1 si desea pedir una cita"<<endl;
        cout<<"Escriba 2 si viene por una consulta"<<endl;
        cout<<"Escriba 3 para cerrar el programa"<<endl;cin>>OpcConsulta;
        while((OpcConsulta<1) &&(OpcConsulta>3)){
            cout<<"La opcion seleccionada no se encuentra disponible, por favor ingresela nuevamente: "<<endl;cin>>OpcConsulta;
        }
        if((OpcConsulta==1)||(OpcConsulta==2)){
        PedirDatosCliente();
        fflush(stdin);
        }
        else if(OpcConsulta==3){
            i=101;

        MostrarMascotasGraves();
        cout<<"\n\nEl numero de mascotas recuperadas es: "<<TotalMascotasRecuperadas()<<endl;
        }
    }
getch();
return 0;
}

void TransformarFechaHoy(char Cadena[]){
    string AnioCadena,MesCadena,DiaCadena,FechaString;
    FechaString+=Cadena;
    stringstream input_stringstream(FechaString);
    getline(input_stringstream,AnioCadena,'-');
    getline(input_stringstream,MesCadena,'-');
    getline(input_stringstream,DiaCadena,' ');

    FechaHoy[ContFechaHoy].Anio=stoi(AnioCadena);
    FechaHoy[ContFechaHoy].Mes=stoi(MesCadena);
    FechaHoy[ContFechaHoy].Dia=stoi(DiaCadena);
}
void TransformarFechaCita(char Texto[]){
    string AnioCadena,MesCadena,DiaCadena,FechaString;
    FechaString+=Texto;
    stringstream input_stringstream(FechaString);
    getline(input_stringstream,AnioCadena,'-');
    getline(input_stringstream,MesCadena,'-');
    getline(input_stringstream,DiaCadena,' ');

    Clientes[ContClientes].Mascotas[j].FechaCita.Anio=stoi(AnioCadena);
    Clientes[ContClientes].Mascotas[j].FechaCita.Mes=stoi(MesCadena);
    Clientes[ContClientes].Mascotas[j].FechaCita.Dia=stoi(DiaCadena);
}
void PedirDatosCliente(){
    fflush(stdin);
    cout<<"\n\t\tDatos del Cliente"<<endl;
    cout<<"Indique su nombre: ";cin.getline(Clientes[ContClientes].Nombre,30,'\n');
    cout<<"Indique su cedula: ";cin>>Clientes[ContClientes].Cedula;
    cout<<"Indique su edad: ";cin>>Clientes[ContClientes].Edad;
    for(j=0;j<ContClientes;j++){
        if(Clientes[ContClientes].Cedula==Clientes[j].Cedula){
            AuxContclientes=ContClientes;
            ContClientes=j;
        }
    }
    if(OpcConsulta==1){
        PedirDatosMascotas();
    if(AuxContclientes>0){
        ContClientes=AuxContclientes;
        AuxContclientes=0;
    }
    fflush(stdin);
    ContClientes++;
    }
    else if(OpcConsulta==2){
        if(ComprobarFechaConsulta()>0){
            cout<<"El estado de entrada de este perro fue: "<<Clientes[ContClientes].Mascotas[ComprobarFechaConsulta()-1].EstadoEntrada<<endl;
            cout<<"El estado de salida de este perro fue: "<<Clientes[ContClientes].Mascotas[ComprobarFechaConsulta()-1].EstadoSalida<<endl;
            fflush(stdin);
            cout<<"\nEl doctor desea hacer alguna observacion?,indique 'si' o 'no'"<<endl;cin.getline(Opc,10,'\n');
            strlwr(Opc);
            ComprobarOpc(Opc);
            if(strcmp(Opc,"si")==0){
                    fflush(stdin);
                cout<<"Escriba su observacion: ";cin.getline(Clientes[ContClientes].Mascotas[ComprobarFechaConsulta()-1].ObservacionDoctor,50,'\n');
            }
        }
        else if(ComprobarFechaConsulta()==0){
            cout<<"El cliente no posee una cita para el dia de hoy"<<endl;
        }
    }
    fflush(stdin);
}

void PedirDatosMascotas(){
    char FechaCitaCadena[15];
    for(j=Clientes[ContClientes].MascotasRegistradas;j<5;j++){
            fflush(stdin);
            strcpy(Opc,"no");
            if(Clientes[ContClientes].MascotasRegistradasPrevias>0){
                MostrarMascotasRegistradas();
                cout<<"\n Desea pedir una cita para alguna de las mascotas mostradas previamente?"<<endl;
                cout<<"Indique 'si' o 'no': ";cin.getline(Opc,10,'\n');
                strlwr(Opc);
                ComprobarOpc(Opc);
                if(strcmp(Opc,"si")==0){
                    cout<<"Indique el numero de la mascota a la que desea pedirle una cita: ";cin>>j;
                    j--;
                    while(j>Clientes[ContClientes].MascotasRegistradas){
                        cout<<"No tiene ninguna mascota registrada con ese numero, por favor indiquelo nuevamente: ";cin>>j;
                    }
                }
            }
            if(strcmp(Opc,"no")==0){
                fflush(stdin);
                cout<<"\n\t\tDatos de la Mascota #"<<j+1<<endl;
                cout<<"Indique la raza de su mascota: ";cin.getline(Clientes[ContClientes].Mascotas[j].Raza,15,'\n');
                cout<<"Indique el tamanio de su mascota: ";cin>>Clientes[ContClientes].Mascotas[j].Tamanio;
                cout<<"\nIndique la edad de su mascota."<<endl;
                cout<<"Anios: ";cin>>Clientes[ContClientes].Mascotas[j].Anios;
                cout<<"Meses: ";cin>>Clientes[ContClientes].Mascotas[j].Meses;
                fflush(stdin);
                cout<<"\nDesea hacer una cita para esta mascota?, indique 'si' o 'no': "<<endl;cin.getline(OpcCita,10,'\n');
                strlwr(OpcCita);
                ComprobarOpc(OpcCita);
                Clientes[ContClientes].MascotasRegistradas++;

            }
            if((strcmp(OpcCita,"si")==0)||(strcmp(Opc,"si")==0)){
                EstadoEntrada_Salida();
                fflush(stdin);
                cout<<"Indique la fecha para la cita, recuerde utilizar un '-' para separar los numeros: ";cin.getline(FechaCitaCadena,15,'\n');
                TransformarFechaCita(FechaCitaCadena);
                while(ComprobarEstructuraFecha(Clientes[ContClientes].Mascotas[j].FechaCita)<3){
                    cout<<"Recuerde que la fecha se debe entregar en el formato YYYY-MM-DD, por favor ingresela nuevamente";
                    cin.getline(FechaCitaCadena,15,'\n');
                    TransformarFechaCita(FechaCitaCadena);
                }
                while((ComprobarFechaMayor(Clientes[ContClientes].Mascotas[j].FechaCita,FechaCitaPrevia)==0)||(ComprobarFechaMayor(Clientes[ContClientes].Mascotas[j].FechaCita,FechaHoy[ContFechaHoy])==0)){
                    cout<<"La fecha para la cita debe ser mayor a la anterior y a la del dia de hoy, por favor vuelva a introducirla: ";
                    cin.getline(FechaCitaCadena,15,'\n');
                    TransformarFechaCita(FechaCitaCadena);
                    while(ComprobarEstructuraFecha(Clientes[ContClientes].Mascotas[j].FechaCita)<3){
                        cout<<"Recuerde que la fecha se debe entregar en el formato YYYY-MM-DD, por favor ingresela nuevamente: ";
                        cin.getline(FechaCitaCadena,15,'\n');
                        TransformarFechaCita(FechaCitaCadena);
                }
                }
                FechaCitaPrevia=Clientes[ContClientes].Mascotas[j].FechaCita;
                CitasPrevias[ContCitas]=Clientes[ContClientes].Mascotas[j].FechaCita;
                ContCitas++;
            }
            fflush(stdin);
            cout<<"Desea agregar otra mascota?"<<endl;
            cout<<"Indique 'si' o 'no': ";cin.getline(Opc,10,'\n');
            fflush(stdin);
            strlwr(Opc);
            ComprobarOpc(Opc);
            if(strcmp(Opc,"no")==0){
                j=10;
            }
            fflush(stdin);
    }
    Clientes[ContClientes].MascotasRegistradasPrevias=Clientes[ContClientes].MascotasRegistradas;

}
int ComprobarFechaConsulta(){
    int Respuesta=0;
    for(j=0;j<Clientes[ContClientes].MascotasRegistradas+1;j++){
        if((Clientes[ContClientes].Mascotas[j].FechaCita.Anio==FechaHoy[ContFechaHoy].Anio)&&(Clientes[ContClientes].Mascotas[j].FechaCita.Mes==FechaHoy[ContFechaHoy].Mes)&&
           (Clientes[ContClientes].Mascotas[j].FechaCita.Dia==FechaHoy[ContFechaHoy].Dia)){
            Respuesta=j+1;
        }
    }
    return Respuesta;
}
void EstadoEntrada_Salida(){
    int EstadoIncorrecto=0;
    fflush(stdin);

    do{
        if(EstadoIncorrecto>0){
            cout<<"El estado introducido no es valido,recuerde que los estado validos son:"<<endl<<"'grave','mal','regular'y'saludable'";
        }
        cout<<"Indique el estado de entrada de su mascota: ";
        cin.getline(Clientes[ContClientes].Mascotas[j].EstadoEntrada,10,'\n');
        strlwr(Clientes[ContClientes].Mascotas[j].EstadoEntrada);

        EstadoIncorrecto++;
    }while((strcmp(Clientes[ContClientes].Mascotas[j].EstadoEntrada,"grave")!=0)&&(strcmp(Clientes[ContClientes].Mascotas[j].EstadoEntrada,"mal")!=0)&&
    (strcmp(Clientes[ContClientes].Mascotas[j].EstadoEntrada,"regular")!=0)&&(strcmp(Clientes[ContClientes].Mascotas[j].EstadoEntrada,"saludable")!=0));

    EstadoIncorrecto=0;
    do{
        if(EstadoIncorrecto>0){
            cout<<"El estado introducido no es valido,recuerde que los estado validos son:"<<endl<<"'grave','mal','regular'y'saludable'";
        }
        cout<<"Indique el estado de salida de su mascota: ";
        cin.getline(Clientes[ContClientes].Mascotas[j].EstadoSalida,10,'\n');
        strlwr(Clientes[ContClientes].Mascotas[j].EstadoSalida);

        EstadoIncorrecto++;
    }while((strcmp(Clientes[ContClientes].Mascotas[j].EstadoSalida,"grave")!=0)&&(strcmp(Clientes[ContClientes].Mascotas[j].EstadoSalida,"mal")!=0)&&
    (strcmp(Clientes[ContClientes].Mascotas[j].EstadoSalida,"regular")!=0)&&(strcmp(Clientes[ContClientes].Mascotas[j].EstadoSalida,"saludable")!=0));
}
int ComprobarFechaMayor(Fecha FechaComprobar,Fecha FechaPrevia){
    int Resultado=0;
    if(FechaComprobar.Anio>FechaPrevia.Anio){
        Resultado=1;
    }
    else if(FechaComprobar.Mes>FechaPrevia.Mes){
        Resultado=1;
    }
    else if(FechaComprobar.Dia>FechaPrevia.Dia){
        Resultado=1;
    }
    return Resultado;
}
int ComprobarEstructuraFecha(Fecha Estructura){
    int Respuesta=1;
    if((Estructura.Mes>=1)&&(Estructura.Mes<=12)){
        Respuesta++;
    }
    if((Estructura.Dia>=1)&&(Estructura.Dia<=31)){
        Respuesta++;
    }
    return Respuesta;
}
void ComprobarOpc(char Opc[]){
    fflush(stdin);
    while((strcmp(Opc,"si")!=0)&&(strcmp(Opc,"no")!=0)){
        cout<<"La opcion ingresada no se encuentra disponible, por favor ingresela nuevamente: ";
        cin.getline(Opc,10,'\n');
        strlwr(Opc);
    }
}
void MostrarMascotasRegistradas(){
    for(l=0;l<Clientes[ContClientes].MascotasRegistradasPrevias;j++){
        fflush(stdin);
        cout<<"\n\t\tDatos de la Mascota #"<<l+1<<endl;
        cout<<"La raza del perro es: "<<Clientes[ContClientes].Mascotas[l].Raza<<endl;
        cout<<"El tamanio del perro es: "<<Clientes[ContClientes].Mascotas[l].Tamanio<<endl;
        fflush(stdin);
        cout<<"La edad del perro es: "<<endl;
        cout<<"Anios: "<<Clientes[ContClientes].Mascotas[l].Anios<<endl;
        cout<<"Meses: "<<Clientes[ContClientes].Mascotas[l].Meses<<endl;
    }
}
void MostrarMascotasGraves(){
    cout<<"\n\n\t\tMascotas Graves"<<endl<<"\n";
    for(j=0;j<ContClientes+1;j++){
        for(k=0;k<Clientes[j].MascotasRegistradas+1;k++){
            if(strcmp(Clientes[j].Mascotas[k].EstadoSalida,"grave")==0){
                fflush(stdin);
                cout<<"\n\tDatos"<<endl;
                cout<<"Nombre del cliente: "<<Clientes[j].Nombre<<endl;
                cout<<"Cedula del cliente: "<<Clientes[j].Cedula<<endl;
                cout<<"Raza del perro: "<<Clientes[j].Mascotas[k].Raza<<endl;
                cout<<"Tamanio del perro: "<<Clientes[j].Mascotas[k].Tamanio<<endl;
                cout<<"Anios del perro: "<<Clientes[j].Mascotas[k].Anios<<endl;
                cout<<"Meses del perro: "<<Clientes[j].Mascotas[k].Meses<<endl;
            }
        }
    }
}
int TotalMascotasRecuperadas(){
    int MascotasRecuperadas=0;
    for(j=0;j<ContClientes+1;j++){
        for(k=0;k<Clientes[j].MascotasRegistradas+1;k++){
                fflush(stdin);
            if((strcmp(Clientes[j].Mascotas[k].EstadoEntrada,"grave")==0)||(strcmp(Clientes[j].Mascotas[k].EstadoEntrada,"mal")==0)){
                if(strcmp(Clientes[j].Mascotas[k].EstadoSalida,"saludable")==0){
                    MascotasRecuperadas++;
                }
            }
        }
    }
    return MascotasRecuperadas;
}
