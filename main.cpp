#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

vector <long long>& generareRandom(long long n, long long nmax) {
    vector <long long> *vect = new vector <long long>(n);
    vector <long long> &v = *vect;
    srand(time(NULL)); // random seed
    for (long long i = 0; i < n; ++i) {
        v[i] = rand();
        v[i] = v[i] << 32; // v[i] <<= 32;
        v[i] = v[i] + rand(); // v[i] += rand();
        v[i] = v[i] % (nmax + 1); // v[i] %= nmax + 1;
    }
    return v;
}

void afisare(vector <long long> &v) {
    long long n = v.size();
    for (long long i = 0; i < n; ++i) {
        cout << v[i] << " ";
    }
}

bool sortat(vector <long long> &v) {
    long long n = v.size();
    for (long long i = 1; i < n; ++i) {
        if (v[i] < v[i - 1]) {
            return false;
        }
    }
    return true;
}

// frecv[i] = de cate ori apare i in vectorul v
void countingSort(vector <long long> &v, long long nmax) {
    long long n = v.size();
    vector <long long> frecv(nmax + 1);
    for (long long i = 0; i < n; ++i) {
        ++frecv[v[i]];
    }
    long long k = 0;
    for (long long i = 0; i <= nmax; ++i) {
        for (long long j = 0; j < frecv[i]; ++j) {
            v[k++] = i;
        }
    }
}

void interclasare(vector <long long> &v, long long st, long long dr) {
    vector <long long> aux(dr - st + 1);
    long long mij = (st + dr) / 2, k = 0, i = st, j = mij + 1;
    while (i <= mij && j <= dr) {
        if (v[i] <= v[j]) {
            aux[k++] = v[i++];
        } else {
            aux[k++] = v[j++];
        }
    }
    while (i <= mij) {
        aux[k++] = v[i++];
    }
    while (j <= dr) {
        aux[k++] = v[j++];
    }
    for (long long i = st; i <= dr; ++i) {
        v[i] = aux[i - st];
    }
}

void mergeSort(vector <long long> &v, long long st, long long dr) {
    if (st >= dr) {
        return;
    }
    long long mij = (st + dr) / 2;
    mergeSort(v, st, mij);
    mergeSort(v, mij + 1, dr);
    interclasare(v, st, dr);
}

void insertionSort(vector <long long> &v, long long st, long long dr) {
    for (long long i = st + 1; i <= dr; ++i) {
        for (long long j = i; j > st && v[j] < v[j - 1]; --j) {
            swap(v[j], v[j - 1]);
        }
    }
}

void timSort(vector <long long> &v, long long st, long long dr) {
    if (dr - st < 32) {
        insertionSort(v, st, dr);
        return;
    }
    long long mij = (st + dr) / 2;
    timSort(v, st, mij);
    timSort(v, mij + 1, dr);
    interclasare(v, st, dr);
}

void shellSort(vector <long long> &v) {
    long long n = v.size();
    for (long long gap = n / 2; gap > 0; gap /= 2) {
        for (long long i = gap; i < n; ++i) {
            for (long long j = i; j >= gap && v[j - gap] > v[j]; j -= gap) {
                swap(v[j - gap], v[j]);
            }
        }
    }
}

void radixSort( vector <unsigned long long> &v, int baza, unsigned long long putere )
{
    vector <unsigned long long> cifre[baza];
    int n = v.size();
    for( int i = 0; i < n; ++i )
        cifre[ v[i] % putere / ( putere / baza ) ].push_back( v[i] );
    int k = 0;
    for( int i = 0; i < baza; ++i )
    {
        int m = cifre[i].size();
        for( int j = 0; j < m; ++j )
            v[k++] = cifre[i][j];
    }
    if( !sortat(v) )
        radixSort( v, baza, putere * baza );
}

int main() {
    long long n, nmax, teste;
    ifstream f("input.txt");
    f >> teste;
    for (long long t = 0; t < teste; ++t) {
        f >> n >> nmax;
        cout << "---------- Testul " << t + 1 << " ----------" << endl;

        vector <long long> v = generareRandom(n, nmax), cop = v;

        auto t1 = clock();
        countingSort(v, nmax);
        auto t2 = clock();
        cout << "Counting Sort: " << (float)(t2 - t1) / CLOCKS_PER_SEC << endl; // timpul in secunde

        v = cop;
        t1 = clock();
        timSort(v, 0, n - 1);
        t2 = clock();
        cout << "Tim Sort: " << (float)(t2 - t1) / CLOCKS_PER_SEC << endl; // timpul in secunde

        v = cop;
        t1 = clock();
        mergeSort(v, 0, n - 1);
        t2 = clock();
        cout << "Merge Sort: " << (float)(t2 - t1) / CLOCKS_PER_SEC << endl; // timpul in secunde

        v = cop;
        t1 = clock();
        shellSort(v);
        t2 = clock();
        cout << "Shell Sort: " << (float)(t2 - t1) / CLOCKS_PER_SEC << endl; // timpul in secunde

        v = cop;
        t1 = clock();
        radixSort(v, 2, 2);
        t2 = clock();
        cout << "Radix Sort: " << (float)(t2 - t1) / CLOCKS_PER_SEC << endl; // timpul in secunde

        cout << endl;
    }


    f.close();
    return 0;
}
