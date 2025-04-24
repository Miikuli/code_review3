/*
Дано описание ориентированного графа в текстовом файле с именем FileName. в виде матрицы смежности.
Первая строка файла содержит количество вершин графа (n), а следующие n
строк содержат матрицу смежности (m), m[i][j]=0, если дуги из вершины i в вершину j не существует,
иначе m[i][j] хранит вес соответствующей дуги. Выполнить поиск в ширину от вершины
с номером k. В результате вывести номера вершин графа, достижимые для данной вершины, в
порядке их обхода при поиске в ширину. Если на очередном шаге сортировки имелось несколько
равноправных вершин, перечислять их в порядке возрастания номеров вершин.
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

vector<int> BFS(const vector<vector<int>>& graph, int start) {
    int n = graph.size();
    vector<bool> visited(n, false);
    vector<int> traversal_order;
    queue<int> q;

    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        traversal_order.push_back(current);

        // Собираем все смежные вершины (в порядке возрастания номеров)
        vector<int> neighbors;
        for (int neighbor = 0; neighbor < n; ++neighbor) {
            if (graph[current][neighbor] != 0 && !visited[neighbor]) {
                neighbors.push_back(neighbor);
            }
        }
        sort(neighbors.begin(), neighbors.end()); // Сортируем по возрастанию

        // Добавляем в очередь
        for (int neighbor : neighbors) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    return traversal_order;
}

vector<vector<int>> readGraph(const string& filename, int& n) {
    ifstream file(filename);
    file >> n;
    vector<vector<int>> graph(n, vector<int>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            file >> graph[i][j];
        }
    }

    return graph;
}

int main() {
    string filename = "graph.txt";  // Пример файла:
                                    // 4
                                    // 0 1 1 0
                                    // 0 0 1 0
                                    // 1 0 0 1
                                    // 0 0 0 0
    int n, k;
    cout << "Введите номер стартовой вершины (k): ";
    cin >> k;

    vector<vector<int>> graph = readGraph(filename, n);

    if (k < 0 || k >= n) {
        cerr << "Ошибка: неверный номер вершины!" << endl;
        return 1;
    }

    vector<int> reachable = BFS(graph, k);

    cout << "Порядок обхода вершин (BFS): ";
    for (int vertex : reachable) {
        cout << vertex << " ";
    }
    cout << endl;

    return 0;
}
