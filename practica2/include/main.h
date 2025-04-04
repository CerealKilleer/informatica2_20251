#ifndef __MAIN_H__
    #define __MAIN_H__
    #include <stdint.h>
    /*
    Ejercicio 1:
    El arreglo array tiene la dirección de memoria 0x7fffffffd440
    Cada elemento del array son 4 bytes (entero).
    El cuarto elemento está en 0x7fffffffd44c y su valor es 3
    Invierte el orden de los elementos del arreglo
    Ejercicio 3:
    short int 2 bytes
     - 0x0A12
     - 0x0A1A
     - 0x0A1A
     - 0x0A1C
     - 39
     - 3
     - 0x0A14
     - Error (?) pensando en los punteros: 0x0A14
*/
    void fun_a(int *, int *);
    void fun_b(int *, int tam);
    void ejercicio_1();
    void ejercicio_2();
    void problema_1();
    void problema_3();
    void problema_5();
    void problema_7();
    void problema_9();
    void problema_11();
    void problema_13();
    void problema_15();
    void problema_17();
    int contador_estrellas (int *, int, int);
    bool str_cmp(char *, char *);
    bool int_to_str(int, char *);
    bool reverse_str(char *, int);
    bool str_remove(char *, char *);
    void procesar_numeros(char *, uint32_t, uint32_t, uint32_t);
    bool gestionar_asiento(bool asientos[15][20], bool, uint32_t, uint32_t);
    bool str_copy(char *, char *);
    uint32_t str_to_num(char *str);
    uint32_t str_len(char *);
    uint32_t sumar_numeros(char *, uint32_t);
    uint32_t str_to_num(char *);
    bool leer_asiento(char *, unsigned short *, unsigned short *);
    bool to_upper(char *);
    void ver_asientos(bool asientos[15][20]);
    bool validar_interseccion(int *, int *);
    int max(int, int);
    int min(int, int);
    void obtener_interseccion(int *, int *, int *);
    int suma_divisores(uint32_t);
#endif