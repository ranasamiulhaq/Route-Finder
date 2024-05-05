#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


#define INF 999
#define size 13

//---------------------------------------------------    Struct Header  ----------------------------------
int types[] = {0,0,0,0};
int Source[]= {0,0,0,0,0,0,0,0,0,0,0,0};
int des[] = {0,0,0,0,0,0,0,0,0,0,0,0};


struct vehicle{
	int type;
	int Source;
	int v_dest;
	string Reg;
	
	vehicle* next = NULL;
};
vehicle* head = NULL;
vehicle* tail = NULL;


//                                              <------------------------------------------------>


//--------------------------------------------------------    Method Headers   --------------------------------

void display(int dist[] ,int distt[], int parent[]);
void dijsktra(int cost[][size] , int tiime[][size]  ,int distDistance[] , int distTime[], bool visited[] , int parent[]);
int getNearest(bool b[] , int d[]);
void init(int pparent[], int ddist[] ,int distt[],  bool visit[]);
void trafficgenerator();
void insert(vehicle** f,vehicle** l ,int tp,string rg,int s,int d);
void pathcall(vehicle** head);
void Welcome();
void welcomeVehical();


//                                              <------------------------------------------------>




//--------------------------------------------------------    Global Initilizations            --------------------------------- 

string signals[13] = {" Airport " , " 26 Number " , " Peshawar Moor " , " Zero Point " , " Serena Hotel " , " Stadium " , " Faizabad " , " Rawal Chock " ,
					 " Comsats " , " Khanapul " , " Taramri " , " T-Chock "}; 
string vehicalArray[4] = {"Ambulance   " , "FireTruck   " , "Police Car   " , "Car   "}; 

int V=12;    
  
int distD[13] = {} ;         // For Distance 
int distT[13] = {} ; 		// For Traffic Time Route
        
bool visitedD[13] = {false};	// For Distance
bool visitedT[13] = {false};	// For Traffic Time Route

int parentD[13] = {} ;		// For Distance Nodes
int parentT[13] = {} ;		// For Traffic Time Nodes
//int parent[9];
int totVehicals = 0;
//              			Connectivity Graph
//				        0	1	2	3	4	5	6	7				
int connection[size][size]=	 {{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0}, //0
					   	  { 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0}, //1
					   	  { 0 , 1 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0}, //2
					   	  { 0 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0}, //3
					   	  { 0 , 0 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 0 , 0 , 0 , 0}, //4
					  	  { 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0}, //5
					  	  { 0 , 0 , 0 , 1 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0}, //6
					  	  { 0 , 0 , 0 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 0}, //7
					  	  { 0 , 0 , 0 , 0 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 0 , 0}, //8
					  	  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 1 , 0}, //9
					  	  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 1 , 1}, //10
					  	  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 0 , 0}, //11
					  	  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0}};//12
			  
			  //				distance Graph
//				      		0	  1	    2 	  3	    4     5	    6  	  7     8 	  9     10    11    12    			
int Distance[size][size]={{ 999 , 999 , 999 , 999 , 999 , 999 , 999 , 999 , 999 , 999 , 999 , 999 , 999}, //0
					   	  { 999 , 999 ,  18 , 999 , 999 , 999 , 999 , 999 , 999 , 999 , 999 , 999 , 999}, //1
					   	  { 999 ,  18 , 999 ,  12 , 999 , 999 , 999 , 999 , 999 , 999 , 999 , 999 , 999}, //2
					   	  { 999 , 999 ,  12 , 999 ,  2  , 999 ,  4  , 999 , 999 , 999 , 999 , 999 , 999}, //3
					   	  { 999 , 999 , 999 ,  2  , 999 ,  8  , 999 ,  4  , 999 , 999 , 999 , 999 , 999}, //4
					  	  { 999 , 999 , 999 , 999 ,  8  , 999 , 999 , 999 ,  5  , 999 , 999 , 999 , 999}, //5
					  	  { 999 , 999 , 999 ,  4  , 999 , 999 , 999 ,  2  , 999 , 999 , 999 , 999 , 999}, //6
					  	  { 999 , 999 , 999 , 999 ,  4  , 999 ,  2  , 999 ,  7  , 999 ,  6  , 999 , 999}, //7
					  	  { 999 , 999 , 999 , 999 , 999 ,  5  , 999 ,  7  , 999 ,  7  , 999 , 999 , 999}, //8
					  	  { 999 , 999 , 999 , 999 , 999 , 999 , 999 , 999 ,  7  , 999 , 999 ,  1  , 999}, //9
					  	  { 999 , 999 , 999 , 999 , 999 , 999 , 999 ,  6  , 999 , 999 , 999 ,  8  ,  15}, //10
					  	  { 999 , 999 , 999 , 999 , 999 , 999 , 999 , 999 , 999 ,  1  ,  8  , 999 , 999}, //11
					  	  { 999 , 999 , 999 , 999 , 999 , 999 , 999 , 999 , 999 , 999 ,  15 , 999 , 999} //12
					  	  };
					  	  

