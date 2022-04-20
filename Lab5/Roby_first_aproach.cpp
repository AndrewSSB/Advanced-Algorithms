#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class coords{
public:
    int x;
    int y;
public:
    coords(int _x, int _y):x(_x), y(_y){}
    coords():x(0), y(0){}

    coords&operator=(const coords &obj);

    friend istream&operator>>(istream &in, coords &obj);
    friend ostream&operator<<(ostream &out, const coords &obj);
};

coords& coords::operator=(const coords & obj){
    if (this != &obj){
        this->x = obj.x;
        this->y = obj.y;
    }
    return *this;
}

istream&operator>>(istream &in, coords &obj){
    cout << "X: "; in >> obj.x;
    cout << "Y: "; in >> obj.y;
    return in;
}

ostream&operator<<(ostream &out, const coords &obj){
    printf("(%d, %d)", obj.x, obj.y);
    return out;
}

int determinant(coords A, coords B, coords C){
    return (A.x - B.x)*(B.y - C.y) - (A.y - B.y)*(B.x - C.x);
}

void first2Coords(coords A, coords B, int &_left, int &_right, int&_coliniar){
    if ((A.x < B.x && A.y < B.y) || (A.x > B.x && A.y > B.y)){
        _left++;
    }
    if ((A.x > B.x && A.y < B.y) || (A.x < B.x && A.y > B.y)){
        _right++;
    }
    if ((A.x == B.x) || (A.y == B.y)){
        _coliniar++;
    }
}

void Turns(vector<coords> _coords){
    //pentru primele 2 coordonate trebuie sa hardcodez, dupa ma folosesc de determinant

    if (_coords.size() < 3)
        return;

    int turnLeft = 0;
    int turnRight = 0;
    int coliniar = 0;

    first2Coords(_coords[0], _coords[1], turnLeft, turnRight, coliniar);

    for (int i = 1; i < int(_coords.size()) - 1; i++){
        int value = determinant(_coords[i-1], _coords[i], _coords[i+1]);
        if (value == 0){
            coliniar++;
        }
        if (value < 0){
            turnRight++;
        }
        if (value > 0){
            turnLeft++;
        }
    }

    cout << turnLeft << " " << turnRight << " " << coliniar;
}

int main()
{
    //Ex 1:
    /*coords P, Q, R;
    cin >> P;
    cin >> Q;
    cin >> R;
    vector<coords> _coords;
    _coords.push_back(P);
    _coords.push_back(Q);
    _coords.push_back(R);

    Turns(_coords);
    */

    //Ex 2:
    vector<coords> _coords;
    int _size;
    cin >> _size;
    for (int i = 0; i < _size; i++){
        int x, y;
        cin >> x;
        cin >> y;
        coords _aux(x, y);
        _coords.push_back(_aux);
    }

    Turns(_coords);

    return 0;
}
