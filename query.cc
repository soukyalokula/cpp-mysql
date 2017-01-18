
//Name: Soukya
//ZID: Z1776873
//Assignment 3


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <postgresql/libpq-fe.h>


using namespace std;

int main()
{	
	PGconn * myDb;
	
	myDb = PQconnectdb("dbname=z1776873 host=students user=z1776873 password=********");
	if(PQstatus(myDb) != CONNECTION_OK)
    	{
      		cerr<<"Couldn't connect to database!\n";
		cerr<<PQerrorMessage(myDb);
    	}
	cerr << "Connected to database." << endl;
  	

	PGresult * result;
	string query,c_name,t_num;
	cout<<"Enter the name of council"<<endl;
	getline(cin,c_name);
	cout<<"Enter the troop number"<<endl;
	getline(cin,t_num);
	
	 
	query="select s.cookie_name,sum(cast(s.quantity as int)) as total_quantity,sum(cast(se.price as float)) as total_price from gs.shopsales s,gs.sells se where s.cookie_name=se.cookie_name and s.council_name=se.council_name and s.troop_number='"+t_num+"' and s.council_name='"+c_name+"' group by s.cookie_name;"; 

  	result = PQexec(myDb, query.c_str());
  	
  	if(PQresultStatus(result) != PGRES_TUPLES_OK)
    	{
		cerr<<PQresultErrorMessage(result) << endl;
    	}
    
	int nrow= PQntuples(result);
	int ncol= PQnfields(result);

	if(nrow==0)
	{
	cout<<"No records found"<<endl;
	return -1;
	}
	
	for(int head=0; head < ncol ; head++)
	{
		cout << PQfname(result,head) <<setw(30)<<right;
		
	}
	cout<<endl<<left;
	for(int row=0; row < nrow; row++)
	{
		for (int col=0; col < ncol; col++)
		{
			cout << PQgetvalue(result,row,col) <<setw(30)<<left;
		}
		cout << endl;
	}
}