int BaseTime[size][size]= {{ 999 , 999 , 999 , 999 , 999 , 999 , 999 , 999 , 999 , 999 , 999 , 999 , 999}, //0
					   	  { 999 , 999 ,  10 , 999 , 999 , 999 , 999 , 999 , 999 , 999 , 999 , 999 , 999}, //1
					   	  { 999 ,  10 , 999 ,  10 , 999 , 999 , 999 , 999 , 999 , 999 , 999 , 999 , 999}, //2
					   	  { 999 , 999 ,  10 , 999 ,  2  , 999 ,  2  , 999 , 999 , 999 , 999 , 999 , 999}, //3
					   	  { 999 , 999 , 999 ,  2  , 999 ,  4  , 999 ,  2  , 999 , 999 , 999 , 999 , 999}, //4
					  	  { 999 , 999 , 999 , 999 ,  4  , 999 , 999 , 999 ,  4  , 999 , 999 , 999 , 999}, //5
					  	  { 999 , 999 , 999 ,  2  , 999 , 999 , 999 ,  2  , 999 , 999 , 999 , 999 , 999}, //6
					  	  { 999 , 999 , 999 , 999 ,  2  , 999 ,  2  , 999 ,  8  , 999 ,  5  , 999 , 999}, //7
					  	  { 999 , 999 , 999 , 999 , 999 ,  4  , 999 ,  8  , 999 ,  7  , 999 , 999 , 999}, //8
					  	  { 999 , 999 , 999 , 999 , 999 , 999 , 999 , 999 ,  7  , 999 , 999 ,  2  , 999}, //9
					  	  { 999 , 999 , 999 , 999 , 999 , 999 , 999 ,  5  , 999 , 999 , 999 ,  8  ,  20}, //10
					  	  { 999 , 999 , 999 , 999 , 999 , 999 , 999 , 999 , 999 ,  2  ,  8  , 999 , 999}, //11
					  	  { 999 , 999 , 999 , 999 , 999 , 999 , 999 , 999 , 999 , 999 ,  20 , 999 , 999} //12
					  	  };
					  	  
													  			  				
int traffic[size][size] ;
int rushtime[size][size] ;
				  
				  
//                                              <------------------------------------------------>
				  

//----------------------------------------------------------Randomising the Traffic Graph-----------------------------------------------------------------


