#include <czmq.h>

struct message
{
    unsigned long long x;
};

struct messagefloat
{
    float x;
    float y;
    float z;
};

void signalHandler(int signal_value);

void* bindpub(void* context, char* socket)
{
    void* publisher = zmq_socket(context, ZMQ_PUB);
    int rc = zmq_bind(publisher, socket);
    assert(rc == 0);
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

void startmsg(void* pub, int* keepLooping)
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
        printf("Sending %llu\r", currmsg.x);
        i++;
    }
}

void pubmsg(void* pub, float values[3]) {
    struct messagefloat currmsg;
    currmsg.x = values[0];
    currmsg.y = values[1];
    currmsg.z = values[2];
    zmq_msg_t msg;
    int framesize = sizeof(currmsg);
    zmq_msg_init_size(&msg, framesize);
    memcpy(zmq_msg_data(&msg), &currmsg, framesize);

    //struct message test;
    //memcpy(&test, zmq_msg_data(&msg), sizeof(test));
    //printf("Wrap: %f, %f, %f\r", test.x, test.y, test.z);
    
    zmq_msg_send(&msg, pub, ZMQ_DONTWAIT);
}

void cleanup(void* pub, void* context)
{
    printf("\nClosing the program\n");
    zmq_close(pub);
    zmq_ctx_destroy(context);
}
