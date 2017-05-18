#include <iostream>
#include <string.h>
#include <limits>
using namespace std;
//DEBUG
string c;

void print_matrix(int** matrix, int n)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j= 0; j < n; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void array_printing(int *array, int n) {
    cout<<endl;
    int begin = array[0];
    do {
       cout << array[begin] << " -> ";
       begin = array[begin];
    }while (begin != array[0]);
    cout << endl;
}

int* copy_table(int* followers, int* res, int size) {
    for (size_t i = 0; i< size; i++)
    {
        res[i] = followers[i];
    }
    return res;
}

void delete_matrix(int** matrix, int n) {
    for (size_t i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int sum(int** dmat, int* followers, int nargs) {
    int suma = 0;
    int i = followers[0];
    do {
        suma += dmat[i][followers[i]];
        i = followers[i];
    }while (i != followers[0]);
    cout << endl;
    return suma;
}

void reverse_path (int i, int j, int* followers, int n) {
    if (followers[i] != j) {
        reverse_path(followers[i], j, followers, n);
    }
    followers[followers[i]] = i;
}

int* opt_2_TSP(int** dmat, int* followers, int n, int max_counter)
{
    int current_cost = sum(dmat, followers, n);
    bool found_something;
    int mini, minj, minc, new_cost, counter = 0;
    do {
       counter++;
       max_counter--;
       minc = current_cost;
       found_something = false;
     //  array_printing(followers, n);
       int begin_state = 0;
       int i = 0;
       do {
           int j = followers[followers[i]];
           while (followers[j] != i) {
               new_cost = current_cost
                       - dmat[i][followers[i]] - dmat[j][followers[j]]
                       + dmat[i][j] + dmat[followers[i]][followers[j]];
               if (new_cost < minc){
                   minc = new_cost;
                   mini = i; minj = j;
                   found_something = true;
               }
               j = followers[j];
           }
           /*
           cout<<i << " -> " << followers[i] << endl;
           array_printing(followers, n);
           cin>>c;
           */
           i = followers[i];

       } while (i != begin_state);
       for (int i = 0; i < n; i++) {
           int j = followers[followers[i]];
           while (followers[j] != i) {
               new_cost = current_cost
                       - dmat[i][followers[i]] - dmat[j][followers[j]]
                       + dmat[i][j] + dmat[followers[i]][followers[j]];
               if (new_cost < minc){
                   minc = new_cost;
                   mini = i; minj = j;
                   found_something = true;
               }
               j = followers[j];
           }
        //   cout<<i << " -> " << followers[i] << endl;
        //   array_printing(followers, n);
        //   cin>>c;
       }

       if (found_something){
     //    cout  << "FOUND SOMETHIG " << endl;
     //    cin >> c;
           current_cost = minc;
     //      array_printing(followers, n);
     //      cout<< "mini "<<mini<<endl<<"minj "<<minj<<endl;
           int fminj = followers[minj];

     //      cout << "PATH REVERSING BETWEEN: mini+1 " << followers[mini] << " i minj " << minj << ":" << endl;
           reverse_path(followers[mini], minj, followers, n);
     //      cout << followers[mini] << "->" << fminj <<endl;
     //      cout << mini << "->" << minj <<endl;
           followers[followers[mini]] = fminj;
           followers[mini] = minj;
     //      array_printing(followers, n);
     //      cout<< "Minimal cost now: " << minc << endl;
     //      cout << "Minimal computet cost " << sum(dmat, followers, n) << endl;
     //      cin>> c;
       }
    } while (found_something && max_counter > 0);
    cout<< "Optymalna sciezka w 2opt zostala znaleziona po " << counter << " petlach" << endl;
    return followers;
}

int* opt_3_TSP(int** dmat, int* followers, int n, int max_counter){
    int current_cost = sum(dmat, followers, n);
    bool found_something;
    int flow, mini, minj, minc, mink, new_cost1, new_cost2, counter = 0;
    do {
       flow = 0;
       counter++;
       max_counter--;
       minc = current_cost;
       found_something = false;
       for (int i = 0; i < n-5; ++i) {
           for (int j = i+2; j < n-3; ++j) {
           for(int k = j+2; k < n-1; ++k){
                    new_cost1 = current_cost
                                - dmat[i][followers[i]] - dmat[j][followers[j]] - dmat[k][followers[k]]
                                + dmat[i][followers[j]] + dmat[j][followers[k]] + dmat[k][followers[i]];
                    new_cost2 = current_cost
                                - dmat[i][followers[i]] - dmat[j][followers[j]] - dmat[k][followers[k]]
                                + dmat[i][j] + dmat[followers[j]][followers[k]] + dmat[k][followers[i]];
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
        cout << "mini " << mini << endl << "minj " << minj << endl << "mink " << mink << endl << "fmini " <<
               followers[mini] << endl << "fminj " << followers[minj] << endl << "fmink " << followers[mink] << endl << "ffmini" <<
               followers[followers[mini]] << endl << "ffminj " << followers[followers[minj]] << endl << "ffmink " << followers[followers[mink]] << endl;;

           if (flow == 2)
           {
               int followeri = minj;
               int followeri_p_1 = mink;
               int followerj_p_1 = followers[mink];

               cout << "PATH REVERSING BETWEEN: mini+1 " << followers[mini] << " i minj " << minj <<":" <<endl;
               reverse_path(followers[mini], minj, followers, n);

               cout << "PATH REVERSING BETWEEN: minj+1 " << followers[minj] << " i mink " << mink << ":" << endl;
               reverse_path(followers[minj], mink, followers, n);

               cout << followers[minj] << " -> " << followerj_p_1 << endl;
               cout << followers[mini] << " -> " << followeri_p_1 << endl;
               cout << mini << " -> " << followeri << endl;

               followers[followers[minj]] = followerj_p_1;
               followers[followers[mini]] = followeri_p_1;
               followers[mini] = followeri;
               }
           else {
               int followerj = followers[minj];
               cout << minj << " -> " << followers[mink] << endl;
               followers[minj] = followers[mink];
               cout << mink << " -> " << followers[mini] << endl;
               followers[mink] = followers[mini];
               cout << mini << " -> " << followerj << endl;
               followers[mini] = followerj;
           }
           array_printing(followers, n);
           cin>>c;
       }
    }while (found_something && max_counter > 0);
    cout<< "Optymalna sciezka w 3opt zostala znaleziona po " << counter << " petlach" << endl;
    return followers;
}


int main(int argc, char *argv[])
{

    int n, max_counter;
    cout<< "ile miast i ile maksymalnie iteracji" << endl;
    cin >> n >> max_counter;

    int** dmat = new int*[n];
    for (int i = 0; i < n; ++i) {
        dmat[i] = new int[n];
    }

    int* followers = new int[n];

    for (int i = 0; i < n; ++i) {
        //cout << "Czytam wiersz " << i<< endl;
        for (int j = 0; j < n; ++j) {
            cin >> dmat[i][j];
        }
        followers[i] = (i+1)%n;
    }

    //////////////////////


    // 2opt time max_counter start
    int copy_followers[100000];
    copy_table(followers, copy_followers, n);

    //Find path
    int* opt_2_path = opt_2_TSP(dmat, copy_followers, n, max_counter);
    // time max_counter stop

    cout<<"optimal path for 2-opt algorithm: "<<endl;
    array_printing(opt_2_path, n);
    cout<<endl<<"Size of path: " << sum(dmat, opt_2_path, n) << endl;

    // TU JEST 3-opt. Narazie nie zrobiony.
    /*
    // 3opt time max_counter start
    copy_table(followers, copy_followers, n);
    int* opt_3_path = opt_3_TSP(dmat, copy_followers, n, max_counter);
    // time max_counter stop

    cout<<"optimal path for 3-opt algorithm: "<<endl;
    for (int i = 0; i < n; ++i) {
        cout<<opt_3_path[i]<< " -> ";
    }
    cout<<endl<<"Size of path: " << sum(dmat, opt_3_path, n) << endl;
*/

    delete_matrix(dmat, n);
    delete[] followers;
    return 0;

}
