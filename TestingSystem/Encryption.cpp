#include "stdafx.h"
#include "Encryption.h"


CEncryption::CEncryption()
{
}


CEncryption::~CEncryption()
{
}


unsigned int CEncryption::chtoint(char ch[4])
{
	unsigned int temp;
	unsigned int intt[4];
	for (int i = 0; i<4; i++)
	{
		int flag = (ch[i] >> 7) & 0x1;
		if (flag == 1)
			intt[i] = 128 + (ch[i] & 0x7f);
		else
			intt[i] = ch[i];
	}
	temp = 256 * 256 * 256 * intt[0] + 256 * 256 * intt[1] + 256 * intt[2] + intt[3];
	return temp;
}


void CEncryption::Ckey(unsigned int x[2], unsigned int y[16][2])///////////密钥生成
{
	unsigned int i;
	PC1(x);
	for (i = 0; i<16; i++)
	{
		x[0] = LTr(i + 1, x[0]);
		x[1] = LTr(i + 1, x[1]);
		y[i][0] = x[0];
		y[i][1] = x[1];
		PC2(y[i]);
	}
}


void CEncryption::cryption(unsigned int text[2], unsigned int key[16][2], int flag)
{
	unsigned int temp;
	unsigned int ex[2];
	int i = 0;
	if (flag == 1)
		i = 15;
	for (;;)
	{

		temp = text[1];
		Extend(text[1], ex);
		ex[0] = ex[0] ^ key[i][0];
		ex[1] = ex[1] ^ key[i][1];
		text[1] = Sbox(ex);
		text[1] = PM(text[1]);
		text[1] = text[0] ^ text[1];
		text[0] = temp;
		if (flag == 0)
		{
			i++;
			if (i == 16)
				break;
		}
		else
		{
			i--;
			if (i<0)
				break;
		}

	}

	temp = text[1];
	text[1] = text[0];
	text[0] = temp;
}


void CEncryption::Extend(unsigned int x, unsigned int y[2])/////////////扩展换算
{
	unsigned int i;
	unsigned int temp = 0;
	y[0] = 0;
	y[1] = 0;
	for (i = 0; i<8; i++)
	{
		temp = (x >> (8 * (7 - i) + 7)) & 0x1;
		temp = (temp << 4) + ((x >> (8 * (7 - i))) & 0xf);
		temp = temp * 2 + ((x >> (8 * (7 - i) + 7)) & 0x1);
		if (i<4)
			y[0] = (y[0] << 6) + temp;
		else
			y[1] = (y[1] << 6) + temp;
	}
}


int CEncryption::filecryption(char *fname, char ch[9], int crypflag)
{
	FILE *fp;
	char ckey1[4] = { '\0','\0','\0','\0' }, ckey2[4] = { '\0','\0','\0','\0' };
	unsigned keyn[2];
	unsigned skeyn[16][2];
	char text1[4], text2[4];
	unsigned int textn[2];
	ckey1[0] = ch[0];     ckey1[1] = ch[1];     ckey1[2] = ch[2];		ckey1[3] = ch[3];
	ckey2[0] = ch[4];		ckey2[1] = ch[5];		ckey2[2] = ch[6];		ckey2[3] = ch[7];
	keyn[0] = chtoint(ckey1);
	keyn[1] = chtoint(ckey2);
	Ckey(keyn, skeyn);
	fp = fopen(fname, "rb+");
	if (fp == NULL)
	{
		return 2;
	}
	int ftel = fseek(fp, 0, 2);
	ftel = ftell(fp);
	ftel = ftel % 8;
	for (int j = ftel; 0<j&&j <= 7; j++)
	{
		fputc(' ', fp);
	}
	char filetemp[20000];
	int filelength = ftell(fp);
	rewind(fp);
	fread(filetemp, filelength, 1, fp);
	int endflag = 0;
	for (; endflag + 8 <= filelength;)
	{

		text1[0] = filetemp[endflag + 0];		text1[1] = filetemp[endflag + 1];		text1[2] = filetemp[endflag + 2];		text1[3] = filetemp[endflag + 3];
		text2[0] = filetemp[endflag + 4];		text2[1] = filetemp[endflag + 5];		text2[2] = filetemp[endflag + 6];		text2[3] = filetemp[endflag + 7];
		textn[0] = chtoint(text1);
		textn[1] = chtoint(text2);
		cryption(textn, skeyn, crypflag);
		inttoch(textn[0], text1);
		inttoch(textn[1], text2);
		filetemp[endflag + 0] = text1[0];		filetemp[endflag + 1] = text1[1];		filetemp[endflag + 2] = text1[2];		filetemp[endflag + 3] = text1[3];
		filetemp[endflag + 4] = text2[0];		filetemp[endflag + 5] = text2[1];       filetemp[endflag + 6] = text2[2];		filetemp[endflag + 7] = text2[3];
		endflag += 8;
	}
	rewind(fp);
	fwrite(filetemp, filelength, 1, fp);
	fclose(fp);
	return 1;
}


