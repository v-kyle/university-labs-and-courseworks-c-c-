#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <locale.h>

class Graph{
private:
    int** a = nullptr;
    int n;
public:
    Graph(int rows) : n(rows) {
        a = new int* [n];
        for(int i = 0; i < n; i++)
            a[i] = new int [n];
    }
    ~Graph(){
        for(int i = 0; i < n;i++)
            delete [] a[i];
        delete [] a;
    }
    void Input(int);
    void Output() const;
    void Search(int, int);
};

void Graph::Input(int f) {
    for(int i = 0; i < n;i++) {
        for(int j = 0; j < n;j++) {
            if(rand() % 3 == 2)
                a[i][j] = 0;
            else
                a[i][j] = rand() % 99 + 1;
        }
        a[i][i] = 0;
    }
}

void Graph::Output() const {
    for(int i = 0; i < n + 1;i++)
    {
        std::cout << i;
        if(i < 10) std::cout << " |";
        else std::cout << "|";
    }
    std::cout << std::endl;
    for(int i = 0; i < n + 1;i++)
        std::cout << "---";
    std::cout << std::endl;
    for(int i = 0; i < n;i++) {
        for(int j = 0; j < n;j++) {
            if(j == 0) {
                std::cout << i + 1;
                if(i < 9) std::cout << " |";
                else std::cout << "|";
            }
            std::cout << a[i][j];
            if(a[i][j] < 10)
                std::cout << "  ";
            else
                std::cout << " ";
        }
        std::cout << std::endl;
    }
}

void Graph::Search(int st, int second)
{
    using namespace std;
    int V = n;
    int distance[V], count, index, i, u, m = st + 1;
    bool visited[V];
    for (i = 0;i < V;i++) {
        distance[i] = INT_MAX;
        visited[i] = false;
    }
    distance[st] = 0;
    for (count = 0;count < V - 1;count++) {
        int min = INT_MAX;
        for (i = 0;i < V;i++)
            if (!visited[i] && distance[i] <= min) {
                min = distance[i];
                index = i;
            }
        u = index;
        visited[u] = true;
        for (i = 0;i < V;i++)
            if (!visited[i] && a[u][i] && distance[u] != INT_MAX &&
                distance[u] + a[u][i] < distance[i])
                distance[i] = distance[u] + a[u][i];
    }
    std::cout<<"The cost of the shortest path from the top "<< m << " to the top " << second << ":\n";
    if (distance[second - 1] != INT_MAX)
        std::cout << m << " -> " << second <<" = "<< distance[second - 1] << endl;
    else std::cout << m << " -> " << second << " = " << "route unavailable" << endl;

    //------------------------------------

    int ver[V];
    int b[V][V];
    int end = second - 1;
    ver[0] = end + 1;
    int k = 1;
    int weight = distance[end];

    for(int i = 0;i < n;i++)
        for(int j= 0;j < n;j++)
            b[i][j] = a[j][i];

    while (end != st ) {
        for (int i = 0; i<V; i++)
            if (b[end][i] != 0) {
                int temp = weight - b[end][i];
                if (temp == distance[i]) {
                    weight = temp;
                    end = i;
                    ver[k] = i + 1;
                    k++;
                }
            }
    }
    printf("\n Shortest path output: \n");
    for (int i = k - 1; i >= 0; i--) {
        cout << ver[i];
        if(i - 1 >= 0)
            cout << " -> ";
    }
    cout << endl;
}

int main() {
    srand(time(nullptr));
    using namespace std;

    int n, s, l;
    cout << "Enter the number of vertices in the graph: \n n =";
    cin >> n;
    cout << "Enter the start vertex: \n s =";
    cin >> s;
    cout << "Enter the end vertex: \n l =";
    cin >> l;
    cout << endl;
    Graph gr(n);
    gr.Input(1);
    gr.Output();
    cout << endl;
    gr.Search(s-1,l);

    return 0;
}