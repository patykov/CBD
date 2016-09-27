enum search_type{
	SEQUENTIAL,INDEXED,BINARY,BITMAP;
};

search_type str_to_enum(std::string const& in_string) {
    if (in_string == "sequential") return SEQUENTIAL;
    if (in_string == "indexed") return INDEXED;
    if (in_string == "binary") return BINARY;
    if (in_string == "bitmap") return BITMAP;
    return t_string;
}

class Table{
	Table(){

	}
	private:{
		void load_data(string filename){

		}
		void write_to_file(string filename){

		}
	}
	protected:{
		vector<string> split_into_vector(string line,char ch){
		    vector<string> result;
		    stringstream line_stream(line);
		    string cell;

		    while(getline(line_stream,cell, ch)){
		        result.push_back(cell);
		    }
		    return result;
		}

		pair<string,string> split_into_pair(string line,char ch){
		    pair<string,string> result;
		    string cell;
		    int pos=line.find_first_of(ch);
		    return make_pair(line.substr(0,pos),line.substr(pos+1));
		}
	}
	public:{ 
		void search(search_type st){
			switch str_to_enum(st){
				case SEQUENTIAL:{

				} 
				case INDEXED:{

				}
				case BINARY:{

				}
				case BITMAP:{

				}
			}
		}
	}
}
