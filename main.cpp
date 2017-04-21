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
int* 2optTSP(int** dmat, int* path, n, counter){
    int current_cost = compute_cost(dmat, path, n);
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
            //    cout << "moj stary koszt " << current_cost << ", to moj nowy koszt " << new_cost<< endl;
            //    cout << "miedzy " << path[i] << " i " << path[j]<< endl;
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
       }
    }while (found_something && counter > 0);
    return path;
}

int* 3optTSP(int** dmat, int* path, n, counter){
    int current_cost = compute_cost(dmat, path, n);
    char x;
    bool found_something;
    int flow, mini, minj, minc, new_cost;
    do {
       flow = 0;
       counter--;
       minc = current_cost;
       found_something = false;
       for (int i = 0; i < n-5; ++i) {
           for (int j = i+2; j < n-3; ++j) {
		   for(int k = j+2; k < n-1; ++k){
                	new_cost1 = current_cost
                        	- dmat[path[i]][path[i+1]] - dmat[path[j]][path[j+1]] - dmat[path[k]][path[k+1]]
                        	+ dmat[path[i]][path[j]] + dmat[path[i+1]][path[j+1]] + ///?????????????????????;
                	new_cost2 = current_cost
                        	- dmat[path[i]][path[i+1]] - dmat[path[j]][path[j+1]] - dmat[path[k]][path[k+1]]
                        	+ dmat[path[i]][path[j]] + dmat[path[i+1]][path[j+1]] + //??????????????????????;
                	if (new_cost1 < minc){
                    	    minc = new_cost1;
                    	    mini = i; minj = j; mink =k;
                    	    found_something = true;
		    	    flow = 1;
                	}
			if (new_cost2 < minc){
                    	    minc = new_cost2;
                    	    mini = i; minj = j; mink = k;
                    	    found_something = true;
		    	    flow = 2;
               		}
	   	}
           }
       }
       if (found_something){
           current_cost = minc;
	   //if flow == 1 bblah blah else halb halb halb
           reverse_path(mini+1, minj, path, n);
       }
    }while (found_something && counter > 0);
    return path;
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
    // 2opt time counter start
    int* 2optpath = 2optTSP(dmat, path, n, counter);
    // time counter stop
  
    for (int i = 0; i < n; ++i) {
   	cout<<2optpath[i]<< " -> ";
    }

    cout<<endl;
    // 3opt time counter start
    int* 3optpath = 3optTSP(dmat, path, n, counter);
    // time counter stop

    for (int i = 0; i < n; ++i) {
   	cout<<3optpath[i]<< " -> ";
    }
    cout<<endl;


    return 0;
}
