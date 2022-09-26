/*******************************************************
* * FILE NAME   : file_func.cpp
*
* * DESCRIPTION : This file consists of file_to_list and list_to_file
* 		  operations for employee and project details
*
* * REVISION 	: 
*
* 	DATE		NAME		REASON
*
* 	----		----		------
*
********************************************************/  

#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include "func.cpp"
using namespace  std;


/*******************************************************
* * FUNCTION NAME   : employee_file_to_list
*
* * DESCRIPTION     : This function creates or open an existing Employee file and 
* 		      read data from file to list  
*
* * RETURN 	    :  ------
*
*
********************************************************/  

void SALARY::employee_file_to_list()
{
	ifstream fr("Employee");
	//fr.open("Project",ios::in);
	if(fr)
	{
		cout<<"here1";
		fr.read((char *) &empdetail,sizeof(emp_details));
		SALARY sal_obj; 
		while(!fr.eof())
		{
			sal_obj.emp_id=empdetail.employee_id;
			strcpy(sal_obj.emp_name,empdetail.employee_name);
			strcpy(sal_obj.dept,empdetail.department);
			sal_obj.salary=empdetail.basic_salary;
			strcpy(sal_obj.contact,empdetail.contact_number);
			sal_obj.pr_no_prid[0]=empdetail.project_id[0];
			sal_obj.pr_no_prid[1]=empdetail.project_id[1];
			sal_obj.pr_no_prid[2]=empdetail.project_id[2];
			sal_obj.pr_no_hrs[0]=empdetail.no_hrs[0];
			sal_obj.pr_no_hrs[1]=empdetail.no_hrs[1];
			sal_obj.pr_no_hrs[2]=empdetail.no_hrs[2];
			sal_obj.project_counter=empdetail.pr_count;
			sal_obj.pr_bonus=empdetail.incentive;
			sal_obj.epf=empdetail.epfdeduct;
			sal_obj.income_tax=empdetail.income_deduct;
			sal_obj.fi_salary=empdetail.total_salary;
			empsal_list.push_back(sal_obj);
			fr.read((char *) &empdetail,sizeof(emp_details));
		}
		fr.close();
	}
}


/*******************************************************
* * FUNCTION NAME   : list_to_employee_file
*
* * DESCRIPTION     : This function writes the data into a employee_file from list
*
* * RETURN 	    :  ------
*
********************************************************/

void SALARY :: list_to_employee_file()
{
	fstream ff1;
	if(!empsal_list.empty())
	{
		ff1.open("Employee", ios::out);
		for(list<SALARY> :: iterator  t=empsal_list.begin(); t!=empsal_list.end();t++)
		{
			empdetail.employee_id=t->emp_id;
			strcpy(empdetail.employee_name,t->emp_name);
			strcpy(empdetail.department,t->dept);
			empdetail.basic_salary=t->salary;
			strcpy(empdetail.contact_number,t->contact);
			empdetail.project_id[0]=t->pr_no_prid[0];
			empdetail.project_id[1]=t->pr_no_prid[1];
			empdetail.project_id[2]=t->pr_no_prid[2];
			empdetail.no_hrs[0]=t->pr_no_hrs[0];
			empdetail.no_hrs[1]=t->pr_no_hrs[1];
			empdetail.no_hrs[2]=t->pr_no_hrs[2];
			empdetail.pr_count=t->project_counter;
			empdetail.incentive=t->pr_bonus;
			empdetail.epfdeduct=t->epf;
			empdetail.income_deduct=t->income_tax;
			empdetail.total_salary=t->fi_salary;
			ff1.write((char *) &empdetail , sizeof(emp_details));
		}
		ff1.close();
	}
}



/*******************************************************
* * FUNCTION NAME   : project_file_to_list
*
* * DESCRIPTION     : This function creates or open an existing project file and 
* 		      read data from file to list  
*
* * RETURN 	    :  ------
*
********************************************************/
void PROJECT::project_file_to_list()
{
	ifstream fr("Project");
	//fr.open("Project",ios::in);
	if(fr)
	{
		cout<<"here1";
		fr.read((char *) &tmp,sizeof(temp));
		PROJECT obj; 
		while(!fr.eof())
		{
			strcpy(obj.pr_name,tmp.project_name);
			obj.team_mem=tmp.t_members;
			obj.pr_id=tmp.project_id;
			pr_list.push_back(obj);
			fr.read((char *) &tmp,sizeof(temp));
		}
		fr.close();
	}
}

/*******************************************************
* * FUNCTION NAME   : list_to_project_file
*
* * DESCRIPTION     : This function writes the data into a project_file from list
*
* * RETURN 	    :  ------
*
********************************************************/



void PROJECT :: list_to_project_file()
{
	fstream ff1;
	if(!pr_list.empty())
	{
		ff1.open("Project", ios::out);
		for(list<PROJECT> :: iterator  t=pr_list.begin(); t!=pr_list.end();t++)
		{
			strcpy(tmp.project_name,t->pr_name);
			tmp.t_members=t->team_mem;
			tmp.project_id=t->pr_id;
			ff1.write((char *) &tmp , sizeof(temp));
		}
		ff1.close();
	}
}












