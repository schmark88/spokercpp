#include "StdAfx.h"
#include "lap.h"


lap::lap(){
}
lap::lap(int param1,int param2)
{
	szin=szin_t(param1);
	magassag=param2;
}

lap::szin_t lap::getLapSz(){
	return szin;
}
int lap::getLapM(){
	return magassag;
}

void lap::print(){
	static char *Szam[] = { 
      "2", "3", "4", "5", "6", "7", "8", "9",
      "10", "Bubi", "Dama", "Kiraly", "Asz"
	};
	
	static char *Sz[] = {
      "Treff", "Kor", "Karo", "Pikk" 
	};
	cout <<Sz[getLapSz()]<<" - ";
      cout<< Szam[getLapM()]<<endl;
	
}
bool lap::operator>(lap& l){
                getLapM();
				l.getLapM();
                return ( getLapM()> l.getLapM());
        }
lap::~lap(void)
{
}
