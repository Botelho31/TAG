#include <bits/stdc++.h>

using namespace std;

vector<int> grafo[50];
map<int,vector<int> > vertices; //


void ClearGrafo(){
    for(int i = 0; i < 50;i++ ){
        for(int j = 0;j < 50;j++){
            grafo[i].push_back(0);
        }
    }
}
void Read(std::string file){
    ClearGrafo();   //Seta o grafo pra 0
    fstream FileReader;
    FileReader.open(file.c_str());
    string checkline;
    int num = 0;
    if (FileReader.is_open()) {
        while (!FileReader.eof()) {
            FileReader >> checkline;    //Checa as palavras do grafo
            if(checkline == "node"){        //se for igual a node entra e espera checar em ID
                while(checkline != "id"){
                    FileReader >> checkline;
                }   
                FileReader >> num;      //Quando chega em ID ele pega o numero do ID e armazena no map com um vector vazio
                vector<int> start;
                start.clear();
                vertices.insert({num,start});

            }
            else if( checkline == "edge"){  //se for igual a edge para e espera chegar em source
                while(checkline != "source"){
                    FileReader >> checkline;
                }
                int source;
                int destiny;    //Quando chega em source ele pega o numero de source
                FileReader >> source;
                FileReader >> checkline; //Quando chega em destiny ele pega o numero de destiny
                FileReader >> destiny;
                vertices[source].push_back(destiny);    //Insere a adjacencia ao vertice
                vertices[destiny].push_back(source);

                grafo[source][destiny] = 1;     //Insere a adjacencia na matriz de adjacencia
                grafo[destiny][source] = 1;
            }
        }
    }else{
        cout << "Error reading File: " << file << endl; //Printa um erro caso nao consiga dar load na file
    }
    FileReader.close();
}

void ImprimirMatrizAdjacencias(){   //Imprime a matriz de adjacencias
    for(int i = 1;i < vertices.size();i++){
        cout  << i << " - ";
        for(int j = 0;j < vertices.size();j++){
            cout << grafo[i][j] << " ";
        }
        cout << endl;
    }
}

