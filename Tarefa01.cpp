#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
// nome do acadêmico: Caio Pereira Oliveira (15100724)

/**
 * @brief      fork: creates a new process.
 *
 *             fork() creates a new process by duplicating the calling process.
 *             The new process is referred to as the child process. The calling
 *             process is referred to as the parent process.
 *
 *             Signature: pid_t fork(void);
 *
 *             Errors:
 *
 *             EAGAIN:
 *
 *             fork() cannot allocate sufficient memory to copy the parent's
 *             page tables and allocate a task structure for the child.
 *
 *             EAGAIN:
 *
 *             It was not possible to create a new process because the caller's
 *             RLIMIT_NPROC resource limit was encountered. To exceed this
 *             limit, the process must have either the CAP_SYS_ADMIN or the
 *             CAP_SYS_RESOURCE capability.
 *
 *             ENOMEM:
 *
 *             fork() failed to allocate the necessary kernel structures because
 *             memory is tight.
 *
 *             ENOSYS:
 *
 *             fork() is not supported on this platform (for example, hardware
 *             without a Memory-Management Unit).
 *
 *             ERESTARTNOINTR (since Linux 2.6.17):
 *
 *             System call was interrupted by a signal and will be restarted.
 *             (This can be seen only during a trace.)
 *
 *
 * @return     The return value is zero in the child and the process-id number
 *             of the child in  the parent,  or  -1  upon error. In the
 *             lattercase, ERRNO indicates the problem.
 */

/**
 * @brief      getpid: returns the process ID of the calling process.
 *
 *             Signature: pid_t getpid(void);
 *
 * @return     The return value is the process ID of the calling process. The
 *             getpid() function shall always be successful and no return value
 *             is reserved to indicate an error.
 */

/**
 * @brief      sleep: sleep for the specified number of seconds
 *
 *             Signature: unsigned int sleep(unsigned int seconds);
 *
 *             sleep() makes the calling thread sleep until `seconds` seconds
 *             have elapsed or a signal arrives which is not ignored.
 *
 * @return     Zero if the requested time has elapsed, or the number of seconds
 *             left to sleep, if the call was interrupted by a signal handler.
 */

/**
 * @brief      waitpid: wait for a child process to stop or terminate
 *
 *             The wait() and waitpid() functions shall obtain status
 *             information pertaining  to one of the caller's child processes.
 *             Various options permit status information to be obtained for
 *             child processes that have  terminated  or  stopped.  If status
 *             information is available for two or more child processes, the
 *             order in which their status is reported is unspecified.
 *
 *             Signature: pid_t waitpid(pid_t pid, int *wstatus, int options);
 *
 *             The waitpid() system call suspends execution  of  the  calling
 *             process until a child specified by pid argument has changed
 *             state.  By default, waitpid() waits only for terminated children,
 *             but this behavior is modifiable via the options argument, as
 *             described below.
 *
 *             The value of pid can be:
 *
 *             < -1   meaning  wait for  any  child process whose process group
 *             ID is equal to the absolute value of pid.
 *
 *             -1     meaning wait for any child process.
 *
 *             0      meaning wait for any child process whose  process  group
 *             ID  is equal to that of the calling process.
 *
 *             > 0    meaning  wait for the child whose process ID is equal to
 *             the value of pid.
 *
 *
 *             The value of options is an OR of zero or more of the following
 *             constants:
 *
 *             WNOHANG: return immediately if no child has exited.
 *
 *             WCONTINUED: also return if a stopped child has been resumed by
 *             delivery of SIGCONT.
 *
 *             WUNTRACED: also return if a child has stopped (but not traced via
 *             ptrace(2)). Status for traced children which have stopped is
 *             provided even if this option is not specified.
 *
 *
 *             If wstatus is not NULL, waitpid() store status information in the
 *             int to which it points. This integer can be inspected with the
 *             following macros (which take the integer itself as an argument,
 *             not apointer to it, as is done in waitpid()!):
 *
 *             WIFEXITED(wstatus): returns true if the child terminated
 *             normally, that is, by calling exit(3) or _exit(2), or by
 *             returning from main().
 *
 *             WEXITSTATUS(wstatus): returns the exit status of the child. This
 *             consists  of  the least  significant 8 bits of the wstatus
 *             argument that the child specified in a call to exit(3) or
 *             _exit(2) or as the argument for a return statement in main().
 *             This macro should be employed only if WIFEXITED returned true.
 *
 *             WIFSIGNALED(wstatus): returns true if the child process was
 *             terminated by a signal.
 *
 *             WTERMSIG(wstatus): returns the number of the signal that caused
 *             the child process to terminate. This macro should be employed
 *             only if WIFSIGNALED returned true.
 *
 *             WCOREDUMP(wstatus): returns true if the child produced a core
 *             dump. This  macro should  be  employed  only if  WIFSIGNALED
 *             returned true.  This macro is not specified in POSIX.1-2001 and
 *             is not  available  on some  UNIX  implementations (e.g.,  AIX,
 *             SunOS).  Only use this enclosed in #ifdef WCOREDUMP ... #endif.
 *
 *             WIFSTOPPED(wstatus): returns true if the child process was
 *             stopped by delivery of a signal; this  is  possible only if the
 *             call was done using WUNTRACED or when the child is being traced
 *             (see ptrace(2)).
 *
 *             WSTOPSIG(wstatus): returns the number of the signal which caused
 *             the child to stop.This macro should be employed only if
 *             WIFSTOPPED returned true.
 *
 *             WIFCONTINUED(wstatus): (since  Linux 2.6.10) returns true if the
 *             child process was resumed by delivery of SIGCONT.
 *
 *             Errors:
 *
 *             ECHILD: The process specified by pid does not exist or is not a
 *             child of the calling process.
 *
 *             EINTR: WNOHANG was not set and an unblocked signal or a SIGCHLD
 *             was caught; see signal(7).
 *
 *             EINVAL: The options argument was invalid.
 *
 *
 * @return     on success, returns the process ID of the child whose state has
 *             changed; if WNOHANG was specified and one or more child(ren)
 *             specified by pid exist, but have not yet changed state, then 0 is
 *             returned. On error, -1 is returned and ERRNO indicates the
 *             problem.
 */

