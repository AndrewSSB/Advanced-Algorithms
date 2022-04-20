#include <iterator>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct coords{
    int x;
    int y;

    friend istream&operator>>(istream& in, coords & obj){
        in >> obj.x;
        in >> obj.y;
        return in;
    }
};

string direction(coords A, coords B, coords C){
    int val = (A.x - B.x)*(B.y - C.y) - (A.y - B.y)*(B.x - C.x);
    if (val == 0) return "TOUCH";
    return (val < 0) ? "RIGHT" : "LEFT";
}

int main()
{
    int t;
    cout << "t: ";
    cin >> t;

    coords _coords[3];
    vector<string> aux;

    for (int i = 0; i < t; i++){
        cin >> _coords[0] >> _coords[1] >> _coords[2];
        aux.push_back(direction(_coords[0], _coords[1], _coords[2]));
    }

    for (auto x : aux)
        cout << x << "\n";
    return 0;
}