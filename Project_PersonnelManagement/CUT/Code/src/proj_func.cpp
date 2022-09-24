
/*****************************************************************************************
 *
 * FILE NAME   : proj_func.cpp
 *
 * DESCRPITION : This file defines the functions in the project menu 
 *               to perform various operations in the project database
 *
 * REVISION    :
 *
 * 	DATE		NAME		REASON
 *
 *       ----           -------         ------
 *
 *******************************************************************************************/

#include<iostream>
#include "personnel.hpp"
#include<cstring>
#include<ctype.h>
#include <list>
using namespace std;

/******************************************************************************************
 * CLASS NAME  : PRO
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
		int team_mem;
	public:
		int pr_id;
		void getdata();
		void view();
		void edit();
		void del_project();
		void project_query();
};

list <PROJECT> pr_list;
PROJECT pr_obj;

/******************************************************************************************
 *
 * FUNCTION NAME  : getdata()
 *
 * DESCRIPTION    : This function  writes the contents in to the project database by
 *                  validating the input
 *
 * RETURN         : No Returns 
 *
 ****************************************************************************************/

void PROJECT:: getdata()
{
	int id=2000;
	if(pr_list.empty())
	{
		id=2000;
	}
	else
	{
		for(PROJECT it:pr_list)
		{
			if(id<it.pr_id)
				id=it.pr_id;
		}
	}

	id+=1;
	pr_obj.pr_id=id;
	cout<<"You are entering the details for Employee Id: "<<pr_obj.pr_id<<endl;
	while(1)
	{
		cout<<endl<<"Enter the project name - \n";
		cin>>pr_name;
		try
		{
		if(pr_name.length()<3 || pr_name.length()>20)
		{
			throw pr_name;
		}
		}
		catch(string a)
		{
			cout<<"\n ---Project name should be more than 2 letters and less than 20!!!!!!\n";
			continue;
		}
		try
		{
		for(int i=0;i<pr_name.length();i++)
		{
			if(!isalpha(pr_name[i]))
			{
			      throw pr_name;
			}
		}
		}
		catch (string b)
		{
			cout<<"\n---Project name should only consists of alphabets!!!!\n";
			continue;
		}
		
         	break;
	}
	while(1)
	{
		string mem;
		cout<<endl<<" Enter no. of people working on this project: ";
		cin>>mem;
		try
		{
		for(int i=0;i<mem.length();i++)
		{
			if(!isdigit(mem[i]))
			{
				throw mem;
			}
		}
		}
		catch (string c)
		{
			cout<<"\n ---Number of members should be an integer !!!!\n";
			continue;
		}
			team_mem=stoi(mem);
			try
			{
			if(team_mem<1 || team_mem>15)
			{
				throw team_mem;
			}
			}
			catch (int d)
			{
				cout<<"\n---Team members should be atleast more than 1 and atmost less than 15!!!\n";
				continue;
			}
				break;
		}	
	}

/* This function displays the project details in project database*/

void PROJECT :: view()
{
	cout<<endl<<"   	"<<pr_id<<"        	"<<pr_name<<"		"<<team_mem<<endl;
}

/******************************************************************************************
 *
 * FUNCTION NAME  : edit()
 *
 * DESCRIPTION    :  This function  edit the details of project in the project database by
 *                   validating the input
 *
 * RETURN         : NO RETURN
 *
 ****************************************************************************************/

void PROJECT :: edit()
{
	int pro_id;
	string id2;
	int ch;
	int flag=0;
	string new_name;
	string new_mem;
	while(1)
	{
	cout<<"\n  Enter the project id to edit :  ";
	cin>>id2;
	try
	{
		for(int i=0;i<id2.length();i++)
		{
			if(!isdigit(id2[i]))
			{
				throw id2;
			}
		}
	}
	catch (string e)
	{
		cout<<"\n\n Project ID should be a digit !!!!!\n\n";
		continue;
	}
	pro_id=stoi(id2);
	break;
	}
	if(pr_list.empty())
	{
		cout<<"\n ----project list id empty!!!! \n";
		exit(0);
	}
	string ch1;
	for (std::list<PROJECT>::iterator it = pr_list.begin(); it != pr_list.end(); ++it)
	{
		if(it->pr_id==pro_id)
		{
			while(ch!=3)
			{
				cout<<"\nEnter which detail you want to edit with the project id"<<pro_id<<endl;
				cout<<"1.Project Name\n2.Number of team members working on it\n3.Return to main menu"<<endl;
				cin>>ch1;
				try
				{
				for(int i=0;i<ch1.length();i++)
				{
					if(!isdigit(ch1[i]))
					{
						throw ch1;
					}
				}
				}
				catch(string f)
				{
					cout<<"\n ---choice should a digit!!!!!! \n";
					continue;
				}
					ch=stoi(ch1);
					switch(ch)
					{
						case 1:
							{
							while(1)
							{
								cout<<"Enter the new name for project id "<<pro_id<<": "<<endl;
								cin.ignore(1,'\n');
								getline(cin,new_name);
								try
								{
									if(new_name.length()<3 || new_name.length()>20)
									{
										throw new_name;
									}
								}
								catch(string a)
								{
									cout<<"\n ---Project name should be more than 2 letters and less than 20!!!!!!\n";
									continue;
								}
								try
								{
									for(int i=0;i<new_name.length();i++)
									{
										if(!isalpha(new_name[i]))
										{
											throw new_name;
										}
									}
								}
								catch (string b)
								{
									cout<<"\n---Project name should only consists of alphabets!!!!\n";
									continue;
								}
							
							it->pr_name=new_name;
							cout<<"----New name is "<<it->pr_name<<endl;
							break;
							}
							break;
							}
						case 2:  
							{
									int team_mem1;
								while(1)
								{
									cout<<"Enter the new team members for Project ID "<<pro_id<<": "<<endl;
									cin>>new_mem;
										try
										{
											for(int i=0;i<new_mem.length();i++)
											{
												if(!isdigit(new_mem[i]))
												{
													throw new_mem;
												}
											}
										}
										catch (string c)
										{
											cout<<"\n ---Number of members should be an integer !!!!\n";
											continue;
										}
								                team_mem1=stoi(new_mem);
										try
										{
											if(team_mem1<1 || team_mem1>15)
											{
												throw team_mem1;
											}
										}
										catch (int d)
										{
											cout<<"\n---Team members should be atleast more than 1 and atmost less than 15!!!\n";
											continue;
										}
								it->team_mem=team_mem1;
								cout<<"----New team members are "<<it->team_mem<<endl;
								break;
								}
								break;
							}
						case 3:
							break;
						default:
							cout<<"\n---please  enter valid choice!!!!!!\n";
							continue;
					}
					break;	
				}

				flag=1;
				break;
			}
		}
	if(flag==1)
	{
		cout<<"\n********succesfully edited**********\n";
	}
	else
	{
		cout<<"\nproject with the project id "<<pro_id<<"does not exist!!!!\n";
	}
}

