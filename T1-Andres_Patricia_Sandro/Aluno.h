#ifndef ALUNO_H
#define ALUNO_H
#endif

#include <Table.h>
#include <BPTree/bpt.h>

using namespace std;

struct aluno_row:table_row{
	char tablename[31];
	int rowsize;
	time_t timestamp;
	int id;
	char dre[10];
	char name[51];
	float cr;
};

class Aluno:public Table{
	private:				
		void generate_id(aluno_row &aluno);
		bpt::bplus_tree bptree;
		map<int,int> hashmap;
	protected:
		size_t row_size();
		void write_row(ofstream &outfile,vector<string> row);
		void write_indexed_row(ofstream &outfile,ofstream &indexfile,vector<string> row);

	public:
		Aluno();		
		aluno_row parse_row(ifstream &infile);		
		void print_row(aluno_row aluno);	
		void read_rows();	
		aluno_row search(string st,string key);		
		aluno_row sequential_search(string key);
		aluno_row binary_search(string key);
		aluno_row indexed_search(string key);
		aluno_row bptree_search(string key);
		aluno_row hashed_search(string key);
		//aluno_row bitmap_search(string key);	
};