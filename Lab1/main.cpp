#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string.h>
#include <queue>
#include <functional>
#include <fstream>
#include <math.h>

#define EMPTY_STRING ""

using namespace std;

bool comparare(pair<float, float> a, pair<float, float> b){
    return a.second/a.first >= b.second/b.first;
}


class Saci{
public:
    int n;
    vector<pair<float, float>> saci;
    vector<pair<float, float>> saciReturnati;
    float capacitateMaxima;

    float pretMaxim;

    Saci(){
        n = 0;
        capacitateMaxima = 0.0;
        pretMaxim = 0.0;
    }

    Saci(int _n, vector<pair<float, float>> _saci, float _capacitateMaxima):n(_n), saci(_saci), capacitateMaxima(_capacitateMaxima){
        pretMaxim = 0.0;
    }

    friend istream&operator>>(istream &in, Saci & sac);
    friend ostream&operator<<(ostream &out, const Saci & sac);

    void calculeaza();
};

istream&operator>>(istream & in, Saci & sac){
    cout << "Introduceti numarul de saci: ";
    in >> sac.n;
    cout << "Introduceti pe rand greutatea si valoarea sacului: \n";
    for (int i = 0; i < sac.n; i++){
        float greutate, valoare;
        cout << "sacul "<< i << ": \n";
        cout << "Greutate: ";
        in >> greutate;
        cout << "Valoare:";
        in >> valoare;
        sac.saci.push_back(make_pair(greutate, valoare));
    }

    cout << "Introduceti cap. sacului dvs: ";
    in >> sac.capacitateMaxima;

    return in;
}

ostream & operator<<(ostream &out, const Saci & sac){
    //for (int i = 0; i<sac.n; i++){
    //    out << sac.saci[i].first << " " << sac.saci[i].second << "\n";
    //}

    out << "Pretul maximal este: " << sac.pretMaxim << "\n";

    return out;
}

void Saci::calculeaza(){
    sort(saci.begin(), saci.end(), comparare);
    int index;
    for (int i = 0; i < n; i++){
        if (capacitateMaxima - saci[i].first >= 0){
            pretMaxim += saci[i].second;
            capacitateMaxima -= saci[i].first;
            index = i;
        }
        else{
            break;
        }
    }

    if (index < (int)saci.size()){
        if (capacitateMaxima > 0){
            float pret = (saci[index+1].second * capacitateMaxima)/saci[index+1].first;
            pretMaxim += pret;
            capacitateMaxima -= capacitateMaxima;
        }
    }
    else{
        cout << "Nu mai sunt saci disponibili\n";
    }
}

//Exercitiul 2

struct Node{
    pair<char, int> nod;
    Node *left, *right;
};

Node* getNode(pair<char, int> nod, Node* left, Node* right)
{
    Node* node = new Node();

    node->nod = nod;
    node->left = left;
    node->right = right;

    return node;
}

struct comp
{
    bool operator()(const Node* l, const Node* r) const
    {
        return l->nod.second > r->nod.second;
    }
};

bool isLeaf(Node* root) {
    return root->left == nullptr && root->right == nullptr;
}

class Ex2{
public:
    string SIR;
    unordered_map<char, int> frecventa;
    unordered_map<char, string> huffmanCode;
    string sirCodificat;
    Node * root;

    Ex2(){SIR = ""; sirCodificat =""; root = nullptr;}
    Ex2(string sir);

    friend istream&operator>>(istream &in, Ex2 & obj);
    friend ostream&operator<<(ostream &out, Ex2 & obj);

    void vectorFrecventa(); //Calculez frecventa fiecarei litere
    void arboreHuffman(); // O lista de noduri pe care le scriu sub forma unui arbore binar (Node contine litera si frecventa ei, nodul stang si nodul drept)
    void codificareHuffman(Node* root, string str, unordered_map<char, string> &huffmanCode); //functie de codificare
    void decodificareHuffman(Node* root, int &index, string str); //functie de decodificare
};

