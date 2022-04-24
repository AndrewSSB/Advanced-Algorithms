#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct interval{
    int a;
    int b;

    friend istream&operator>>(istream & in, interval & obj){
        in >> obj.a;
        in >> obj.b;
        return in;
    }

    friend ostream&operator<<(ostream & out, interval & obj){
        printf("[%d, %d]", obj.a, obj.b);
        return out;
    }

    void setInterval(int _x, int _y){
        a = _x;
        b = _y;
    }

};

bool comparare(interval A, interval B){
    return A.a < B.a;// || A.b < B.b;
}

void calculateInterval(vector<interval> intervals, interval base){
    sort(intervals.begin(), intervals.end(), comparare);

    int a = base.a;
    int b = base.b;

    vector<int> positions;
    int poz = 0;

    while (poz < (int)intervals.size() && a < b){
        interval selectedInterv;
        selectedInterv.setInterval(INT_MAX, INT_MAX);
        int selectedPoz = INT_MAX;

        while (poz < (int)intervals.size() && intervals[poz].a <= a){
            if (selectedInterv.a == INT_MAX || selectedInterv.b == INT_MAX){
                selectedInterv = intervals[poz];
                selectedPoz = poz;
            }
            else if (intervals[poz].b <= selectedInterv.b){
                selectedInterv = intervals[poz];
                selectedPoz = poz;
            }
            poz++;
        }

        if (selectedInterv.a != INT_MAX && selectedInterv.b != INT_MAX && selectedPoz != INT_MAX){
            if (selectedInterv.b < a)
                break;
            positions.push_back(selectedPoz+1);
            a = selectedInterv.b;
        }
        else
            break;
    }

    if (positions.size() == 0 || intervals[positions[positions.size()-1]-1].b < base.b)
        cout << 0;
    else{
        cout << positions.size() << endl;
        for (int x : positions)
            cout << x << " ";
    }
}

int main()
{
    interval a;
    cin >> a;
    int _size;
    cin >> _size;
    vector<interval> intervals;
    for (int i = 0; i < _size; i++){
        interval aux;
        cin >> aux;
        if (aux.b < a.a || aux.a > a.b)
            continue;
        intervals.push_back(aux);
    }

    calculateInterval(intervals, a);

    return 0;
}
