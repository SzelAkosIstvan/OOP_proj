#pragma once
#include <iostream>
#include <cmath>
using namespace std;
template<class T>
class RitkaVektor;

template<class T>
class Vektor
{
public:
	Vektor();
	Vektor(int dim);
	Vektor(T *t, int dim);
	Vektor(const Vektor&);
    ~Vektor();

	Vektor operator+(const Vektor&);
	Vektor operator-(const Vektor&);
    Vektor& operator=(const Vektor&);
	double operator*(const Vektor&);
	double operator~();
	double operator%(const Vektor&);
	T      operator[](int) const;
	operator RitkaVektor<T>();
    void kiir() const;
    void dimCheck(const Vektor&);

private:
	T*  m_t;
	int m_dim;
};

template<class T>
Vektor<T>::Vektor(): m_dim(0) {}

template<class T>
Vektor<T>::Vektor(int dim): m_dim(dim) {
    m_t = new T[m_dim];
    for(int i=0;i<m_dim;i++)
    {
        m_t[i]=1;
    }
}

template<class T>
Vektor<T>::Vektor(T *t, int dim): m_dim(dim) {
    m_t = new T[m_dim];
    for(int i=0;i<m_dim;i++)
    {
        m_t[i] = t[i];
    }
}

template<class T>
Vektor<T>::Vektor(const Vektor<T>& other) {
    m_dim = other.m_dim;
    m_t = new T[m_dim];
    for(int i=0;i<m_dim;i++)
    {
        m_t[i] = other.m_t[i];
    }
}

template<class T>
Vektor<T>::~Vektor() {
    m_dim = 0;
    delete[] m_t;
}

template<class T>
void Vektor<T>::kiir() const {
    for(int i=0;i<m_dim;i++)
    {
        cout<<m_t[i]<<"\t";
    }
    cout<<endl;
}

template<class T>
void Vektor<T>::dimCheck(const Vektor<T>& other) {
    if(m_dim!=other.m_dim)
    {
        throw "Nem egyezik meg a ket vektor merete!";
    }
}

template<class T>
Vektor<T>& Vektor<T>::operator=(const Vektor& other)
{
    dimCheck(other);
    for (int i=0;i<m_dim;i++)
    {
        m_t[i] = other.m_t[i];
    }
    return *this;
}

template <class T>
Vektor<T> Vektor<T>::operator+(const Vektor& other)
{
    dimCheck(other);
    T* seged;
    seged = new T[m_dim];
    for (int i = 0; i < m_dim; ++i)
    {
        seged[i] = m_t[i] + other.m_t[i];
    }
    Vektor uj(seged, m_dim);
    delete[] seged;
    return uj;
}

template <class T>
Vektor<T> Vektor<T>::operator-(const Vektor& other)
{
    dimCheck(other);
    Vektor<T>seged(m_dim);
    for (int i = 0; i < m_dim; ++i)
    {
        seged.m_t[i] = m_t[i] - other.m_t[i];
    }
    return seged;
}

template <class T>
double Vektor<T>::operator*(const Vektor& other)
{
    dimCheck(other);
    double s = 0;
    for (int i = 0; i < m_dim; ++i)
    {
        s += (m_t[i] * other.m_t[i]);
    }
    return s;
}

template <class T>
double Vektor<T>::operator~()
{
    double norma = 0;
    for (int i = 0; i < m_dim; ++i)
    {
        norma += (m_t[i] * m_t[i]);
    }
    return sqrt(norma);
}

template <class T>
double Vektor<T>::operator%(const Vektor& other)
{
    dimCheck(other);
    double tavolsag = 0;
    for (int i = 0; i < m_dim; ++i)
    {
        double seged = m_t[i] - other.m_t[i];
        tavolsag += seged * seged;
    }
    return sqrt(tavolsag);
}

template <class T>
T Vektor<T>::operator [](int i) const
{
    if (i >= m_dim)
    {
        throw "Ilyen indexu elem nem talalhato";
    }
    else
    {
        return m_t[i];
    }
}

template <class T>
Vektor<T>::operator RitkaVektor<T>()
{
    RitkaVektor<T>v(m_t, m_dim);
    return v;
}