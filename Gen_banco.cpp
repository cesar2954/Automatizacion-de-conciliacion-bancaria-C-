#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

struct Transaction {
    std::string id;
    std::string fecha;
    double monto;
};

int main() {
    std::ifstream archivoEntrada("datos.csv");
    std::ofstream archivoSalida("extracto_banco.csv");
    std::vector<Transaction> datosERP;
    std::string linea;

    if (!archivoEntrada.is_open()) {
        std::cerr << "Error: No se encontro 'datos.csv'. Ejecuta primero el generador del ERP." << std::endl;
        return 1;
    }

    // 1. Leer datos del ERP para saber qué existe
    std::getline(archivoEntrada, linea); // Saltar encabezado
    while (std::getline(archivoEntrada, linea)) {
        std::stringstream ss(linea);
        Transaction t;
        std::string temp;
        std::getline(ss, t.id, ',');
        std::getline(ss, t.fecha, ',');
        std::getline(ss, temp, ',');
        t.monto = std::stod(temp);
        datosERP.push_back(t);
    }

    // 2. Crear el encabezado del banco
    archivoSalida << "FECHA_OPERACION,DESCRIPCION,MONTO,REFERENCIA_BUSQUEDA\n";

    // 3. Simular que el banco procesó CADA 5ta transacción del ERP (para variar los datos)
    for (size_t i = 0; i < datosERP.size(); i += 5) {
        archivoSalida << datosERP[i].fecha << ","
                      << "TRANSFERENCIA RECIBIDA REF-" << datosERP[i].id << ","
                      << datosERP[i].monto << ","
                      << datosERP[i].id << "\n";
    }

    // 4. AGREGAR UNA ANOMALÍA: Una comisión que NO está en el ERP
    archivoSalida << "2025-12-31,COMISION MANTENIMIENTO CUENTA,45.00,99999\n";

    archivoEntrada.close();
    archivoSalida.close();

    std::cout << "¡Exito! 'extracto_banco.csv' generado usando datos de 'datos.csv'." << std::endl;
    std::cout << "Se han tomado " << (datosERP.size() / 5) + 1 << " transacciones para el banco." << std::endl;

    return 0;
}