#include "Usuario.h"
#include <fstream>

Usuario::Usuario() {}

Usuario::Usuario(const std::string& nombre, const std::string& password)
    : nombre(nombre), password(password) {}

std::string Usuario::getNombre() const {
    return nombre;
}

bool Usuario::verificarPassword(const std::string& pwd) const {
    return password == pwd;
}

void Usuario::guardar(std::ofstream& out) const {
    size_t len = nombre.size();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(nombre.c_str(), len);
    len = password.size();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(password.c_str(), len);
}

void Usuario::cargar(std::ifstream& in) {
    size_t len;
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    nombre.resize(len);
    in.read(&nombre[0], len);
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    password.resize(len);
    in.read(&password[0], len);
}