void CEncryption::inttoch(_int64 temp, char ch[4])
{
	ch[0] = temp / (256 * 256 * 256);
	ch[1] = (temp - 256 * 256 * 256 * ch[0]) / (256 * 256);
	ch[2] = (temp - 256 * 256 * 256 * ch[0] - 256 * 256 * ch[1]) / 256;
	ch[3] = temp - 256 * 256 * 256 * ch[0] - 256 * 256 * ch[1] - 256 * ch[2];
}


void CEncryption::IP_PM(unsigned int x[2])
{
	unsigned temp[2], flag;
	temp[1] = x[1];
	temp[0] = x[0];
	x[0] = 0;
	x[1] = 0;
	for (int i = 0; i<64; i++)
	{
		if (i<32)
		{
			if (IP_PERMUTE[i]>32)
			{
				flag = 64 - IP_PERMUTE[i];
				flag = temp[1] >> flag;
				flag = flag & 0x1;
				x[0] = 2 * x[0] + flag;
			}
			else
			{
				flag = 32 - IP_PERMUTE[i];
				flag = temp[0] >> flag;
				flag = flag & 0x1;
				x[0] = 2 * x[0] + flag;
			}
		}
		else
		{
			if (IP_PERMUTE[i]>32)
			{
				flag = 64 - IP_PERMUTE[i];
				flag = temp[1] >> flag;
				flag = flag & 0x1;
				x[1] = 2 * x[1] + flag;
			}
			else
			{
				flag = 32 - IP_PERMUTE[i];
				flag = temp[0] >> flag;
				flag = flag & 0x1;
				x[1] = 2 * x[1] + flag;
			}
		}
	}
}


void CEncryption::IP_PM1(unsigned int x[2])
{
	unsigned int temp[2], flag;
	temp[1] = x[1];
	temp[0] = x[0];
	x[0] = 0;
	x[1] = 0;
	for (int i = 0; i<64; i++)
	{
		if (i<32)
		{
			if (IP_PERMUTE_1[i]>32)
			{
				flag = 64 - IP_PERMUTE_1[i];
				flag = temp[1] >> flag;
				flag = flag & 0x1;
				x[0] = 2 * x[0] + flag;
			}
			else
			{
				flag = 32 - IP_PERMUTE_1[i];
				flag = temp[0] >> flag;
				flag = flag & 0x1;
				x[0] = 2 * x[0] + flag;
			}
		}
		else
		{
			if (IP_PERMUTE_1[i]>32)
			{
				flag = 64 - IP_PERMUTE_1[i];
				flag = temp[1] >> flag;
				flag = flag & 0x1;
				x[1] = 2 * x[1] + flag;
			}
			else
			{
				flag = 32 - IP_PERMUTE_1[i];
				flag = temp[0] >> flag;
				flag = flag & 0x1;
				x[1] = 2 * x[1] + flag;
			}
		}
	}
}


unsigned int CEncryption::LTr(unsigned int x, unsigned int y)////////////// 28位密钥 移位
{
	unsigned int temp;
	unsigned int flag;
	flag = LTranslocation[x - 1];
	temp = y >> (28 - flag);
	if (flag = 1)
		temp = temp & 0x1;
	else
		temp = temp & 0x3;
	y = (y << flag) + temp;
	return y;
}


