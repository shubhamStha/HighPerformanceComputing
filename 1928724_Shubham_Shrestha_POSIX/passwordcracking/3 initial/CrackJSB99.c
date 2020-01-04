#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>
#include <math.h>
/******************************************************************************
 *
 * To compile:
 *   cc -o CrackJSB99 CrackJSB99.c -lm
 *
 * To run:
 *   ./CrackJSB99
 *
 *Shubham Shrestha
 *****************************************************************************/
int n_passwords = 4;

char *encrypted_passwords[] = {
  "$6$KB$i2I9tTsR57XSltwTDy.wYRUX8e28uk2ngZoC9Cg5U/uKTUO/L/PjtA/VIALFVxtB0P.XGmS3bm/ZpQJr9n9LU0",
  "$6$KB$Vcm6TkAHH9437hFT9oUN2gbSUERwyMGAKMNIFWWmSivXImao9fDkWzCHgc8jvb2r86cZbjp4QURH8RLSel6GG/",
  "$6$KB$qQTi2V6gYpi3yk1KcQtRGZUjlTCWhfmTPDv5AIGarCjVZrHBw3mKG9TBd7GeudeHI70c3pipajdWqhjht1TI8/",
  "$6$KB$CRPS9qs.4vF0eOoJwis03SerIK.UTK/9FLPVmQw3wke9QzUY.FBGgVk7LuNsDWNW6K4D/nPWPCVODlV0/EbUm."
};


void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}


void crack(char *salt_and_encrypted){
  int a, b, c, d;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0
  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);

  for(a='A'; a<='Z'; a++){
    for(b='A'; b<='Z'; b++){
      for(c='A'; c<='Z'; c++){
	for(d=0; d<=99; d++){
        sprintf(plain, "%c%c%c%02d", a, b, c, d);
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);

	  }else{printf("%-8d%s %s\n", count, plain, enc);}
        }
      }
    }
  }
  printf("%d solutions explored\n", count);
}

int time_difference(struct timespec *start, struct timespec *finish,
                              long long int *difference) {
  long long int ds =  finish->tv_sec - start->tv_sec;
  long long int dn =  finish->tv_nsec - start->tv_nsec;

  if(dn < 0 ) {
    ds--;
    dn += 1000000000;
  }
  *difference = ds * 1000000000 + dn;
  return !(*difference > 0);
}


int main(int argc, char *argv[]){
  struct timespec start, finish;
  long long int time_elapsed;

  clock_gettime(CLOCK_MONOTONIC, &start);
  int i;

  for(i=0;i<n_passwords;i<i++) {
    crack(encrypted_passwords[i]);
  }

   clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed,
         (time_elapsed/1.0e9));

  return 0;
}