istream&operator>>(istream &in, Ex2 & obj){ // functie de citire
    cout << "Introduceti textul aici: ";
    char aux[100];
    in.getline(aux, 100);

    obj.SIR = (string)aux;

    return in;
}

ostream&operator<<(ostream &out, Ex2 &obj){ // functie de afisare
    out << "Huffman codes are: \n";
    for (auto x : obj.huffmanCode)
        out << x.first << " " << x.second << "\n";

    for (char ch : obj.SIR)
        obj.sirCodificat += obj.huffmanCode[ch];

    out << "\nEncoded string is: \n";

    ofstream g("date.out");
    g << obj.sirCodificat;
    g.close();

    out << obj.sirCodificat << "\n";

    return out;
}

void Ex2::vectorFrecventa(){
    for (char ch : SIR){
        frecventa[ch]++;
    }
}

void Ex2::arboreHuffman(){

    priority_queue<Node *, vector<Node *>, comp> pq;

    for (auto x: frecventa) {
        //cout << x.first << " " << x.second << "\n";
        pq.push(getNode(x, nullptr, nullptr));
    }

    while(pq.size() != 1){
        Node * left = pq.top(); pq.pop();
        Node * right = pq.top(); pq.pop();

        int sum = left->nod.second + right->nod.second;
        pq.push(getNode(make_pair('\0', sum), left, right));
    }

    //Node * root = pq.top();
    root = pq.top();
}

void Ex2::codificareHuffman(Node* root, string str, unordered_map<char, string> &huffmanCode)
{
    if (root == nullptr) {
        return;
    }

    if (isLeaf(root)) {
        huffmanCode[root->nod.first] = (str != EMPTY_STRING) ? str : "1";
    }

    codificareHuffman(root->left, str + "0", huffmanCode);
    codificareHuffman(root->right, str + "1", huffmanCode);
}

void Ex2::decodificareHuffman(Node* root, int &index, string str){
    if (root == nullptr) {
        return;
    }

    if (isLeaf(root))
    {
        cout << root->nod.first;
        return;
    }

    index++;

    if (str[index] == '0') {
        decodificareHuffman(root->left, index, str);
    }
    else {
        decodificareHuffman(root->right, index, str);
    }
}

Ex2::Ex2(string sir):SIR(sir){
    sirCodificat = "";
}

class Ex3{
public:
    int calculeazaFibonacci(int n);
    int calculeazaFibonacciIterativ(int n);
    int calculeazaFibonacciO1(int n);
};

int Ex3::calculeazaFibonacci(int n){
    if (n <= 1)
        return n;
    return calculeazaFibonacci(n-1) + calculeazaFibonacci(n-2);
}

int Ex3::calculeazaFibonacciIterativ(int n){
    int a = 1, b = 1;
    if (n <= 2) return 1;
    for (int i = 1; i < n; ++ i) {
        int c = a + b;
        a = b;
        b = c;
    }
    return a;
}

int Ex3::calculeazaFibonacciO1(int n){
    return (pow(1 + sqrt(5), n) - pow(1 - sqrt(5), n)) / (pow(2, n) * sqrt(5));
}

//Ex4

int maxi(int a, int b);

int lcs(const char* X, const char* Y, int m, int n) // O(2^(n*m))
{
    if (m == 0 || n == 0)
        return 0;
    if (X[m - 1] == Y[n - 1])
        return 1 + lcs(X, Y, m - 1, n - 1);
    else
        return maxi(lcs(X, Y, m, n - 1), lcs(X, Y, m - 1, n));
}

int maxi(int a, int b)
{
    return (a > b) ? a : b;
}

void LCS(const char *X, const char *Y, int m, int n )
{
    int L[m+1][n+1];

    for (int i=0; i<=m; i++){
        for (int j=0; j<=n; j++){
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (X[i-1] == Y[j-1])
                L[i][j] = L[i-1][j-1] + 1;
            else
                L[i][j] = max(L[i-1][j], L[i][j-1]);
        }
    }

    int index = L[m][n];

    char lcs[index+1];
    lcs[index] = '\0';

    int i = m, j = n;
    while (i > 0 && j > 0){
        if (X[i-1] == Y[j-1]){
            lcs[index-1] = X[i-1];
            i--; j--; index--;
        }
        else if (L[i-1][j] > L[i][j-1])
            i--;
        else
            j--;
      }

    cout << "LCS of " << X << " and " << Y << " is " << lcs;
}

