#include <bits/stdc++.h>
#include <cstdlib>

class vec2{
    int x,y;
};

class victor{
    public:
        victor(int x){
            haspassed = false;
            number = x;
        }
        int number;
        bool haspassed;
        std::vector<int> vizinhos;
        void InsertCon(int x){
            vizinhos.push_back(x);
        }
};

std::vector<victor*> vectors;

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
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            victor *numero = new victor(matriz[i][j]);
            for (int x = 0; x < 9; x++) {
                if (i != x) {
                    numero->InsertCon(matriz[x][j]);
                }
            }
            for (int x = 0; x < 9; x++) {
                if (j != x) {
                    numero->InsertCon(matriz[i][x]);
                }
            }
            vectors.push_back(numero);
        }
    }
}

void AlgoritmoGuloso(victor *vector){
    if(vector->number > 0){
        return;
    }else{
        for(int i = 1;i <= 9;i++){
            bool vizinhoHasNumber = false;
            for(int j = 0;j < vector->vizinhos.size();j++){
                if(vector->vizinhos[j] == i){
                    vizinhoHasNumber = true;
                    break;
                }
            }
            if(!vizinhoHasNumber){
                vector->number = i;
                return;
            }
        }
    }
}


int main(int argc, char const **argv) {

    CarregarMatriz("Sudoku.txt");
    CarregarGrafo();

    for(int i = 0;i < vectors.size();i++){
        AlgoritmoGuloso(vectors[i]);
    }
    for (int i = 0; i < vectors.size(); i++) {
        std::cout << vectors[i]->number << "  ";
        if(((i + 1) % 9) == 0){
            std::cout << '\n';
        }
    }

    std::cout << '\n';
    std::cout << '\n';
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            std::cout << matriz[i][j] << "  ";
        }
        std::cout << '\n';
    }

    return 0;
}