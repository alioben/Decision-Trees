/** Type representing attribute like true Windy **/
typedef size_t attribute;

/** Class representing a feature like Wind **/
class feature {
    public:
        feature(size_t id, size_t nb_attrs, bool is_class);
        size_t id;								/** Position int the table of data **/
        size_t nb_attrs;					/** Number of attributes of this feature **/
        bool is_class;
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
	CSV_Reader* reader;
	vector<vector<string>> attrs_values;
	vector<vector<attribute>> data;
	size_t rc;
	private:
		vector<vector<atribute>> generate_data();
	public:
		DTClassifier(string filename, string c);
		node& fit();
		
};

void print_vec(vector<attribute> as);

void print_tree(node* n);

double get_entropy(vector<vector<attribute>> data, feature& feat);

vector<vector<attribute>> search(vector<vector<attribute>> data, size_t col, size_t attr);

double mean(double* array, size_t size);
