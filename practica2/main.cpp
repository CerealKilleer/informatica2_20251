#include <iostream>
using namespace std;
#include "main.h"


int main() {
    problema_17(); 
    return 0;
}


void problema_17() {
    uint numero, divisores_b, divisores_3, suma_total;
    suma_total = 0;
    cout << "Ingrese el  número: " << endl;
    cin >> numero;
    
    for (int a=1; a < numero; a++) {
        uint b = suma_divisores(a);
        if (a == b || b >= numero)
            continue;
        divisores_b = suma_divisores(b);
        if (a == divisores_b)
            suma_total += a;
    }
    cout << "El resultado de la suma es: " << suma_total << endl;
}

int suma_divisores(uint numero) {
    int suma = 0;
    for (int i = 1; i <= numero/2; i++)
        if (!(numero % i))
            suma += i;
    return suma;
}

void problema_15() {
    int rect_1[] = {13,6,5,21};
    int rect_2[] = {15,3,7,8};
    int rect_3[] = {0,0,0,0};
    if (validar_interseccion(rect_1, rect_2)) {
        cout << "Hay intersección" << endl;
        obtener_interseccion(rect_1, rect_2, rect_3);
        cout << "{" << rect_3[0] << "," << rect_3[1] << "," << rect_3[2] << "," << rect_3[3] << "}" << endl;
    }
    else {
        cout << "No hay intersección" << endl;
    }
}

bool validar_interseccion(int *rect1, int *rect2) {
    int x1, x2, x3, x4, y1, y2, y3, y4;
    x1 = rect1[0];
    y1 = rect1[1];
    x2 = rect1[0] + rect1[2];
    y2 = rect1[1] + rect1[3];
    x3 = rect2[0];
    y3 = rect2[1];
    x4 = rect2[0] + rect2[2];
    y4 = rect2[1] + rect2[3];
    
    return !((x1 > x4) || (x3 > x2) || (y1 > y4) || (y3 > y2));
}

void obtener_interseccion(int *rect1, int *rect2, int *rect3) {
    rect3[0] = max(rect1[0], rect2[0]);
    rect3[1] = max(rect1[1], rect2[1]);
    rect3[2] = min(rect1[0] + rect1[2], rect2[0] + rect2[2]) - rect3[0];
    rect3[3] = min(rect1[1] + rect1[3], rect2[1] + rect2[3]) - rect3[1];
}

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a > b ? b : a;
}

void problema_13() {
    int valores[6][6] = {
        {0,  0,  0,  0,  0,  0},
        {0, 10, 12, 15, 10,  0},
        {0, 14, 20, 22, 16,  0},
        {0, 11, 18, 21, 13,  0},
        {0,  0,  0,  0,  0,  0},
        {0,  0,  0,  0,  0,  0}
    };
    
    cout << "Hay " << contador_estrellas(*valores,6,6) << " estrellas\n";
}


int contador_estrellas (int *matrix, int filas, int columnas) {
    int cnt_estrellas = 0;

    for (int i = 1; i < filas-1; i++) {
        for (int j = 1; j < columnas-1; j++) {
            int suma = 0;
            int index = i*columnas + j;
            suma += matrix[index];
            suma += matrix[index - 1];
            suma += matrix[index + 1];
            suma += matrix[index - columnas];
            suma += matrix[index + columnas];
            if (suma / 5.0 > 6)
                cnt_estrellas++;
        }  
    }
    
    return cnt_estrellas;
}

