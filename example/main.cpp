#include <iostream>
#include "../DT.h"


int main(){
	try{
	DTClassifier* classifier = new DTClassifier("data.csv", "Class");
	node tree = classifier->fit();
	print_tree(&tree);
	cout << endl;
	} catch(const char* e){
		cout << e << endl;
	} 
	return 0;
}