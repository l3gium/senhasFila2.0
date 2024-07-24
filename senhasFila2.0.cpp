#include <iostream>
#include <locale.h>
#include <string>
#include <vector>

/*Desenvolvido por Beatriz Bastos Borges e Miguel Luizatto Alves.*/

using namespace std;

struct No 
{
    int dado;
    No *prox;
};

struct Fila 
{
    No *ini;
    No *fim;
};

Fila* init() 
{
    Fila *f = new Fila;
    f->ini = NULL;
    f->fim = NULL;
    return f;
}

int isEmpty(Fila *f) 
{
    return (f->ini == NULL);
}

void enqueue(Fila *f, int v) 
{
    No *no = new No;
    no->dado = v;
    no->prox = NULL;
    if (isEmpty(f)) {
        f->ini = no;
    }
    else {
        f->fim->prox = no;
    }
    f->fim = no;
}

int dequeue(Fila *f) 
{
    int ret;
    if (isEmpty(f)) 
    {
        ret = -1;
    }
    else 
    {
        No *no = f->ini;
        ret = no->dado;
        f->ini = no->prox;
        if (f->ini == NULL) 
        {
            f->fim = NULL;
        }
        delete no;
    }
    return ret;
}

int count(Fila *f) 
{
    int qtde = 0;
    No *no;
    no = f->ini;
    while (no != NULL) 
    {
        qtde++;
        no = no->prox;
    }
    return qtde;
}

void print(Fila *f) 
{
    No *no;
    no = f->ini;
    cout << "Quantidade de de senhas atendidas: " << count(f) << endl;
    cout << "\n";
    while (no != NULL) 
    {
        cout << no->dado << endl;
        no = no->prox;
    }
    cout << "\n";
}

void freeFila(Fila *f) 
{
    No *no = f->ini;
    while (no != NULL) 
    {
        No *temp = no->prox;
        delete no;
        no = temp;
    }
    delete f;
}

struct Guiche 
{
    int id;
    Fila *senhasAtendidas;
};

vector<Guiche> guiches;

Guiche* findGuiche(int id) 
{
    for (size_t i = 0; i < guiches.size(); i++) 
    {
        if (guiches[i].id == id) 
        {
            return &guiches[i];
        }
    }
    return nullptr;
}

void abrirGuiche(int id) 
{
    Guiche guiche;
    guiche.id = id;
    guiche.senhasAtendidas = init();
    guiches.push_back(guiche);
    cout << "Guich� " << id << " aberto." << endl;
}

void listarSenhasAtendidas(int id) 
{
    Guiche *guiche = findGuiche(id);
    if (guiche != nullptr) 
    {
        cout << "Senhas atendidas pelo guich� " << id << ":" << endl;
        print(guiche->senhasAtendidas);
    } 
    else 
    {
        cout << "Guich� " << id << " n�o encontrado." << "\n" << endl;
    }
}

int main(int argc, char** argv) 
{
    setlocale(LC_ALL, "");
    Fila *senhasGeradas = init();
    int opcao;
    int senha = 0;

    do 
    {
        cout << "Digite uma op��o: " << endl;
        cout << "0. Sair" << endl;
        cout << "1. Gerar senha" << endl;
        cout << "2. Abrir guich�" << endl;
        cout << "3. Realizar atendimento" << endl;
        cout << "4. Listar senhas atendidas" << endl;
        cout << "Op��o: ";
        cin >> opcao;
        cout << "\n";

        if (opcao == 0 && !isEmpty(senhasGeradas)) 
        {
            cout << "Ainda h� senhas aguardando atendimento. N�o � poss�vel sair." << "\n" << endl;
            opcao = -1;
        }
        int totalAtendidas = 0;
        switch (opcao) 
        {
            case 0:
                cout << "Encerrando programa...\n";
                
                for (const auto& guiche : guiches) 
                {
                    totalAtendidas += count(guiche.senhasAtendidas);
                }
                cout << "Total de senhas atendidas: " << totalAtendidas << endl;
            case 1:
                senha++;
                enqueue(senhasGeradas, senha);
                cout << "Senha gerada: " << senha << endl;
                cout << "Senhas aguardando atendimento: " << count(senhasGeradas) << "\n" << endl;
                break;
            case 2: 
            {
                int idGuiche;
                cout << "Digite o ID do guich� a ser aberto: ";
                cin >> idGuiche;
                cout << "\n";
                abrirGuiche(idGuiche);
                cout << "Senhas aguardando atendimento: " << count(senhasGeradas) << endl;
                cout << "N�mero de guich�s abertos: " << guiches.size() << "\n" << endl;
                break;
            }
            case 3: 
            {
                if (isEmpty(senhasGeradas)) 
                {
                    cout << "Nenhuma senha para atender." << endl;
                    break;
                }
                int idGuiche;
                cout << "Digite o ID do guich�: ";
                cin >> idGuiche;
                cout << "\n";
                Guiche *guiche = findGuiche(idGuiche);
                if (guiche != nullptr) 
                {
                    int senhaAtendida = dequeue(senhasGeradas);
                    enqueue(guiche->senhasAtendidas, senhaAtendida);
                    cout << "\nSenha atendida: " << senhaAtendida << endl;
                } 
                else 
                {
                    cout << "Guich� " << idGuiche << " n�o encontrado." << endl;
                }
                cout << "Senhas aguardando atendimento: " << count(senhasGeradas) << "\n" << endl;
                break;
            }
            case 4: 
            {
                int idGuiche;
                cout << "Digite o ID do guich�: ";
                cin >> idGuiche;
                cout << "\n";
                listarSenhasAtendidas(idGuiche);
                break;
            }
            default:
                cout << "Op��o inv�lida. Tente novamente." << "\n" << endl;
        }

    } while (opcao != 0);

    freeFila(senhasGeradas);
    for (auto& guiche : guiches) 
    {
        freeFila(guiche.senhasAtendidas);
    }

    return 0;
}