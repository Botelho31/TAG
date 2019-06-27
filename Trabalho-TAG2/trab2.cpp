#include <bits/stdc++.h>
#include <cstdlib>

using namespace std;

class Materia{
    public:
    Materia(int id,string nome,int peso){
        this->id = id;
        this->nome = nome;
        this->peso = peso;
        this->countapontada = 0;
    }
    void InsertCon(Materia* materia){
        conexoes.push_back(materia);
    }
    int id;
    string nome;
    int peso;
    int countapontada;
    vector<Materia*> conexoes;
};

map<int,Materia*> vertice;
vector<Materia*> verticesenumerados;

void Read(std::string file){
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
                int id;
                string nome;
                int peso;

                FileReader >> id;      //Quando chega em ID ele pega o numero do ID e armazena no map com um vector vazio
                FileReader >> nome;
                FileReader >> peso;
                Materia *materia = new Materia(id,nome,peso);
                vertice.insert({id,materia});
                // if(peso != 0){
                    verticesenumerados.push_back(materia);
                // }
                num ++;
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
                vertice[source]->InsertCon(vertice[destiny]);
                vertice[destiny]->countapontada += 1;
            }
        }
    }else{
        cout << "Error reading File: " << file << endl; //Printa um erro caso nao consiga dar load na file
    }
    FileReader.close();
}

void ImprimirAdjacencias(){     //Imprime a lista de adjacencias
   for(int i = 0;i < verticesenumerados.size();i ++){
        std::cout << "Numero: " << i+1 << std::endl;
        std::cout << "ID: " << verticesenumerados[i]->id << " NOME: " << verticesenumerados[i]->nome << std::endl;
        for(int j = 0;j < verticesenumerados[i]->conexoes.size();j++){
            std::cout << "-> ID: " << verticesenumerados[i]->conexoes[j]->id << " NOME: " << verticesenumerados[i]->conexoes[j]->nome << std::endl;
        }
        std::cout << std::endl;
    }
}

void ImprimirGraus(){       //Imprime o grau de cada vetor
    for(int i = 0;i < verticesenumerados.size();i ++){
        std::cout << "Numero: " << i+1 << std::endl;
        std::cout << "ID: " << verticesenumerados[i]->id << std::endl;
        std::cout << "NOME: " << verticesenumerados[i]->nome << std::endl;
        std::cout << "PESO: " << verticesenumerados[i]->peso << std::endl;
        std::cout << "INDO PRA ELE: " << verticesenumerados[i]->countapontada << std::endl;
        std::cout << "GRAU: " << verticesenumerados[i]->conexoes.size() << std::endl;
        std::cout << std::endl;
    }
}

void GerarGrafoPng(vector<Materia*> materias){
    ofstream myfile;
    myfile.open ("grafo.dot");
    myfile << "digraph {\n";
    for(int i = 0;i < materias.size();i++){
        for(int j = 0;j < materias[i]->conexoes.size();j ++){
            myfile << "\t" << materias[i]->id << " -> " << materias[i]->conexoes[j]->id << " [label = " << materias[i]->peso << "];\n";
        }
    }
    myfile << "}\n";
    myfile.close();
    system("dot -Tpng spider.dot -o spider.png");
}

void GerarGrafoCriticoPng(vector<Materia*> materias,map<int,int> caminhoCritico,vector<int> sourcesCaminhoCritico){
    ofstream myfile;
    myfile.open ("grafo.dot");
    myfile << "digraph {\n";
    for(int i = 0;i < materias.size();i++){
        for(int j = 0;j < materias[i]->conexoes.size();j ++){
            for(int x = 0;x < sourcesCaminhoCritico.size();x ++){
                if(sourcesCaminhoCritico[x] == materias[i]->id){
                    caminhoCritico[materias[i]->id] 
                }
            }
            myfile << "\t" << materias[i]->id << " -> " << materias[i]->conexoes[j]->id << " [label = " << materias[i]->peso << "];\n";
        }
    }
    myfile << "}\n";
    myfile.close();
}

vector<Materia*> OrganizacaoTopologica(){
    //verifica vertices com 0 entradas
    queue<Materia*> fila;
    queue<Materia*> filafinal;
    int contadordevertices = 0;
    for (int i = 0; i < verticesenumerados.size(); i++) {
        if(verticesenumerados[i]->countapontada == 0){
            fila.push(verticesenumerados[i]);
        }
    }
    while(!fila.empty()){
        contadordevertices++;
        if(fila.front()->conexoes.size() != 0){
            for (int i = 0; i < fila.front()->conexoes.size(); i++) {
                fila.front()->conexoes[i]->countapontada--;
                if(fila.front()->conexoes[i]->countapontada == 0){
                    fila.push(fila.front()->conexoes[i]);
                }
            }
        }
        filafinal.push(fila.front());
        fila.pop();
    }
    if(contadordevertices == verticesenumerados.size()){
        cout << "O vertice pode ser Ordenado Topologicamente" << '\n';
    }
    vector<Materia*> vecordenado;
    for(int i = (filafinal.size() - 1);i > 0;i--){
        vecordenado.push_back(filafinal.front());
        filafinal.pop();
    }
    return vecordenado;

}




int main(void){
    Read("materias.gml");

    //Gera o grafo original não ordenado
    GerarGrafoPng(verticesenumerados);
    system("dot -Tpng grafo.dot -o grafoNaoOrd.png");

    //Gera o grafo ordenado topologicamente
    vector<Materia*> filaordenada = OrganizacaoTopologica();
    GerarGrafoPng(filaordenada);
    system("dot -Tpng grafo.dot -o grafoOrd.png");

    //Gera o Caminho Critico topologicamente

    //Gera a fila de ordenação topologica
    for(int i = 0;i < filaordenada.size();i++){
        if( (i + 1) < filaordenada.size()){
            bool found = false;
            for(int j = 0;j < filaordenada[i]->conexoes.size();j++){
                if(filaordenada[i]->conexoes[j]->id == filaordenada[i + 1]->id){
                    filaordenada[i]->conexoes.clear();
                    filaordenada[i]->InsertCon(filaordenada[i + 1]);
                    found = true;
                }
            }
            if(!found){
                filaordenada[i]->conexoes.clear();
            }
        }
    }
    GerarGrafoPng(filaordenada);
    system("dot -Tpng grafo.dot -o filaDeOrd.png");
    return 0;
}
  