#  Financial Matching Engine & Audit Pipeline (C++)

![C++](https://img.shields.io/badge/Language-C%2B%2B17-blue.svg)
![Status](https://img.shields.io/badge/Status-Production--Ready-success.svg)
![Focus](https://img.shields.io/badge/Focus-Audit%20%26%20Finance-orange.svg)

#  Propósito del Proyecto
Este ecosistema de herramientas automatiza el proceso de **Conciliación Bancaria**, una de las tareas más críticas y propensas a errores en la auditoría financiera. Utilizando algoritmos de búsqueda optimizados en C++, el sistema permite cruzar miles de registros contables (ERP) contra extractos bancarios en milisegundos, identificando discrepancias, omisiones y errores de registro.



#  Arquitectura del Sistema
El proyecto está diseñado como un **Pipeline de Datos** de tres etapas:

1.  **Generador ERP (`generador.cpp`)**: Simula la exportación masiva de un Libro Mayor contable en formato CSV (1,000+ registros).
2.  **Generador Bancario (`gen_banco_automatico.cpp`)**: Actúa como una interfaz de datos bancarios. Lee el archivo del ERP para simular transacciones procesadas, aplicando desfases y agregando cargos bancarios imprevistos.
3.  **Matching Engine (`Conciliador_Final.cpp`)**: El núcleo del sistema. Utiliza una estructura de **Hash Map (`std::unordered_map`)** para garantizar una complejidad computacional de **O(n)**, permitiendo una escalabilidad superior a las soluciones basadas en hojas de cálculo (Excel).

#  Guía de Ejecución Rápida

Para ejecutar el ciclo de auditoría completo, compile y ejecute los archivos en el siguiente orden:

```bash
# 1. Generar la contabilidad del ERP
g++ generador.cpp -o generador
.\generador

# 2. Generar el extracto del banco basado en el ERP
g++ gen_banco.cpp -o gen_banco
.\gen_banco

# 3. Ejecutar la conciliación y generar informe
g++ Conciliador.cpp -o conciliador
.\conciliador
