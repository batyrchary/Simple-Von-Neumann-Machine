#include <iostream>
#include <unistd.h>
#include <vector>	// sormak lazim ekleyebilcezmi
#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>


using namespace std;

vector <pthread_mutex_t> light_vehicle_seperator;

vector<int> araba_varmi;

vector<pthread_cond_t> araba_var;
vector<pthread_mutex_t> araba_varmis;
vector<pthread_cond_t> arabayi_kaldir;

/////////////////////////////////////////////////
int sayici=0;
/////////////////////////////////////////////////

typedef struct
{
	int all[4];
} reader;

vector<reader> readers;


typedef struct
{
	vector<pthread_cond_t> allYesil;
	vector<pthread_mutex_t> allKirmizi;
} red_icin;

vector<red_icin> kirmizi;
////////////////////////////////////////////////////////////

enum DIRECTION {WEST, SOUTH, EAST, NORTH};//Directions of the crossroad


///////////////////////////////////////////////////////AKSAM
struct night_vehicle
{
	int vehicleCode;
	int intersectionCode;
	DIRECTION from;
	DIRECTION to;
	pthread_cond_t* condition;
	pthread_mutex_t* mutex;
	sem_t* semaphore;

};

typedef struct//Struct for the intersections in the day mode
{
	vector<night_vehicle> girenler;
	vector<night_vehicle> bekleyenler;
} night;

vector<night> nighter;

vector<pthread_mutex_t> night_mutex;

pthread_mutex_t locker;




//////////////////////////////////////////////////AKSAM bitdi
























#include "writeOutput.h"//Outputs of the simulation

class CrossRoad//Class for the crossroad
{
	private:
		int N;// It is the number of intersections.
		int *lightState;// Its value is the direction of the green light on the intersection, -1 in the night mode. Its size is N.
	public:
		CrossRoad(int _N,int _mode);//Constructor
		void Enter(int vehicleCode, int intersectionCode, DIRECTION From,DIRECTION To);//Vehicles call this function for entering the intersection
		void Exit(int vehicleCode, int intersectionCode, DIRECTION From,DIRECTION To);//Vehicles call this function for exiting the intersection
		void SetGreenLight(int intersectionCode);//Call this function for turning green traffic lights on in the given intersection
};

typedef struct//Struct for the intersections in the day mode
{
	int intersectionCode;//Id of the intersection
	int duration;//Duration of the green light in the day mode
	CrossRoad *crossroad;//CrossRoad class object of the intersection
} intersectionData;


struct path
{
	int intersectionCode;
	DIRECTION from;
	DIRECTION to;

};

struct vehicle
{
	int vehicleCode;
	int arriveTime;
	int moveTime;
	vector<path> paths;

};

typedef struct//Struct for the intersections in the day mode
{
	vehicle iVehicle;//Id of the intersection
	CrossRoad *crossroad;//CrossRoad class object of the intersection
} vehicleData;




void *trafficLight(void *data)//Traffic light thread
{
	intersectionData *iData=(intersectionData *)data;//Getting intersection data
	
	while(true)
	{
		usleep(iData->duration*1000);//Waiting until the green light on the next direction turns on
		(iData->crossroad)->SetGreenLight(iData->intersectionCode);//Turning next green light on the next direction on
	}

}





void *vehicle_thread(void *argument_vehicle)
{

	vehicleData *iVehicleData=(vehicleData *)argument_vehicle;//Getting intersection data
	vehicle iVehicle=iVehicleData->iVehicle;


	for(int i=0; i<iVehicle.paths.size(); i++)
	{

		usleep(iVehicle.arriveTime*1000);
		writeOutput(0,iVehicle.vehicleCode,(iVehicle.paths[i]).intersectionCode,(iVehicle.paths[i]).from,(iVehicle.paths[i]).to);


(iVehicleData->crossroad)->Enter(iVehicle.vehicleCode,(iVehicle.paths[i]).intersectionCode,(iVehicle.paths[i]).from,(iVehicle.paths[i]).to);
		
		usleep(iVehicle.moveTime*1000);
		
(iVehicleData->crossroad)->Exit(iVehicle.vehicleCode,(iVehicle.paths[i]).intersectionCode,(iVehicle.paths[i]).from,(iVehicle.paths[i]).to);
				

	}

pthread_mutex_lock(&locker);
sayici--;
pthread_mutex_unlock(&locker);


pthread_exit(0);


}


