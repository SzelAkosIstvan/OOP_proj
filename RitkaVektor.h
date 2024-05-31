#pragma once
#include "Vektor.h"
#include <cmath>
#include <iostream>
using namespace std;

template < class T >
struct nonZero
{
	T elem;
	int index;
};


template<class T>
class RitkaVektor
{
public:

	operator Vektor<T>();
	RitkaVektor();
	RitkaVektor(int dim);
	RitkaVektor(T *t, int dim);
	RitkaVektor(const RitkaVektor&);
    ~RitkaVektor();

	RitkaVektor operator+(const RitkaVektor&);
	RitkaVektor operator-(const RitkaVektor&);
    RitkaVektor& operator=(const RitkaVektor&);
	double operator*(const RitkaVektor&);
	double operator~();
	double operator%(const RitkaVektor&);
	T      operator[](int) const;
    void kiir() const;
    void dimCheck(const RitkaVektor&);


private:


	nonZero <T> * vektor;
	int nZeroDim;
	int dim;
};

template<class T>
RitkaVektor<T>::RitkaVektor(): dim(0), nZeroDim(0) {}

template<class T>
RitkaVektor<T>::RitkaVektor(int dim): dim(dim), nZeroDim(1) {
    vektor = new nonZero<T>[dim];
    vektor[0].index=0;
    vektor[0].elem=1;
}

template<class T>
RitkaVektor<T>::RitkaVektor(T* t, int dim): dim(dim), nZeroDim(0) {
    int szamlalo = 0;
    vektor = new nonZero<T>[dim];
    for(int i=0;i<dim;i++)
    {
        if(t[i])
        {
            vektor[szamlalo].index = i;
            vektor[szamlalo].elem = t[i];
            szamlalo++;
            nZeroDim++;
        }
    }
}

template<class T>
RitkaVektor<T>::RitkaVektor(const RitkaVektor<T>& other) {
    dim = other.dim;
    vektor = new nonZero<T>[dim];
    for(int i=0;i<dim;i++)
    {
        vektor[i].elem = other.vektor[i].elem;
        vektor[i].index = other.vektor[i].index;
    }
    nZeroDim = other.nZeroDim;

}

template<class T>
RitkaVektor<T>::~RitkaVektor() {
    dim = 0;
    nZeroDim = 0;
    delete[] vektor;
}

template<class T>
void RitkaVektor<T>::kiir()const
{
    for (int i = 0; i < nZeroDim; i++)
    {
        cout<<vektor[i].index<<": "<<vektor[i].elem<<"\t";
    }
    cout << endl;
}

template<class T>
void RitkaVektor<T>::dimCheck(const RitkaVektor<T>& other) {
    if(dim!=other.dim)
    {
        throw "Nem egyezik meg a ket vektor merete!";
    }
}

template<class T>
RitkaVektor<T>& RitkaVektor<T>::operator=(const RitkaVektor<T>& other) {
    dimCheck(other);
    nZeroDim=other.nZeroDim;
    for(int i=0;i<nZeroDim;i++)
    {
        vektor[i].elem = other.vektor[i].elem;
        vektor[i].index = other.vektor[i].index;
    }
    return *this;
}

template<class T>
RitkaVektor<T> RitkaVektor<T>::operator+(const RitkaVektor<T>& other) {
    dimCheck(other);
    RitkaVektor<T>seged(dim);
    int i = 0, j = 0, k = 0;
    while (i < nZeroDim && j < other.nZeroDim)
    {
        if (vektor[i].index < other.vektor[j].index)
        {
            seged.vektor[k].index = vektor[i].index;
            seged.vektor[k].elem = vektor[i].elem;
            i++; k++;
        }
        else if(vektor[i].index > other.vektor[j].index)
        {
            seged.vektor[k].index = other.vektor[j].index;
            seged.vektor[k].elem = other.vektor[j].elem;
            j++; k++;
        }
        else
        {
            T aux = 0;
            aux = vektor[i].elem + other.vektor[j].elem;
            seged.vektor[k].elem = aux;
            seged.vektor[k].index = vektor[i].index;
            i++; j++; k++;
        }
    }
    seged.nZeroDim = k;
    return seged;
}

template<class T>
RitkaVektor<T> RitkaVektor<T>::operator-(const RitkaVektor<T>& other) {
    dimCheck(other);
    RitkaVektor<T>seged(dim);
    int i = 0, j = 0, k = 0;
    while (i < nZeroDim && j < other.nZeroDim)
    {
        if (vektor[i].index < other.vektor[j].index)
        {
            seged.vektor[k].index = vektor[i].index;
            seged.vektor[k].elem = vektor[i].elem;
            i++; k++;
        }
        else if (vektor[i].index > other.vektor[j].index)
        {
            seged.vektor[k].index = other.vektor[j].index;
            seged.vektor[k].elem = -other.vektor[j].elem;
            j++; k++;
        }
        else
        {
            T aux = 0;
            aux = vektor[i].elem - other.vektor[j].elem;
            seged.vektor[k].elem = aux;
            seged.vektor[k].index = vektor[i].index;
            i++; j++; k++;
        }
    }
    seged.nZeroDim = k;
    return seged;
}

template<class T>
T RitkaVektor<T>::operator [](int i) const {
    if (i >= dim)
    {
        throw "Ilyen indexu elem nem talalhato";
    }
    else
    {
        if (i >= nZeroDim)
        {
            return 0;
        }
        else
        {
            return vektor[i].elem;
        }
    }
}

template<class T>
double RitkaVektor<T>::operator*(const RitkaVektor<T>& other) {
    dimCheck(other);
    int i = 0, j = 0;
    double eredmeny = 0;
    while (i < nZeroDim && j < other.nZeroDim)
    {
        if (vektor[i].index < other.vektor[j].index) {i++;}
        else if (vektor[i].index > other.vektor[j].index) {j++;}
        else
        {
            eredmeny += vektor[i].elem * other.vektor[j].elem;
            i++; j++;
        }
    }
    return eredmeny;
}

template<class T>
double RitkaVektor<T>::operator~() {
    double norma=0;
    for(int i=0;i<nZeroDim;i++)
    {
        norma += vektor[i].elem*vektor[i].elem;
    }
    return sqrt(norma);
}

template<class T>
double RitkaVektor<T>::operator%(const RitkaVektor<T>& other) {
    dimCheck(other);
    int i = 0, j = 0;
    double tavolsag = 0;
    while (i < nZeroDim && j < other.nZeroDim)
    {
        if (vektor[i].index < other.vektor[j].index) {i++;}
        else if (vektor[i].index > other.vektor[j].index) {j++;}
        else
        {
            double kivonas = vektor[i].elem - other.vektor[j].elem;
            tavolsag += kivonas * kivonas;
            i++; j++;
        }
    }
    return sqrt(tavolsag);
}

template<class T>
RitkaVektor<T>::operator Vektor<T>() {
    T* seged = new T[dim];
    for (int i = 0; i < dim; i++)
    {
        seged[i] = 0;
    }
    for (int i = 0; i < nZeroDim; i++)
    {
        seged[vektor[i].index] = vektor[i].elem;
    }
    Vektor<int>t(seged, dim);
    delete[]seged;
    return t;
}