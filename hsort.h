#include <iostream>
#include <vector> 

template <typename T, typename Comparator >
void heapify(std::vector<T>& data, size_t loc, size_t effsize, Comparator& c ) {
	//checks for out of bounds
	 if ((2*loc+1) > effsize) {
	 	return;
	 }
	 size_t smallChild= 2*loc+1;
	 //sees which one is the best child
	 if (2*loc+2 <= effsize) {
	 	size_t rightChild= smallChild+ 1;
	 	if (c(data[rightChild],data[smallChild])) {
	 		smallChild= rightChild;
	 	}
	 }
	 //switches child and parent if child is better, then heapifies again
	 if (c(data[smallChild],data[loc])) {
	 	T temp= data[smallChild];
	 	data[smallChild]=data[loc];
	 	data[loc]= temp;
	 	heapify(data, smallChild, effsize, c);
	 }

}

template <typename T, typename Comparator>
//"pops" the data by swapping first and last, decreasing effective size, then heapifying
void heappop(std::vector<T>& data, size_t &effsize, Comparator& c) {
	T temp= data[0];
	data[0]= data[effsize];
	data[effsize]= temp;
	effsize= effsize -1;
	heapify(data, 0, effsize, c);
}

template <typename T, typename Comparator >
void hsort(std::vector<T>& data, Comparator c = Comparator()) {
	//nothing to do on empty
	if (data.size()== 0) {
		return;
	}
	//heapifies data originally
	size_t effsize= data.size()-1;
	for (int i= data.size()-1; i >=0; i--) {
		heapify(data, i, effsize, c);
	}
	//continues to pop in order to sort
	while (effsize > 0) {
		heappop(data, effsize, c);
	}
	//sorted backwards so we reverse
	for(unsigned int i=0; i < data.size()/2; ++i) {
		T temp= data[i];
		data[i]= data[data.size()-i-1];
		data[data.size()-i-1]= temp;
	}

}

