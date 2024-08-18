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

// // Use only core 1 for demo purposes
// #if CONFIG_FREERTOS_UNICORE
//   static const BaseType_t app_cpu = 0;
// #else
//   static const BaseType_t app_cpu = 1;
// #endif

// // Pins (change this if your Arduino board does not have LED_BUILTIN defined)
// static const int led_pin = LED_BUILTIN;
// static SemaphoreHandle_t mutex;

// //*****************************************************************************
// // Tasks

// // Blink LED based on rate passed by parameter
// void blinkLED(void *parameters) {

//   // Copy the parameter into a local variable
//   int num = *(int *)parameters;

//   // Print the parameter
//   Serial.print("Received: ");
//   Serial.println(num);

//   // Configure the LED pin
//   pinMode(led_pin, OUTPUT);

//   xSemaphoreGive(mutex);
//   // Blink forever and ever
//   while (1) {
//     digitalWrite(led_pin, HIGH);
//     vTaskDelay(num / portTICK_PERIOD_MS);
//     digitalWrite(led_pin, LOW);
//     vTaskDelay(num / portTICK_PERIOD_MS);
//   }
// }



// //*****************************************************************************
// // Main (runs as its own task with priority 1 on core 1)

// void setup() {

//   long int delay_arg;

//   // Configure Serial
//   Serial.begin(115200);

//   // Wait a moment to start (so we don't miss Serial output)
//   vTaskDelay(1000 / portTICK_PERIOD_MS);
//   Serial.println();
//   Serial.println("---FreeRTOS Mutex Challenge---");
//   Serial.println("Enter a number for delay (milliseconds)");

//   mutex = xSemaphoreCreateMutex();

//   // Wait for input from Serial
//   while (Serial.available() <= 0);

//   // Read integer value
//   delay_arg = Serial.parseInt();
//   Serial.print("Sending: ");
//   Serial.println(delay_arg);

//   // Start task 1
//   xTaskCreatePinnedToCore(blinkLED,
//                           "Blink LED",
//                           1024,
//                           (void *)&delay_arg,
//                           1,
//                           NULL,
//                           app_cpu);

//   // Do nothing until mutex has been returned (maximum delay)
//   xSemaphoreTake(mutex, portMAX_DELAY);

//   // Show that we accomplished our task of passing the stack-based argument
//   Serial.println("Done!");
// }

// void loop() {
  
//   // Do nothing but allow yielding to lower-priority tasks
//   vTaskDelay(1000 / portTICK_PERIOD_MS);
// }

//********************************************************** Semaphore ************************************************************

// /**
//  * FreeRTOS Counting Semaphore Challenge
//  * 
//  * Challenge: use a mutex and counting semaphores to protect the shared buffer 
//  * so that each number (0 throguh 4) is printed exactly 3 times to the Serial 
//  * monitor (in any order). Do not use queues to do this!
//  * 
//  * Hint: you will need 2 counting semaphores in addition to the mutex, one for 
//  * remembering number of filled slots in the buffer and another for 
//  * remembering the number of empty slots in the buffer.
//  * 
//  * Date: January 24, 2021
//  * Author: Shawn Hymel
//  * License: 0BSD
//  */

// // You'll likely need this on vanilla FreeRTOS
// //#include <semphr.h>

// // Use only core 1 for demo purposes
// #if CONFIG_FREERTOS_UNICORE
//   static const BaseType_t app_cpu = 0;
// #else
//   static const BaseType_t app_cpu = 1;
// #endif

// // Settings
// enum {BUF_SIZE = 5};                  // Size of buffer array
// static const int num_prod_tasks = 5;  // Number of producer tasks
// static const int num_cons_tasks = 2;  // Number of consumer tasks
// static const int num_writes = 3;      // Num times each producer writes to buf

// // Globals
// static int buf[BUF_SIZE];             // Shared buffer
// static int head = 0;                  // Writing index to buffer
// static int tail = 0;                  // Reading index to buffer
// static SemaphoreHandle_t bin_sem;     // Waits for parameter to be read
// static SemaphoreHandle_t mutex;       // Lock access to buffer and Serial
// static SemaphoreHandle_t sem_empty;   // Counts number of empty slots in buf
// static SemaphoreHandle_t sem_filled;  // Counts number of filled slots in buf

// //*****************************************************************************
// // Tasks

// // Producer: write a given number of times to shared buffer
// void producer(void *parameters) {

//   // Copy the parameters into a local variable
//   int num = *(int *)parameters;

//   // Release the binary semaphore
//   xSemaphoreGive(bin_sem);

//   // Fill shared buffer with task number
//   for (int i = 0; i < num_writes; i++) {

//     // Wait for empty slot in buffer to be available
//     xSemaphoreTake(sem_empty, portMAX_DELAY);

//     // Critical section (accessing shared buffer)
//     xSemaphoreTake(mutex, portMAX_DELAY);
//     buf[head] = num;
//     head = (head + 1) % BUF_SIZE;
//     xSemaphoreGive(mutex);

//     // Signal to consumer tasks that a slot in the buffer has been filled
//     xSemaphoreGive(sem_filled);
//   }

//   // Delete self task
//   vTaskDelete(NULL);
// }

// // Consumer: continuously read from shared buffer
// void consumer(void *parameters) {

