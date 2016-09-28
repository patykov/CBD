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

using namespace std;

enum search_type{
			SEQUENTIAL,INDEXED,BINARY,BITMAP
		};
		
class Table{
	protected:		
		

		search_type str_to_enum(string const& in_string);
		virtual void load_data(ofstream &outfile,vector<string> row);

		vector<string> split_into_vector(string line,char ch);

		pair<string,string> split_into_pair(string line,char ch);
		void write_to_file(string filename);
	public:
		void search(string st);
};