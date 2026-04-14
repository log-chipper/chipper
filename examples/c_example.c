#include "../clients/c/chipper_client.h"

int main(void) {
    if (chipper_client_init("/tmp/chipper.sock", "myapp", "worker") != 0) {
        return 1;
    }

    chipper_client_log("info", "hello from C client, user_id=%d", 42);
    chipper_client_log("error", "something failed: %s", "oops");

    chipper_client_close();
    return 0;
}
