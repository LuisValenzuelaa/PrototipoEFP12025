#include "Catalogo.h"
#include <iostream>

void Catalogo::agregarItem(const std::string& item) {
    items.push_back(item);
}

void Catalogo::mostrar() const {
    for (const auto& item : items) {
        std::cout << "- " << item << std::endl;
    }
}
