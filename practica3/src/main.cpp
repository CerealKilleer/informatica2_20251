#include <iostream>
#include <fstream>
#include <lib_int_to_bin.hpp>

bool process_file(char *);
bool int_to_binary_matrix(char *, u_int8_t **, uint);

int main(void)
{
    process_file("data.txt");
    return 0;
}

bool process_file(char *file_name)
{
    uint rows;
    char * memory_block; 

    std::ifstream file (file_name, std::ios::in| std::ios::binary| std::ios::ate); // Peri por qui ate?

    if (!file.is_open()) {
        return false;
    } else {
        rows = file.tellg(); // Pos para saber el tamaño del archivo fácilmente
        memory_block = new char[rows];
        file.seekg(0, std::ios::beg); // Vea que luego vuelvo a poner el cursor al inicio, mor
        file.read(memory_block, rows);
        file.close();
    }
    
    u_int8_t ** binary_matrix = new u_int8_t *[rows];
    for (uint i=0; i<rows; i++)
        binary_matrix[i] = new u_int8_t[BITS_ON_BYTES];

    int_to_binary_matrix(memory_block, binary_matrix, rows);
    delete[] memory_block;

    //Memory leeeeeaks moment
    for (uint i=0; i<rows; i++) {
        delete[] binary_matrix[i];
    }
    delete[] binary_matrix;
    return true;
}

bool int_to_binary_matrix(char *memory_block, u_int8_t ** binary_matrix, uint size) 
{
    for (int i=0; i<size; i++) {
        if(!int_to_bin(memory_block[i], binary_matrix[i]))
            return false;
    }
    
    return true;
}