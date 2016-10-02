#include <Aluno.h>

int main(){
	Aluno table_aluno;
	table_aluno.write_to_file();
	//aluno.print_file("cbd.dat");
	//table_aluno.read_binary();
	//aluno_row aluno = table_aluno.sequential_search("320933490");
	aluno_row aluno = table_aluno.search("binary","420949093");
	table_aluno.print_row(aluno);
	//table_aluno.print_row(aluno);
	//row& = dynamic_cast<aluno_row&>();
	return 0;
}