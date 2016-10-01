#ifndef ALUNO_H
#define ALUNO_H
#endif

#include <Table.h>

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
	
	protected:
		size_t row_size();
		void write_row(ofstream &outfile,vector<string> row);

	public:
		Aluno();		
		bool parse_row(ifstream &infile);		
		void print_row(aluno_row aluno);
		void read_binary();
};