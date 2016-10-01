#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <cassert>
#include "csv_reader/csv_reader.h"
using namespace std;

/** Type representing attribute like true Windy **/
typedef size_t attribute;

/** Class representing a feature like Wind **/
class feature {
    public:
        feature(size_t id, size_t nb_attrs, bool is_class);
        size_t id;								/** Position int the table of data **/
        size_t nb_attrs;					/** Number of attributes of this feature **/
        bool is_class;
        bool active;
};

/** Class for a node in decision tree **/
class node {
    public:
        vector<node*> children;
        feature* feat;							/** Feature of split after this node **/
        attribute decision;						/** Decision taken by following this path **/
        double entropy;
        void classify(vector<vector<attribute>> data, vector<feature*> features);
};

/** Clas for Decision Tree **/
class DTClassifier{
	private:
		vector<vector<attribute>> generate_data();
		CSV_Reader* reader;
		vector<vector<string>> attrs_values;
		vector<vector<attribute>> data;
		vector<feature*> features;
		size_t rc;
	public:
		DTClassifier(string filename, string c);
		node& fit();
		
};

void print_vec(vector<attribute> as);

void print_tree(node* n);

double get_entropy(vector<vector<attribute>> data, feature& feat);

vector<vector<attribute>> search(vector<vector<attribute>> data, size_t col, size_t attr);

double mean(double* array, size_t size);
