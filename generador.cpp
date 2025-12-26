#include <iostream>
#include <fstream>
#include <vector>
#include <random> // Para generar números aleatorios de calidad
#include <string>

int main() {
    int totalFilas = 1000;
    std::ofstream archivo("datos.csv");

    // Configuración de aleatoriedad
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> montoNormal(500.0, 3000.0); // Transacciones comunes
    std::uniform_real_distribution<double> montoAnomalo(50000.0, 100000.0); // Fraudes o errores

    if (!archivo.is_open()) {
        std::cerr << "Error al crear el archivo." << std::endl;
        return 1;
    }

    // Escribir encabezado
    archivo << "id,fecha,monto\n";

    for (int i = 1; i <= totalFilas; ++i) {
        double monto;
        
        // Crear una anomalía cada 100 registros (aprox)
        if (i % 100 == 0) {
            monto = montoAnomalo(gen);
        } else {
            monto = montoNormal(gen);
        }

        // Escribir fila: ID, Fecha ficticia, Monto
        archivo << i << ",2025-12-25," << monto << "\n";
    }

    archivo.close();
    std::cout << "¡Exito! Se ha creado 'datos.csv' con " << totalFilas << " filas." << std::endl;

    return 0;
}