#include <Aluno.h>

int Aluno::row_size(){
	return 30*sizeof(char)+sizeof(time_t)+sizeof(int)+sizeof(50*sizeof(char))+sizeof(float);
}

void Aluno::generate_id(int &id){
	id+=1;
}

void Aluno::parse_row(ifstream infile,string row){				
	infile.read(reinterpret_cast<char *>(&tablename), sizeof(tablename));
	infile.read(reinterpret_cast<char *>(&timestamp), sizeof(timestamp));
	infile.read(reinterpret_cast<char *>(&id), sizeof(id));
	infile.read(reinterpret_cast<char *>(&name), sizeof(name));			
	infile.read(reinterpret_cast<char *>(&cr), sizeof(cr));
}
void Aluno::load_data(ofstream outfile,vector<string> row){			
	name=row[0];
	cr=atof(row[1]);
	time(&timestamp);
	generate_id(&id);
	outfile.write(tablename,30*sizeof(char));
	outfile.write(timestamp,sizeof(time_t));
	outfile.write(id,sizeof(int));
	outfile.write(name,50*sizeof(char));
	outfile.write(cr,sizeof(float));			
}