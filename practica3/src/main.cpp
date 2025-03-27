#include <iostream>
#include <fstream>
#include <lib_int_to_bin.hpp>
#include <lib_cypher_decipher.hpp>

int read_file(const char *, uint8_t **);
bool int_to_binary_matrix(uint8_t *, uint8_t **, uint);
bool assign_matrix_bytes(uint8_t ***, int32_t);
bool delete_matrix(uint8_t ***, int32_t);
void bin_to_char(uint8_t **, int32_t, uint8_t *);
bool write_file(const char *, uint8_t *, int32_t);

int main(void)
{
    uint8_t * memory_block;
    uint8_t ** binary_matrix;
    int32_t rows; 

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

    cypher_1(binary_matrix, 200, rows, BITS_ON_BYTES);
    memory_block = new uint8_t[rows];
    
    if (memory_block == NULL) {
        std::cout << "Error. Sin memoria" << std::endl;
        //Memory leeeeeaks moment
        delete_matrix(&binary_matrix, rows);
        return EXIT_FAILURE;
    }

    bin_to_char(binary_matrix, rows, memory_block);
    //Memory leeeeeaks moment
    delete_matrix(&binary_matrix, rows);

    if (!write_file("data.bin", memory_block, rows)) {
        std::cout << "Error al escribir" << std::endl;
        delete[] memory_block;
        return EXIT_FAILURE;
    }

    std::cout << "Archivo escrito" << std::endl;

    for (int i=0; i < rows; i++) {
        std::cout << memory_block[i];
    }

    delete[] memory_block;
    return 0;
}

bool write_file(const char * file_name, uint8_t * memory_block, int32_t size)
{
    std::ofstream file (file_name, std::ios::out|std::ios::binary);
    if (!file.is_open()) {
        return false;
    }
    else {
        file.write((char *)memory_block, size);
        file.close();
    }
    return true;
}

void bin_to_char(uint8_t **binary_matrix, int32_t rows, uint8_t *memory_block) 
{
    for (int i=0; i < rows; i++) {
        *(memory_block + i) = bin_to_int(*(binary_matrix + i));
    }
    return;
}

bool delete_matrix(uint8_t *** binary_matrix, int32_t rows)
{
    for (uint i=0; i<rows; i++) {
        delete[] (*binary_matrix)[i];
    }
    delete[] (*binary_matrix);
    return true;
}

bool assign_matrix_bytes(uint8_t *** binary_matrix, int rows)
{
    /*** 
     * Asigna memoria dinamica para la matriz
     * ***/

    *binary_matrix = new uint8_t *[rows];
    if (*binary_matrix == NULL)
        return false;

    for (uint i=0; i<rows; i++) {
        (*binary_matrix)[i] = new uint8_t[BITS_ON_BYTES];
        if ((*binary_matrix)[i] == NULL) {
            return false;
        }
    }
    return true;
}

int32_t read_file(const char *file_name, uint8_t ** memory_block)
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
        *memory_block = new uint8_t[rows];
        if (*memory_block == NULL) {
            file.close();
            return -1;
        }
        file.read((char *)*memory_block, rows);
        file.close();
    }

    if (memory_block == NULL)
        return -1;

    return rows;
}

bool int_to_binary_matrix(uint8_t *memory_block, uint8_t ** binary_matrix, uint size) 
{
    for (int i=0; i<size; i++) {
        if(!int_to_bin(memory_block[i], binary_matrix[i]))
            return false;
    }
    
    return true;
}