//   int val;

//   // Read from buffer
//   while (1) {

//     // Wait for at least one slot in buffer to be filled
//     xSemaphoreTake(sem_filled, portMAX_DELAY);

//     // Lock critical section with a mutex
//     xSemaphoreTake(mutex, portMAX_DELAY);
//     val = buf[tail];
//     tail = (tail + 1) % BUF_SIZE;
//     Serial.println(val);
//     xSemaphoreGive(mutex);

//     // Signal to producer thread that a slot in the buffer is free
//     xSemaphoreGive(sem_empty);
//   }
// }

// //*****************************************************************************
// // Main (runs as its own task with priority 1 on core 1)

// void setup() {

//   char task_name[12];
  
//   // Configure Serial
//   Serial.begin(115200);

//   // Wait a moment to start (so we don't miss Serial output)
//   vTaskDelay(1000 / portTICK_PERIOD_MS);
//   Serial.println();
//   Serial.println("---FreeRTOS Semaphore Solution---");

//   // Create mutexes and semaphores before starting tasks
//   bin_sem = xSemaphoreCreateBinary();
//   mutex = xSemaphoreCreateMutex();
//   sem_empty = xSemaphoreCreateCounting(BUF_SIZE, BUF_SIZE);
//   sem_filled = xSemaphoreCreateCounting(BUF_SIZE, 0);

//   // Start producer tasks (wait for each to read argument)
//   for (int i = 0; i < num_prod_tasks; i++) {
//     sprintf(task_name, "Producer %i", i);
//     xTaskCreatePinnedToCore(producer,
//                             task_name,
//                             1024,
//                             (void *)&i,
//                             1,
//                             NULL,
//                             app_cpu);
//     xSemaphoreTake(bin_sem, portMAX_DELAY);
//   }

//   // Start consumer tasks
//   for (int i = 0; i < num_cons_tasks; i++) {
//     sprintf(task_name, "Consumer %i", i);
//     xTaskCreatePinnedToCore(consumer,
//                             task_name,
//                             1024,
//                             NULL,
//                             1,
//                             NULL,
//                             app_cpu);
//   }

//   // Notify that all tasks have been created (lock Serial with mutex)
//   xSemaphoreTake(mutex, portMAX_DELAY);
//   Serial.println("All tasks created");
//   xSemaphoreGive(mutex);
// }

// void loop() {
  
//   // Do nothing but allow yielding to lower-priority tasks
//   vTaskDelay(1000 / portTICK_PERIOD_MS);
// }

//********************************************************** Timers ************************************************************
// // You'll likely need this on FreeRTOS
// // #include timers.h

// // Use only core 1 for demo purposes
// #if CONFIG_FREERTOS_UNICORE
//   static const BaseType_t app_cpu = 0;
// #else
//   static const BaseType_t app_cpu = 1;
// #endif

// // Globals
// static TimerHandle_t one_shot_timer = NULL;
// static TimerHandle_t auto_reload_timer = NULL;

// //*********************************************************************************
// // Callbacks

// // Called when one of the timers expires
// void myTimerCallback(TimerHandle_t xTimer) {

//   // Print message if timer 0 expired
//   if ((uint32_t)pvTimerGetTimerID(xTimer) == 0) {
//     Serial.println("One-shot timer expired");
//   }
  
//   // Print message if timer 1 expired
//   if ((uint32_t)pvTimerGetTimerID(xTimer) == 1) {
//     Serial.println("Auto-reload timer expired");
//   }
// }

// //*********************************************************************************
// // Main (runs as its own task with priority 1 on core 1)

// void setup() {

//   // Configure Serial
//   Serial.begin(115200);

//   // Wait a moment to start (so we don't miss Serial output)
//   vTaskDelay(1000 / portTICK_PERIOD_MS);
//   Serial.println();
//   Serial.println("---FreeRTOS Timer Demo---");

//   // Create a one-shot timer
//   one_shot_timer = xTimerCreate(
//                             "One-shot timer",           // Name of timer
//                             2000 / portTICK_PERIOD_MS,  // Period of timer (in ticks)
//                             pdFALSE,                    // Auto-reload
//                             (void *) 0,                 // Timer ID
//                             myTimerCallback);           // Callback function

//   // Create a one-shot timer
//   auto_reload_timer = xTimerCreate(
//                             "Auto-reload timer",           // Name of timer
//                             1000 / portTICK_PERIOD_MS,  // Period of timer (in ticks)
//                             pdTRUE,                    // Auto-reload
//                             (void *) 1,                 // Timer ID
//                             myTimerCallback);           // Callback function

//   // Check to make sure timers were created
//   if (one_shot_timer == NULL || auto_reload_timer == NULL) {
//     Serial.println("Could not create one of the timers");
//   } else {

//     // Wait and then print out a message that we're starting the timer
//     vTaskDelay(1000 / portTICK_PERIOD_MS);
//     Serial.println("Starting timers...");

//     // Start timers (max block time if command queue is full)
//     xTimerStart(one_shot_timer, portMAX_DELAY);
//     xTimerStart(auto_reload_timer, portMAX_DELAY);
//   }

//   // Delete self task to show that timers will work with no user tasks
//   vTaskDelete(NULL);
// }

// void loop() {
//   // put your main code here, to run repeatedly:

