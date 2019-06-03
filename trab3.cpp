#include <bits/stdc++.h>
#include <cstdlib>

using namespace std;

class Professor{
    public:
        Professor(int habilitacao,vector<int> escolas){
            this->habilitacao = habilitacao;
            this->escolas = escolas;
            this->matched = false;
            this->emparelhado = 999;
            this->proposicoes = 0;
        }
        int habilitacao;
        vector<int> escolas;
        //Verifica se o professor ainda esta livro ou nao
        bool matched;
        //referente a qual escola o professor vai trabalhar
        int emparelhado;
        //proposicoes indica quantas escolas os professores ja aplicaram
        int proposicoes;
};

class Escola{
    public:
        Escola(int escola,vector<int> habilitacaopretendidas){
            this->escola = escola;
            this->habilitacaopretendidas = habilitacaopretendidas;
            for (int i = 0; i < habilitacaopretendidas.size(); i++) {
                matched.push_back(false);
                //o numero 999 eh um numero absurdo que eh tratado como se a escola nao tivesse vinculado a ninguem
                emparelhado.push_back(999);
            }

        }
        int escola;
        vector<int> habilitacaopretendidas;
        //referemte se ja foi emparelhado ou nao
        vector<bool> matched;
        //referente a qual professor foi emparelhado com essa escola
        vector<int> emparelhado;
};

vector<Professor> professores;
vector<Escola> escolas;

bool IsNumber(char number){
    switch(number){
        case'0':
            break;
        case'1':
            break;
        case'2':
            break;
        case'3':
            break;
        case'4':
            break;
        case'5':
            break;
        case'6':
            break;
        case'7':
            break;
        case'8':
            break;
        case'9':
            break;
        default:
            return false;
            break;
    }
    return true;
}

string ParseParenthesis(string checkline,vector<int> &intnumbers){
    stringstream Parser,ParenthesisParser;
    ParenthesisParser << checkline;
    getline(ParenthesisParser,checkline,'(');
    getline(ParenthesisParser,checkline,')');
    Parser << checkline;
    while(!Parser.eof()){
        getline(Parser,checkline,'\n');
        int iterator = 0;
        vector<stringstream> numbers;
        numbers.push_back(std::stringstream());
        for(char& c : checkline) {
            if(IsNumber(c)){
                numbers[iterator] << c;
            }
            if(c == ','){
                iterator ++;
                numbers.push_back(std::stringstream());
            }
        }
        for(int i = 0; i < numbers.size();i++){
            int a = -1;
            numbers[i] >> a;
            if(a >= 0){
                intnumbers.push_back(a);
            }
        }
    }
    return checkline;
}

void Read(std::string file){
    fstream FileReader;
    stringstream ParenthesisParser;
    FileReader.open(file.c_str());
    string checkline;
    int num = 0;
    bool escolastarted = false;
    if (FileReader.is_open()) {
        while (!FileReader.eof() && !escolastarted) {
            vector<int> Prof;
            vector<int> EscolasOrdenadas;
            getline(FileReader,checkline,':');
            if(ParseParenthesis(checkline,Prof) == "Escolas"){
                escolastarted = true;
            }
            getline(FileReader,checkline,'\n');
            ParseParenthesis(checkline,EscolasOrdenadas);

            if(!Prof.empty()){
                Professor professor = Professor(Prof[1],EscolasOrdenadas);
                professores.push_back(professor);
            }
        }
        while(!FileReader.eof()){
            vector<int> EscolaPars;
            vector<int> Habilitacao;
            getline(FileReader,checkline,':');
            ParseParenthesis(checkline,EscolaPars);
            getline(FileReader,checkline,'\n');
            if(checkline.size() > 4){
                stringstream Parser;
                Parser << checkline;
                getline(Parser,checkline,':');
                ParseParenthesis(checkline,Habilitacao);
                getline(Parser,checkline,'\n');
                ParseParenthesis(checkline,Habilitacao);
            }else{
                ParseParenthesis(checkline,Habilitacao);
            }
            if(!EscolaPars.empty()){
                Escola escola = Escola(EscolaPars[0],Habilitacao);
                escolas.push_back(escola);
            }
        }
    }else{
        cout << "Error reading File: " << file << endl; //Printa um erro caso nao consiga dar load na file
    }
    FileReader.close();
}

