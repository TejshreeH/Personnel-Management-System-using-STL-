/********************************************************************************************
 * * FILE NAME           : personnel.hpp
 *
 * * DESCRIPTION         : This file consists of function declarations used in various functions
 *
 * * REVISION HISTORY    :
 *
 *	DATE		NAME		REASON
 *
 *	------          ------          -------
 *
 *******************************************************************************************/
#ifndef H_PERSONNEL
#define H_PERSONNEL
#include <iostream>
#include <vector>
#include <string>
#include <list>
using namespace std;

int employee();
int project();
int emp_salary_list();
int query();
int payreport();
int emp_with_3_proj_report();
int addemp();
int editemp();
int delemp();
int viewemp();
int addproj();
int editproj();
int delproj();
int viewproj();
int view_emp_record();

/******************************************************************************************
 * CLASS NAME  : EMPPRO
 *
 * DESCRIPTION : This is the base class and consists of various variable
 *               initializations used in the employee function
 *
 * RETURN      : ---
 *
 *****************************************************************************************/               

class EMPLOYEE
{
	protected:
		int emp_id;
		string emp_name;
		string dept;
		double salary;
		string contact;
	public:
		EMPLOYEE()
		{
			int emp_id=100;
			string name= " ";
			string dept= " ";
			double salary= 0;
			string contact=" ";
		}
		void getdata();
};

/***********************************************************************************************************
 * CLASS NAME  : EMP
 *
 * DESCRIPTION : This is the derived class and inheriting from the base class EMPPRO 
 *               and  consists of various variable initializations used in the project function
 *
 * RETURN      : ----
 * 
 ***********************************************************************************************************/		 

class EMPLOYEE_PROJECT:public EMPLOYEE
{
	protected:
		vector<int>pr_no_prid;
		vector<int>pr_no_hrs;
		int project_counter;
	public:
		EMPLOYEE_PROJECT()
		{
			project_counter=0;
		}
};
/***********************************************************************************************************
 * CLASS NAME  : SALARY
 *
 * DESCRIPTION : This is the multi level derived class and inheriting from the  class EMP 
 *               and  consists of various variable initializations used in the employee function
 *
 * RETURN      : ----
 * 
 **********************************************************************************************************/		 

class SALARY: public EMPLOYEE_PROJECT
{
	protected:
		double pr_bonus;
		double epf;
		double income_tax;
		double fi_salary;
	public:
		SALARY()
		{
			double epf=0;
			double income_tax=0;
			double fi_salary=0;
		}
		void calc_fi_salary();
		void add_employee();
		void view1();
		void view_employee();
		void editdata();
		void deldata();
		void salary_view();
		void view_emp_record();
		void emp_list_with_3_projects();
};

/******************************************************************************************
 * CLASS NAME  : PROJECT
 *
 * DESCRIPTION : This is the base class and consists of various variable
 *                initializations used in the project function
 *
 * RETURN      : ---
 *
 ******************************************************************************************/

class PROJECT
{
	private:
		string pr_name;
	public:
		int team_mem;
		int pr_id;
		void getdata();
		void view();
		void edit();
		void del_project();
		void project_query();
};

list <SALARY> empsal_list;// Salary list Declaration
SALARY obj;
list <PROJECT> pr_list;
PROJECT pr_obj;





#endif
