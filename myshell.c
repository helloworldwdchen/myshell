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

char *builtin_str[] = {                     //内部函数名称字符串数组
    "cd",
    "help",
    "quit"
};
int (*builtin_func[])(char **) = {          //内部函数函数指针数组
    &myshell_cd,
    &myshell_help,
    &myshell_quit
};
int num_builtins(){                         //获取内部函数的数量
    return sizeof(builtin_str)/sizeof(char *);
};



/*-------------------------------------------------------*/

int main(){
    myshell_loop();         // 进入主循环
    return 0;
}

/*-------------------------------------------------------*/

void myshell_loop(void){
    char *line;             // 接受输入的命令的字符串
    char **args;            // 参数数组
    int status;             // 运行状态标记值

    do{
        printf("$ ");
        line = myshell_readline();          // 读入输入
        args = myshell_splitline(line);     // 将命令解析
        status = myshell_execute(args);     // 执行命令

        free(line);           // 释放空间
        free(args);

    } while(status);
}

#define RL_BUFSIZE 1024             // 缓冲区大小常数
char* myshell_readline(void){       // 读取输入命令
    int bufsize = RL_BUFSIZE;       // 缓冲区大小值
    int position = 0;               // 位置
    char *buffer = malloc(bufsize*sizeof(char));    // 申请一块缓冲区空间
    char c;                         // 用来输入的字符

    if(!buffer){                    // 如果申请失败就打印错误并退出
        fprintf(stderr,"myshell allocation error\n");
        exit(0);
    }

    while(1){                   //读入部分

        c = getchar();
        if(c == EOF){           //读到结束符，退出
            exit(0);
        }
        else if(c=='\n'){       //读到换行，结束输入,返回缓冲区
            buffer[position] = '\0';
            return buffer;
        }
        else{                   //将读到的字符加入到缓冲区
            buffer[position] = c;
        }
        position++;

        if(position>=bufsize){      //如果缓冲区大小不足，realloc新空间
            bufsize += RL_BUFSIZE;
            buffer = realloc(buffer, bufsize);
            if(!buffer){
                fprintf(stderr,"myshell allocation error\n");
                exit(0);
            }
        }

    }
}

#define ARG_BUFSIZE 64              //缓冲区大小常量
#define ARG_DELIM " \t\r\n\a"       //用来分割字符串的字符
char** myshell_splitline(char* line){       //解析字符串函数
    int bufsize = ARG_BUFSIZE;          
    int position = 0;
    char **args = malloc(bufsize*sizeof(char*));
    char *arg;                      //用来分割单个参数
    char **args_backup;             //用来在申请新空间失败时释放原空间

    if(!args){                  //如果申请空间失败，打印错误并退出
        fprintf(stderr,"myshell allocation error\n");
        exit(0);
    }

    arg = strtok(line, ARG_DELIM);      //分割下输入的命令
    while(arg != NULL){                 //利用循环完成输入命令的分割
        args[position] = arg;
        position++;

        if(position >= bufsize){
            bufsize+=ARG_BUFSIZE;
            args_backup = args;
            args = realloc(args, bufsize*sizeof(char *));
            if(!args){
                free(args_backup);
                fprintf(stderr,"myshell allocation error\n");
                exit(0);
             }
        }

        arg = strtok(NULL, ARG_DELIM);
    }

    args[position] = NULL;
    // for(int i=0; i<position; i++){
    //     printf("%s*\n", args[i]);
    // }
    return args;
}

int myshell_execute(char **args){           //执行函数
    int i;

    if(args[0] == NULL){                    //如果无参数，退出
        return 1;
    }

    for(i=0; i<num_builtins(); i++){            //遍历内部函数，查找当前输入的命令是否在内部命令中
        if(strcmp(args[0], builtin_str[i]) == 0){
            return (*builtin_func[i])(args);        //在的话就运行相应的内部函数
        }
    }

    return myshell_launch(args);                //否则当作外部函数运行
}

int myshell_launch(char **args){            //外部函数运行函数
    pid_t pid;
    int status;

    pid = fork();                           //fork一个新进程
    if(pid == 0){                           //如果是子进程
        // 子进程
        if(execvp(args[0], args) == -1){
            perror("myshell");
        }
        exit(0);
    }
    else if(pid < 0){                       //如果fork失败
        perror("myshell");
    }
    else{                               //如果是父进程
        // 父进程
        do{
            waitpid(pid, &status, WUNTRACED);
            // WUNTRACED 若子进程进入暂停状态，则马上返回，但子进程的结束状态不予以理会
        }while(!WIFEXITED(status) && !WIFSIGNALED(status));
        // WIFEXITED(status)如果若为正常结束子进程返回的状态，则为真；
        // WIFSIGNALED(status)若为异常结束子进程返回的状态，则为真；
    }

    return 1;
}

int myshell_cd(char **args){
    printf("you command is 'cd'\n");
    return 1;
}
int myshell_help(char **arg){
    int i;
    printf("wintermorning's LSH\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    for (i = 0; i < num_builtins(); i++) {
        printf("  %s\n", builtin_str[i]);
    }

    printf("Use the man command for information on other programs.\n");
    return 1;
}
int myshell_quit(char **args){
    return 0;
}