#include<stdio.h>
#include<stdlib.h>
#include<assert.h>


void CodeCount(char *Path) {
	FILE *file = fopen(Path, "r");
	if (file == NULL) {
		printf("��ʧ��");
		exit(0);
	}
	char s;
	int count = 0;
	s = fgetc(file);
	while (s != EOF){
		s = fgetc(file);
		if (s != ' ' && s != '\n' && s != '\t') 
			count++;
	}
	printf("�ַ����ǣ�%d", count);
	fclose(file);
}

void WordCount(char *Path) {
	FILE *file = fopen(Path, "r");
	if (file == NULL) {
		printf("��ʧ��");
		exit(0);
	}
	int count = 0;
	int judge = 0;
	char s;
	while ((s=fgetc(file))!= EOF) {
		if ((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z')) {
			if (judge == 0)
				count++;
			judge = 1;
		}
		else
			judge = 0;
	}
	printf("�������ǣ�%d", count);
	fclose(file);
}

void LineCount(char *Path) {
	FILE *file = fopen(Path, "r");
	if (file == NULL) {
		printf("��ʧ��");
		exit(0);
	}
	int count = 0;
	char *s = (char *)malloc(100 * sizeof(char));
	while ((s = fgets(s, 100, file)) != NULL) {
		count++;
	}
	printf("�����ǣ�%d", count);
	free(s);
	fclose(file);
}

//ע���С����С�������
void Lines(char *Path) {
	FILE *file = fopen(Path, "r");
	assert(file != NULL);
	int sum = 0, blank = 0, note = 0, code = 0;
	//sum����������blank�ǿհ��У�note��ע���У�code�Ǵ�����
	int judge_note = 0, judge_code = 0;                             
	//judge_code�ж��Ƿ��Ǵ����У�judge_note�ж��Ƿ�Ϊ/**/�����ע��
	char *s = (char*)malloc(100 * sizeof(char)); 
	while (fgets(s, 100, file) != NULL) {
		for (int i = 0; s[i] != '\0'; i++) {
			if (((s[i] >= 'a'&& s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')) && judge_note == 0)
			{
				if (judge_code == 0) {
					code++;
					judge_code = 1;
				}	
			}
			if (s[i] == '/' && s[i + 1] == '/' && judge_code == 0 && judge_note == 0) {
				note++;
				break;
			}
			if (s[i] == '/' && s[i + 1] == '*' && judge_code == 0) {
				judge_note = 1;
				if (judge_code) 
					note--;
			}//�����к�ע�Ͳ���
			if (s[i] == '*' && s[i + 1] == '/') {
				judge_note = 0;
				if(s[i+2] == '\n')
					note++;
			}
		}
		if (judge_note) {
			note++;
		}//���ע�������У�ÿ�м�һ
		sum++;
		judge_code = 0;
		//��������,����judge_note�����������Բ�����
	}
	free(s);
	fclose(file);
	blank = sum - note - code;
	printf("�����У�%d ע���У�%d ���У�%d ", code, note, blank);
}


int main(int argc, char *argv[]) {
	/*������ԭ������û�в���������Ҫ��cmd������WordCount�����Ը������*/
	char *s = (char *)malloc(2 * sizeof(char));
	char cmd;
	FILE * file = NULL;
	if (argv[2] == NULL || argv[1] == NULL)
		exit(1);
	file = fopen(argv[2], "r");
	if (file != NULL)
	{
		s = argv[1];
		cmd = s[1];
	}
	
	switch (cmd)
	{
	case 'c':CodeCount(argv[2]); break;
	case 'w':WordCount(argv[2]); break;
	case 'l':LineCount(argv[2]); break;
	case 'a':Lines(argv[2]); break;
	default:
		break;
	}
	fclose(file);
	return 0;
}


