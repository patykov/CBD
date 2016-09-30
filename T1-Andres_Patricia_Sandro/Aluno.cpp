#include <Aluno.h>

Aluno::Aluno(){
	this->tablename = "aluno";
	this->id=0;
}

int Aluno::row_size(){
	return (30*sizeof(char))+sizeof(time_t)+sizeof(int)+(50*sizeof(char))+(9*sizeof(char))+sizeof(float);
}

void Aluno::generate_id(aluno_row &aluno){
	aluno.id+=1;
}

void Aluno::parse_row(ifstream &infile){
	aluno_row aluno;			
	infile.read(reinterpret_cast<char *>(&aluno.tablename), sizeof(aluno.tablename));
	infile.read(reinterpret_cast<char *>(&aluno.rowsize), sizeof(aluno.rowsize));
	infile.read(reinterpret_cast<char *>(&aluno.timestamp), sizeof(aluno.timestamp));
	infile.read(reinterpret_cast<char *>(&aluno.id), sizeof(aluno.id));
	infile.read(reinterpret_cast<char *>(&aluno.name), sizeof(aluno.name));			
	infile.read(reinterpret_cast<char *>(&aluno.cr), sizeof(aluno.cr));
}
void Aluno::write_row(ofstream &outfile, vector<string> row){			
	aluno_row aluno;
	aluno.dre=row[0];
	aluno.name=row[1];
	aluno.cr=atof(row[2].c_str());	
	time(&aluno.timestamp);
	generate_id(aluno);
	outfile.write(reinterpret_cast<char *>(&tablename),30*sizeof(char));	
	ostringstream ss;
    ss << row_size();    
	outfile.write(ss.str().c_str(),sizeof(int));	
	outfile.write(reinterpret_cast<char *>(&aluno.timestamp),sizeof(time_t));
	outfile.write(reinterpret_cast<char *>(&aluno.id),sizeof(int));
	outfile.write(reinterpret_cast<char *>(&aluno.name),50*sizeof(char));
	outfile.write(reinterpret_cast<char *>(&aluno.cr),sizeof(float));		
	cout<<"ths"<<endl;	
}