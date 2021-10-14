#include <czmq.h>

struct message
{
    unsigned long long x;
};

void signalHandler(int signal_value);

void* bindpub(void* context, char* socket)
{
    void* publisher = zmq_socket(context, ZMQ_PUB);
    int rc = zmq_bind(publisher, socket);
    printf("Publisher connected\n");
    return publisher;
}

void* connectsub(void* context, char* socket)
{
    void* subscriber = zmq_socket(context, ZMQ_SUB);
    int rc = zmq_connect(subscriber, socket);
    const char* filter = "";
    rc = zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, filter, strlen(filter));
    printf("Subscriber connected, waiting for other publisher\n");
    return subscriber;
}

void startmsg(void* pub, void* sub, int* keepLooping)
{
    signal(SIGINT, signalHandler);
    unsigned long long i = 0;
    while (*keepLooping)
    {
        // Send message
        struct message currmsg;
        currmsg.x = i;
        zmq_msg_t msg;
        int framesize = sizeof(currmsg);
        zmq_msg_init_size(&msg, framesize);
        memcpy(zmq_msg_data(&msg), &currmsg, framesize);
        zmq_msg_send(&msg, pub, ZMQ_DONTWAIT);
        i++;

        // Receive message
        zmq_msg_t recv_msg;
        zmq_msg_init(&recv_msg);
        int size = zmq_msg_recv(&recv_msg, sub, ZMQ_DONTWAIT);
        if (size != -1)
        {
            struct message recv_msg_struct;
            memcpy(&recv_msg_struct, zmq_msg_data(&recv_msg), sizeof(recv_msg_struct));
            printf("%llu\r", recv_msg_struct.x);
        }
        zmq_msg_close(&recv_msg);
    }
}

void cleanup(void* pub, void* sub, void* context)
{
    printf("\nClosing the program\n");
    zmq_close(pub);
    zmq_close(sub);
    zmq_ctx_destroy(context);
}
