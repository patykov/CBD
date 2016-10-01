#ifndef TABLE_H
#define TABLE_H
#endif

#include <stdlib.h>
#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <dirent.h>
#include <time.h>

using namespace std;

enum search_type{
			SEQUENTIAL,INDEXED,BINARY,BITMAP,BPTREE
		};

struct table_row{

};
class Table{
	class Search;
	protected:	
		string tablename;
		string key_field;
		int id;
		virtual size_t row_size()=0;
		virtual void write_row(ofstream &outfile, vector<string> row)=0;		
		virtual bool parse_row(ifstream &infile)=0;				
		virtual void read_binary()=0;

		search_type str_to_enum(string const& in_string);	

		vector<string> split_into_vector(string line,char ch);
		pair<string,string> split_into_pair(string line,char ch);		

	public:			
		void write_to_file(string filename);
		void search(string st,string key);
		void print_file(string filename);
};

class Table::Search{
	public:
		table_row sequential_search(string key);
		table_row binary_search(string key);
		table_row indexed_search(string key);
		table_row bptree_search(string key);
		table_row bitmap_search(string key);
};