void trafficgenerator(){
	srand(time(0));
														 	//				Traffic Graph
													//				      0	    1	  2 	3	  4 	5	  6  	7    8
int    temp[size][size]={ { 999 , 999        , 999 		  , 999 	  , 999 		, 999 		, 999 		, 999 		, 999 , 999 , 999 , 999 , 999}, //0
					   	  { 999 , 999        ,  rand()%10 , 999 	  , 999 		, 999 		, 999 		, 999 		, 999 , 999 , 999 , 999 , 999}, //1
					   	  { 999 ,  rand()%10 , 999 		  , rand()%10 , 999 		, 999 		, 999 		, 999 		, 999 , 999 , 999 , 999 , 999}, //2
					   	  { 999 , 999 		 ,  rand()%10 , 999 	  ,  rand()%10  , 999 		,  rand()%10, 999 		, 999 , 999 , 999 , 999 , 999}, //3
					   	  { 999 , 999 		 , 999 		  , rand()%10 , 999 		, rand()%10 , 999 		, rand()%10 , 999 , 999 , 999 , 999 , 999}, //4
					  	  { 999 , 999        , 999 		  , 999 	  ,  rand()%10  , 999 		, 999 		, 999 		,  rand()%10  , 999 , 999 , 999 , 999}, //5
					  	  { 999 , 999		 , 999 		  , rand()%10 , 999 		, 999 		, 999 		, rand()%10 , 999 , 999 , 999 , 999 , 999}, //6
					  	  { 999 , 999   	 , 999		  , 999 	  ,  rand()%20  , 999 		,  rand()%20, 999 		,  rand()%20  , 999 ,  rand()%20  , 999 , 999}, //7
					  	  { 999 , 999 	 	 , 999 		  , 999 	  , 999 		,  rand()%10, 999 		,  rand()%10, 999 ,  rand()%10  , 999 , 999 , 999}, //8
					  	  { 999 , 999		 , 999 		  , 999 	  , 999 		, 999 		, 999 		, 999 		,  rand()%10  , 999 , 999 ,  rand()%10  , 999}, //9
					  	  { 999 , 999 		 , 999 		  , 999 	  , 999 		, 999 		, 999 		,  rand()%10, 999 , 999 , 999 ,  rand()%10  ,  15}, //10
					  	  { 999 , 999 		 , 999 		  , 999 	  , 999 		, 999 		, 999 		, 999 , 999 ,  rand()%10  ,  rand()%10  , 999 , 999}, //11
					  	  { 999 , 999 		 , 999 		  , 999 	  , 999 		, 999 		, 999 		, 999 , 999 , 999 ,  rand()%10 , 999 , 999} //12
					  	  };
	for(int i=0 ; i<size ; i ++){
		for(int j=0 ; j<size ; j++ ){
			traffic[i][j] = temp[i][j];
			
			if(temp[i][j] == 999 ){
				rushtime[i][j] = temp[i][j];
			}
			else
				rushtime[i][j] = BaseTime[i][j] + (temp[i][j] * 1.5);
		}
 
	}
		
}
//----------------------------------------------------------------------------------------------------------

void checktype(vehicle** f){
	vehicle* p = *f;
	
	while(p!=NULL){
		if((p)->type == 1){
			types[0]++;
//			cout<<types[0];
		}
		else if(p->type == 2){
		
		types[1]++;
	}
	else if(p->type == 3){
		types[2]++;
	}
	else if(p->type == 4){
		types[3]++;
	}
	p=p->next; 
	
}
}

void checkpath(vehicle** f,int arr[],int x){
	vehicle* p = *f;
	int v;
	
	while(p!=NULL){
		if(x==1){
		v = p->Source;	
		}
		else if(x ==2){
			v = p->v_dest;
		}
		switch(v){
//			case 0 :arr[0]++; 
//					break;
			case 1 : arr[0]++;
					 break;
			case 2 : arr[1]++;
					break;
			case 3: arr[2]++;
					break;
			
			case 4 : arr[3]++;
			break;
			case 5 :arr[4]++;
			 break;
			case 6 : arr[5]++;
			break;
			case 7 :  arr[6]++;
			break;
			case 8 : arr[7]++; 
			break;
			case 9 : arr[8]++;
			 break;
			case 10 : arr[9]++;
			break;
			case 11 :  arr[10]++;
			break;
			case 12 :  arr[11]++;
			break;
			
		}
	
	p=p->next; 
	
}
}