// }

// // You'll likely need this on FreeRTOS
// // #include timers.h

// // Use only core 1 for demo purposes
// #if CONFIG_FREERTOS_UNICORE
//   static const BaseType_t app_cpu = 0;
// #else
//   static const BaseType_t app_cpu = 1;
// #endif

// // Pins
// static const int led_pin = LED_BUILTIN;

// // Globals
// static TimerHandle_t one_shot_timer = NULL;

// //*********************************************************************************
// // Callbacks

// // Called when one of the timers expires
// void myTimerCallback(TimerHandle_t xTimer) {

//   digitalWrite(led_pin, LOW);
    
//   // Print message if timer 0 expired
//   if ((uint32_t)pvTimerGetTimerID(xTimer) == 0) {
//     Serial.println("One-shot timer expired");
//   }
//   Serial.println("Turned off LED");
// }

// //*********************************************************************************
// // Main (runs as its own task with priority 1 on core 1)

// void setup() {

//   // Configure Serial
//   Serial.begin(115200);

//   // Wait a moment to start (so we don't miss Serial output)
//   vTaskDelay(1000 / portTICK_PERIOD_MS);
//   Serial.println();
//   Serial.println("---FreeRTOS Timer Demo---");

//   // Configure pin
//   pinMode(led_pin, OUTPUT);

//   digitalWrite(led_pin, HIGH);

//   // Create a one-shot timer
//   one_shot_timer = xTimerCreate(
//                             "One-shot timer",           // Name of timer
//                             5000 / portTICK_PERIOD_MS,  // Period of timer (in ticks)
//                             pdFALSE,                    // Auto-reload
//                             (void *) 0,                 // Timer ID
//                             myTimerCallback);           // Callback function


//   // Check to make sure timers were created
//   if (one_shot_timer == NULL) {
//     Serial.println("Could not create one of the timers");
//   } else {

//     // Wait and then print out a message that we're starting the timer
//     vTaskDelay(1000 / portTICK_PERIOD_MS);
//     Serial.println("Starting timers...");

//     while (1) {
//       if (Serial.read() > 0) {
//         Serial.print("Imput Sensed");
//         xTimerStart(one_shot_timer, 5000);        
//       }
//     }
//     // Start timers (max block time if command queue is full)
//     xTimerStart(one_shot_timer, portMAX_DELAY);
//   }

//   // Delete self task to show that timers will work with no user tasks
//   vTaskDelete(NULL);
// }

// void loop() {
//   // put your main code here, to run repeatedly:

// }

//********************************************************** Interrupts ************************************************************

  // Failed to Comile

//************************************************** 10 - Deadlock and Starvation **************************************************

// /**
//  * ESP32 Dining Philosophers Solution: Arbitrator/Waiter
//  * 
//  * One possible solution to the Dining Philosophers problem.
//  * 
//  * Based on http://www.cs.virginia.edu/luther/COA2/S2019/pa05-dp.html
//  * 
//  * Date: February 8, 2021
//  * Author: Shawn Hymel
//  * License: 0BSD
//  */

// // You'll likely need this on vanilla FreeRTOS
// //#include <semphr.h>

// // Use only core 1 for demo purposes
// #if CONFIG_FREERTOS_UNICORE
//   static const BaseType_t app_cpu = 0;
// #else
//   static const BaseType_t app_cpu = 1;
// #endif

// // Settings
// enum { NUM_TASKS = 5 };           // Number of tasks (philosophers)
// enum { TASK_STACK_SIZE = 2048 };  // Bytes in ESP32, words in vanilla FreeRTOS

// // Globals
// static SemaphoreHandle_t bin_sem;   // Wait for parameters to be read
// static SemaphoreHandle_t done_sem;  // Notifies main task when done
// static SemaphoreHandle_t chopstick[NUM_TASKS];
// static SemaphoreHandle_t arbitrator;  // Controls who eats when (e.g. waiter)

// //*****************************************************************************
// // Tasks

// // The only task: eating
// void eat(void *parameters) {

//   int num;
//   char buf[50];

//   // Copy parameter and increment semaphore count
//   num = *(int *)parameters;
//   xSemaphoreGive(bin_sem);

//   // We have to wait our turn to eat
//   xSemaphoreTake(arbitrator, portMAX_DELAY);

//   // Take left chopstick
//   xSemaphoreTake(chopstick[num], portMAX_DELAY);
//   sprintf(buf, "Philosopher %i took chopstick %i", num, num);
//   Serial.println(buf);

//   // Add some delay to force deadlock
//   vTaskDelay(1 / portTICK_PERIOD_MS);

//   // Take right chopstick
//   xSemaphoreTake(chopstick[(num+1)%NUM_TASKS], portMAX_DELAY);
//   sprintf(buf, "Philosopher %i took chopstick %i", num, (num+1)%NUM_TASKS);
//   Serial.println(buf);

//   // Do some eating
//   sprintf(buf, "Philosopher %i is eating", num);
//   Serial.println(buf);
//   vTaskDelay(10 / portTICK_PERIOD_MS);

//   // Put down right chopstick
//   xSemaphoreGive(chopstick[(num+1)%NUM_TASKS]);
//   sprintf(buf, "Philosopher %i returned chopstick %i", num, (num+1)%NUM_TASKS);
//   Serial.println(buf);

