#include <time.h>

#ifndef ALUNO_H
#define ALUNO_H
#endif

using namespace std;

class Aluno:Table{
	private:{	
		string tablename="aluno";
		time_t timestamp;
		int id=0;
		string name;		
		float cr;

		int row_size();

		void generate_id(int &id);
	}

	public:{		
		void parse_row(ifstream infile,string row);
		void load_data(ofstream outfile,vector<string> row);
	}
};