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
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

// Чтение матрицы смежности из файла
vector<vector<int>> readAdjMatrix(const string& filename, int& n) {
    ifstream file(filename);
    if (!file) {
        cerr << "Не удалось открыть файл.\n";
        exit(1);
    }

    file >> n;
    vector<vector<int>> matrix(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            file >> matrix[i][j];

    return matrix;
}

// Поиск в ширину от вершины k
vector<int> bfs(const vector<vector<int>>& graph, int k) {
    int n = graph.size();
    vector<bool> visited(n, false);
    queue<int> q;
    vector<int> result;

    visited[k] = true;
    q.push(k);

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        result.push_back(v);

        vector<int> neighbors;
        for (int i = 0; i < n; ++i) {
            if (graph[v][i] != 0 && !visited[i]) {
                neighbors.push_back(i);
            }
        }

        sort(neighbors.begin(), neighbors.end()); // сортировка по возрастанию номеров

        for (int u : neighbors) {
            visited[u] = true;
            q.push(u);
        }
    }

    return result;
}

int main() {
    string filename = "FileName";
    int n;
    vector<vector<int>> graph = readAdjMatrix(filename, n);

    int startVertex;
    cout << "Введите начальную вершину (от 0 до " << n-1 << "): ";
    cin >> startVertex;

    if (startVertex < 0 || startVertex >= n) {
        cerr << "Недопустимая вершина.\n";
        return 1;
    }

    vector<int> reachable = bfs(graph, startVertex);

    cout << "Достижимые вершины из " << startVertex << ": ";
    for (int v : reachable) {
        cout << v << " ";
    }
    cout << endl;

    return 0;
}
