#include "Bitacora.h"
#include <fstream>
#include <ctime>

void Bitacora::registrar(const std::string& mensaje) {
    std::ofstream out("bitacora.txt", std::ios::app);
    std::time_t t = std::time(nullptr);
    out << std::ctime(&t) << ": " << mensaje << std::endl;
}
