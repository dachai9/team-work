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
    //运算符生成
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
        num2 = rand() % range + 1;//分母
        // srand((unsigned)time(NULL));
        num1 = rand() % range*num2 + 1;//分子
        while(num2 == 0) {
            // srand((unsigned)time(NULL));
            num2 = rand() % range +1;
        }
        // 前面的带分数
        md1 = num1/num2;

        // 处理后的分子
        md2 = num1%num2;
    } while(md2 == 0);

    char smd1[100] = {};
    char smd2[100] = {};
    char snum2[100] = {};
    itoa(md1, smd1, 10);
    itoa(md2, smd2, 10);
    itoa(num2, snum2, 10);
    // 如果前面的带分数等于0就不要显示”'“
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
    flag = rand() % 2;  //是否生成分数
//    printf("flag = %d\n", flag);
    if(flag == 1) {
        return getzhenRandom(range);
    } else {
        return getfenRandom(range);
    }
}

int buildnum(int num, int range) {
//    int num = 0;      //数量
//    int range = 0;    //范围
    int num2 = 1;
    char *svary1, *svary2, *svary3, *svary4;
    char s1[100]= {},s2[100]= {}, s3[100]= {};
    char a[100] = {};
    char b[20] = {};

    FILE *fp;
    fp = fopen("Exercises.txt", "w");
    if(fp == NULL) {
        printf("Exercises.txt 打不开！");
        return 0;
    }
    // 清空原答案文件
    FILE *fpan;
    if((fpan = fopen("Answers.txt", "w")) == NULL) {
        printf("打开Answers.txt失败!\n");
    }
//    printf("清空成功！\n");
    fclose(fpan);

    for(int i=1; i<=num; i++) {
//        printf("\n%d. ", i);

        //随机个数运算符
        // srand((unsigned)time(NULL));
        num2 = rand() % 3 + 1;
//        num2 = 3;
//        printf("运算符个数：%d\n",num2);
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
                optor1 = "÷";
            }
//            printf("%s %s %s =\n", s1, optor1, svary2);
            fprintf(fp, "%d%s %s %s %s =\n", i, ".", s1, optor1, svary2);
        }
        if(num2==2) {
            int flag;
            //  srand((unsigned)time(NULL));
            flag = rand() % 3; // 是否生成括号
//            printf("括号位置：%d\n", flag);

            svary1=getRandom(range);
            strcpy(s1, svary1); // 第一个变量

            char *optor1 = getSignal(); // 第一个运算符
//            printf("%s\n",optor1);
            svary2 = getRandom(range);
            strcpy(s2,svary2); // 第二个变量

            char *optor2= getSignal(); // 第二个运算符
//            printf("%s\n",optor1);
//            printf("%s\n",optor2);
            svary3=getRandom(range); // 第三个变量

            memset(a, 0, sizeof(a)); // 初始化a数组

            // flag==1：(a+b)+c
            // flag==2：a+(b+c)
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

//            printf("加入括号后生成：%s\n", a);
            if(Countarray(a, b) == -1) {
//                printf("返回的是-1\n\n");
                i--;
                continue;
            }

            if(optor1 == "/")
                optor1 = "÷";
            if(optor2 == "/")
                optor2 = "÷";
//            printf("(无括号)化成÷后：%s %s %s %s %s =\n", s1, optor1, s2,optor2,svary3);
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
            flag = rand() % 5 + 1; // 是否生成括号
//            printf("括号位置：%d\n", flag);
            svary1=getRandom(range);
            strcpy(s1, svary1); // 第一个变量

            char *optor1 = getSignal();
//            printf("optor1 = %s\n",optor1); // 第一个运算符

            svary2 = getRandom(range);
            strcpy(s2,svary2); // 第二个变量

            char *optor2= getSignal();
//            printf("optor2 = %s\n",optor2); // 第二个运算符

            svary3=getRandom(range); // 第三个变量
            strcpy(s3, svary3);

            char *optor3= getSignal();
//            printf("optor3 = %s\n",optor3); // 第三个运算符

            svary4=getRandom(range); // 第四个变量

            memset(a, 0, sizeof(a)); // 初始化a数组
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

//            printf("加入括号后生成：%s\n", a);
            if(Countarray(a, b) == -1) {
//                printf("返回的是-1\n\n");
                i--;
                continue;
            }
            //将/转换为÷
            if(optor1 == "/")
                optor1 = "÷";
            if(optor2 == "/")
                optor2 = "÷";
            if(optor3 == "/")
                optor3 = "÷";

//            printf("(无括号)化成÷后：%s %s %s %s %s %s %s=\n", s1, optor1, s2, optor2, s3, optor3, svary4);
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
//        printf("生成成功！\n");
        FILE *fp_a;
        if((fp_a = fopen("Answers.txt", "a+")) == NULL) {
            printf("打开Answers.txt失败!\n");
        }
        fprintf(fp_a, "%s\n", b);
        memset(b, 0, sizeof(b));
        fclose(fp_a);
    }
    fclose(fp);
    printf("题目写入Exercises.txt文件成功！\n");
    printf("答案写入Answers.txt文件成功！\n");
//    printf("上传成功！\n");
    return 0;
}

void Check(char *exer, char *answer) {
    printf("传入的文件名：%s  %s\n", exer, answer);
    FILE *fp_e, *fp_a, *fp_c, *fp_r, *fp_w;
    fp_e = fopen(exer, "r");
    fp_a = fopen(answer, "r");
    fp_c = fopen("Grade.txt", "w+");
    fp_r = fopen("Right.txt", "w+");
    fp_w = fopen("Wrong.txt", "w+");

    if(fp_e == NULL || fp_a == NULL || fp_c == NULL || fp_r == NULL || fp_w == NULL) {
        printf("读取文件失败！\n");
        return ;
    }
    char a[50]; // 获取题目
    char a_b[50];
    char b[50]; // 获取正确答案
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
    // 写入文件
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
        printf("删除Right.txt文件失败！\n");
    }
    if(remove("Wrong.txt") == -1) {
        printf("删除Wrong.txt文件失败！\n");
    }
    printf("校对结束!!!\n");
    printf("校对结果存入Grade.txt文件成功！\n");
}