const int NPROCESS = 5;

using namespace std;

int main () {
    // include declarations you need
    int count = 0;
    pid_t child_pid;
    pid_t parent = getpid();

    /* Repeat 5 times */
    for (int i = 0; i < NPROCESS; ++i) {
        cout << "Parent process " << parent << ": Creating child" << endl;

        /* Duplicate this process */
        child_pid = fork();

        /* If there was an error on duplication then */
        if (child_pid < 0) {
            cout << "Error on fork()" << endl;
            return -1;

        /* If child-process is running then */
        } else if (child_pid == 0) {
            child_pid = getpid();
            cout << "Child process " << child_pid << ": Running" << endl;
            count++;

            /* Sleep for 1 second */
            sleep(1);

            cout << "Child process " << child_pid << ": Exiting with status " << count << endl;

            return count;
        }
    }

    /* if this is the parent-process then */
    cout << "Parent process " << parent << ": Waiting children to exit" << endl;
    // int errno, status, sum = 0;
    int errno, status, sum = 0;
    /* Parent-process waits for all children to exit, adding each status to the sum variable */

    for (int i = 0; i < NPROCESS; ++i) {
        waitpid(-1, &status, 0);

        if (errno == ECHILD) {
            cout << "Error: no child process (ECHILD)" << endl;
            return -1;
        }

        if (WIFEXITED(status)) {
            sum += WEXITSTATUS(status);
        } else {
            cout << "Parent process " << parent << ": Child exited with error" << endl;
        }
    }

    cout << "Parent process " << parent << ": Exiting with sum " << sum << endl;

    /*  */
    return count;

    /* Respostas do "Para pensar e responder junto ao código:"

    1) 5, porque cada processo terá sua cópia de count (inicializado em 0),
       que quando incrementado irá de 0 para 1, então somando os counts de
       todos os processos chegaremos a 5.

    2) Não, porque condição de corrida só ocorre quando existe
       memória compartilhada, como este aplicativo usa apenas
       processos (que não compartilham memória), não há possibilidade de
       condição de corrida.

    3) Serão endereços iguais, pois correspondem a um endereço virtual
       contido em uma página do processo que foi copiada pelo sistema
       operacional quando a chamada de sistema fork foi acionada.
       Note que por mais que os endereços virtuais sejam iguais eles
       correspondem a endereços físicos diferentes.

    */
}
