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
#include <iostream>

int main() {
    std::string filename = "graph.txt";
    int n, startVertex;
    bool errorFlag = false;

    auto graph = ReadGraph(filename, n, errorFlag);

    if (errorFlag) {
        std::cerr << "Ошибка чтения файла!" << std::endl;
        return 1;
    }

    std::cout << "Введите начальную вершину (0-" << n - 1 << "): ";
    if (!(std::cin >> startVertex) || startVertex < 0 || startVertex >= n) {
        std::cerr << "Неверный номер вершины!" << std::endl;
        return 1;
    }

    auto reachable = Bfs(graph, startVertex);

    std::cout << "Порядок обхода: ";
    for (int v : reachable) {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    return 0;
}