void PrintProfessores(){
    for(int i = 0;i < professores.size();i++){
        cout << "Professor Numero: " << i << endl;
        cout << "\t Habilitacao: "<< professores[i].habilitacao << endl;
        cout << "\t Escolas Pretendidas: ";
        for(int j = 0;j < professores[i].escolas.size();j++){
            cout << professores[i].escolas[j] << " ";
        }
        cout << "\t Professor esta livre: " << professores[i].matched;
        cout << endl;
        cout << endl;
    }
}

void PrintEscolas(){
    for(int i = 0;i < escolas.size();i++){
        cout << "Escola Numero: "<< escolas[i].escola << endl;
        cout << "\tHabilitacoes Pretendidas: ";
        for(int j = 0;j < escolas[i].habilitacaopretendidas.size();j++){
            cout << escolas[i].habilitacaopretendidas[j] << " ";
            cout << "Vaga esta livre:" <<escolas[i].matched[j] << " ";
        }
        cout << endl;
        cout << endl;
    }
}
//verifica se as escolas podem ainda ser mexidas
bool VerificaProfessor(){
    int flag = 0;
    for (int i = 0; i < professores.size(); i++) {
        if(!(professores[i].matched) && (professores[i].proposicoes != 50)){
            flag++;
        }
    }
    if (flag != 0) {
        //se existir alguma escola livre e que nao tenha proposto trabalho para todos os professores, retorne verdadeiro
        return true;
    }
    //caso contrario retorne falso
    return false;
}

//escolhe um professor que ainda esta livro e que nao pediu para trabalhar em todas as escolas
int EscolheProfessor(){
    for (int i = 0; i < professores.size(); i++) {
        if(!(professores[i].matched) && (professores[i].proposicoes != 50)){
            return i;
        }
    }
    return 999;
}

//verifica a prioridade das escolas nos professores
int GetNiveldePreferencia(Professor prof, int preferencia){
    for (int x = 0; x < prof.escolas.size(); x++) {
        if(prof.escolas[x] == preferencia){
            return x;
        }
    }
}

//faz os Emparelhamento
void Emparelhamento(){
    //verifica se tem professores livres ainda
    while (VerificaProfessor()) {
        //escolhe um professore livre e que nao tenha pedido pra todas as escolas
        int i = EscolheProfessor();
        professores[i].proposicoes++;
        for (int j = 0; j < professores[i].escolas.size(); j++) {
            for (int x = 0; x < escolas[professores[i].escolas[j]].habilitacaopretendidas.size(); x++) {
                //se a escola n for escolhida ainda e a escola tiver interesse na habilidade do profesor ele entra nesse if
                if (!(escolas[professores[i].escolas[j]].matched[x]) && escolas[professores[i].escolas[j]].habilitacaopretendidas[x] == professores[i].habilitacao) {
                    professores[i].emparelhado = professores[i].escolas[j];
                    professores[i].matched = true;
                    escolas[professores[i].escolas[j]].matched[x] = true;
                    escolas[professores[i].escolas[j]].emparelhado[x] = i;
                }
                //verifica se a escola ja foi escolhida e verifica se a preferencia do match anterior eh maior que a preferencia do professor atual, nesse caso entra nesse if
                //Botelho da uma verificada nesse if, pq tem chance de dar alguma merda com relacao a isso pq, talvez, nem sempre eh pra tu ignorar o fato se ja deu match (isso nao eh ctz, so estou confabulando)
                else if(escolas[professores[i].escolas[j]].matched[x] && (GetNiveldePreferencia(professores[i], professores[i].escolas[j]) < GetNiveldePreferencia(professores[escolas[j].emparelhado[x]], professores[i].escolas[j]))){
                    professores[i].emparelhado = professores[i].escolas[j];
                    professores[i].matched = true;
                    escolas[professores[i].escolas[j]].emparelhado[x] = i;
                    professores[escolas[j].emparelhado[x]].emparelhado = 999;
                    professores[escolas[j].emparelhado[x]].matched = false;
                }
            }
        }
    }
}


int main(void){
    Read("professores.txt");
    PrintProfessores();
    PrintEscolas();
    return 0;
}
