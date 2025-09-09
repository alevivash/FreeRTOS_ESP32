#_FreeRTOS Semaphore Demo_

This project provides a simple example of using a binary semaphore for task synchronization with FreeRTOS on an ESP32.

A producer task sends a signal (gives the semaphore) every second, and a consumer task waits for that signal (takes the semaphore) before printing a message. This demonstrates how to coordinate actions between different tasks safely.