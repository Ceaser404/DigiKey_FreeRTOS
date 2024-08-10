//***********************************************Getting Started with FreeRTOS**********************************************************

// // Use only core 1 for demo purposes
// #if CONFIG_FREERTOS_UNICORE
// static const BaseType_t app_cpu = 0;
// #else
// static const BaseType_t app_cpu = 1;
// #endif

// // Pins
// static const int led_pin = LED_BUILTIN;

// // Our task: blink an LED
// void toggleLED(void *parameter) {
//   while(1) {
//     digitalWrite(led_pin, HIGH);
//     vTaskDelay(200 / portTICK_PERIOD_MS);
//     digitalWrite(led_pin, LOW);
//     vTaskDelay(200 / portTICK_PERIOD_MS);
//   }
// }

// // Our task: blink an LED
// void toggleLEDDiff(void *parameter) {
//   while(1) {
//     digitalWrite(led_pin, HIGH);
//     vTaskDelay(550 / portTICK_PERIOD_MS);
//     digitalWrite(led_pin, LOW);
//     vTaskDelay(125 / portTICK_PERIOD_MS);
//   }
// }

// void setup() {
  
//   // Configure pin
//   pinMode(led_pin, OUTPUT);

//   // Task to run forever
//   xTaskCreatePinnedToCore(  // Use xTaskCreate() in vanilla FreeRTOS
//       toggleLED,            // Function to be called
//       "Toggle LED",         // Name of task
//       1024,                 // Stack size (bytes in ESP32, words in FreeRTOS)
//       NULL,                 // Parameter to pass to function
//       1,                    // Task priority (0 to configMAX_PRIORITIES - 1)
//       NULL,                 // Task handle
//       app_cpu);             // Run on one core for demo purposes  (ESP32 only)

//   // Task to run forever
//   xTaskCreatePinnedToCore(  // Use xTaskCreate() in vanilla FreeRTOS
//       toggleLEDDiff,            // Function to be called
//       "Toggle LED Different",         // Name of task
//       1024,                 // Stack size (bytes in ESP32, words in FreeRTOS)
//       NULL,                 // Parameter to pass to function
//       1,                    // Task priority (0 to configMAX_PRIORITIES - 1)
//       NULL,                 // Task handle
//       app_cpu);             // Run on one core for demo purposes  (ESP32 only)

//     // If this was vanilla FreeRTOS, you'd want to call vTaskStartSchedular() in
//     // main after setting up your tasks.

// }

// void loop() {
//   // put your main code here, to run repeatedly:

// }

//*********************************************************Task Scheduling****************************************************************

// // Use only core 1 for demo purposes
// #if CONFIG_FREERTOS_UNICORE
//   static const BaseType_t app_cpu = 0;
// #else
//   static const BaseType_t app_cpu = 1;
// #endif

// // Some string to print
// const char msg[] = "Barkadeer brig Arr booty rum.";

// // Task handles
// static TaskHandle_t task_1 = NULL;
// static TaskHandle_t task_2 = NULL;

// //************************************************************************************
// // Tasks

// // Task: print to Serial Terminal with lower priority
// void startTask1(void *parameter) {

//   // Count number of characters in string
//   int msg_len = strlen(msg);

//   // Print string to Terminal
//   while (1) {
//     Serial.println();
//     for (int i = 0; i < msg_len; i++) {
//       Serial.print(msg[i]);
//       //vTaskDelay(100 / portTICK_PERIOD_MS);
//     }
//     //Serial.println();
//     //vTaskDelay(1000 / portTICK_PERIOD_MS);
//   }
// }

// // Task: print to Serial Terminal with higher priority
// void startTask2(void *parameter) {
//   while (1) {
//     Serial.print('*TASK SUCCESSFUL*');
    
//     vTaskDelay(5000 / portTICK_PERIOD_MS);
//   }
// }

// //***********************************************************************************

// void setup() {

//   // Configure Serial (go slow so we can watch the preemption)
//   Serial.begin(2400);

