#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>     /* system, NULL, EXIT_FAILURE */
#include<string>
#include<vector>
#include<string.h>
using namespace std;
#include <sys/types.h>
#include <sys/wait.h> 



struct commands
{
	string command;
	vector<string> argument; 
	vector<int> i_pipe;
	vector<int> o_pipe;
};



int exist(string input)
{
	int result=0; 
	for(int i=0; i<input.length(); i++)
	{
		if(input[i]=='|')
		{
			result=i;
			break;
		}	
	}
	
	return result;

}
bool tek (string input)
{
	bool varmi=false;
	for(int i=0; i<input.length(); i++)
	{
		if(input[i]=='|')
		{
			if(input[i-1]=='>' || input[i-1]=='<' )
			{
				varmi=true;
				break;
			}
		}	
	}
	
	return varmi;
	
}

int exist1(string input)
{
	int result=0; 
	for(int i=0; i<input.length(); i++)
	{
		if(input[i]==' ')
		{
			result=i;
			break;
		}	
	}
	
	return result;

}


int notExist_p(int n, vector<int>pipe_out)
{
	int result = 1;
	for(int i=0; i<pipe_out.size(); i++)
	{
		if(pipe_out[i]== n)
		{
			result=0;
			break;
		}	
	}
	
	return result;
	
}

int Exist_p(int n, vector<int>pipe_out)
{
	int result = 0;
	for(int i=0; i<pipe_out.size(); i++)
	{
		if(pipe_out[i]== n)
		{
			result=i;
			break;
		}	
	}
	
	return result;
	
}



vector<int> ayiriciya_yardimci(string devami, vector<int> &output_pipe)
{
	vector<int> i_pipe;
	string sayi="";
	bool inputmu=true;
	
	
	int size=devami.length();
	for(int i=1; i<size; i++)
	{
		if(devami[i]=='|')
		{
			if(devami[i-1]=='<')
			{
				inputmu=true;
			}
			else if(devami[i-1]=='>')
			{
				inputmu=false;
			}
			i=i+1;
		}	
		else if( (devami[i]!='>' && devami[i]!='<') &&devami[i]!=' ')
		{
			//sayi.append(devami.substr(i,i+1));
			sayi.push_back(devami[i]);
			if((devami[i+1]==' ' || (i+1)==size ) && inputmu )
			{
				i_pipe.push_back(atoi(sayi.c_str()));
				sayi="";
				i=i+1;
			}
			else if((devami[i+1]==' ' || (i+1)==size ) && !inputmu)
			{
				output_pipe.push_back(atoi(sayi.c_str()));
				sayi="";
				i=i+1;
			}
		}
	}
	
	return i_pipe;
}


vector<string> argument_hazirlayci(string arg)
{
	vector<string> ret;
	string argument="";

	for(int i=0; i<arg.length(); i++)
	{
		
		if(arg[i]!=' ')
		{	
			argument.push_back(arg[i]);			
			
		}
		else if(arg[i]==' ')
		{
			ret.push_back(argument);
			argument="";
		}	
	}
	ret.push_back(argument);

	
	return ret;

}




commands ayirici(string input)
{

	commands ret;

	int length=input.length();

	string command_ve_arguman;

	int found;
	found=input.find_first_of("|",0);
	command_ve_arguman=input.substr(0,found-2);

	int space = exist1(command_ve_arguman);
	if(space)
	{
		int index;
		index=(command_ve_arguman).find_first_of(" ",0);
		string command=(command_ve_arguman).substr(0,index);

	
		int uzunluk=command_ve_arguman.length();
		string arg=(command_ve_arguman).substr(index+1,uzunluk-index-1);	
				
		ret.command=command;
		ret.argument=argument_hazirlayci(arg);
	}
	else
	{
		ret.command=command_ve_arguman;
	}

	
///////////////////////////YUKARISI COMMAND VER ARGUMANI AYIRYO AMA ARGUMAN LARI BIR BIRINDEN AYIRMYO
	string devami=input.substr(found-1,length);
		
	ret.i_pipe=ayiriciya_yardimci(devami, ret.o_pipe);

	return ret;
}

//////////////////////////////////////////////////////////////////////////////////////