void problema_11() {
    bool asientos[15][20];
    char asiento[5];
    unsigned short opc, fila, silla;

    for (int i=0; i<15;i++)
        for (int j=0; j<20;j++)
            asientos[i][j] = true;

    do {
        cout << "----- Sistema de reservas -----" << endl;
        cout << "1. Reservar\n2. Cancelar reserva\n3. Ver asientos\n0. Salir" << endl;
        cin >> opc;
        switch (opc) {
        case 1:
            if (!(leer_asiento(asiento, &fila, &silla))) {
                cout << "El asiento ingresado no es valido" << endl;
                continue;
            }
            if (gestionar_asiento(asientos, true, fila, silla))
                cout << asiento << " reservado"<< endl;
            else
                cout << asiento << " ocupado"<< endl;
            break;
        case 2:
            if (!(leer_asiento(asiento, &fila, &silla))) {
                cout << "El asiento ingresado no es valido" << endl;
                continue;
            }
            if (gestionar_asiento(asientos, false, fila, silla))
                cout << asiento << " liberado"<< endl;
            else
                cout << asiento << " no cupado"<< endl;
            break;
        case 3:
            ver_asientos(asientos);
            break;
        case 0:
            cout << "Saliendo..." << endl;
        default:
            cout << "Opción no válida" << endl; 
            break;
        }
    }while(opc != 0);
}

void ver_asientos(bool asientos[15][20]) {
    for (int i=0; i<15; i++) {
        for (int j=0; j<20; j++) {
            if (asientos[i][j])
                cout << "| - ";
            else
                cout << "| + ";
        }
        cout << "|"<< endl;
    }
}
bool leer_asiento(char *asiento, unsigned short *fila, unsigned short *silla) {
    cout << "Escriba la asiento en formato: fila-silla" << endl;
    cin >> asiento;
    to_upper(asiento);
    *fila = *asiento - 'A';
    *silla = str_to_num(asiento + 2) - 1;
    
    if (*fila < 0 || *fila > 14)
        return false;
    if (*silla < 0 || *silla > 19)
        return false;
    return true;
}

bool gestionar_asiento(bool asientos[15][20], bool reservar, uint fila, uint silla) {
    if (asientos[fila][silla] && reservar) {
        asientos[fila][silla] = !reservar;
        return true;
    } else if (!asientos[fila][silla] && reservar) {
        return false;
    } else if (asientos[fila][silla] && !reservar) {
        return false;
    } else {
        asientos[fila][silla] = !reservar;
        return true;
    }
}

bool to_upper(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] = str[i] - ('a' - 'A');
        i++;
    }
    return true;
}

void problema_9() {
    uint n, len, ceros, cant_numeros, i;
    bool agregar_ceros = false;
    char numeros[20];
    cout << "Escriba los números" << endl;
    cin >> numeros;
    cout << "¿Cuántas cifras? " << endl;
    cin >> n;
    len = str_len(numeros);

    if (n <= 0) {
        cout << "Más de 1 cifra " << endl;
        return;
    }

    if (len % n)
        agregar_ceros = true;
    
    if (agregar_ceros)
        ceros = n - (len % n);
    else
        ceros = 0;

    if (ceros > 0)
        cant_numeros = len/n + 1;
    else
        cant_numeros = len/n;

    procesar_numeros(numeros, len, ceros, n);
}

void procesar_numeros(char *numeros, uint len, uint ceros, uint n) {
    char nuevos_numeros[len+ceros+1];
    uint suma, i;
    for (int i=0; i<ceros;i++)
        nuevos_numeros[i] = '0';

    str_copy(numeros, nuevos_numeros + ceros);
    suma = sumar_numeros(nuevos_numeros, n);
    
    i=0;
    while (i < len+ceros) {
        if (!(i % n) && (i != 0))
            cout << '+';
        cout << nuevos_numeros[i++];
    }
    cout << "=" << suma << endl;
}

uint sumar_numeros(char *nuevos_numeros, uint n) {
    char numero[n+1];
    uint i = 0;
    uint suma = 0;
    while(*nuevos_numeros != '\0') {
        numero[i++] = *nuevos_numeros++;
        if (i == n) {
            numero[i] = '\0';
            i = 0;
            suma += str_to_num(numero);
        }
    }
    return suma;
}

uint str_to_num(char *str) {
    uint power = 10;
    uint number = 0;
    for (;*str != '\0';) {
        number = number*power + (*str - '0');
        str++;
    }
    
    return number;
}
bool str_copy(char *str_a, char *str_b) {

    while (*str_a != '\0')
        *str_b++ = *str_a++;

    *str_b = '\0';
    return true;
}

