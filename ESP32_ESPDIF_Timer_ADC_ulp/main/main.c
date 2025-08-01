/* ULP Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.

   See https://github.com/platformio/platform-espressif32/tree/develop/examples/espidf-ulp-adc
*/

#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "my_ulp_adc.h"
#include "esp_sleep.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define max(a, b) (a > b ? a : b)

#define mS_TO_uS_FACTOR 1000ULL
#define TIME_TO_SLEEP 2000

void app_main(void)
{
    esp_sleep_wakeup_cause_t wakeup_reason = esp_sleep_get_wakeup_cause();
    switch (wakeup_reason)
    {
    case ESP_SLEEP_WAKEUP_UNDEFINED: // First run, initialize ULP program
        printf("First run: %d\n", wakeup_reason);
        init_ulp_program();
        break;

    case ESP_SLEEP_WAKEUP_TIMER:
        printf("Wakeup caused by Timer");
        // ***** HERE YOUR SKETCH *****
        break;

    case ESP_SLEEP_WAKEUP_ULP:
        printf("Wakeup caused by ULP program - ");
        // ***** HERE YOUR SKETCH *****
        printf("ULP did %" PRIu32 " measurements since last reset\n", ulp_sample_counter & UINT16_MAX);
        printf("Thresholds:  low=%" PRIu32 "  high=%" PRIu32 "\n", ulp_low_thr, ulp_high_thr);
        ulp_last_result &= UINT16_MAX;
        printf("Value=%" PRIu32 " was %s threshold\n", ulp_last_result,
               ulp_last_result < ulp_low_thr ? "below" : "above");
        break;

    default:
        printf("Wakeup was not caused by defined deep sleep mode: %d\n", wakeup_reason);
        break;
    }

    printf("\nEntering deep sleep\n");
    start_ulp_program();
    ESP_ERROR_CHECK(esp_sleep_enable_ulp_wakeup());

    // Activate and configure the timer wakeup source
    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * mS_TO_uS_FACTOR);

    esp_deep_sleep_start();
}