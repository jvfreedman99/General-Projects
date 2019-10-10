#include <iostream> 
#include <vector>
#include "hsort.h"
using namespace std;

int main () {
	vector<int> numbers;
	for (int i=1; i < 101; i++) {
		numbers.push_back(101-i);
	}
	hsort(numbers, less<int>());
	for (int i =0; i < 100; i++) {
		cout << numbers[i] << ' ';
		
	}
    cout << endl;

    vector<int> random;
    random.push_back(9);
    random.push_back(14);
    random.push_back(3);
    random.push_back(45);
    random.push_back(20);
    random.push_back(34);
    random.push_back(120);
    random.push_back(34);
    random.push_back(14);
    hsort(random, less<int>());
    for (int i=0; i < random.size(); i++) {
    	cout << random[i] << ' ';
    }
	return 0;
}