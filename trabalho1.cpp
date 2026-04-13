#include<iostream>
#include<string>
#include<fstream>
#include<list>
using namespace std;

//Função para remover partes da lista
string retiraParte(string &textoInicial, int posInicio, int tamanho){
    string final = "";

    for(int i = posInicio; i < tamanho + posInicio; i++){
        final += textoInicial[i];
    }
    return final;
}


int main(){
    
    ifstream arquivo;
    arquivo.open("arquivo.txt");
    
    string nome;
    list <string> listaArq;
    

    if(!arquivo.is_open()){
        cerr << "Erro ao abrir o arquivo" << endl;
        return 1;
    }

    //Passa os nomes do arquivo para uma lista
    while(getline(arquivo,nome)){

        if(!nome.empty() && nome.back() == '\r') nome.pop_back();

        int tamanhoLinha = nome.length();
        int inicioDatas = tamanhoLinha - 18;
        
        //Separa o nome das datas
        string nomeSozinho = retiraParte(nome, 0, inicioDatas);
        string data[3];

        //Remove as datas e organiza em YY/MM/DD
        for(int i = 0; i < 3; i++){
            int posicao = inicioDatas + (i * 6);
            string dia = retiraParte(nome,posicao,2); 
            string mes = retiraParte(nome,posicao + 2, 2);
            string ano = retiraParte(nome, posicao + 4, 2);

            //Completa os anos para ordenar
            if(ano > "26"){
                ano = "19" + ano;
            }
            else ano = "20" + ano;

            data[i] = ano + mes + dia;
        }

        //Ordena os anos em ordem cronológica
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 2 - i; j++){
                if(data[j] > data[j+1]){
                    string temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                }
            }
        }

        //Remove o 19 e 20 dos anos e reorganiza em DD/MM/YY
        for(int i = 0; i <3; i++){
            data[i] = retiraParte(data[i],6,2) + retiraParte(data[i], 4, 2) + retiraParte(data[i], 2, 2);
        }

        listaArq.push_back(nomeSozinho + data[0] + data[1] + data[2]);
    }

    list<string>::iterator it_atual = listaArq.begin();
    list<string>::iterator it_prox = it_atual;
    it_prox++;

    //Ordena os nomes em ordem crescente
    for(int i = 0; i < listaArq.size(); i++){
        list<string>::iterator it_atual = listaArq.begin();
        list<string>::iterator it_prox = it_atual;
        it_prox++;

        while(it_prox !=listaArq.end()){
            string guardaString = *it_atual;

            if (*it_atual > *it_prox){
                *it_atual = *it_prox;
                *it_prox = guardaString;
            }
            it_atual++;
            it_prox++;

        }

    }
    for (string s : listaArq) {
        cout << s << endl;
    }
    return 0;
}