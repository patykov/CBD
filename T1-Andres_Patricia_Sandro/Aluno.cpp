#include <Aluno.h>

Aluno::Aluno(){
	this->tablename="aluno";
	this->id=0;
	this->key_field="dre";
	this->schema["tablename"]="char[31]";
	this->schema["rowsize"]="int";
	this->schema["timestamp"]="time_t";
	this->schema["id"]="int";
	this->schema["dre"]="char[10]";
	this->schema["name"]="char[51]";
	this->schema["cr"]="float";
	this->bptree(".",true);
}

size_t Aluno::row_size(){
	return sizeof(aluno_row);
	//return (30*sizeof(char))+sizeof(int)+sizeof(time_t)+sizeof(int)+(9*sizeof(char))+(50*sizeof(char))+sizeof(float);
}

void Aluno::generate_id(aluno_row &aluno){
	this->id++;
	aluno.id=this->id;
}

aluno_row Aluno::parse_row(ifstream &infile){
	aluno_row aluno;			

	bool result=infile.read((char *)&aluno,sizeof(aluno_row));	
	return aluno;	
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

void Aluno::write_indexed_row(ofstream &outfile, ofstream &indexfile, vector<string> row){		
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
	int pos=outfile.tellp();
	indexfile.write((const char*)&(aluno.id),sizeof(int));
	indexfile.write((const char*)&pos,sizeof(int));
	bptree.insert(aluno.id,pos);
	hashmap[aluno.id]=pos;
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

void Aluno::read_rows(){
    string filename=this->tablename+".dat";
    ifstream infile(filename.c_str(), ios::in | ios::binary);   
    if(infile.is_open())
    { 
    	aluno_row aluno;
        while(infile.read((char *)&aluno,sizeof(aluno_row))){         
            this->print_row(aluno);               	     
        }                   
        infile.close();
    }
}

aluno_row Aluno::search(string st,string key){        
	switch (str_to_enum(st)){
		case SEQUENTIAL:{
            return this->sequential_search(key);
			break;
		} 
        case BINARY:{
            return this->binary_search(key);
            break;
        }
		case INDEXED:{
            return this->indexed_search(key);
			break;
		}
		case BPTREE:{
            return this->bptree_search(key);
			break;
		}
		case BITMAP:{
            return this->bitmap_search(key);
			break;
		}
		default:{
            return this->sequential_search(key);
			break;
		}
	}
}

aluno_row Aluno::sequential_search(string key){
	aluno_row aluno; 
    string filename=this->tablename+".csv";
    cout<<"Searching file "<<filename<<endl;
    ifstream infile(filename.c_str(), ios::in);   
    char buffer[this->row_size()];
    if(infile.is_open())
    { 
        string line;
        while(infile>>line){
            vector<string> row=split_into_vector(line,',');
            string primary_key=row[0];
            if(primary_key==key){               	
                std::copy(row[0].begin(),row[0].end(),aluno.dre);
				aluno.dre[row[0].size()]='\0';
				std::copy(row[1].begin(),row[1].end(),aluno.name);	
				aluno.name[row[1].size()]='\0';
				aluno.cr=atof(row[2].c_str());	
				cout<<"found"<<endl;
				break;
                
            }
        }
        infile.close();        
    }
    return aluno;
}

aluno_row Aluno::binary_search(string key){
	aluno_row aluno;
    string filename=this->tablename+".dat";
    cout<<"Searching file "<<filename<<endl;
    ifstream infile(filename.c_str(), ios::in | ios::binary);   
    char buffer[this->row_size()];
    if(infile.is_open())
    {     	
        while(infile.read((char *)&aluno,sizeof(aluno_row))){                     
            if(aluno.dre==key){
            	return aluno;
            }
        }                   
        infile.close();
    }
}

aluno_row Aluno::indexed_search(string key){
	aluno_row aluno;
    string filename=this->tablename+".dat";
    string filename_index=this->tablename+"_index.dat";
    cout<<"Searching file "<<filename<<endl;
    ifstream infile_index(filename_index.c_str(), ios::in | ios::binary);
    int key2=atoi(key.c_str());   
    int id;
    int pos;
    if(infile_index.is_open())
    {     	
        while(infile_index>>id){
        	infile_index>>pos;
        	if(id==key2)
        	{
        		ifstream infile(filename.c_str(),ios::in|ios::binary);
        		if(infile.is_open())
			    {
			    	infile.seekg(pos,infile.beg);     	
			        infile.read((char *)&aluno,sizeof(aluno_row));
			        infile.close();
			        break;
			    }	
        	}
            
        }                   
        infile_index.close();
    }	
    return aluno;
}

aluno_row Aluno::bptree_search(string key){
	aluno_row aluno;
	int pos;
	int key2=atoi(key.c_str());
	bptree.search(key, &pos);
	ifstream infile(filename.c_str(),ios::in|ios::binary);
	if(infile.is_open())
    {
    	infile.seekg(pos,infile.beg);     	
        infile.read((char *)&aluno,sizeof(aluno_row));
        infile.close();
    }
    return aluno;
}

aluno_row Aluno::hashed_search(string key){
	aluno_row aluno;
	int key2=atoi(key.c_str());
	int pos=this->hashmap[key2];
	
	ifstream infile(filename.c_str(),ios::in|ios::binary);
	if(infile.is_open())
    {
    	infile.seekg(pos,infile.beg);     	
        infile.read((char *)&aluno,sizeof(aluno_row));
        infile.close();
    }
    return aluno;
}