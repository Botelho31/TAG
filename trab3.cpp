#include <bits/stdc++.h>
#include <cstdlib>

using namespace std;

class Professor{
    public:
        Professor(int habilitacao,vector<int> escolas){
            this->habilitacao = habilitacao;
            this->escolas = escolas;
        }
        int habilitacao;
        vector<int> escolas;
};

class Escola{
    public:
        Escola(int escola,vector<int> habilitacaopretendidas){
            this->escola = escola;
            this->habilitacaopretendidas = habilitacaopretendidas;
        }
        int escola;
        vector<int> habilitacaopretendidas;
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

    for(int i = 0;i < professores.size();i++){
        cout << professores[i].habilitacao << endl;
        cout << "\t";
        for(int j = 0;j < professores[i].escolas.size();j++){
            cout << professores[i].escolas[j] << " ";
        }
        cout << endl;
    }
    for(int i = 0;i < escolas.size();i++){
        cout << escolas[i].escola << endl;
        cout << "\t";
        for(int j = 0;j < escolas[i].habilitacaopretendidas.size();j++){
            cout << escolas[i].habilitacaopretendidas[j] << " ";
        }
        cout << endl;
    }
}





int main(void){
    Read("professores.txt");

    return 0;
}
  