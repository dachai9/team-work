#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<windows.h>
#include<time.h>
#include "zhan.cpp"

#define MAX 100


char *getSignal() {
    int opnum = 0;
    char *optor;
    //���������
    //srand((unsigned)time(NULL));
    opnum = rand() % 4;
    switch (opnum) {
    case 0:
        optor = "+";
        break;
    case 1:
        optor = "-";
        break;
    case 2:
        optor = "*";
        break;
    case 3:
        optor = "/";
        break;
    default:
        break;
    }
    return optor;
}

char *getzhenRandom(int range) {
    int vary;
    char *svary;
    //srand((unsigned)time(NULL));
    vary = rand() % range + 1;
    itoa(vary, svary, 10);

    return svary;
}

char *getfenRandom(int range) {
    char *a;
    memset(a, 0, sizeof(a));
    int md1, md2, num1, num2;
    do {
        // srand((unsigned)time(NULL));
        num2 = rand() % range + 1;//��ĸ
        // srand((unsigned)time(NULL));
        num1 = rand() % range*num2 + 1;//����
        while(num2 == 0) {
            // srand((unsigned)time(NULL));
            num2 = rand() % range +1;
        }
        // ǰ��Ĵ�����
        md1 = num1/num2;

        // �����ķ���
        md2 = num1%num2;
    } while(md2 == 0);

    char smd1[100] = {};
    char smd2[100] = {};
    char snum2[100] = {};
    itoa(md1, smd1, 10);
    itoa(md2, smd2, 10);
    itoa(num2, snum2, 10);
    // ���ǰ��Ĵ���������0�Ͳ�Ҫ��ʾ��'��
    if(md1 != 0) {
        strcat(a, smd1);
        strcat(a, "'");
    }
    strcat(a, smd2);
    strcat(a, "/");
    strcat(a, snum2);
    return a;
}

char *getRandom(int range) {
    int flag;
    char svary[10];
    // srand((unsigned)time(NULL));
    flag = rand() % 2;  //�Ƿ����ɷ���
//    printf("flag = %d\n", flag);
    if(flag == 1) {
        return getzhenRandom(range);
    } else {
        return getfenRandom(range);
    }
}

