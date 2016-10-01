#include <Aluno.h>

Aluno::Aluno(){
	this->tablename="aluno";
	this->id=0;
	this->key_field="dre";
}

size_t Aluno::row_size(){
	return (30*sizeof(char))+sizeof(int)+sizeof(time_t)+sizeof(int)+(9*sizeof(char))+(50*sizeof(char))+sizeof(float);
}

void Aluno::generate_id(aluno_row &aluno){
	this->id++;
	aluno.id=this->id;
}

bool Aluno::parse_row(ifstream &infile){
	aluno_row aluno;			

	bool result=infile.read((char *)&aluno,sizeof(aluno_row));	
	if(result){
		//this->print_row(aluno);	
	}	
	return result;	
}

void Aluno::write_row(ofstream &outfile, vector<string> row){		
	aluno_row aluno;
	std::copy(this->tablename.begin(),this->tablename.end(),aluno.tablename);
	aluno.tablename[this->tablename.size()]='\0';
	aluno.rowsize=sizeof(aluno_row);//this->row_size();
	time_t timestamp;
	time(&timestamp);
	aluno.timestamp=timestamp;
	generate_id(aluno);	
	std::copy(row[0].begin(),row[0].end(),aluno.dre);
	aluno.dre[row[0].size()]='\0';
	std::copy(row[1].begin(),row[1].end(),aluno.name);	
	aluno.name[row[1].size()]='\0';
	aluno.cr=atof(row[2].c_str());		
	//this->print_row(aluno);
	outfile.write((const char *)&aluno, sizeof( aluno_row ));		
}

void Aluno::read_binary(){
	string filename=this->tablename+".dat";
	ifstream infile(filename.c_str(), ios::in | ios::binary);   
	if(infile.is_open())
	{ 
		while(this->parse_row(infile)){			
								
		} 					
		infile.close();
	}
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