#include "../graph/graph.h"
#include <iostream>
using namespace std;

int main() {
    GraphMatrix<string, string> g;
    // 添加顶点
    g.insert("A");
    g.insert("B");
    g.insert("C");
    g.insert("D");
    g.insert("E");
    g.insert("F");
    
    // 添加边 (权重, 顶点1索引, 顶点2索引)
    g.insert("AB", 1, 0, 1); // A --1-- B
    g.insert("AD", 4, 0, 3); // A --4-- D
    g.insert("BE", 3, 1, 4); // B --3-- E
    g.insert("BC", 2, 1, 2); // B --2-- C
    g.insert("CF", 5, 2, 5); // C --5-- F
    g.insert("DF", 6, 3, 5); // D --6-- F
    g.insert("EF", 5, 4, 5);

    // 测试DFS
    cout << "DFS starting from A:" << endl;
    g.dfs(0); // 从顶点 'A' 开始深度优先搜索（0 表示顶点 A）
    for (int i = 0; i < g.n; i++) {
        cout << "Vertex " << g.vertex(i) << ": ";
        cout << "dTime = " << g.dTime(i) << ", ";
        cout << "fTime = " << g.fTime(i) << ", ";
        cout << "parent = " << (g.parent(i) != -1 ? g.vertex(g.parent(i)) : "None") << endl;
    }

    // 测试BFS
    cout << "\nBFS starting from A:" << endl;
    g.bfs(0); // 从顶点 'A' 开始广度优先搜索
    for (int i = 0; i < g.n; i++) {
        cout << "Vertex " << g.vertex(i) << ": ";
        cout << "dTime = " << g.dTime(i) << ", ";
        cout << "parent = " << (g.parent(i) != -1 ? g.vertex(g.parent(i)) : "None") << endl;
    }

    // 测试Dijkstra算法，寻找从A（顶点0）到其他顶点的最短路径
    cout << "\nDijkstra from A:" << endl;
    g.dijkstra(0);

    // 测试Prim算法，构建最小生成树
    cout << "\nPrim from A:" << endl;
    g.prim(0);

    return 0;
}