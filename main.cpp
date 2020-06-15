#include <iostream>
#include <cstdlib>
#include "LinkedList.h"

using namespace std;

int main() 
{
	LinkedList List;

	for (int i = 0; i < 7; i++) {
		List.pushBack(i);
	}

	for (int i = 0; i < List.size(); i++) {
		cout << "\n" << i << ":" << List[i];
	}

	List.reverse();

	List.remove(3);

	for (int i = 0; i < List.size(); i++) {
		cout << "\n" << i << ":" << List[i];
	}

	return 0;
}