CrossRoad::CrossRoad(int _N,int _mode)
{
	N=_N;
	lightState = new int [_N]; ///////////////////////


	if(_mode==0)
	{
		for(int i=0; i<_N; i++)
			{
				lightState[i]=0;
			}		
	}
	else
	{
		for(int i=0; i<_N; i++)
			{
				lightState[i]=-1;
			}
	}
}






void CrossRoad::Enter(int vehicleCode, int intersectionCode, DIRECTION From,DIRECTION To)
{

	if(lightState[0]==-1) //	night
	{
		pthread_mutex_lock(&night_mutex[intersectionCode]); 

		night_vehicle nVehicle;
		nVehicle.vehicleCode=vehicleCode;
		nVehicle.intersectionCode=intersectionCode;
		nVehicle.from=From;
		nVehicle.to=To;	
		
		bool girsinmi=true;
		for(int i=0; i<nighter[intersectionCode].girenler.size(); i++)	// icerdekilerle tek tek kontrol et
		{
			night_vehicle controller=nighter[intersectionCode].girenler[i];
			
			if(From == controller.from) //vehicles entering from same direction donot conflict 
			{
			}
			else	//coming from another direction
			{
				if(((controller.from+1)%4) == controller.to)// turning right
				{
					if(To == controller.to) //outgoing direction same
					{
						girsinmi=false; // conflict
						break;
					}
				}
				else if(controller.from == ((controller.to+1)%4)) // turning left/////////// tekrar bak
				{
					if((controller.to==From) && (((From+1)%4)==To)) 
					{//coming from opposite direction and turning right dosnt conflict
					}
					else // conflict
					{
						girsinmi=false;
						break;
					}
				}
				else if(((controller.from+2)%4) == controller.to)	// opposite direction
				{
					if(((controller.from+2)%4)==From)//opposite
					{
						if(From == ((To+1)%4))//left
						{
							girsinmi=false;
							break;
						}					
					}
					else if(controller.from == ((From+1)%4)) // coming from left
					{

						if(((From +1)%4) == To)//turning right dont conflict 
						{
						}
						else	//conflict
						{
							girsinmi=false;
							break;
						}

					}
					else if(((controller.from+1)%4) == From) //coming from right
					{
						girsinmi =false;
						break;
					}

				}
				
			}



		}
		
		if(girsinmi)	// girsin
		{
			(nighter[intersectionCode].girenler).push_back(nVehicle);
			writeOutput(1,vehicleCode,intersectionCode,From,To);		
			pthread_mutex_unlock(&night_mutex[intersectionCode]);

		}
		else	// girmesin
		{
			

	pthread_cond_t* c = new pthread_cond_t;
	pthread_mutex_t* m = new pthread_mutex_t;

	nVehicle.condition=c;
	nVehicle.mutex=m;


	sem_t* s=new sem_t;
	sem_init(s, 0, 0);

nVehicle.semaphore=s;

			(nighter[intersectionCode].bekleyenler).push_back(nVehicle);

//	pthread_mutex_lock(m);



	pthread_mutex_unlock(&night_mutex[intersectionCode]);


		sem_wait(nVehicle.semaphore);


//	pthread_cond_wait(c,m); 
		
//	pthread_mutex_unlock(m);

			
		}
		
	}
	else
	{


while(1)
{

		pthread_mutex_lock(&light_vehicle_seperator[intersectionCode]);
		if(lightState[intersectionCode-1]==From) //yesil isiksa
		{
			readers[intersectionCode].all[From]++; //birinci olarak mi geldi kendi yonunde
			if(readers[intersectionCode].all[From] == 1)
			{
				if(araba_varmi[intersectionCode]) //ilk gelen ise araba varmi o intersectionda
				{

					pthread_mutex_lock(&araba_varmis[intersectionCode]);

					readers[intersectionCode].all[From]--; //araba herseyi tekrardan baslatcagi icin artik 1. olmicak
					pthread_mutex_unlock(&light_vehicle_seperator[intersectionCode]); //var ise digerleride kullansin

					pthread_cond_wait(&arabayi_kaldir[intersectionCode], &araba_varmis[intersectionCode]); 
		
					pthread_mutex_unlock(&araba_varmis[intersectionCode]); 
														
				}
				else if(!araba_varmi[intersectionCode]) //araba yok ise
				{
					araba_varmi[intersectionCode]++;	//araba var artik
					writeOutput(1,vehicleCode,intersectionCode,From,To);		
					pthread_mutex_unlock(&light_vehicle_seperator[intersectionCode]);
					break;
				}
		
			
			}
			else	//ikinci olarak geldi ise
			{
				araba_varmi[intersectionCode]++;	//kac tane araba var onu tutcaz basicly
				writeOutput(1,vehicleCode,intersectionCode,From,To);		
				pthread_mutex_unlock(&light_vehicle_seperator[intersectionCode]);
				break;
			}

		}
		else //kirmizi ise
		{

			pthread_mutex_lock(&kirmizi[intersectionCode].allKirmizi[From]);
			pthread_mutex_unlock(&light_vehicle_seperator[intersectionCode]); //var ise digerleride kullansin

			pthread_cond_wait(&kirmizi[intersectionCode].allYesil[From], &kirmizi[intersectionCode].allKirmizi[From]); 
		
			pthread_mutex_unlock(&kirmizi[intersectionCode].allKirmizi[From]);

		}
	


}
				
	}
		
}





