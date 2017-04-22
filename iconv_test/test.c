#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sciconv.h>

#define _INT_STR	(35)
#define _STR_NAME	"name.data"

//
// ���� libiconv.lib ���ʹ��
// 
int main(void) {

	char name[_INT_STR] = "��־ - simplec";
	printf("[%s] is utf8 = %d.\n", name, si_isutf8(name));
	si_gbktoutf8(name);
	printf("[%s] is utf8 = %d.\n", name, si_isutf8(name));

	// ����ַ������ı���, ͨ��UTF-8�ı��鿴������ʽ
	FILE * txt = fopen(_STR_NAME, "wb");
	if (NULL == txt) {
		fprintf(stderr, "fopen " _STR_NAME " wb is error!");
		exit(EXIT_FAILURE);
	}
	// ���ｫname����д�뵽�ļ���
	fwrite(name, sizeof(char), _INT_STR, txt);
	fclose(txt);

	puts(_STR_NAME " write is success!");

	return EXIT_SUCCESS;
}