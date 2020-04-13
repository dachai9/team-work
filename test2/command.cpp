#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<windows.h>
#include<time.h>
#include "team-project.cpp"

//exe -n 10 -r 10
//exe -e txt -a txt

int main(int argc, char *argv[]) {
    printf("��������%d\n", argc);
    char **func;
    int k=0;
    int amount = 0;
    int limit = 0;
    char *txt_e;
    char *txt_a;

    if(argc != 5) {
        printf("�����������ȷ��\n");
        return 0;
    }

    if(argv[1][1] == 'n') {
        for(int i=2; i<argc; i++) {
            if(i == 2){
                for(int j=0; argv[i][j]!='\0'; j++) {
                    if(argv[i][j] < '0' || argv[i][j] > '9') {
                        printf("����ڶ����������ԣ���\n");
                        return 0;
                    }
                    amount *= 10;
                    amount += argv[i][j]-'0';
                }
            }
            if(i==3 && argv[i][1] != 'r') {
                printf("�����������������\n");
                return 0;
            }
            if(i == 4) {
                for(int j=0; argv[i][j]!='\0'; j++) {
                    if(argv[i][j] < '0' || argv[i][j] > '9') {
                        printf("������ĸ��������ԣ���\n");
                        return 0;
                    }
                    limit *= 10;
                    limit += argv[i][j]-'0';
                }
            }
        }
        buildnum(amount, limit);
    } else if(argv[1][1] == 'e') {
        for(int i=2; i<argc; i++) {
            if(i == 2){
                txt_e = argv[2];
            }
            if(i==3 && argv[i][1] != 'a') {
                printf("�����������������\n");
                return 0;
            }
            if(i == 4) {
                txt_a = argv[4];
            }
        }
        Check(txt_e, txt_a);
    }
    return 0;
}



