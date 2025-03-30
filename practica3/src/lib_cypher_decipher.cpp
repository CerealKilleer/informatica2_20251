#include <iostream>
#include <lib_cypher_decipher.hpp>


namespace {
    int compare_zeros_ones(uint8_t **bits, uint32_t n)
    {
        /***
         * Retorna 3 si hay mas 1s, 2 si hay mas ceros y 1 si hay igual cantidad
         *  ***/

        uint32_t zeros_cnt = 0;
        uint32_t ones_cnt = 0;
        for (uint32_t i=0; i < n; i++) {
            if (!(*bits[i]))
                zeros_cnt++;
        }

        ones_cnt = n - zeros_cnt;
        if (ones_cnt > zeros_cnt)
            return EVERY_THREE;
        else if (ones_cnt < zeros_cnt)
            return EVERY_TWO;
        else
            return EVERY_ONE;
    }

    void change_bits(uint32_t n, uint32_t m, uint8_t **group)
    {
        uint32_t bits_cnt = 0;
        for (uint32_t i=0; i < n; i++) {
            bits_cnt++;
            if (bits_cnt == m) {
                *group[i] = !(*group[i]);
                bits_cnt = 0;
            }
        }
    }

    bool get_groups(uint32_t n, uint8_t *group, uint32_t row, uint32_t col, uint8_t **matrix, uint32_t rows, uint32_t cols) 
    {
    uint32_t k = 0;
    uint32_t j=col;
    for (uint32_t i=row; i<rows; i++) {
        while (j<cols) {
            group[k++] = matrix[i][j];
            if (!(k % n))
                return true;
            j++;
        }
        j=0;
    }
    return false;
    }

    void circular_shift(uint8_t **bits, uint32_t n)
    {
        uint8_t aux = *bits[n-1];
        for (uint32_t i=0; i < n-1; i++) {
            *bits[n - 1 - i] = *bits[n - 2 - i];
        }
        *bits[0] = aux;
    }
}

bool decipher_1(uint8_t **matrix, uint32_t n, uint32_t rows, uint32_t cols) 
{
    uint8_t **group = new uint8_t*[n];
    uint8_t m, m_aux;
    uint32_t k = 0;

    change_bits(n,EVERY_ONE,0,0,matrix,rows,cols);

    if (!get_groups(n,group,0,0,matrix,rows,cols)) {
        std::cout << "No hay suficientes datos" << std::endl;
        return false;
    }

    m = compare_zeros_ones(group, n);

    for (uint32_t i=0; i < rows; i++) {
        for (uint32_t j=0; j < cols; j++) {
            if (k == n) {
                change_bits(n,m,i,j,matrix,rows,cols);
                get_groups(n,group,i,j,matrix,rows,cols);
                m = compare_zeros_ones(group, n);
                k = 0;
            }
            k++;
        }
    }
    return true;
}

bool cypher_1(uint8_t **matrix, uint32_t n, uint32_t rows, uint32_t cols)
{
    uint8_t **group = new uint8_t*[n]; 
    uint8_t m, m_aux;
    bool first_group = true;
    uint32_t k = 0;
    
    m = EVERY_ONE;
    
    for (uint32_t i=0; i < rows; i++) {
        for (uint32_t j=0; j < cols; j++) {
            group[k++] = &matrix[i][j];
            if (k == n) {
                m = m_aux;
                m_aux = compare_zeros_ones(group, n);
                if (first_group) {
                    first_group = false;
                    change_bits(m,EVERY_ONE,group);
                }
                change_bits(n,m,group);
                k = 0;
            }
            k++;
        }
    }

    delete [] group;
    return true;
}

bool cypher2(uint8_t **matrix, uint32_t n, uint32_t rows, uint32_t cols)
{
    uint8_t **group = new uint8_t*[n];
    uint32_t bits_count = 0;
    uint32_t k = 0;

    for (uint32_t i=0; i < rows; i++) {
        for (uint32_t j=0; j < cols; j++) {
            group[k++] = &matrix[i][j];
            bits_count++;
            if (!(bits_count % n)) {
                circular_shift(group, n);
                k = 0;
            }
        }
    }
    
    if (k)
        circular_shift(group, k);
    
    delete[] group;
    return true;
}