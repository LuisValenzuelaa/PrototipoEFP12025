#ifndef USUARIO_H
#define USUARIO_H

#include <string>

class Usuario {
private:
    std::string nombre;
    std::string password;

public:
    Usuario();
    Usuario(const std::string& nombre, const std::string& password);

    std::string getNombre() const;
    bool verificarPassword(const std::string& pwd) const;

    void guardar(std::ofstream& out) const;
    void cargar(std::ifstream& in);
};

#endif
