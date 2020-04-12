//https://blog.csdn.net/weixin_43821874/article/details/86485920
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<malloc.h>
#define MAX_LEN 100
#define MAX 100

//ջ������ʵ��
typedef struct {
    int data[MAX_LEN];
    int top;
} Stack;

//Ϊջ����ռ�
Stack *Createstack() {
    Stack *p;
    p = (Stack *)malloc(sizeof(*p));
    p->top = -1;
    return p;
}

//��ջ
int Push(Stack *p, int x) {
    if(p->top == MAX_LEN - 1)
        return -1; //ջ����
    p->top++;
    p->data[p->top] = x;
    return 0;
}

//��ջ
int Pop(Stack *L, int *x) {
    if(L->top == -1)
        return -1;  //ջ��
    *x = L->data[L->top];
    L->top--;
    return 0;
}

//��ȡջ��Ԫ��
int Top(Stack *L, int *x) {
    if(L->top == -1)
        return -1; //ջ��
    *x = L->data[L->top];
    return 0;
}

//�п�
int Empty(Stack *L) {
    if(L->top == -1)
        return 1;
    return 0;
}

//�������ȼ�
int Priority(char ope) {
    switch(ope) {
    case '(':
        return 0; // �������Ѿ���ջ�ڣ�����Ƚϣ��������ȼ����
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        return -1;
    }
}

//���Լ��
int gcd(int a,int b) {
    int r=0;
    while (r=a%b,r!=0) {
        a=b;
        b=r;
    }
    return b;
}

//��С������
int beishu(int n1,int n2) {
    return n1*n2/gcd(n1,n2);
}

//�����ַ���
void constring(char s[],char t[],char q[]) {
    int i=0,j=0;
    for(i=0; s[i]!='\0'; i++) {
        q[i]=s[i];
    }
    for(j=0; t[j]; j++) {
        q[i+j]=t[j];
    }
    q[i+j]='\0';
}

//����
char *easy(int val_f,int val_m,char a[]) {
    char str0[100] = {};
    char str1[100] = {};
    char str2[100] = {};
    int n1,n2;
    int n3;
    if(val_f == 0) {
        a[0] = '0';
//        printf("a=%s\n",a);
        return 0;
    }
    n1=val_f/val_m;
    n2=val_f%val_m;
//    printf("n1 = %d, n2 = %d\n", n1, n2);
    if(n1==0) {
        if(n2!=0) {
            n3 = gcd(val_f,val_m);
            n1 = val_f/n3; // �����ķ���
            n2 = val_m/n3; // �����ķ�ĸ
//            printf("\nn1 = %d, n2 = %d, n3 = %d\n", n1, n2, n3);
            itoa(n1,str1,10);
            itoa(n2,str2,10);
            constring(str1,"/",a);
            constring(a,str2,a);
        }
        a[0] = '0';
    } else {
        if(n2==0) {
            itoa(n1,str0,10);
            constring(a,str0,a);
        } else {
            n3 = gcd(n2,val_m);
            n2/=n3;
            val_m/=n3;
            itoa(n1,str1,10);
            itoa(n2,str2,10);
            itoa(val_m,str0,10);

            constring(str1,"'",a);
            constring(a,str2,a);
            constring(a,"/",a);
            constring(a,str0,a);
        }
    }
    return 0;
}

//����
int Calculation(Stack *f_numstack,Stack *m_numstack, int ope) {
    int sum1 = 0, sum2 = 0, n_f1, n_f2, n_m1, n_m2;
    Pop(f_numstack, &n_f2);
    Pop(m_numstack,&n_m2);
    Pop(f_numstack,&n_f1);
    Pop(m_numstack, &n_m1);
//    printf("n_f2=%d,n_m2=%d,n_f1=%d,n_m1=%d\n",n_f2,n_m2,n_f1,n_m1);

    switch(ope) {
    case '+':
        if(n_f2==0) {
            sum1=n_f1;
            sum2=n_m1;
        } else if(n_f1==0) {
            sum1=n_f2;
            sum2=n_m2;
        } else {
            sum2=beishu(n_m1,n_m2);
            n_f1=sum2/n_m1*n_f1;
            n_f2=sum2/n_m2*n_f2;
            sum1=n_f1+n_f2;
        }
        break;
    case '-':
        if(n_f1==0&&n_f2!=0)
            return -1;
        else if(n_f1!=0&&n_f2==0) {
            sum1=n_f1;
            sum2=n_m1;
        } else if(n_f1==0&&n_f2==0) {
            sum1=0;
            sum2=1;
        } else {
            sum2=beishu(n_m1,n_m2);
            n_f1=(sum2/n_m1)*n_f1;
            n_f2=(sum2/n_m2)*n_f2;
            sum1=n_f1-n_f2;
//            printf("sum1=%d, sum2=%d\n",sum1,sum2);
            if(sum1<0) {
//                printf("return -1;\n");
                return -1;
            }else if(sum1==0) {
                sum1=0;
                sum2=1;
            }
        }
        break;
    case '*':
        if(n_f1==0||n_f2==0) {
            sum1=0;
            sum2=1;
        }
        sum1=n_f1*n_f2;
        sum2=n_m1*n_m2;
        break;
    case '/':
        if(n_f2==0)
            return -1;
        else if(n_f1==0&&n_f2!=0) {
            sum1=0;
            sum2=1;
        } else {
            sum1=n_f1*n_m2;
            sum2=n_f2*n_m1;
        }
        break;
    default:
        break;
    }
//    printf("sum1=%d,sum2=%d\n", sum1,sum2);
    Push(f_numstack, sum1);
    Push(m_numstack, sum2);
}

