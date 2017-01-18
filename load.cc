//Soukya Lokula
//Z1776873
//Assignment 3

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <postgresql/libpq-fe.h>
#include <sstream>

using namespace std;



string escape_string(PGconn *p,const string &s)
{
	string result;
	char *clean;
	clean=new char[s.length()*2+1];
	PQescapeStringConn(p,clean,s.c_str(),s.length(),0);
	result=clean;
	delete[] clean;
	return result;
}



int main()
{
    	string line,filename;
	string council_name[35],service_unit_name[35],leader_name[35],leader_address[35],girl_name[35],girl_address[35],girl_rank[35],customer_name[35],customer_address[35],cookie_name[35],baker_name[35],baker_address[35],date_sold[35];
	
	string troop_number[35],quantity[35],service_unit_number1[35],cookie_price[35];
	int list=-1;

	PGconn * myDb;
  
	myDb = PQconnectdb("dbname=z1776873 host=courses user=z1776873 password=1992Mar12");
	if(PQstatus(myDb) != CONNECTION_OK)
    	{
    		cerr << "Couldn't connect to database!\n";
		cerr<<PQerrorMessage(myDb);
    	}
	
	else
	cout<<"Connected to Database"<<endl;
	
	cout<<"Enter the name of file to read from "<<endl;
	cin>>filename;
	ifstream inputFile;
	

	inputFile.open(filename);
	if(inputFile.fail())
	{
		cout<<"Could not open the file";
		exit(-1);
	}
	
	while(!inputFile.eof())
	{
		list++;
		int start,end;
		getline(inputFile,line); 
		end = line.find('|',0); 
		if(end > 0)
		{
        
			council_name[list] = line.substr(0,end);
			start = end+1;
			end = line.find('|',start);

        
			service_unit_name[list] = line.substr(start,end-start);
			start = end+1;
			end = line.find('|',start);

        		service_unit_number1[list] = line.substr(start,end-start);
                        start = end+1;
                        end = line.find('|',start);

        		
			troop_number[list] = line.substr(start,end-start);
                        start = end+1;
                        end = line.find('|',start);
        
			leader_name[list]= line.substr(start,end-start);
			start = end+1;
			end = line.find('|',start);

        
			leader_address[list]= line.substr(start,end-start);
			start = end+1;
			end = line.find('|',start);

        
			girl_name[list] = line.substr(start,end-start);
			start = end+1;
			end = line.find('|',start);

        
			girl_address[list] = line.substr(start,end-start);
			start = end+1;
			end = line.find('|',start);

        
			girl_rank[list] = line.substr(start,end-start);
			start = end+1;
			end = line.find('|',start);


        
			customer_name[list]= line.substr(start,end-start);
			start = end+1;
			end = line.find('|',start);

        
			customer_address[list]= line.substr(start,end-start);
			start = end+1;
			end = line.find('|',start);

       
			cookie_name[list]= line.substr(start,end-start);
			start = end+1;
			end = line.find('|',start);

        		
			cookie_price[list]=line.substr(start,end-start);
                        start = end+1;
                        end = line.find('|',start);

        
			baker_name[list]= line.substr(start,end-start);
			start = end+1;
			end = line.find('|',start);

        
			baker_address[list]= line.substr(start,end-start);
			start = end+1;
			end = line.find('|',start);

        		quantity[list]= line.substr(start,end-start);
                        start = end+1;
                        end = line.length();
        
			date_sold[list] = line.substr(start,end-start);
	
    }

}
 
for(int i = 0;i<30 ;i++)
{
	string q1="select * from gs.member where member_name='"+escape_string(myDb,girl_name[i])+"' and member_address='"+girl_address[i]+"';";
	PGresult *res1,*result1;
	res1=PQexec(myDb,q1.c_str());

	if(PQntuples(res1)<1)
	{
		string query1 = "insert into gs.member values ('"+escape_string(myDb,girl_name[i])+"','"+girl_address[i]+"');";
		result1 = PQexec(myDb,query1.c_str());
	}




	string q2="select * from gs.member where member_name='"+escape_string(myDb,leader_name[i])+"' and member_address='"+leader_address[i]+"';";
	PGresult *res2,*result2;
	res2=PQexec(myDb,q2.c_str());

	if(PQntuples(res2)<1)
	{
		string query2 = "insert into gs.member values ('"+escape_string(myDb,leader_name[i])+"','"+leader_address[i]+"');";
		result2 = PQexec(myDb,query2.c_str());
	}


	string q3="select * from gs.customer where customer_name='"+escape_string(myDb,customer_name[i])+"' and customer_address='"+customer_address[i]+"';";
	PGresult *res3,*result3;
	res3=PQexec(myDb,q3.c_str());

	if(PQntuples(res3)<1)
	{
		string query3 = "insert into gs.customer values ('"+escape_string(myDb,customer_name[i])+"','"+customer_address[i]+"');";
		result3 = PQexec(myDb,query3.c_str());
	}

	string q4="select * from gs.baker where baker_name='"+escape_string(myDb,baker_name[i])+"';";
	PGresult *res4,*result4;
	res4=PQexec(myDb,q4.c_str());

	if(PQntuples(res4)<1)
	{
		string query4 = "insert into gs.baker values ('"+escape_string(myDb,baker_name[i])+"','"+baker_address[i]+"');";
		result4 = PQexec(myDb,query4.c_str());
	}


	string q5="select * from gs.council where council_name='"+council_name[i]+"' and baker_name='"+baker_name[i]+"';";
	PGresult *res5,*result5;
	res5=PQexec(myDb,q5.c_str());
	
	if(PQntuples(res5)<1)
	{
		string query5 = "insert into gs.council values ('"+council_name[i]+"','"+baker_name[i]+"');";
		result5 = PQexec(myDb,query5.c_str());
	}


	string q6="select * from gs.cookie where cookie_name='"+cookie_name[i]+"';";
	PGresult *res6,*result6;
	res6=PQexec(myDb,q6.c_str());

	if(PQntuples(res6)<1)
	{
		string query6 = "insert into gs.cookie values ('"+escape_string(myDb,cookie_name[i])+"');";
		result6 = PQexec(myDb,query6.c_str());
	}



	string q7="select * from gs.girl where girl_name='"+escape_string(myDb,girl_name[i])+"' and girl_address='"+girl_address[i]+"';";
	PGresult *res7,*result7;
	res7=PQexec(myDb,q7.c_str());
	if(PQntuples(res7)<1)
	{
		string query7 = "insert into gs.girl values ('"+escape_string(myDb,girl_name[i])+"','"+girl_address[i]+"','"+girl_rank[i]+"');";
		result7 = PQexec(myDb,query7.c_str());
	}



	string q8="select * from gs.leader where leader_name='"+escape_string(myDb,leader_name[i])+"' and leader_address='"+leader_address[i]+"';";
	PGresult *res8,*result8;
	res8=PQexec(myDb,q8.c_str());

	if(PQntuples(res8)<1)
	{
		string query8 = "insert into gs.leader values ('"+escape_string(myDb,leader_name[i])+"','"+leader_address[i]+"');";
		result8 = PQexec(myDb,query8.c_str());
	}


	


	string q9="select * from gs.serviceunit where council_name='"+escape_string(myDb,council_name[i])+"' and su_number='"+service_unit_number1[i]+"';";
	PGresult *res9,*result9;
	res9=PQexec(myDb,q9.c_str());

	if(PQntuples(res9)<1)
	{
		string query9 = "insert into gs.serviceunit values ('"+escape_string(myDb,council_name[i])+"','"+service_unit_number1[i]+"','"+service_unit_name[i]+"');";
		result9 = PQexec(myDb,query9.c_str());
	}


	string q10="select * from gs.troop where su_number='"+service_unit_number1[i]+"' and council_name='"+council_name[i]+"' and troop_number='"+troop_number[i]+"';";
	PGresult *res10,*result10;
	res10=PQexec(myDb,q10.c_str());

	if(PQntuples(res10)<1)
	{
		string query10 = "insert into gs.troop values ('"+service_unit_number1[i]+"','"+council_name[i]+"','"+troop_number[i]+"');";
		result10 = PQexec(myDb,query10.c_str());
	}




	string q11="select * from gs.offers where cookie_name='"+escape_string(myDb,cookie_name[i])+"' and baker_name='"+baker_name[i]+"';";
	PGresult *res11,*result11;
	res11=PQexec(myDb,q11.c_str());

	if(PQntuples(res11)<1)
	{
		string query11 = "insert into gs.offers values ('"+escape_string(myDb,cookie_name[i])+"','"+baker_name[i]+"');";
		result11 = PQexec(myDb,query11.c_str());
	}




	string q12="select * from gs.sells where council_name='"+escape_string(myDb,council_name[i])+"' and cookie_name='"+cookie_name[i]+"';";
	PGresult *res12,*result12;
	res12=PQexec(myDb,q12.c_str());

	if(PQntuples(res12)<1)
	{
		string query12 = "insert into gs.sells values ('"+escape_string(myDb,council_name[i])+"','"+cookie_name[i]+"','"+cookie_price[i]+"');";
		result12 = PQexec(myDb,query12.c_str());
	}



	string q13="select * from gs.belongs where member_name='"+escape_string(myDb,girl_name[i])+"' and member_address='"+girl_address[i]+"' and troop_number='"+troop_number[i]+"' and su_number='"+service_unit_number1[i]+"' and council_name='"+council_name[i]+"';";
	PGresult *res13,*result13;
	res13=PQexec(myDb,q13.c_str());

	if(PQntuples(res13)<1)
	{
		string query13 = "insert into gs.belongs values ('"+escape_string(myDb,girl_name[i])+"','"+girl_address[i]+"',troop_number[i],'"+service_unit_number1[i]+"','"+council_name[i]+"');";
		result13 = PQexec(myDb,query13.c_str());
	}



	string q14="select * from gs.belongs where member_name='"+escape_string(myDb,leader_name[i])+"' and member_address='"+leader_address[i]+"' and troop_number='"+troop_number[i]+"' and su_number='"+service_unit_number1[i]+"' and council_name='"+council_name[i]+"';";
	PGresult *res14,*result14;
	res14=PQexec(myDb,q14.c_str());

	if(PQntuples(res14)<1)
	{
		string query14 = "insert into gs.belongs values ('"+escape_string(myDb,leader_name[i])+"','"+leader_address[i]+"','"+troop_number[i]+"','"+service_unit_number1[i]+"','"+council_name[i]+"');";
		result14 = PQexec(myDb,query14.c_str());
	}




	string q15="select * from gs.shopsales where cookie_name='"+escape_string(myDb,cookie_name[i])+"' and troop_number='"+troop_number[i]+"' and su_number='"+service_unit_number1[i]+"' and council_name='"+council_name[i]+"' and date='"+date_sold[i]+"';";
	PGresult *res15,*result15;
	res15=PQexec(myDb,q15.c_str());

	if(PQntuples(res15)<1)
	{
		string query15 = "insert into gs.shopsales values ('"+escape_string(myDb,cookie_name[i])+"','"+troop_number[i]+"','"+service_unit_number1[i]+"','"+council_name[i]+"', '"+quantity[i]+"','"+date_sold[i]+"');";
		result15 = PQexec(myDb,query15.c_str());
	}


	string q16="select * from gs.indsales where cookie_name='"+escape_string(myDb,cookie_name[i])+"' and cust_name='"+escape_string(myDb,customer_name[i])+"' and cust_address='"+customer_address[i]+"' and girl_name='"+escape_string(myDb,girl_name[i])+"' and girl_address='"+girl_address[i]+"' and date='"+date_sold[i]+"';";
	PGresult *res16,*result16;
	res16=PQexec(myDb,q16.c_str());

	if(PQntuples(res16)<1)
	{
		string query16 = "insert into gs.indsales values ('"+escape_string(myDb,cookie_name[i])+"','"+escape_string(myDb,customer_name[i])+"','"+customer_address[i]+"','"+escape_string(myDb,girl_name[i])+"', '"+girl_address[i]+"','"+date_sold[i]+"','"+quantity[i]+"');";
		result16 = PQexec(myDb,query16.c_str());
	}



}
cout<<"Successfully inserted the records."<<endl;
return 0;

}
