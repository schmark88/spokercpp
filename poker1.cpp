// poker1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "lap.h"


//f�ggv�ny pontsz�mok ki�rt�kel�s�re
int Pontszam(lap lap1,lap lap2,lap lap3,lap lap4, lap lap5){
	//lapok magass�ga �s szine t�mb�kben t�rolva,egy�b v�ltoz�k
	int M[5];
	M[0]=lap1.getLapM();
	M[1]=lap2.getLapM();
	M[2]=lap3.getLapM();
	M[3]=lap4.getLapM();
	M[4]=lap5.getLapM();
	bool sor=true;
	int S[5];
	S[0]=lap1.getLapSz();
	S[1]=lap2.getLapSz();
	S[2]=lap3.getLapSz();
	S[3]=lap4.getLapSz();
	S[4]=lap5.getLapSz();
	int has=0;
	int has2=0;
	int hLap=0;
	int pont;
	bool szin=false;
	try{
	//sorbarendez� algoritmus
	for (int i = 0;i<5;i++) {
        for (int j = i+1;j<5;j++) {
           if (M[j] > M[i]) {
               int t=M[i];
			   M[i]=M[j];
			   M[j]=t;
           }
		}
	}
	pont=M[0];
	//sor vizsg�lata
	for(int i=0;i<4;i++){
		if(M[i]!=(M[i+1]+1)){
			sor=false;
		}
				
	}
	//azonos magas�gg� lapok vizsg�lata
	for(int i=0;i<4;i++){
		if(M[i]==(M[i+1])){
			has++;
			if(hLap<M[i])hLap=M[i]; //legmagasabb �rt�k� p�r elt�rol�sa, ezzel n�velj�k meg az alap pontsz�mot poker drill p�r eset�n
		}else if (has!=0 && has2==0){
			has2=has;
			has=0;
		}
				
	}
	//sz�n egyez�s
	for(int i=0;i<4;i++){
		if(S[i]!=(S[i+1])){
			szin=false;
		}
	}
	//ki�rt�kel�s
	if(has2==1 || has==1){
		pont=20+hLap;
	}
	if(has2==1 && has==1){
		pont=40+hLap;
	}
	if(has2==2 || has==2){
		pont=60+hLap;
	}
	if(sor){
		pont=80+M[0];
	}
	if(szin){
		pont=100+M[0];
	}
	if((has2==2 && has==1) || (has2==1 && has==2)){
		pont=120+hLap;
	}
	if(has2==3 || has==3){
		pont=140+hLap;
	}
	if(szin && sor){
		pont=160+M[0];
	}
	if(sor && M[0]==13){
		pont=180;
	}
	}catch(...){
		cout<< "hiba a programban"<< endl;
	}
	 return pont;
}