//   // Put down left chopstick
//   xSemaphoreGive(chopstick[num]);
//   sprintf(buf, "Philosopher %i returned chopstick %i", num, num);
//   Serial.println(buf);

//   // Tell the arbitrator (waiter) that we're done
//   xSemaphoreGive(arbitrator);

//   // Notify main task and delete self
//   xSemaphoreGive(done_sem);
//   vTaskDelete(NULL);
// }

// //*****************************************************************************
// // Main (runs as its own task with priority 1 on core 1)

// void setup() {

//   char task_name[20];

//   // Configure Serial
//   Serial.begin(115200);

//   // Wait a moment to start (so we don't miss Serial output)
//   vTaskDelay(1000 / portTICK_PERIOD_MS);
//   Serial.println();
//   Serial.println("---FreeRTOS Dining Philosophers Arbitrator Solution---");

//   // Create kernel objects before starting tasks
//   bin_sem = xSemaphoreCreateBinary();
//   done_sem = xSemaphoreCreateCounting(NUM_TASKS, 0);
//   for (int i = 0; i < NUM_TASKS; i++) {
//     chopstick[i] = xSemaphoreCreateMutex();
//   }
//   arbitrator = xSemaphoreCreateMutex();
  
//   // Have the philosphers start eating
//   for (int i = 0; i < NUM_TASKS; i++) {
//     sprintf(task_name, "Philosopher %i", i);
//     xTaskCreatePinnedToCore(eat,
//                             task_name,
//                             TASK_STACK_SIZE,
//                             (void *)&i,
//                             1,
//                             NULL,
//                             app_cpu);
//     xSemaphoreTake(bin_sem, portMAX_DELAY);
//   }


//   // Wait until all the philosophers are done
//   for (int i = 0; i < NUM_TASKS; i++) {
//     xSemaphoreTake(done_sem, portMAX_DELAY);
//   }

//   // Say that we made it through without deadlock
//   Serial.println("Done! No deadlock occurred!");
// }

// void loop() {
//   // Do nothing in this task
// }

// /**
//  * ESP32 Dining Philosophers Solution: Hierarchy
//  * 
//  * One possible solution to the Dining Philosophers problem.
//  * 
//  * Based on http://www.cs.virginia.edu/luther/COA2/S2019/pa05-dp.html
//  * 
//  * Date: February 8, 2021
//  * Author: Shawn Hymel
//  * License: 0BSD
//  */

// // You'll likely need this on vanilla FreeRTOS
// //#include <semphr.h>

// // Use only core 1 for demo purposes
// #if CONFIG_FREERTOS_UNICORE
//   static const BaseType_t app_cpu = 0;
// #else
//   static const BaseType_t app_cpu = 1;
// #endif

// // Settings
// enum { NUM_TASKS = 5 };           // Number of tasks (philosophers)
// enum { TASK_STACK_SIZE = 2048 };  // Bytes in ESP32, words in vanilla FreeRTOS

// // Globals
// static SemaphoreHandle_t bin_sem;   // Wait for parameters to be read
// static SemaphoreHandle_t done_sem;  // Notifies main task when done
// static SemaphoreHandle_t chopstick[NUM_TASKS];

// //*****************************************************************************
// // Tasks

// // The only task: eating
// void eat(void *parameters) {

//   int num;
//   char buf[50];
//   int idx_1;
//   int idx_2;

//   // Copy parameter and increment semaphore count
//   num = *(int *)parameters;
//   xSemaphoreGive(bin_sem);

//   // Assign priority: pick up lower-numbered chopstick first
//   if (num < (num + 1) % NUM_TASKS) {
//     idx_1 = num;
//     idx_2 = (num + 1) % NUM_TASKS;
//   } else {
//     idx_1 = (num + 1) % NUM_TASKS;
//     idx_2 = num;
//   }

//   // Take lower-numbered chopstick
//   xSemaphoreTake(chopstick[idx_1], portMAX_DELAY);
//   sprintf(buf, "Philosopher %i took chopstick %i", num, num);
//   Serial.println(buf);

//   // Add some delay to force deadlock
//   vTaskDelay(1 / portTICK_PERIOD_MS);

//   // Take higher-numbered chopstick
//   xSemaphoreTake(chopstick[idx_2], portMAX_DELAY);
//   sprintf(buf, "Philosopher %i took chopstick %i", num, (num+1)%NUM_TASKS);
//   Serial.println(buf);

//   // Do some eating
//   sprintf(buf, "Philosopher %i is eating", num);
//   Serial.println(buf);
//   vTaskDelay(10 / portTICK_PERIOD_MS);

//   // Put down higher-numbered chopstick
//   xSemaphoreGive(chopstick[idx_2]);
//   sprintf(buf, "Philosopher %i returned chopstick %i", num, (num+1)%NUM_TASKS);
//   Serial.println(buf);

//   // Put down lower-numbered chopstick
//   xSemaphoreGive(chopstick[idx_1]);
//   sprintf(buf, "Philosopher %i returned chopstick %i", num, num);
//   Serial.println(buf);

//   // Notify main task and delete self
//   xSemaphoreGive(done_sem);
//   vTaskDelete(NULL);
// }

