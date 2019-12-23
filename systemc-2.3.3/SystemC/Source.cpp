
#include <systemc.h>

SC_MODULE(dRegisterEn8) {
	sc_in <sc_logic> clk, rst, en;
	sc_in<sc_lv<8>> regin;
	sc_out <sc_lv<8>> regout;

	SC_CTOR(dRegisterEn8)
	{
		SC_METHOD(registering8);
		sensitive << clk << rst;
	}

	void registering8()
	{
		sc_lv<8> temp;
		if (rst == '1')
		{
			for (int i = 0; i <= 8; i++)
				temp[i] = sc_logic(0);
			regout = temp;
		}

		else if ((clk->event) && (clk == '1'))
		{
			if (en == '1') regout = regin;
		}
	}

};

SC_MODULE(MUX4to1) {
	sc_in<sc_lv<8>> M1;
	sc_in<sc_lv<8>> M2;
	sc_in<sc_lv<8>> M3;
	sc_in<sc_lv<8>> M4;
	sc_in<sc_lv<2>> Select;

	sc_out<sc_lv<8>> Output;

	SC_CTOR(MUX4to1) {
		SC_METHOD(Mutuplexing);
		sensitive << Select;
	}

	void Mutuplexing()
	{
		if (Select.read().to_uint() == 00)
			Output.write(M1);
		else if (Select.read().to_uint() == 01)
			Output.write(M2);
		else if (Select.read().to_uint() == 10)
			Output.write(M3);
		else if (Select.read().to_uint() == 11)
			Output.write(M4);
		else Output = "xxxxxxxx";
	}
};

SC_MODULE(CLA8)
{
	sc_in<sc_lv<8>> i1;
	sc_in<sc_lv<8>> i2;
	sc_in<sc_logic> cin;
	sc_out<sc_logic> cout;
	sc_out < sc_lv<8>> Cla_out;

	SC_CTOR(CLA8)
	{
		SC_METHOD(adding);
		sensitive << i1 << i2 << cin;
	}

	void adding()
	{
		sc_lv<9> result;
		result = i1.read().to_uint() + i2.read().to_uint() + cin.read().value();

		Cla_out = result.range(7, 0);
		cout = result[8];
	}

};

SC_MODULE(FlipflopI)
{
	sc_in<sc_logic> D;
	sc_in<sc_logic> clk, rst;
	sc_out<sc_logic> Q;

	SC_CTOR(FlipflopI)
	{
		SC_METHOD(Fliped)
			sensitive << clk << rst;
	};

	void Fliped()
	{
		if (rst == '0')
		{
			Q = sc_logic(0);
		}
		else if ((clk->event) && (clk == '1'))
		{
			Q = D;
		}
	}
};

SC_MODULE(dRegisterEn32) {
	sc_in <sc_logic> clk, rst, en;
	sc_in<sc_lv<32>> regin;
	sc_out <sc_lv<32>> regout;

	SC_CTOR(dRegisterEn32)
	{
		SC_METHOD(registering32);
		sensitive << clk << rst;
	}

	void registering32()
	{
		sc_lv<8> temp;
		if (rst == '1')
		{
			for (int i = 0; i <= 32; i++)
				temp[i] = sc_logic(0);
			regout = temp;
		}

		else if ((clk->event) && (clk == '1'))
		{
			if (en == '1') regout = regin;
		}
	}

};

