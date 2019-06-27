#include <bits/stdc++.h>
#include <cstdlib>
#include <time.h> 

class vec2
{
    int x, y;
};

class victor
{
    public:
        victor(int x)
        {
            haspassed = false;
            number = x;
            saturation = 0;
        }
        int saturation;
        int number;
        bool haspassed;
        std::vector<victor *> vizinhos;
        void InsertCon(victor *vector)
        {
            vizinhos.push_back(vector);
        }
};

std::vector<std::vector<victor *>> vectors;

int matriz[9][9];

void ClearMatriz(){
    for(int i = 0;i < 9;i++){
        for(int j = 0;j < 9;j++){
            matriz[i][j] = 0;
        }
    }
}

void CarregarMatriz(std::string file)
{
    std::ifstream FileReader;
    std::string num;
    std::stringstream auxiliar;
    int numero;
    int posicaox = 0;
    int posicaoy = 0;
    FileReader.open(file);
    if (FileReader.is_open())
    {
        while (!FileReader.eof())
        {
            auxiliar.clear();
            getline(FileReader, num, ',');
            auxiliar << num;
            auxiliar >> numero;
            if (posicaox == 9)
            {
                posicaox = 0;
                posicaoy++;
            }
            if (posicaoy == 9)
            {
                posicaoy = 0;
            }
            matriz[posicaoy][posicaox] = numero;
            posicaox++;
        }
    }
    else
    {
        std::cout << "Problemas na abertura do arquivo Sudoku.txt" << '\n';
    }
}

void CarregarGrafo()
{
    for (int i = 0; i < 9; i++)
    {
        std::vector<victor *> vectorRow;
        for (int j = 0; j < 9; j++)
        {
            victor *numero = new victor(matriz[i][j]);
            vectorRow.push_back(numero);
        }
        vectors.push_back(vectorRow);
    }
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            for (int x = 0; x < 9; x++)
            {
                if (i != x)
                {
                    vectors[i][j]->InsertCon(vectors[x][j]);
                }
            }
            for (int x = 0; x < 9; x++)
            {
                if (j != x)
                {
                    vectors[i][j]->InsertCon(vectors[i][x]);
                }
            }
        }
    }
}

bool RecarregarSaturacao()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {

            vectors[i][j]->saturation = 0;
            std::vector<int> filledCollors;
            for (int z = 0; z < vectors[i][j]->vizinhos.size(); z++)
            {
                if (vectors[i][j]->number != 0)
                {
                    break;
                }
                else
                {
                    if (vectors[i][j]->vizinhos[z]->number > 0)
                    {
                        bool alreadyHasColor = false;
                        for (int x = 0; x < filledCollors.size(); x++)
                        {
                            if (filledCollors[x] == vectors[i][j]->vizinhos[z]->number)
                            {
                                alreadyHasColor = true;
                            }
                        }
                        if (!alreadyHasColor)
                        {
                            vectors[i][j]->saturation++;
                            filledCollors.push_back(vectors[i][j]->vizinhos[z]->number);
                            if (vectors[i][j]->saturation == 9)
                            {
                                vectors[i][j]->saturation = 0;
                                vectors[i][j]->number = -1;
                                return false;
                            }
                        }
                    }
                }
            }
        }
    }

    return true;
}

victor *PegarMaiorSaturacao()
{
    victor *pickedvector = vectors[0][0];
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (vectors[i][j]->number == 0)
            {
                if (pickedvector->saturation < vectors[i][j]->saturation)
                {
                    pickedvector = vectors[i][j];
                }
                else if((pickedvector->saturation == vectors[i][j]->saturation) && ((rand() % 2) == 0 )){
                    pickedvector = vectors[i][j];
                }
            }
        }
    }
    return pickedvector;
}

int AlgoritmoGuloso(victor *vector,bool backtracking = false)
{
    if (vector->number > 0){
        return -1;
    }
    else
    {
        for (int i = 1; i <= 9; i++)
        {
            bool vizinhoHasNumber = false;
            for (int j = 0; j < vector->vizinhos.size(); j++)
            {
                if (vector->vizinhos[j]->number == i)
                {
                    vizinhoHasNumber = true;
                }
            }
            if (!vizinhoHasNumber){
                vector->number = i;
                return i;
            }
        }
        
    }
}

void printMatriz()
{
    std::cout << '\n';
    std::cout << '\n';

    for (int i = 0; i < vectors.size(); i++)
    {
        for (int j = 0; j < vectors[i].size(); j++)
        {
            if((((j + 1) % 3) == 0) && ((j + 1) != vectors[i].size())){
                std::cout << vectors[i][j]->number << " | ";
            }else{
                std::cout << vectors[i][j]->number << "  ";
            }
        }
        std::cout << '\n';
        if((((i + 1) % 3) == 0) && ((i + 1) != vectors.size())){
            for (int j = 0; j < 27; j++){
                std::cout << "-";
            }
            std::cout << '\n';
        }
    }
}

void printSaturacaoMatriz()
{

    RecarregarSaturacao();
    for (int i = 0; i < vectors.size(); i++)
    {
        for (int j = 0; j < vectors[i].size(); j++)
        {
            std::cout << vectors[i][j]->saturation << "  ";
        }
        std::cout << '\n';
    }
}