/******************************************************************************************
 *
 * FUNCTION NAME  : del_project()
 *
 * DESCRIPTION    : This function  delete the details of project in the project database
 *
 * RETURN         : NO RETURN
 *
 ****************************************************************************************/

void PROJECT::del_project()
{
	int p_id;
	string p1_id;
	while(1)
	{
	cout<<"Enter the project id to delete: ";
	cin>>p1_id;
	try
	{
		for(int i=0;i<p1_id.length();i++)
		{
			if(!isdigit(p1_id[i]))
			{
				throw p1_id;
			}
		}
	}
	catch (string q)
	{
		cout<<"\n\n  -------Project Id should be a digit !!!!!!\n\n";
		continue;
	}
        p_id=stoi(p1_id);
	break;
       }
	if(pr_list.empty())
	{
		cout<<"\n ----Project list is empty!!!!!! \n";
		exit(0);
	}
	int flag=0;
	for (std::list<PROJECT>::iterator it = pr_list.begin(); it != pr_list.end(); ++it)
	{
		if(it->pr_id==p_id)
		{
			it = pr_list.erase(it);
			flag=1;
			break;
		}
	}
	if(flag==1)
	{
		cout<<"\n ******* Succesfully deleted *******\n";
	}
	else
	{
		cout<<"\nproject with the project id "<<p_id<<" does not exist!!!!\n";
	}
}


/* This project_query displays the highest team members in the project*/

void PROJECT :: project_query()
{
	if(pr_list.empty())
	{
		cout<<"   ---List is empty----"<<endl;
	}
	else
	{
		std::list<PROJECT>::iterator st;
		st= pr_list.begin();
		int highest_no;
		highest_no=st->team_mem;
		for(PROJECT st:pr_list)
		{
			if(highest_no<=st.team_mem)
			{
				highest_no=st.team_mem;
			}

		}

	cout<<"------------------------------------------------------------------------------------"<<endl;
	cout<<"    Project Id	          Name		      Team Members "<<endl;
	for(PROJECT st:pr_list)
	{
		if(st.team_mem==highest_no)
		{
			cout<<"     "<<st.pr_id<<"                        "<<st.pr_name<<"                    "<<st.team_mem <<endl;
		}
	}
	cout<<"------------------------------------------------------------------------------------"<<endl;
	}

}

/* This function calls the getdata function and pushes the info in to the project list */

void addproj()
{
	int ch=0;
	string choice;
	int flag=0;
	while(ch==0)
	{
		pr_obj.getdata();
		pr_list.push_back(pr_obj);
		while(1)
		{
			cout<<endl<<"---Press 0 to continue-";
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
			catch (string x)
			{
				cout<<"\n ---choice should be digit !!!\n";
				continue;
			}
				ch=stoi(choice);
				if(ch==0)
				{
					pr_obj.getdata();
					pr_list.push_back(pr_obj);
					continue;
				}
				else
				{
					break;
				}
                         break;
			}
		}

	}

/* This function calls the viewproj function and displays the project list */

void viewproj()
{
	cout<<"------------------------------------------------------------------------------------"<<endl;
	cout<<"    Project Id	          Name		      Team Members "<<endl;
	for(PROJECT st:pr_list)
	{
		st.view();
	}
	cout<<"------------------------------------------------------------------------------------"<<endl;
}

/* This function calls the edit function and edits the details in the project list */

void editproj()
{
	pr_obj.edit();
}


/* This function calls the del_proj function and deletes the details in the project list */

void delproj()
{
	pr_obj.del_project();
}

/* This function calls the project_query function and displays the top project */

void query()
{
	pr_obj.project_query();
}
