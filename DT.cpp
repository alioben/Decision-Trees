#include "DT.h"
#include "csv_reader/sutils.h"

/** Feature functions **/
feature::feature(size_t id, size_t attrs, bool is_class) {
    this->nb_attrs = attrs;
    this->id = id;
    this->is_class = is_class;
    this->active = true;
}

/** Calculate the entropy of the data based on the attributes **/
double get_entropy(vector<vector<attribute>> data, feature& feat) {
    size_t length = feat.nb_attrs;
    if(length == 0)
        return 0;

    size_t totals[length];
    for(int i = 0; i < length; i++)
        totals[i] = 0;

    double entropy = 0;

    // Compute the number of occurences for each attribute
    for(auto &line: data)
        totals[line.at(feat.id)]++;

    // Get the entropy
    for(size_t i = 0; i < length; i++) {
        double f = totals[i]*1.0/data.size();
        if(f > 0)
            entropy -= f*log2(f);
    }

    return entropy;
}

/** Classify the data and get the best feature to split with **/
void node::classify(vector<vector<attribute>> data, vector<feature*> features) {
    // Calculate entropy of data
    double entropy = get_entropy(data, *(features.back()));

    // If we are at the bottom -> make decision
    if(entropy == 0) {
        decision = data.at(0).at(features.back()->id);
        return;
    }

    /*
    cout << "------------------------" << endl;
    cout << "current entropy: " << entropy << endl;
    */

    // Calculate gain for each feature and get the best one
    double max_gain = 0;
    size_t id;
    for(auto &f: features) {
        if(!f->is_class && f->active){
            // Keep track of entropies for each attribute
            double entropies[f->nb_attrs];
            for(int i = 0; i < f->nb_attrs; i++)
                entropies[i] = 0;
            // Sort data for each attribute of the current feature
            for(size_t a = 0; a < f->nb_attrs; a++) {
                vector<vector<attribute>> attr_to_rows = search(data, f->id, a);
                // Calculate entropy for this attribute
                entropies[a] = (attr_to_rows.size()/(1.0*data.size()))*get_entropy(attr_to_rows, *features.back());
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
    }
    
    /*
    cout << "max gain: " << max_gain << endl;
    cout << "entropy of best: " << (entropy-max_gain) << endl;
    cout << "split on feature #" << id << endl << endl;
    */

    // Update the list of features
    feat = features.at(id);
    feat->active = false;

    for(size_t a = 0; a < feat->nb_attrs; a++) {
        // Get data for this new node
        vector<vector<attribute>> new_data = search(data, feat->id, a);

        // Next node
        node* new_node = new node();
        this->children.push_back(new_node);
        new_node->classify(new_data, features);
    }

    this->entropy = entropy;
}

/** Filter data and return specific rows **/
vector<vector<attribute>> search(vector<vector<attribute>> data, size_t col, size_t attr) {
    vector<vector<attribute>> attr_to_rows;
    for(auto &l: data) {
        if(l.at(col) == attr)
            attr_to_rows.push_back(l);
    }
    return attr_to_rows;
}

/** Calculate the mean of an array **/
double mean(double* array, size_t size) {
    if(size == 0)
        return 0;
    double sum = 0;
    for(size_t i =0 ; i < size; i++)
        sum += array[i];
    return sum;
}

/** Print a single line of data **/
void print_vec(vector<attribute> as) {

    for(auto &a: as) {
        cout << a << ", ";
    }
    cout << endl;
}

/** Print the decision tree **/
void print_tree(node* n) {
    if(n->children.size() > 0) {
        printf(" [c: %lu, f: %lu, e: %.2f]{", n->children.size(), n->feat->id, n->entropy);
        for(auto &c: n->children)
            print_tree(c);
        printf("} ");
    } else
        printf(" [d: %lu] ", n->decision);
}

DTClassifier::DTClassifier(string filename, string c) {
    reader = new CSV_Reader(filename);
    rc = 0;
    // Store the index of the class in the table
    while(rc < reader->get_size_col() && 
        c.compare(reader->get_attr_at(rc)))
		rc++;
}

vector<vector<attribute>> DTClassifier::generate_data() {
    size_t cols = reader->get_size_col();

    // Clear old data
    data.clear();
    attrs_values.clear();
    attrs_values.resize(cols);

    // Load data into array
    while(reader->is_next()) {

		vector<attribute> new_line;
        CSV_Row row = reader->get_next_row();

        for(size_t j = 0; j < cols; j++) {
            size_t i = (j == this->rc) ? (cols-1) : ((j < this->rc) ? j : j-1);

			string val = row.get_string_at(j);
			// Get the equivalent index for this value
			int index = index_of(attrs_values.at(i), val);
			if(index < 0){
				attrs_values.at(i).push_back(val);
				index = attrs_values.at(i).size()-1;
			}

			// Insert the coloumns in the new line
			new_line.push_back((attribute)index);
        }

        // Insert the line in the data array
        data.push_back(new_line);
    }
    return data;
}

node& DTClassifier::fit(){
    // Generate data from csv file
    vector<vector<attribute>> data = generate_data();

    /*
    cout << "data:"<< endl;
    for(int i = 0; i < data.size(); i++){
        for(int j = 0; j < data.at(i).size(); j++){
            cout << data.at(i).at(j) << " ";
        }
        cout << endl;
    }
    */
    
	// Initialize the array of features
	for(size_t i = 0; i < attrs_values.size(); i++){
        bool is_class = (i == attrs_values.size()-1);
		feature* f = new feature(i, attrs_values.at(i).size(), is_class);
		features.push_back(f);
	}
	
    // Fit the decision tree to data
	node* root = new node();
	root->classify(data, features);
    return *root;
}
