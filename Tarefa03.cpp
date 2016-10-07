#include <iostream>
#include <pthread.h>
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
 * @brief      pthread_mutex_init
 *
 *             Signature: int pthread_mutex_init(pthread_mutex_t *restrict
 *             mutex, const pthread_mutexattr_t *restrict attr);
 *
 *             The pthread_mutex_init() function shall initialize the mutex
 *             referenced by mutex with attributes specified by attr. If attr
 *             is NULL, the default mutex attributes are used; the effect
 *             shall be the same as passing the address of a default mutex
 *             attributes object. Upon successful initialization, the state of
 *             the mutex becomes initialized and unlocked.
 *
 * @return     If successful, the pthread_mutex_init() functions shall return
 *             zero; otherwise, an error number shall be returned to indicate
 *             the error.
 */

/**
 * @brief      pthread_mutex_destroy
 *
 *             Signature: int pthread_mutex_destroy(pthread_mutex_t *mutex);
 *
 *             The pthread_mutex_destroy() function shall destroy the mutex
 *             object referenced by mutex; the mutex object becomes, in effect,
 *             uninitialized. An implementation may cause
 *             pthread_mutex_destroy() to set the object referenced by mutex to
 *             an invalid value.
 *
 * @return     If successful, the pthread_mutex_destroy() function shall return
 *             zero; otherwise, an error number shall be returned to indicate
 *             the error.
 */

/**
 * @brief      pthread_mutex_lock
 *
 *             Signature: int pthread_mutex_lock(pthread_mutex_t *mutex);
 *
 *             The mutex object referenced by mutex shall be locked by calling
 *             pthread_mutex_lock(). If the mutex is already locked, the calling
 *             thread shall block until the mutex becomes available. This
 *             operation shall return with the mutex object referenced by mutex
 *             in the locked state with the calling thread as its owner.
 *
 * @return     If successful, the pthread_mutex_lock(), pthread_mutex_trylock(),
 *             and pthread_mutex_unlock() functions shall return zero;
 *             otherwise, an error number shall be returned to indicate the
 *             error.
 */

/**
 * @brief      pthread_mutex_unlock
 *
 *             Signature: int pthread_mutex_unlock(pthread_mutex_t *mutex);
 *
 *             The pthread_mutex_unlock() function shall release the mutex
 *             object referenced by mutex. The manner in which a mutex is
 *             released is dependent upon the mutex's type attribute. If there
 *             are threads blocked on the mutex object referenced by mutex when
 *             pthread_mutex_unlock() is called, resulting in the mutex becoming
 *             available, the scheduling policy shall determine which thread
 *             shall acquire the mutex.
 *
 * @return     If successful, the pthread_mutex_lock(), pthread_mutex_trylock(),
 *             and pthread_mutex_unlock() functions shall return zero;
 *             otherwise, an error number shall be returned to indicate the
 *             error.
 */

pthread_mutex_t mutex;

void* inc_(void* void_ptr) {
    int *ptr = (int *)void_ptr;

    for (int i = 0; i < 100; ++i) {
        pthread_mutex_lock(&mutex);
        ++(*ptr);
        pthread_mutex_unlock(&mutex);
    }

    std::cout << "increment finished" << std::endl;

    return NULL;
}

void* dec_(void* void_ptr) {
    int *ptr = (int*) void_ptr;

    for (int i = 0; i < 100; ++i) {
        pthread_mutex_lock(&mutex);
        --(*ptr);
        pthread_mutex_unlock(&mutex);
    }

    std::cout << "decrement finished" << std::endl;

    return NULL;
}

int main() {
    int x = 0;
    std::cout << "x: " << x << std::endl;

    pthread_t inc_thread, dec_thread;

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&inc_thread, NULL, inc_, &x);
    pthread_create(&dec_thread, NULL, dec_, &x);

    pthread_join(inc_thread, NULL);
    pthread_join(dec_thread, NULL);

    pthread_mutex_destroy(&mutex);

    std::cout << "x: " << x << std::endl;
    return 0;
}
/* Respostas do "Para pensar e responder junto ao código:"

1. Na implementação computacional da Unidade 1 o que acontecia com a variável global count quando ela era incrementada pelos diferentes processos?

Cada processo tinha sua cópia da variável count, que cada thread incrementava de 0 para 1 uma vez, de modo que ela tomasse o valor 1 em todos os processo filhos.


2. O mesmo vai acontecer agora quando a variável global x for incrementada e decrementada pelos diferentes threads?

Não, porque threads compartilham memória, o x que uma thread incrementa está no mesmo endereço que o x que outra thread decrementa.


3. Qual é o valor esperado para a variável x após o término do aplicativo?

0


4. Se não houver mutex, qual será o valor final da variável global x (ou sua distribuição de probabilidade)?

Não é possível determinar, pois depende da implementação do escalonador.

*/
