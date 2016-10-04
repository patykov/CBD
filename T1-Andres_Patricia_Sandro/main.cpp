#include <Aluno.h>

int main(){
	Aluno table_aluno;
	table_aluno.write_to_file();
	//aluno.print_file("cbd.dat");
	//table_aluno.read_binary();
	//aluno_row aluno = table_aluno.sequential_search("320933490");
	#ifdef BENCHMARK
     clock_t start, end;
     double cpu_time_used;
     
     start = clock();
     aluno_row aluno = table_aluno.search("binary","420949093");
     end = clock();
     cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
     cout<<"Tempo de execucao: "<<cpu_time_used<<endl;
    #else
    	aluno_row aluno = table_aluno.search("binary","420949093"); 
	#endif
	
	table_aluno.print_row(aluno);
	//table_aluno.print_row(aluno);
	//row& = dynamic_cast<aluno_row&>();
	return 0;
}