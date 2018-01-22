/*
This version is for pigpio version 3+
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>

#include <pigpio/pigpio.h>

/*
This software converts pigpio notification reports
into a VCD format understood by GTKWave.
*/

#define RS (sizeof(gpioReport_t))

static char * timeStamp()
{
   static char buf[32];

   struct timeval now;
   struct tm tmp;

   gettimeofday(&now, NULL);

   localtime_r(&now.tv_sec, &tmp);
   strftime(buf, sizeof(buf), "%F %T", &tmp);

   return buf;
}

int symbol(int bit)
{
   if (bit < 26) return ('A' + bit);
   else          return ('a' + bit - 26);
}

int main(int argc, char * argv[])
{
   int b, r, v;
   uint32_t t0;
   uint32_t lastLevel, changed;

   gpioReport_t report;

   r=read(STDIN_FILENO, &report, RS);

   if (r != RS) exit(-1);

   printf("$date %s $end\n", timeStamp());
   printf("$version pig2vcd V1 $end\n");
   printf("$timescale 1 us $end\n");
   printf("$scope module top $end\n");

   for (b=0; b<32; b++)
      printf("$var wire 1 %c %d $end\n", symbol(b), b);
        
   printf("$upscope $end\n");
   printf("$enddefinitions $end\n");
         
   t0 = report.tick;
   lastLevel =0;

   while ((r=read(STDIN_FILENO, &report, RS)) == RS)
   {
      if (report.level != lastLevel)
      {
         printf("#%u\n", report.tick - t0);

         changed = report.level ^ lastLevel;

         lastLevel = report.level;

         for (b=0; b<32; b++)
         {
            if (changed & (1<<b))
            {
               if (report.level & (1<<b)) v='1'; else v='0';

               printf("%c%c\n", v, symbol(b));
            }
         }
      }
   }
   return 0;
}

