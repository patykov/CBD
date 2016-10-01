#ifndef ALUNO_H
#define ALUNO_H
#endif

#include <Table.h>

using namespace std;

struct aluno_row{
	char tablename[30];
	int rowsize;
	time_t timestamp;
	int id;
	char dre[9];
	char name[50];
	float cr;
};

class Aluno:public Table{
	private:
		string tablename;
		int id;
		size_t row_size();
		void generate_id(aluno_row &aluno);
	
	protected:
		void write_row(ofstream &outfile,vector<string> row);

	public:
		Aluno();		
		void parse_row(ifstream &infile);		
		void print_row(aluno_row aluno);
};