#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define LED_GPIO GPIO_NUM_2
#define BLINK_DELAY_MS 1000

static const char *TAG = "blink_c";

void app_main(void)
{
    // Configure the IOMUX/GPIO for the LED pin
    gpio_reset_pin(LED_GPIO);
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_level(LED_GPIO, 0);

    ESP_LOGI(TAG, "ESP-IDF blink example started");

    while (1) {
        // Toggle LED
        gpio_set_level(LED_GPIO, 1);
        ESP_LOGI(TAG, "LED ON");
        vTaskDelay(pdMS_TO_TICKS(BLINK_DELAY_MS));

        gpio_set_level(LED_GPIO, 0);
        ESP_LOGI(TAG, "LED OFF");
        vTaskDelay(pdMS_TO_TICKS(BLINK_DELAY_MS));
    }
}
