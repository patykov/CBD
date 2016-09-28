#include <Table.h>

search_type Table::str_to_enum(std::string const& in_string) {
    if (in_string == "sequential") return SEQUENTIAL;
    if (in_string == "indexed") return INDEXED;
    if (in_string == "binary") return BINARY;
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
void Table::write_to_file(string filename){
	ifstream rel(filename.c_str());	
	string line;		
	if (rel.is_open())
    {
        ofstream outfile("cbd.dat", ios::binary);
        ostream_iterator<string> output_iterator(outfile, "\n");      

        while (rel.good())
        {
        	getline (rel,line);
        	vector<string> row = split_into_vector(line,','); 	            	
         	load_data(outfile,row);
        }
        rel.close();
        outfile.close();
        
    }
}	
void Table::search(string st){
	switch (str_to_enum(st)){
		case SEQUENTIAL:{
			break;
		} 
		case INDEXED:{
			break;
		}
		case BINARY:{
			break;
		}
		case BITMAP:{
			break;
		}
		default:{
			break;
		}
	}
}	

int main(){

	return 0;
}