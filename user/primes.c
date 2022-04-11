#include "kernel/types.h"
#include "user/user.h"
#define RD 0
#define WR 1

void primes(int lp[2])
{
    close(lp[WR]);
    //从左管道读取数据，并打印第一个素数
    int first;
    if(read(lp[RD],&first,sizeof(int)) == sizeof(int)) {
        printf("prime %d\n", first);

        //将不能被整除的数放入右管道
        int rp[2];
        pipe(rp); // 当前进程的右管道
        int data;
        while (read(lp[RD],&first,sizeof(int)) == sizeof(int)) {
             // 将无法整除的数据传递入右管道
             if (data % first){
                 write(rp[WR],&data,sizeof(int));
             }
        }
        close(lp[RD]);
        close(rp[WR]);
        //创建子进程处理，递归处理
        if (fork() == 0) {
            primes(rp);    // 递归的思想，但这将在一个新的进程中调用
        } else {
            close(rp[RD]);
            wait(0);
        }
    }
    
    exit(0);
    
}



int main(int argc, char const *argv[])
{
    int p[2];
    pipe(p);

    //第一个进程写入数据
    for(int i = 2; i <= 35; ++i) {
        write(p[WR],&i,sizeof(int));
    }

    if(fork()==0) {
        primes(p);
    }else {
        close(p[WR]);
        close(p[RD]);
        wait(0);
    }
    
    exit(0);
}