#include <iostream>
#include <string>
#include <cmath>
using namespace std;


/** Type representing attribute like true Windy **/
typedef size_t attribute;

/** Class representing a feature like Wind **/
class feature {
    private:
        size_t id;
        size_t nb_attrs;
    public:
        feature(size_t id, size_t nb_attrs);
        feature(size_t id);
        void add_attribute();
};

/** Class for a node in decision tree **/
class node {
    public:
        vector<node*> children;
        feature* feat;
        attribute decision:
        void classify(vector<vector<attribute>> data, vector<feature*> features, size_t rid, size_t nb_class);
};

#include "DT.h"

/** Feature functions **/
feature::feature(size_t id, size_t attrs) {
    this->nb_attrs = atrs;
    this->id = id;
}

feature::feature(size_t id) {
    this(id, 0);
}

void feature::add(attribute attr) {
    nb_attrs++;
}

/** Calculate the entropy of the data based on the attributes **/
static double get_entropy(vector<vector<attribute>> data, size_t rid, size_t nb_attrs) {
    size_t length = nb_attrs;
    if(length = 0)
        return 0;
    size_t totals[length];
    double entropy = 0;

    // Compute the number of occurences for each attribute
    for(auto &line: data)
        totals.at(line.at(rid))++;

    // Get the entropy
    for(size_t i = 0; i < length; i++) {
        double f = totals[i]*1.0/length;
        entropy -= f*log2(f);
    }

    return entropy;
}

/** Classify the data and get the best feature to split with **/
void node::classify(vector<vector<attribute>> data, vector<feature*> features, size_t rid, size_t nb_class) {
    // Calculate entropy of data
    double entropy = get_entropy(data, rid, nb_class);
	
	// If we are at the bottom -> make decision
	if(entropy == 0){
		decision = data.at(rid).at(0);
		return;
	}
	
    // Calculate gain for each feature and get the best one
    double max_gain = 0;
    size_t id;
    for(auto &f: features) {
        // Keep track of entropies for each attribute
        double entropies[f->nb_attrs];

        // Sort data for each attribute of the current feature
        for(size_t a = 0; a < f->nb_attrs; a++) {
            vector<vector<attribute>> attr_to_rows = search(data, f->id, a);

            // Calculate entropy for this attribute
            entropies[a] = get_entropy(attr_to_rows, rid, nb_class);
        }

        // Calculate the gain
        double gain = entropy - mean(entropies, f->nb_attrs);
        assert(gain >= 0);

        // Update the best split
        if(gain > max_gain) {
            max_gain = gain;
            id = f->id;
        }
    }

    feat = features.at(id);
    for(size_t a = 0; a < feat->nb_attrs; a++) {
		// Get data for this new node
		vector<vector<attribute>> new_data = search(data, feat->id, a);
		
		// Update the features list
		features.erase(vec.begin() + id);
		
		// Next node
		node* new_node = new node();
		children.insert(new_node);
		new_node.classify(new_data, features, rid, nb_class);
	}
}

vector<vector<attribute>> search(vector<vector<attribute>> data, size_t col, size_t attr) {
    vector<vector<attribute>> attr_to_rows;
    for(auto &l: data) {
        if(l.at(col) == attr)
            attr_to_rows.insert(l);
    }
    return attr_to_rows;
}

double mean(double* array, size_t size) {
    if(size == 0)
        return 0;
    double sum = 0;
    for(size_t i =0 ; i < size; i++)
        sum += array[i];
    return sum*1.0/size;
}
