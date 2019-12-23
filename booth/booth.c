#include <string>
#include <iostream>
using namespace std;

class bus
{
public:
	string v;
	bus() { v.resize(1, 'X'); }
	bus(int SIZE, char c) { v.resize(SIZE, c); }
	bus(const string s) { v = s; }
	bus(const char* c) { v = c; }
	bus(const int i) { v = toBinary(i); }
	bus(const bus& a) { v = a.v; }

	void fill(char c)
	{
		v.assign(v.length(), c);
	};

	friend bool operator== (bus a, bus b)
	{
		return (a.v == b.v);
	}

	friend bus operator~ (bus a)
	{
		a.v = ;
	}
};


class registerER
{
	bus *d, *c, *q, *e ,*r;
public:
	registerER(bus& D, bus& Q, bus& clk, bus& rst, bus& En) { d = &D; c = &clk; q = &Q; e = &En; r = &rst; }
	void evl()
	{
		if (r->v == "1") q->fill('0');
		else if (e->v == "1") q->v = d->v;
	};
};


class MUX2to1
{
	bus *i1, *i2, *sel, *o1;
public:
	MUX2to1(bus& a, bus& b, bus& select, bus& out) : i1(&a), i2(&b), sel(&select), o1(&out)
	{
		o1->fill('X');
	};
	
	void evl()
	{
		if (*sel == "0") *o1 = *i1;
		else *o1 = *i2;
	};

};


class Controller
{

};

class Datapath
{
	bus *a, *b;
	bus *Clock, *Reset;
	bus *EnableA, *EnableB, *EnableP, *EnableM, *EnableN, *EnableR;
	bus	*Selecl;
	bus* twobit;

	registerER* Areg;
	registerER* Breg;
	registerER* Mreg;
	registerER* Nreg;
	registerER* Preg;
	registerER* Rreg;

	MUX2to1* Multiplexer;

	bus Aout, Bout, Pout, Mout, Nout, Rout;
	bus Anot;
	bus MUXOut;
	bus complimentA;
	bus shifted;


public:
	Datapath(bus& A, bus& B, bus& EnA, bus& EnB, bus& EnM, bus& EnN, bus& EnP, bus& Clk, bus& Rst, bus& Sel, bus& EnR, bus& twoin) : a(&A), b(&B), Clock(&Clk), Reset(&Rst), EnableA(&EnA), EnableB(&EnB), EnableP(&EnP), EnableM(&EnM), EnableN(&EnN), Selecl(&Sel), EnableR(&EnR), twobit(&twoin)
	{
		Areg = new registerER(*a, Aout, *Clock, *Reset, *EnableA);
		Breg = new registerER(*b, Bout, *Clock, *Reset, *EnableB);
		Preg = new registerER(shifted, Pout, *Clock, *Reset, *EnableP);
		Mreg = new registerER(Aout, Mout, *Clock, *Reset, *EnableM);
		Nreg = new registerER(complimentA, Nout, *Clock, *Reset, *EnableN);
		Rreg = new registerER(Pout, Rout, *Clock, *Reset, *EnableR);

		Multiplexer = new MUX2to1(Mout, Nout, *Selecl, MUXOut);
	}

		void evl()
		{
			Areg->evl();
			Breg->evl();

			Anot = ~Aout;

			Mreg->evl();
			Nreg->evl();
			Preg->evl();
			Multiplexer->evl();
			//ADD;


		};



};

class controler
{
	bus *Clock, *Reset;
	bus *EnableA, *EnableB, *EnableP, *EnableM, *EnableN, *EnableR;
	bus	*Selecl;
	bus *twobit;

	int Nstate;
	int Pstate;

public:
	controler(bus &Clk, bus &Rst,
		bus &EA, bus &EB, bus &EP, bus &EM, bus &EN, bus &ER,
		bus &Sel,
		bus &tb) :

		Clock(&Clk), Reset(&Rst), EnableA(&EA), EnableB(&EB), EnableP(&EP), EnableM(&EM), EnableN(&EN), EnableR(&ER), Selecl(&Sel), twobit(&tb)
	{
		Nstate = 0;
		Pstate = 0;

	}

	void evl(bus *twobit)
	{
		*EnableA = "0";
		*EnableB = "0";
		*EnableP = "0";
		*EnableM = "0";
		*EnableN = "0";
		*EnableR = "0";
		*Selecl = "xx";
		switch (Pstate) {
		case 0 : //wait for go
		case 1 ://
		case 2:
		case 3:
		case 4:


		}

	}

};

class Top
{

};

string toBinary(int n)
{
	string r;
	while (n != 0) { r = (n % 2 == 0 ? "0" : "1") + r; n /= 2; }
	return r;
}

