#include "amichat_stream.h"
#include <assert.h>
#include <string.h>
static int cb(const char *d,size_t n,int f,void *u){int *c=(int*)u;(*c)++;assert(d);assert(n==5);assert(strcmp(d,"hello")==0);assert(f==1);return 1;}
int main(void){AmiChatStream s;int c=0;AmiChat_StreamInit(&s,cb,&c);assert(AmiChat_StreamEmit(&s,"hello",5,1)==AMICHAT_OK);assert(c==1);AmiChat_StreamCancel(&s);assert(AmiChat_StreamEmit(&s,"hello",5,0)==AMICHAT_ERR_CANCELLED);return 0;}
