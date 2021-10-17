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
    
    //startmsg(pub, &keepLooping);

    signal(SIGINT, signalHandler);
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;
    float temp[] = { x,y,z };
    while (keepLooping)
    {
        pubmsg(pub, temp);
        temp[0] += 0.5;
        temp[1] += 0.5;
        temp[2] += 0.5;
    }

    cleanup(pub, context);
    return 0;
}