void problema_7() {
    char linea[20];
    char copia[20];
    cout << "Escriba una cadena" << endl;
    cin >> linea;
    if (str_remove(linea, copia))
        cout << "Original: " << linea << ". Sin repetidos: " << copia << endl;
}

void problema_5() {
    int numero = 0;
    char numero_str[10];
    cout << "Ingrese un número: " << endl;
    cin >> numero;
    if (int_to_str(numero, numero_str))
        cout << "To string: " << numero_str << endl;
    
}

void problema_3() {
    char input1[30];
    char input2[30];
    cout << "Ingrese la primera cadena: ";
    cin >> input1;
    cout << "Ingrese la segunda cadena: ";
    cin >> input2;
    if (str_cmp(input1, input2))
        cout << "Las cadenas son iguales" << endl;
    else
        cout << "Las cadenas son diferentes" << endl;
}


void problema_1() {
    int cambio = 0;
    int monedas[] = {50000,20000,10000,5000,2000,1000,500,200,100,50};

    do {
        cout << "¿Cuánto es el cambio?" << endl;
        cin >> cambio;
    } while (cambio < 0);
    
    for (int i = 0; i < sizeof(monedas)/sizeof(monedas[0]); i++) {
        cout << monedas[i] << ": " << cambio / monedas[i] << endl;
        cambio = cambio % monedas[i];
    }

    cout << "Faltante: " << cambio << endl;
}

void ejercicio_2() {
    unsigned short b[4][2] = {{77,50},{5,2},{28,39},{99,3}};
    cout << b << endl;
    cout << b + 2 << endl;
    cout << *(b + 2) << endl;
    cout << *(b + 2) + 1 << endl;
    cout << *(*(b + 2) + 1) << endl;
    cout << b[3][1] << endl;
}

void ejercicio_1() {
    int array[10] = {0,1,2,3,4,5,6,7,8,9};
    fun_b(array, 10);
}

void fun_a(int *px, int *py) {
    int tmp = *px;
    *px = *py;
    *py = tmp;
}

void fun_b(int *a, int tam) {
    int f, l;
    int *b = a;
    for (f = 0, l = tam - 1; f < l; f++, l--)
        fun_a(&b[f], &b[l]);
}

uint str_len(char *str) {
    uint len = 0;
    while (*str != '\0') {
        len++;
        *str++;
    }
        
    return len;
}

bool str_cmp(char *str1, char *str2) {
    while (*str1 && *str2) {
        if (*str1 != *str2)
            return false;
        str1++;
        str2++;
    }
    return true;
}

bool int_to_str(int numero, char *num_to_str) {
    int i = 0;
    bool negative_flag = false;

    if (numero < 0) {
        negative_flag = true;
        numero *= -1;
    }

    while (numero != 0) {
        *(num_to_str + i) = (numero % 10) + 48; //Base ASCII '0' = 48
        numero /= 10;
        i++; 
    }

    if (negative_flag) {
        *(num_to_str + i) = '-';
        i++;
    }

    *(num_to_str + i) = '\0';
    return reverse_str(num_to_str, i);
}

bool reverse_str(char *str, int length) {
    char aux;

    for (int i=0, j=length-1; i < j; i++, j--) {
        aux = str[i];
        str[i] = str[j];
        str[j] = aux;
    }
    str[length] = '\0';
    return true;
}

bool str_remove(char *linea, char *copia) {
    uint len_linea = 0;
    uint len_copia = 0;
    bool is_new = true;
    char c;
    len_linea = str_len(linea);

    for (int i=0; i<len_linea; i++) {
        c = linea[i];
        for (int j=0; j<len_copia; j++) {
            if (copia[j] == c)
                is_new = false;
        }
        if(is_new) 
            copia[len_copia++] = c;
        else
            is_new = true; 
    }
    copia[len_copia] = '\0';
    
    return true;
}