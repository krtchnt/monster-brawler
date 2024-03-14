#pragma once

#include <PubSubClient.h>

#include "include/broker_config.h"

extern const String TOPIC_DAMAGE;

extern PubSubClient mqtt;

void setup_iot();