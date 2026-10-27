// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
      size = v.size;
      pMem = new T[size];
      for (int i = 0; i < size;++i)
          pMem[i] = v.pMem[i];
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
  }
  ~TDynamicVector()
  {
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (*this == other) { return *this; }
      else
      {
          size = other.size;
          vec = new T[size];
          for (int i = 0; i < size;++i)
          {
              pMem[i] = other.pMem[i];
          }
          return *this;
      }
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      return pMem[ind]
  }
  const T& operator[](size_t ind) const
  {
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind >= size)
      {
          std::cout << "incorrect index" << endl;
      }
      else {
          return pMem[ind];
      }
  }
  const T& at(size_t ind) const
  {
      if (ind >= size)
      {
          std::cout << "incorrect index" << endl;
      }
      else {
          return pMem[ind];
      }
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (size != v.size)
          return false;
      else
      {
          for (int i = 0; i < size;i++)
          {
              if (pMem[i] != v[i])
                  return false;
          }
      }
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return!(pMem == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector<T> tmp(*this);
      for (int i = 0; i < size; ++i)
      {
          tmp.pMem[i] += val;
      }
      return tmp;
  }
  TDynamicVector operator-(T val)
  {
      TDynamicVector<T> tmp(*this);
      for (int i = 0; i < size; ++i)
      {
          tmp.pMem[i] -= val;
      }
      return tmp;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector<T> tmp(*this);
      for (int i = 0; i < size; ++i)
      {
          tmp.pMem[i] *= val;
      }
      return tmp;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (size != v.size)
          throw std::cout << "size!" << endl;
      else:
      {
          TDynamicVector <T> tmp(*this);
          for (int i = 0;i < size;++i)
          {
              tmp[i] += v[i];
          }
      }
      return tmp;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (size != v.size)
          throw std::cout << "size!" << endl;
      else:
      {
          TDynamicVector <T> tmp(*this);
          for (int i = 0;i < size;++i)
          {
              tmp[i] -= v[i];
          }
      }
      return tmp;
  }
  T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  {
      if (size != v.size)
          throw std::cout << "size" << endl;
      else
      {
          TDynamicVector <T> tmp(*this);
          for (int i = 0; i < size;i++)
              tmp += pMem[i] * v.pMem[i];
      }
      return tmp;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if(*this == other) {return true}
      if(sz!=other.sz) {return false}
      for (int i = 0; i < sz;i++)
      {
          for (int j = 0; j < sz;j++)
          {
              if (pMem[i][j] != other[i][j])
                  return false;
          }
      }
      return true;
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      TDynamicMatrix<T> tmp(*this);
      for (int i = 0; i < sz; ++i)
      {
          tmp[i] = pMem[i] * val;
      }
      return tmp;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      TDynamicVector<T> tmp(sz);
      for (int i = 0; i < sz;++i)
          tmp[i] = pMem[i] * other;
      return tmp;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      TDynamicMatrix<T>tmp(sz);
      for (int i = 0; i < sz;++i)
          tmp[i] = pMem[i] + other[i];
      return tmp;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      TDynamicMatrix<T>tmp(sz);
      for (int i = 0; i < sz;++i)
          tmp[i] = pMem[i] - other[i];
      return tmp;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      TDynamicMatrix<T> tmp(sz);
      T Sum;
      for (int i = 0; i < sz;i++)
      {
          for (int j = 0; j < sz;++j)
          {
              Sum = 0;
              for (int k = 0; k < sz; k++)
              {
                  sum+=pMem[i][k]*other[k][j]
              }
              tmp[i] = sum;
          }
      }
      return tmp;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++)
          istr >> v.pMem[i];
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++)
          ostr << v.pMem[i] << ' ';
      return ostr;
  }
};

#endif
