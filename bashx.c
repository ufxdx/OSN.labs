/* Program that implements the basic functionality of the shell (bash), */
/* written on the course of lectures "Operating Systems and Networks".  */

#define _GNU_SOURCE
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define MAXARG 17
#define MAXLENGTH 80

int main() {
  for(;;){
    putchar('$');
    char newL, *argv[MAXARG], buffer[MAXLENGTH];
    int i = 0, thing = 0;

      do{
          thing = scanf("%79s%c", buffer, &newL);
          if((thing == EOF) || (i == 15)) {
            argv[i] = NULL;
            break;
          }
          argv[i] = (char*) malloc(thing*sizeof(char));
          strcpy(argv[i], buffer);
          if(newL == '\n'){
            argv[i+1] = NULL;
            break;
          }
          i++;
      }while(thing != EOF);

          if(thing == EOF) {
            for (int j = 0; j<=i; j++){
              free(argv[j]);
            }
              return EXIT_SUCCESS;
          }

          pid_t pid = fork();
          if(!pid) {
            if(execvp(argv[0], argv) == -1) {
              perror("execvp_err");
            }
          }
          pid = wait(NULL);
      		if(pid == -1) {
      			perror("wait_err");
      		}
          for(int j = 0; j <= i; j++){
      				free(argv[j]);
            }
      }
  }
