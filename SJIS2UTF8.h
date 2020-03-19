#pragma once

#include <Arduino.h>

bool convertSjis2UTF8(uint32_t max_len, char *str_sjis, char *str_utf8);
