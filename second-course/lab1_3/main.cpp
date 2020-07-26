#include <iostream>
#include <windows.h>
#include <time.h>
#include <chrono>
#include <queue>

using namespace std;
class Node {
    char d;
    Node* lft;
    Node* mdl;
    Node* rgt;
public:
    Node():lft(nullptr), mdl(nullptr),rgt(nullptr){}
    ~Node() {
        if (lft) delete lft;
        if (mdl) delete mdl;
        if (rgt) delete rgt;
    }
    friend class Tree;
};

class Tree
{
    Node* root;
    char num{}, maxnum{};
    int maxrow{}, offset{};
    int count = 0;
    int depth1 = 0;
    char**SCREEN{};
    void clrscr()
    {
        for (int i = 0; i < maxrow; i++)

            memset(SCREEN[i], '.', 80);

    }
    Node* MakeNode(int depth)
    {
        Node* v = nullptr;
        int Y = (depth < rand() % 6 + 1) && (num < 'z');
        if (Y) {

            v = new Node;
            v->lft = MakeNode(depth + 1);
            v->d = num++;
            v->mdl = MakeNode(depth + 1);
            v->rgt = MakeNode(depth + 1);

        }

        return v;

    }
    void OutNodes(Node* v, int r, int c)
    {
        int i = 1;
        if (r && c && (c < 80))
        {
            if (SCREEN[r - 1][c - 1] == '.')
            {
                SCREEN[r - 1][c - 1] = v->d;
            }
            else
            {
                while ((SCREEN[r - 1][c - i] != '.') || (SCREEN[r - 1][c + i] != '.'))
                    i++;
                if (SCREEN[r - 1][c - i] != '.')
                {
                    SCREEN[r - 1][c - i] = v->d;
                }
                else
                {
                    SCREEN[r - 1][c + i] = v->d;
                }
            }
        }
        if (r < maxrow) {

            if (v->lft) OutNodes(v->lft, r + 1, c - (offset >> r));
            if (v->mdl) OutNodes(v->mdl, r + 1, c);
            if (v->rgt) OutNodes(v->rgt, r + 1, c + (offset >> r));

        }

    }
    Tree(const Tree& B)
    {
        root = new Node;
        root->d = B.root->d;
        root->lft = B.root->lft;
        root->mdl = B.root->mdl;
        root->mdl = B.root->mdl;
        B.root->lft = nullptr;
        B.root->mdl = nullptr;
        B.root->rgt = nullptr;
    }
    Tree operator = (const Tree& B)
    {
        if (this != &B)
        {
            root = new Node;
            root->d = B.root->d;
            root->lft = B.root->lft;
            root->mdl = B.root->mdl;
            root->mdl = B.root->mdl;
            B.root->lft = nullptr;
            B.root->mdl = nullptr;
            B.root->rgt = nullptr;
        }
        return *this;
    }
public:
    Tree(char nm, char mnm, int mxr) :	num(nm), maxnum(mnm), maxrow(mxr), offset(40), root(nullptr)
    {
        SCREEN = new char* [maxrow];

        for (int i = 0; i < maxrow; i++) SCREEN[i] = new char[80];
    }
    ~Tree() {
        for (int i = 0; i < maxrow; i++) delete[]SCREEN[i];
        delete[]SCREEN; delete root;
    }
    void MakeTree()
    {
        root = MakeNode(0);
    }
    bool exist() { return root != nullptr; }
    Node* Out_root()
    {
        return root;
    }
    void result()
    {
        cout << "Nodes Passed = " << count << endl;
        cout << "The number of vertices having at least one descendant = " << depth1 << endl;
    }
    std::string BFS(Node* root1)
    {
        std::queue<Node*> q;
        std::string st;
        q.push(root1);
        int less_then_two_vassals = 0;
        while (!q.empty()) {
            count++;
            int current_vassals = 0;
            Node *tmp = (Node*) q.front();
            q.pop();
            st = st + tmp->d + "_";
            if (tmp->lft) {
                current_vassals++;
                q.push(tmp->lft);
            }
            if (tmp->mdl) {
                current_vassals++;
                q.push(tmp->mdl);
            }
            if (tmp->rgt) {
                current_vassals++;
                q.push(tmp->rgt);
            }
            if (current_vassals >= 1) {
                depth1++;
            }
        }
        cout<<st<<endl;
    }
    void OutTree()
    {
        clrscr();

        OutNodes(root, 1, offset);

        for (int i = 0; i < maxrow; i++)

        {
            SCREEN[i][79] = 0;

            cout << "\n" << SCREEN[i];

        }

        cout << "\n";
    }
};
int main()
{
    unsigned long begin_t, end_t, begin_t1, end_t1, begin_t2, end_t2;
    Tree Tr('a', 'z', 8);
    srand(time(nullptr));

    auto begin_t4 = chrono::high_resolution_clock::now();
    Tr.MakeTree();
    auto end_t4 = chrono::high_resolution_clock::now();
    auto time = chrono::duration_cast<chrono::nanoseconds>(end_t4-begin_t4);
    if (Tr.exist()) {
        begin_t = clock();
        Tr.OutTree();
        end_t = clock();
        cout << "\n" << "Tree search: ";
        begin_t1 = clock();
        cout<< Tr.BFS(Tr.Out_root());
        end_t1 = clock();
        Tr.result();
        cout << endl;
        cout << "Time to create a tree: " << time.count()<< endl;
        cout << "Wood processing time: " << (float)(end_t - begin_t) / CLOCKS_PER_SEC << endl;
        cout << "Tree output time: " << (float)(end_t1 - begin_t1) / CLOCKS_PER_SEC << endl;
    }

    else cout << "Tree is empty!";

    cout << "\n" << "=== End ===";
    return 0;
}