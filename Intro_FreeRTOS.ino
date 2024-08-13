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

// // Use only core 1 for demo purposes
// #if CONFIG_FREERTOS_UNICORE
// static const BaseType_t app_cpu = 0;
// #else
// static const BaseType_t app_cpu = 1;
// #endif

// // Task: Perform some mundate task
// void testTask(void *parameter) {
//   while(1) {
//     int a = 1;
//     int b[100];

//     // Do something with array so it's not optimized out by the compiler
//     for (int i = 0; i < 100; i++) {
//       b[i] = a + 1;
//     }
//     Serial.println(b[0]);

//     // Print out remaining stack memory (words)
//     Serial.print("High water mark (words): ");
//     Serial.println(uxTaskGetStackHighWaterMark(NULL));

//     // Print out number of free heap memory bytes before malloc
//     Serial.print("Heap before malloc (bytes): ");
//     Serial.println(xPortGetFreeHeapSize());
//     int *ptr = (int*)pvPortMalloc(1024 * sizeof(int));

//     // One way to prevent heap overflow is to check the malloc output
//     if (ptr == NULL) {
//       Serial.println("Not enough heap.");
//     } else {
//       // Do something with memory so it's not optimized out by the compiler
//       for (int i = 0; i < 1024; i++) {
//         ptr[i] = 3;
//       }      
//     }

//     // Print out number of free heap memory bytes after malloc
//     Serial.print("Heap after malloc (bytes): ");
//     Serial.println(xPortGetFreeHeapSize());

//     vPortFree(ptr);

//     // Wait for a while
//     vTaskDelay(100 / portTICK_PERIOD_MS);
//   }
// }

// void setup() {

//   // Configure Serial
//   Serial.begin(115200);

//   // Wait a moment to start (so we don't miss Serial output)
//   vTaskDelay(1000 / portTICK_PERIOD_MS);
//   Serial.println();
//   Serial.println("---FreeRTOS Memory Demo---");

//   // Start the only other task
//   xTaskCreatePinnedToCore(testTask,
//                           "Test Task",
//                           1400,
//                           NULL,
//                           1,
//                           NULL,
//                           app_cpu);

//   // Delete "setup and loop" task
//   vTaskDelete(NULL);
// }

// void loop() {
//   // put your main code here, to run regularly:
// }

//**********************************CHALLENGE***********************************

// // Use only core 1 for demo purposes
// #if CONFIG_FREERTOS_UNICORE
// static const BaseType_t app_cpu = 0;
// #else
// static const BaseType_t app_cpu = 1;
// #endif

// char *ptr = NULL;
// static volatile uint8_t msg_flag = 0;

// // Task: Perform some mundate task
// void TaskA(void *parameter) {
//   while(1) {
//     int a = 1;
//     int b[100];

//     // Perform operations on the array
//     for (int i = 0; i < 100; i++) {
//       b[i] = a + 1;
//     }
//     Serial.println(b[0]);

//     // Print out the high water mark (remaining stack memory)
//     Serial.print("High water mark (words): ");
//     Serial.println(uxTaskGetStackHighWaterMark(NULL));

//     // Print the amount of free heap memory before allocation
//     Serial.print("Heap before malloc (bytes): ");
//     Serial.println(xPortGetFreeHeapSize());

//     // Check if there is any data available in the serial buffer
//     if (Serial.available() > 0) {
//         // Read the input string
//         String inputString = Serial.readString();

//         // Allocate memory on the heap for the string, including the null terminator
//         char *ptr = (char*)pvPortMalloc(inputString.length() + 1); // +1 for null terminator

//         // Ensure that the allocation was successful
//         if (ptr != NULL) {
//           // Copy the string to the allocated memory
//           strcpy(ptr, inputString.c_str());

//           // Print the received string
//           Serial.print("Received and stored on heap: ");
//           Serial.println(ptr);

//           // Free the allocated memory
//           //vPortFree(ptr);

//           vTaskDelay(1000 / portTICK_PERIOD_MS);

//           // Print the amount of free heap memory after allocation
//           Serial.print("Heap after malloc (bytes): ");
//           Serial.println(xPortGetFreeHeapSize());

//           // Notify other task that message is ready
//           msg_flag = 1;

//         } else {
//             Serial.println("Failed to allocate memory on heap.");
//         }
//     } else {
//         Serial.println("No input received.");
//     }
//     // Wait for a while before repeating the loop
//     vTaskDelay(1000 / portTICK_PERIOD_MS);
//   }
// }

// void TaskB(void *parameter) {
//   while(1) {
//     // Wait for flag to be set and print message
//     if (msg_flag == 1) {
//       Serial.println();
//       Serial.print("TASKB WILL CLEAR THE HEAP!");

//       // Free buffer, set pointer to NULL, and clear flag
//       if (ptr != NULL) {
//           vPortFree(ptr);
//           ptr = NULL;
//       }
//       msg_flag = 0;
//     }

//     vTaskDelay(2500 / portTICK_PERIOD_MS);    
//   }
// }

