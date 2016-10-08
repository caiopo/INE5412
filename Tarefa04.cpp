#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

// Nome do aluno: Caio Pereira Oliveira (15100724)

/**
 * @brief      pthread_create
 *
 *             Signature: int pthread_create(pthread_t *thread, const
 *             pthread_attr_t *attr, void *(*start_routine) (void *), void
 *             *arg);
 *
 *             The pthread_create() function starts a new thread in the calling
 *             process. The new thread starts execution by invoking
 *             start_routine(); arg is passed as the sole argument of
 *             start_routine().
 *
 *             The attr argument points to a pthread_attr_t structure whose
 *             contents are used at thread creation time to determine attributes
 *             for the new thread; this structure is initialized using
 *             pthread_attr_init(3) and related functions. If attr is NULL, then
 *             the thread is created with default attributes.
 *
 *             Before returning, a successful call to pthread_create() stores
 *             the ID of the new thread in the buffer pointed to by thread; this
 *             identifier is used to refer to the thread in subsequent calls to
 *             other pthreads functions.
 *
 * @return     On success, pthread_create() returns 0; on error, it returns an
 *             error number, and the contents of *thread are undefined.
 */

/**
 * @brief      pthread_join
 *
 *             Signature: int pthread_join(pthread_t thread, void **retval);
 *
 *             The pthread_join() function waits for the thread specified by
 *             thread to terminate. If that thread has already terminated, then
 *             pthread_join() returns immediately. The thread specified by
 *             thread must be joinable.
 *
 *             If retval is not NULL, then pthread_join() copies the exit status
 *             of the target thread (i.e., the value that the target thread
 *             supplied to pthread_exit(3)) into the location pointed to by
 *             *retval. If the tar‐ get thread was canceled, then
 *             PTHREAD_CANCELED is placed in *retval.
 *
 *             If multiple threads simultaneously try to join with the same
 *             thread, the results are undefined. If the thread calling
 *             pthread_join() is canceled, then the target thread will remain
 *             joinable (i.e., it will not be detached).
 *
 *
 *
 * @return     On success, pthread_join() returns 0; on error, it returns an
 *             error number.
 */

/**
 * @brief      sem_init
 *
 *             Signature: int sem_init(sem_t *sem, int pshared, unsigned int value);
 *
 *             sem_init() initializes the unnamed semaphore at the address
 *             pointed to by sem. The value argument specifies the initial
 *             value for the semaphore.
 *
 * @return     sem_init() returns 0 on success; on error, -1 is returned, and
 *             errno is set to indicate the error.
 */

/**
 * @brief      sem_post
 *
 *             Signature: int sem_post(sem_t *sem);
 *
 *             sem_post() increments (unlocks) the semaphore pointed to by sem.
 *             If the semaphore's value consequently becomes greater than zero,
 *             then another process or thread blocked in a sem_wait(3) call will
 *             be woken up and proceed to lock the semaphore.
 *
 * @return     sem_post() returns 0 on success; on error, the value of the
 *             semaphore is left unchanged, -1 is returned, and errno is set to
 *             indicate the error.
 */

/**
 * @brief      sem_wait
 *
 *             Signature: int sem_wait(sem_t *sem);
 *
 *             sem_wait() decrements (locks) the semaphore pointed to by sem. If
 *             the semaphore's value is greater than zero, then the decrement
 *             proceeds, and the function returns, immediately. If the semaphore
 *             currently has the value zero, then the call blocks until either
 *             it becomes possible to perform the decrement (i.e., the semaphore
 *             value rises above zero), or a signal handler interrupts the call.
 *
 * @return     0 on success; on error, the value of the semaphore is left
 *             unchanged, -1 is returned, and errno is set to indicate the
 *             error.
 */


const unsigned int NUM_CHILDS = 7, NUM_BALLS = 1;

sem_t semaphore;


void* child(void *void_ptr) {
  unsigned int childNum = *((unsigned int*) void_ptr);

    for (unsigned int i = 1; i <= 5; ++i) {
        std::cout << "Child " << childNum << " wants to play with the ball for the " << i << "th time" << std::endl;

        std::cout << " Child " << childNum << " wants to take a ball from the basket" << std::endl;

        sem_wait(&semaphore);

        std::cout << "  Child " << childNum << " is playing with the ball" << std::endl;

        sleep(1);

        std::cout << "  Child " << childNum << " wants to leave the ball in the basket" << std::endl;

        sem_post(&semaphore);

        std::cout << " Child " << childNum << " has droped the ball in the basket" << std::endl;
    }

    std::cout << "Child " << childNum << " will no longer play" << std::endl;

    return NULL;
}

int main() {
    std::cout << "The kindengarten is open" << std::endl;

    sem_init(&semaphore, 0, NUM_BALLS);

    pthread_t threads[NUM_CHILDS];

    for(unsigned int i = 0; i < NUM_CHILDS; ++i)
        pthread_create(&threads[i], NULL, child, new unsigned int(i));

    for(unsigned int i = 0; i < NUM_CHILDS; ++i)
        pthread_join(threads[i], NULL);

    sem_destroy(&semaphore);

    std::cout << "The kindengarten is closed" << std::endl;
    return 0;
}

/* Respostas das perguntas "para pensar":
1.1: Os semáforos podem ser variáveis locais?

Não, pois eles deve estar em uma área de memória acessável por todas as threads.

1.2: Todas as threads "child" terminam? Justifique.

Sim, pois eventualmente todas as crianças brincarão com a bola 5 vezes.

2: E se no cesto couber uma única bola, como na versão original do problema?
Há algum erro de programação para que as threads não terminem?
O que poderia ser feito para detectar que um evento nunca ocorrerá e
fazer com que o programa finalize com sucesso, encerrando todas suas threads?

Se houverem 3 bolas, mas o cesto apenas guardar 1, poderá ocorrer a situação
em que duas crianças brincam e as outras 5 já pararam de brincar (deixando o cesto cheio),
então quando as duas crianças terminarem de brincar, não poderão guardar suas bolas no cesto,
entrando em deadlock.

Quando houverem menos crianças no kindergarten que bolas, as bolas excedentes
devem ser removidas para evitar deadlock.
*/
