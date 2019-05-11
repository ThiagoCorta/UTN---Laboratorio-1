#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include "utn.h"
#include "auto.h"

void initAutos(eAuto* list, int len)
{
    for(int i = 0 ; i < len ; i++)
    {
        list[i].isEmpty=0;
    }
}

int findEmptyAuto(eAuto* list, int len)
{
    int indice = -1;

    for(int i = 0 ; i < len ; i++)
    {
        if(list[i].isEmpty==0)
        {
            indice=i;
            break;
        }
    }

    return indice;
}

int findAutoById(eAuto* list, int len, int id)
{
    int esta = -1;

    for(int i = 0 ; i < len ; i++)
    {
        if(list[i].idAuto==id)
        {
            esta=i;
        }
    }

    return esta;

}

int getIdAuto()
{
    static int id = 100;
    id++;
    return id;

}

int addAuto(eAuto* list, int len, eMarca* marcas, int lenM, eColor* colores, int lenC)
{
    int indice;
    int todoOk=-1;
    int auxInt;


    indice=findEmptyAuto(list,len);

    if(indice!=-1)
    {
        list[indice].idAuto = getIdAuto();

        utn_getEntero(&auxInt,20,"Ingresar patente del auto (3) numeros  : \n", "Error ingresar patente Valida \n",0,999);
        list[indice].patente=auxInt;

        mostrarModelos(marcas,lenM);
        utn_getEntero(&auxInt,20,"Ingresar Marca : \n", "Error ingresar marca valida \n",1000,1004);

        list[indice].idMarca=auxInt;

        mostrarColores(colores,lenC);

        utn_getEntero(&auxInt,20,"Ingresar color del auto : \n", "Error ingresar color Valida \n",5000,5004);

        list[indice].idColor=auxInt;

        utn_getEntero(&auxInt,20,"Ingresar anio de fabricacion del auto : \n", "Error ingresar modelo valido \n",1900,2019);

        list[indice].modeloAnio=auxInt;


        list[indice].isEmpty=1;

        printf("\nAuto ingresado con Exito!!.\n");
        todoOk=0;
    }
    else
    {
        printf("\nNo hay mas espacio para nuevos Autos.\n");
    }

    return todoOk;
}

char preguntarSiEstaSeguro(char* msg, char* msgerror)
{
    char confirma;

    printf("%s", msg);
    fflush(stdin);
    confirma = tolower(getche());

    while(confirma!='s' && confirma!='n')
    {
        printf("%s", msgerror);
        fflush(stdin);
        confirma = tolower(getche());
    }

    return confirma;
}

int removeAuto(eAuto* list, int len, int id)
{
    int todoOk = -1;
    int esta;

    esta = findAutoById(list,len,id);

    if(esta!=-1)
    {
        if(preguntarSiEstaSeguro("Desea dar de baja el auto s/n : ", "Error ingresar s/n : ")=='s')
        {
            list[esta].isEmpty=0;
            todoOk=1;
            printf("Auto dado de baja.\n\n");
        }
        else
        {
            printf("\nEl Auto NO fude dado de baja.\n");
        }

    }
    else
    {
        printf("\nEl Auto no se encuentra en nuestros registos.\n");
    }

    return todoOk;

}

void printAuto(eAuto list, eColor* color,int lenc,eMarca* marcas, int lenM)
{
    char nombreColor[20];
    char nombreMarca[20];
    int consigioColor;
    int consigioMarca;

    consigioColor = obtenerColores(color,lenc,list.idColor,nombreColor);
    consigioMarca = obtenerMarcas(marcas,lenM,list.idMarca,nombreMarca);

    if(!consigioColor)
    {
        strcpy(nombreColor, "Sin definir");
    }

    if(!consigioMarca)
    {
        strcpy(nombreMarca, "Sin definir");
    }

    printf("%5d %12s %12s %10d %10d \n", list.idAuto, nombreMarca,nombreColor,list.modeloAnio,list.patente);
}


void printAutos(eAuto* list, int len, eMarca* marca, int lenM, eColor* color, int lenC)
{
    int cont=0;

    system("cls");
    printf("\n");
    printf("%5s %12s %12s %10s %10s  \n", "IDAuto", "Marca", "Color", "Modelo", "Patente");

    for(int i = 0 ; i < len ; i++)
    {
        if(list[i].isEmpty==1)
        {
            printAuto(list[i],color,lenC,marca,lenM);
            cont++;
        }

    }
    if(cont==0)
    {
        printf("No hay autos que mostrar.\n");

    }
}

int menuModificar()
{
    int opcion;

    system("cls");
    fflush(stdin);
    printf("1- Modificar color.\n2- Modificar Modelo.\n3-Volver al menu principal\n\n Ingresar opcion :  ");
    scanf("%d", &opcion);

    return opcion;

}


