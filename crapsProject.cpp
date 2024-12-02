#include <iostream>
#include <cstdlib> 
#include <ctime> 
#include <vector>
#include <fstream> 

using namespace std;

int tirarDados() {
    int sumaDados;
    int dado1 = rand() % 6 + 1;
    int dado2 = rand() % 6 + 1;
    sumaDados = dado1 + dado2;
    cout << "Has tirado un " << dado1 << " y un " << dado2 << ". Total: " << sumaDados << endl;
    return sumaDados;
}

void imprimirMatriz(const vector<vector<int>> &matriz) {
    cout << "Matriz de resultados:\n";
    for (size_t i = 0; i < matriz.size(); ++i) {
        for (size_t j = 0; j < matriz[i].size(); ++j) {
            cout << matriz[i][j] << "\t";
        }
        cout << endl;
    }
}

void guardarEnArchivoCSV(const vector<vector<int>> &matriz, const string &nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo para escribir.\n";
        return;
    }
    for (size_t i = 0; i < matriz.size(); ++i) {
        for (size_t j = 0; j < matriz[i].size(); ++j) {
            archivo << matriz[i][j];
            if (j < matriz[i].size() - 1) {
                archivo << ",";
            }
        }
        archivo << endl;
    }
    archivo.close();
    cout << "La matriz ha sido guardada en el archivo: " << nombreArchivo << endl;
}

void contarPerdedores(const vector<vector<int>> &matriz) {
    cout << "Jugadores que perdieron en cada ronda:\n";
    for (size_t ronda = 1; ronda < matriz[0].size(); ++ronda) {
        int perdedores = 0;
        for (size_t jugador = 1; jugador < matriz.size(); ++jugador) {
            int resultado = matriz[jugador][ronda];
            if ((ronda == 1 && resultado == 0 ) || (ronda > 1 && resultado == 0)) {
                ++perdedores;
            }
        }
        cout << "Ronda " << ronda << ": " << perdedores << " jugador(es) perdieron.\n";
        perdedores = 0;
    }
}

void contarGanadores(const vector<vector<int>> &matriz) {
    cout << "Jugadores que ganaron en cada ronda:\n";
    for (size_t ronda = 1; ronda < matriz[0].size(); ++ronda) {
        int ganadores = 0;
        for (size_t jugador = 1; jugador < matriz.size(); ++jugador) {
            int resultado = matriz[jugador][ronda];
            if ((ronda == 1 && resultado == 1 ) || (ronda > 1 && resultado ==1)) {
                ++ganadores;
            }
        }
        cout << "Ronda " << ronda << ": " << ganadores << " jugador(es) ganador(es).\n";
        ganadores = 0;
    }
}

void rondasPerdidasPorJugador(const vector<vector<int>> &matriz) {
    cout << "Rondas perdidas por cada jugador:\n";
    for (size_t jugador = 1; jugador < matriz.size(); ++jugador) {
        int perdidas = 0;
        for (size_t ronda = 1; ronda < matriz[jugador].size(); ++ronda) {
            int resultado = matriz[jugador][ronda];
            if ((ronda == 1 && resultado == 0 ) || (ronda > 1 && resultado == 0)) {
                ++perdidas;
            }
        }
        cout << "Jugador " << jugador << ": " << perdidas << " rondas perdidas.\n";
    }
}

void rondasGanadasPorJugador(const vector<vector<int>> &matriz) {
    cout << "Rondas ganadas por cada jugador:\n";
    for (size_t jugador = 1; jugador < matriz.size(); ++jugador) {
        int ganadas = 0;
        for (size_t ronda = 1; ronda < matriz[jugador].size(); ++ronda) {
            int resultado = matriz[jugador][ronda];
            if ((ronda == 1 && resultado == 1 ) || (ronda > 1 && resultado ==1)) {
                ++ganadas;
            }
        }
        cout << "Jugador " << jugador << ": " << ganadas << " rondas ganadas.\n";
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    cout << "¡Bienvenido al juego de Craps!" << endl;

    int jugadores;
    cout << "Ingrese el número de jugadores que van a jugar esta partida: ";
    cin >> jugadores;

    vector<vector<int>> matrizResultados(jugadores + 1);
    matrizResultados[0].push_back(0);
    vector<vector<int>> matrizGana(jugadores + 1);
    matrizGana[0].push_back(0);

    int ronda = 0;
    for (int i = 1; i <= jugadores; ++i) {
        matrizResultados[i].push_back(i);
        matrizGana[i].push_back(i);
    }

    char continuar;
    do {
        ++ronda;
        matrizResultados[0].push_back(ronda);
        matrizGana[0].push_back(ronda);

        for (int i = 1; i <= jugadores; ++i) {
            int suma = tirarDados();

            if (suma == 7 || suma == 11) {
                cout << "Jugador " << i << ": ¡Felicidades! Has ganado en la primera tirada." << endl;
                matrizResultados[i].push_back(suma);
                matrizGana[i].push_back(1);

            } else if (suma == 2 || suma == 3 || suma == 12) {
                cout << "Jugador " << i << ": ¡Craps! Has perdido en la primera tirada de dados." << endl;
                matrizResultados[i].push_back(suma);
                matrizGana[i].push_back(0);
            } else {
                int punto = suma;
                cout << "Jugador " << i << ": Tu punto es " << punto << ". Sigue tirando hasta igualarlo, pero evita sacar un 7." << endl;

                while (true) {
                    suma = tirarDados();
                    if (suma == punto) {
                        cout << "Jugador " << i << ": ¡Felicidades! Has igualado tu punto y ganado el juego." << endl;
                        matrizResultados[i].push_back(punto);
                        matrizGana[i].push_back(1);
                        break;
                    } else if (suma == 7) {
                        cout << "Jugador " << i << ": ¡Has sacado un 7! Has perdido el juego." << endl;
                        matrizResultados[i].push_back(suma);
                        matrizGana[i].push_back(0);
                        break;
                    }
                }
            }
        }

        cout << "¿Deseas jugar otra ronda (s es Si y n es No)? (s/n): ";
        cin >> continuar;
    } while (continuar == 's' || continuar == 'S');

    int opcion;
    do {
        cout << "|---| Menú Final de Craps |---|" << endl;
        cout << "1. Generar e Imprimir las matrices de puntajes" << endl;
        cout << "2. Cantidad de jugadores que Perdieron en cada ronda" << endl;
        cout << "3. Cantidad de jugadores que Ganaron en cada ronda" << endl;
        cout << "4. Número de rondas Perdidas por jugador" << endl;
        cout << "5. Número de rondas Ganadas por jugador" << endl;
        cout << "6. Salir del juego" << endl;
        cout << "Selecciona una opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            imprimirMatriz(matrizResultados);
            guardarEnArchivoCSV(matrizResultados, "resultados_craps.csv");
            break;
        case 2:
            contarPerdedores(matrizGana);
            break;
        case 3:
            contarGanadores(matrizGana);
            break;
        case 4:
            rondasPerdidasPorJugador(matrizGana);
            break;
        case 5:
            rondasGanadasPorJugador(matrizGana);
            break;
        case 6:
            cout << "Saliendo del juego...\n";
            break;
        default:
            cout << "El dato ingresado es invalido, por favor ingrese un numero entero entre 1 y 6\n";
            break;
        }
    } while (opcion >= 1 || opcion < 6);

    return 0;
}