/*Trabajo Práctico N° 3: Recursión
1. Calcular el factorial de un número en forma recursiva.
2. Calcular la potencia de un número en forma recursiva.
3. Recorrer un arreglo y mostrar sus elementos en forma recursiva.
4. Recorrer un arreglo comenzando desde la posición 0 y mostrar sus elementos en
forma invertida (recursivo).
5. Determinar en forma recursiva si un arreglo es capicúa.
6. Sumar en forma recursiva los elementos de un arreglo de enteros.
7. Buscar el menor elemento de un arreglo en forma recursiva.
8. Buscar el menor elemento de un archivo números de enteros.
9. Invertir los elementos de un archivo de números enteros.
10.Recorrer un archivo y mostrar sus elementos en forma invertida.
11. Ingresar valores a una variable (por teclado) y mostrarlo en el orden inverso
(hasta ingresar un ‘*’). NO usar arreglos.
12.Determinar si un arreglo contiene un determinado elemento.*/

#include <stdlib.h>
#include <stdio.h>

//-------FUNCIONES AUXILIARES PAR MANEJO DE ARCHIVOS-------
int menor(int a, int b){
  int men=a;
  if(b<a){
    men=b;
  }
  return men;
}

int cargarArchivo(char direccion[]){
  FILE * archivo;
  archivo=fopen(direccion,"a+b");
  int i=0;
  char control = 's';

  if(archivo){
    while(control=='s'){
      int num;
      printf("Ingrese un numero: ");
      fflush(stdin);
      scanf("%i",&num);
      fwrite(&num,sizeof(int),1,archivo);
      i++;
      printf("\nDesea continuar? S/N " );
      fflush(stdin);
      scanf(" %c",&control);
    }
  }
  fclose(archivo);
  return i;
}

void mostrarArchivo(char direccion[]){
  int num;
  FILE *archivo;
  archivo=fopen(direccion,"rb");
  if(archivo){
    fread(&num,sizeof(int),1,archivo);
    while(!feof(archivo)){
      printf("|%i|",num );
      fread(&num,sizeof(int),1,archivo);
    }
  }
  fclose(archivo);
}

int contarArchivo(char direccion[]){
  int rta;
  FILE * archivo;
  archivo=fopen(direccion,"rb");
  if(archivo){
    fseek(archivo,0*sizeof(int),SEEK_END);
    rta=ftell(archivo)/sizeof(int);
  }
  fclose(archivo);
  return rta;
}

//-------RESOLUCION DE EJERCICIOS-------
//1. Calcular el factorial de un número en forma recursiva.
int factorial(int num){
  int rta;
  if(num==0){//condicion de corte
    rta=1;//solucion trivial
  }else{
    rta=num*factorial(num-1);
  }
  return rta;
}

//2. Calcular la potencia de un número en forma recursiva.
int potencia(int num, int pot){
  int rta;
  if(pot==0){
    rta=1;
  }else{
    rta=num*potencia(num,pot-1);
  }
  return rta;
}

// 3. Recorrer un arreglo y mostrar sus elementos en forma recursiva.
void mostrarArreglo(int a[],int validos,int i){
  if(i==validos-1){
    printf("|%i|",a[i] );
  }else{
    printf("|%i|",a[i] );
    mostrarArreglo(a,validos,i+1);
  }
}

//4. Recorrer un arreglo comenzando desde la posición 0 y mostrar sus elementos en
//forma invertida (recursivo).
void mostrarInvertido(int a[],int validos, int i){
  if(i==validos-1){
    printf("|%i|",a[validos-1] );
  }else{
    mostrarInvertido(a,validos,i+1);
    printf("|%i|",a[i] );
  }
}

//5. Determinar en forma recursiva si un arreglo es capicúa.
int capicua(int a[],int j, int i){ //arreglo,validos-1,0
  int flag=1;
  if(i<j&&flag==1){
    if(a[i]==a[j]){
      flag=capicua(a,j-1,i+1);
    }else{
      flag=0;
    }
  }
  return flag;
}

//6. Sumar en forma recursiva los elementos de un arreglo de enteros.
int suma(int a[],int validos, int i){
  int rta;
  if(i<validos-1){
    rta=a[i]+suma(a,validos,i+1);
  }else{
    rta=a[i];
  }
  return rta;
}

