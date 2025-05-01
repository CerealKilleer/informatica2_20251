#include "esp_timer.h"

void setup()
{
  Serial.begin(115200);
  const esp_timer_create_args_t timer_args = {
    .callback = &timer_handler,
    .name = "Prueba"
  };
  esp_timer_handle_t periodic_timer;
  esp_timer_create(&timer_args, &periodic_timer);
  esp_timer_start_periodic(periodic_timer, 1000000);
}

void loop()
{
  while(true) {
    continue;
  }
}

void timer_handler(void *arg)
{
  Serial.println("Este texto está ejecutandose cada X tiempo");
}