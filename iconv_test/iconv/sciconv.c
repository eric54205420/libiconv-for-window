#include <sciconv.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

//
// si_isutf8 - �жϵ�ǰ�ַ����Ƿ���utf-8����
// in		: �������ַ���
// return	: true��ʾȷʵutf8����, false����
//
bool 
si_isutf8(const char * in) {
	uint8_t bytes = 0, c;		// bytes ��ʾ�����ֽ���, utf-8 [1, 6] �ֽڱ���
	bool isascii = true;

	while ((c = *in++)) {
		if ((c & 0x80)) // ascii �����λΪ0, 0xxx xxxx
			isascii = false;

		// ��������ֽ���, �����ֽ��ײ�
		if (bytes == 0) { 
			if (c >= 0x80) {
				if (c >= 0xFC && c <= 0xFD)
					bytes = 6;
				else if (c >= 0xF8)
					bytes = 5;
				else if (c >= 0xF0)
					bytes = 4;
				else if (c >= 0xE0)
					bytes = 3;
				else if (c >= 0xC0)
					bytes = 2;
				else	// �쳣����ֱ�ӷ���
					return false;
				--bytes;
			}
		}
		else { // ���ֽڵķ����ֽ�, ӦΪ 10xx xxxx
			if ((c & 0xC0) != 0x80)
				return false;
			--bytes;
		}
	}
	// bytes > 0 Υ��utf-8����, isacii == true ��ʾ��ascii����
	return bytes == 0 && !isascii;
}

//
// si_iconv - ���ַ��� in ת��, from �� -> to ��
// in		: ��ת����ַ��� 
// len		: �ַ����鳤��
// from		: ��ʼ�����ַ���
// to		: ת�ɵı����ַ��� 
// rlen		: ����ת�����ַ�������, ����NULL��ʾ����Ҫ
// return	: ����ת���Ĵ�, ��Ҫ�Լ����� 
//
char * 
si_iconv(const char * in, const char * from, const char * to, size_t * rlen) {
	char * buff, * sin, * sout;
	size_t lenin, lenout, len;
	iconv_t ct;

	// ��iconv ת������
	if ((ct = iconv_open(to, from)) == (iconv_t)-1)
		return NULL;
	
	// ��������, buff������������
	len = strlen(in) + 1;
	lenout = len << 1;
	if ((buff = malloc(lenout)) == NULL) {
		iconv_close(ct);
		return NULL;
	}
	sout = buff;
	sin = (char *)in;
	lenin = len + 1;

	// ��ʼת��
	if (iconv(ct, &sin, &lenin, &sout, &lenout) == -1) {
		free(sout);
		iconv_close(ct);
		return NULL;
	}
	iconv_close(ct);

	// ��ʼ���¹����ڴ淵������
	lenout = strlen(buff);
	// �����������ս������
	if (rlen)
		*rlen = lenout;

	// �ڴ���Сһ���ɹ�
	return realloc(buff, lenout + 1);;
}

//
// si_iconv - ���ַ�������in ת��, ����Ƿ���in������. 
// in		: �ַ�����
// from		: ��ʼ�����ַ���
// to		: ת�ɵı����ַ��� 
// return	: void
// 
void 
si_aconv(char in[], const char * from, const char * to) {
	size_t len;
	char * out;
	if (!in || !from || !to)
		return;

	out = si_iconv(in, from, to, &len);
	if (NULL == out)
		return;

	// ��ʼ�������ݹ���
	memcpy(in, out, len);
	free(out);
}

//
// si_gbktoutf8 - ���ַ�������in, ת��utf8����
// in		: �ַ�����
// return	: void
//
inline void si_gbktoutf8(char in[]) {
	si_aconv(in, "gbk", "utf-8");
}

//
// si_utf8togbk - ���ַ�������in, ת��gbk����
// in		: �ַ�����
// return	: void
//
inline void si_utf8togbk(char in[]) {
	si_aconv(in, "utf-8", "gbk");
}