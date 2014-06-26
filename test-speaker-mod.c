#include <kilolib.h>

// declare variables
uint32_t last_changed = 0;
uint8_t message_sent = 0;
uint8_t odd = 0;
message_t messages[2];

void setup() {
    // initialize even an odd messages
    messages[0].data[0] = 0;
    messages[0].type = NORMAL;
    messages[0].crc = message_crc(&messages[0]);
    messages[1].data[0] = 1;
    messages[1].type = NORMAL;
    messages[1].crc = message_crc(&messages[1]);
}

void loop() {
    // switch message sent every 2 seconds (64 ticks)
    if (kilo_ticks > last_changed + 64) {
        last_changed = kilo_ticks;
        odd = !odd;
    }

    // blink led magenta on message sent
    if (message_sent) {
        message_sent = 0;
        set_color(RGB(1,0,1));
        delay(100);
        set_color(RGB(0,0,0));
    }
}

message_t *message_tx() {
    return &messages[odd];
}

void message_tx_succes() {
    message_sent = 1;
}

int main() {
    kilo_init();
    kilo_message_tx = message_tx;
    kilo_message_tx_success = message_tx_succes;
    kilo_start(setup, loop);

    return 0;
}