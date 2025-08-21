#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

TaskHandle_t myTaskHandle = NULL; 
TaskHandle_t myTaskHandle2 = NULL;

void Demo_Task(void *arg) // Function to be executed by the task
{
    int count = 0;
    while(1){
        count++;
        printf("Demo_Task printing..\n"); 
        vTaskDelay(1000/ portTICK_PERIOD_MS);
        if (count == 5)
        {
          vTaskDelete(myTaskHandle2);
          printf("Demo_Task2 is deleted!\n");
        }
    }
}

void Demo_Task2(void *arg)
{
    for (int i = 0; i < 5; i++) {
        printf("Demo_Task2 printing..\n"); // Function to be executed by the second task
        vTaskDelay(1000/ portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
   xTaskCreate(Demo_Task, "Demo_Task", 4096, NULL, 10, &myTaskHandle); // Create the first task
   xTaskCreatePinnedToCore(Demo_Task2, "Demo_Task2", 4096, NULL,10, &myTaskHandle2, 1);  // Create the second task pinned to core 1
 }