/*
Дано описание ориентированного графа в текстовом файле с именем FileName. в виде матрицы смежности.
Первая строка файла содержит количество вершин графа (n), а следующие n
строк содержат матрицу смежности (m), m[i][j]=0, если дуги из вершины i в вершину j не существует,
иначе m[i][j] хранит вес соответствующей дуги. Выполнить поиск в ширину от вершины
с номером k. В результате вывести номера вершин графа, достижимые для данной вершины, в
порядке их обхода при поиске в ширину. Если на очередном шаге сортировки имелось несколько
равноправных вершин, перечислять их в порядке возрастания номеров вершин.
 */

#include "graph_bfs.h"
#include <fstream>
#include <queue>
#include <algorithm>

std::vector<std::vector<int>> ReadGraph(const std::string& filename, int& n, bool& errorFlag) {
    errorFlag = false;
    std::vector<std::vector<int>> matrix;
    std::ifstream file(filename);

    if (!file) {
        errorFlag = true;
        return matrix;
    }

    if (!(file >> n)) {
        errorFlag = true;
        return matrix;
    }

    matrix.resize(n, std::vector<int>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!(file >> matrix[i][j])) {
                errorFlag = true;
                return matrix;
            }
        }
    }

    return matrix;
}

std::vector<int> Bfs(const std::vector<std::vector<int>>& graph, int start) {
    int n = graph.size();
    std::vector<bool> visited(n, false);
    std::queue<int> q;
    std::vector<int> result;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        result.push_back(v);

        std::vector<int> neighbors;
        for (int i = 0; i < n; ++i) {
            if (graph[v][i] != 0 && !visited[i]) {
                neighbors.push_back(i);
            }
        }

        std::sort(neighbors.begin(), neighbors.end());

        for (int u : neighbors) {
            visited[u] = true;
            q.push(u);
        }
    }

    return result;
}
