#ifndef CATALOGO_H
#define CATALOGO_H

#include <vector>
#include <string>

class Catalogo {
private:
    std::vector<std::string> items;

public:
    void agregarItem(const std::string& item);
    void mostrar() const;
};

#endif
