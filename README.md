# ESP32-TEST

ESP32 DevKitC v4 用の PlatformIO Arduino フレームワークプロジェクトです。

## 仕様

- 内蔵LED（GPIO 2）を使用
- 1秒（1000ms）間隔で LED を ON/OFF で点滅
- `setup()` でシリアル通信を 115200bps で開始
- `setup()` で `ESP32 Initialized.` を出力
- `loop()` で LED の状態が変わるたびに `LED ON` / `LED OFF` をシリアルモニタへ出力

## ソース

- `src/main.cpp`
- `platformio.ini`

## ビルド方法

```bash
python3 -m platformio run
```

## 出力ファームウェア

- `.pio/build/esp32dev/firmware.bin`

## ボード設定

- `platformio.ini` では `az-delivery-devkit-v4` を使用
