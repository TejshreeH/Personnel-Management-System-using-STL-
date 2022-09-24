/*****************************************************************************************
 *
 * FILE NAME   : func.cpp
 *
 * DESCRPITION : This file defines the functions in the employee menu 
 *               to perform various operations in the employee database
 *
 * REVISION    :
 *
 * 	DATE		NAME		REASON
 *
 *       ----           -------         ------
 *
 ******************************************************************************************/       

#include<iostream>
#include<iomanip>
#include <list>
#include <vector>
#include <mutex>
#include <thread>
#include "personnel.hpp"
#include "proj_func.cpp"
using namespace std;
mutex accum_mutex;

/******************************************************************************************
 * CLASS NAME  : EMPPRO
 *
 * DESCRIPTION : This is the base class and consists of various variable
 *               initializations used in the employee function
 *
 * RETURN      : ---
 *
*****************************************************************************************/               

class EMPPRO
{
	protected:
		int emp_id;
		string emp_name;
		string dept;
		double salary;
		string contact;
	public:
		EMPPRO()
		{
			int emp_id=100;
			string name= " ";
			string dept= " ";
			double salary= 0;
			string contact=" ";
		}
		void getdata();
		void view();
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

class EMP:public EMPPRO
{
	protected:
		vector<int>pr_no_prid;
		vector<int>pr_no_hrs;
		int project_counter=0;
	public:
		EMP()
		{
			int proj_id=0;
			int w_hrs=0;
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

class SALARY: public EMP
{
	protected:
		double pr_bonus;
		double epf;
		double prof_tax;
		double income_tax;
		double fi_salary;
	public:
		SALARY()
		{
			double epf=0;
			double prof_tax=200;
			double income_tax=0;
			double fi_salary=0;
		}
		void calc_pr_bonus(double);
		void calc_fi_salary();
		void getdata1();
		void view1();
		void editdata();
		void deldata();
		void salary_view();
		void emp_proj_details();
		void emp_list_with_3_projects();
};


list <EMP> emp_list; // Employee details list declaration
list <SALARY> empsal_list;// Salary list Declaration
SALARY obj;

/******************************************************************************************
 *
 * FUNCTION NAME  : getdata()
 *
 * DESCRIPTION    :  This function  writes the contents in to the employee database by
 *                 validating the input
 *
 * RETURN         : No Returns 
 *
 ****************************************************************************************/

void EMPPRO::getdata()
{
	int id=100;
	if(empsal_list.empty())
	{
		id=100;
	}
	else
	{
		for(SALARY it:empsal_list)
		{
			if(id<it.emp_id)
				id=it.emp_id;
		}
	}

	id+=1;
	obj.emp_id=id;
	cout<<"\n\nYou are entering the details for Employee Id: "<<obj.emp_id<<endl<<endl;

	while(1)
	{
		cout<<"\n  Enter the employee name - ";
		cin.ignore(1,'\n');
		getline(cin,emp_name);
		try
		{
			if(emp_name.length()<3 || emp_name.length()>20)
			{
				throw emp_name;
			}
		}
		catch(string& e)
		{
			cout<<"\n\n ---Name should be more than 2 and less than 20!!! \n   TRY AGAIN !!!!!!!\n\n";
			continue;
		}
		try
		{
		for(int i=0;i<emp_name.length();i++)
		{
			if(!isalpha(emp_name[i]))
			{
				throw emp_name;
			}
		}
		}
		catch(string i)
		{
			cout<<"\n\n---Name should only consists of alphabets!!!!\n   TRY AGAIN !!!!!!!\n\n";
			continue;
		}
		
			break;
	}		
	while(1)
	{
		cout<<"  Enter Department- ";
		cin>>dept;
		for(int i=0;i<dept.length();i++)
		{
			dept[i]=toupper(dept[i]);
		}
		if(dept=="IT" || dept=="HR" || dept=="SALES" || dept=="MARKETING")
		{
			break;
		}
		else
		{
			cout<<"\n---Department should be either IT Or HR or SALES or MARKETING --\n";
			continue;
		}
	}
	while(1)
	{
		cout<<"  Enter Contact Number- ";
		cin>>contact;
		try
		{
		if(contact.length()!=10)
		{
			throw contact;
		}
		}
		catch(string g)
		{
			cout<<"\n ----Mobile number should be 10 digits!!!!\n";
			continue;
		}
		try
		{
		for(int i=0;i<contact.length();i++)
		{
			if(!isdigit(contact[i]))
			{
			    throw contact;
			}
		}
		}
		catch(string f)
		{
			cout<<"\n ----Mobile number should only consists of digits!!!\n";
			continue;
		}
			break;
	}
	while(1)
	{
		string salary1;
		cout<<"   Enter the Employee's Basic  Salary- ";
		cin>>salary1;
		try
		{
		for(int i=0;i<salary1.length();i++)
		{
			if(!isdigit(salary1[i]))
			{
				throw salary1;
			}
		}
		}
		catch(string e)
		{
			cout<<"\n ---Salary should a number !!!\n";
			continue;
		}
			salary=stod(salary1);
			if(salary<=0)
			{
				cout<<"\n ----Basic Salary should be greater than Rs. 10,000!!!\n";
				continue;
			}
			else if(salary<10000 || salary>200000)
			{
				cout<<"\n ----Salary should be in the range 10000 to 200000!!!!\n";
				continue;
			}
			else
				break;
		}
	}

/*  view the details of the employee from the employee data base */

void EMPPRO::view()
{

	cout<<endl<<"   "<<emp_id<<"          "<<emp_name<<"          "<<dept<<"          "<<salary<<"          "<<contact<<endl;
}

/******************************************************************************************
 *
 * FUNCTION NAME  : getdata1()
 *
 * DESCRIPTION    :  This function  add project details to the employee in the employee database by
 *                   validating the input
 *
 * RETURN         : No Returns 
 *
******************************************************************************************/

void SALARY::getdata1()
{
	getdata();
	string yn;
	int f=0;
	int proj_id;
	int w_hrs;
	pr_no_prid.clear();
	pr_no_hrs.clear();
	while(1)
	{
	cout<<setfill(' ')<<endl;
	cout<<"  Do you wish to add project for the employee?"<<endl<<"---Enter yes or no"<<endl;
	cin>>yn;
	try
	{
	for(int i=0;i<yn.length();i++)
	{
		if(isdigit(yn[i]))
		{
			throw yn;
		}
	}
	}
	catch(string x)
	{
		cout<<"\n!!!! choice should be either yes or no!!!!!\n";
		continue;
	}
	try
	{
		if((yn!="yes") && (yn!="no"))
		{
			f=1;
			throw yn;
		}
	}
	catch (string y)
	{
		if(f==1)
		{
			cout<<"\n\n -------choice should be either yes or no -------\n\n";
			pr_no_prid={0};
			pr_no_hrs={0};
                         continue;
		}
	}
	break;
}
	project_counter=0;
	int ch=0;
	while(ch==0)
	{       
		if(yn=="yes" && project_counter<3)
		{
			cout<<"  Enter the project id: ";
			cin>>proj_id;
			if(pr_list.empty())
			{
				cout<<"----Your Database currently have no projects----"<<endl;
				pr_no_prid={0};
				pr_no_hrs={0};
				break;
			}
			else
			{
				int flag;
		for (std::list<PROJECT>::iterator it = pr_list.begin(); it != pr_list.end(); ++it)
			{
				flag=0;
				if(it->pr_id==proj_id)
				{
					cout<<"Enter the no. of hours employee worked on this project: ";
					cin>>w_hrs;
					pr_no_prid.push_back(proj_id);
					pr_no_hrs.push_back(w_hrs);
					project_counter++;
					break;
				}
				else
				{
					flag=1;
					continue;
				}
			}
					if(flag==1)
					cout<<"This id doesn't exists!!!!!"<<endl;
			}
			while(1)
			{
				string choice;
				cout<<"   Press 0 to add projects to employee  "<<endl;
				cin>>choice;
				try
				{
				for(int i=0;i<choice.length();i++)
				{
					if(!isdigit(choice[i]))
					{
						throw choice;
					}
				}
				}
				catch (string y)
				{
					cout<<"\n ---choice should be digit !!!\n";
					continue;
				}
					ch=stoi(choice);
					break;
			}
			if(ch==0)
			{
				continue;
			}
			else if(ch>0)
			{
				break;
			}
			else
			{
				break;
			}

		}
		else
		{
			break;
		}
			if(project_counter>2)
			{
				cout<<"---This employee already have 3 Projects. Cannot assign any more projects---"<<endl;
				break;
			}
		

	}
}


/* view the employee project report for all employees in the employee list*/

void SALARY::view1()
{
		cout<<endl<<"Employee Id: "<<emp_id<<endl<<"Employee Name: "<<emp_name<<endl;
		cout<<endl<<"Department: "<<dept<<endl<<"Contact Number: "<<contact<<endl;
		cout<<endl<<"No. of Projects: "<<project_counter<<endl;
		if(project_counter==0)
		{
			cout<<"Not assigned at any project yet";
		}
		else if(project_counter==1)
		{
		cout<<endl<<"Project 1 ID: "<<pr_no_prid[0]<<"		"<<"No. of hours worked on project 1: "<<pr_no_hrs[0]<<endl;
		}
		else if(project_counter==2)
		{
		cout<<endl<<"Project 1 ID: "<<pr_no_prid[0]<<"		"<<"No. of hours worked on project 1: "<<pr_no_hrs[0]<<endl;
		cout<<endl<<"Project 2 ID: "<<pr_no_prid[1]<<"		"<<"No. of hours worked on project 2: "<<pr_no_hrs[1]<<endl;
		}
		else
		{
		cout<<endl<<"Project 1 ID: "<<pr_no_prid[0]<<"		"<<"No. of hours worked on project 1: "<<pr_no_hrs[0]<<endl;
		cout<<endl<<"Project 2 ID: "<<pr_no_prid[1]<<"		"<<"No. of hours worked on project 2: "<<pr_no_hrs[1]<<endl;
		cout<<endl<<"Project 3 ID: "<<pr_no_prid[2]<<"		"<<"No. of hours worked on project 3: "<<pr_no_hrs[2]<<endl;
		}
}

/*view the employee project report for the particular employee by entering the employee id*/

void SALARY :: emp_proj_details()
{
	if(empsal_list.empty())
	{
		cout<<"   ---List is empty----"<<endl;
	}
	else
	{
	int ed;
	cout<<"Enter the employee id to see the project details: ";
	cin>>ed;
	int flag;
	for(SALARY st:empsal_list)
	{
		flag=0;
		if(ed==st.emp_id)
		{
			cout<<"------------------------------------------------------------"<<endl;
			cout<<"  Employee Id	      Name	      Department	 Project ID"<<endl;
			st.view1();
			cout<<"------------------------------------------------------------"<<endl;
			break;
		}
		else
		{
			flag=1;
			continue;
		}
	}
		if(flag==1)
			cout<<"This id doesn't exists"<<endl;
	}
}

/*view the employees working on 3 projects at a time from the employee list*/

void SALARY :: emp_list_with_3_projects()
{
	if(empsal_list.empty())
	{
		cout<<"   ---List is empty----"<<endl;
	}
	else
	{
		int flag;
	for(SALARY st:empsal_list)
	{
		flag=0;
		if(st.project_counter==3)
		{
			cout<<"------------------------------------------------------------"<<endl;
			cout<<"  Employee Id	      Name	      Department	 Project ID"<<endl;
			st.view1();
			cout<<"------------------------------------------------------------"<<endl;
			break;
		}
		else
		{
			flag=1;
			continue;
		}
	}
		if(flag==1)
			cout<<"No employee is currently working on 3 Projects."<<endl;

	}
}

/******************************************************************************************
 *
 * FUNCTION NAME  : editdata()
 *
 * DESCRIPTION    :  This function  edit the details of employee in the employee database by
 *                   validating the input
 *
 * RETURN         : NO RETURN
 *
 ****************************************************************************************/

void SALARY::editdata()
{
	int ed;
	string eid;
	int choice;
	string ch;
	if(empsal_list.empty())
	{
		cout<<"---List is empty---"<<endl;
	}
	else
	{
		while(1)
		{
		cout<<"  Enter the employee id to edit: ";
		cin>>eid;
		try
		{
			for(int i=0;i<eid.length();i++)
			{
				if(!isdigit(eid[i]))
				{
					throw eid;
				}
			}
		}
		catch (string n)
		{
			cout<<"\n\n Employee id should be a digit !!!!!!\n\n";
			continue;
		}
		
		ed=stoi(eid);
		break;
		}
		string n_name;
		string n_dept;
		string n_contact;
		int n_pr[6];
		string pr[6];
		for (std::list<SALARY>::iterator it = empsal_list.begin(); it != empsal_list.end(); ++it)
		{
			if(it->emp_id==ed)
			{

				while(choice!=8)
				{
					cout<<"Which detail of Employee Id "<<ed<<"you want to change?"<<endl;
					cout<<"1. Name"<<endl<<"2. Department"<<endl<<"3. Contact Number"<<endl<<"4. Project 1"<<endl<<"5. Project 2"<<endl<<"6. Project 3"<<endl<<"7.salary"<<endl<<"8.Exit"<<endl;
					while(1)
					{
					cout<<endl<<"Enter choice: "<<endl;
					cin>>ch;
					try
					{
					for(int i=0;i<ch.length();i++)
					{
						if(!isdigit(ch[i]))
						{
							throw ch;
						}
					}
					}
					catch (string z)
					{
						cout<<"\n---Choice should be a digit !!!!!\n";
					        continue;
					}
						choice=stoi(ch);
						break;
					}

						switch(choice)
						{
							case 1:
								{
									while(1)
									{
									cout<<"Enter the new name for Employee ID "<<ed<<": "<<endl;
									cin>>n_name;
									try
									{
										for(int i=0;i<n_name.length();i++)
										{
											if(!isalpha(n_name[i]))
											{
											  throw n_name;
											}
										}
									}
									catch(string p)
									{
                                                                            cout<<"\n -----Name should not contain any digits!!!!!!\n\n";
						                             continue;
									     }			     
		                                                        try
		                                                        {
			                                                     if(emp_name.length()<3 || emp_name.length()>20)
			                                                        {           
				                                                       throw emp_name;
			                                                          }
		                                                         }
		                                                        catch(string d)
		                                                          {            
			                                                   cout<<"\n\n ---Name should be more than 2 and less than 20!!! \n   TRY AGAIN !!!!!!!\n\n";
			                                                     continue;
									  }
									break;
	                                                             }
									it->emp_name=n_name;
									cout<<"----New name is "<<it->emp_name<<endl;
									break;
							            }
					              case 2:
								{
									while(1)
									{
										cout<<"Enter the new Department for Employee ID "<<ed<<": "<<endl;
										cin>>n_dept;
										try
										{
										for(int i=0;i<n_dept.length();i++)
										{  
											n_dept[i]=toupper(n_dept[i]);
										}
										       
											if(n_dept=="IT" || n_dept=="HR" || n_dept=="SALES" || n_dept=="MARKETING")
											{
												break;
											}
											else
											{
												throw n_dept;
											}
										}
										catch(string m)
										{
											cout<<"\n\n Department name should be either IT OR HR OR SALES OR MARKETING !!!!\n\n";
											continue;
										}

										break;
									}

										it->dept=n_dept;
										cout<<"----New Department is "<<it->dept<<endl;
									        break;
									
									}
							case 3:
								{
									cout<<"Enter the new contact for Employee ID "<<ed<<": "<<endl;
									cin.ignore(1,'\n');
									getline(cin,n_contact);
									try
									{
										for(int i=0;i<n_contact.length();i++)
										{
											if(!isdigit(n_contact[i]))
											{
											  throw n_contact;
											}
										}
									}
									catch(string r)
									{
                                                                            cout<<"\n -----Name should not contain any digits!!!!!!\n\n";
						                             continue;
									     }			     
		                                                        try
		                                                         {
		                                                           if(n_contact.length()!=10)
		                                                             {
			                                                        throw n_contact;
		                                                              }
		                                                          }
		                                                         catch(string g)
		                                                          {
			                                                   cout<<"\n ----Mobile number should be 10 digits!!!!\n";
			                                                     continue;
		                                                           }
									it->contact=n_contact;
									break;
								}
							case 4:
								{
									
									cout<<"Enter the new Project 1 ID for Employee ID "<<ed<<": "<<endl;
									cin>>pr[0];
									try
									{
										for(int i=0;i<pr[0].length();i++)
										{
											if(!isdigit(pr[0][i]))
											{
											  throw pr[0];
											}
										}
									}
									catch(string c)
									{
										cout<<"\n ----Project ID should only contain digits!!!!!!\n\n";
										continue;
									}
									n_pr[0]=stoi(pr[0]);
					                                int flag=0;				
									for (std::list<PROJECT>::iterator st = pr_list.begin(); st != pr_list.end(); ++st)
									{
										if(st->pr_id==n_pr[0])
										{
											flag=1;
											break;
								      		}
									}	
										if(flag==1)
										{
											cout<<"\n\n ------Project Id exits!! -------\n\n";
											it->pr_no_prid[0]=n_pr[0];
											project_counter++;
											cout<<"count"<<project_counter;
										}
										else
										{
											cout<<"\n\n ------Project Id does not exits!! -------\n\n";
                                                                                         break;
										}
										
									cout<<"Enter the no. of hours worked : ";
									cin>>pr[1];
									try
									{
										for(int i=0;i<pr[1].length();i++)
										{
											if(!isdigit(pr[1][i]))
											{
												throw pr[1];
											}
										}
									}
									catch(string d)
									{
										cout<<"\n ----Number of houres worked should be  digit!!!!!!\n\n";
										continue;
									}			     
									n_pr[1]=stoi(pr[1]);
									it->pr_no_hrs[0]=n_pr[1];
									break;
								}
							case 5:
								{
									cout<<"Enter the new Project 2 ID for Employee ID "<<ed<<": "<<endl;
									cin>>pr[2];
									try
									{
										for(int i=0;i<pr[2].length();i++)
										{
											if(!isdigit(pr[2][i]))
											{
												throw pr[2];
											}
										}
									}
									catch(string b)
									{
										cout<<"\n ----Project ID should only contain digits!!!!!!\n\n";
										continue;
									}
									n_pr[2]=stoi(pr[2]);
					                                int flag=0;				
									for (std::list<PROJECT>::iterator st = pr_list.begin(); st != pr_list.end(); ++st)
									{
										if(st->pr_id==n_pr[2])
										{
											flag=1;
											break;
								      		}
									}	
										if(flag==1)
										{
											cout<<"\n\n ------Project Id exits!! -------\n\n";
											it->pr_no_prid[1]=n_pr[2];
											project_counter++;
										}
										else
										{
											cout<<"\n\n ------Project Id does not exits!! -------\n\n";
                                                                                         break;
										}
										
									cout<<"Enter the no. of hours worked : ";
									cin>>pr[3];
									try
									{
										for(int i=0;i<pr[3].length();i++)
										{
											if(!isdigit(pr[3][i]))
											{
												throw pr[3];
											}
										}
									}
									catch(string c)
									{
										cout<<"\n ----Number of working hours should be  digit!!!!!!\n\n";
										continue;
									}
									n_pr[3]=stoi(pr[3]);
									it->pr_no_hrs[1]=n_pr[3];
									break;
								}
							case 6:
								{
									cout<<"Enter the new Project 3 ID for Employee ID "<<ed<<": "<<endl;
									cin>>pr[4];
									try
									{
										for(int i=0;i<pr[4].length();i++)
										{
											if(!isdigit(pr[4][i]))
											{
											  throw pr[4];
											}
										}
									}
									catch(string a)
									{
                                                                            cout<<"\n ----Project ID should only contain digits!!!!!!\n\n";
						                             continue;
									     }
						                          n_pr[4]=stoi(pr[4]);
					                                    int flag=0;				  
									for (std::list<PROJECT>::iterator st = pr_list.begin(); st != pr_list.end(); ++st)
									{
										if(st->pr_id==n_pr[4])
										{
											flag=1;
											break;
								      		}
									}	
										if(flag==1)
										{
											cout<<"\n\n ------Project Id  exits!! -------\n\n";
											it->pr_no_prid[1]=n_pr[4];
											project_counter++;
										}
										else
										{
											cout<<"\n\n ------Project Id does not exits!! -------\n\n";
                                                                                         break;
										}
									
									cout<<"Enter the no. of hours worked : ";
									cin>>pr[5];
									try
									{
										for(int i=0;i<pr[5].length();i++)
										{
											if(!isdigit(pr[5][i]))
											{
											  throw pr[5];
											}
										}
									}
									catch(string c)
									{
                                                                            cout<<"\n -NUmber of hours should be  digit!!!!!!\n\n";
						                             continue;
									     }
						                         n_pr[5]=stoi(pr[5]);			     
									it->pr_no_hrs[2]=n_pr[5];
									break;
								}
							case 7:
								{
									double n_salary;
									string sal;
									while(1)
									{
										cout<<"Enter the new salary for Employee ID "<<ed<<": "<<endl;
										cin>>sal;
										try
										{
											for(int i=0;i<sal.length();i++)
											{
												if(!isdigit(sal[i]))
												{
													throw sal;
												}
											}
										}
										catch(string e)
										{
											cout<<"\n ---Salary should a number !!!\n";
											continue;
										}
                                                                                  n_salary=stod(sal);
										if(n_salary<=0)
										{
											cout<<"\n ----Basic Salary should be greater than Rs. 10,000!!!\n";
											continue;
										}
										else if(n_salary<10000 || n_salary>200000)
										{
											cout<<"\n ----Salary should be in the range 10000 to 200000!!!!\n";
											continue;
										}
										else
											break;
									}

									it->salary=n_salary;
									cout<<"----New salary is "<<it->salary<<endl;
									break;
								}

							case 8: break;
							default:cout<<endl<<"----INVALID CHOICE----"<<endl;
						}

					}
				}
			else
				cout<<"--This employee id doesn't exist!!!"<<endl;
		}
	}
}

/******************************************************************************************
 *
 * FUNCTION NAME  : deldata()
 *
 * DESCRIPTION    :  This function deletes the employee details from the employee database
 *
 * RETURN         : No Returns 
 *
 ****************************************************************************************/

void SALARY::deldata()
{

	if(empsal_list.empty())
	{
		cout<<"   ---List is empty----"<<endl;
	}
	else{
		int ed;
		int flag;
		cout<<"Enter the employee id to delete: ";
		cin>>ed;
		for (std::list<SALARY>::iterator it = empsal_list.begin(); it != empsal_list.end(); ++it)
		{
			flag=0;
			if(it->emp_id==ed)
			{
				if(it->pr_no_prid[0]==0)
				{
					it = empsal_list.erase(it);
					cout<<"*****Deleted Successfully*****"<<endl;
				}
				else
					cout<<"\n   This employee has some projects . It cannot be removed\n";
				break;
			}
			else
			{
				flag=1;
				continue;
			}
		}
			if(flag==1)
				cout<<"This employee id doesn't exists!!!!"<<endl;
	}
}

/* calculating the bonus for the employees working on 3 projects at a time */ 

void SALARY::calc_pr_bonus(double sal)
{
	int ed;
	int working_days=23;
	cout<<"Enter the employee id : ";
	cin>>ed;
	for (std::list<SALARY>::iterator it = empsal_list.begin(); it != empsal_list.end(); ++it)
	{
		if(it->emp_id==ed)
		{
			if(it->pr_no_prid[0]==0)
				pr_bonus=0;
			else
			{
				pr_bonus = double ((45 * 9 * working_days) + (it->pr_no_hrs[0]*10) + (it->pr_no_hrs[1]*10) + (it->pr_no_hrs[2]*10));
				cout<<"  Function pr_bonus"<<pr_bonus;
				it->pr_bonus=pr_bonus;
			}
		}
	}
}

/*  view the final salary of all the employees after adding the bonus and deducting the incentives and income tax in the base salary*/

void SALARY::salary_view()
{
	if(empsal_list.empty())
	{
		cout<<"   ---List is empty----"<<endl;
	}
	else
	{
	double sal;
	cout<<"Employee Id           Employee Name           Salary"<<endl;
	for (std::list<SALARY>::iterator it = empsal_list.begin(); it != empsal_list.end(); ++it)
	{
		sal=it->salary;
		if(it->pr_no_prid[0]==0)
			it->pr_bonus=0;
		else
		{
			it->pr_bonus = double ((45 * 9 * 23) + (it->pr_no_hrs[0]*10) + (it->pr_no_hrs[1]*10) + (it->pr_no_hrs[2]*10));
		}

		double bonus =it->pr_bonus;
		it->epf = (sal*8.5)/100;
		it->income_tax = (((sal*12)*15)/100)/12;
		it->fi_salary = (sal+bonus) - it->income_tax - it->epf;
		cout<<"----------------------------------------------------------------------"<<endl;
		cout<<it->emp_id<<"               "<<it->emp_name<<"            "<<it->fi_salary<<endl;
		cout<<"----------------------------------------------------------------------"<<endl;
	}
	}
}

/* view the final salary of an employee in  the list by entering the employee id */

void SALARY::calc_fi_salary()
{
	if(empsal_list.empty())
	{
		cout<<"   ---List is empty----"<<endl;
	}
	else
	{
	double sal;
	int ed;
	int flag;
	int working_days=23;

	cout<<"Enter the employee id : ";
	cin>>ed;
	for (std::list<SALARY>::iterator it = empsal_list.begin(); it != empsal_list.end(); ++it)
	{

		if(it->emp_id==ed)
		{
		flag=0;
			sal=it->salary;
			if(it->pr_no_prid[0]==0)
				it->pr_bonus=0;
			else
			{
				it->pr_bonus = double ((45 * 9 * 23) + (it->pr_no_hrs[0]*10) + (it->pr_no_hrs[1]*10) + (it->pr_no_hrs[2]*10));
			}

			double bonus =it->pr_bonus;
			it->epf = (sal*8.5)/100;
			it->income_tax = (((sal*12)*15)/100)/12;
			it->fi_salary = (sal+bonus) - it->income_tax - it->epf;
			cout<<"----------------------------------------------------------------------"<<endl;
			cout<<"             MARSPRO ORGANISATION "<<endl;
			cout<<"             Pay Slip for employee "<<it->emp_name<<endl;
			cout<<"----------------------------------------------------------------------"<<endl;
			cout<<"Basic Salary           Project Bonus       ||    EPF Deduction       Income Tax Deduction"<<endl;
			cout<<sal<<"                    "<<it->pr_bonus<<"                      "<<it->epf<<"                   "<<it->income_tax<<endl;
			cout<<endl<<endl<<"Total Salary ="<<it->fi_salary<<endl<<endl;
			break;

		}
			else
			{
				flag=1;
				continue;
			}
		}
			if(flag==1)
				cout<<"This employee id doesn't exists!!!!"<<endl;

	}
}






/* This function calls the getdata1 function and pushes the info in to the employee list */

void addemp()
{
	int ch=0;
	while(ch==0)
	{
		obj.getdata1();
		emp_list.push_back(obj);
		empsal_list.push_back(obj);
		while(1)
		{
                  string ch1;
		  int f2=0;
		cout<<endl<<" ---Enter 0 to continue adding employee details -";
		cin>>ch1;
		for(int i=0;i<ch1.length();i++)
		{
			if(!isdigit(ch1[i]))
			{
				f2=1;
				break;
			}
		}
		if(f2==1)
		{
			cout<<"\n\n choice should be a digit !!!!!!\n\n        TRY AGAIN        \n\n";
			continue;
		}
		else
		{
			ch=stoi(ch1);
			break;
		}
		}
	}

}
 
/* This function calls the view1 function and displays the employee list */

void viewemp()
{
	for(SALARY st:empsal_list)
	{
		cout<<"-------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
		st.view1();
		cout<<"-------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
	}

}

/* This function calls the editdata function and edits the details in theemployee list */

void editemp()
{
	obj.editdata();
}

/* This function calls the deldata function and deletes the details in the employee list */

void delemp()
{
	obj.deldata();
}

/* This function calls the calc_fi_salary function and displays the salary for all the employee in  employee list */

void payreport()

	
{

	accum_mutex.lock();
	obj.calc_fi_salary();
      
	accum_mutex.unlock();
}

/* This function calls the emp_list_with_3_projects function and displays the list of employees working on 3 projects in  the employee list */

void emp_proj_report()
{
	obj.emp_list_with_3_projects();
}

/* This function calls the view1 function and displays the employee details along with number of projects */

void view_emp_record()
{
	accum_mutex.lock();

	if(empsal_list.empty())
	{
		cout<<"Your employee database doesn't have any records."<<endl;
	}
	else
	{
		obj.emp_proj_details();

	}
	accum_mutex.unlock();
}

/* This function calls the salary_view function and displays the details of salary */ 

void emp_salary_list()
{
	obj.salary_view();
}
