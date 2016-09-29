#include <Aluno.h>

Aluno::Aluno(){
	tablename = "aluno";
}

int Aluno::row_size(){
	return (30*sizeof(char))+sizeof(time_t)+sizeof(int)+(50*sizeof(char))+(9*sizeof(char))+sizeof(float);
}

void Aluno::generate_id(aluno_row &aluno){
	aluno.id+=1;
}

void Aluno::parse_row(ifstream infile){
	aluno_row aluno;			
	infile.read(reinterpret_cast<char *>(&aluno.tablename), sizeof(aluno.tablename));
	infile.read(reinterpret_cast<char *>(&aluno.rowsize), sizeof(aluno.rowsize));
	infile.read(reinterpret_cast<char *>(&aluno.timestamp), sizeof(aluno.timestamp));
	infile.read(reinterpret_cast<char *>(&aluno.id), sizeof(aluno.id));
	infile.read(reinterpret_cast<char *>(&aluno.name), sizeof(aluno.name));			
	infile.read(reinterpret_cast<char *>(&aluno.cr), sizeof(aluno.cr));
}
void Aluno::load_data(ofstream outfile, vector<string> row){			
	aluno_row aluno;
	aluno.dre=row[0];
	aluno.name=row[1];
	aluno.cr=stof(row[2]);
	time(&aluno.timestamp);
	generate_id(aluno);
	outfile.write(reinterpret_cast<char *>(&tablename),30*sizeof(char));
	outfile.write(reinterpret_cast<char *>(row_size()),sizeof(int));
	outfile.write(reinterpret_cast<char *>(&aluno.timestamp),sizeof(time_t));
	outfile.write(reinterpret_cast<char *>(&aluno.id),sizeof(int));
	outfile.write(reinterpret_cast<char *>(&aluno.name),50*sizeof(char));
	outfile.write(reinterpret_cast<char *>(&aluno.cr),sizeof(float));			
}