//�������������ķ���
int Dealope(Stack *f_numstack,Stack *m_numstack, Stack *opestack, int ope) {
    int old_ope;
    if(Empty(opestack) || ope == '(') {
        Push(opestack, ope);
        return 0;
    }
    Top(opestack, &old_ope);
//    printf("old_ope = %c\tope = %c\n", old_ope, ope);
    if(Priority(ope) > Priority(old_ope)) {
        Push(opestack, ope);
        return 0;
    }
    while(Priority(ope) <= Priority(old_ope)) {
        Pop(opestack, &old_ope);
        if(Calculation(f_numstack,m_numstack, old_ope) == -1)
            return -1;
        if(Empty(opestack))
            break;
        Top(opestack, &old_ope);
    }
    Push(opestack, ope);
    return 0;
}

//������
int Right(Stack *f_numstack,Stack *m_numstack, Stack *opestack) {
    int old_ope;
    Top(opestack, &old_ope);
    while(old_ope != '(') {
        Pop(opestack, &old_ope);
        if(Calculation(f_numstack,m_numstack, old_ope) == -1)
            return -1;
        Top(opestack, &old_ope);
    }
    Pop(opestack, &old_ope);//ȥ��������
    return 0;
}

void to_f(Stack *f_numstack,Stack *m_numstack,int value1,int value2) {
    Push(f_numstack,value1);
    Push(m_numstack,value2);
}
//���м�����
int Countarray(char *str, char b[]) {
//    char str[MAX];
    memset(b, 0, sizeof(b));
//    printf("����ļ����⣺");
//    printf("%s\n", str);
    int i=0, value=0, flag=0,val_f=0,val_m=0;
    int old_ope;
    Stack *f_numstack,*m_numstack, *opestack;//�ֱ�Ϊ���ӣ���ĸ���������ջ
    f_numstack = Createstack();
    m_numstack = Createstack();
    opestack = Createstack();
    while(str[i] != '#') {
        if(str[i] == ' ') {
            i++;
            continue;
        }
        if(str[i] >= '0' && str[i] <= '9') {
            value *= 10;
            value += str[i] - '0';
            flag = 1;
        } else {
            // ���������
            if(str[i]=='\'') {
                i++;
                int value1[2]= {};
                memset(value1, 0, sizeof(value1)); // ��ʼ��value1����
                int j=0;

                while(str[i]!=' ' && str[i]!='#' && str[i]!=')') {
                    if(str[i]=='/') {
                        j=1;
                        i++;
                        continue;
                    }
                    value1[j] *= 10;
                    value1[j] += str[i] - '0';
                    i++;
                }
                value1[0]+=value*value1[1];
                // ���ӷ�ĸ��ջ
//                printf("\tvalue1[0] = %d\n\tvalue1[1] = %d\n", value1[0], value1[1]);
                to_f(f_numstack,m_numstack,value1[0],value1[1]);
                flag=0;
                value=0;
                if(str[i]=='#') {
                    break;
                }
                if(str[i] == ')')
                    i--;
                i++;
            }
            if(flag) {
                to_f(f_numstack,m_numstack,value,1);
                flag = 0;
                value = 0;
            }
            // ֱ�ӽ�������
            if(str[i]=='#') {
                break;
            }
            if(str[i] == ')') {
                if(Right(f_numstack,m_numstack, opestack)==-1)
                    return -1;//������
            } else {
                if(Dealope(f_numstack,m_numstack, opestack, str[i]) == -1)
                    return -1;//��������
            }
        }
        i++;
    }
    if(flag) {
        // value������
        to_f(f_numstack,m_numstack,value,1);
    }
    while(!Empty(opestack)) {
        Pop(opestack, &old_ope);
        // �����������
        if(Calculation(f_numstack,m_numstack, old_ope) == -1)
            return -1;
    }
    Pop(f_numstack, &val_f);
    Pop(m_numstack,&val_m);
    // �洢�����Ľ��
//    char b[100] = {};
    easy(val_f, val_m, b);
//    printf("b=%s\n",b);
//    printf("1\n");
//    printf("%s = %s\n\n", str, b);
    return 0;
}

//��������
int Expression(char a[], FILE *fp, char b[]) {
    char x[MAX];
    char y[MAX];
    char z1[MAX] = {"��"};
    char z2[MAX] = {"="};
    int i=0,j=0,k=0;
    memset(x,0,sizeof(x));
    memset(y,0,sizeof(y));
//    x[0]=fgetc(fp);
//    printf("x[0]=%c ",x[0]);
//        while(x[i] != '\n' && x[i]!=EOF) {
//        x[++i] = fgetc(fp);
//        printf("x[i]=%c ",x[i]); // 1+2 = #
//    }
    fscanf(fp,"%s",y);
    while(strcmp(y,z2) != 0) {
        if(feof(fp))
            return -1;
        if(strcmp(y,z2) == 0)
            break;
        if(strcmp(y,z1) == 0)
            constring(x,"/",x);
        else
            constring(x,y,x);
        memset(y,0,sizeof(y));
        constring(x, " ", x);
        fscanf(fp,"%s",y);
    }
    constring(x, "\n", x);
    for(k=0; x[k] != '.'; k++);
    for(i=k+1; x[i]!='\n'; i++) {
        if(x[i] == '=')
            break;
        a[j] = x[i];
        j++;
    }
    a[j] = '#';
    Countarray(a, b);
    return 0;
}

