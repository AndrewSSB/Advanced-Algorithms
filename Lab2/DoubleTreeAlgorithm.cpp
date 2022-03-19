#include <cstdio> //Double-tree algorithm
#include <cstring>
#include <vector>
#include <algorithm>
#define MAX 100

using namespace std;

FILE *f, *g;
struct tree
{
    int x, y; //muchie de tipul (x,y) si (y,x) daca graful este neorientat
    int index;
    float cost;
} v[MAX];
int nr_orase,nr_noduri,start=0,viz[MAX];
float c;

vector<int> adj[MAX];
vector<int> vec;
int vis[MAX]; //vectorul pentru vizita din Euler Tour
int Euler[2*MAX]; //vectorul pentru Euler Tour

void citire()
{
    int i,x,y;
    double c;
    fscanf(f,"%d%d",&nr_orase,&nr_noduri); //nr_orase muchii
    for (i=1;i<=nr_orase;++i)
    {
        fscanf(f,"%d%d%f",&v[i].x,&v[i].y,&v[i].cost);
        v[i].index=i;
    }
}

void add_edge(int u, int v) //adaugarea unei muchii
{
    adj[u].push_back(v);
    adj[v].push_back(u);
}

//1. Minimum spanning tree
void kruskal()
{
    /*
    plecam cu costul 0, alegem muchiile
    sortate in functie de cost
    */
    int i,j,k;
    c=0;
    i=1; //plecam cu prima muchie (v[1].x,v[1].y)
    for(k=1;k<nr_orase;++k)
    {
        while(viz[v[i].x]==viz[v[i].y]&&viz[v[i].x]) //daca ambele capete ale muchiei de pe pozitia i au fost vizitate
            ++i; //crestem i-ul
        if (v[i].x&&v[i].y)
        {
            c+=v[i].cost; //adaugam la cost, cost-ul muchiei de pe pozitia in care cele doua capete ale muchiei nu au fost vizitate (macar unul dintre ele)
            //fprintf(g,"%d %d\n",v[i].x,v[i].y); //afisam cele doua capete ale muchiei gasite nevizitata

            //2. dublarea arborelui de acoperire de cost minim (introducem nodurile intr-un nou arbore)
            add_edge(v[i].x,v[i].y);
            if (!start)
                start=v[i].x; //root
        }
        if(viz[v[i].x]+viz[v[i].y]==0) //daca amandoua nu au fost vizitate
            viz[v[i].x]=viz[v[i].y]=v[i].x; //le initializam vizita ambelor ca fiind capatul v[i].x
        else
            if(viz[v[i].x]*viz[v[i].y]==0) //daca cel putin unul dintre ele a fost vizitat
            viz[v[i].x]=viz[v[i].y]=viz[v[i].x]+viz[v[i].y]; //le initializam vizita ambleor ca fiind suma viziarilor ambelor capete
        else
        {//daca amandoua au fost vizitate
            for(j=1;j<=nr_orase;++j)
                if(viz[j]==viz[v[i].x]&&j!=v[i].x)
                    viz[j]=viz[v[i].y];
            viz[v[i].x]=viz[v[i].y];
        }
        ++i;
    }
    fprintf(g,"%.2f\n",c);
}

//4. c.
//Functia care pastreaza Euler Tour al arborelui
void eulerTree(int u, int &index)
{
    vis[u]=1;
    Euler[index++]=u;
    for (auto it: adj[u])
    {
        if (!vis[it])
        {
            eulerTree(it, index);
            Euler[index++]=u;
        }
    }
}

//Functie care afiseaza Euler Tour al arborelui
void printEulerTour(int root)
{
    int index=0;
    eulerTree(root,index);
    for (int i=0;i<(2*nr_noduri-1);++i)
            {
                fprintf(g,"%d ",Euler[i]);
                vec.push_back(Euler[i]);
            }

    fprintf(g,"\n");
}

//5. Remove duplicates
void remove_duplicate()
{
    vector<int>::iterator ip;
    ip = std::unique(vec.begin(), vec.begin()+nr_noduri);
    vec.resize(std::distance(vec.begin(), ip));
    for (ip=vec.begin();ip!=vec.end();++ip)
        fprintf (g,"%d ",*ip);
    fprintf (g,"\n");
}
int main()
{
    f=fopen("ex1_pct6.in","r");
    g=fopen("date.out","w");
    citire();
    memset(viz,0,sizeof(viz));
    kruskal();
    printEulerTour(start);
    remove_duplicate(); //lista ramasa constituie solutia aprox. a TSP
    return 0;
}
