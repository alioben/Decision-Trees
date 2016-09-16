#include <string>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <fstream>
using namespace std;

class CSV_Row{
	private:
		vector<string> elements;		/** The elements of the row **/
	public:
		CSV_Row(string line);		/** Constructor **/
		size_t get_size_col();		/** Get the number of columns of the current row **/
		string get_string_at(size_t col);		/** Get the string located at column 'col' **/
		double get_double_at(size_t col);		/** Get the string located at column 'col' **/
		int get_int_at(size_t col);		/** Get the string located at column 'col' **/
		tm get_time_at(size_t col, string time_format);		/** Get the number of columns of the current row **/
		string get_string_at(string col);		/** Get the string located at column 'col' **/
		double get_double_at(string col);		/** Get the string located at column 'col' **/
		int get_int_at(string col);		/** Get the string located at column 'col' **/
};

class CSV_Reader{
	private:
		ifstream infile;		/** Input stream **/
		vector<string> attributes;		/** Attributes of the csv file **/
		size_t tot_cols;		/** The total number of columns in the csv file **/
		size_t line_nb;		/** The current line number reached **/
	public:
		CSV_Reader(string filename);
		CSV_Row& get_next_row();	/** Fetch the next row from file **/
		bool is_next();
};
