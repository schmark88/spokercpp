#pragma once
#include <iostream>
using namespace std;
//Osztály ami a lapokat reprezentálja a játékban
class lap
{
public:
	typedef enum {treff=0,kor=1,karo=2,pikk=3}szin_t;
private: 
	int magassag;
	szin_t szin;
public:
	lap();
	lap(int,int);
	szin_t getLapSz(void);
	int getLapM(void);
	void print();
	bool operator>( lap& l);
	~lap(void);
};
