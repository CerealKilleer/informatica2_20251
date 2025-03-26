#include <iostream>
#include <fstream>
#include <lib_int_to_bin.hpp>

int read_file(char *file_name, char ** memory_block);
bool int_to_binary_matrix(char *, u_int8_t **, uint);
bool assign_matrix_bytes(u_int8_t ***, int);
bool delete_matrix(u_int8_t ***, int);

int main(void)
{
    char * memory_block;
    u_int8_t ** binary_matrix;
    int rows; 
    rows = read_file("data.txt", &memory_block);
    if (rows == -1) {
        std::cout << "No se pudo abrir el archivo" << std::endl;
        return EXIT_FAILURE;
    }
    
    if (!assign_matrix_bytes(&binary_matrix, rows)) {
        std::cout << "No se pudo asignar memoria dinámica" << std::endl;
        return EXIT_FAILURE;
    }
    int_to_binary_matrix(memory_block, binary_matrix, rows);
    delete[] memory_block;

    for (int i=0; i < rows; i++)
        for (int j=0; j < 8; j++)
            std::cout << static_cast<int>(binary_matrix[i][j]);
    std::cout<<std::endl;
    
    //Memory leeeeeaks moment
    delete_matrix(&binary_matrix, rows);
    return 0;
}

bool delete_matrix(u_int8_t *** binary_matrix, int rows)
{
    for (uint i=0; i<rows; i++) {
        delete[] (*binary_matrix)[i];
    }
    delete[] (*binary_matrix);
    return true;
}

bool assign_matrix_bytes(u_int8_t *** binary_matrix, int rows)
{
    /*** 
     * Asigna memoria dinamica para la matriz
     * ***/

    *binary_matrix = new u_int8_t *[rows];
    if (*binary_matrix == NULL)
        return false;

    for (uint i=0; i<rows; i++) {
        (*binary_matrix)[i] = new u_int8_t[BITS_ON_BYTES];
        if ((*binary_matrix)[i] == NULL) {
            return false;
        }
    }
    return true;
}

int read_file(char *file_name, char ** memory_block)
{
    /***
        Recibe el nombre del archivo y retorna un bloque de memoria 
        con todo el archivo leido junto con su tamaño
    ***/
    int rows;
    std::ifstream file (file_name, std::ios::in| std::ios::binary| std::ios::ate); // Peri por qui ate?

    if (!file.is_open()) {
        return -1;
    } else {
        rows = file.tellg(); // Pos para saber el tamaño del archivo fácilmente
        file.seekg(0, std::ios::beg); // Vea que luego vuelvo a poner el cursor al inicio, mor
        *memory_block = new char[rows];
        if (*memory_block == NULL) {
            file.close();
            return -1;
        }
        file.read(*memory_block, rows);
        file.close();
    }

    if (memory_block == NULL)
        return -1;

    return rows;
}

bool int_to_binary_matrix(char *memory_block, u_int8_t ** binary_matrix, uint size) 
{
    for (int i=0; i<size; i++) {
        if(!int_to_bin(memory_block[i], binary_matrix[i]))
            return false;
    }
    
    return true;
}