#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <math.h>
#include <list>
#include <unordered_set>
#include <unordered_map>

using namespace std;

struct coords{
    float x;
    float y;

    inline coords addCoords(float x, float y){ this->x = x; this->y = y; return *this;}

    bool operator==(coords p){
        return x == p.x && y == p.y;
    }

    bool operator!=(coords p){
        return x != p.x || y != p.y;
    }
};

struct cities{
    coords city1;
    coords city2;

    cities(coords _x, coords _y){
        this->city1 = _x;
        this->city2 = _y;
    }

    cities(){
        this->city1.x = 0.0;
        this->city1.y = 0.0;
        this->city2.x = 0.0;
        this->city2.y = 0.0;
    }

    friend ostream&operator<<(ostream &out, const cities & obj){
        printf("Oras1(%.2f, %.2f) -> Oras2(%.2f, %.2f): ", obj.city1.x, obj.city1.y, obj.city2.x, obj.city2.y); //imi e lene sa le scriu cu out
        return out;
    }
};

class Graph{
public:
    vector<coords> city;
    //vector<pair<cities, float>> distanceBetweenCities;
    vector<pair<cities, float>> distanceBetweenCities;
    float ** distanceBCities;
    float solution;
    float cost;

    float distantaEuclidiana(coords, coords);
    void completeGraph();

    void travelingSalesman();
    void nearestNeighbour();

    friend istream&operator>>(istream &in, Graph &obj);
    friend ostream&operator<<(ostream &out, const Graph & obj);
    Graph(){
        distanceBCities = nullptr;
        solution = INT_MAX * 1.0;
        cost = 1000.0;
    }

    void permute(int * a, int i, int n);
    void cal_sum(int * a, int n);
};

istream&operator>>(istream &in, Graph &obj){
    ifstream fin("date.in");
    float x, y;
    coords coordonate;
    while(fin >> x >> y){
        obj.city.push_back(coordonate.addCoords(x, y));
    }
    fin.close();

    //aici initializez matricea de adiacenta
    //mai intai verific daca e deja ocupata (sa pot citi din nou)
    if (obj.distanceBCities != NULL){
        for (int i = 0; i < (int)obj.city.size(); i++)
            delete[] obj.distanceBCities[i];
        delete[] obj.distanceBCities;
    }

    //aloc matricea ca sa o pot calcula (fac asta ca daca o initializam in costructor nu stiam lungimea ei si nu voiam sa-i dau valori mai mari/mic)
    obj.distanceBCities = new float*[obj.city.size()];
    for (int i = 0; i < (int)obj.city.size(); i++){
        obj.distanceBCities[i] = new float[obj.city.size()];
    }

    return in;
}

ostream&operator<<(ostream &out, const Graph & obj){
    //for (auto u : obj.city)
    //    out << u.x << " " << u.y << "\n";

    /*for (auto x : obj.distanceBetweenCities){
        out << x.first << x.second << "\n";
    }*/

    /*for (int i = 0; i < obj.city.size(); i++){
        for (int j = 0; j < obj.city.size(); j++)
            cout << obj.distanceBCities[i][j] << " ";
        cout << "\n";
    }*/

    cout << "TSP: " << obj.solution << "\n";

    cout << "Nearest neighbour: " << obj.cost << "\n";
    return out;
}

float Graph::distantaEuclidiana(coords a, coords b){
    return sqrt(pow((b.x - a.x), 2) + pow((b.y - a.y), 2));
}

void Graph::completeGraph(){
    for (vector<coords>::iterator it1 = city.begin(); it1 != city.end(); it1++){
        for (vector<coords>::iterator it2 = city.begin(); it2 != city.end(); it2++){
            if (it2 != it1){
                cities aux(*(it1), *(it2));
                float aux2 = distantaEuclidiana(*(it1), *(it2));
                distanceBetweenCities.push_back(make_pair(aux, aux2));
            }
        }
    }

    int len = city.size();

    for (int i = 0; i < len; i++){
        for (int j = 0; j < len; j++){
            if (i != j){
                distanceBCities[i][j] = distantaEuclidiana(city[i], city[j]);
            }
            else{
                distanceBCities[i][j] = 0.0;
            }
        }
    }
}

void TSP(float ** matrix, vector<bool>& v, int currPos, int n, int counter, float cost, float& ans){
    if (counter == n && matrix[currPos][0]) {
        ans = min(ans, cost + matrix[currPos][0]);
        return;
    }

    for (int i = 0; i < n; i++) {
        if (!v[i] && matrix[currPos][i]) {

            // Mark as visited
            v[i] = true;
            TSP(matrix, v, i, n, counter + 1,
                cost + matrix[currPos][i], ans);

            // Mark ith node as unvisited
            v[i] = false;
        }
    }
}

void Graph::travelingSalesman(){
    int len = city.size();
    vector<bool> v(len);
    for (int i = 0; i < len; i++)
        v[i] = false;

    v[0] = true;

    TSP(distanceBCities, v, 0, len, 1, 0, solution);
}

void Graph::nearestNeighbour(){
    int len = city.size(); //matrice de vizite;
    bool visited[len][len];
    for (int i = 0; i < len; i++)
        for (int j = 0; j < len; j++){
            visited[i][j] = false;
        }

    //selectez o muchie a - b

    //float cost = 0.0;

    for (int i = 0; i < len; i++){
        float cost_min = 1000.0;
        for (int j = 0; j < len; j++){
            if (distanceBCities[i][j] < cost_min && visited[i][j] == false && i != j){
                cost_min = distanceBCities[i][j];
                visited[i][j] = true;
            }
        }
        cost += cost_min;
    }
}

void swap(int *x, int *y){
    int t;
    t = *x;
    *x = *y;
    *y = t;
}

void Graph::cal_sum(int * a, int n){
    int i; float suma = 0;
    for (i = 0; i <= n; i++)
        suma+= distanceBCities[a[i%city.size()]][a[(i+1)%city.size()]];

    if (cost > suma){
        cost = suma;
    }
}

void Graph::permute(int *a, int i, int n){
    int j;
    if (i == n)
        cal_sum(a, n);
    else{
        for (j = i; j <= n; j++){
            swap((a + i), (a + j));
            permute(a, i+1, n);
            swap((a+i), (a+j));
        }
    }
}

class Chromosome{
public:
    int a, b, n;
    float precizie;
    vector<bool> numberOfBits;

    Chromosome();
    Chromosome(int _a, int _b, int _n);

    float transformation();
};

Chromosome::Chromosome(){
    this->a = 0;
    this->b = 0;
    this->n = 0;
    this->precizie = 0.0;
}

Chromosome::Chromosome(int _a, int _b, int _n):numberOfBits(_n, false){
    this->a = _a;
    this->b = _b;
    this->n = _n;
    this->precizie = (b-a)/pow(2, n);
}

float Chromosome::transformation(){
    int j = 0;
    int number = 0;
    for (int i = this->numberOfBits.size()-1; i >= 0; i--){
        number += numberOfBits[i]*pow(2, j);
        j++;
    }

    float number_to_return;
    number_to_return = number * this->precizie;
    number_to_return += this->a;

    return number_to_return;
}

int main()
{
    Graph test;
    cin >> test;
    test.completeGraph();
    test.travelingSalesman();

    int a[] = {0, 1, 2, 3, 4};

    test.permute(a, 0, 4);
    cout << test;

    /*Chromosome obj(5, 10, 8);
    obj.numberOfBits = {0, 1, 0, 1, 0, 0, 1, 0};

    float number = obj.transformation();
    cout << number; */

    return 0;
}
