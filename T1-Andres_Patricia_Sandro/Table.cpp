#include <Table.h>

search_type Table::str_to_enum(std::string const& in_string) {
    if (in_string == "sequential") return SEQUENTIAL;
    if (in_string == "binary") return BINARY;
    if (in_string == "indexed") return INDEXED;
    if (in_string == "bptree") return BPTREE;
    if (in_string == "bitmap") return BITMAP;
    return SEQUENTIAL;
}

vector<string> Table::split_into_vector(string line,char ch){
    vector<string> result;
    stringstream line_stream(line);
    string cell;

    while(getline(line_stream,cell, ch)){
        result.push_back(cell);
    }
    return result;
}

pair<string,string> Table::split_into_pair(string line,char ch){
    pair<string,string> result;
    string cell;
    int pos=line.find_first_of(ch);
    return make_pair(line.substr(0,pos),line.substr(pos+1));
}
void Table::write_to_file(){
    string filename=this->tablename+".csv";
	ifstream rel(filename.c_str());	
	if (rel.is_open())
    {        
        string line;
        ofstream outfile((this->tablename+".dat").c_str(), ios::out | ios::binary);
        ostream_iterator<string> output_iterator(outfile, "\n");      
        //cout<<filename.c_str()<<endl;
        int i=0;
        while (rel.good())
        {            
        	getline (rel,line);
            if(!line.empty()){                
            	vector<string> row = split_into_vector(line,','); 	            	                
             	write_row(outfile, row);
            }
        }
        outfile.close();
        rel.close();
        
        
    }
}	

void Table::print_file(string filename){
    ifstream infile(filename.c_str(), ios::in | ios::binary);
    if(infile.is_open()){
        // get length of file:
        infile.seekg (0, infile.end);
        int length = infile.tellg();
        infile.seekg (0, infile.beg);

        // allocate memory:
        char * buffer = new char [length];

        // read data as a block:
        infile.read (buffer,length);

        infile.close();

        // print content:
        std::cout.write (buffer,length);

        delete[] buffer;
    }
}