// //*****************************************************************************
// // Main (runs as its own task with priority 1 on core 1)

// void setup() {

//   char task_name[20];

//   // Configure Serial
//   Serial.begin(115200);

//   // Wait a moment to start (so we don't miss Serial output)
//   vTaskDelay(1000 / portTICK_PERIOD_MS);
//   Serial.println();
//   Serial.println("---FreeRTOS Dining Philosophers Hierarchy Solution---");

//   // Create kernel objects before starting tasks
//   bin_sem = xSemaphoreCreateBinary();
//   done_sem = xSemaphoreCreateCounting(NUM_TASKS, 0);
//   for (int i = 0; i < NUM_TASKS; i++) {
//     chopstick[i] = xSemaphoreCreateMutex();
//   }

//   // Have the philosphers start eating
//   for (int i = 0; i < NUM_TASKS; i++) {
//     sprintf(task_name, "Philosopher %i", i);
//     xTaskCreatePinnedToCore(eat,
//                             task_name,
//                             TASK_STACK_SIZE,
//                             (void *)&i,
//                             1,
//                             NULL,
//                             app_cpu);
//     xSemaphoreTake(bin_sem, portMAX_DELAY);
//   }


//   // Wait until all the philosophers are done
//   for (int i = 0; i < NUM_TASKS; i++) {
//     xSemaphoreTake(done_sem, portMAX_DELAY);
//   }

//   // Say that we made it through without deadlock
//   Serial.println("Done! No deadlock occurred!");
// }

// void loop() {
//   // Do nothing in this task
// }


//************************************************** 11 - Priority Inversion **************************************************

// /**
//  * ESP32 Priority Inheritance Demo
//  * 
//  * Demonstrate priority inheritance.
//  * 
//  * Date: February 12, 2021
//  * Author: Shawn Hymel
//  * License: 0BSD
//  */

// // You'll likely need this on vanilla FreeRTOS
// //#include <semphr.h>

// // Use only core 1 for demo purposes
// #if CONFIG_FREERTOS_UNICORE
//   static const BaseType_t app_cpu = 0;
// #else
//   static const BaseType_t app_cpu = 1;
// #endif

// // Settings
// TickType_t cs_wait = 250;  // Time spent in critical section (ms)
// TickType_t med_wait = 5000; // Time medium task spends working (ms)

// // Globals
// static SemaphoreHandle_t lock;

// //*****************************************************************************
// // Tasks

// // Task L (low priority)
// void doTaskL(void *parameters) {

//   TickType_t timestamp;

//   // Do forever
//   while (1) {

//     // Take lock
//     Serial.println("Task L trying to take lock...");
//     timestamp = xTaskGetTickCount() * portTICK_PERIOD_MS;
//     xSemaphoreTake(lock, portMAX_DELAY);

//     // Say how long we spend waiting for a lock
//     Serial.print("Task L got lock. Spent ");
//     Serial.print((xTaskGetTickCount() * portTICK_PERIOD_MS) - timestamp);
//     Serial.println(" ms waiting for lock. Doing some work...");

//     // Hog the processor for a while doing nothing
//     timestamp = xTaskGetTickCount() * portTICK_PERIOD_MS;
//     while ( (xTaskGetTickCount() * portTICK_PERIOD_MS) - timestamp < cs_wait);

//     // Release lock
//     Serial.println("Task L releasing lock.");
//     xSemaphoreGive(lock);

//     // Go to sleep
//     vTaskDelay(100 / portTICK_PERIOD_MS);
//   }
// }

// // Task M (medium priority)
// void doTaskM(void *parameters) {

//   TickType_t timestamp;

//   // Do forever
//   while (1) {

//     // Hog the processor for a while doing nothing
//     Serial.println("Task M doing some work...");
//     timestamp = xTaskGetTickCount() * portTICK_PERIOD_MS;
//     while ( (xTaskGetTickCount() * portTICK_PERIOD_MS) - timestamp < med_wait);

//     // Go to sleep
//     Serial.println("Task M done!");
//     vTaskDelay(500 / portTICK_PERIOD_MS);
//   }
// }

// // Task H (high priority)
// void doTaskH(void *parameters) {

//   TickType_t timestamp;

//   // Do forever
//   while (1) {

//     // Take lock
//     Serial.println("Task H trying to take lock...");
//     timestamp = xTaskGetTickCount() * portTICK_PERIOD_MS;
//     xSemaphoreTake(lock, portMAX_DELAY);

//     // Say how long we spend waiting for a lock
//     Serial.print("Task H got lock. Spent ");
//     Serial.print((xTaskGetTickCount() * portTICK_PERIOD_MS) - timestamp);
//     Serial.println(" ms waiting for lock. Doing some work...");

//     // Hog the processor for a while doing nothing
//     timestamp = xTaskGetTickCount() * portTICK_PERIOD_MS;
//     while ( (xTaskGetTickCount() * portTICK_PERIOD_MS) - timestamp < cs_wait);

//     // Release lock
//     Serial.println("Task H releasing lock.");
//     xSemaphoreGive(lock);
    
//     // Go to sleep
//     vTaskDelay(2500 / portTICK_PERIOD_MS);
//   }
// }

// //*****************************************************************************
// // Main (runs as its own task with priority 1 on core 1)

