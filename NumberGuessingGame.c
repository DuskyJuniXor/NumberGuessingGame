#include <stdio.h>
#include <sys/time.h>                                       //linux上计时需要用gettimeofday()，需要调用该包
#include <string.h>
#include <time.h>
#include <stdlib.h>                                         //调用exit(EXIT_FAILURE)用

void menu();                                                //(个人习惯)提前声明函数; menu修改后无返回值改为void
void regist();
void game();
void login();                                               //login修改后无返回值，改为void
void clean_stdin();

char id[50],pwd[20], pwdr[20], text[50];                    //由于后面使用strcat时要防止超出id数组长度，改为50; 我的注册界面添加pwdr[20]数组

void clean_stdin(){                                         //由于linux中fflush(stdin)函数不能使用，添加一个clean_stdin函数以起到相同效果
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

//登录 
void login()
{
    printf("登录界面\n");
    printf("ID：");
    //gets(id);
    fgets(id, sizeof(id) - 1, stdin);                       //linux中的gcc编译器认为gets函数是不安全的，需要用fgets函数
    id[strlen(id) - 1] = '\0';                              //fgets函数会读入'\n'换行符，故需将换行符更换为结束符'\0'
    printf("PWD：");
    //gets(pwd); 
    fgets(pwd, sizeof(pwd) - 1, stdin);
    pwd[strlen(pwd) - 1] = '\0';
    strcat(id,pwd);
    strcat(id,"\n");
    
	int ok=0;                                              //len未被使用到，强迫症不爽，故删除
    FILE *fp = fopen("user.txt", "r");
    if(NULL == fp)
    {
        printf("Failed to open user.txt\n");
        //return 0;                                        //return0只是退出函数，不符合程序运行逻辑，故改。
        exit(EXIT_FAILURE);
    }

    while(!feof(fp))
    {
        memset(text, 0, sizeof(text));
        fgets(text, sizeof(text) - 1, fp); 
        if(strcmp(id,text) == 0)
		{
           ok=1;
           break;
        }
    }
    
    if(ok)
    {
      printf("登录成功!\n");
	}
    else
    {
      printf("登录失败!\n");
      menu();                                               //这里我们希望登录失败能回到menu界面重新登录，故添加
	}
	fclose(fp);
}

//注册                                                      //啥都没有，使用自己写的版本
/*void regist()
{
	printf("注册界面\n");
    
    login();
}*/

void regist(){
    printf("注册界面\n");
    FILE *fp = fopen("user.txt", "a");
    if(fp == NULL){
        printf("Failed to open user.txt\n");
        exit(EXIT_FAILURE);
    }else{
        id:
        printf("ID(within 20 characters): ");
        fgets(id, sizeof(id) - 1, stdin);
        id[strlen(id) - 1] = '\0';

        if(strlen(id) > 20){
            printf("Illegal id: the length of id must be within 20\n");
            goto id;
        }

        password:
        printf("password(within 20 characters): ");
        fgets(pwd, sizeof(pwd) - 1, stdin);
	pwd[strlen(pwd) - 1] = '\0';
        if(strlen(pwd) > 20){
            printf("Illegal password: the length of password must be within 20\n");
            goto password;
        }

        printf("Repeat password:" );
        fgets(pwdr, sizeof(pwdr) - 1, stdin);
	pwdr[strlen(pwdr) - 1] = '\0';
        if(strcmp(pwd, pwdr) == 0){
            printf("Registed successfully!\n");
            strcat(id, pwd);
            strcat(id, "\n");
            fputs(id, fp);
            fclose(fp); 
            login();
        }else{
            printf("Error: passwords didn't correspond with each other\n");
            goto password;
        }
    }
}

//游戏 
void game()
{	
	//clock_t start, end;                                   //linux下clock()函数只计算CPU计算时间，不好，改为gettimeofday()函数
    //start = clock();
    struct timeval start;                              //声明变量
    struct timeval end;
    gettimeofday(&start, NULL);
    //printf("runtime = %f\n",run_time);                    //本语句没有用
    srand((unsigned)time(NULL));
    int num = rand() % 1000;  
    int guess, i = 0; 
	int min = 0, max = 1000;  
    while (1)
	{
    	printf("Please guess number:");
        scanf("%d", &guess);
        if (num > guess)
		{
            i++;	
            printf("猜小了\n");
            min = guess;
            printf("范围:%d - %d\n", min, max);
        }
		else if (num < guess)
		{
            i++;	
            printf("猜大了\n");
            max = guess;
            printf("范围:%d - %d\n", min, max);
        }
		else
		{
            i++;	
            //end = clock();
            gettimeofday(&end, NULL);
            int t = (double)(end.tv_sec-start.tv_sec);                  //声明未声明的t变量并复制                                            
            printf("猜对了!\n猜数次数：%d次\n用时：%d秒\n", i, t);  
            break;
        }
 
    }
}

//菜单 
void menu()
{
    printf("**欢迎玩猜数字游戏！**\n");                    //（小声)加个标题不过分吧
	printf("1 注册\n");
	printf("0 登录\n");
    int a = 0;
    scanf("%d",&a);
    //fflush(stdin);                                    //linux下fflush()用不了
    clean_stdin();
    if(a)
       regist();
    else
        login();
}

int main()
{ 
	int a;
    menu();
    choice:
    printf("1 Play\n");
    printf("0 Exit\n");
    scanf("%d", &a);
    clean_stdin();
    switch (a){
        case 1:
        game();
        break;
        
        case 0:
        break;
        
        default:
        printf("选项错误!\n请重新输入：\n");
        goto choice;                                    //满足“重新输入”需求
        break;
    }
    return 0;
}


