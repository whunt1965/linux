/*
 * ukl.h
 *
 * Copyright (C) 2018, Ali Raza <aliraza@bu.edu>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include <trace/events/printk.h>
#include <asm/unistd.h>
#include <linux/fs.h>
#include <linux/file.h>
#include <linux/string.h>
#include <linux/mm.h>
#include <linux/fdtable.h>
#include <linux/fsnotify.h>
#include <linux/module.h>
#include <linux/tty.h>
#include <linux/namei.h>
#include <linux/backing-dev.h>
#include <linux/capability.h>
#include <linux/securebits.h>
#include <linux/security.h>
#include <linux/mount.h>
#include <linux/fcntl.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/personality.h>
#include <linux/pagemap.h>
#include <linux/syscalls.h>
#include <linux/rcupdate.h>
#include <linux/audit.h>
#include <linux/falloc.h>
#include <linux/fs_struct.h>
#include <linux/ima.h>
#include <linux/dnotify.h>
#include <linux/compat.h>
#include <linux/gfp.h>
#include <linux/utsname.h>
#include <linux/sched/task.h>
#include <linux/signal.h>
#include <linux/signal_types.h>

#include <linux/socket.h>
#include <uapi/linux/in.h>

#include <asm/socket.h>			/* arch-dependent defines	*/
#include <linux/sockios.h>		/* the SIOCxxx I/O controls	*/
#include <linux/uio.h>			/* iovec support		*/
#include <linux/types.h>		/* pid_t			*/
#include <linux/compiler.h>		/* 			*/
#include <uapi/linux/socket.h>

#include <net/sock.h>

#include <asm/proto.h>
#include <asm/prctl.h>
#include <asm/desc.h>
#include <asm/segment.h>

#include <linux/mman.h>
#include <linux/sys.h>
#include <linux/futex.h>
#include <linux/sched/mm.h>
#include <vdso/vsyscall.h>
#include <vdso/datapage.h>
#include <asm/vdso/gettimeofday.h>

void enter_ukl(void);
void exit_ukl(void);
void printukl(const char *fmt, ...);