void CrossRoad::Exit(int vehicleCode, int intersectionCode, DIRECTION From,DIRECTION To)
{

	if(lightState[0]==-1) //	night
	{


		pthread_mutex_lock(&night_mutex[intersectionCode]);

		vector<night_vehicle> exiter;

		for(int i=0; i<nighter[intersectionCode].girenler.size(); i++)
		{		
			if(nighter[intersectionCode].girenler[i].vehicleCode != vehicleCode) //silmek istedigmi almicaz
			{
				exiter.push_back(nighter[intersectionCode].girenler[i]);
			}
		}

		writeOutput(2,vehicleCode,intersectionCode,From,To); //sildikden hemen sonra write yapcaz ki uyandirdigimiza problem olmasin

		vector<night_vehicle> exiter2;



		for(int j=0; j<nighter[intersectionCode].bekleyenler.size(); j++)	// bekleyenlerle tek tek kontrol et
		{
			bool check=true;
			
			night_vehicle bekle=nighter[intersectionCode].bekleyenler[j];


			for(int i=0; i<exiter.size(); i++)	// icerdekilerle tek tek kontrol et
			{
				night_vehicle controller=exiter[i];
			
				if(bekle.from == controller.from) //vehicles entering from same direction donot conflict 
				{
				}
				else	//coming from another direction
				{
					if(((controller.from+1)%4) == controller.to)// turning right
					{
						if(bekle.to == controller.to) //outgoing direction same
						{
							check=false; // conflict
							break;
						}
					}
					else if(controller.from == ((controller.to+1)%4)) // turning left/////////// tekrar bak
					{
						if((controller.to==bekle.from) && (((bekle.from+1)%4)==bekle.to)) 
						{//coming from opposite direction and turning right dosnt conflict
						}
						else // conflict
						{
							check=false;
							break;
						}
					}
					else if(((controller.from+2)%4) == controller.to)	// opposite direction
					{
						if(((controller.from+2)%4)==bekle.from)//opposite
						{
							if(bekle.from == ((bekle.to+1)%4))//left
							{
								check=false;
								break;
							}					
						}
						else if(controller.from == ((bekle.from+1)%4)) // coming from left
						{

							if(((bekle.from +1)%4) == bekle.to)//turning right dont conflict 
							{
							}
							else	//conflict
							{
								check=false;
								break;
							}

						}
						else if(((controller.from+1)%4) == bekle.from) //coming from right
						{
							check =false;
							break;
						}

					}
				
				}

			}

			if(check)
			{									//shurda uyandirmamiz lazim


//			pthread_mutex_lock(bekle.mutex);
				exiter.push_back(bekle);
	

//				pthread_cond_broadcast(bekle.condition); 
				//writeOutput(1,vehicleCode,intersectionCode,From,To);		
				writeOutput(1, bekle.vehicleCode,bekle.intersectionCode,bekle.from,bekle.to);
				sem_post(bekle.semaphore);				

//				pthread_mutex_unlock(bekle.mutex);







			}
			else
			{
				exiter2.push_back(nighter[intersectionCode].bekleyenler[j]);
			}			
		}


		nighter[intersectionCode].girenler.clear(); //girenleri update yapyoz

		for(int i=0; i<exiter.size(); i++)
		{
			nighter[intersectionCode].girenler.push_back(exiter[i]);
		}


		nighter[intersectionCode].bekleyenler.clear(); //bekleyenleri update yapyoz
		for(int i=0; i<exiter2.size(); i++)
		{
			nighter[intersectionCode].bekleyenler.push_back(exiter2[i]);
		}
		
		pthread_mutex_unlock(&night_mutex[intersectionCode]);
	
	
	}
	else
	{

		pthread_mutex_lock(&light_vehicle_seperator[intersectionCode]);
		writeOutput(2,vehicleCode,intersectionCode,From,To);
		araba_varmi[intersectionCode]--;
		if(araba_varmi[intersectionCode]==0)
		{

			pthread_mutex_lock(&araba_varmis[intersectionCode]);
			pthread_cond_broadcast(&arabayi_kaldir[intersectionCode]); 
			pthread_mutex_unlock(&araba_varmis[intersectionCode]); 
		}	
		pthread_mutex_unlock(&light_vehicle_seperator[intersectionCode]);


	}
}


