#include <Arduino.h>
#include "AudioTools.h"
#include "AudioLibs/AudioA2DP.h"
#include "AudioLibs/AudioSourceSPIFFS.h"
#include "AudioCodecs/CodecMP3Helix.h"

const char *startFilePath="/";
const char* ext="mp3";
AudioSourceSPIFFS source(startFilePath, ext);
A2DPStream out;
MP3DecoderHelix decoder;
AudioPlayer player(source, out, decoder);

void printMetaData(MetaDataType type, const char* str, int len){
  Serial.print("==> ");
  Serial.print(toStr(type));
  Serial.print(": ");
  Serial.println(str);
}

void setup() {
  Serial.begin(115200);
  AudioLogger::instance().begin(Serial, AudioLogger::Info);

  SPIFFS.begin(true);

  // setup output - We send the test signal via A2DP - so we conect to the "LEXON MINO L" Bluetooth Speaker
  auto cfg = out.defaultConfig(TX_MODE);
  cfg.name = "Sonos";
//  cfg.auto_reconnect = true;  // if this is use we just quickly connect to the last device ignoring cfg.name
  out.begin(cfg);

  // setup player
  player.setVolume(1);
  player.begin();
}

void loop() {
  player.copy();
}