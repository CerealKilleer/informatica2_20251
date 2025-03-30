#include <iostream>
#include <fstream>
#include <lib_int_to_bin.hpp>
#include <lib_cypher_decipher.hpp>
#include <cstring>
#define FAILURE true
#define SUCCESS false

using method_ptr = bool(*)(uint8_t **, uint32_t, uint32_t, uint32_t);

int read_file(const char *, uint8_t **);
bool int_to_binary_matrix(uint8_t *, uint8_t **, uint);
bool assign_matrix_bytes(uint8_t ***, int32_t);
bool delete_matrix(uint8_t ***, int32_t);
void bin_to_char(uint8_t **, int32_t, uint8_t *);
bool app(method_ptr, char *, char*, uint8_t);
bool write_file(const char *, uint8_t *, int32_t);


int main(int argc, char* argv[])
{
    
    char * origen = "test.txt";
    char * destino = "test_c.txt";
    char * metodo = "c2";
    uint8_t semilla = 7;

    if (argc > 1) {
        std::cerr << "Uso: " << argv[0] << " [origen] [destino] [metodo] [semilla]" << std::endl;
        return -1;
    }

    
    bool result;

    if (strcmp(metodo, "c1") == 0) {
        result = app(cypher_1, origen, destino, semilla);
    } else if (strcmp(metodo, "d1") == 0) {
        result = app(decipher_1, origen, destino, semilla);
    } else if (strcmp(metodo, "c2") == 0) {
        result = app(cypher2, origen, destino, semilla);
    }  else {
        std::cerr << "Metodo no valido" << std::endl;
        result = FAILURE;
    }

    if (result == FAILURE) {
        std::cerr << "La aplicación falló satisfactoriamente" << std::endl;
        return -1;
    }

    return 0;
}

bool app(method_ptr metodo, char *origen, char*destino, uint8_t semilla)
{
    uint8_t * memory_block;
    uint8_t ** binary_matrix;
    int32_t rows; 

    rows = read_file(origen, &memory_block);
    if (rows == -1) {
        std::cout << "No se pudo abrir el archivo" << std::endl;
        return FAILURE;
    }
    
    if (!assign_matrix_bytes(&binary_matrix, rows)) {
        std::cout << "No se pudo asignar memoria dinámica" << std::endl;
        return FAILURE;
    }

    if (!int_to_binary_matrix(memory_block, binary_matrix, rows)) {
        std::cout << "Error al convertir a binario" << std::endl;
        delete[] memory_block;
        delete_matrix(&binary_matrix, rows);
        return FAILURE;
    }

    delete[] memory_block;

    if (!metodo(binary_matrix, semilla, rows, BITS_ON_BYTES)) {
        std::cout << "Error al aplicar la operación" << std::endl;
        delete_matrix(&binary_matrix, rows);
        return FAILURE;
    }

    memory_block = new uint8_t[rows];
    
    if (memory_block == NULL) {
        std::cout << "Error. Sin memoria" << std::endl;
        delete_matrix(&binary_matrix, rows);
        return FAILURE;
    }

    bin_to_char(binary_matrix, rows, memory_block);
    std::cout << "Matriz binaria:" << std::endl;

    for (int i=0; i < rows; i++)
        for (int j=0; j < BITS_ON_BYTES; j++) 
            std::cout << (int)binary_matrix[i][j];
        
    std::cout << std::endl;
    delete_matrix(&binary_matrix, rows);

    if (!write_file(destino, memory_block, rows)) {
        std::cout << "Error al escribir" << std::endl;
        delete[] memory_block;
        return FAILURE;
    }

    std::cout << "Archivo escrito" << std::endl;

    for (int i=0; i < rows; i++) {
        std::cout <<(memory_block[i]);
    }

    delete[] memory_block;
    return SUCCESS;

}

bool write_file(const char * file_name, uint8_t * memory_block, int32_t size)
{
    std::ofstream file (file_name, std::ios::out|std::ios::binary);
    if (!file.is_open())
        return false;
    
    file.write(reinterpret_cast<const char*>(memory_block), size);
    file.close();

    return true;
}

void bin_to_char(uint8_t **binary_matrix, int32_t rows, uint8_t *memory_block) 
{
    for (uint32_t i=0; i < rows; i++) {
        *(memory_block + i) = bin_to_int(*(binary_matrix + i));
    }
    return;
}

bool delete_matrix(uint8_t *** binary_matrix, int32_t rows)
{
    for (uint32_t i=0; i<rows; i++) {
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

    for (uint32_t i=0; i<rows; i++) {
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
        if (rows == -1) {
            file.close();
            return -1;
        }
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