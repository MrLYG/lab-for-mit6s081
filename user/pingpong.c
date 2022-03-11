#include "user/user.h"

#define R = 0; //read form pipe
#define W = 1; //write to pipe
int 
main()
{
    char msg = 'p'; // msg used to send

    // pipe
    int p2c[2];
    int c2p[2];
    pipe(p2c);
    pipe(c2p);

    int ppid = fork();
    //child process
    if (ppid = 0){
        //close unused pipe ends
        close(c2p[R]);
        close(p2c[W]);

        read(p2c[R],&msg,sizeof(char));
        fprintf(1, "%d: received ping\n", getpid());
        write(c2p[W],&msg,sizeof(char));
        close(c2p[W]);
        close(p2c[R]);
        exit(0);
    }else{ //parent process

        //close unused pipe ends
        close(p2c[R]);
        close(c2p[W]);

        
        write(p2c[W],&msg,sizeof(char));
        wait((int *) 0);
        read(c2p[R],&msg,sizeof(char))
        fprintf(1,"%d: received pong\n", getpid())
        close(p2c[W]);
        close(c2p[R]);
        exit(0);
    }

}