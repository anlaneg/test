his is the complete listing of function calls for POSIX®.1, POSIX.1b and POSIX.1c. All of them are fully supported by LynxOS®.
POSIX.1 function calls Function	POSIX Description
access 	Tests for file accessibility
alarm 	Schedules an alarm
asctime 	Converts a time structure to a string
cfgetispeed 	Reads terminal input baud rate
cfgetospeed 	Reads terminal output baud rate
cfsetispeed 	Sets terminal input baud rate
cfsetospeed 	Sets terminal output baud rate
chdir 	Changes current working directory
chmod 	Changes file mode
chown 	Changes owner and/or group of a file
close 	Closes a file
closedir 	Ends directory read operation
creat 	Creates a new file or rewrites an existing one
ctermid 	Generates terminal pathname
cuserid 	Gets user name
dup 	Duplicates an open file descriptor
dup2 	Duplicates an open file descriptor
execl 	Executes a file
execle 	Executes a file
execlp 	Executes a file
execv 	Executes a file
execve 	Executes a file
execvp 	Executes a file
_exit 	Terminates a process
fcntl 	Manipulates an open file descriptor
fdopen 	Opens a stream on a file descriptor
fork 	Creates a process
fpathconf 	Gets configuration variable for an open file
fstat 	Gets file status
getcwd 	Gets current working directory
getegid 	Gets effective group ID
getenv 	Gets environment variable
geteuid 	Gets effective user ID
getgid 	Gets real group ID
getgrgid 	Reads groups database based on group ID
getgrnam 	Reads groups database based on group name
getgroups 	Gets supplementary group IDs
getlogin 	Gets user name
getpgrp 	Gets process group ID
getpid 	Gets process ID
getppid 	Gets parent process ID
getpwnam 	Reads user database based on user name
getpwuid 	Reads user database based on user ID
getuid 	Gets real user ID
isatty 	Determines if a file descriptor is associated with a terminal
kill 	Sends a kill signal to a process
link 	Creates a link to a file
longjmp 	Restores the calling environment
lseek 	Repositions read/write file offset
mkdir 	Makes a directory
mkfifo 	Makes a FIFO special file
open 	Opens a file
opendir 	Opens a directory
pathconf 	Gets configuration variables for a path
pause 	Suspends a process execution
pipe 	Creates an interprocess channel
read 	Reads from a file
readdir 	Reads a directory
rename 	Renames a file
rewinddir 	Resets the readdir() pointer
rmdir 	Removes a directory
setgid 	Sets group ID
setjmp 	Saves the calling environment for use by longjmp()
setlocale 	Sets or queries a program's locale
setpgid 	Sets a process group ID for job control
setuid 	Sets the user ID
sigaction 	Examines and changes signal action
sigaddset 	Adds a signal to a signal set
sigdelset 	Removes a signal to a signal set
sigemptyset 	Creates an empty signal set
sigfillset 	Creates a full set of signals
sigismember 	Tests a signal for a selected member
siglongjmp 	Goes to and restores signal mask
sigpending 	Examines pending signals
sigprocmask 	Examines and changes blocked signals
sigsetjmp 	Saves state for siglongjmp()
sigsuspend 	Waits for a signal
sleep 	Delays process execution
stat 	Gets information about a file
sysconf 	Gets system configuration information
tcdrain 	Waits for all output to be transmitted to the terminal
tcflow 	Suspends/restarts terminal output
tcflush 	Discards terminal data
tcgetattr 	Gets terminal attributes
tcgetpgrp 	Gets foreground process group ID
tcsendbreak 	Sends a break to a terminal
tcsetattr 	Sets terminal attributes
tcsetpgrp 	Sets foreground process group ID
time 	Determines the current calendar time
times 	Gets process times
ttyname 	Determines a terminal pathname
tzset 	Sets the timezone from environment variables
umask 	Sets the file creation mask
uname 	Gets system name
unlink 	Removes a directory entry
utime 	Sets file access and modification times
waitpid 	Waits for process termination
write 	Writes to a file

 
POSIX.1b function calls Function	POSIX Description
aio_cancel 	Tries to cancel an asynchronous operation
aio_error 	Retrieves the error status for an asynchronous operation
aio_read 	Asynchronously reads from a file
aio_return 	Retrieves the return status for an asynchronous operation
aio_suspend 	Waits for an asynchronous operation to complete
aio_write 	Asynchronously writes to a file
clock_getres 	Gets resolution of a POSIX.1b clock
clock_gettime 	Gets the time according to a particular POSIX.1b clock
clock_settime 	Sets the time according to a particular POSIX.1b clock
fdatasync 	Synchronizes at least the data part of a file with the underlying media
fsync 	Synchronizes a file with the underlying media
kill, sigqueue 	Sends signals to a process
lio_listio 	Performs a list of I/O operations, synchronously or asynchronously
mlock 	Locks a range of memory
mlockall 	Locks the entire memory space down
mmap 	Maps a shared memory object (or possibly another file) into process's address space
mprotect 	Changes memory protection on a mapped area
mq_close 	Terminates access to a POSIX.1b message queue
mq_getattr 	Gets POSIX.1b message queue attributes
mq_notify 	Registers a request to be notified when a message arrives on an empty message queue
mq_open 	Creates/accesses a POSIX.1b message queue
mq_receive 	Receives a message from a POSIX.1b message queue
mq_send 	Sends a message on a POSIX.1b message queue
mq_setattr 	Sets a subset of POSIX.1b message queue attributes
msync 	Makes a mapping consistent with the underlying object
munlock 	Unlocks a range of memory
munlockall 	Unlocks the entire address space
munmap 	Undo mapping established by mmap
nanosleep 	Pauses execution for a number of nanoseconds
sched_get_priority_max 	Gets maximum priority value for a scheduler
sched_get_priority_min 	Gets minimum priority value for a scheduler
sched_getparam 	Retrieves scheduling parameters for a particular process
sched_getscheduler 	Retrieves scheduling algorithm for a particular purpose
sched_rr_get_interval 	Gets the SCHED_RR interval for the named process
sched_setparam 	Sets scheduling parameters for a process
sched_setscheduler 	Sets scheduling algorithm/parameters for a process
sched_yield 	Yields the processor
sem_close 	Terminates access to a POSIX.1b semaphore
sem_destroy 	De-initializes a POSIX.1b unnamed semaphore
sem_getvalue 	Gets the value of a POSIX.1b semaphore
sem_open 	Creates/accesses a POSIX.1b named semaphore
sem_post 	Posts (signal) a POSIX.1b named or unnamed semaphore
sem_unlink 	Destroys a POSIX.1b named semaphore
sem_wait, sem_trywait 	Waits on a POSIX.1b named or unnamed semaphore
shm_open 	Creates/accesses a POSIX.1b shared memory object
shm_unlink 	Destroys a POSIX.1b shared memory object
sigwaitinfosigtimedwait 	Synchronously awaits signal arrival; avoid calling handler
timer_create 	Creates a POSIX.1b timer based on a particular clock
timer_delete 	Deletes a POSIX.1b timer
timer_gettime 	Time remaining on a POSIX.1b timer before expiration
timer_settime 	Sets expiration time/interval for a POSIX.1b timer
wait, waitpid 	Retrieves status of a terminated process and clean up corpse

 
POSIX.1c function calls Function	POSIX Description
pthread_atfork 	Declares procedures to be called before and after a fork
pthread_attr_destroy 	Destroys a thread attribute object
pthread_attr_getdetachstate 	Obtains the setting of the detached state of a thread
pthread_attr_getinheritsched 	Obtains the setting of the scheduling inheritance of a thread
pthread_attr_getschedparam 	Obtains the parameters associated with the scheduling policy attribute of a thread
pthread_attr_getschedpolicy 	Obtains the setting of the scheduling policy of a thread
pthread_attr_getscope 	Obtains the setting of the scheduling scope of a thread
pthread_attr_getstackaddr 	Obtains the stack address of a thread
pthread_attr_getstacksize 	Obtains the stack size of a thread
pthread_attr_init 	Initializes a thread attribute object
pthread_attr_setdetachstate 	Adjusts the detached state of a thread
pthread_attr_setinheritsched 	Adjusts the scheduling inheritance of a thread
pthread_attr_setschedparam 	Adjusts the parameters associated with the scheduling policy of a thread
pthread_attr_setschedpolicy 	Adjusts the scheduling policy of a thread
pthread_attr_setscope 	Adjusts the scheduling scope of a thread
pthread_attr_setstackaddr 	Adjusts the stack address of a thread
pthread_attr_setstacksize 	Adjusts the stack size of a thread
pthread_cancel 	Cancels the specific thread
pthread_cleanup_pop 	Removes the routine from the top of a thread's cleanup stack, and if execute is nonzero, runs it
pthread_cleanup_push 	Places a routine on the top of a thread's cleanup stack
pthread_condattr_destroy 	Destroys a condition variable attribute object
pthread_condattr_getpshared 	Obtains the process-shared setting of a condition variable attribute object
pthread_condattr_init 	Initializes a condition variable attribute object
pthread_condattr_setpshared 	Sets the process-shared attribute in a condition variable attribute object to either PTHREAD_PROCESS_SHARED or PTHREAD_PROCESS_PRIVATE
pthread_cond_broadcast 	Unblocks all threads that are waiting on a condition variable
pthread_cond_destroy 	Destroys a condition variable
pthread_cond_init 	Initializes a condition variable with the attributes specified in the specified condition variable attribute object
pthread_cond_signal 	Unblocks at least one thread waiting on a condition variable
pthread_cond_timedwait 	Automatically unlocks the specified mutex, and places the calling thread into a wait state
pthread_cond_wait 	Automatically unlocks the specified mutex, and places the calling thread into a wait state
pthread_create 	Creates a thread with the attributes specified in attr
pthread_detach 	Marks a threads internal data structures for deletion
pthread_equal 	Compares one thread handle to another thread handle
pthread_exit 	Terminates the calling thread
pthread_getschedparam 	Obtains both scheduling policy and scheduling parameters of an existing thread
pthread_getspecific 	Obtains the thread specific data value associated with the specific key in the calling thread
pthread_join 	Causes the calling thread to wait for the specific threadâ€™s termination
pthread_key_create 	Generates a unique thread-specific key that's visible to all threads in a process
pthread_key_delete 	Deletes a thread specific key
pthread_kill 	Delivers a signal to the specified thread
pthread_mutexattr_destroy 	Destroys a mutex attribute object
pthread_mutexattr_getprioceiling 	Obtains the priority ceiling of a mutex attribute object
pthread_mutexattr_getprotocol 	Obtains protocol of a mutex attribute object
pthread_mutexattr_getpshared 	Obtains a process-shared setting of a mutex attribute object
pthread_mutexattr_init 	Initializes a mutex attribute object
pthread_mutexattr_setprioceiling 	Sets the priority ceiling attribute of a mutex attribute object
pthread_mutexattr_setprotocol 	Sets the protocol attribute of a mutex attribute object
pthread_mutexattr_setpshared 	Sets the process-shared attribute of a mutex attribute object to either PTHREAD_PROCESS_SHARED or PTHREAD_PROCESS_PRIVATE
pthread_mutex_destroy 	Destroys a mutex
pthread_mutex_init 	Initializes a mutex with the attributes specified in the specified mutex attribute object
pthread_mutex_lock 	Locks an unlocked mutex
pthread_mutex_trylock 	Tries to lock a not tested
pthread_mutex_unlock 	Unlocks a mutex
pthread_once 	Ensures that init_routine will run just once regardless of how many threads in the process call it
pthread_self 	Obtains a thread handle of a calling thread
pthread_setcancelstate 	Sets a thread's cancelability state
pthread_setcanceltype 	Sets a thread's cancelability type
pthread_setschedparam 	Adjusts the scheduling policy and scheduling parameters of an existing thread
pthread_setspecific 	Sets the thread-specific data value associated with the specific key in the calling thread
pthread_sigmask 	Examines or changes the calling thread's signal mask
pthread_testcancel 	Requests that any pending cancellation request be delivered to the calling thread
