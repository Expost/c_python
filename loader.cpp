#include <stdio.h>
#include <dlfcn.h>

int main()
{
    int (*init_func)();
    int (*on_recv_func)();

    void *handle = dlopen("./replaysvr.so", RTLD_LAZY);
    if (!handle)
    {
        printf("handle is null\n");
        return -1;
    }

    init_func = (int (*)())dlsym(handle, "init");
    if (!init_func)
    {
        printf("init func is null with error %s\n", dlerror());
        return -1;
    }

    init_func();

    on_recv_func = (int (*)())dlsym(handle, "on_recv");
    if (!on_recv_func)
    {
        printf("on_recv_func is null with error %s\n", dlerror());
        return -1;
    }

    on_recv_func();

    dlclose(handle);
    return 0;
}