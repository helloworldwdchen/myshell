#include<stdio.h> 
// printf(), fprintf(), stderr, getchar(), perror()

#include<string.h> 
// strtok(), strcmp()

#include<stdlib.h>
// malloc(), realloc(), free(), exit(), execvp()

#include<unistd.h>
// chdir(), fork(), exec(), pid_t



/*-------------------------------------------------------*/

void myshell_loop(void);                    //shell主循环函数
char* myshell_readline(void);               //读入命令函数
char** myshell_splitline(char *line);       //命令解析函数
int myshell_execute(char **args);           //执行函数
int myshell_launch(char **args);            //外部命令执行函数

int myshell_cd(char **args);
int myshell_help(char **args);
int myshell_quit(char **args);
int myshell_cls(char **args);

int num_builtins();

extern void test();