// void setup() {

//   // Configure Serial
//   Serial.begin(115200);

//   // Wait a moment to start (so we don't miss Serial output)
//   vTaskDelay(1000 / portTICK_PERIOD_MS);
//   Serial.println();
//   Serial.println("---FreeRTOS Priority Inheritance Demo---");

//   // Create semaphores and mutexes before starting tasks
//   lock = xSemaphoreCreateMutex();
  
//   // The order of starting the tasks matters to force priority inversion

//   // Start Task L (low priority)
//   xTaskCreatePinnedToCore(doTaskL,
//                           "Task L",
//                           1024,
//                           NULL,
//                           1,
//                           NULL,
//                           app_cpu);

//   // Introduce a delay to force priority inversion
//   vTaskDelay(1 / portTICK_PERIOD_MS);

//   // Start Task H (high priority)
//   xTaskCreatePinnedToCore(doTaskH,
//                           "Task H",
//                           1024,
//                           NULL,
//                           3,
//                           NULL,
//                           app_cpu);

//   // // Start Task M (medium priority)
//   // xTaskCreatePinnedToCore(doTaskM,
//   //                         "Task M",
//   //                         1024,
//   //                         NULL,
//   //                         2,
//   //                         NULL,
//   //                         app_cpu);

//   // Delete "setup and loop" task
//   vTaskDelete(NULL);
// }

// void loop() {
//   // Execution should never get here
// }

//************************************************** 12 - Multicore Systems **************************************************

// /**
//  * ESP32 Multicore Demo
//  * 
//  * How to run two tasks on different cores
//  * 
//  * Date: March 3, 2021
//  * Author: Shawn Hymel
//  * License: 0BSD
//  */

// // Core definitions (assuming you have dual-core ESP32)
// static const BaseType_t pro_cpu = 0;
// static const BaseType_t app_cpu = 1;

// // Settings
// static const TickType_t time_hog = 200;  // Time (ms) hogging the CPU

// //*****************************************************************************
// // Functions

// // Hogs the processor. Accurate to about 1 second (no promises).
// static void hog_delay(uint32_t ms) {
//   for (uint32_t i = 0; i < ms; i++) {
//     for (uint32_t j = 0; j < 40000; j++) {
//       asm("nop");
//     }
//   }
// }

// //*****************************************************************************
// // Tasks

// // Task L (low priority)
// void doTaskL(void *parameters) {
  
//   TickType_t timestamp;
//   char str[20];

//   // Do forever
//   while (1) {

//     // Say something
//     sprintf(str, "Task L, Core %i\r\n", xPortGetCoreID());
//     Serial.print(str);
    
//     // Hog the processor for a while doing nothing (this is a bad idea)
//     hog_delay(time_hog);
//   }
// }

// // Task H (high priority)
// void doTaskH(void *parameters) {
  
//   TickType_t timestamp;
//   char str[20];

//   // Do forever
//   while (1) {

//     // Say something
//     sprintf(str, "Task H, Core %i\r\n", xPortGetCoreID());
//     Serial.print(str);
    
//     // Hog the processor for a while doing nothing (this is a bad idea)
//     hog_delay(time_hog);
//   }
// }

// //*****************************************************************************
// // Main (runs as its own task with priority 1 on core 1)

// void setup() {
  
//   // Configure Serial
//   Serial.begin(115200);

//   // Wait a moment to start (so we don't miss Serial output)
//   vTaskDelay(1000 / portTICK_PERIOD_MS);
//   Serial.println();
//   Serial.println("---FreeRTOS Priority Inheritance Demo---");
  
//   // Start Task L (low priority)
//   xTaskCreatePinnedToCore(doTaskL,
//                           "Task L",
//                           2048,
//                           NULL,
//                           1,
//                           NULL,
// //                          pro_cpu);
//                           tskNO_AFFINITY);

//   // Start Task H (low priority)
//   xTaskCreatePinnedToCore(doTaskH,
//                           "Task H",
//                           2048,
//                           NULL,
//                           2,
//                           NULL,
// //                          pro_cpu);
//                           tskNO_AFFINITY);

//   // Delete "setup and loop" task
//   vTaskDelete(NULL);
// }

// void loop() {
//   // Execution should never get here
// }

/**
 * ESP32 Multicore Spinlock Demo
 * 
 * Demonstration of critical sections and ISRs with multicore processor.
 * 
 * Date: March 3, 2021
 * Author: Shawn Hymel
 * License: 0BSD
 */

// // Core definitions (assuming you have dual-core ESP32)
// static const BaseType_t pro_cpu = 0;
// static const BaseType_t app_cpu = 1;

// // Settings
// static const TickType_t time_hog = 1;  // Time (ms) hogging the CPU in Task 1
// static const TickType_t task_0_delay = 30;  // Time (ms) Task 0 blocks itself
// static const TickType_t task_1_delay = 100; // Time (ms) Task 1 blocks itself

// // Pins
// static const int pin_0 = 12;
// static const int pin_1 = 13;

// // Globals
// static portMUX_TYPE spinlock = portMUX_INITIALIZER_UNLOCKED;

// //*****************************************************************************
// // Functions

