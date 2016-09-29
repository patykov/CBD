#ifndef ALUNO_H
#define ALUNO_H
#endif

#include <Table.h>

using namespace std;

struct aluno_row{
	string tablename;
	int rowsize;
	time_t timestamp;
	int id;
	string dre;
	string name;
	float cr;
};

class Aluno:public Table{
	private:
		string tablename;

		int row_size();
		void generate_id(aluno_row &aluno);
	
	protected:
		void load_data(ofstream &outfile,vector<string> row);
	public:
		Aluno();		
		void parse_row(ifstream infile);		
		
};