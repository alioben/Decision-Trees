#include "csv_reader.h"
#include "sutils.h"

/** Initialize the attributes and the number of columns **/
CSV_Reader::CSV_Reader(string filename){
	infile.open(filename);
	CSV_Row first_row = get_next_row();
	tot_cols = first_row.get_size_col();
}

/** Fetch the next row from file **/
CSV_Row& CSV_Reader::get_next_row(){
	if(!infile.eof()){
		// Read line from file
		string line;
		getline(infile,line);
		CSV_Row* new_row = new CSV_Row(line);
		
		// Check for malformation
		if(new_row->get_size_col() != tot_cols && tot_cols){
			string error = "Line number ";
			error += to_string(line_nb) + " does not have the same number of columns.";
			throw error.c_str();
		}
		
		// Update the current line
		line_nb++;
		
		return *new_row;
	} else throw "No more row can be read.";
}

bool CSV_Reader::is_next(){
	char last_char = infile.get();
	if(last_char != '\n' && last_char != EOF) infile.putback(last_char);
	return !infile.eof();
}

/** Initiliaze the CSV row by reading the element of that row **/
CSV_Row::CSV_Row(string line){
	string delimiter = ",";
	size_t position = 0;
	string token;
	while ((position = line.find(delimiter)) != string::npos) {
		token = line.substr(0, position);
		elements.push_back(trim(token));
		line.erase(0, position + delimiter.length());
	}
}

/** Getters for double, string, int, time and size **/
int CSV_Row::get_int_at(size_t col){
	if(col >= elements.size())
		throw "Index out of range.";
	return stoi(elements.at(col));
}

size_t CSV_Row::get_size_col(){
	return elements.size();
}

string CSV_Row::get_string_at(size_t col){
	if(col >= elements.size())
		throw "Index out of range.";
	return elements.at(col);
}

double CSV_Row::get_double_at(size_t col){
	if(col >= elements.size())
		throw "Index out of range.";
	return parse_double(elements.at(col));
}

/** Overloaded getters for row elements **/
int CSV_Row::get_int_at(string col){
	int pos = index_of(elements, col);
	if(pos < 0)
		throw "Index out of range.";
	return stoi(elements.at(pos));
}

string CSV_Row::get_string_at(string col){
	int pos = index_of(elements, col);
	if(pos < 0)
		throw "Index out of range.";
	return elements.at(pos);
}

double CSV_Row::get_double_at(string col){
	int pos = index_of(elements, col);
	if(pos < 0)
		throw "Index out of range.";
	return parse_double(elements.at(pos));
}
