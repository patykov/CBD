class Aluno:Table{
	private:{
		int id;
		string name;
		string dre;
		float cr;
	}

	public:{
		parse_field(){
			
		}
		parse_row(string row)
		{
			id=atoi(row_id);
			name=row_name;
			dre=row_dre;
			cr=atof(row_cr);		
		}
	}
}