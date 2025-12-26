#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <iomanip>

struct Transaction {
    std::string id;
    double monto;
    std::string fecha;
};

class Reconciliador {
public:
    // 1. Leer el archivo "datos.csv" (Formato: id,fecha,monto)
    std::vector<Transaction> leerArchivoDatos(std::string nombreArchivo) {
        std::vector<Transaction> lista;
        std::ifstream archivo(nombreArchivo);
        std::string linea;

        if (!archivo.is_open()) {
            std::cerr << "Error: No se pudo abrir " << nombreArchivo << std::endl;
            return lista;
        }

        std::getline(archivo, linea); // Saltar encabezado (id,fecha,monto)

        while (std::getline(archivo, linea)) {
            std::stringstream ss(linea);
            Transaction t;
            std::string temp;

            std::getline(ss, t.id, ',');     // Leer ID
            std::getline(ss, t.fecha, ',');  // Leer Fecha
            std::getline(ss, temp, ',');     // Leer Monto como string
            
            if (!temp.empty()) {
                t.monto = std::stod(temp);
                lista.push_back(t);
            }
        }
        archivo.close();
        return lista;
    }

    // 2. Leer el archivo del Banco (extracto_banco.csv)
    std::vector<Transaction> leerBanco(std::string nombreArchivo) {
        std::vector<Transaction> lista;
        std::ifstream archivo(nombreArchivo);
        std::string linea;

        if (std::getline(archivo, linea)) { /* Saltar encabezado */ }

        while (std::getline(archivo, linea)) {
            std::stringstream ss(linea);
            std::string fecha, desc, monto, ref;
            
            std::getline(ss, fecha, ',');
            std::getline(ss, desc, ',');
            std::getline(ss, monto, ',');
            std::getline(ss, ref, ',');

            if (!ref.empty()) {
                lista.push_back({ref, std::stod(monto), fecha});
            }
        }
        return lista;
    }

    // 3. Conciliar y generar informe TXT
    void conciliarYReportar(std::vector<Transaction> erp, std::vector<Transaction> banco) {
        std::unordered_map<std::string, double> mapaERP;
        std::ofstream reporte("informe_auditoria.txt");
        
        reporte << "==========================================\n";
        reporte << "      INFORME DE CONCILIACION BANCARIA    \n";
        reporte << "==========================================\n\n";

        for (const auto& t : erp) {
            mapaERP[t.id] = t.monto;
        }

        for (const auto& b : banco) {
            if (mapaERP.count(b.id)) {
                if (std::abs(mapaERP[b.id] - b.monto) < 0.01) {
                    reporte << "[OK] CONCILIADO: ID " << b.id << " por $" << b.monto << "\n";
                } else {
                    reporte << "[!] DIFERENCIA: ID " << b.id << " (ERP: $" << mapaERP[b.id] << " | Banco: $" << b.monto << ")\n";
                }
                mapaERP.erase(b.id);
            } else {
                reporte << "[?] SOLO EN BANCO: ID " << b.id << " ($" << b.monto << ") - Pendiente de registro ERP\n";
            }
        }

        for (auto const& [id, monto] : mapaERP) {
            reporte << "[?] SOLO EN ERP: ID " << id << " ($" << monto << ") - No aparece en extracto\n";
        }

        reporte.close();
        std::cout << "Conciliacion finalizada. Resultados guardados en 'informe_auditoria.txt'" << std::endl;
    }
};

int main() {
    Reconciliador motor;

    // Cargamos los 1,000 registros de 'datos.csv' y los del banco
    auto datosERP = motor.leerArchivoDatos("datos.csv");
    auto datosBanco = motor.leerBanco("extracto_banco.csv");

    if(datosERP.empty() || datosBanco.empty()) {
        std::cout << "Error: Asegurate de tener los archivos 'datos.csv' y 'extracto_banco.csv' listos." << std::endl;
        return 1;
    }

    motor.conciliarYReportar(datosERP, datosBanco);

    return 0;
}