int _tmain(int argc, _TCHAR* argv[])
{	
	//random seed
	srand((unsigned)time(NULL));
	// k�l�nf�le v�ltoz�k
	ofstream log;
	log.open ("log.txt",ios::app);
	int R[10]; //haszn�lt randomok t�mbje
	int random; // jelenlegi random �rt�k
	int j = 0;
	int c = 0;
	int randt; // ideiglenes random
	int randi=0;// index a random t�mbh�z
	int pontP=0;
	int pontE=0;
	int b=0;
	bool k=false; // cilus v�ltozo
	bool hvalasz;// v�laszok �rv�nyess�g�t t�rol� v�ltoz�
	//pakli l�trehoz�sa
	lap *Pakli= new lap[52];

	try{
	for(int a = lap::treff; a <= lap::pikk; a++){
		for( int i = 0; i < 13; i++ ){
		    Pakli[j++]=lap(a,i);
		}
	}
	
	//oszt�s
	//J�t�kos 2 lapot kap amit t�mbben t�rolunk
	lap Player[2];
	while( c!=2){
		//biztos�tja h ne kapjuk 2x ugyanazt a randomot
		do{
			k=false;
			randt=rand()%52;
			for(int i=0;i<10;i++){
				if(R[i]==randt){
				k=true;
				}
			}
			if(!k){
				R[randi]=randt;// Haszn�lt randomok t�mbj�be helyezz�k a jelenlegit
				random=randt;
				randi++;
			}
		}while(k);
		Player[c]= Pakli[random];
		c++;
		
	}
	c=0;
	// Ellenf�l 2 lapot kap amit t�mbben t�rolunk
	lap Enemy[2];
	while( c!=2){
		//biztos�tja h ne kapjuk 2x ugyanazt a randomot
		do{
			k=false;
			randt=rand()%52;
			for(int i=0;i<10;i++){
				if(R[i]==randt){
				k=true;
				}
			}
			if(!k){
				R[randi]=randt;// Haszn�lt randomok t�mbj�be helyezz�k a jelenlegit
				random=randt;
				randi++;
			}
		}while(k);	
		Enemy[c]= Pakli[random];//k�rtya kioszt�sa 
		c++;
	}
	
	c=0;
	//j�t�kos lapjainak ki�r�sa, megbizonyod�s arr�l szeretn�-e folytatni a j�t�kot
	cout <<"Az On Lapjai:" <<endl;
	Player[0].print();
	Player[1].print();
	//v�lasz �rv�nyess�g�nek ellen�rz�se
	hvalasz=true;
			while(hvalasz){
				cout<< "Folytatja? igen-1 nem-2"<< endl;
				cin >>j;
				if (j==2){
					c=3;
					hvalasz=false;
				}else if(j==1){
					hvalasz=false;
					}else {
					hvalasz=true;
					cout<<"nincs iylen opci�"<<endl;
				}
			}
	//Asztalon l�v� 3 lap kioszt�sa szint�n t�mbben t�rolva. Minden kiosztott lap ut�n �jabb k�rd�s
	lap Table[3];
	if (j==1){
		cout<<endl;
		cout<<"Asztalon levo lapok:"<<endl;
		while( c!=3){
			//biztos�tja h ne kapjuk 2x ugyanazt a randomot
			do{
				k=false;
				randt=rand()%52;
				for(int i=0;i<10;i++){
					if(R[i]==randt){
					k=true;
					
					}
				}
				if(!k){
					R[randi]=randt;
					random=randt;
					randi++;
				}
			}while(k);	
			k=false;
			Table[c]= Pakli[random];//k�rtya kioszt�sa
			Table[c].print();
			c++;
			hvalasz=true;
			while(hvalasz && c!=3 ){
				cout<< "Folytatja? igen-1 nem-2"<< endl;
				cin >>j;
				if (j==2){
					c=3;
					hvalasz=false;
				}else if(j==1){
					hvalasz=false;
					}else {
					hvalasz=true;
					cout<<"Nincs iylen opcio!!"<<endl;
				}
			}
		}
		cout<<endl;
		cout<<"Ellenfel lapjai:"<<endl;
		Enemy[0].print();
		Enemy[1].print();
	}
	//pontsz�mok ki�rt�kel�se,eredm�ny ki�r�sa
	pontP=Pontszam(Player[0],Player[1],Table[0],Table[1], Table[2]);
	pontE=Pontszam(Enemy[0],Enemy[1],Table[0],Table[1], Table[2]);
	if (pontP < pontE || j==2){
		cout<<"Vesztettel"<<endl;
		log<<"Vesztettel"<<endl;
		if(j==1){
		cout<< "Pontjaid:  "<< pontP<<endl;
		cout<< "Ellenfel:  "<< pontE<<endl;
		log<< "Pontjaid:  "<< pontP<<endl;
		log<< "Ellenfel:  "<< pontE<<endl;
		}
	}else {
		cout<<"Nyertel"<<endl;
		log<<"Nyertel"<<endl;
		if(j==1){
		cout<< "Pontjaid:  "<< pontP<<endl;
		cout<< "Ellenfel:  "<< pontE<<endl;
		log<< "Pontjaid:  "<< pontP<<endl;
		log<< "Ellenfel:  "<< pontE<<endl;
		}
		}
	//operator overloading haszn�lata
	cout<< "Legnagyonn lapod:"<<endl;
	if(Player[0]>Player[1]){
		Player[0].print();
	}else {
		Player[1].print();
	}
	}catch(...){
		cout<< "Hiba a programban"<<endl;
	}
	//dinamikus mem�ria felszabad�t�s,f�jl bez�r�sa
	delete[] Pakli;
	log.close();
	return 0;
}

