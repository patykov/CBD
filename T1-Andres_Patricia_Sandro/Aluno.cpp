#include <Aluno.h>

Aluno::Aluno(){
	this->tablename="aluno";
	this->id=0;
}

size_t Aluno::row_size(){
	return (30*sizeof(char))+sizeof(int)+sizeof(time_t)+sizeof(int)+(9*sizeof(char))+(50*sizeof(char))+sizeof(float);
}

void Aluno::generate_id(aluno_row &aluno){
	aluno.id+=1;
}

void Aluno::parse_row(ifstream &infile){
	aluno_row aluno;			

	infile.read((char *)&aluno,sizeof(aluno_row));
	infile.close();
	this->print_row(aluno);
	cout<<sizeof(aluno_row)<<endl;
	cout<<row_size()<<endl;
}

void Aluno::write_row(ofstream &outfile, vector<string> row){			
	aluno_row aluno;
	std::copy(this->tablename.begin(),this->tablename.end(),aluno.tablename);
	aluno.rowsize=this->row_size();
	time_t timestamp;
	time(&timestamp);
	aluno.timestamp=timestamp;
	generate_id(aluno);
	std::copy(row[0].begin(),row[0].end(),aluno.dre);
	std::copy(row[1].begin(),row[1].end(),aluno.name);	
	aluno.cr=atof(row[2].c_str());		
	outfile.write((const char *)&aluno, sizeof( aluno_row ));		
}

void Aluno::print_row(aluno_row aluno){
	cout<<aluno.tablename<<endl;
	cout<<aluno.rowsize<<endl;
	cout<<aluno.timestamp<<endl;
	cout<<aluno.id<<endl;
	cout<<aluno.dre<<endl;
	cout<<aluno.name<<endl;
	cout<<aluno.cr<<endl;	
}