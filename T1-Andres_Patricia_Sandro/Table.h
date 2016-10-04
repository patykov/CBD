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
#include <map>
#include <dirent.h>
#include <time.h>

using namespace std;

enum search_type{
			SEQUENTIAL,INDEXED,BINARY,BITMAP,BPTREE,HASHED
		};

struct table_row{
	virtual ~table_row() {}
};
class Table{	
	protected:			
		string tablename;
		string key_field;
		int id;
		map<string,string> schema;

		virtual size_t row_size()=0;
		virtual void write_row(ofstream &outfile, vector<string> row)=0;									
		virtual void write_indexed_row(ofstream &outfile, ofstream &indexfile,vector<string> row)=0;									
		search_type str_to_enum(string const& in_string);	

		vector<string> split_into_vector(string line,char ch);
		pair<string,string> split_into_pair(string line,char ch);		

	public:			
		void write_to_file();
		void print_file(string filename);		
};