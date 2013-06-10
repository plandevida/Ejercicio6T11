//
//  main.cpp
//  Ejercicio6T11
//
//  Created by Daniel on 10/06/13.
//  Copyright (c) 2013 Daniel. All rights reserved.
//

#include <iostream>
#include "Lista.h"

using namespace std;

const int N = 5;
const int M = 8;
Lista<char> palabra;

void ej6T11();
void ej6T11(const char lab[N][M], bool marcas[][M], int xOrigen, int yOrigen, int xDestino, int yDestino, char solucion[], int k, typename Lista<char>::Iterador &it, char mejorSol[], int &mejorLog);
void calculaPosicion(int &x, int &y, int k);
char calculaDirecion(int k);
bool esValida(const char lab[N][M], char solucion[], int k, char letra, int x, int y);
bool esSolucion(int x, int y, int xDest, int yDest);

int main(int argc, const char * argv[])
{

    ej6T11();
    
    return 0;
}

void ej6T11() {
    char lab[N][M] = { {'M','D','A','A','E','E','D','A'},
                       {'A','E','E','D','D','A','E','D'},
                       {'D','B','D','X','E','D','A','E'},
                       {'E','A','E','D','A','R','T','D'},
                       {'E','D','M','P','L','E','D','A'},
                     };
    
    palabra.ponDr('E');
    palabra.ponDr('D');
    palabra.ponDr('A');
    
    char solucion[N*M];
    char mejorSolucion[N*M];
    
    for (int i=0; i < N*M; i++) {
        solucion[i] = ' ';
        mejorSolucion[i] = ' ';
    }
    
    bool marcas[N][M];
    
    for (int j = 0; j < N; j++) {
        for (int k = 0; k < M; k++) {
            marcas[j][k] = false;
        }
    }
    
    Lista<char>::Iterador it = palabra.principio();
    it.avanza();
    
    int mejorLongitud = N*M;
    
    ej6T11(lab, marcas, N-1, 0, 0, M-1, solucion, 0, it, mejorSolucion, mejorLongitud);
}

void ej6T11(const char lab[N][M], bool marcas[][M], int xOrigen, int yOrigen, int xDestino, int yDestino, char solucion[], int k, typename Lista<char>::Iterador &it, char mejorSol[], int &mejorLog) {
    
    char letra;
    int xAux, yAux;
    
    for (int i = 0; i < 4; i++) {
        xAux = xOrigen;
        yAux = yOrigen;
        
        calculaPosicion(xAux, yAux, i);
        
        if ( ! marcas[xAux][yAux]) {
            letra = it.elem();
            
            solucion[k] = calculaDirecion(i);
            
            if ( esValida(lab, solucion, k, letra, xAux, yAux) ) {
                
                if ( esSolucion(xAux, yAux, xDestino, yDestino) ) {
                    
                    if ( k < mejorLog ) {
                        
                        mejorLog = k;
                        
                        for (int j = 0; j < k; j++) {
                            mejorSol[j] = solucion[j];
                        }
                        
                        cout << endl << "Tratar mejor solucion" << endl;
                        for (int g=0; g <= k; g++) {
                            cout << solucion[g] << ", ";
                        }
                    }
                }
                else {
                    
                    it.avanza();
                    if (it == palabra.final()) {
                        it = palabra.principio();
                    }
                    
                    marcas[xAux][yAux] = true;
                    
                    ej6T11(lab, marcas, xAux, yAux, xDestino, yDestino, solucion, k+1, it, mejorSol, mejorLog);
                    
                    marcas[xAux][yAux] = false;
                }
            }
        }
    }
}

bool esValida(const char lab[N][M], char solucion[], int k, char letra, int x, int y) {
    
    return (x >= 0 && x < N && y >= 0 && y < M) && (letra == lab[x][y]);
}

bool esSolucion(int x, int y, int xDest, int yDest) {
    
    return (x == xDest && y == yDest);
}

void calculaPosicion(int &x, int &y, int k) {
    
    switch (k) {
        case 0: // E
            y += 1;
            break;
        case 1: // N
            x -= 1;
            break;
        case 2: // O
            y -= 1;
            break;
        case 3: // S
            x += 1;
            break;
    }
}

char calculaDirecion(int k) {
    char dir = ' ';
    
    switch (k) {
        case 0: // E
            dir = 'E';
            break;
        case 1: // N
            dir = 'N';
            break;
        case 2: // O
            dir = 'O';
            break;
        case 3: // S
            dir = 'S';
            break;
    }
    
    return dir;
}