void printer(vector<commands> s_array)
{
	for(int i=0; i<s_array.size(); i++)
	{
		cout<<"command = "<<(s_array[i]).command<<endl;
		cout<<"argument => ";		
		for(int j=0; j<((s_array[i]).argument).size(); j++)
		{
			cout<<(s_array[i]).argument[j]<<",";
		}
		cout<<endl;
		cout<<"i_pipe => ";	
		for(int jjj=0; jjj<((s_array[i]).i_pipe).size(); jjj++)
		{
			cout<<(s_array[i]).i_pipe[jjj]<<",";
		}
		cout<<endl;
		cout<<"o_pipe => ";		
		for(int jj=0; jj<((s_array[i]).o_pipe).size(); jj++)
		{
			cout<<(s_array[i]).o_pipe[jj]<<",";
		}
		cout<<endl;
	}

	
}
/*
struct commands
{
	string command;
	vector<string> argument; 
	vector<int> i_pipe;
	vector<int> o_pipe;
};
*/

bool checker(vector<commands> s_array, int &pipe_sayisi)
{
	bool ret = false;

	vector<int> out;
	vector<int> in;
	for(int i=0; i<(s_array).size(); i++)
	{
		for(int k=0; k<((s_array[i]).o_pipe).size(); k++)
		{
			bool varmi = false;
			for(int j=0; j<out.size(); j++)
			{
				if(out[j]== (s_array[i]).o_pipe[k])
					varmi=true;
			}
			if(!varmi)
				out.push_back((s_array[i]).o_pipe[k]);
		}
		
	}

	for(int i=0; i<(s_array).size(); i++)
	{
		for(int k=0; k<((s_array[i]).i_pipe).size(); k++)
		{
			bool varmi = false;
			for(int j=0; j<in.size(); j++)
			{
				if(in[j]== (s_array[i]).i_pipe[k])
					varmi=true;
			}
			if(!varmi)
				in.push_back((s_array[i]).i_pipe[k]);
		}
		
	}	

	pipe_sayisi=out.size();

	vector<int> result;
	for(int i=0; i<out.size(); i++)
	{
		bool varmi=false;
		for(int j=0; j<in.size(); j++)
		{
			if(out[i]==in[j])
				varmi=true;
		}
		if(!varmi)
			result.push_back(i);
	}	

	ret=(result.empty()) && (out.size() == in.size());
	return ret;
 
}





