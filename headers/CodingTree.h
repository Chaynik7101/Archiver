#pragma once
#include <queue>
#include <string>
#include <fstream>
#include <algorithm>

class Branch
{
	public:
		Branch(void);
		int let;
		int freq;
		Branch* lb_0;
		Branch* rb_1;
		bool operator > (const Branch&) const;
		bool operator < (const Branch&) const;
		~Branch(void);
};

class Branch_ptr_compare
{
	public:
		bool operator () (const Branch*,const Branch*) const;
};

class Code
{
	public:
		Code(void);
		int let;
		unsigned int code;
		int length;
		int freq;
		bool operator < (const Code&) const;
		bool operator > (const Code&) const;
		bool operator == (const Code&) const;
		~Code(void);
};

enum inpoutp{File,Console};

class CodingTree
{
	private:
		Branch* root;
		Code* Coding_Table;
		int* Symb_Freq;
		std::string Name_of_File_for_reading;
		std::string Name_of_File_for_recording_Tree;
		std::string s_for_reading;
		inpoutp Mode;
		int num_of_ch;
		int length_of_information;
		void Couting_Symb_Freq();
		void Create_Coding_Tree();
		void record_Tree();
		void readCreate_Tree();
		void sfor_rd_record_inF();
		void Create_Coding_Table(const Branch*, unsigned int, int, int& i);
		void Delete_Tree(Branch*&);
	public:
		CodingTree(const std::string&,const inpoutp = File);
		CodingTree(const std::string&,const std::string&);
		CodingTree(const CodingTree&);
		CodingTree& operator = (const CodingTree&);
		void set_svstr_nF(const std::string&);
		std::string get_record_nF();
		std::string get_read_nF();
		std::string get_Sfor_reading();
		int get_length_inf();
		int get_numb_ch();
		inpoutp get_Mode();
		Code* get_CTable();
		Branch* get_CTree();
		~CodingTree(void);
};