// void setup() {
//   Serial.begin(600);
//   vTaskDelay(1000 / portTICK_PERIOD_MS); // Give time for serial monitor to start
//   Serial.println("---FreeRTOS Memory Demo---");

//   // Create the task pinned to core 1 with an increased stack size
//   xTaskCreatePinnedToCore(TaskA,
//                           "Test TaskA",
//                           4800,  // Increased stack size
//                           NULL,
//                           1,
//                           NULL,
//                           app_cpu);

//   // Create the task pinned to core 1 with an increased stack size
//   xTaskCreatePinnedToCore(TaskB,
//                           "Test TaskB",
//                           1080,  // Increased stack size
//                           NULL,
//                           1,
//                           NULL,
//                           app_cpu);


//   // Delete the setup task
//   vTaskDelete(NULL);
// }

// void loop() {
//   // No need for code here, as the loop task is deleted
// }

//************************************************* QUEUE ************************************************

// // Use only core 1 for demo purposes
// #if CONFIG_FREERTOS_UNICORE
// static const BaseType_t app_cpu = 0;
// #else
// static const BaseType_t app_cpu = 1;
// #endif

// // Settings
// static const uint8_t msg_queue_len = 5;

// // Globals
// static QueueHandle_t msg_queue;

// // Task: wait for item on queue and print it
// void printMessages(void *parameters) {

//   int item;

//   // Loop forever
//   while (1) {

//     // See if there's a message in the queue (do not block)
//     if (xQueueReceive(msg_queue, (void *)&item, 0) == pdTRUE) {
      
//     }
//     Serial.println(item);
//     // Wait before trying again
//     vTaskDelay(500 / portTICK_PERIOD_MS);
//   }
// }

// //************************************************************************
// // Main (runs as its own task with priority 1 on core 1)

// void setup() {
  
//   // Configure Serial
//   Serial.begin(115200);

//   // Wait a moment to start (so we don't miss Serial output)
//   vTaskDelay(1000 / portTICK_PERIOD_MS);
//   Serial.println();
//   Serial.println("---FreeRTOS Queue Demo---");

//   // Create queue
//   msg_queue = xQueueCreate(msg_queue_len, sizeof(int));

//   // Start print task
//   xTaskCreatePinnedToCore(printMessages,
//                           "Print Messages",
//                           1024,
//                           NULL,
//                           1,
//                           NULL,
//                           app_cpu);
// }

// void loop() {
  
//   static int num = 0;

//   // Try to add item to queue for 10 ticks, fail if queue is full
//   if (xQueueSend(msg_queue, (void *)&num, 10) != pdTRUE) {
//     Serial.println("Queue full");
//   }
//   num++;

//   // Wait before trying again
//   vTaskDelay(500 / portTICK_PERIOD_MS);
// }

// // Use only core 1 for demo purposes
// #if CONFIG_FREERTOS_UNICORE
// static const BaseType_t app_cpu = 0;
// #else
// static const BaseType_t app_cpu = 1;
// #endif

// // Settings
// static const uint8_t msg_queue1_len = 50;
// static const uint8_t msg_queue2_len = 50;

// // Globals
// static QueueHandle_t queue_1;
// static QueueHandle_t queue_2;

// // Led Pin
// static const int led_pin = LED_BUILTIN;

// // Task: wait for item on queue and print it
// void taskA(void *parameters) {

//   int item;
//   int send_time;

//   // Loop forever
//   while (1) {
//     if (Serial.available() > 0) {

//       Serial.print("Input delay to terminal: ");
//       send_time = Serial.parseInt();
    
//       // Print newline to terminal
//       Serial.print("\r\n");

//       // Send integer to other task via queue
//       if (xQueueSend(queue_1, (void *)&send_time, 10) != pdTRUE) {
//         Serial.println("ERROR: Could not put item on delay queue.");
//       }


//     }
//     // Wait before trying again
//     Serial.println("Tick");
//     vTaskDelay(500 / portTICK_PERIOD_MS);     
//   }
// }

// void taskB(void *parameters) {

//   int delay_time = 0;
//   int true_delay = 50;

//   while (1) {

//     if (xQueueReceive(queue_1, (void *)&delay_time, 1) == pdTRUE) {
//       if (delay_time > 0) {
//         Serial.print("delay time is: ");
//         Serial.print(delay_time);     
//         true_delay = delay_time;
//       }
//     }

//     digitalWrite(led_pin, HIGH);
//     vTaskDelay(true_delay / portTICK_PERIOD_MS);
//     digitalWrite(led_pin, LOW);
//     vTaskDelay(true_delay / portTICK_PERIOD_MS);

//   }
// }

// void setup() {
  
//   // Configure Serial
//   Serial.begin(115200);

//   // Configure LED Pin
//   pinMode(led_pin, OUTPUT);

//   // Wait a moment to start (so we don't miss Serial output)
//   vTaskDelay(1000 / portTICK_PERIOD_MS);
//   Serial.println();
//   Serial.println("---FreeRTOS Queue Demo---");

