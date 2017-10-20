#include <time.h>
typedef struct
{
  struct timespec t0;  // Start timer
  struct timespec t1;  // Stop timer
  long n;              // How long many lap samples
  double *tx; // lap timer
  double timer;        // Total time
  long count;          // Number of periods
  double min;          // Min loop time
  double max;          // Max loop time
}ptrtimer;

ptrtimer *ptrtimer_init(long n);
int ptrtimer_start(ptrtimer *id);
int ptrtimer_lap(ptrtimer *id);
int ptrtimer_stop(ptrtimer *id);
int ptrtimer_report(ptrtimer *id);
int ptrtimer_reportLong(ptrtimer *id);
double ptrtimer_getavg(ptrtimer *id);
int ptrtimer_reset(ptrtimer *id);
int ptrtimer_close(ptrtimer *id);
