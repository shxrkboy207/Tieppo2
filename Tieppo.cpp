#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

//recebendo dados do arquivo
int lerDados(string nomeArquivo, float dados[][2], string classe[]) {

    ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo!" << endl;
        return 0;
    }

    int quantidade = 0;

    while (arquivo >> dados[quantidade][0]
                   >> dados[quantidade][1]
                   >> classe[quantidade]) {

        quantidade++;
    }

    arquivo.close();

    return quantidade;
}

//adicionando nova fruta ao arquivo
void colocarFrutaNaLista(string nomeArquivo, float peso, float diametro, string classe){
    // adicionando nova fruta ao arquivo

    ofstream arquivo(nomeArquivo, ios::app);

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo!" << endl;
        return;
    }

    arquivo << peso << " "
            << diametro << " "
            << classe << endl;

    //arquivo.close();
}

// função satanica
float funcaoDistanciaEuclidiana(float x1, float y1, float x2, float y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

//função para ordenar as distancias e classes(bagulho chato de descobrir como faz MEU DEUS.)
int ordenar(float distancias[], string classe[], float dados[][2], int tamanho) {

    // repetidor que lê o tamanho do vetor e compara os valores e os troca de posição caso seja preciso
    for (int i = 0; i < tamanho - 1; i++) {

        for (int j = 0; j < tamanho - i - 1; j++) {

            // comparando os elementos do vetor
            if (distancias[j] > distancias[j + 1]) {

                // trocando os elementos de posição
                float aux = distancias[j];
                distancias[j] = distancias[j + 1];
                distancias[j + 1] = aux;

                //trocando as classes de posição
                string aux2 = classe[j];
                classe[j] = classe[j + 1];
                classe[j + 1] = aux2;

                //trocando o peso de posição
                float auxPeso = dados[j][0];
                dados[j][0] = dados[j + 1][0];
                dados[j + 1][0] = auxPeso;

                //trocando o diametro de posição
                float auxDiametro = dados[j][1];
                dados[j][1] = dados[j + 1][1];
                dados[j + 1][1] = auxDiametro;
            }
        }
    }

    return 0;
}

//função da votação das classes
string votar(string classe[], int k) {

    int votosBanana = 0;
    int votosKiwi = 0;

    for (int i = 0; i < k; i++) {

        if (classe[i] == "Banana")
            votosBanana++;

        if (classe[i] == "Kiwi")
            votosKiwi++;
    }

    // DEBUG (pode remover depois)
    cout << "\nVotos Banana: " << votosBanana << endl;
    cout << "Votos Kiwi: " << votosKiwi << endl;

    // empate = maior prioridade para K
    if (votosBanana == votosKiwi) {
        return "Kiwi";
    }

    if (votosBanana > votosKiwi)
        return "Banana";
    else
        return "Kiwi";
}

//inicio do código
int main() {

    //recebendo os dados do arquivo
    float dados[1000][2];
    string classe[1000];

    int quantidade = lerDados("frutas.txt", dados, classe);

    //DEBUG pra conferir se leu certo
    cout << "Dados carregados" << endl;

    for (int i = 0; i < quantidade; i++) {
        cout << dados[i][0] << " "
             << dados[i][1] << " "
             << classe[i] << endl;
    }

    float novoPeso, novoDiametro;

    cout << "\nDigite o peso da nova fruta: ";
    cin >> novoPeso;

    cout << "Digite o diametro da nova fruta: ";
    cin >> novoDiametro;

    cout << "\nDistancias\n";

    float distancias[1000];

    // calculando distancias
    for (int i = 0; i < quantidade; i++) {

        distancias[i] = funcaoDistanciaEuclidiana(
            novoPeso,
            novoDiametro,
            dados[i][0],
            dados[i][1]
        );
    }

    // ordenar depois de calcular
    ordenar(distancias, classe, dados, quantidade);

    // mostrar resultados
    for (int i = 0; i < quantidade; i++) {

        cout << "fruta " << i + 1
             << " (Classe " << classe[i] << ")"
             << " -> Distancia: "
             << distancias[i]
             << endl;
    }

    //declarando o k vizinhos
    int k = 3;

    cout << "\nk vizinhos = " << k << endl;

    for (int i = 0; i < k; i++) {

        cout << "Vizinho " << i + 1
             << " Classe: " << classe[i]
             << " Distancia: " << distancias[i]
             << endl;
    }

    string resultado = votar(classe, k);

    //GLORIA FINALMENTE
    cout << "Classe prevista pelo KNN: "
         << resultado
         << endl;

    colocarFrutaNaLista(
        "frutas.txt",
        novoPeso,
        novoDiametro,
        resultado
    );

dados[quantidade][0] = novoPeso;
dados[quantidade][1] = novoDiametro;
classe[quantidade] = resultado;
quantidade++;

//mostrar essa bagaça atualizada(teste 123124124)
quantidade = lerDados("frutas.txt", dados, classe);

cout << "\n=== MATRIZ ATUALIZADA ===\n";

for (int i = 0; i < quantidade; i++) {

    cout << dados[i][0] << " "
         << dados[i][1] << " "
         << classe[i]
         << endl;
}

cout << "\nPressione ENTER para sair...";
cin.ignore();
cin.get();
}