bool IsGrafoPainted(){
    bool painted = true;
    for (int i = 0; i < vectors.size(); i++)
    {
        for (int j = 0; j < vectors[i].size(); j++)
        {
            if(vectors[i][j]->number == 0){
                painted = false;
            }
        }
    }
    return painted;
}

bool Dsatur()
{
    int saturation = 9;
    bool failed = false;
    while (!IsGrafoPainted())
    {   
        bool saturation9 = false;
        saturation9 = !RecarregarSaturacao();
        victor *maiorsaturacao = PegarMaiorSaturacao();
        AlgoritmoGuloso(maiorsaturacao);
        saturation = maiorsaturacao->saturation;

        if(saturation9){
            failed = true;
        }
    }

    for (int i = 0; i < vectors.size(); i++)
    {
        for (int j = 0; j < vectors[i].size(); j++)
        {
            if(vectors[i][j]->number == -1){
                vectors[i][j]->number = 0;
            }
        }
    }

    if(failed){
        // std::cout << std::endl;
        // std::cout << "DSatur has failed" << std::endl;
        return false;
    }
    else{
        // std::cout << std::endl;
        // std::cout << "DSatur has been Successfull" << std::endl;
        return true;
    }
}

void repeatDsatur(){
    bool success = false;
    int count = 0;
    while(!success && (count < 50)){
        vectors.clear();
        CarregarGrafo();
        int Seed = rand();
        srand(Seed);

        success = Dsatur();
        count++;
    }
    if(count >= 50){
        std::cout << "Matriz não é Resolvivel" << std::endl;
    }
}

void getRandomSudoku(){
    ClearMatriz();
    repeatDsatur();
}

std::vector<int> vx;
std::vector<int> vy;

bool Checkv(int x,int y, std::vector<int> v, std::vector<int> v1){
    for (int i = 0; i < v.size(); i++) {
        if (x == v[i] && y == v1[i]) {
            return true;
        }
    }
    return false;
}


void Fillwithzeros(){
    int x;
    int y;
    for (int i = 0; i < 9; i++) {
        if (i < 3) {
            int flag = rand()%3 + 5;
            for (int z = 0; z < flag; z++) {
                x = (rand()%3) + (i * 3);
                y = (rand()%3);
                while (Checkv(x, y, vx, vy)) {
                    x = (rand()%3) + (i * 3);
                    y = (rand()%3);
                }
                vx.push_back(x);
                vy.push_back(y);
                vectors[x][y]->number = 0;
            }
            vx.clear();
            vy.clear();
        }
        else{
            if (i < 6) {
                int flag = rand()%3 + 5;
                for (int z = 0; z < flag; z++) {
                    x = (rand()%3) + ((i%3) * 3);
                    y = (rand()%3) + 3;
                    while (Checkv(x, y, vx, vy)) {
                        x = (rand()%3) + ((i%3) * 3);
                        y = (rand()%3) + 3;
                    }
                    vx.push_back(x);
                    vy.push_back(y);
                    vectors[x][y]->number = 0;
                }
                vx.clear();
                vy.clear();
            }
            else{
                if (i < 9) {
                    int flag = rand()%3 + 5;
                    for (int z = 0; z < flag; z++) {
                        x = (rand()%3) + ((i%3) * 3);
                        y = (rand()%3) + 6;
                        while (Checkv(x, y, vx, vy)) {
                            x = (rand()%3) + ((i%3) * 3);
                            y = (rand()%3) + 6;
                        }
                        vx.push_back(x);
                        vy.push_back(y);
                        vectors[x][y]->number = 0;
                    }
                    vx.clear();
                    vy.clear();
                }
            }
        }
    }
}


int main(int argc, char const **argv)
{
    srand(time(NULL));
    bool matrizinicial = false;
    bool quit = false;
    while(!matrizinicial && !quit){
        std::cout << "Escolha que tipo de Sudoku inicial deseja ter:" << std::endl;
        std::cout << "1- Jogo do input no arquivo Sudoku.txt" << std::endl;
        std::cout << "2- Jogo criado aleatoriamente" << std::endl;
        std::cout << "3- Sair" << std::endl;
        std::cout << std::endl;

        std::string input;
        std::cin >> input;
        if(input == "1"){
            std::cout << "Matriz Inicial - " << std::endl;
            CarregarMatriz("Sudoku.txt");
            CarregarGrafo();
            printMatriz();
            matrizinicial = true;
        }else if(input == "2"){
            std::cout << "Matriz Inicial - " << std::endl;
            getRandomSudoku();
            Fillwithzeros();
            printMatriz();
            matrizinicial = true;
        }else if(input == "3"){
            quit = true;
            std::cout << "Saindo" << std::endl << std::endl; 
        }else{
            std::cout << "Nenhuma Matriz Escolhida" << std::endl << std::endl; 
        }

    }
    if(matrizinicial){
        int count = 1;
        bool finish = false;
        std::cout << "Matriz Final - " << count << std::endl;
        repeatDsatur();
        printMatriz();
        while(!finish){
            std::cout << std::endl;
            std::cout << "Digite 1 para ter outro resultado ou 2 para sair" << std::endl;
            std::string input2;
            std::cin >> input2;
            if(input2 == "1"){
                count ++;
                std::cout << "Matriz Final - " << count << std::endl;
                repeatDsatur();
                printMatriz();
            }else if(input2 == "2"){
                std::cout << "Saindo" << std::endl;
                finish = true;
            }
        }
    }

    return 0;
}