#include <bits/stdc++.h>
#include <cstdlib>

class vec2{
    int x,y;
};

class vector{
    int number;
    bool haspassed;
    std::vector<int> vizinhos;
};

std::vector<vector> vectors;

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

void AlgoritmoGuloso(int x,int y){
    // if(matriz[x][y] > 0){
    //     return;
    // }else{
    //     std::vector<int> vizinhos;
    //     if(x > 0){
    //         vizinhos.push_back(matriz[x - 1][y]);
    //     }
    //     if(x < 8){
    //         vizinhos.push_back(matriz[x + 1][y]);
    //     }
    //     if(y > 0){
    //         vizinhos.push_back(matriz[x][y - 1]);
    //     }
    //     if(y < 9){
    //         vizinhos.push_back(matriz[x + 1][y + 1]);
    //     }
    //     for(int i = 1;i <= 9;i++){
    //         bool vizinhoHasNumber = false;
    //         for(int j = 0;j < vizinhos.size();i++){
    //             if(vizinhos[j] == i){
    //                 vizinhoHasNumber = true;
    //                 break;
    //             }
    //         }
    //         if(!vizinhoHasNumber){
    //             matriz[x][y] = i;
    //             break;
    //         }
    //     }
    //     if(x > 0){
    //         AlgoritmoGuloso(x - 1,y);
    //     }
    //     if(x < 8){
    //         AlgoritmoGuloso(x + 1,y);
    //     }
    //     if(y > 0){
    //         AlgoritmoGuloso(x,y - 1);
    //     }
    //     if(y < 9){
    //         AlgoritmoGuloso(x ,y + 1);
    //     }
    // }
}


int main(int argc, char const **argv) {

    CarregarMatriz("Sudoku.txt");
    // AlgoritmoGuloso(1,0);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            std::cout << matriz[i][j] << "  ";
        }
        std::cout << '\n';
    }

    return 0;
}
