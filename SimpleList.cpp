#include "SimpleList.h"
#include <iostream>
#include <type_traits>
using namespace std;

template <class T>
void destroy(T a);
template <class T>
void destroy(T *a);
template <class T>
void DeleteFuncs(T *b);


template<class T>
void destroy(T a){
}

template<class T>
void destroy(T* a){
  delete a;
}

template<class T>
void DeleteFuncs(T *b){
  if(is_pointer<T>::value){
    for(int i = 0;i<10;i++){
      destroy(b[i]);
    }
  }else{
    destroy(b);
  }
}


template <class T>
SimpleList<T>::SimpleList(){
  this->numElements=0;
  this->elements=new T[CAPACITY];
}

template <class T>
SimpleList<T>::~SimpleList(){
  if(is_pointer<T>::value){
    for(int i = 0;i<10;i++){
      destroy(elements[i]);
    }
  }else{
    delete [] elements;
  }
  //DeleteFuncs(elements);
  //delete[] elements;
}

template <class T>
T SimpleList<T>::at(int index) const throw (InvalidIndexException){
  if(index>=numElements||index<0){
    throw InvalidIndexException();
  }
  return elements[index];
}

template <class T>
bool SimpleList<T>::empty() const {
  if(this->numElements==0){
    return true;
  }
  return false;
}

template <class T>
T SimpleList<T>::first() const throw (EmptyListException){
  if(empty()){
    throw EmptyListException();
  }
  return at(0);
}

template <class T>
T SimpleList<T>::last() const throw (EmptyListException){
  if(empty()){
    throw EmptyListException();
  }
  return at(numElements-1);
}

template <class T>
int SimpleList<T>::getNumElements() const{
  return numElements;
}

template <class T>
void SimpleList<T>::insert(T item) throw (FullListException){
  if(numElements>=CAPACITY){
    //elements[numElements]=item;
    throw FullListException();
  }
  elements[numElements]=item;
  numElements++;
}

template <class T>
void SimpleList<T>::remove(int index) throw (InvalidIndexException, EmptyListException){
  if(empty()){
    throw EmptyListException();
  }
  if(index>=numElements||index<0){
    throw InvalidIndexException();
  }
  T *temp=new T[CAPACITY];
  while(index<numElements-1){
    elements[index]=elements[index+1];
    index+=1;
  }
  numElements-=1;
  for(int i=0;i<=numElements-1;i++){
    temp[i]=elements[i];
  }
  elements=temp;
  //DeleteFuncs(temp);

}
