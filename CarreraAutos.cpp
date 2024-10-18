#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <random>
#include <chrono>

using namespace std;

// Variables globales
int distanciaMeta;              // Distancia total que los autos deben recorrer (en metros)
int numeroAutos;                // Número de autos que participan en la carrera
vector<int> progresoAutos;      // Vector para almacenar el progreso de cada auto (distancia recorrida en metros)
vector<int> ordenLlegada;       // Vector que almacena el orden en que los autos llegan a la meta
int lugarLlegada = 1;           // Contador para llevar el lugar de llegada de los autos

// Mutex para sincronizar el acceso a recursos compartidos (consola y progreso)
mutex consolaMutex;

/**
 * Función que simula la carrera de un auto.
 * Cada auto avanza de manera aleatoria y se pausa entre movimientos para simular el tiempo de avance.
 * @param idAuto: Identificador único del auto (número de auto en la carrera)
*/
void simularCarrera(int idAuto) {
    // Inicialización de generador de números aleatorios
    random_device randomDevice;  // Dispositivo aleatorio para semillas
    mt19937 generador(randomDevice());  // Generador de números aleatorios basado en Mersenne Twister
    uniform_int_distribution<> avanceDistribucion(1, 10); // Distribución aleatoria de avance (1-10 metros)
    uniform_int_distribution<> pausaDistribucion(100, 500); // Distribución aleatoria para pausa (100-500 ms)

    int progreso = 0;  // Progreso actual del auto (en metros)

    // Bucle que simula el avance del auto hasta que alcance la distancia meta
    while (progreso < distanciaMeta) {
        int avance = avanceDistribucion(generador);  // Calcular avance aleatorio (1-10 metros)
        this_thread::sleep_for(chrono::milliseconds(pausaDistribucion(generador)));  // Pausar el auto de manera aleatoria (100-500 ms)

        // Bloquear el acceso para actualizar el progreso y mostrar el resultado en consola
        consolaMutex.lock();
        progreso += avance;  // Actualizar el progreso del auto
        if (progreso > distanciaMeta) progreso = distanciaMeta;  // Evitar que el auto avance más allá de la meta
        progresoAutos[idAuto] = progreso;  // Almacenar el progreso actual en el vector correspondiente

        // Comprobar si el auto ha alcanzado la meta
        if (progreso == distanciaMeta) {
            // Mostrar en consola el mensaje de llegada en rojo
            cout << "\033[91mAuto " << idAuto << " avanza " << avance << " metros y termina la carrera en el lugar " << lugarLlegada << "!\033[0m\n";
            ordenLlegada.push_back(idAuto);  // Registrar el auto en el orden de llegada
            lugarLlegada++;  // Incrementar el contador de lugar de llegada
        } else {
            // Mostrar el progreso intermedio del auto
            cout << "Auto " << idAuto << " avanza " << avance << " metros (total: " << progreso << " metros)\n";
        }

        consolaMutex.unlock();  // Liberar el mutex para que otros autos puedan avanzar
    }
}

/**
 * Función principal que inicializa la carrera y ejecuta las hebras de los autos.
 * Recibe los parámetros de distancia de la carrera y el número de autos desde la línea de comandos.
 */
int main(int argc, char *argv[]) {
    // Validar los argumentos de entrada (espera dos argumentos: distancia y número de autos)
    if (argc != 3) {
        cout << "Uso: ./carrera <distancia_meta> <numero_autos>\n";
        return 1;
    }

    // Asignar la distancia total de la carrera y el número de autos a las variables globales
    distanciaMeta = stoi(argv[1]);  // Convertir el primer argumento a entero (distancia total en metros)
    numeroAutos = stoi(argv[2]);    // Convertir el segundo argumento a entero (número de autos participantes)

    // Inicializar el vector de progreso de los autos con ceros
    progresoAutos.resize(numeroAutos, 0);

    // Crear un vector para almacenar las hebras de los autos
    vector<thread> hebrasAutos;

    // Crear una hebra por cada auto, ejecutando la función simularCarrera
    for (int i = 0; i < numeroAutos; ++i) {
        hebrasAutos.push_back(thread(simularCarrera, i));  // Crear y lanzar la hebra para cada auto
    }

    // Esperar a que todas las hebras (autos) terminen su ejecución
    for (int i = 0; i < numeroAutos; ++i) {
        hebrasAutos[i].join();  // Asegurarse de que cada auto termine su carrera antes de continuar
    }

    // Mostrar los resultados finales de la carrera, basados en el orden de llegada
    cout << "\nResultados de la carrera:\n";
    cout << "Lugar               Auto\n";
    cout << "------------------------\n";

    // Mostrar en consola el orden de llegada de los autos
    for (int i = 0; i < ordenLlegada.size(); ++i) {
        cout << " " << i + 1 << "                Auto " << ordenLlegada[i] << "\n";
    }

    return 0;
}
