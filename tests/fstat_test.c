#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

// int main ()
// {
// 	struct stat	st;
// 	int	no_exist_fd;
// 	int	dir_fd;
// 	int	r_only_fd;
// 	int	w_only_fd;

// 	no_exist_fd = open("no_exist", O_RDWR);
// 	dir_fd = open("prova", O_RDWR | __O_DIRECTORY);
// 	r_only_fd = open("r_only", O_RDONLY);
// 	w_only_fd = open("w_only", O_WRONLY);
// 	printf("no_exist_fd: %d\ndir_fd: %d\nr_only_fd: %d\nw_only_fd: %d\n", no_exist_fd, dir_fd, r_only_fd, w_only_fd);
// 	printf("\nNO_EXIST\n");
// 	printf("stat result: %d\n", stat("no_exist", &st));
// 	if (S_ISBLK(st.st_mode))
// 		printf("block device\n"); 
// 	else if(S_ISCHR(st.st_mode))
// 		printf("character device\n");
// 	else if(S_ISDIR(st.st_mode))
// 		printf("directory\n");
// 	else if(S_ISFIFO(st.st_mode))
// 		printf("FIFO/pipe\n");
// 	else if(S_ISLNK(st.st_mode))
// 		printf("symlink\n");
//         else if(S_ISREG(st.st_mode))
// 		printf("regular file\n");
//         else if(S_ISSOCK(st.st_mode))
// 		printf("socket\n");
// 	else
// 		printf("unknown?\n");

// }