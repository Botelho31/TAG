#include <bits/stdc++.h>
#include <cstdlib>
#include <time.h> 

//Vertice do grafo
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
std::stringstream logcontent;

int matriz[9][9];

//Insere o log do programa no arquivo log.txt
void Log(std::string log,bool finishline = true){
    if(finishline){
        logcontent << log << "\n";
        std::cout << log << std::endl;
    }else{
        logcontent << log;
        std::cout << log;
    }
}

void SaveLog(){
    std::ofstream logfile;
    logfile.open("log.txt");
    logfile << logcontent.str();
    logfile.close();
}

//Limpa a matriz
void ClearMatriz(){
    for(int i = 0;i < 9;i++){
        for(int j = 0;j < 9;j++){
            matriz[i][j] = 0;
        }
    }
}

//Carrega a matriz de um txt no formato especificado no Readme
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

//Preenche o grafo e suas conexoes com todos da mesma fileira e coluna
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

//Recarrega os indices de saturação do grafo
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

//Pega o vertice de maior saturação, resolvendo conflitos onde a saturação é igual de forma aleatoria
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

//Algoritmo Guloso
int AlgoritmoGuloso(victor *vector)
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

//Printa a matriz no formato de Sudoku
void printMatriz()
{
    std::stringstream matriz;
    std::cout << std::endl;
    std::cout << std::endl;
    matriz << "\n";
    matriz << "\n";

    for (int i = 0; i < vectors.size(); i++)
    {
        for (int j = 0; j < vectors[i].size(); j++)
        {
            if((((j + 1) % 3) == 0) && ((j + 1) != vectors[i].size())){
                std::stringstream line;
                line << vectors[i][j]->number << " | ";
                line.str().pop_back();
                matriz << line.str();
                std::cout << line.str();
            }else{
                std::stringstream line;
                line << vectors[i][j]->number << " ";
                line.str().pop_back();
                matriz << line.str();
                std::cout << line.str();
            }
        }
        matriz << "\n";
        std::cout << std::endl;
        if((((i + 1) % 3) == 0) && ((i + 1) != vectors.size())){
            for (int j = 0; j < 24; j++){
                matriz << "-";
                std::cout << "-";
            }
            matriz << "\n";
            std::cout << std::endl;
        }
    }
    matriz << "\n";
    std::cout << std::endl;
    logcontent << matriz.str();
}

//Printa a saturação da matriz por ponto
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

//Ve se o grafo ja esta completamente preenchido
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

//Usa o algoritmo Guloso baseado na ordem de maior saturação
bool Dsatur(bool print = false)
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
        if(print){
            printMatriz();
        }

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
        if(print){
            Log("\n --DSatur has failed--");
        }
        return false;
    }
    else{
        if(print){
            Log("\n --DSatur has been successfull--");
        }
        return true;
    }
}

//Repete o algortimo de Dsatur com randomização diferente a cada tentativa na soluçaõ de conflito
void repeatDsatur(bool print = false){
    bool success = false;
    int count = 0;
    while(!success && (count < 50)){
        vectors.clear();
        CarregarGrafo();
        int Seed = rand();
        srand(Seed);
        if(print){
            std::stringstream print;
            print <<  "\nTentativa Numero - " << count;
            Log(print.str());
        }
        success = Dsatur(print); 
        count++;
    }
    if(count >= 50){
        Log("Matriz não é Resolvivel com 50 tentativas");
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

//Enche uma matriz cheia de numeros com zeros aleatoriamente
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
        Log("Escolha que tipo de Sudoku inicial deseja ter:");
        Log("1- Jogo do input no arquivo Sudoku.txt");
        Log("2- Jogo criado aleatoriamente");
        Log("3- Sair\n");
        std::string input;
        std::cin >> input;
        Log(input);
        if(input == "1"){
            Log("Matriz Inicial: ");
            CarregarMatriz("Sudoku.txt");
            CarregarGrafo();
            printMatriz();
            matrizinicial = true;
        }else if(input == "2"){
             Log("Matriz Inicial: ");
            getRandomSudoku();
            Fillwithzeros();
            printMatriz();
            matrizinicial = true;
        }else if(input == "3"){
            quit = true;
             Log("Saindo\n");
        }else{
            Log("Nenhuma Matriz Escolhida\n");
        }

    }
    if(matrizinicial){

        Log("Essa é a matriz inicial digite qualquer coisa e aperte enter para resolve-la:");
        std::string input3;
        std::cin >> input3;
        int count = 1;
        bool finish = false;
        std::cout << std::endl;
        repeatDsatur(true);
        while(!finish){
            std::cout << std::endl;
            Log("Digite 1 para ter outro resultado ou 2 para sair");
            std::string input2;
            std::cin >> input2;
            Log(input2);
            if(input2 == "1"){
                count ++;
                Log("Matriz Final - " + count);
                repeatDsatur(true);
            }else if(input2 == "2"){
                Log("Saindo");
                finish = true;
            }
        }
    }

    SaveLog();
    return 0;
}