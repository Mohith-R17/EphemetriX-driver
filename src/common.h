#pragma once

#pragma pack(push, 1)

struct IMUPacket {
  float w;
  float x;
  float y;
  float z;

  float ax;
  float ay;
  float az;
};

#pragma pack(pop)
