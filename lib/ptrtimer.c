#include <stdlib.h>
#include <stdio.h>
#include <ptrtimer.h>

ptrtimer *ptrtimer_init(long n)
{
  ptrtimer *id;
  id = malloc(sizeof(ptrtimer));
  id->n=n;
  if (id == NULL)
     return NULL;
  if(id->n>0)
    id->tx = malloc (n*sizeof(struct timespec));
  ptrtimer_reset(id);
  return id;
}
int ptrtimer_start(ptrtimer *id)
{
  clock_gettime(CLOCK_REALTIME,&id->t0);
  // printf("tv_sec:%ld  tv_nsec:%ld\n", id->t0.tv_sec, id->t0.tv_nsec);
  return 0;
}

int ptrtimer_lap(ptrtimer *id)
{
  ptrtimer_stop(id);
  ptrtimer_start(id);
  return 0;
}

int ptrtimer_stop(ptrtimer *id)
{
  double dt;
  clock_gettime(CLOCK_REALTIME,&id->t1);
  dt =(double)(id->t1.tv_sec - id->t0.tv_sec) + ((double)(id->t1.tv_nsec - id->t0.tv_nsec)*0.000000001d);
  id->timer += dt;
  if(dt > id->max)
    id->max = dt;
  if(dt < id->min)
    id->min = dt;

  if (id->n>0)
    if(id->count<id->n)
    {
      id->tx[id->count] = dt;
    }
  (id->count)++;
  if(id->count == 1)
    id->min=dt;
  return 0;
}

int ptrtimer_report(ptrtimer *id)
{
  printf("min:%3f max:%3f avg:%3f count: %ld \n",id->min,id->max,id->timer/(double)id->count,id->count);
  return 0;
}

int ptrtimer_reportLong(ptrtimer *id)
{
  long i, n;
  ptrtimer_report(id);
  if(id->count < id->n)
    n = id->count;
  else
    n = id->n;
  for(i = 0; i<n ; i++)
    printf("lap: %ld dt: %3f\n", i, id->tx[i]);
  return 0;
}

double ptrtimer_getavg(ptrtimer *id)
{
   return id->timer/(double)id->count;
}

int ptrtimer_reset(ptrtimer *id)
{
  int i;
  clock_gettime(CLOCK_REALTIME,&id->t0);
  id->t1.tv_sec = id->t0.tv_sec;
  id->t1.tv_nsec = id->t0.tv_nsec;
  id->count = 0;
  id->timer = 0.0;
  id->max = 0.0;
  id->min = 0.0;
  if(id->n>0)
  { 
    for( i = 0; i<id->n ; i++)
    { 
      id->tx[i] = 0.0;
    }
  }
return 0;
}

int ptrtimer_close(ptrtimer *id)
{
  if(id->n>0)
    free(id->tx);
  free(id);
  return 0;
}