void ImprimirAdjacencias(){     //Imprime a lista de adjacencias
    cout << "List de Adjacencias: " << endl;
    for(int i = 1;i <= vertices.size();i++){
        cout << "Vertice: " << i << endl;
        cout << "  ";
        for(int j = 0;j < vertices[i].size();j++){
            cout << vertices[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void ImprimirGraus(){       //Imprime o grau de cada vetor
    cout << "Graus Dos Vetores: " << endl;
    for(int i = 1;i <= vertices.size();i++){
        cout << "Vertice: " << i;
        cout << "  Grau: ";
        int grau = 0;
        for(int j = 0;j < vertices[i].size();j++){
            grau ++;
        }
        cout << grau << endl;
    }
    cout << endl;
}

//funcao para achar o coeficente de aglomeracao de um vertice num e retorna-lo
double CoeficienteAglomeracao(int num){\
    double coeficente;
    int quantidadedevizinho = 0;
    double triangulo = 0;
    vector<int> v = vertices[num];
    //iguala flag com o numero de adjacencia (vizinhos de num)
    quantidadedevizinho = v.size();
    // std::cout << quantidadedevizinho << '\n';
    //dois loops para achar 2 numeros adjacentes no mesmo vertice e ver se eles possuem uma ligacao entre si
    for (int i = 0; i < quantidadedevizinho; i++) {
        int v1=v[i];
        for (int j = 0; j < quantidadedevizinho; j++) {
            //Se i for igual a j, quer dizer q sao o mesmo vertice entao j eh iterado.
            int v2=v[j];

            //for para percorrer o vertice adjacente e ver se ele possui um adjacente em comum c num
            for (int x = 0; x < vertices[v1].size(); x++) {
                //verifica se o triangulo foi formado
                if(v2 == vertices[v1][x]){
                    //note que o mesmo triangulo sempre eh contado 2 vezes e isso sera compensado no final
                    triangulo += 0.5;
                }
            }
        }
    }

    // std::cout << triangulo << '\n';
    // std::cout << '\n';
    //equacao do coeficente eh 2 vezes o numero de triangulos dividido por o numero de adjacentes vezes o numero de adjacentes menos 1, se o numero de vizinhos for maior q 1
    if(quantidadedevizinho>1){
        coeficente = (2*triangulo)/(quantidadedevizinho*(quantidadedevizinho-1));
    }
    else {
        coeficente = 0.0;
    }
    // std::cout << '\n';

    //se ele so tiver um vizinho nao pode fazer divisao por 0
    return coeficente;
}
//Funcao que acha a media de todos os coeficentes de aglomeracao do grafo
double mediaCoeficienteAglomeracao(){
    double total=0.0;
    double media;
    //soma todos os indices de aglomeracao de todos os vertices do grafo em uma variavel
    for (int i = 1; i < 35; i++) {
        total += CoeficienteAglomeracao(i);
    }

    std::cout << "Total dos coeficente ";
    std::cout << total << '\n';

    //a media eh a soma de todos dividido pelo numero de vertices
    media = total/34;

    return media;
}


//Começa logica dos cliques
vector<vector<int>> cliquesmax;

void GetCliques(vector<int> r,vector<int> p,vector<int> x){     //função do algoritmo bron-kerbosch
    if(p.empty() && x.empty()){     //se p e x estiverem vazios insere R na lista de cliques
        cliquesmax.push_back(r);

    }
    if((p.empty()) && (!x.empty())){    //se p estiver vazio mas x não, realiza backtracking
        return;
    }

    map<int,bool> pmem,xmem;
    for(int i = 0;i <= vertices.size();i++){    //inicia uma copia da lista de p e x no formato de map
        pmem[i] = false;                        //pois não se pode modificar a que estamos percorrendo
        pmem[i] = false; 
    }
    for (int i = 0;i < p.size();i++){
        pmem[p[i]] = true;
    }
    for (int i = 0;i < x.size();i++){
        xmem[x[i]] = true;
    }
    
    for(int i = 0;i < p.size();i++){
        r.push_back(p[i]);      //insere o novo vertice em R

        vector<int> pprox,xprox;        

        for(int j = 0;j < vertices[p[i]].size();j++){   
            if(pmem[vertices[p[i]][j]]){        //insere a interceção dos vizinhos do vertice com p em p
                pprox.push_back(vertices[p[i]][j]);
            }
            if(xmem[vertices[p[i]][j]]){        //insere a interceção dos vizinhos do vertice com x em x
                xprox.push_back(vertices[p[i]][j]);
            }
        }

        GetCliques(r,pprox,xprox);      //faz uma chamada recursiva com os novos dados
        
        r.pop_back();       //remove o vertice que ja foi checado

        pmem[p[i]] = false;     // remove o vertice de P e o insere em X

        xmem[p[i]] = true;
            
    }
}

void cliquemax(){   //função que inicia e printa os cliques maximais
    vector<int> verticesR;
    vector<int> verticesP;
    vector<int> verticesX;


    for(int i = 1;i <= vertices.size();i++){        //adiciona todos os vertices em p
        verticesP.push_back(i);
    }
    GetCliques(verticesR,verticesP,verticesX);  //chama a função do algoritmo bron-kerbosch

    std::cout << "Lista dos cliques maximais: " << std::endl;
    for(int i = 0;i < cliquesmax.size();i++){   //imprime a lista de cliques maximais
        std::cout << i + 1 << " - ";
        for(int j = 0;j < cliquesmax[i].size();j++){
            std::cout << cliquesmax[i][j] << " ";
        }
        std::cout  << std::endl;
    }
    std::cout  << std::endl;


}
//Acaba logica dos cliques

int main(void){
    Read("karate.gml");

    for (int i = 1; i < 35; i++) {
        printf("Vertice -%d Coeficiente de Aglomeracao -%lf\n", i , CoeficienteAglomeracao(i));
    }
    printf("Media dos Coeficientes: %lf\n", mediaCoeficienteAglomeracao());
    std::cout << std::endl;
    ImprimirGraus();
    ImprimirAdjacencias();
    cliquemax();
    return 0;
}
  