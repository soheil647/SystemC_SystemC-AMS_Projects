#include <systemc.h>

template<class T>
class put_if : virtual public sc_interface
{
public:
	virtual void put(int initiator, int target, T data);
};

template<class T>
class get_if : virtual public sc_interface
{
public:
	virtual void get(int &intiator, int target, T data);
};

template<class T>
class Router : public put_if<T>, public get_if<T>
{
	int goingTo, comingFrom;
	T dataPlaced[4][32];

	sc_event dataAvaiable[4];
	sc_event dataReceived[4];

	sc_mutex busBusy;

public:
	Router() : goingTo(-1), comingFrom(-1) {};
	~Router() {};

	void put(int initiator, int target, T data[4][8])
	{
		busBusy.lock();
		comingFrom = initiator;
		goingTo = target;

		int i;
		int z =0;
		while(z<=3)
		{
			if (z == 3)
			{
				wait(dataReceived[0], dataReceived[1], dataReceived[2], dataReceived[3]);
				z = z - 1;
			}

				i = 0;
				for (int j = 0; j < 32; j++)
				{
					dataPlaced[z][j] = data[i][j%8];
					if (j % 8 == 7) i++;
				}
				z++;
				dataAvaiable[target].notify();
			
		}
	}

};