void CrossRoad::SetGreenLight(int intersectionCode)
{

	pthread_mutex_lock(&light_vehicle_seperator[intersectionCode+1]);



	lightState[intersectionCode]++;
	if(lightState[intersectionCode] >= 4)
	{
		lightState[intersectionCode]=0;		
	}
	
	if(lightState[intersectionCode]==0)
	{	

		pthread_mutex_lock(&kirmizi[intersectionCode+1].allKirmizi[0]);
		writeOutput(3, 0, intersectionCode+1, WEST, SOUTH);    
		readers[intersectionCode+1].all[0]=0;
		pthread_cond_broadcast(&kirmizi[intersectionCode+1].allYesil[0]); 
		pthread_mutex_unlock(&kirmizi[intersectionCode+1].allKirmizi[0]);

		
	}
	else if(lightState[intersectionCode]==1)
	{



		pthread_mutex_lock(&kirmizi[intersectionCode+1].allKirmizi[1]);
		writeOutput(3, 0, intersectionCode+1, SOUTH, SOUTH);
		readers[intersectionCode+1].all[1]=0;
		pthread_cond_broadcast(&kirmizi[intersectionCode+1].allYesil[1]); 
		pthread_mutex_unlock(&kirmizi[intersectionCode+1].allKirmizi[1]);





	}	
	else if(lightState[intersectionCode]==2)
	{	


		pthread_mutex_lock(&kirmizi[intersectionCode+1].allKirmizi[2]);
		writeOutput(3, 0, intersectionCode+1, EAST,SOUTH);
		readers[intersectionCode+1].all[2]=0;
		pthread_cond_broadcast(&kirmizi[intersectionCode+1].allYesil[2]); 
		pthread_mutex_unlock(&kirmizi[intersectionCode+1].allKirmizi[2]);




	}	
	else
	{	

		pthread_mutex_lock(&kirmizi[intersectionCode+1].allKirmizi[3]);
		writeOutput(3, 0, intersectionCode+1, NORTH,SOUTH);
		readers[intersectionCode+1].all[3]=0;
		pthread_cond_broadcast(&kirmizi[intersectionCode+1].allYesil[3]); 
		pthread_mutex_unlock(&kirmizi[intersectionCode+1].allKirmizi[3]);



	}

	pthread_mutex_unlock(&light_vehicle_seperator[intersectionCode+1]);



}






void ayirici(string line, string &vCode, string &aTime, string &mTime)
{
	int length=line.length();
	int found;

	found=line.find_first_of(" ",0);
	vCode=line.substr(0,found);
	string devami=line.substr(found+1);

	length=devami.length();
	found=devami.find_first_of(" ",0);
	aTime=devami.substr(0,found);
	mTime=devami.substr(found+1);
}