int buildnum(int num, int range) {
//    int num = 0;      //����
//    int range = 0;    //��Χ
    int num2 = 1;
    char *svary1, *svary2, *svary3, *svary4;
    char s1[100]= {},s2[100]= {}, s3[100]= {};
    char a[100] = {};
    char b[20] = {};

    FILE *fp;
    fp = fopen("Exercises.txt", "w");
    if(fp == NULL) {
        printf("Exercises.txt �򲻿���");
        return 0;
    }
    // ���ԭ���ļ�
    FILE *fpan;
    if((fpan = fopen("Answers.txt", "w")) == NULL) {
        printf("��Answers.txtʧ��!\n");
    }
//    printf("��ճɹ���\n");
    fclose(fpan);

    for(int i=1; i<=num; i++) {
//        printf("\n%d. ", i);

        //������������
        // srand((unsigned)time(NULL));
        num2 = rand() % 3 + 1;
//        num2 = 3;
//        printf("�����������%d\n",num2);
        if(num2 == 1) {
            svary1 = getRandom(range);
            strcpy(s1, svary1);

            char *optor1 = getSignal();
            svary2 = getRandom(range);

            memset(a, 0, sizeof(a));
            constring(a, s1, a);
            constring(a, " ", a);
            constring(a, optor1, a);
            constring(a, " ", a);
            constring(a, svary2, a);
            constring(a, "#", a);

            if(Countarray(a, b) == -1) {
                i--;
                continue;

            }
//            printf("%d. ", i);

            if(optor1 == "/") {
                optor1 = "��";
            }
//            printf("%s %s %s =\n", s1, optor1, svary2);
            fprintf(fp, "%d%s %s %s %s =\n", i, ".", s1, optor1, svary2);
        }
        if(num2==2) {
            int flag;
            //  srand((unsigned)time(NULL));
            flag = rand() % 3; // �Ƿ���������
//            printf("����λ�ã�%d\n", flag);

            svary1=getRandom(range);
            strcpy(s1, svary1); // ��һ������

            char *optor1 = getSignal(); // ��һ�������
//            printf("%s\n",optor1);
            svary2 = getRandom(range);
            strcpy(s2,svary2); // �ڶ�������

            char *optor2= getSignal(); // �ڶ��������
//            printf("%s\n",optor1);
//            printf("%s\n",optor2);
            svary3=getRandom(range); // ����������

            memset(a, 0, sizeof(a)); // ��ʼ��a����

            // flag==1��(a+b)+c
            // flag==2��a+(b+c)
            if(flag == 1) {
                constring(a, "(", a);
            }
            constring(a, s1, a);
            constring(a, " ", a);
            constring(a, optor1, a);
            constring(a, " ", a);
            if(flag == 2) {
                constring(a, "(", a);
            }
            constring(a, s2, a);
            if(flag == 1) {
                constring(a, ")", a);
            }
            constring(a, " ", a);
            constring(a, optor2, a);
            constring(a, " ", a);
            constring(a, svary3, a);
            if(flag == 2) {
                constring(a, ")", a);
            }
            constring(a, "#", a);

//            printf("�������ź����ɣ�%s\n", a);
            if(Countarray(a, b) == -1) {
//                printf("���ص���-1\n\n");
                i--;
                continue;
            }

            if(optor1 == "/")
                optor1 = "��";
            if(optor2 == "/")
                optor2 = "��";
//            printf("(������)���ɡº�%s %s %s %s %s =\n", s1, optor1, s2,optor2,svary3);
            if(flag == 1) {
                fprintf(fp, "%d%s %s%s %s %s%s %s %s =\n", i, ".", "(", s1, optor1, s2, ")", optor2, svary3);
            } else if(flag == 2) {
                fprintf(fp, "%d%s %s %s %s%s %s %s%s =\n", i, ".", s1, optor1, "(", s2, optor2, svary3, ")");
            } else {
                fprintf(fp, "%d%s %s %s %s %s %s =\n", i, ".", s1, optor1, s2, optor2, svary3);
            }
        }
        if(num2 == 3) {
            int flag;
            //  srand((unsigned)time(NULL));
            flag = rand() % 5 + 1; // �Ƿ���������
//            printf("����λ�ã�%d\n", flag);
            svary1=getRandom(range);
            strcpy(s1, svary1); // ��һ������

            char *optor1 = getSignal();
//            printf("optor1 = %s\n",optor1); // ��һ�������

            svary2 = getRandom(range);
            strcpy(s2,svary2); // �ڶ�������

            char *optor2= getSignal();
//            printf("optor2 = %s\n",optor2); // �ڶ��������

            svary3=getRandom(range); // ����������
            strcpy(s3, svary3);

            char *optor3= getSignal();
//            printf("optor3 = %s\n",optor3); // �����������

            svary4=getRandom(range); // ���ĸ�����

            memset(a, 0, sizeof(a)); // ��ʼ��a����
            // printf("1\n");

            // flag==1: (a+b)+c+d
            // flag==2: a+(b+c)+d
            // flag==3: a+b+(c+d)
            // flag==4: (a+b+c)+d
            // flag==5: a+(b+c+d)
            if(flag == 1 || flag == 4) {
                constring(a, "(", a);
            }
            constring(a, s1, a);
            constring(a, " ", a);
            constring(a, optor1, a);
            constring(a, " ", a);
            if(flag == 2 || flag == 5) {
                constring(a, "(", a);
            }
            constring(a, s2, a);
            if(flag == 1) {
                constring(a, ")", a);
            }
            constring(a, " ", a);
            constring(a, optor2, a);
            constring(a, " ", a);
            if(flag == 3) {
                constring(a, "(", a);
            }
            constring(a, s3, a);
            if(flag == 2 || flag == 4) {
                constring(a, ")", a);
            }
            constring(a, " ", a);
            constring(a, optor3, a);
            constring(a, " ", a);
            constring(a, svary4, a);
            if(flag == 3 || flag == 5) {
                constring(a, ")", a);
            }
            constring(a, "#", a);

//            printf("�������ź����ɣ�%s\n", a);
            if(Countarray(a, b) == -1) {
//                printf("���ص���-1\n\n");
                i--;
                continue;
            }
            //��/ת��Ϊ��
            if(optor1 == "/")
                optor1 = "��";
            if(optor2 == "/")
                optor2 = "��";
            if(optor3 == "/")
                optor3 = "��";

//            printf("(������)���ɡº�%s %s %s %s %s %s %s=\n", s1, optor1, s2, optor2, s3, optor3, svary4);
            if(flag == 1) {
                fprintf(fp, "%d%s %s%s %s %s%s %s %s %s %s =\n", i, ".", "(", s1, optor1, s2, ")", optor2, s3, optor3, svary4);
            } else if(flag == 2) {
                fprintf(fp, "%d%s %s %s %s%s %s %s%s %s %s =\n", i, ".", s1, optor1, "(", s2, optor2, s3, ")", optor3, svary4);
            } else if(flag == 3) {
                fprintf(fp, "%d%s %s %s %s %s %s%s %s %s%s =\n", i, ".", s1, optor1, s2, optor2, "(", s3, optor3, svary4, ")");
            } else if(flag == 4) {
                fprintf(fp, "%d%s %s%s %s %s %s %s%s %s %s =\n", i, ".", "(", s1, optor1, s2, optor2, s3, ")", optor3, svary4);
            } else if(flag == 5) {
                fprintf(fp, "%d%s %s %s %s%s %s %s %s %s%s =\n", i, ".", s1, optor1, "(", s2, optor2, s3, optor3, svary4, ")");
            } else {
                fprintf(fp, "%d%s %s %s %s %s %s %s %s=\n", i, ".", s1, optor1, s2, optor2, s3, optor3, svary4);
            }

        }
//        printf("���ɳɹ���\n");
        FILE *fp_a;
        if((fp_a = fopen("Answers.txt", "a+")) == NULL) {
            printf("��Answers.txtʧ��!\n");
        }
        fprintf(fp_a, "%s\n", b);
        memset(b, 0, sizeof(b));
        fclose(fp_a);
    }
    fclose(fp);
    printf("��Ŀд��Exercises.txt�ļ��ɹ���\n");
    printf("��д��Answers.txt�ļ��ɹ���\n");
//    printf("�ϴ��ɹ���\n");
    return 0;
}

