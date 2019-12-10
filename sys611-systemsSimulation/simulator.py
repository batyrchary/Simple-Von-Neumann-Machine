import numpy as np
import os
from os.path import isfile, join
from os import listdir
import pandas as pd
from sklearn.decomposition import PCA
import math
import subprocess
from multiprocessing import Process, Lock, Manager,Queue, Pipe
import itertools

from random import shuffle
from random import randrange
import random



user_selection_policies=[1,2,3,4]#FIFO, minduration,minrequirement,random
datacenter_selection_policies=[1,2,3]#closest,random,lessoccupied

for user_selection_policy in user_selection_policies:
	for datacenter_selection_policy in datacenter_selection_policies:
		
		taverage_for_one_run_latency=0
		taverage_for_one_run_waiting=0
		taverage_for_one_run_cpu=0
		taverage_for_one_run_mem=0

		for execution_times in range(0,100):
		
			maxtime=600

			average_for_one_run_latency=0
			average_for_one_run_waiting=0
			average_for_one_run_cpu=0
			average_for_one_run_mem=0
			average_for_one_run_counter=0


			filename="./results/result-"+str(user_selection_policy)+"-"+str(datacenter_selection_policy)+"-"+str(execution_times)+".csv"
			fileW=open(filename,"w+")



			#read latency data
			latency_datacenter=[]
			file_m=open("mergedResult.csv", "r")
			for line in file_m:

				line=line.strip("\n\r")
				if "prob_id" in line:
					continue
				
				splitted=line.split(",")

				prb_id=splitted[0]
				d1=float(splitted[1])
				d2=float(splitted[2])
				d3=float(splitted[3])
				d4=float(splitted[4])
				d5=float(splitted[5])

				latency_datacenter.append([prb_id,d1,d2,d3,d4,d5])
			file_m.close()


			#read server capacity data
			machine_capacity=[]
			file_m=open("server_machine_random_mapped.csv", "r")
			for line in file_m:

				line=line.strip("\n\r")
				if "cpu" in line:
					continue
				
				splitted=line.split(",")
				cpu=float(splitted[2])
				memory=float(splitted[3])

				machine_capacity.append([cpu,memory,cpu,memory])
			file_m.close()





			datacenters=[]

			#assign servers randomly to datacenters
			for i in range(0,5):
				datacenter1={}
				datacenter1["servers"]=[]
				datacenter1["users"]=[]
				
				number_servers_in_datacenter=100	
				for i in range(0, number_servers_in_datacenter):
					lm=len(machine_capacity)-1

					rindex=random.randint(0,lm)
					machine=machine_capacity[rindex]
					servers=datacenter1.get("servers")
					servers.append(machine)
					datacenter1["servers"]=servers

				datacenters.append(datacenter1)





			#read user requests and assigne latency info for each user request randomly
			user_requests=[]
			counter=0
			max_time=0
			frequency_increase=8
			file_j=open("frequency0.csv", "r")
			for line in file_j:

				if counter==10000:
					break
				counter=counter+1


				ld=len(latency_datacenter)-1
				rindex=random.randint(0,ld)
				user_request=latency_datacenter[rindex]

				line=line.strip("\n\r")
				if "cpu" in line:
					continue

				splitted=line.split(",")
				start=float(splitted[0])/frequency_increase
				duration=float(splitted[1])
				cpu=float(splitted[2])
				memory=float(splitted[3])

				user_request=user_request+[start,duration,cpu,memory]
				user_requests.append(user_request)

				if ((start+duration) > max_time ):
					max_time=start+duration





			queue=[]
			not_fitting=[]
			#[prb_id,d1,d2,d3,d4,d5,start,duration,cpu,memory]

			number_of_active_users=0
			total_latency=0

			total_wait=0
			total_passed_users=0


			for time in range(0, int(max_time)):

				
				if(time==maxtime):
					break
				
				if len(not_fitting)>0:
			#		print len(not_fitting)
					#for not_user in not_fitting:
					#	print not_user
					time=time-1
				else:
					average_latency=0
					average_wait=0
					if(number_of_active_users>0):
						average_latency=total_latency/number_of_active_users
						
					if(total_passed_users!=0):
						average_wait=float(total_wait)/total_passed_users
					#printline="time:,"+str(time)+",total_latency:,"+str(total_latency)+",active_users:,"+str(number_of_active_users)+",average latency:,"+str(average_latency)+",average_wait:,"+str(average_wait)
					printline="time:,"+str(time)+",active_users:,"+str(number_of_active_users)+",average latency:,"+str(average_latency)+",average_wait:,"+str(average_wait)
					#print printline

					#printline="time:"+str(time)
					cpuD=0
					memD=0
					for i in range(0,5):
						datacenter1=datacenters[i]
						servers1=datacenter1.get("servers")
						Rcpu=0
						Rmem=0

						rcounter=0
						for ser in servers1:
							cpu=ser[0]
							mem=ser[1]
							cpuo=ser[2]
							memo=ser[3]

							if (cpu!=cpuo or mem!=memo):
								rcounter=rcounter+1
								Rcpu=Rcpu+cpu/cpuo
								Rmem=Rmem+mem/memo


						memR=0
						cpuR=0
						if(rcounter!=0):
							memR=Rmem/rcounter
							cpuR=Rcpu/rcounter
						

						cpuD=cpuD+cpuR
						memD=memD+memR
						printline=printline+",cpuR"+str(i)+":"+str(cpuR)
						printline=printline+",memR"+str(i)+":"+str(memR)

					printline=printline+",cpuD:"+str(float(cpuD)/5)+",memD:"+str(float(memD)/5)
					#print printline
					fileW.write(printline+"\n")

					average_for_one_run_latency=average_for_one_run_latency+average_latency
					average_for_one_run_waiting=average_for_one_run_waiting+average_wait
					average_for_one_run_cpu=average_for_one_run_cpu+cpuD/5
					average_for_one_run_mem=average_for_one_run_mem+memD/5
					average_for_one_run_counter=average_for_one_run_counter+1


					#"user_requests:",len(user_requests),"queue:",len(queue), "notfitting:", len(not_fitting)
				 

				#if(time%1000==0):
				#	print len(queue)

				tobedeleted=[]
				index_del=0
				for user_request in user_requests:
					start_time=user_request[6]
					if (start_time>time):
						break

					tobedeleted.append(index_del)
					index_del=index_del+1
					queue.append(user_request)

				if len(tobedeleted)>0:
					del user_requests[min(tobedeleted):max(tobedeleted)]

				
				if len(queue)==0:
					#print "continue:",len(queue)
					continue

				index_min_duration=0
				index_min_requirement=0
				value_min_duration=9999999999
				value_min_requirement=5

				index_counter=0
				for uq in queue:
					if value_min_duration>uq[7]:
						index_min_duration=index_counter
						value_min_duration=uq[7]

					if value_min_requirement>(uq[8]+uq[9]):
						index_min_requirement=index_counter
						value_min_requirement=uq[8]+uq[9]

					index_counter=index_counter+1


				#select user_request_from_queue
				 
				if (user_selection_policy==1):#first come first served	
					#user_request=queue[0][:]
					#del queue[0]
					amk_index=0
			#		print "just deleted:",len(queue)
					
				elif(user_selection_policy==2):#minduration	
					amk_index=index_min_duration
					#user_request=queue[index_min_duration][:]
					#del queue[index_min_duration]
				elif(user_selection_policy==3):#minrequirement	
					amk_index=index_min_requirement
					#user_request=queue[index_min_requirement][:]
					#del queue[index_min_requirement]
				else:						#random
					ld=len(queue)-1
					rindex=random.randint(0,ld)
					amk_index=rindex
					#user_request=queue[rindex][:]
					#del queue[rindex]

				user_request=[]
				for amk in queue[amk_index]:
					user_request.append(amk)
				
				
				del queue[amk_index]
				amk_queue=[]
				for aq in range(0,len(queue)):
					if(aq!=amk_index):
						amk_queue.append(queue[aq])
				queue=amk_queue

				
				total_wait=total_wait+len(queue)
				total_passed_users=total_passed_users+1


				
				latencies_of_user=user_request[1:6]
				index_min_latency=0
				min_latency_value=99999999

				index_less_occupied=0
				less_occupied_value=99999999

				candidate_datacenters=[]
				for i in range(0,5):
					datacenter1=datacenters[i]
					
					servers1=datacenter1.get("servers")
					users_in_datacenter=datacenter1.get("users")

					to_be_finished_users=[]
					for ui in range(0, len(users_in_datacenter)):
						assigned_server_index=users_in_datacenter[ui][0]
						assigned_user_cpu=users_in_datacenter[ui][1][8]
						assigned_user_mem=users_in_datacenter[ui][1][9]
						assigned_user_end=users_in_datacenter[ui][1][6]+users_in_datacenter[ui][1][7]
						
						assigned_datacenter_index=users_in_datacenter[ui][2]
						assigned_latency=users_in_datacenter[ui][1][1:6][assigned_datacenter_index]

						if (assigned_user_end<=time):
							to_be_finished_users.append(ui)
							server_to_be_updated=servers1[assigned_server_index]
							server_to_be_updated[0]=server_to_be_updated[0]+assigned_user_cpu
							server_to_be_updated[1]=server_to_be_updated[1]+assigned_user_mem

							if (server_to_be_updated[0]<0):
								server_to_be_updated[0]=0
							if (server_to_be_updated[1]<0):
								server_to_be_updated[1]=0

							servers1[assigned_server_index]=server_to_be_updated

							number_of_active_users=number_of_active_users-1
							total_latency=total_latency-assigned_latency



					for finish_index in sorted(to_be_finished_users, reverse=True):
						del users_in_datacenter[finish_index]

					datacenter1["servers"]=servers1
					datacenter1["users"]=users_in_datacenter


					number_of_hosting_users=len(users_in_datacenter)

					for si in range(0,len(servers1)):
						server=servers1[si]

						cpu=server[0]
						mem=server[1]

						if(cpu>user_request[8] and mem>user_request[9]):
							candidate_datacenters.append([i,si])

							if latencies_of_user[i]<min_latency_value:
								min_latency_value=latencies_of_user[i]
								index_min_latency=i
							
							if(less_occupied_value<number_of_hosting_users):
								less_occupied_value=number_of_hosting_users
								index_less_occupied=i


				if len(candidate_datacenters)==0:
					#print "candidate_datacenters:",len(candidate_datacenters)
					not_fitting.append(user_request)
					continue


				#[prb_id,d1,d2,d3,d4,d5,start,duration,cpu,memory]
				

				
				#datacenter_selection_policy==1
				index_datacenter=index_min_latency # assigne to closest
				if (datacenter_selection_policy==2):
					index_datacenter=random.choice(candidate_datacenters)[0]
				elif(datacenter_selection_policy==3):
					index_datacenter=index_less_occupied



				datacenter_to_be_assigned=datacenters[index_datacenter]
				server_to_be_assigned=0
				for cdatacenter in candidate_datacenters:
					if cdatacenter[0]==index_datacenter:
						server_to_be_assigned=cdatacenter[1]
						break

				servers_in_datacenter=datacenter_to_be_assigned.get("servers")
				users_in_datacenter=datacenter_to_be_assigned.get("users")

				server_updated=servers_in_datacenter[server_to_be_assigned]
				server_updated[0]=server_updated[0]-user_request[8]
				server_updated[1]=server_updated[1]-user_request[9]
				if (server_updated[0]<0):
					server_updated[0]=0
				if (server_updated[1]<0):
					server_updated[1]=0

				servers_in_datacenter[server_to_be_assigned]=server_updated
				
				users_in_datacenter.append([server_to_be_assigned,user_request,index_datacenter])
				datacenter_to_be_assigned["servers"]=servers_in_datacenter
				datacenter_to_be_assigned["users"]=users_in_datacenter
				datacenters[index_datacenter]=datacenter_to_be_assigned

				assigned_latency=user_request[1:6][index_datacenter]


				number_of_active_users=number_of_active_users+1
				total_latency=total_latency+assigned_latency






				queue=queue+not_fitting
				not_fitting=[]

				
			fileW.close()


			#printline="latency:,"+str(average_for_one_run_latency/float(average_for_one_run_counter))
			#printline=printline+",waiting:,"+str(average_for_one_run_waiting/float(average_for_one_run_counter))

			#printline=printline+",cpu:,"+str(average_for_one_run_cpu/float(average_for_one_run_counter))
			#printline=printline+",mem:,"+str(average_for_one_run_mem/float(average_for_one_run_counter))
			#printline=printline+",execution_times:"+","+str(execution_times)
			#print printline

			taverage_for_one_run_latency=taverage_for_one_run_latency+average_for_one_run_latency/float(average_for_one_run_counter)
			taverage_for_one_run_waiting=taverage_for_one_run_waiting+average_for_one_run_waiting/float(average_for_one_run_counter)
			taverage_for_one_run_cpu=taverage_for_one_run_cpu+average_for_one_run_cpu/float(average_for_one_run_counter)
			taverage_for_one_run_mem=taverage_for_one_run_mem+average_for_one_run_mem/float(average_for_one_run_counter)

		printline="latency:,"+str(taverage_for_one_run_latency/float(100))
		printline=printline+",waiting:,"+str(taverage_for_one_run_waiting/float(100))

		printline=printline+",cpu:,"+str(taverage_for_one_run_cpu/float(100))
		printline=printline+",mem:,"+str(taverage_for_one_run_mem/float(100))
		
		printline=printline+",user_selection_policy:,"+str(user_selection_policy)
		printline=printline+",datacenter_selection_policy:,"+str(datacenter_selection_policy)


		print printline











