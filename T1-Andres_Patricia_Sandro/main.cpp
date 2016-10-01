#include <Aluno.h>

int main(){
	Aluno aluno;
	aluno.write_to_file("aluno.csv");
	//aluno.print_file("cbd.dat");
	aluno.read_binary();
	return 0;
}