void Check(char *exer, char *answer) {
    printf("������ļ�����%s  %s\n", exer, answer);
    FILE *fp_e, *fp_a, *fp_c, *fp_r, *fp_w;
    fp_e = fopen(exer, "r");
    fp_a = fopen(answer, "r");
    fp_c = fopen("Grade.txt", "w+");
    fp_r = fopen("Right.txt", "w+");
    fp_w = fopen("Wrong.txt", "w+");

    if(fp_e == NULL || fp_a == NULL || fp_c == NULL || fp_r == NULL || fp_w == NULL) {
        printf("��ȡ�ļ�ʧ�ܣ�\n");
        return ;
    }
    char a[50]; // ��ȡ��Ŀ
    char a_b[50];
    char b[50]; // ��ȡ��ȷ��
    memset(a,0,sizeof(a));
    memset(a_b,0,sizeof(a_b));
    memset(b,0,sizeof(b));
    char getc_r, getc_w;
    int i=0, r_num=0, w_num=0;

    while(!feof(fp_e)){
        i++;
        if(Expression(a, fp_e, a_b) == -1) break;
        fscanf(fp_a,"%s",b);
        if(strcmp(a_b, b) == 0) {
            r_num++;
            fprintf(fp_r, ",%d", i);
        }
        else {
            w_num++;
            fprintf(fp_w, ",%d", i);
        }
        memset(a,0,sizeof(a));
        memset(a_b,0,sizeof(a_b));
        memset(b,0,sizeof(b));
    }
    // д���ļ�
    rewind(fp_r);
    rewind(fp_w);
    getc_r = fgetc(fp_r);
    getc_w = fgetc(fp_w);

    fprintf(fp_c, "%s%d%s", "Correct: ", r_num, "(");
    while(getc_r != EOF && getc_r != ' ') {
        if(getc_r == ' ') break;
        getc_r = fgetc(fp_r);
        fprintf(fp_c, "%c", getc_r);
//        if(getc_r == ' ') break;
    }
    fprintf(fp_c, "%s%s%s%d%s", ")", "\n", "Wrong: ", w_num, "(");
//        fscanf(fp_w, "%s", gets_w);
    while(getc_w != EOF && getc_w != ' ') {
        if(getc_w == ' ') break;
        getc_w = fgetc(fp_w);
        fprintf(fp_c, "%c", getc_w);
//        if(getc_w == ' ') break;
    }
    fprintf(fp_c, "%s", ")");

    fclose(fp_a);
    fclose(fp_e);
    fclose(fp_r);
    fclose(fp_w);
    if(remove("Right.txt") == -1) {
        printf("ɾ��Right.txt�ļ�ʧ�ܣ�\n");
    }
    if(remove("Wrong.txt") == -1) {
        printf("ɾ��Wrong.txt�ļ�ʧ�ܣ�\n");
    }
    printf("У�Խ���!!!\n");
    printf("У�Խ������Grade.txt�ļ��ɹ���\n");
}