void CEncryption::PC1(unsigned int x[2])////////////// 密钥置换 64位到56位
{
	unsigned int temp[2], flag;
	temp[1] = x[1];
	temp[0] = x[0];
	x[0] = 0;
	x[1] = 0;
	for (int i = 0; i<56; i++)
	{
		if (i<28)
		{
			if (PC_PERMUTE1[i]>32)
			{
				flag = 64 - PC_PERMUTE1[i];
				flag = temp[1] >> flag;
				flag = flag & 0x1;
				x[0] = 2 * x[0] + flag;
			}
			else
			{
				flag = 32 - PC_PERMUTE1[i];
				flag = temp[0] >> flag;
				flag = flag & 0x1;
				x[0] = 2 * x[0] + flag;
			}
		}
		else
		{
			if (PC_PERMUTE1[i]>32)
			{
				flag = 64 - PC_PERMUTE1[i];
				flag = temp[1] >> flag;
				flag = flag & 0x1;
				x[1] = 2 * x[1] + flag;
			}
			else
			{
				flag = 32 - IP_PERMUTE_1[i];
				flag = temp[0] >> flag;
				flag = flag & 0x1;
				x[1] = 2 * x[1] + flag;
			}
		}
	}
}


void CEncryption::PC2(unsigned x[2])//////////// 密钥置换 56位到 48位
{
	unsigned int temp[2], flag;
	temp[1] = x[1];
	temp[0] = x[0];
	x[0] = 0;
	x[1] = 0;
	for (int i = 0; i<48; i++)
	{
		if (i<24)
		{
			if (PC_PERMUTE2[i]>28)
			{
				flag = 56 - PC_PERMUTE2[i];
				flag = temp[1] >> flag;
				flag = flag & 0x1;
				x[0] = 2 * x[0] + flag;
			}
			else
			{
				flag = 28 - PC_PERMUTE2[i];
				flag = temp[0] >> flag;
				flag = flag & 0x1;
				x[0] = 2 * x[0] + flag;
			}
		}
		else
		{
			if (PC_PERMUTE2[i]>28)
			{
				flag = 56 - PC_PERMUTE2[i];
				flag = temp[1] >> flag;
				flag = flag & 0x1;
				x[1] = 2 * x[1] + flag;
			}
			else
			{
				flag = 28 - PC_PERMUTE2[i];
				flag = temp[0] >> flag;
				flag = flag & 0x1;
				x[1] = 2 * x[1] + flag;
			}
		}
	}
}


unsigned int CEncryption::PM(unsigned int x)    /////////////32位置换
{
	unsigned int temp, flag;
	unsigned int i;
	temp = x;
	x = 0;
	for (i = 0; i<32; i++)
	{
		flag = temp >> P_PERMUTE[i];
		flag = flag & 0x1;
		x = x * 2 + flag;
	}
	return x;
}


unsigned int CEncryption::Sbox(unsigned int x[2])     /////////////////// s 合置换
{
	unsigned int ret = 0;
	unsigned int i, j;
	unsigned int temp = 0, flag = 0;
	for (i = 0, j = 0; i<8; i++)
	{
		if (i >= 4)
			j = 1;
		temp = x[j] >> ((3 - i % 4) * 6);
		flag = temp & 0x3;
		temp = temp >> 2;
		temp = temp & 0xf;
		switch (i)
		{
		case 0:temp = S_BOX1[flag][temp]; break;
		case 1:temp = S_BOX2[flag][temp]; break;
		case 2:temp = S_BOX3[flag][temp]; break;
		case 3:temp = S_BOX4[flag][temp]; break;
		case 4:temp = S_BOX5[flag][temp]; break;
		case 5:temp = S_BOX6[flag][temp]; break;
		case 6:temp = S_BOX7[flag][temp]; break;
		case 7:temp = S_BOX8[flag][temp]; break;
		}
		ret = ret << 4;
		ret += temp;
	}
	return ret;
}