//   // Wait a moment to start (so we don't miss Serial output)
//   vTaskDelay(1000 / portTICK_PERIOD_MS);
//   Serial.println();
//   Serial.println("---FreeRTOS Task Demo---");

//   // Print self priority
//   Serial.print("Setup and loop task running on core ");
//   Serial.print(xPortGetCoreID());
//   Serial.print(" with priority ");
//   Serial.println(uxTaskPriorityGet(NULL));

//   // Task to run forever
//   xTaskCreatePinnedToCore(startTask1,
//                           "Task 1",
//                           1024,
//                           NULL,
//                           20,
//                           &task_1,
//                           app_cpu);

//   // Task to run once with higher priority
//   xTaskCreatePinnedToCore(startTask2,
//                           "Task 2",
//                           1024,
//                           NULL,
//                           21,
//                           &task_2,
//                           app_cpu);
// }

// void loop() {

//   // Suspend the higher priority task for some intervals
//   // for (int i = 0; i < 3; i++) {
//   //   vTaskSuspend(task_2);
//   //   vTaskDelay(2000 / portTICK_PERIOD_MS);
//   //   vTaskResume(task_2);
//   //   vTaskDelay(2000 / portTICK_PERIOD_MS);
//   // }

//   // // Delete the lower priority task
//   // if (task_1 != NULL) {
//   //   vTaskDelete(task_1);
//   //   task_1 = NULL;
//   // }

// }

// #if CONFIG_FREERTOS_UNICORE
//   static const BaseType_t app_cpu = 0;
// #else
//   static const BaseType_t app_cpu = 1;
// #endif


// // Pins
// static const int led_pin = LED_BUILTIN;
// int delay_time = 5000;
// int new_delay_time = 1000;

// // Task handles
// static TaskHandle_t task_1 = NULL;
// static TaskHandle_t task_2 = NULL;

// //********************************************************
// // Tasks

// // Task: toggle LED
// void startTask1(void *parameter) {
//   pinMode(led_pin, OUTPUT);
//   while (1) {
//     digitalWrite(led_pin, HIGH);
//     vTaskDelay(delay_time / portTICK_PERIOD_MS);
//     digitalWrite(led_pin, LOW);
//     vTaskDelay(delay_time / portTICK_PERIOD_MS); // Add this to complete the cycle
//   }
// }

// // Task: Listen Input
// void startTask2(void *parameter) {
//   while (1) {
//     Serial.println("Input New Integer Delay Time:");
//     new_delay_time = Serial.parseInt();
//     if (new_delay_time > 0) {
//       delay_time = new_delay_time;
//       Serial.print("Updated delay time to: ");
//       Serial.println(delay_time);
//     }
//     vTaskDelay(1000 / portTICK_PERIOD_MS); // Add a small delay to avoid overwhelming the CPU
//   }
// }

// //**********************************************************

// void setup() {

//   // Configure Serial (go slow so we can watch the preemption)
//   Serial.begin(2400);

//   // Wait a moment to start (so we don't miss Serial output)
//   vTaskDelay(1000 / portTICK_PERIOD_MS);
//   Serial.println();
//   Serial.println("---FreeRTOS Task Demo---");

//   // Print self priority
//   Serial.print("Setup and loop task running on core ");
//   Serial.print(xPortGetCoreID());
//   Serial.print(" with priority ");
//   Serial.println(uxTaskPriorityGet(NULL));

//   // Task to run forever
//   xTaskCreatePinnedToCore(startTask1,
//                           "Task 1",
//                           1024,
//                           NULL,
//                           1,
//                           &task_1,
//                           app_cpu);

//   // Task to run once with higher priority
//   xTaskCreatePinnedToCore(startTask2,
//                           "Task 2",
//                           1024,
//                           NULL,
//                           1,
//                           &task_2,
//                           app_cpu);
// }

// void loop() {

// }

//*********************************************************Memory Management****************************************************************


















