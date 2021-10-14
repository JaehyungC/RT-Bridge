#include "wrap.h"

static int keepLooping = 1;

void signalHandler(int signal_value)
{
    keepLooping = 0;
}

int main(void)
{
    void* context = zmq_ctx_new();
    void* pub = bindpub(context, "tcp://*:5555");
    void* sub = connectsub(context, "tcp://169.254.121.192:5556");
    startmsg(pub, sub, &keepLooping);
    cleanup(pub, sub, context);
    return 0;
}

/*int main(void)
{
    signal(SIGINT, signalHandler);

    void* context = zmq_ctx_new();
    void* publisher = zmq_socket(context, ZMQ_PUB);
    int rc = zmq_bind(publisher, "tcp://*:5555");
    printf("Publisher binding to socket!\n");
    assert(rc == 0);
    printf("Publisher connection successful!\n");

    unsigned long long i = 1;

    printf("Starting while loop for messaging!\n");

    while (keepLooping)
    {
        struct message currmsg;
        currmsg.x = i;

        zmq_msg_t msg;
        int framesize = sizeof(currmsg);
        zmq_msg_init_size(&msg, framesize);
        memcpy(zmq_msg_data(&msg), &currmsg, framesize);
        zmq_msg_send(&msg, publisher, ZMQ_DONTWAIT);



        i++;
    }

    printf("\nClosing the program!\n");
    zmq_close(publisher);
    zmq_ctx_destroy(context);

    return 0;
}*/