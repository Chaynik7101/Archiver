#include "Bits.h"

Bits::Bits(const std::string& inp_NofFile, const packun& Pack_UnPack)
{
	OutByte = 0;
	length = 0;
	pos = nullptr;
	pos_inF = 0;
	std::string part_1;
	if(Pack_UnPack == Pack){
		if(inp_NofFile.find('.') != std::string::npos){
			int i = 0;
			for(; inp_NofFile[i] != '.'; i++);
			part_1 = inp_NofFile.substr(0,i);
		} else part_1 = inp_NofFile;
		outp_NameF = part_1 + ".arch";
	} else {
		int i = 0;
		for(; inp_NofFile[i] != '.'; i++);
		part_1 = inp_NofFile.substr(0,i);
		outp_NameF = part_1 + "_unzip";
	}
}

Bits::Bits(const std::string& inp_str)
{
	OutByte = 0;
	length = 0;
	pos = nullptr;
	pos_inF = 0;
	for(int i = 0; i < 6; i++) outp_NameF.push_back(inp_str[i]);
	outp_NameF += ".arch";
}

Bits::Bits(const Bits& b)
{
	OutByte = b.OutByte;
	length = b.length;
	pos = b.pos;
	outp_NameF = b.outp_NameF;
}

Bits& Bits::operator = (const Bits& b)
{
	OutByte = b.OutByte;
	length = b.length;
	pos = b.pos;
	outp_NameF = b.outp_NameF;
	return *this;
}

void Bits::Record_char(const Code& Coded_ch)
{
	int len = Coded_ch.length;
	int code = Coded_ch.code;
	std::ofstream fout(outp_NameF,std::ios::app);
	while(len > 0){
		while((length < 8) && (len > 0)){
			OutByte <<= 1;
			OutByte |= (code & 1);
			code >>= 1;
			len--;
			length++;
		}
		if(length == 8){
			fout << OutByte;
			OutByte = 0;
			length = 0;
		}
	}
	fout.close();
}

bool Bits::Record_char(const Branch* root, unsigned char* buffer, const int file_size, const int sizebuf) /////////////////////////
{
	std::ofstream fout(outp_NameF,std::ios::app);
	int i = 0;
	if(!pos) pos = root;
	int buf_i_len = 8;
	while((i < sizebuf) && (buf_i_len > 0)){
		if(pos_inF > file_size - 3){
			if(pos_inF == file_size - 1){
				while((pos->let == -1) && (buf_i_len > 0)){
					if(buffer[i] & 0x80) pos = pos->rb_1;
					else pos = pos->lb_0;
					buffer[i] <<= 1;
					buf_i_len--;
				}
				if((pos->let != -1)){
					fout << static_cast<unsigned char>(pos->let);
					pos = root;
					if(buf_i_len <= 0){
						return true;
					}
				}
			} else if(buffer[i] == '0'){
				return true;
			} else {
				buf_i_len = static_cast<unsigned int>(buffer[i] - '0');
				i++;
				pos_inF++;
			}
		} else {
			while((pos->let == -1) && (buf_i_len > 0)){
				if(buffer[i] & 0x80) pos = pos->rb_1;
				else pos = pos->lb_0;
				buffer[i] <<= 1;
				buf_i_len--;
			}
			if((pos->let != -1)){
				fout << static_cast<unsigned char>(pos->let);
				pos = root;
				if(!buf_i_len){
					i++;
					pos_inF++;
					buf_i_len = 8;
				}
			} else {
				i++;
				pos_inF++;
				buf_i_len = 8;
			}
		}
	}
	fout.close();
	return false;
}

void Bits::Record_lastCh()
{
	std::ofstream fout(outp_NameF,std::ios::app | std::ios::binary);
	OutByte <<= 8 - length;
	fout << length;
	fout << OutByte;
	fout.close();
}

Code* Bits::binsch_code(Code* ArrC, int left, int right, const Code& key)
{
	int index = (left + right) / 2;
	Code middle = ArrC[index];
	if(left == index){
		if(ArrC[left+1] == key) return ArrC + (left + 1);
		else if(ArrC[left] == key) return ArrC + (left);
		else return nullptr;
	}
	if(middle == key) return ArrC + index;
	else if (middle > key) return binsch_code(ArrC,left,index,key);
	else return binsch_code(ArrC,index,right,key);
}

std::string Bits::get_res_nF()
{
	return outp_NameF;
}

int Bits::get_pos_inF()
{
	return pos_inF;
}

Bits::~Bits(void){}