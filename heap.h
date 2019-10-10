#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
 public:
  /// Constructs an m-ary heap for any m >= 2
  Heap(int m, PComparator c = PComparator());

  /// Destructor as needed
  ~Heap();

  /// Adds an item
  void push(const T& item);

  /// returns the element at the top of the heap 
  ///  max (if max-heap) or min (if min-heap)
  T const & top() const;

  /// Removes the top element
  void pop();

  /// returns true if the heap is empty
  bool empty() const;

 private:
  std::vector<T> heapV;
  size_t m_;
  PComparator com_;
  void trickleDown(size_t loc);
  void trickleUp(size_t loc);

  /// Add whatever helper functions and data members you need below




};

//constructor with given m and comparator
template <typename T, typename PComparator >
Heap<T,PComparator>::Heap(int m, PComparator c) 
: m_(m), com_(c)
{

}
//destructor
template <typename T, typename PComparator >
Heap<T,PComparator>::~Heap() {

}
// Add implementation of member functions here
template <typename T, typename PComparator >
void Heap<T,PComparator>::trickleDown(size_t loc) {
   if ((m_*loc+1) > heapV.size()-1) {
      return;
   }
   // very similar to heapify but for m children
   size_t smallChild= m_*loc+1;
   size_t temp= smallChild;
   for (size_t i=2; i < m_+1; ++i) {
      if (m_*loc+i <= heapV.size()-1) {
        size_t nextChild= temp+ i-1;
        if (com_(heapV[nextChild], heapV[smallChild])) {
           smallChild= nextChild;
        }
      }
    }
   if (com_(heapV[smallChild], heapV[loc])) {
      T temp2= heapV[smallChild];
      heapV[smallChild]=heapV[loc];
      heapV[loc]= temp2;
      trickleDown(smallChild);
   }
}

template <typename T, typename PComparator >
void Heap<T,PComparator>::trickleUp(size_t loc) {
    if (loc == 0) {
      return;
    }
    //switch with parent while better than  them
    int parent= (loc-1)/m_;
    while (parent >= 0 && com_(heapV[loc], heapV[parent])) {
      T temp= heapV[parent];
      heapV[parent]= heapV[loc];
      heapV[loc]= temp;
      loc= parent;
      parent= (loc-1)/m_;
    }
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    throw std::logic_error("can't top an empty heap");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return heapV[0];


}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    throw std::logic_error("can't pop an empty heap");
  }
  //swap first and last then pop the back and trickledown
  T temp= heapV[0];
  heapV[0]= heapV[heapV.size()-1];
  heapV[heapV.size()-1]=temp;
  heapV.pop_back();
  if (!empty()) {
    trickleDown(0);
  }


}

template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item) {
  //just insert and then sort 
  heapV.push_back(item);
  trickleUp(heapV.size()-1);
}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const {
    if (heapV.size() == 0) {
      return true;
    }
    else { return false;}
}
#endif