vehicle function(string line)
{
	string vCode;
	string aTime;
	string mTime;

	ayirici(line,vCode,aTime,mTime);

	vehicle V;
	V.vehicleCode=atoi(vCode.c_str());
	V.arriveTime=atoi(aTime.c_str());
	V.moveTime=atoi(mTime.c_str());

	while(line != "NR")
	{
		string iCode;
		string from;
		string to;
		
		path P;		
		
		getline (cin,line);
		if(line != "NR")
		{
			ayirici(line, iCode, from, to);
			P.intersectionCode=atoi(iCode.c_str());
			//cout<<"hata = "<<P.intersectionCode<<endl;	
			if(from == "WEST")
				P.from = WEST;
			else if(from == "SOUTH")
				P.from = SOUTH;
			else if(from == "EAST")
				P.from = EAST;
			else
				P.from = NORTH;

			if(to == "WEST")
				P.to = WEST;
			else if(to == "SOUTH")
				P.to = SOUTH;
			else if(to == "EAST")
				P.to = EAST;
			else
				P.to = NORTH;

			(V.paths).push_back(P);				
		}		
	}

	return V;
}





int main(int argc, char *argv[])
{
	int N, mode, duration;
	
	N = atoi(argv[1]);// Number of intersections
	mode = atoi(argv[2]);// mode day(0) or night(1)
	duration = atoi(argv[3]);// duration of green light


	CrossRoad Road(N, mode);//Constructor

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);





///////////////////////////////////////////////////////////////////////// AKSAM 
	
nighter.resize(N+1);
night_mutex.resize(N+1);


pthread_mutex_init(&locker, NULL);
for(int i=1; i<=N; i++)
{
	pthread_mutex_init(&night_mutex[i], NULL);

}





//////////////////////////////////////////////////////////////////////////// AKSAM bitdi


/////////////////////////////////////////////////////////////////////////
	
light_vehicle_seperator.resize(N+1);
araba_varmi.resize(N+1);

readers.resize(N+1);
araba_var.resize(N+1);

araba_varmis.resize(N+1);
arabayi_kaldir.resize(N+1);


kirmizi.resize(N+1);

for(int i=1; i<=N; i++)
{
	pthread_mutex_init(&light_vehicle_seperator[i], NULL);
	
	pthread_mutex_init(&araba_varmis[i], NULL);
		
	araba_varmi[i]=0;
	readers[i].all[0]=0;
	readers[i].all[1]=0;
	readers[i].all[2]=0;
	readers[i].all[3]=0;
	
	
	kirmizi[i].allYesil.resize(4);
	kirmizi[i].allKirmizi.resize(4);
	pthread_mutex_init(&kirmizi[i].allKirmizi[0], NULL);
	pthread_mutex_init(&kirmizi[i].allKirmizi[1], NULL);
	pthread_mutex_init(&kirmizi[i].allKirmizi[2], NULL);
	pthread_mutex_init(&kirmizi[i].allKirmizi[3], NULL);


	
}



////////////////////////////////////////////////////////////////////////////
	pthread_t traffic_light_threads[N];
	intersectionData argument[N];

	for(int i=0; i<N; i++)
	{
		argument[i].intersectionCode=i;
		argument[i].duration=duration;
		argument[i].crossroad=&Road;
	}

	if(mode==0) //start_traffic_light_thread
	{
		for (int i = 0; i < N; i++)
		pthread_create(&traffic_light_threads[i], &attr, trafficLight, (void*) &argument[i]);

	}
////////////////////////////////////////////////////////////////////



vector<vehicle> vehicles;
vector<pthread_t> vehicle_threads;

vector<vehicleData>argument_vehicle1;


string line;
while(getline(cin,line))
{

		vehicle VV = function(line); //vehicle al

		vehicleData* argument_vehicle = new vehicleData; 

		argument_vehicle->iVehicle=VV;
		argument_vehicle->crossroad=&Road;


		pthread_t Vthread;
		vehicle_threads.push_back(Vthread);
		
		pthread_create(&vehicle_threads[vehicle_threads.size()-1], &attr, vehicle_thread, (void*) argument_vehicle);


pthread_mutex_lock(&locker);
sayici++;
pthread_mutex_unlock(&locker);

}







while(1)
{
	if(!sayici)
		break;
}

///////////////////////////////////////////////////////


//	for (int i = 0; i < vehicles.size(); i++)
//		pthread_join(vehicle_threads[i], NULL);


//	for (int i = 0; i < N; i++)
//		pthread_join(traffic_light_threads[i], NULL);


//pthread_exit(0);

	return 0;
}