int modifyAuto(eAuto* list, int len, eColor* color, int lenc, eMarca* marcas, int lenM)
{

    int id;
    int esta;
    int auxInt;
    char seguir='s';
    int todoOk=-1;


    printAutos(list,len,marcas,lenM,color,lenc);

    printf("\n\nIngrese el ID del auto que desea modificar:\n ");
    scanf("%d", &id);

    esta = findAutoById(list, len, id);

    if( esta == -1)
    {

        printf("\nEl Auto con id %d no esta registrado en el sistema\n", id);
    }
    else
    {
        do
        {
            switch(menuModificar())
        {
        case 1 :
            if(preguntarSiEstaSeguro("Desea cambiar el color del auto ? s/n : ", "Error ingresar s/n : ")=='s')
            {
                mostrarColores(color,lenc);
                utn_getEntero(&auxInt,20,"Ingresar color del auto : \n", "Error ingresar color Valida \n",5000,5004);

                list[esta].idColor=auxInt;
                printf("Auto modificado con exito!..\n\n");
                todoOk=0;
                system("pause");
            }

            break;
        case 2 :
            if(preguntarSiEstaSeguro("Desea cambiar el modelo del auto s/n : ", "Error ingresar s/n : ")=='s')
            {
                utn_getEntero(&auxInt,20,"Ingresar anio de fabricacion del auto : \n", "Error ingresar modelo valido \n",1900,2019);
                list[esta].modeloAnio=auxInt;
                printf("Auto modificado con exito!..\n\n");
                todoOk=0;
                system("pause");
            }
            break;
        case 3:
            seguir='n';
            break;


        default:
            printf("Ingresar opcion valida\n");
            system("pause");
            break;


        }

        }while(seguir=='s');
    }

    return todoOk;
}

int menuAbm()
{
    int opcion;
    system("cls");
    fflush(stdin);

    printf("|**************MENU ABM TP2**************|\n");
    printf("\n 1- Alta Auto:\n");
    printf(" 2- Baja Auto:\n");
    printf(" 3- Modificar Auto:\n");
    printf(" 4- Mostrar Autos: \n");
    printf(" 5- Listar marcas: \n");
    printf(" 6- listar colores: \n");
    printf(" 7- listar servicios: \n");
    printf(" 8- Alta trabajo: \n");
    printf(" 9- listar trabajos: \n");
    printf(" 10- Salir:");
    printf("\n\n Ingresar opcion : ");

    scanf("%d", &opcion);

return opcion;
}

void mostrarModelos( eMarca* marca, int len){

    printf("\nID    Marcas\n");

    for(int i=0; i < len; i++){
        printf("%d:      %10s\n", marca[i].idMarca, marca[i].descripcion);
    }
}

void mostrarServicios(eServicio* servicio, int lenS){

    printf("\nID           Servicios       Precios\n");

    for(int i=0; i < lenS; i++){
        printf("%d:      %10s %10d$\n", servicio[i].idServicio, servicio[i].descripcion, servicio[i].precioServicio);
    }
}

void mostrarColores( eColor* color, int lenC){

    printf("\nID    Colores\n");

    for(int i=0; i < lenC; i++){
        printf("%d:      %10s\n", color[i].idColor, color[i].nombreColor);
    }
}


int obtenerColores(eColor* colores, int lenC, int idColor, char* desc)
{
    int todoOk=-1;
    for(int i= 0 ; i<lenC;i++)
    {
        if(idColor == colores[i].idColor)
        {
            strcpy(desc,colores[i].nombreColor);
            todoOk=1;
            break;
        }
    }
    return todoOk;
}

int obtenerMarcas(eMarca* marcas, int lenM, int idMarca, char* desc)
{
    int todoOk=-1;
    for(int i= 0 ; i<lenM;i++)
    {
        if(idMarca == marcas[i].idMarca)
        {
            strcpy(desc,marcas[i].descripcion);
            todoOk=1;
            break;
        }
    }
    return todoOk;
}

int findServicioById(eServicio* servicio, int lenS, int idServicio)
{
    int esta = -1;

    for(int i = 0 ; i < lenS ; i++)
    {
       if(servicio[i].idServicio==idServicio)
       {
           esta=i;
       }
    }

    return esta;
}

void sortAutos(eAuto* list, int len)
{

     eAuto autos;

    for(int i = 0 ; i<len-1; i++)
    {
        for(int j=i+1; j<len; j++)
        {
            if(list[i].idMarca<list[j].idMarca)
                {
                    autos=list[i];
                    list[i]=list[j];
                    list[j]=autos;
                }
               else
                {
                    if(list[i].idMarca==list[j].idMarca && list[i].patente > list[i].patente)
                    {
                    autos=list[i];
                    list[i]=list[j];
                    list[j]=autos;
                    }
                }
            }
    }

}

int findArrayAuto(eAuto* autos, int lenA)
{
    int esta =-1;

    for(int i = 0 ; i< lenA ; i++)
    {
        if(autos[i].isEmpty==1)
        {
            esta=1;
            break;
        }
    }
    return esta;
}

