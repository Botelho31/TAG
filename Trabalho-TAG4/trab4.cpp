#include <bits/stdc++.h>
#include <cstdlib>

int matriz[9][9];

void CarregarMatriz(std::string file){
    std::ifstream FileReader;
    std::string num;
    std::stringstream auxiliar;
    int numero;
    int posicaox = 0;
    int posicaoy = 0;
    FileReader.open(file);
    if(FileReader.is_open()){
        while(!FileReader.eof()){
            auxiliar.clear();
            getline(FileReader, num, ',');
            auxiliar << num;
            auxiliar >> numero;
            if (posicaox == 9) {
                posicaox = 0;
                posicaoy++;
            }
            if (posicaoy == 9) {
                posicaoy = 0;
            }
            matriz[posicaox][posicaoy] = numero;
            posicaox++;
        }
    }
    else{
        std::cout << "Problemas na abertura do arquivo Sudoku.txt" << '\n';
    }
}


void CarregarGrafo(){
    
}


int main(int argc, char const **argv) {

    CarregarMatriz("Sudoku.txt");
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            std::cout << matriz[i][j] << "  ";
        }
        std::cout << '\n';
    }

    return 0;
}
