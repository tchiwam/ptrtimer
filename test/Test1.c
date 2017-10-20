#include "config.h"
#include <ptrtimer.h>

#include <unistd.h>
#include <stdio.h>
#include <time.h>

int main (int argc, char *argv[])
{
  long i,j;
  struct timespec t;
  fprintf(stdout,"Usage: %s \n",argv[0]);
  clock_gettime(CLOCK_REALTIME,&t);
  printf("tv_sec:%ld  tv_nsec:%ld\n", t.tv_sec, t.tv_nsec);

  ptrtimer *id,*id2;
  id = ptrtimer_init(10);
  id2 = ptrtimer_init(20);
  for(j=0;j<10;j++)
  {
    printf("Loop1\n");
    ptrtimer_start(id2);
    for(i=0; i<10; i ++)
    {
      ptrtimer_start(id);
      usleep(100000);
      ptrtimer_stop(id);
    }
    ptrtimer_stop(id2);

    printf("Loop2\n");
    ptrtimer_start(id2);
    for(i=0; i<10; i ++)
    {
      ptrtimer_start(id);
      usleep(100000);
      ptrtimer_stop(id);
    }
    ptrtimer_stop(id2);
  }

  printf("Reports\n");
  ptrtimer_report(id);
  ptrtimer_report(id2);
  ptrtimer_reportLong(id2);

  ptrtimer_close(id);
  ptrtimer_close(id2);

  clock_gettime(CLOCK_REALTIME,&t);
  printf("tv_sec:%ld  tv_nsec:%ld\n", t.tv_sec, t.tv_nsec);

  return 0;
}
