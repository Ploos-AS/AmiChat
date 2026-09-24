#include "amichat_worker.h"
#include "amichat_config.h"
#include <assert.h>
#include <string.h>

typedef struct Seen {
    AmiChatWorker *worker;
    int chunks;
    int done;
    int cancelled;
    int errors;
    AmiChatResult result;
} Seen;

static AmiChatResult fake(AmiChatTransport *t, const AmiChatTransportRequest *r,
                          AmiChatTransportResponse *p)
{
    const char *a = "data: {\"choices\":[{\"delta\":{\"content\":\"one\"}}]}\n\n";
    const char *b = "data: {\"choices\":[{\"delta\":{\"content\":\"two\"}}]}\n\n";
    AmiChatResult e;
    (void)t;
    p->status_code = 200;
    p->body = 0;
    p->content_type = "text/event-stream";
    e = r->body_callback(a, strlen(a), r->body_userdata);
    if (e != AMICHAT_OK)
        return e;
    return r->body_callback(b, strlen(b), r->body_userdata);
}

static void event_cb(const AmiChatWorkerEvent *e, void *u)
{
    Seen *s = (Seen *)u;
    if (e->type == AMICHAT_WORKER_CHUNK) {
        s->chunks++;
        if (s->chunks == 1)
            AmiChat_WorkerCancel(s->worker);
    } else if (e->type == AMICHAT_WORKER_DONE) {
        s->done++;
    } else if (e->type == AMICHAT_WORKER_CANCELLED) {
        s->cancelled++;
        s->result = e->result;
    } else if (e->type == AMICHAT_WORKER_ERROR) {
        s->errors++;
        s->result = e->result;
    }
}

int main(void)
{
    static const AmiChatTransportOps ops = { fake, 0 };
    AmiChatTransport tr = { &ops, 0 };
    AmiChatSession *session = AmiChat_SessionCreate(&tr);
    AmiChatConfig *config;
    AmiChatWorker *worker;
    Seen seen;
    AmiChatResult result;

    assert(session);
    config = AmiChat_SessionConfig(session);
    assert(AmiChat_ConfigSetProvider(config, "openrouter") == AMICHAT_OK);
    assert(AmiChat_ConfigSetModel(config, "m") == AMICHAT_OK);
    assert(AmiChat_SessionApplyConfig(session) == AMICHAT_OK);

    memset(&seen, 0, sizeof(seen));
    worker = AmiChat_WorkerCreate(session, event_cb, &seen);
    assert(worker);
    seen.worker = worker;

    result = AmiChat_WorkerSend(worker, "hello");
    assert(result == AMICHAT_ERR_CANCELLED);
    assert(seen.chunks == 1);
    assert(seen.done == 0);
    assert(seen.cancelled == 1);
    assert(seen.errors == 0);
    assert(seen.result == AMICHAT_ERR_CANCELLED);
    assert(AmiChat_WorkerBusy(worker) == 0);
    assert(AmiChat_WorkerState(worker) == AMICHAT_WORKER_CANCELLED_STATE);

    AmiChat_WorkerDestroy(worker);
    AmiChat_SessionDestroy(session);
    return 0;
}
