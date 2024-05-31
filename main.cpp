#include <iostream>
#include "RitkaVektor.h"
#include "Vektor.h"
using namespace std;
int main() {
    int elso[3] = { 1,2,3 };
    int masodik[3] = { 4,0,6 };
    int harmadik[2] = { 1, 0};
    Vektor<int> vek1(elso, 3), vek2(masodik,3), vekplusz(harmadik,2);
    RitkaVektor<int> vek3(elso, 3), vek4(masodik, 3);
    double s;
    try
    {
        vek1.kiir();
        vek1 = vek1-vek2;//vekplusz
        vek1.kiir();
        vek1 = vek1+vek2;
        (vek1+vek2).kiir();
        cout<<"vek2[1]: "<<vek2[1]<<endl;
        s = vek1 % vek2;
        cout<<"vek1 tavolsaga vek2-tol: "<<s<<endl;
        s = ~vek1;
        cout<<"norma: "<<s<<endl;

        vek4.kiir();
        vek3 = vek3+vek4;
        vek3.kiir();
        vek3 = vek3-vek4;
        (vek3-vek4).kiir();
        cout<<"vek4[1]: "<<vek4[1]<<endl;//vek4[5]
        s = vek3 % vek4;
        cout<<"vek3 tavolsaga vek4-tol: "<<s<<endl;
        s = ~vek3;
        cout<<"norma: "<<s<<endl;
    }
    catch (const char* hibaUzenet)
    {
        cout<<hibaUzenet<<endl;
    }
    return 0;
}
