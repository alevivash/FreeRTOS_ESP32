#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "driver/gpio.h"

#define ESP_INRTERRUPT_FLAG_DEFAULT 0
#define LED_PIN 27
#define PUSH_BUTTON_PIN 33

TaskHandle_t ISR = NULL; //INTERRUPT SERVICE ROUTINE

void IRAM_ATTR button_isr_handler(void* arg) // Interrupt service routine
{
    xTaskResumeFromISR(ISR); // Resume the task from ISR
}

void interrupt_task(void* arg) // Task to handle the interrupt
{
    bool led_state = false;
    while(1) {
        vTaskSuspend(NULL); // Suspend the task until resumed by ISR
        led_state = !led_state;
        gpio_set_level(LED_PIN, led_state); // Toggle LED state
        printf("Button Pressed!\n");
    }
}

void app_main(void)
{
    // Configure LED pin
    esp_rom_gpio_pad_select_gpio(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(LED_PIN, 0); // Turn off LED initially

    // Configure push button pin
    esp_rom_gpio_pad_select_gpio(PUSH_BUTTON_PIN);
    gpio_set_direction(PUSH_BUTTON_PIN, GPIO_MODE_INPUT);
    gpio_set_pull_mode(PUSH_BUTTON_PIN, GPIO_PULLUP_ONLY); // Enable internal pull-up resistor

    // Create the interrupt handling task
    xTaskCreate(interrupt_task, "interrupt_task", 2048, NULL, 10, &ISR);

    // Install ISR service
    gpio_install_isr_service(ESP_INRTERRUPT_FLAG_DEFAULT);
    // Attach the interrupt service routine to the button pin
    gpio_isr_handler_add(PUSH_BUTTON_PIN, button_isr_handler, NULL);
}
