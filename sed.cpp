#include "mbed.h"

// PCとのシリアル通信用
UnbufferedSerial pc(USBTX, USBRX, 9600); // tx, rx

// D5, D4ピンに接続されたシリアル通信用
UnbufferedSerial device(D5, D4, 9600); // tx, rx

int main() {
    char c;
    while (true) {
        // PCからデータを受信し、デバイスに転送
        if (pc.readable()) {
            pc.read(&c, 1);
            device.write(&c, 1);
        }

        // デバイスからデータを受信し、PCに転送（必要に応じて）
        if (device.readable()) {
            device.read(&c, 1);
            pc.write(&c, 1);
        }
    }
}
