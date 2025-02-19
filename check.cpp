#include "mbed.h"

// ピンの設定 (mbedボードに合わせて変更)
UnbufferedSerial pc(D5, D4, 9600); // TX, RXピンとボーレートの設定

int main() {
    char buffer[128]; // データを格納するバッファ
    size_t buffer_index = 0; // バッファのインデックス

    while (true) {
        // データが受信されるまで待機
        if (pc.readable()) {
            char c;
            // 1バイト読み込み
            pc.read(&c, 1);

            // 改行文字が来たらバッファの内容を表示し、バッファをクリア
            if (c == '\n' || c == '\r') {
                buffer[buffer_index] = '\0'; // 文字列の終端
                printf("Received: %s\n", buffer);
                buffer_index = 0; // バッファのインデックスをリセット
            } else {
                // バッファにデータを格納
                if (buffer_index < sizeof(buffer) - 1) {
                    buffer[buffer_index++] = c;
                }
            }
        }
    }
}