ssize_t ukl_write(int fd, const void* buf, size_t count);
ssize_t ukl_read(int fd, const void* buf, size_t count);
long ukl_open(const char* filename, int flags, unsigned short mode);
long ukl_close(int fd);
void ukl_exit_group(int error_code);
int ukl_socket(int family, int type, int protocol);
int ukl_bind(int fd, struct sockaddr  *umyaddr, int addrlen);
int ukl_connect(int fd, struct sockaddr  *uservaddr, int addrlen);
int ukl_listen(int fd, int backlog);
int ukl_accept(int fd, struct sockaddr *upeer_sockaddr, int *upeer_addrlen);
int ukl_ioctl(int fd, int cmd, long arg);
int ukl_recvfrom(int fd, void  *ubuf, size_t size, unsigned int flags, struct sockaddr  *addr, int  *addr_len);
int ukl_sendto(int fd, void *buff, size_t len, unsigned int flags, struct sockaddr *addr, int addr_len);
int ukl_recv(int fd, void  *ubuf, size_t size, unsigned int flags);
int ukl_send(int fd, void *buff, size_t len, unsigned int flags);
int ukl_setsockopt(int fd, int level, int optname, char *optval, int optlen);
long ukl_arch_prctl(int option, unsigned long arg2);
int ukl_get_thread_area(struct user_desc  *u_info);
int ukl_set_thread_area(struct user_desc  *u_info);
unsigned long ukl_mmap(unsigned long addr, unsigned long len, unsigned long prot, unsigned long flags, unsigned long fd, unsigned long off);
int ukl_set_tid_address(int * tidptr);
int ukl_set_robust_list(struct robust_list_head * head, size_t len);
int ukl_rt_sigprocmask(int how, sigset_t * nset,  sigset_t * oset, size_t sigsetsize);
int ukl_rt_sigaction(int sig, const struct sigaction * act, struct sigaction * oact, size_t sigsetsize);
int ukl_prlimit64(pid_t pid, unsigned int resource, const struct rlimit64 * new_rlim, struct rlimit64 * old_rlim);
unsigned long ukl_brk(unsigned long brk);
int ukl_fstat(unsigned int fd, struct stat  * statbuf);
int ukl_mprotect(unsigned long start, size_t len, unsigned long prot);
long ukl_clone(unsigned long clone_flags, unsigned long newsp, int * parent_tidptr, unsigned long tls, int * child_tidptr);
int ukl_munmap(unsigned long addr, size_t len);
void ukl_exit(int error_code);
long ukl_futex(unsigned int  * uaddr, int op, unsigned int  val, struct __kernel_timespec * utime, unsigned int  * uaddr2, unsigned int  val3);
int ukl_setrlimit (unsigned int  resource, const struct rlimit* rlim);
int ukl_clock_gettime(const clockid_t which_clock, struct __kernel_timespec * tp);
int ukl_gettimeofday(struct timeval* tv, struct timezone* tz);
int ukl_epoll_create1(int flags);
int ukl_pipe2(int* fildes, int flags);
time_t ukl_time (time_t *t);
int ukl_fcntl(unsigned int fd, unsigned int cmd, unsigned long arg);
int ukl_epoll_ctl(int epfd, int op, int fd, struct epoll_event* event);
int ukl_epoll_wait(int epfd, struct epoll_event * events, int maxevents, int timeout);
int ukl_nanosleep(struct __kernel_timespec *rqtp, struct __kernel_timespec *rmtp);
int ukl_mlock(long start, size_t len);
int ukl_mlock2(long start, size_t len, int flags);
int ukl_tgkill(pid_t tgid, pid_t pid, int sig);
pid_t ukl_getpid(void);
pid_t ukl_gettid(void);
int ukl_sendmmsg(int fd, struct mmsghdr *mmsg, unsigned int vlen, unsigned int flags);
long ukl_mknod(const char * filename, umode_t mode, unsigned int dev);
int ukl_mount(char * dev_name, char * dir_name, char * type, unsigned long flags, void * data);
int ukl_chroot(const char * filename);
int ukl_chdir(const char * filename);
long ukl_openat(int dfd, const char * filename, int flags, umode_t mode);
int ukl_getsockopt(int fd, int level, int optname, char  * optval, int * optlen);
long ukl_mkdir(const char *pathname, umode_t mode);
void ukl_sync(void);
int ukl_select(int n, fd_set  * inp, fd_set  * outp, fd_set  * exp, struct __kernel_old_timeval  * tvp);
int ukl_poll(struct pollfd * ufds, unsigned int nfds, int timeout_msecs);
int ukl_sysinfo(struct sysinfo * info);
int ukl_epoll_create(int size);
int ukl_renameat2(int olddfd, const char *oldname, int newdfd, const char *newname, unsigned int flags);
int ukl_renameat(int olddfd, const char *oldname, int newdfd, const char *newname);
int ukl_rename(const char *oldname, const char *newname);
int ukl_getrusage(int who, struct rusage * ru);
int ukl_epoll_pwait(int epfd, struct epoll_event* events, int maxevents, int timeout, const sigset_t * sigmask, size_t sigsetsize);
uid_t ukl_getuid(void);
uid_t ukl_geteuid(void);
gid_t ukl_getgid(void);
gid_t ukl_getegid(void);
off_t ukl_lseek(unsigned int fd, off_t offset, unsigned int whence);
int ukl_getsockname(int fd, struct sockaddr *usockaddr, int *usockaddr_len);
long ukl_recvmsg(int fd, struct user_msghdr *msg, unsigned int flags);
int ukl_accept4(int fd, struct sockaddr *upeer_sockaddr, int *upeer_addrlen, int flags);
int ukl_getpeername(int fd, struct sockaddr *usockaddr, int *usockaddr_len);
int ukl_kill(pid_t pid, int sig);
int ukl_rt_sigsuspend(sigset_t * unewset, size_t sigsetsize);
int ukl_sigaltstack (const stack_t *uss, stack_t *uoss);
ssize_t ukl_getrandom(char * buf, size_t count, unsigned int flags);
int ukl_settimeofday(struct __kernel_old_timeval * tv, struct timezone * tz);
int ukl_getitimer(int which, struct itimerval * value);