int main()
{
    bool running = true;
    while (running){
        cout << "1 - Knapsack problem\n";
        cout << "2 - Huffman algorithm\n";
        cout << "3 - Fibonacci algorithm\n";
        cout << "4 - Problema 4\n";
        cout << "x - Exit\n";
        char ch;
        cin >> ch;
        switch (ch) {
            case '1' : {
                Saci n;
                cin >> n;
                n.calculeaza();
                cout << n;
            }
            break;
            case '2' : {
                string Huffman = ""; //string default

                /*ifstream f("test.in");
                string tp;
                while(getline(f, tp)){
                    Huffman += tp;
                }

                f.close(); */

                //Ex2 ex2(Huffman);
                fflush(stdin);
                Ex2 ex2;
                cin >> ex2;

                cout << "Textul introdus este: \n" << ex2.SIR << "\n\n";

                ex2.vectorFrecventa();
                ex2.arboreHuffman();
                ex2.codificareHuffman(ex2.root, EMPTY_STRING, ex2.huffmanCode);

                cout << ex2;
                /*cout << "\nDecoded text: \n";

                if (isLeaf(ex2.root))
                {
                    while (ex2.root->nod.second--) {
                        cout << ex2.root->nod.first;
                    }
                    cout << "\n";
                }
                else {
                    int index = -1;
                    while (index < (int)ex2.sirCodificat.size() - 1) {
                        ex2.decodificareHuffman(ex2.root, index, ex2.sirCodificat);
                    }
                    cout << "\n\n";
                } */

                cout << "Percentage of data compression: " << (((ex2.SIR.length() * 8) - ex2.sirCodificat.length()) * 1.0 / (ex2.SIR.length() * 8)) * 100 << "%\n";
                //Teoretic ar trebui sa fie mai bun, dar nu e ...

                // 47 lung sirului dat ca exemplu, * 8 = 376 biti ocupati, dupa compresie => 194 de biti ocupati
                // => procentul de compresie este ~ 48%;
            }
            break;
            case '3' : {
                Ex3 ex3;
                int n;
                //Ex3 pct 1
                cout << "Introduceti al catelea numar vreti sa calculati: ";
                cin >> n;
                cout << ex3.calculeazaFibonacci(n) << "\n";
                cout << "The recursion function has O(2^n) time complexity.\n";


                //Ex3 pct 3
                cout << ex3.calculeazaFibonacciIterativ(n) << "\n";
                cout << "The iterativ function seems to be O(n) in time complexity.\n";

                //Theres a better implementation running in O(1) time complexity
                //source : https://helloacm.com/compute-the-nth-fibonacci-numbers-using-iterative-and-math-algorithms/

                cout << ex3.calculeazaFibonacciO1(n) << "\n";
                cout << "Usuing Binet's formula time complexity is O(1)\n";
            }
            break;
            case '4' : {
                fflush(stdin);
                char X[101];
                char Y[101];
                cout << "Introduceti primul sir: ";
                cin.getline(X, 100);
                fflush(stdin);
                cout << "Introduceti al doilea sir: ";
                cin.getline(Y, 100);

                int m = strlen(X);
                int n = strlen(Y);

                printf("Length of LCS is %d\n", lcs(X, Y, m, n));

                cout << "Cu programare dinamica: \n";
                LCS(X, Y, m, n);
                cout << "\n";

                // Subpunctul 2 -> putem verifica daca cele 2 caractere sunt egale sau nu (altceva mai eficient nu cred ca exista);
                // Subpunctul 3 -> parcurgem stringul si vedem daca exista o potrivire (altceva nu cred ca putem face);
            }
            break;
            case 'x' : {
                running = false;
            }
            break;
            default: running = false;
            break;
        }
    }
    return 0;
}
