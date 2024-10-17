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
 * Función principal
 */
int main() {
    return 0;
}
