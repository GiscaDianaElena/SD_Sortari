#include <iostream>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include <algorithm>
#include <vector>

using namespace std;

vector <unsigned long long> aux;

void merge( vector <unsigned long long> &v, int st, int dr)
{
    aux.resize(dr - st + 1);
    int mij = (st + dr) / 2, k = 0;
    int i = st, j = mj + 1;
    while(i <= mij && j <= dr)
      if( v[i] <= v[j] )
        aux[k++] = v[i++];
      else
        aux[k++] = v[j++]
    while( i <= mij)
      aux[k++] = v[i++];
    while( j <= dr )
      aux[k++] = v[j++];
    for( int i = st; i <= dr; i++)
      v[i] = aux[ i - st ];
}

void mergeSort( vector <unsigned long long> &v, int st, int dr)
{
    if( st >= dr )
      return;
    int mij = ( st + dr ) / 2;
    mergeSort( v, st, mij );
    mergeSort( v, mij + 1, dr );
    mergeSort( v, st, dr );
}
