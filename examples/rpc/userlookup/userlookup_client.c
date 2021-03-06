/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include <stdio.h>
#include "userlookup.h"

int
l_byname( char* host, char *name ) {
  CLIENT *clnt;
  uid_retval *rval;
  clnt = clnt_create(host, ULKUP_PROG, ULKUP_VERSION, "udp");
  if (clnt == NULL) {
    clnt_pcreateerror(host);
    exit(1);
  }
  rval = byname_1(&name, clnt);
  if (rval == NULL) {
    clnt_perror(clnt, "call failed:");
  }
  clnt_destroy( clnt );
  if (rval->found==NOTFOUND)
    return(-1);
  else
    return(rval->uid);
}


char *
l_bynum( char* host, int uid )
{
  CLIENT *clnt;
  uname_retval *rval;

  clnt = clnt_create(host, ULKUP_PROG, ULKUP_VERSION, "udp");
  if (clnt == NULL) {
    clnt_pcreateerror(host);
    exit(1);
  }

  rval = bynum_1(&uid, clnt);
  if (rval == NULL) {
    clnt_perror(clnt, "call failed:");
  }
  clnt_destroy( clnt );
  if (rval->found==NOTFOUND) 
    return(NULL);
  else
    return(rval->name);
	
}


int main( int argc, char* argv[] ) {
  char *host;
  char *name;
  int uid;
  char *uname;

  if(argc < 3) {
    printf("usage: %s server_host name_or_uid\n", argv[0]);
    exit(1);
  }
  host = argv[1];
  name = argv[2];
  if ((name[0]>='0')&&(name[0]<='9')) {
    uid = atoi(name);
    uname = l_bynum(host,uid);
    if (uname==NULL)
      printf("UID %d, no such UID\n",uid);
    else
      printf("UID %d, Name is %s\n",uid,uname);
  } else {
    uid = l_byname(host,name);
    if (uid==-1) 
      printf("Name %s, no such user\n",name);
	     else
      printf("Name %s, UID is %d\n",name,uid);
  }
  return(0);
}










