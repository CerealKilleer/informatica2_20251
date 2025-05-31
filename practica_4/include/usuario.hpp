#ifndef __USUARIO_HPP__
#define __USUARIO_HPP__
#include <stdint.h>
class Usuario
{
    public:
        uint32_t cedula;
        uint16_t antiguedad;
        float puntuacion;
        bool anfitrion;
        
        Usuario(uint32_t cedula, uint16_t antiguedad, float puntuacion, bool anfitrion);
};
#endif