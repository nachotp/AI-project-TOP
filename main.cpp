#include <iostream>
#include <stdio.h>

using namespace std;

int main(int argc, char const *argv[]){
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);
    
    int n, m;
    float tmax;
    scanf("%*s %d", &n);
    scanf("%*s %d", &m);
    scanf("%*s %f", &tmax);
    cout << n << " nodos " << m << " rutas en tiempo " << tmax << '\n';
    return 0;
}
