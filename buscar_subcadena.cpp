#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <sstream>

using namespace std;

class Palabra {
private:
    string palabra;
    unsigned int n_linea;
public:
    Palabra(string palabra, unsigned int n_linea) : palabra(palabra), n_linea(n_linea) {}
    void FijarPalabra(string n_palabra) { palabra = n_palabra; }
    void FijarNumLinea(unsigned int n_num) { n_linea = n_num; }
    string ObtenerPalabra() const { return palabra; }
    unsigned int ObtenerNumLinea() const { return n_linea; }
};

class ArchivoTexto {
private:
    vector<list<string>> lineasTexto;
public:
    void AgregarListaPals(list<string> n_lista) { lineasTexto.push_back(n_lista); }

    void BuscarPrincipio(const string& subcadena) {
        cout << "Palabras que comienzan con '" << subcadena << "':" << endl;
        int count = 0;
        for (size_t i = 0; i < lineasTexto.size(); i++) {
            for (const string& palabra : lineasTexto[i]) {
                if (palabra.rfind(subcadena, 0) == 0) {
                    cout << "Linea " << i + 1 << ": " << palabra << endl;
                    count++;
                }
            }
        }
        cout << "Total: " << count << "\n" << endl;
    }

    void BuscarContiene(const string& subcadena) {
        cout << "Palabras que contienen '" << subcadena << "':" << endl;
        int count = 0;
        for (size_t i = 0; i < lineasTexto.size(); i++) {
            for (const string& palabra : lineasTexto[i]) {
                if (palabra.find(subcadena) != string::npos) {
                    cout << "Linea " << i + 1 << ": " << palabra << endl;
                    count++;
                }
            }
        }
        cout << "Total: " << count << "\n" << endl;
    }

    void BuscarInvertida(const string& subcadena) {
        stack<char> pila;
        for (char c : subcadena) pila.push(c);
        string subInvertida;
        while (!pila.empty()) {
            subInvertida += pila.top();
            pila.pop();
        }

        cout << "Palabras que contienen la subcadena invertida '" << subInvertida << "':" << endl;
        int count = 0;
        for (size_t i = 0; i < lineasTexto.size(); i++) {
            for (const string& palabra : lineasTexto[i]) {
                if (palabra.find(subInvertida) != string::npos) {
                    cout << "Linea " << i + 1 << ": " << palabra << endl;
                    count++;
                }
            }
        }
        cout << "Total: " << count << "\n" << endl;
    }

    void CargarDesdeArchivo(const string& nombreArchivo) {
        ifstream archivo(nombreArchivo);
        if (!archivo) {
            cerr << "Error al abrir el archivo." << endl;
            exit(1);
        }

        string linea;
        getline(archivo, linea); // Leer cantidad de líneas (no usada directamente)
        string subcadena;
        getline(archivo, subcadena); // Leer la subcadena a buscar
        
        while (getline(archivo, linea)) {
            list<string> palabras;
            stringstream ss(linea);
            string palabra;
            while (ss >> palabra) {
                palabras.push_back(palabra);
            }
            AgregarListaPals(palabras);
        }
        archivo.close();
        
        // Ejecutar las búsquedas en el orden correcto
        BuscarPrincipio(subcadena);
        BuscarContiene(subcadena);
        BuscarInvertida(subcadena);
    }
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Uso: " << argv[0] << " archivo.txt" << endl;
        return 1;
    }
    
    ArchivoTexto texto;
    texto.CargarDesdeArchivo(argv[1]);
    
    return 0;
}
