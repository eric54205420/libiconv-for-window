#ifndef _H_SIMPLEC_SCICONV
#define _H_SIMPLEC_SCICONV

#include <iconv.h>
#include <stdbool.h>

//
// iconv for window helper
//		by simplec wz
//

//
// si_isutf8 - �жϵ�ǰ�ַ����Ƿ���utf-8����
// in		: �������ַ���
// return	: true��ʾȷʵutf8����, false����
//
extern bool si_isutf8(const char * in);

//
// si_iconv - ���ַ��� in ת��, from �� -> to ��
// in		: ��ת����ַ��� 
// len		: �ַ����鳤��
// from		: ��ʼ�����ַ���
// to		: ת�ɵı����ַ��� 
// rlen		: ����ת�����ַ�������, ����NULL��ʾ����Ҫ
// return	: ����ת���Ĵ�, ��Ҫ�Լ����� 
//
extern char * si_iconv(const char * in, const char * from, const char * to, size_t * rlen);

//
// si_iconv - ���ַ�������in ת��, ����Ƿ���in������. 
// in		: �ַ�����
// from		: ��ʼ�����ַ���
// to		: ת�ɵı����ַ��� 
// return	: void
// 
extern void si_aconv(char in[], const char * from, const char * to);

//
// si_gbktoutf8 - ���ַ�������in, ת��utf8����
// in		: �ַ�����
// len		: �ַ����鳤��
// return	: void
//
extern void si_gbktoutf8(char in[]);

//
// si_utf8togbk - ���ַ�������in, ת��gbk����
// in		: �ַ�����
// len		: �ַ����鳤��
// return	: void
//
extern void si_utf8togbk(char in[]);

#endif