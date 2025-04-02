#ifndef __APP_H__
#define __APP_H__
#include <stdint.h>
#define FAILURE true
#define SUCCESS false

using method_ptr = bool(*)(uint8_t **, uint32_t, uint32_t, uint32_t);

int read_file(const char *, uint8_t **);
bool int_to_binary_matrix(uint8_t *, uint8_t **, uint32_t);
bool assign_matrix_bytes(uint8_t ***, int32_t);
bool delete_matrix(uint8_t ***, int32_t);
void bin_to_char(uint8_t **, int32_t, uint8_t *);
bool app(method_ptr, char *, char*, uint8_t);
bool write_file(const char *, uint8_t *, int32_t);
bool app_main(char* argv[]);

#endif