//7. Buscar el menor elemento de un arreglo en forma recursiva.
int buscarMenor(int a[], int validos, int i){
  int rta;
  if(i<validos-1){
    rta=menor(a[i],buscarMenor(a,validos,i+1));
  }else{
    rta=a[i];
  }
  return rta;
}

//8. Buscar el menor elemento de un archivo números de enteros.
int buscarMenorArchivo(FILE * archivo){
  int menor;
  int valor;
  if(fread(&menor,sizeof(int),1,archivo)==0){
    // Llegado al fin del archivo condicion de corte.
    //Con el fread en la sentencia del if mueve el cursor en cada iteracion.
    fseek(archivo,-1*sizeof(int),SEEK_END);
    fread(&menor,sizeof(int),1,archivo);
  }else{
    valor=buscarMenorArchivo(archivo);
    if(valor<menor){
      menor=valor;
    }
  }
  return menor;
}

int mostrarMenorArchivo(char direccion[]){
  int rta;
  FILE * archivo;
  archivo=fopen(direccion,"rb");
  if(archivo){
    rta=buscarMenorArchivo(archivo);
    printf("El menor numero en el archivo es: %i\n",rta);
  }
  fclose(archivo);
}

//9. Invertir los elementos de un archivo de números enteros.
void invertirArchivo(FILE * archivo,int i, int j){
  int ppio;
  int fin;
  if(i<j){
    fseek(archivo,i*sizeof(int),SEEK_SET);
    fread(&ppio,sizeof(int),1,archivo);

    fseek(archivo,j*sizeof(int),SEEK_SET);
    fread(&fin,sizeof(int),1,archivo);

    fseek(archivo,i*sizeof(int),SEEK_SET);
    fwrite(&fin,sizeof(int),1,archivo);

    fseek(archivo,j*sizeof(int),SEEK_SET);
    fwrite(&ppio,sizeof(int),1,archivo);

    invertirArchivo(archivo,i+1,j-1);
  }
}

void iniciarInvertirArchivo(char direccion[]){
  int cant=contarArchivo(direccion);
  FILE * archivo;

  archivo=fopen(direccion,"r+b");
  if(archivo){
    invertirArchivo(archivo,0,cant-1);
  }
  fclose(archivo);
}

//10.Recorrer un archivo y mostrar sus elementos en forma invertida.
void mostrarArchivoInvertido(FILE * archivo){
  int num;
  if(fread(&num,sizeof(int),1,archivo)>0){
    mostrarArchivoInvertido(archivo);
    printf("|%i|",num );
  }
}

void iniciarMostrarArchivoInvertido(char direccion[]){
  FILE * archivo;
  archivo=fopen(direccion,"rb");
  if(archivo){
    mostrarArchivoInvertido(archivo);
  }
  fclose(archivo);
}

//11. Ingresar valores a una variable (por teclado) y mostrarlo en el orden inverso
void mostrarCharInvertido(){
  char caracter;
  printf("Ingrese un caracter que no sea un *: ");
  fflush(stdin);
  scanf(" %c",&caracter);
  if(caracter!='*'){
    mostrarCharInvertido();
    printf("%c",caracter);
  }else{
    printf("\nTe dije que no ingreses *!! Mira lo que hiciste!!!\n\n");
  }
}

int main(int argc, char const *argv[]) {
  int arreglo[]={5,1,3,4,5};
  int validos=5;
  char direccion[20]={"num.dat"};

  system("clear");
  //printf("La potencia de %i a la %i es %i\n",5,3,potencia(5,3) );
  //mostrarArreglo(arreglo,validos,0);
  //mostrarInvertido(arreglo,validos,0);
  //printf("El arreglo es capicua: %i\n",capicua(arreglo,validos-1,0) );
  //printf("La suma de los elementos del arreglo es: %i\n",suma(arreglo,validos,0) );
  //printf("El menor elemento del arreglo es: %i\n",buscarMenor(arreglo,validos,0) );
  //validos=cargarArchivo(direccion);
  //printf("Cantidad de datos en archivo: %i",contarArchivo(direccion));
  //mostrarMenorArchivo(direccion);
  //printf("Archivo original\n");
  //mostrarArchivo(direccion);
  //iniciarInvertirArchivo(direccion);
  //printf("\nArchivo invertido\n");
  //mostrarArchivo(direccion);
  //iniciarMostrarArchivoInvertido(direccion);
  mostrarCharInvertido();
  printf("\n\n\n");
  return 0;
}
