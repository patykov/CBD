#include <Aluno.h>

int main(){
	Aluno aluno;
	aluno.write_to_file("aluno.csv");
	//aluno.print_file("cbd.dat");
	ifstream infile("cbd.dat", ios::binary);    
	infile.clear();
	infile.seekg(0,infile.beg);    	
	aluno.parse_row(infile);		
	infile.close();
	return 0;
}