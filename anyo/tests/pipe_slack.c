#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

/* Une petite fonction pour executer un programme avec son path. Pas de surprises */
void        ft_execwait(char *path, char **av)
{
    pid_t   father;
    int     osef;

    osef = 0;
    father = fork();
    if (father > 0)
        wait(&osef);
    else
    {
        execve(path, av, NULL);
    }
}

/* + Il faut fermer le coté du pipe que tu n’utilises pas */
int main(int argc, char **argv)
{
    int p[2];
    char tab[6];
    int save = dup(1);


    pipe(p);
    dup2(p[1], 1);
    ft_execwait("/bin/ls", argv);

    
    close(p[1]);
    dup2(p[0], 0);
    pipe(p);
    dup2(p[1], 1);
    ft_execwait("/usr/bin/rev", argv);

    close(p[1]);
    dup2(p[0], 0);
    pipe(p);
    dup2(p[1], 1);
    ft_execwait("/usr/bin/rev", argv);

    close(p[1]);
    dup2(p[0], 0);
    pipe(p);
    dup2(p[1], 1);
    ft_execwait("/bin/cat", argv);


    close(p[1]);
    dup2(save, 1);
    dup2(p[0], 0);
    ft_execwait("/usr/bin/say", argv);

    return (0);
}
