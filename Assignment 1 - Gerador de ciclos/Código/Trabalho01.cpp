#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

class Graph {
private:
    int V; // Número de vértices no grafo
    vector<vector<int>> adj; // Lista de adjacências

public:
    Graph(int V) : V(V), adj(V) {} // Construtor

    // Adiciona uma aresta entre os vértices u e v
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // O grafo é não direcionado
    }

    // Função para imprimir todos os ciclos no grafo usando DFS
    void printAllCyclesDFS();

    // Função utilitária para encontrar ciclos a partir de um vértice específico usando DFS
    void printAllCyclesUtilDFS(vector<int>& path, vector<bool>& visited, int start, int current);

    // Função para imprimir todos os ciclos no grafo usando permutação
    void printAllCyclesPermutation();
};

// Função para imprimir todos os ciclos no grafo usando DFS
void Graph::printAllCyclesDFS() {
    vector<int> path; // Caminho atual durante a busca por ciclos
    vector<bool> visited(V, false); // Mantém o controle dos vértices visitados durante a busca

    // Itera sobre todos os vértices para iniciar a busca por ciclos
    for (int i = 0; i < V; ++i) {
        path.push_back(i); // Adiciona o vértice atual ao caminho
        visited[i] = true; // Marca o vértice como visitado
        printAllCyclesUtilDFS(path, visited, i, i); // Chamada para a função utilitária para encontrar ciclos
        visited[i] = false; // Marca o vértice como não visitado para a próxima iteração
        path.pop_back(); // Remove o vértice atual do caminho
    }
}

// Função utilitária para encontrar ciclos a partir de um vértice específico usando DFS
void Graph::printAllCyclesUtilDFS(vector<int>& path, vector<bool>& visited, int start, int current) 
{
    // Verifica se o caminho atual tem mais de dois vértices e se o vértice atual está conectado ao vértice inicial (formando um ciclo)
    if (path.size() > 2 && find(adj[current].begin(), adj[current].end(), start) != adj[current].end())
    {
        // Se um ciclo for encontrado, imprime os vértices do ciclo
        for (int vertex : path) 
        {
            cout << vertex << " "; // Imprime o ciclo encontrado
        }

        cout << endl;
        return;
    }

    // Itera sobre todos os vértices adjacentes ao vértice atual
    for (int next : adj[current]) 
    {
        // Verifica se o vértice adjacente não foi visitado ainda
        if (!visited[next]) 
        {
            visited[next] = true; // Marca o vértice adjacente como visitado
            path.push_back(next); // Adiciona o vértice adjacente ao caminho

            // Chama recursivamente a função para explorar os vértices adjacentes ao vértice adjacente atual
            printAllCyclesUtilDFS(path, visited, start, next);
            path.pop_back(); // Remove o vértice adjacente do caminho para explorar outras possibilidades
            visited[next] = false; // Marca o vértice adjacente como não visitado para futuras iterações
        }
    }
}

// Função para imprimir todos os ciclos no grafo usando permutação
void Graph::printAllCyclesPermutation() 
{
    // Inicializa um vetor de vértices com os índices de 0 a V-1
    vector<int> vertices(V);

    for (int i = 0; i < V; ++i) 
    {
        vertices[i] = i;
    }

    // Gera todas as permutações possíveis dos vértices
    do 
    {
        bool isCycle = true;

        // Verifica se a permutação atual forma um ciclo válido
        for (int i = 0; i < V - 1; ++i) 
        {
            // Verifica se há uma aresta entre os vértices adjacentes na permutação
            if (find(adj[vertices[i]].begin(), adj[vertices[i]].end(), vertices[i + 1]) == adj[vertices[i]].end()) 
            {
                isCycle = false;

                break;
            }
        }

        // Se a permutação forma um ciclo válido, imprime os vértices do ciclo
        if (isCycle) 
        {
            for (int vertex : vertices) 
            {
                cout << vertex << " ";
            }

            cout << endl;
        }
    } 
    while (next_permutation(vertices.begin(), vertices.end())); // Gera a próxima permutação
}

int main() {
    // Criação do grafo de 4 vértices
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
       

    // Criação do grafo de 5 vértices
    /*
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(2, 4);
    */

    // Criação do grafo de 12 vértices
    /*
    Graph g(12);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);
    g.addEdge(4, 6);
    g.addEdge(5, 6);
    g.addEdge(5, 7);
    g.addEdge(6, 7);
    g.addEdge(6, 8);
    g.addEdge(7, 8);
    g.addEdge(7, 9);
    g.addEdge(8, 9);
    g.addEdge(8, 10);
    g.addEdge(9, 10);
    g.addEdge(9, 11);
    g.addEdge(10, 11);
    */

    // Execução do algoritmo para encontrar ciclos em g1 usando DFS e medir o tempo de execução
    auto start1 = chrono::high_resolution_clock::now();
    g.printAllCyclesDFS();
    auto end1 = chrono::high_resolution_clock::now();
    auto duration1 = chrono::duration_cast<chrono::microseconds>(end1 - start1);
    cout << "Time taken by DFS based approach: " << duration1.count() << " microseconds" << endl;

    // Execução do algoritmo para encontrar ciclos em g1 usando permutação e medir o tempo de execução
    auto start2 = chrono::high_resolution_clock::now();
    g.printAllCyclesPermutation();
    auto end2 = chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<chrono::microseconds>(end2 - start2);
    cout << "Time taken by permutation based approach: " << duration2.count() << " microseconds" << endl;

    return 0;
}