void displaypath(int arr[],string s[]){
	for(int i = 0 ; i< 12 ; i++){
		switch(i){
			case 0 : cout<< "\n"<<s[i]<<":     "<<arr[i]; break;
			case 1 : cout<< "\n"<<s[i]<<":     "<<arr[i]; break;
			case 2 : cout<< "\n"<<s[i]<<":     "<<arr[i]; break;
			case 3 : cout<< "\n"<<s[i]<<":     "<<arr[i];break;
			case 4 : cout<< "\n"<<s[i]<<":     "<< arr[i];break;
			case 5 : cout<< "\n"<<s[i]<<":     "<<arr[i]; break;
			case 6 : cout<< "\n"<<s[i]<<":     "<<arr[i]; break;
			case 7 : cout<< "\n"<<s[i]<<":     "<<arr[i];break;
			case 8 : cout<< "\n"<<s[i]<<":     "<<arr[i];break;
			case 9 : cout<< "\n"<<s[i]<<":     "<<arr[i]; break;
			case 10 :cout<< "\n"<<s[i]<<":     "<<arr[i]; break;
			case 11 :cout<< "\n"<<s[i]<<":     "<<arr[i];break;
//			case 12 :cout<< "\n"<<s[i-1]<<"   "<< arr[12];break;
//			case 12 : cout << "\n"<<s[i]<< "   "<< arr[12];break;
			
		}
//		cout<<arr[i];
	}
}

void displayvehicles(int arr[]){
	for(int i = 0 ; i< 4 ; i++){
		switch(i){
			case 0 : cout<<"\nAMBULANCE    "<<arr[0]; break;
			case 1 : cout<<"\nFIRE TRUCK "<<arr[1]; break;
			case 2 : cout<< "\nPOLICE    "<<arr[2];break;
			case 3 : cout << "\nPERSONAL   "<< arr[3];break;
		}
//		cout<<arr[i];
	}
}

//                                              <------------------------------------------------>




// --------------------------------------------------Local Method for Dijkestra -------------------------------------------------------------------


void init(int pparent[], int ddist[] ,int distt[],  bool visit[] ,int source_vertex , int destination){ 
    for (int i = 1; i <= V; i++)
    {
        pparent[i] = i;
        ddist[i] = INF;
        distt[i] = INF;
        visit[i] = false;
        for (int j = 1; j <= V; j++) 
        	traffic[i][j] = 0;
    }
    ddist[source_vertex] = 0;
    distt[source_vertex] = 0;
}

//                                              <------------------------------------------------>

//-----------------------------------------------------         STACK        --------------------------------------------------------------------------


string Stackarr[10];
int top = -1;


void push(string x){
    if(top == -1){
        Stackarr[++top] = x;
    }
    else
        Stackarr[++top] = x;

}

string pop(){
    if (top==-1)
    {
        cout<<"\nEMPTY";
    }
    
    else
        return Stackarr[top--];
}

//                                                <------------------------------------------>


//  ---------------------------------------------------  Vehicals Counter   -----------------------------------------------------------------------


// --------------------------------------------------Local Method for Dijkestra -------------------------------------------------------------------


int getNearest(bool b[] , int d[]){
                       // returns the nearest unvisited vertex with least distance
    int minValue = INF; // initially all the nodes have 999 distance
    int minValueNode = 0;
    for (int i = 1; i <= V; i++)
    {
        if (!b[i] && d[i] < minValue)
        {
            minValue = d[i];
            minValueNode = i;
        }
    }
    return minValueNode;
}

//                                              <------------------------------------------------>




//----------------------------------------------------------Modified Dijkestra for specific route ---------------------------------------------------