//   // Create queue
//   queue_1 = xQueueCreate(msg_queue1_len, sizeof(int));

//   // Start print task
//   xTaskCreatePinnedToCore(taskA,
//                           "Print Messages",
//                           1024,
//                           NULL,
//                           2,
//                           NULL,
//                           app_cpu);

//   xTaskCreatePinnedToCore(taskB,
//                           "Print Messages",
//                           1024,
//                           NULL,
//                           1,
//                           NULL,
//                           app_cpu);
// }

// void loop() {
  
// }

//*********************************************** MUTEX *******************************************

// // Use only core 1 for demo purposes
// #if CONFIG_FREERTOS_UNICORE
// static const BaseType_t app_cpu = 0;
// #else
// static const BaseType_t app_cpu = 1;
// #endif

// // Globals
// static int shared_var = 0;
// static SemaphoreHandle_t mutex;

// //**********************************************************
// // Tasks

// // Increment shared variable (the wrong way)
// void incTask(void *parameters) {

//   int local_var;

//   // Loop forever
//   while (1) {

//     // Take mutex prior to critical section
//     if (xSemaphoreTake(mutex, 0) == pdTRUE) {
//       // Roundabout way to do "shared_var++" randomly and poorly
//       local_var = shared_var;
//       local_var++;
//       vTaskDelay(random(100, 500) / portTICK_PERIOD_MS);
//       shared_var = local_var;

//       // Give mutex after critical Section
//       xSemaphoreGive(mutex);

//       // Print out new shared variable
//       Serial.println(shared_var);  
//     } else {
//       // Do something else
//     }
//   }
// }

// //**********************************************************
// // Main (runs as its own task with priority 1 on core 1)

// void setup() {

//   // Hack to kinda get randomness
//   randomSeed(analogRead(0));

//   // Configure Serial
//   Serial.begin(115200);

//   // Wait a moment to start (so we don't miss Serial output)
//   vTaskDelay(1000 / portTICK_PERIOD_MS);
//   Serial.println();
//   Serial.println("---FreeRTOS Race Condition Demo---");

//   // Create mutex before starting tasks
//   mutex = xSemaphoreCreateMutex();

//   // Start task 1
//   xTaskCreatePinnedToCore(incTask,
//                       "Increment Task 1",
//                       1024,
//                       NULL,
//                       1,
//                       NULL,
//                       app_cpu);

//   // Show that we accomplished our task of passing the stack-based argument
//   Serial.println("Done!");
// }


// void loop() {
//   vTaskDelay(1000 / portTICK_PERIOD_MS);
// }

/**
 * FreeRTOS Mutex Challenge
 * 
 * Pass a parameter to a task using a mutex.
 * 
 * Date: January 20, 2021
 * Author: Shawn Hymel
 * License: 0BSD
 */

// You'll likely need this on vanilla FreeRTOS
//#include <semphr.h>

// Use only core 1 for demo purposes
#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu = 0;
#else
  static const BaseType_t app_cpu = 1;
#endif

// Pins (change this if your Arduino board does not have LED_BUILTIN defined)
static const int led_pin = LED_BUILTIN;
static SemaphoreHandle_t mutex;

//*****************************************************************************
// Tasks

// Blink LED based on rate passed by parameter
void blinkLED(void *parameters) {

  // Copy the parameter into a local variable
  int num = *(int *)parameters;

  // Print the parameter
  Serial.print("Received: ");
  Serial.println(num);

  // Configure the LED pin
  pinMode(led_pin, OUTPUT);

  xSemaphoreGive(mutex);
  // Blink forever and ever
  while (1) {
    digitalWrite(led_pin, HIGH);
    vTaskDelay(num / portTICK_PERIOD_MS);
    digitalWrite(led_pin, LOW);
    vTaskDelay(num / portTICK_PERIOD_MS);
  }
}



//*****************************************************************************
// Main (runs as its own task with priority 1 on core 1)

void setup() {

  long int delay_arg;

  // Configure Serial
  Serial.begin(115200);

  // Wait a moment to start (so we don't miss Serial output)
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  Serial.println();
  Serial.println("---FreeRTOS Mutex Challenge---");
  Serial.println("Enter a number for delay (milliseconds)");

  mutex = xSemaphoreCreateMutex();

  // Wait for input from Serial
  while (Serial.available() <= 0);

  // Read integer value
  delay_arg = Serial.parseInt();
  Serial.print("Sending: ");
  Serial.println(delay_arg);

  // Start task 1
  xTaskCreatePinnedToCore(blinkLED,
                          "Blink LED",
                          1024,
                          (void *)&delay_arg,
                          1,
                          NULL,
                          app_cpu);

  // Do nothing until mutex has been returned (maximum delay)
  xSemaphoreTake(mutex, portMAX_DELAY);

  // Show that we accomplished our task of passing the stack-based argument
  Serial.println("Done!");
}

void loop() {
  
  // Do nothing but allow yielding to lower-priority tasks
  vTaskDelay(1000 / portTICK_PERIOD_MS);
}









