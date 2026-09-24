#include "amichat_transport_amiapi.h"
#include <amiapi/amiapi.h>
#include <stdlib.h>
#include <string.h>

typedef struct AmiAPITransportState {
    struct AmiAPIContext *ctx;
    char *body;
    char *content_type;
} AmiAPITransportState;

static char *copy_bytes(const unsigned char *data,size_t n)
{
    char *p=(char*)malloc(n+1);
    if(!p)return 0;
    if(n)memcpy(p,data,n);
    p[n]='\0';
    return p;
}

static void clear_response(AmiAPITransportState *s)
{
    free(s->body); s->body=0;
    free(s->content_type); s->content_type=0;
}

static AmiChatResult map_error(enum AmiAPIError e)
{
    if(e==AMIAPI_OK)return AMICHAT_OK;
    return AMICHAT_ERR_NETWORK;
}

static AmiChatResult request_fn(AmiChatTransport *transport,
                                const AmiChatTransportRequest *request,
                                AmiChatTransportResponse *response)
{
    AmiAPITransportState *s;
    struct AmiAPIRequest *r;
    struct AmiAPIResponse *rp;
    enum AmiAPIError e;
    const char *ct;
    const char *h,*line,*colon;
    char name[128],value[768];
    size_t n,v;

    if(!transport||!request||!response||!request->method||!request->url)
        return AMICHAT_ERR_INVALID_ARGUMENT;
    s=(AmiAPITransportState*)transport->userdata;
    if(!s||!s->ctx)return AMICHAT_ERR_INVALID_ARGUMENT;
    clear_response(s);
    r=AmiAPI_RequestCreate(s->ctx,request->method,request->url);
    if(!r)return map_error(AmiAPI_LastError(s->ctx));

    h=request->headers;
    while(h&&*h){
        line=strstr(h,"\r\n");
        if(!line)line=h+strlen(h);
        colon=(const char*)memchr(h,':',(size_t)(line-h));
        if(colon){
            n=(size_t)(colon-h);
            while(n&&h[n-1]==' ')n--;
            v=(size_t)(line-colon-1);
            while(v&&colon[1]==' '){colon++;v--;}
            if(n<sizeof(name)&&v<sizeof(value)){
                memcpy(name,h,n);name[n]='\0';
                memcpy(value,colon+1,v);value[v]='\0';
                e=AmiAPI_RequestSetHeader(r,name,value);
                if(e!=AMIAPI_OK){AmiAPI_RequestDestroy(r);return map_error(e);}
            }
        }
        h=*line?line+2:line;
    }

    if(request->body){
        e=AmiAPI_RequestSetBody(r,request->body,strlen(request->body));
        if(e!=AMIAPI_OK){AmiAPI_RequestDestroy(r);return map_error(e);}
    }

    rp=AmiAPI_RequestExecute(r);
    if(!rp){e=AmiAPI_LastError(s->ctx);AmiAPI_RequestDestroy(r);return map_error(e);}
    response->status_code=(long)AmiAPI_Status(rp);
    if(AmiAPI_Body(rp)){
        s->body=copy_bytes(AmiAPI_Body(rp),AmiAPI_BodySize(rp));
        if(!s->body){AmiAPI_FreeResponse(rp);AmiAPI_RequestDestroy(r);return AMICHAT_ERR_NOMEM;}
    }
    ct=AmiAPI_Header(rp,"Content-Type");
    if(ct){s->content_type=copy_bytes((const unsigned char*)ct,strlen(ct));if(!s->content_type){AmiAPI_FreeResponse(rp);AmiAPI_RequestDestroy(r);return AMICHAT_ERR_NOMEM;}}
    response->body=s->body;
    response->content_type=s->content_type;
    AmiAPI_FreeResponse(rp);
    AmiAPI_RequestDestroy(r);
    return AMICHAT_OK;
}

static void destroy_fn(AmiChatTransport *transport)
{
    AmiAPITransportState *s;
    if(!transport)return;
    s=(AmiAPITransportState*)transport->userdata;
    if(s){clear_response(s);if(s->ctx)AmiAPI_Destroy(s->ctx);free(s);}
    free(transport);
}

static const AmiChatTransportOps ops={request_fn,destroy_fn};

AmiChatTransport *AmiChat_AmiAPITransportCreate(void)
{
    AmiChatTransport *t=(AmiChatTransport*)calloc(1,sizeof(*t));
    AmiAPITransportState *s;
    if(!t)return 0;
    s=(AmiAPITransportState*)calloc(1,sizeof(*s));
    if(!s){free(t);return 0;}
    s->ctx=AmiAPI_Create();
    if(!s->ctx){free(s);free(t);return 0;}
    t->ops=&ops;t->userdata=s;
    return t;
}
