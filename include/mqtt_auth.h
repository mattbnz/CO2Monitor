#ifndef _MQTT_AUTH_H
#define _MQTT_AUTH_H

// Haven't seen one bigger than ~1700bytes
#define PEM_BUFLEN 2048

namespace mqtt {
  bool initKey();
}

#endif