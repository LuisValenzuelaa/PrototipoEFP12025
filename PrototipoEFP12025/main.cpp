#include <iostream>
#include <fstream>
#include <vector>
#include "Usuario.h"
#include "Catalogo.h"
#include "Bitacora.h"

std::vector<Usuario> cargarUsuarios() {
    std::vector<Usuario> usuarios;
    std::ifstream in("usuarios.dat", std::ios::binary);
    if (!in) return usuarios;

    while (in.peek() != EOF) {
        Usuario u;
        u.cargar(in);
        usuarios.push_back(u);
    }
    return usuarios;
}

void guardarUsuarios(const std::vector<Usuario>& usuarios) {
    std::ofstream out("usuarios.dat", std::ios::binary);
    for (const auto& u : usuarios) {
        u.guardar(out);
    }
}

Usuario* autenticar(std::vector<Usuario>& usuarios) {
    std::string nombre, password;
    std::cout << "Usuario: ";
    std::cin >> nombre;
    std::cout << "Contraseńa: ";
    std::cin >> password;

    for (auto& u : usuarios) {
        if (u.getNombre() == nombre && u.verificarPassword(password)) {
            Bitacora::registrar("Inicio de sesión: " + nombre);
            return &u;
        }
    }
    std::cout << "Autenticación fallida.\n";
    return nullptr;
}

void registrarUsuario(std::vector<Usuario>& usuarios) {
    std::string nombre, password;
    std::cout << "Nuevo usuario: ";
    std::cin >> nombre;
    std::cout << "Contraseńa: ";
    std::cin >> password;
    usuarios.emplace_back(nombre, password);
    guardarUsuarios(usuarios);
    Bitacora::registrar("Usuario registrado: " + nombre);
}

int main() {
    std::vector<Usuario> usuarios = cargarUsuarios();
    Catalogo catalogo;

    Usuario* usuarioActual = nullptr;

    int opcion;
    do {
        std::cout << "\n1. Iniciar sesión\n2. Salir\nOpción: ";
        std::cin >> opcion;

        if (opcion == 1) {
            usuarioActual = autenticar(usuarios);
            if (usuarioActual) {
                int op;
                do {
                    std::cout << "\nBienvenido, " << usuarioActual->getNombre() << "\n";
                    std::cout << "1. Ver catálogo\n";
                    std::cout << "2. Agregar al catálogo\n";
                    std::cout << "3. Registrar nuevo usuario\n";
                    std::cout << "3. Seguridad\n";
                    std::cout << "3. Informes\n";
                    std::cout << "4. Cerrar sesión\n";
                    std::cout << "Opción: ";
                    std::cin >> op;

                    if (op == 1) {
                        catalogo.mostrar();
                    } else if (op == 2) {
                        std::string item;
                        std::cout << "Nombre del item: ";
                        std::cin.ignore();
                        std::getline(std::cin, item);
                        catalogo.agregarItem(item);
                        Bitacora::registrar("Item agregado por " + usuarioActual->getNombre());
                    } else if (op == 3) {
                        registrarUsuario(usuarios);
                    } else if (op == 4) {
                        usuarioActual = nullptr;
                        std::cout << "Sesión cerrada.\n";
                    }
                } while (usuarioActual != nullptr);
            }
        }

    } while (opcion != 2);

    return 0;
}