void prosdoy_main(vector<commands> s_array, int pipe_sayisi)
{
	// ilki bn bir printere sokaly hemme zat bamy;	
	//printer(s_array);
	//cout<<"pipe_sayisi = "<<pipe_sayisi<<endl;
	//////////////////////////bar eken so lets continue	
	
	int command_sayisi=s_array.size();	

	int child_status;
	int identifier;
	
	vector<pid_t> pids;
	
	pair<int,int> cift;
	vector<pair<int,int> >fds;
	
	vector<int> identifiers;
	

	pid_t pid;
	int fdss[2];
	
//////////////////////////////////	


vector<int> pipe_out;



for(int c=0; c<command_sayisi; c++ )
{
	for(int p=0; p<((s_array[c]).o_pipe).size() ; p++)
	{
		int n=(s_array[c]).o_pipe[p];
	
		if( (notExist_p(n, pipe_out)) )
		{
			pipe_out.push_back(n);
		}
	}
}

/*for(int i=0; i<pipe_out.size(); i++)
{
	cout<<"kacinci pipe hamgi index alyo = "<<pipe_out[i];
}
cout<<endl;*/

	
///////////////////////////////////	
	
	for(int p=0; p<pipe_sayisi; p++) //pipe stuff
	{	
		pipe(fdss);
		cift.first=fdss[0];
		cift.second=fdss[1];
		fds.push_back(cift);
		
	}


	///////////////////////////////////////////////////////////

/*
	for(int i=0; i<fds.size(); i++)
	{
		cout<<"f = "<<fds[i].first<<" s = "<<fds[i].second<<endl;
	}
*/	




	for(int i=0; i<command_sayisi; i++) //frok stuff
	{
		
		pids.push_back(pid=fork());
		identifiers.push_back(i);
		if(pid==0)
		{
			identifier=i;
			break;
		}
	}


if(pid != 0)
{
	for(int i=0; i<fds.size(); i++)//close stuff
	{
	
		close(fds[i].first);
 		close(fds[i].second);
	}

}




/////////////////////////////////////////////////////////

	if(pid==0) // pipe stuff
	{
		for(int i=0; i<command_sayisi; i++)
		{
			if(identifier == i)
			{
				commands the_one=s_array[i];
				
				if((the_one.i_pipe).size()>0) // i_pipe var
				{
					int pipe_num=the_one.i_pipe[0];
					int index=Exist_p(pipe_num,pipe_out);//pipe_out da pipe_num-lar pipe indexlerine gore durya
					// index=kacinci pipe a gondercegimiz
					 //cout<<"index = "<<index<<endl;
					 
//						 close(fd[1]);
//						dup2(fd[0],0);
//						close(fd[0]);
						// 0 -> pipe read end 1 -> stdout
//						execl("/usr/bin/tr","tr","/a-z/","/A-Z/",NULL);

					 
						close(fds[index].second);
					 	dup2(fds[index].first,0);
			 			close(fds[index].first);
					 
				}
				if((the_one.o_pipe).size()>0) // o_pipe var
				{

					if((the_one.o_pipe).size() > 1) // repeater lazim
					{
						int fdr[2];
						pid_t pidr;
						pipe(fdr);
						string genel="";
						char buf[1024];
						pidr=fork();
						
						
						int ret=0;
						if(pidr == 0)//child
						{
						
						
						
							close(fdr[0]);
					 		dup2(fdr[1],1);
			 				close(fdr[1]);
						
							for(int i=0; i<fds.size(); i++)//close stuff
							{
								close(fds[i].first);
 								close(fds[i].second);
							}
							
								for(int j=0; j<command_sayisi;j++)
								{
									if(identifiers[j]==identifier)
									{	
									//char* argvs[] = {"ls", "-l", NULL};
										int size_needed = (s_array[j]).argument.size(); 
										char* argvs[size_needed+2];
				
										string c = (s_array[j]).command;			
										char *y = new char[c.length() + 1];
										strcpy(y,c.c_str());

										argvs[0]=y;				
										for(int i=0; i<size_needed;i++)
										{
											c=(s_array[j]).argument[i];
											char *yy = new char[c.length() + 1];
											strcpy(yy,c.c_str());
					
											argvs[i+1]=yy;
										}
										argvs[size_needed + 1] = NULL;
										execvp((s_array[j]).command.c_str(),argvs);
											
									}	
								}
						
						
							
						}
						else//parent
						{
							pid_t wpid = waitpid(pidr, &child_status, 0);
							bool bitmedi=true;
							//cout<<"cocuk bitdi"<<endl;
							while(bitmedi)
							{
								
								
							
								//genel.append(buf, 30);
								close(fdr[1]);
								ret = read(fdr[0],buf, 1023);
								//cout<<"genel = "<<genel<<endl;
						
								if(ret<=0)
								{
									bitmedi=false;
							//		cout<<"cikdim"<<endl;
								}
								else
								{
									genel += buf;
									for(int k=0; k<1023;k++)
									{
										buf[k]= '\0';
									}								
								}
								
							//	cout<<"zaa"<<endl;
							}
							///cout<<"ddddddddda"<<endl;
							close(fdr[0]);

						
							for(int i=0; i<(the_one.o_pipe).size(); i++)
							{
								int p_n=the_one.o_pipe[i];
								int ind=Exist_p(p_n,pipe_out);
								
								write(fds[ind].second, genel.c_str(), genel.length());
						 
							
						
						
							}
							
							for(int i=0; i<fds.size(); i++)//close stuff
							{
	
								close(fds[i].first);
 								close(fds[i].second);
							}
							exit(0);
						
						
							
						}
						
						
						
										
	
					}

					if((the_one.o_pipe).size() == 1) //bitane var
					{
						int pipe_num2=the_one.o_pipe[0];
						int index2=Exist_p(pipe_num2,pipe_out);
						//cout<<"index = "<<index2<<endl;
					 


					 //close(fd[0]);
					//dup2(fd[1],1);
					//close(fd[1]);
					// 0 -> stdin, 1 -> pipe write end
					//execl("/bin/ls","ls","-l",NULL);
					 
						close(fds[index2].first);
					 	dup2(fds[index2].second,1);
			 			close(fds[index2].second);
					}


				
				}
				
			//	if(pid != 0)
			//	{
					for(int i=0; i<fds.size(); i++)//close stuff
					{
	
						close(fds[i].first);
 						close(fds[i].second);
					}

			//	}
				
			}
		}		
	}



















	if((pid==0) )//exec stuff
	{

		for(int j=0; j<command_sayisi;j++)
		{
			if(identifiers[j]==identifier)
			{	
				//char* argvs[] = {"ls", "-l", NULL};
				int size_needed = (s_array[j]).argument.size(); 
				char* argvs[size_needed+2];
				
				string c = (s_array[j]).command;			
				char *y = new char[c.length() + 1];
				strcpy(y,c.c_str());

				argvs[0]=y;				
				for(int i=0; i<size_needed;i++)
				{
					c=(s_array[j]).argument[i];
					char *yy = new char[c.length() + 1];
					strcpy(yy,c.c_str());
					
					argvs[i+1]=yy;
				}
				argvs[size_needed + 1] = NULL;
				execvp((s_array[j]).command.c_str(),argvs);
											
			}	
		}
	}



/*	if(pid != 0) 
	{
		cout<<"command_sayisi = "<<command_sayisi <<endl;
		for(int j=0; j<command_sayisi;j++)
		{
			cout<<"pids["<<j<<"] = "<<pids[j]<<endl;
			cout<<"identifiers["<<j<<"] = "<<identifiers[j]<<endl;
			
		}
	}

*/


/*
	if(fpid != 0) //reap stuff
	{
		for(int j=0; j<fpids.size();j++)
		{
		//	cout<<"before  = "<<fpids[j]<<endl;
			pid_t wpid = waitpid(fpids[j], &child_status, 0);
		//	cout<<"reaping  = "<<fpids[j]<<endl;
	
		}
	}

*/

	if(pid != 0) //reap stuff
	{
		for(int j=0; j<command_sayisi;j++)
		{
		//	cout<<"before reap = "<<pids[j]<<endl;
			pid_t wpid = waitpid(pids[j], &child_status, 0);
		//	cout<<"reaping child = "<<pids[j]<<endl;
	
		}
	}




return;


}

