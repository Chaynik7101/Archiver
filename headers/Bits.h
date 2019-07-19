#pragma once
#include "CodingTree.h"

enum packun {Pack,UnPack};

class Bits
{
	private:
		std::string outp_NameF;
		const Branch* pos;
		unsigned char OutByte;
		int length;
		int pos_inF;
	public:
		Bits(const std::string&,const packun&);
		Bits(const std::string&);
		Bits(const Bits&);
		Bits& operator = (const Bits&);
		void Record_char(const Code&);
		bool Record_char(const Branch*,unsigned char*,const int,const int sizebuf = 100);
		void Record_lastCh();
		int get_pos_inF();
		Code* binsch_code(Code*,int,int,const Code&);
		std::string get_res_nF();
		~Bits(void);
};