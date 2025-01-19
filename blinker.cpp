// LED Blink Program with Thread-Safe Termination
#include <pigpio.h>      // Raspberry Pi GPIO library
#include <iostream>      // For standard I/O
#include <unistd.h>      // For sleep function
#include <signal.h>      // For signal handling (Ctrl+C)
#include <atomic>        // For thread-safe boolean
#include <thread>        // For input handling thread
#define LED_PIN 18      // Define GPIO pin for LED

// Thread-safe boolean for program termination
std::atomic<bool> running{true};

// Function to handle keyboard input in separate thread
void input_thread() {
   system("stty raw");   // Set terminal to raw mode (immediate key detection)
   char input;
   while(running) {
      input = getchar(); // Get character without waiting for enter
      if(input == 'q'){  // Check for 'q' key
         running = false; // Signal program to terminate
      }
   }
   system("stty cooked"); // Restore terminal to normal mode
}

// Handler for Ctrl+C and termination signals
void signalHandler(int signum) {
        std::cout << "\nStopping LED and cleaning up..." << std::endl;
        gpioWrite(LED_PIN, 0);  // Turn off LED
        gpioTerminate();        // Cleanup GPIO
        exit(signum);           // Exit program
}

int main(){
        // Start the input handling thread
        std::thread input(input_thread);
        
        // Set up signal handlers for clean termination
        signal(SIGINT, signalHandler);
        signal(SIGTERM, signalHandler);
        
        // Initialize pigpio library
        if(gpioInitialise() < 0){
           std::cout << "pigpio initialization failed" << std::endl;
           return 1;
        }
        
        // Configure LED pin as output
        gpioSetMode(LED_PIN, PI_OUTPUT);
        
        // Display startup messages
        std::cout << "LED Blinking Program Started\n\r" << std::flush;
        std::cout << "Press 'q' to Exit\n\r" << std::flush;
        
        // Main LED blinking loop
        while(running){
                gpioWrite(LED_PIN, 1);    // Turn LED on
                std::cout << "LED ON\n\r" << std::flush;
                sleep(1);                  // Wait 1 second
                gpioWrite(LED_PIN, 0);     // Turn LED off
                std::cout << "LED OFF\n\r" << std::flush;
                sleep(1);                  // Wait 1 second
        }
        
        // Clean up
        input.join();           // Wait for input thread to finish
        gpioWrite(LED_PIN, 0);  // Ensure LED is off
        gpioTerminate();        // Cleanup GPIO
        return 0;
}