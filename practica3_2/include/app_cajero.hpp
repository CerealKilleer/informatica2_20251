#ifndef __APP_CAJERO__
    #define __APP_CAJERO__
    #include <stdint.h>
    #include <string>
    using method_ptr = bool(*)(uint8_t **, uint32_t, uint32_t, uint32_t);
    int main_app();
    bool validar_usuario(const std::string& file_string, bool, std::string&);
    bool validate_user_pass(std::string &, std::string &, const std::string &, bool, std::string&);
    bool validate_new_user(const std::string, std::string&);
    bool write_data(const char*, method_ptr, uint32_t, const std::string&);
    std::string read_data(const char*, method_ptr, uint32_t);
    bool crear_usuario(std::string&);
    bool is_number(const std::string&);
    void app_administrador(std::string& users_file);
    void app_user(std::string&, std::string&);
    void consultar_saldo(std::string&, std::string&);
#endif