void dijsktra(int cost[][size] , int tiime[][size]  ,int distDistance[] , int distTime[], bool visited[] , int parent[] , int source_vertex , int destination){
	
	init(parent, distTime,distDistance,visited,source_vertex , destination);
	//trafficgenerator();
	totVehicals = 0;
	
    for (int i = 1; i <= V; i++){
    	int nearestUnvisitedVertex = getNearest(visited , distDistance);
        visited[nearestUnvisitedVertex] = true; // vetex visited
		
	  	
	
	
        // update the distDistanceance of adjancent nodes
        for (int adj = 1; adj <= V; adj++)
        {
                if (cost[nearestUnvisitedVertex][adj] != INF &&
	                distDistance[adj] > distDistance[nearestUnvisitedVertex] + cost[nearestUnvisitedVertex][adj])
	            {
	                distDistance[adj] = distDistance[nearestUnvisitedVertex] + cost[nearestUnvisitedVertex][adj];
	                distTime[adj] = distTime[nearestUnvisitedVertex] + tiime[nearestUnvisitedVertex][adj];
	                parent[adj] = nearestUnvisitedVertex; 
	                totVehicals = totVehicals  + traffic[nearestUnvisitedVertex][adj];
			    }
        }
    	
    }
    
}

//                                              <------------------------------------------------>


//------------------------------------------------------Display For Route of Distance and Time ---------------------------------------------------------


void display(int dist[] ,int distt[], int parent[], int source_vertex , int destination){
    	
    	cout << "\n|          Total Distance  in KMs            :          " << dist[destination] <<"                          |" << endl;
    	cout << "|          Total Time Travell                :          " << distt[destination]<<"                          |"  << endl;
    	cout << "|          Number of Vehicals on route       :          " << totVehicals <<"                          |" << endl;
    	cout<<"|                                                                                   |";
		cout << "\n|                   Your Path will be "<<"                                              |\n" ;
        //cout << " "<<
		push(signals[destination-1]) ;
        int parnode = parent[destination];
        while (parnode != source_vertex && (parnode > 0 && parnode < 13))
        {
           // cout << "<--" <<
		    push(signals[parnode-1]);
			// << " ";
            parnode = parent[parnode];
        }
        //cout<<"<--"<< 
		push(signals[source_vertex-1]);
		// << " "<< endl;
		
		while(top!= -1){
			cout<< pop() <<" --> " ;
		}
		
        cout<<"\n|                                                                                   |\n";
        cout<<"|                                                                                   |";    
}
//                                              <------------------------------------------------>



//---------------------------------------------------------- Graphs Display Meathod -----------------------------------------------------------------------


void displayarray(int a[][size]){
	for(int i=0 ; i<size ; i ++){
		for(int j=0 ; j<size ; j++ ){
			cout << a[i][j] << "      ";
			
		}
		cout <<"\n";
	}
}

//                                              <------------------------------------------------>


//---------------------------------------------------------Vehicals Struct-----------------------------------------------------------------------

//----------------------------------------------------Priority Queue For Vehicals-----------------------------------------------------------------


void insert(vehicle** f,vehicle** l ,int tp,string rg,int s,int d){
	vehicle* curr = new vehicle;
	curr->Source=s;
	curr->type = tp;
	curr->v_dest = d;
	curr->Reg = rg;
		
	if((*f)==NULL) {
		(*f) =(*l)= curr;
	}

	else {
		
		if((*f)->type >= curr->type){
		
			curr->next = (*f);
			(*f) = curr;
		}
	
		else{
		vehicle* p = *f;
		vehicle* q = NULL;
			while(p->next!=NULL && p->next->type <= curr->type){
				q=p;
				p=p->next;
			}
		
			curr->next = p->next;
			p->next = curr;
		
	}
}
}
void pathcall(vehicle** head){
	vehicle* p = *head;
	trafficgenerator();
	while(p!=NULL){
		
		cout<<" _____________________________\n";
		cout<<"|                                                                                   |";
	    cout<<"\n|                                   "<<vehicalArray[p->type-1]<<"                                    |";
		//cout<<"\n|----------------->    Registration           "<<p->Reg<<"    <---------------------------|\n";
		cout<<"\n|                 >    Registration           "<<p->Reg<<"    <                           |\n";
		cout<<"|_____________________________|\n";
		cout<<"|                                                                                   |";
		
		cout<<"\n|                               Shortest Route"<<"                                      |\n";
		cout<<"|                                                                                   |";
		dijsktra(Distance , rushtime ,distD, distT, visitedD , parentD,p->Source ,p->v_dest);
		display(distD,distT, parentD, p->Source , p->v_dest);
		
		cout<<"\n|_____________________________|\n";
		cout<<"|                                                                                   |";
		cout<<"\n|                         >    Best Route As Per Traffic "<<"    <                      |";
		cout<<"\n|                                                                                   |";
		dijsktra(rushtime , Distance ,distD, distT, visitedT , parentT, p->Source , p->v_dest);
		display(distT,distD, parentT, p->Source , p->v_dest);
		cout<<"\n|_____________________________|\n";

		p = p->next;
		
		
	}
}
//	/cout<<vehicalArray[(p->type)-1]<<"  "<<p->Reg << "\n "<<p->Source<<"  "<<p->Source<<"  "<<p->v_dest<<endl;
//}


