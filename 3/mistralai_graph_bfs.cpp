#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

// Функция для выполнения поиска в ширину (BFS)
void bfs(const std::vector<std::vector<int>>& graph, int startVertex, std::vector<bool>& visited) {
    std::queue<int> q;
    q.push(startVertex);
    visited[startVertex] = true;

    while (!q.empty()) {
        int currentVertex = q.front();
        q.pop();
        std::cout << currentVertex << " ";

        for (int i = 0; i < graph.size(); ++i) {
            if (graph[currentVertex][i] > 0 && !visited[i]) {
                q.push(i);
                visited[i] = true;
            }
        }
    }
}

int main() {
    std::string filename = "graph.txt";
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл " << filename << std::endl;
        return 1;
    }

    int n;
    file >> n;
    std::vector<std::vector<int>> graph(n, std::vector<int>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            file >> graph[i][j];
        }
    }
    file.close();

    int startVertex;
    std::cout << "Введите номер стартовой вершины: ";
    std::cin >> startVertex;

    if (startVertex < 0 || startVertex >= n) {
        std::cerr << "Неверный номер вершины." << std::endl;
        return 1;
    }

    std::vector<bool> visited(n, false);
    bfs(graph, startVertex, visited);
    std::cout << std::endl;

    return 0;
}
