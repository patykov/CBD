#include <stdlib.h>
#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <dirent.h>
#include <time.h>

using namespace std;

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

vector<string> parse_line(string line,char ch,vector<pair<string,string> > schema){
    vector<string> result;
    stringstream line_stream(line);
    string cell;

    while(getline(line_stream,cell, ch)){
        result.push_back(cell);
    }
    return result;
}

enum type_name {
    t_string,t_int,t_float,t_bool
};

type_name hashit(std::string const& in_string) {
    if (in_string == "string") return t_string;
    if (in_string == "int") return t_int;
    if (in_string == "float") return t_float;
    if (in_string == "bool") return t_bool;
    return t_string;
}

unsigned row_size(vector<pair<string,string> > schema){
    unsigned size=0;
    for(unsigned i=0; i<schema.size(); i++){
        switch(hashit(schema[i].second)){
            case t_string:{
                size+=200*sizeof(char); // assume tamanho máximo 200 para a string
                break;
            }
            case t_int:{
                size+=sizeof(int);
                //outfile.write()
                break;
            }
            case t_float:{
                size+=sizeof(float);
                break;
            }
            case t_bool:{
                size+=sizeof(bool);
                break;
            }
        }
    }
    int cabecalho = 200*sizeof(char) + sizeof(time_t) + sizeof(int);
    return size+cabecalho;
}

void find_key(string file_name, unsigned key, int block_size){
    ifstream file(file_name.c_str(), ifstream::binary);
    if (file.is_open()){
        file.seekg(0, ios::end); //seeking to the end of the file
        int length = file.tellg(); //Getting the length of file or positon of enf of file
        char * buffer = new char [block_size];
        int seek_position = key*block_size;
        int aux=0;
        if(seek_position >= 0 && seek_position <= length){ //Checking if is a valid position
            file.seekg(seek_position, ios::beg);

            /*for(unsigned i = 0; i<block_size; i++){
                file.get(buffer[i]);
                aux++;
            }
            buffer[aux-1] = '\0';
            for(unsigned i = 0; buffer[i] != '\0'; i++){
                cout << buffer[i];
            }*/
        }
        else {
            cout << "Invalid Seek Position." << endl;
        }
        file.close();
        delete[] buffer;
    }
    else {
        cout << "File could not be opened." << endl;
    }
}

void write_binary(ofstream &outfile, string s, string t){
    switch(hashit(t)){
        case t_string:{
            string val = s;
            outfile.write(reinterpret_cast<const char *>(&val),200*sizeof(char));
            break;
        }
        case t_int:{
            int val = atoi(s.c_str());
            outfile.write(reinterpret_cast<const char *>(&val),sizeof(int));
            break;
        }
        case t_float:{
            float val = atof(s.c_str());
            outfile.write(reinterpret_cast<const char *>(&val),sizeof(float));
            break;
        }
        case t_bool:{
            bool val = (s == "1")?(true):(false);
            outfile.write(reinterpret_cast<const char *>(&val),sizeof(bool));
            break;
        }
    }
}

int read_binary(ifstream &infile, string t){   
    switch(hashit(t)){
        case t_string:{     
            char * buffer = new char[200*sizeof(char)];
            infile.read(buffer,200*sizeof(char));
            string val=buffer;
            cout<<val<<endl;
            return sizeof(char);
        }
        case t_int:{
            char * buffer = new char[sizeof(int)];
            infile.read(buffer,sizeof(int));
            int val=atoi(buffer);
            cout<<val<<endl;
            return sizeof(int);
        }
        case t_float:{
            char * buffer = new char[sizeof(float)];
            infile.read(buffer,sizeof(float));
            float val=atof(buffer);
            cout<<val<<endl;
            return sizeof(float);
        }
        case t_bool:{
            char * buffer = new char[sizeof(bool)];
            infile.read(buffer,sizeof(bool));
            bool val=(bool)buffer;
            cout<<val<<endl;
            return sizeof(bool);
        }
    }
}
    
int main(){
    string line;
    vector<string> row;
    ifstream schema("schema.csv");
    map<string,vector<pair<string,string> > > schemas;
    vector<pair<string,string> > table_schema;
    pair<string,string> name_type;
    time_t timestamp;
    int key = 0;

    if (schema.is_open()){
        while (schema.good()){
            getline (schema,line);
            row = split_into_vector(line,',');
            string table_name = row[0];

            unsigned rsize = row.size();
            for(unsigned i=1; i<rsize; i++){
               name_type = split_into_pair(row[i],':');
               table_schema.push_back(name_type);
            }
            schemas[table_name]=table_schema;
        }
        schema.close();
    }
        
    for (map<string,vector<pair<string,string> > >::iterator it=schemas.begin(); it!=schemas.end(); ++it){
        string file_name = it->first+".csv";

        ifstream rel(file_name.c_str());

        table_schema = it->second;
        /*cout << "table " << it->first << endl;
        for(unsigned i=0;i<table_schema.size();i++)
        {
            cout << table_schema[i].first << "(" << table_schema[i].second << ")" << endl;
        }*/

        if (rel.is_open()){
            ofstream outfile("cbd", ios::binary);
            ostream_iterator<string> output_iterator(outfile, "\n");
            outfile.write(reinterpret_cast<const char *>(&it->first), 200*sizeof(char));
            time(&timestamp);
            outfile.write(reinterpret_cast<const char *>(&timestamp), sizeof(time_t));
            outfile.write(reinterpret_cast<const char *>(&key), sizeof(int));
            key++;
            while (rel.good()){
                getline (rel,line);
                row = split_into_vector(line,',');
                for(unsigned i=0;i<row.size();i++){
                    string s = row[i];
                    string t = table_schema[i].second;
                    //cout<<s<<"("<<t<<")"<<endl; // imprime valor e tipo da célula
                    write_binary(outfile,s,t);
                }
            }
            rel.close();
            outfile.close();
        }
        //cout<<row_size(table_schema);
        find_key("cbd", 1, row_size(table_schema));
        ifstream file(file_name.c_str(), ifstream::binary);
        if (file.is_open()){
            for (unsigned i=0; i<1; i++){
                string t = table_schema[i].second;
                read_binary(file, t);
            }
        }
        file.close();
    }

}