SC_MODULE(datapath)
{
	//ports
	sc_in<sc_logic> clk, rst;
	sc_in<sc_logic> LdA, LdB, LdR;
	sc_in<sc_logic> Ld0, Ld1, Ld2, Ld3;
	sc_in<sc_lv<32>> Abus, Bbus;
	sc_in<sc_lv<2>> Select;

	sc_out<sc_lv<32>> Resultbus;
	sc_out<sc_logic> cout;

	//Signals
	sc_signal<sc_lv<8>> A0, A1, A2, A3, B0, B1, B2, B3;
	sc_signal<sc_lv<8>> MAout, MBout;
	sc_signal<sc_logic> cin;
	sc_signal<sc_lv<8>> CLA_Out;
	sc_signal<sc_lv<32>> Result;

	//component
	dRegisterEn8* Areg0;
	dRegisterEn8* Areg1;
	dRegisterEn8* Areg2;
	dRegisterEn8* Areg3;
	dRegisterEn8* Breg0;
	dRegisterEn8* Breg1;
	dRegisterEn8* Breg2;
	dRegisterEn8* Breg3;
	MUX4to1* MA;
	MUX4to1* MB;
	CLA8* CLA;
	FlipflopI* FlipFlop;
	dRegisterEn8* RES0;
	dRegisterEn8* RES1;
	dRegisterEn8* RES2;
	dRegisterEn8* RES3;
	dRegisterEn32* ResultREG;

	SC_CTOR(datapath)
	{
		Areg0 = new dRegisterEn8("A0");
		{
			Areg0->clk(clk);
			Areg0->rst(rst);
			Areg0->en(LdA);
			Areg0->regin(Abus.read().range(7, 0));
			Areg0->regout(A0);
		}
		Areg1 = new dRegisterEn8("A1");
		{
			Areg1->clk(clk);
			Areg1->rst(rst);
			Areg1->en(LdA);
			Areg1->regin(Abus.read().range(15, 8));
			Areg1->regout(A1);
		}
		Areg2 = new dRegisterEn8("A2");
		{
			Areg2->clk(clk);
			Areg2->rst(rst);
			Areg2->en(LdA);
			Areg2->regin(Abus.read().range(23, 16));
			Areg2->regout(A2);
		}
		Areg3 = new dRegisterEn8("A3");
		{
			Areg3->clk(clk);
			Areg3->rst(rst);
			Areg3->en(LdA);
			Areg3->regin(Abus.read().range(31, 24));
			Areg3->regout(A3);
		}
		Breg0 = new dRegisterEn8("B0");
		{
			Breg0->clk(clk);
			Breg0->rst(rst);
			Breg0->en(LdB);
			Breg0->regin(Bbus.read().range(7, 0));
			Breg0->regout(B0);
		}
		Breg1 = new dRegisterEn8("B1");
		{
			Breg1->clk(clk);
			Breg1->rst(rst);
			Breg1->en(LdB);
			Breg1->regin(Bbus.read().range(15, 8));
			Breg1->regout(B1);
		}
		Breg2 = new dRegisterEn8("B2");
		{
			Breg2->clk(clk);
			Breg2->rst(rst);
			Breg2->en(LdB);
			Breg2->regin(Bbus.read().range(23, 16));
			Breg2->regout(B2);
		}
		Breg3 = new dRegisterEn8("B3");
		{
			Breg3->clk(clk);
			Breg3->rst(rst);
			Breg3->en(LdB);
			Breg3->regin(Bbus.read().range(31, 24));
			Breg3->regout(B3);
		}
		MA = new MUX4to1("MA");
		{
			MA->M1(A0);
			MA->M2(A1);
			MA->M3(A2);
			MA->M4(A3);
			MA->Select(Select);
			MA->Output(MAout);
		}
		MB = new MUX4to1("MB");
		{
			MA->M1(B0);
			MA->M2(B1);
			MA->M3(B2);
			MA->M4(B3);
			MA->Select(Select);
			MA->Output(MBout);
		}
		CLA = new CLA8("CLA");
		{
			CLA->i1(MAout);
			CLA->i2(MBout);
			CLA->cin(cin);
			CLA->cout(cout);
			CLA->Cla_out(CLA_Out);
		}
		FlipFlop = new FlipflopI("Flip");
		{
			FlipFlop->clk(clk);
			FlipFlop->rst(rst);
			FlipFlop->D(cout);
			FlipFlop->Q(cin);
		}
		RES0 = new dRegisterEn8("RES0");
		{
			RES0->clk(clk);
			RES0->rst(rst);
			RES0->en(Ld0);
			RES0->regin(CLA_Out);
			RES0->regout(Result[7:0]);
		}
		RES1 = new dRegisterEn8("RES1");
		{
			RES1->clk(clk);
			RES1->rst(rst);
			RES1->en(Ld1);
			RES1->regin(CLA_Out);
			RES1->regout(Result[7:0]);
		}
		RES2 = new dRegisterEn8("RES2");
		{
			RES2->clk(clk);
			RES2->rst(rst);
			RES2->en(Ld2);
			RES2->regin(CLA_Out);
			RES2->regout(Result[7:0]);
		}
		RES3 = new dRegisterEn8("RES3");
		{
			RES3->clk(clk);
			RES3->rst(rst);
			RES3->en(Ld0);
			RES3->regin(CLA_Out);
			RES3->regout(Result[7:0]);
		}
		ResultREG = new dRegisterEn32("ResultREG");
		{
			ResultREG->clk(clk);
			ResultREG->rst(rst);
			ResultREG->en(LdR);
			ResultREG->regin(Result);
			ResultREG->regout(Resultbus);
		}
	};


};


