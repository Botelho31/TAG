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
            saturation = 0;
        }
        int saturation;
        int number;
        bool haspassed;
        std::vector<victor*> vizinhos;
        void InsertCon(victor *vector){
            vizinhos.push_back(vector);
        }
};

std::vector<std::vector<victor*>> vectors;

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
        std::vector<victor*> vectorRow;
        for (int j = 0; j < 9; j++) {
            victor *numero = new victor(matriz[i][j]);
            vectorRow.push_back(numero);
        }
        vectors.push_back(vectorRow);
    }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            for (int x = 0; x < 9; x++) {
                if (i != x) {
                    vectors[i][j]->InsertCon(vectors[x][j]);
                }
            }
            for (int x = 0; x < 9; x++) {
                if (j != x) {
                    vectors[i][j]->InsertCon(vectors[i][x]);
                }
            }
        }
    }
}

void RecarregarSaturacao(){
    for(int i = 1;i < 9;i++){
        for(int j = 0;j < 9;j++){

            vectors[i][j]->saturation = 0;
            std::vector<int> filledCollors;
            for(int z = 0;z < vectors[i][j]->vizinhos.size();z++){
                if(vectors[i][j]->number != 0){
                    break;
                }else{
                    if(vectors[i][j]->vizinhos[z]->number > 0){
                        bool alreadyHasColor = false;
                        for(int x = 0;x < filledCollors.size();x++){
                            if(filledCollors[x] == vectors[i][j]->vizinhos[z]->number){
                                alreadyHasColor = true;
                            }
                        }
                        if(!alreadyHasColor){
                            vectors[i][j]->saturation ++;
                            filledCollors.push_back(vectors[i][j]->vizinhos[z]->number);
                            if(vectors[i][j]->saturation == 9){
                                vectors[i][j]->saturation = 0;
                                vectors[i][j]->number = -1;
                            }
                        }
                    }
                }
            }
        }
    }
}

victor* PegarMaiorSaturacao(){
    victor* pickedvector  = vectors[0][0];
    for(int i = 0;i < 9;i++){
        for(int j = 0;j < 9;j++){
            if(vectors[i][j]->number == 0){
                if(pickedvector->saturation < vectors[i][j]->saturation){
                    pickedvector = vectors[i][j];
                    std::cout << i << " " << j << std::endl;
                    std::cout << pickedvector->saturation << std::endl;
                    std::cout << pickedvector->number << std::endl;
                }
            }
        }
    }
    return pickedvector;
}

void AlgoritmoGuloso(victor *vector){
    if(vector->number > 0){
        return;
    }else{
        for(int i = 1;i <= 9;i++){
            bool vizinhoHasNumber = false;
            for(int j = 0;j < vector->vizinhos.size();j++){
                if(vector->vizinhos[j]->number == i){
                    vizinhoHasNumber = true;
                }
            }
            if(!vizinhoHasNumber){
                vector->number = i;
                return;
            }
        }
    }
}

void printMatriz(){
    std::cout << '\n';
    std::cout << '\n';

    for(int i = 0;i < vectors.size();i++){
        for(int j = 0;j < vectors[i].size();j++){
            std::cout << vectors[i][j]->number << "  ";
        }
        std::cout << '\n';
    }
}

void printSaturacaoMatriz(){
    
    for(int i = 0;i < vectors.size();i++){
        for(int j = 0;j < vectors[i].size();j++){
            std::cout << vectors[i][j]->saturation << "  ";
        }
        std::cout << '\n';
    }
}


int main(int argc, char const **argv) {

    CarregarMatriz("Sudoku.txt");
    CarregarGrafo();

    RecarregarSaturacao();
    printSaturacaoMatriz();
    for(int x = 0;x < 2000;x ++){
        RecarregarSaturacao();
        AlgoritmoGuloso(PegarMaiorSaturacao());
    }
    printMatriz();

    return 0;
}