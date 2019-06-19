#include <bits/stdc++.h>
#include <cstdlib>

int matriz[9][9];

using namespace std;
int main() {
    Load("Sudoku.txt")

    for (int i = 0; i < 9; i++) {
        for (int i = 0; i < 9; i++) {
            std::cout << matriz[9][9] << '\n';
        }
    }

    return 0;
}

void Load (string file) {
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
            // std::cout << numero << '\n';
            if (posicaox == 9) {
                posicaox = 0;
            }
            if (posicaoy == 9) {
                posicaoy = 0;
            }
            matriz[posicaox][posicaoy] = numero;
        }
    }
    else{
      std::cout << "Problemas na abertura do arquivo Sudoku.txt" << '\n';
    }
}