void tek_icin_main(string command_ve_arguman)
{
	//cout<<"command_ve_arguman = "<<command_ve_arguman<<endl;
	string command;
	vector<string> argument;
	int space = exist1(command_ve_arguman);
	if(space)
	{
	//	cout<<"girdi"<<endl;
		int index;
		index=(command_ve_arguman).find_first_of(" ",0);
	//	cout<<"index = "<<index<<endl;
		string com=(command_ve_arguman).substr(0,index);
		
	
		int uzunluk=command_ve_arguman.length();
		string arg=(command_ve_arguman).substr(index+1,uzunluk-index-1);	
				
		command=com;
		argument=argument_hazirlayci(arg);
	}
	else
	{
		command=command_ve_arguman;
	}
	
	
	int pid;
	int child_status;
	pid=fork();
	if(pid==0) //child
	{
	/*	for(int a=0; a<argument.size(); a++)
		{
			cout<<"argument = "<<argument[a]<<endl;
		}*/
		//cout<<"command = "<<command<<endl;
		int size_needed = argument.size(); 
		char* argvs[size_needed+2];
				
		char *y = new char[command.length() + 1];
		strcpy(y,command.c_str());
		string c;
		argvs[0]=y;				
		for(int i=0; i<size_needed;i++)
		{
			c=argument[i];
			char *yy = new char[c.length() + 1];
			strcpy(yy,c.c_str());
					
			argvs[i+1]=yy;
		}
		argvs[size_needed + 1] = NULL;
		execvp(command.c_str(),argvs);
				
		
		
		
	/*char* argvs[size_needed+2];
				
				string c = (s_array[j]).command;			
				char *y = new char[c.length() + 1];
				strcpy(y,c.c_str());

				argvs[0]=y;				
				for(int i=0; i<size_needed;i++)
				{
					c=(s_array[j]).argument[i];
					char *yy = new char[c.length() + 1];
					strcpy(yy,c.c_str());
					
					argvs[i+1]=yy;
				}
				argvs[size_needed + 1] = NULL;
				execvp((s_array[j]).command.c_str(),argvs);	
	*/	
		
	}
	else //parent
	{
		//cout<<"pid = "<<pid<<endl;
		pid_t wpid = waitpid(pid, &child_status, 0);
	}
	
	

}




////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{

int pid;
int status;
	vector<commands> s_array;

	while (1)
	{
		string input;
		getline (cin,input);
		
		if(strcmp("quit",input.c_str())==0)
		{
			//cout<<"girdi"<<endl;
			break;
		}
		else 
		{
			
			if(!(tek(input)))
			{
				//cout<<"zaaaaaa"<<endl;
				
				tek_icin_main(input);
				
			}
			else
			{

			
				s_array.push_back(ayirici(input));
				int pipe_sayisi;
				if(checker(s_array,pipe_sayisi))
				{
			////////// SIMDI BANA LAZIM OLAN SEYLERI ALDYM YUKARDA PROSDOY MAIN-DA DEVAM EDELIM

					pid=fork();				
							
					if(pid==0)
					{		
	


						prosdoy_main(s_array,pipe_sayisi);
						s_array.clear();
						exit(0);
					
					}		
					else
					{
						pid_t wpid = waitpid(pid, &status, 0);
						s_array.clear();
					}	
				}

				
				
			}		
		}
		


	}


	return 0;
}

