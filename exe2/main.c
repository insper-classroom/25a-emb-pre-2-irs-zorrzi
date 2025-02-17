#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN = 28;
const int LED_PIN = 4;

volatile int btn_flag = 0;

void btn_callback(uint gpio, uint32_t events) {
  if (events & GPIO_IRQ_EDGE_FALL) {
      btn_flag = 1;
  }
}

int main() {
  stdio_init_all();

  gpio_init(BTN_PIN);
  gpio_set_dir(BTN_PIN, GPIO_IN);
  gpio_pull_up(BTN_PIN);

  // LED
  gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);

  gpio_set_irq_enabled_with_callback(
    BTN_PIN, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &btn_callback);


  int led_state = 0;

  while (true) {
    if (btn_flag == 1){
      btn_flag = 0;
      led_state = !led_state;
  
      gpio_put(LED_PIN, led_state);
    }
  }


}