// // Hogs the processor. Accurate to about 1 second (no promises).
// static void hog_delay(uint32_t ms) {
//   for (uint32_t i = 0; i < ms; i++) {
//     for (uint32_t j = 0; j < 40000; j++) {
//       asm("nop");
//     }
//   }
// }

// //*****************************************************************************
// // Tasks

// // Task in Core 0
// void doTask0(void *parameters) {

//   // Configure pin
//   pinMode(pin_0, OUTPUT);

//   // Do forever
//   while (1) {

//     // Toggle pin
//     portENTER_CRITICAL(&spinlock);
//     digitalWrite(pin_0, !digitalRead(pin_0));
//     portEXIT_CRITICAL(&spinlock);
    
//     // Yield processor for a while
//     vTaskDelay(task_0_delay / portTICK_PERIOD_MS);
//   }
// }

// // Task in Core 1
// void doTask1(void *parameters) {

//   // Configure pin
//   pinMode(pin_1, OUTPUT);

//   // Do forever
//   while (1) {

//     // Do some long critical section (this is bad practice)
//     portENTER_CRITICAL(&spinlock);
//     digitalWrite(pin_1, HIGH);
//     hog_delay(time_hog);
//     digitalWrite(pin_1, LOW);
//     portEXIT_CRITICAL(&spinlock);
    
//     // Yield processor for a while
//     vTaskDelay(task_1_delay / portTICK_PERIOD_MS);
//   }
// }

// //*****************************************************************************
// // Main (runs as its own task with priority 1 on core 1)

// void setup() {

//   // Start Task 0 (in Core 0)
//   xTaskCreatePinnedToCore(doTask0,
//                           "Task 0",
//                           1024,
//                           NULL,
//                           1,
//                           NULL,
//                           pro_cpu);

//   // Start Task 1 (in Core 1)
//   xTaskCreatePinnedToCore(doTask1,
//                           "Task 1",
//                           1024,
//                           NULL,
//                           1,
//                           NULL,
//                           app_cpu);

//   // Delete "setup and loop" task
//   vTaskDelete(NULL);
// }

// void loop() {
//   // Execution should never get here
// }


/**
 * ESP32 Sample and Process Solution
 * 
 * Sample ADC in an ISR, process on one core, handle CLI on the other.
 * 
 * Note: Changes from original, single-core version are marked with a
 * "%%%" in the comment.
 * 
 * Date: March 3, 2021
 * Author: Shawn Hymel
 * License: 0BSD
 */

// You'll likely need this on vanilla FreeRTOS
//#include <semphr.h>

// Core definitions (assuming you have dual-core ESP32)
// %%% We can use both cores now
static const BaseType_t pro_cpu = 0;
static const BaseType_t app_cpu = 1;

// Settings
static const char command[] = "avg";              // Command
static const uint16_t timer_divider = 8;          // Divide 80 MHz by this
static const uint64_t timer_max_count = 1000000;  // Timer counts to this value
static const uint32_t cli_delay = 10;             // ms delay
enum { BUF_LEN = 10 };      // Number of elements in sample buffer
enum { MSG_LEN = 100 };     // Max characters in message body
enum { MSG_QUEUE_LEN = 5 }; // Number of slots in message queue
enum { CMD_BUF_LEN = 255};  // Number of characters in command buffer

// Pins
static const int adc_pin = A0;

// Message struct to wrap strings for queue
typedef struct Message {
  char body[MSG_LEN];
} Message;

// Globals
static hw_timer_t *timer = NULL;
static TaskHandle_t processing_task = NULL;
static SemaphoreHandle_t sem_done_reading = NULL;
static portMUX_TYPE spinlock = portMUX_INITIALIZER_UNLOCKED;
static QueueHandle_t msg_queue;
static volatile uint16_t buf_0[BUF_LEN];      // One buffer in the pair
static volatile uint16_t buf_1[BUF_LEN];      // The other buffer in the pair
static volatile uint16_t* write_to = buf_0;   // Double buffer write pointer
static volatile uint16_t* read_from = buf_1;  // Double buffer read pointer
static volatile uint8_t buf_overrun = 0;      // Double buffer overrun flag
static float adc_avg;
                                              
//*****************************************************************************
// Functions that can be called from anywhere (in this file)

// Swap the write_to and read_from pointers in the double buffer
// Only ISR calls this at the moment, so no need to make it thread-safe
void IRAM_ATTR swap() {
  volatile uint16_t* temp_ptr = write_to;
  write_to = read_from;
  read_from = temp_ptr;
}

//*****************************************************************************
// Interrupt Service Routines (ISRs)

// This function executes when timer reaches max (and resets)
void IRAM_ATTR onTimer() {

  static uint16_t idx = 0;
  BaseType_t task_woken = pdFALSE;

  // If buffer is not overrun, read ADC to next buffer element. If buffer is
  // overrun, drop the sample.
  if ((idx < BUF_LEN) && (buf_overrun == 0)) {
    write_to[idx] = analogRead(adc_pin);
    idx++;
  }

  // Check if the buffer is full
  if (idx >= BUF_LEN) {

    // If reading is not done, set overrun flag. We don't need to set this
    // as a critical section, as nothing can interrupt and change either value.
    if (xSemaphoreTakeFromISR(sem_done_reading, &task_woken) == pdFALSE) {
      buf_overrun = 1;
    }

    // Only swap buffers and notify task if overrun flag is cleared
    if (buf_overrun == 0) {

      // Reset index and swap buffer pointers
      idx = 0;
      swap();
  
      // A task notification works like a binary semaphore but is faster
      vTaskNotifyGiveFromISR(processing_task, &task_woken);
    }
  }
  
  // Exit from ISR (Vanilla FreeRTOS)
  //portYIELD_FROM_ISR(task_woken);

  // Exit from ISR (ESP-IDF)
  if (task_woken) {
    portYIELD_FROM_ISR();
  }
}