//                                   <-------------------------END OF VEHICALS STRUCT--------------------------------------->


//-----------------------------------------------------------WELCOME SCREEN CODE---------------------------------------------------------------------
//--------------------------------------------------------------------------------


void Welcome(){	
	cout<< " \n Welcome to the Traffic Control Algorithm \n";
	
	cout<< " \n Please Seletect Your Starting Location and Destination \n";
	cout<< " \n Enter Choice from 1-12 \n";
	cout<< "1)  Airport ";
	cout<< "\n2)  26 Number ";
	cout<< "\n3)  Peshawar Moor ";
	cout<< "\n4)  Zero point ";
	cout<< "\n5)  Serena Chock ";
	cout<< "\n6)  Stadium ";
	cout<< "\n7)  Faizabad ";
	cout<< "\n8)  Rawal Chock ";
	cout<< "\n9)  Comsats ";
	cout<< "\n10) KhannaPul ";
	cout<< "\n11) Taramri Chock ";
	cout<< "\n12) T Chock ";
	
}

void welcomeVehical(){
	
	cout<<"-----------Welcome--------------";

	int type,source,dest;
	string reg;
	
	cout<<"\n\n Plese select your car type";
	cout<<"\n (1)  for Ambulance ";
	cout<<"\n (2)  for Fire bergate ";
	cout<<"\n (3)  for Police mobile ";
	cout<<"\n (4)  for Personal ";
	
	cout<<"\n Your Car type: ";
	cin>>type;
	cout<<"\n Enter Registraion Number : ";
	cin>>reg;
	
	Welcome();
	
	cout<<"\n Enter your Source: ";
	cin>>source;
	cout<<"\n Enter your Destination: ";
	cin>>dest;
		
	insert(&head,&tail,type,reg,source,dest);
}




//---------------------------------------------------------    MAIN    --------------------------------------------------------------------------------
int main(){
	int source_vertex , destination;
	bool flag = true;
	char choice;
	
//	while(flag){
//		
	//Welcome();
	cout<< "\n\n--------------------------------------------------\n\n";
	
	int check = 1;

	while(check != 0 ){
		welcomeVehical();
		cout<<"Press  0 to stop ";
		cin>>check;
		
	
	}
	
		
	pathcall(&head);
		
	checktype(&head);
	checkpath(&head,Source,1);
	checkpath(&head,des,2);
	cout<<"\n------------------------TYPES OF CARS----------------------------";
	displayvehicles(types);
	
	
	cout<<"\n------------------------VEHCILES MOVING FROM SOURCE ----------------------------";
		
		

		displaypath(Source,signals);
		
			cout<<"\n------------------------VEHCILES MOVING TOWARDS DESTINATION ----------------------------";


displaypath(des,signals);
	
	
    //displayarray(traffic);
    //displayarray(rushtime);
 //
    //display(distD,distT, parentT);
    
    
    cout<< "\nWant to Exit ? (y/n) \n" << traffic [1][2];
    cin >> choice;
    
    
//}
	getchar();

    return 0;
}


