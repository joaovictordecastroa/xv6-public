//
// Created by joaov on 5/4/24.
//
#include "types.h"
#include "param.h"
#include "stat.h"
#include "user.h"

void sanity(int n) {
  int numProcesses = 3 * n;

  for (int i = 0; i < numProcesses; i++) {
    int pid = fork();

    if (pid > 0) // Father
    {
      pid = wait();
    } else if (pid == 0) { // Child
      if (getpid() % 3 == 0)  // CPU-BOUND
      {
        for (int j = 0; j < CPUBOUNDLOOPSIZE; j++) {
          for (int k = 0; k < CPUBOUNDITERACTIONS; k++) {
            // do-nothing
          }
        }

        printf(1, "CPU-BOUND %d process finished\n", getpid());

        exit();
      } else if (getpid() % 3 == 1) // S-CPU
      {
        for (int j = 0; j < SCPULOOPSIZE; j++) {
          for (int k = 0; k < SCPUITERACTIONS; k++) {
            // do-nothing
          }

          yield();
        }

        printf(1, "S-BOUND %d process finished\n", getpid());

        exit();
      } else if (getpid() % 3 == 2) {
        for (int l = 0; l < IOBOUNDINTERACTIONS; l++) {
          sleep(1);
        }

        printf(1, "IO-BOUND %d process finished\n", getpid());

        exit();
      } else {
        printf(1, "Process %d failed to fork\n", getpid());

        exit();
      }
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf(2, "Missing the number of programs in the arguments of function\n");

    exit();
  }

  int numProcesses = atoi(argv[1]);

  printf(1, "Running %d programs\n", numProcesses);

  sanity(numProcesses);

  exit();
}