//*****************************************************************************
// Tasks

// Serial terminal task
void doCLI(void *parameters) {

  Message rcv_msg;
  char c;
  char cmd_buf[CMD_BUF_LEN];
  uint8_t idx = 0;
  uint8_t cmd_len = strlen(command);

  // Clear whole buffer
  memset(cmd_buf, 0, CMD_BUF_LEN);

  // Loop forever
  while (1) {

    // Look for any error messages that need to be printed
    if (xQueueReceive(msg_queue, (void *)&rcv_msg, 0) == pdTRUE) {
      Serial.println(rcv_msg.body);
    }

    // Read characters from serial
    if (Serial.available() > 0) {
      c = Serial.read();

      // Store received character to buffer if not over buffer limit
      if (idx < CMD_BUF_LEN - 1) {
        cmd_buf[idx] = c;
        idx++;
      }

      // Print newline and check input on 'enter'
      if ((c == '\n') || (c == '\r')) {
        
        // Print newline to terminal
        Serial.print("\r\n");

        // Print average value if command given is "avg"
        cmd_buf[idx - 1] = '\0';
        if (strcmp(cmd_buf, command) == 0) {
          Serial.print("Average: ");
          Serial.println(adc_avg);
        }

        // Reset receive buffer and index counter
        memset(cmd_buf, 0, CMD_BUF_LEN);
        idx = 0;

      // Otherwise, echo character back to serial terminal
      } else {
        Serial.print(c);
      }
    }

    // Don't hog the CPU. Yield to other tasks for a while
    vTaskDelay(cli_delay / portTICK_PERIOD_MS);
  }
}

// Wait for semaphore and calculate average of ADC values
void calcAverage(void *parameters) {

  Message msg;
  float avg;

  // Start a timer to run ISR every 100 ms
  // %%% We move this here so it runsin core 0
  timer = timerBegin(0, timer_divider, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, timer_max_count, true);
  timerAlarmEnable(timer);

  // Loop forever, wait for semaphore, and print value
  while (1) {

    // Wait for notification from ISR (similar to binary semaphore)
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

    // Calculate average (as floating point value)
    avg = 0.0;
    for (int i = 0; i < BUF_LEN; i++) {
      avg += (float)read_from[i];
      //vTaskDelay(105 / portTICK_PERIOD_MS); // Uncomment to test overrun flag
    }
    avg /= BUF_LEN;

    // Updating the shared float may or may not take multiple isntructions, so
    // we protect it with a mutex or critical section. The ESP-IDF critical
    // section is the easiest for this application.
    portENTER_CRITICAL(&spinlock);
    adc_avg = avg;
    portEXIT_CRITICAL(&spinlock);

    // If we took too long to process, buffer writing will have overrun. So,
    // we send a message to be printed out to the serial terminal.
    if (buf_overrun == 1) {
      strcpy(msg.body, "Error: Buffer overrun. Samples have been dropped.");
      xQueueSend(msg_queue, (void *)&msg, 10);
    }

    // Clearing the overrun flag and giving the "done reading" semaphore must
    // be done together without being interrupted.
    portENTER_CRITICAL(&spinlock);
    buf_overrun = 0;
    xSemaphoreGive(sem_done_reading);
    portEXIT_CRITICAL(&spinlock);
  }
}

//*****************************************************************************
// Main (runs as its own task with priority 1 on core 1)

void setup() {

  // Configure Serial
  Serial.begin(115200);

  // Wait a moment to start (so we don't miss Serial output)
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  Serial.println();
  Serial.println("---FreeRTOS Sample and Process Demo---");

  // Create semaphore before it is used (in task or ISR)
  sem_done_reading = xSemaphoreCreateBinary();

  // Force reboot if we can't create the semaphore
  if (sem_done_reading == NULL) {
    Serial.println("Could not create one or more semaphores");
    ESP.restart();
  }

  // We want the done reading semaphore to initialize to 1
  xSemaphoreGive(sem_done_reading);

  // Create message queue before it is used
  msg_queue = xQueueCreate(MSG_QUEUE_LEN, sizeof(Message));

  // Start task to handle command line interface events. Let's set it at a
  // higher priority but only run it once every 10 ms.
  xTaskCreatePinnedToCore(doCLI,
                          "Do CLI",
                          1024,
                          NULL,
                          2,
                          NULL,
                          app_cpu);

  // Start task to calculate average. Save handle for use with notifications.
  // %%% We set this task to run in Core 0
  xTaskCreatePinnedToCore(calcAverage,
                          "Calculate average",
                          1024,
                          NULL,
                          1,
                          &processing_task,
                          pro_cpu);

  // Delete "setup and loop" task
  vTaskDelete(NULL);
}

void loop() {
  // Execution should never get here
}



