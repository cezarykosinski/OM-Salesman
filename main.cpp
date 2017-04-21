#include <QCoreApplication>
#include <iostream>

using namespace std;

int dist(int** dmat, int a, int b)
{
    return dmat[a][b];
}
int compute_cost(int** dmat, int* path, int n) {
    int cost = 0;
    for (int i = 1; i < n+1; ++i) {
        cost += dmat[path[(i-1)%n]][path[i%n]];
    }
    return cost;
}

void reverse_path (int i, int j, int* path, int n) {
    while (i < j) {
        swap(path[i], path[j]);
        i++;
        j--;
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    int n, counter;
    cout<< "ile i ile razy" << endl;
    cin >> n >> counter;

    int** dmat = new int*[n];
    for (int i = 0; i < n; ++i) {
        dmat[i] = new int[n];
    }
    int* path = new int[n];

    for (int i = 0; i < n; ++i) {
        cout << "Czytam wiersz " << i<< endl;
        for (int j = 0; j < n; ++j) {
            cin >> dmat[i][j];
        }
        path[i] = i;
    }
    cout<<"Se poczytalem, tera do roboty :)" << endl;

    int current_cost = compute_cost(dmat, path, n);
    cout<< current_cost<< "WTF" <<endl;
    char x;
    bool found_something;
    int mini, minj, minc, new_cost;
    do {
       counter--;
       minc = current_cost;
       cout<< "counter " << counter << endl;
       found_something = false;
       for (int i = 0; i < n-2; ++i) {
           for (int j = i+2; j < n-1; ++j) {
                new_cost = current_cost
                        - dmat[path[i]][path[i+1]] - dmat[path[j]][path[j+1]]
                        + dmat[path[i]][path[j]] + dmat[path[i+1]][path[j+1]];
                cout << "moj stary koszt " << current_cost << ", to moj nowy koszt " << new_cost<< endl;
                cout << "miedzy " << path[i] << " i " << path[j]<< endl;
            //    cin>>x;
                if (new_cost < minc){
                    minc = new_cost;
                    mini = i; minj = j;
                    found_something = true;
                }
           }
       }
       if (found_something){
           current_cost = minc;
           reverse_path(mini+1, minj, path, n);
           //swap(path[mini],path[minj+1]);
       }
       for (int i = 0; i < n; ++i) {
           cout<<path[i]<< " -> ";
       }
       cin>>x;
       cout<<endl;
    }while (found_something && counter > 0);
    return 0;
}
