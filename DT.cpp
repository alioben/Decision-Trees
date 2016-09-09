#include <iostream>
#include <string>
#include <cmath>
using namespace std;
#include "DT.h"

/** Type representing attribute like true Windy **/
typedef int attribute;

/** Class representing a feature like Wind **/
static class feature{
	private:
		int id;
		vector<attribute> attributes;
	public:
		feature(int id, vector<attribute>);
		feature(int id);
		void add(attribute attr);
};

/** Class for a node in decision tree **/
class node{
	public:
		vector<node*> children;
		vector<attribute> attrs;
		feature feat;
		node(vector<node*> children, vector<attribute> attrs, vector<feature> feat) : children(children), attrs(attrs), feat(feat);
};

class dtclassifier {
	private:
		node* root;
		size_t depth = 0;
		size_t rid = 0;
		vector<vector<attribute>> data;
		vector<feature*> features;
		vector<attribute> rattributes;
		double get_entropy();
	public:
		dtclassifier(vector<vector<attribute>>, vector<feature>, size_t);
		void classify();
		node* get_dt();
};

/*************************************************
 * Feature functions
 * ***********************************************/
feature::feature(int id, vector<attribute> attrs){
	if(attrs != NULL)
		attributes = attrs;
	this->id = id;
}

feature::feature(int id){
	this(id, NULL);
}

void feature::add(attribute attr){
	attributes.insert(attr);
}


/*****************************************************
 * Classifier function
 *****************************************************/
dtclassifier(vector<vector<attribute>> data, vector<feature> features, size_t rid): data(data), features(features){
	this->data = data;
	this->features = features;
	this->rid = rid;
}

/* Generalize get_entropy with variales rid vector<attributes> */
double dtclassifier::get_entropy(vector<vector<attribute>> data, size_t rid){
	size_t length = rattributes.size();
	if(length = 0)
		return 0;
	size_t totals[length];
	double entropy = 0;
	
	for(auto &line: data)
		totals.at(line.at(rid))++;
	
	for(size_t i = 0; i < length; i++){
		double f = totals[i]*1.0/length;
		entropy -= f*log2(f);
	}
	
	return entropy;
}

void dtclassifier::classify(){
	// Calculate entropy of data
	double entropy = get_entropy(data);
	
	// Calculate gain for each feature
	vector<double> gains;
	for(auto &f: features){
		
	}
}
