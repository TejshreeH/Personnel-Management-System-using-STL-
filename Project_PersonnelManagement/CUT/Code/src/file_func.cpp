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

int employee_file_to_list()
{	fstream emp_file;
	emp_file.open("Employee File",ios::in | ios::binary);
	if(!emp_file)
	{
		cout<<"Cannot open the file"<<endl;
		return EXIT_FAILURE;
	}
	emp_file.read((char *) &obj, sizeof(obj));


	while(!emp_file.eof())
	{
		empsal_list.push_back(obj);
		emp_file.read((char *) &obj, sizeof(obj));
	}

	emp_file.close();

	return EXIT_SUCCESS;
}


/*******************************************************
* * FUNCTION NAME   : list_to_employee_file
*
* * DESCRIPTION     : This function writes the data into a employee_file from list
*
* * RETURN 	    :  ------
*
********************************************************/


int list_to_employee_file()
{
	fstream emp_file;
	emp_file.open("Employee File", ios::out|ios::binary);
	if(!emp_file)
	{
		cout<<"Employee File doesn't exists."<<endl;
		return EXIT_FAILURE;
	}
	if(!empsal_list.empty())
	{
		for(SALARY st:empsal_list)
		{
			emp_file.write((char *) &st , sizeof(st));
		}
		emp_file.close();
		empsal_list.clear();
	}
		return EXIT_SUCCESS;
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

int project_file_to_list()
{
	fstream project_file;
	project_file.open("Project File",ios::in | ios::binary);
	if(!project_file)
	{
		cout<<"Cannot open the file"<<endl;
		return EXIT_FAILURE;
	}
	project_file.read((char *) &pr_obj, sizeof(pr_obj));
	while(!project_file.eof())
	{
		pr_list.push_back(pr_obj);
		project_file.read((char *) &pr_obj, sizeof(pr_obj));
	}
	project_file.close();
	return EXIT_SUCCESS;
}


/*******************************************************
* * FUNCTION NAME   : list_to_project_file
*
* * DESCRIPTION     : This function writes the data into a project_file from list
*
* * RETURN 	    :  ------
*
********************************************************/


int list_to_project_file()
{
	fstream project_file;
	project_file.open("Project File", ios::out|ios::binary);
	if(!project_file)
	{
		cout<<"Project File doesn't exists."<<endl;
		return EXIT_FAILURE;
	}
	if(!pr_list.empty())
	{
		for(PROJECT st:pr_list)
		{
			project_file.write((char *) &st , sizeof(st));
		}
		project_file.close();
		pr_list.clear();
	}
		return EXIT_SUCCESS;
}
