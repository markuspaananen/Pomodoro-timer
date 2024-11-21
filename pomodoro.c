#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#define POMODORO_DURATION 25 * 60  // 25 minutes in seconds
#define BREAK_DURATION 5 * 60     // 5 minutes in seconds

void send_notification(const char *title, const char *message) {
    // Use system command 'notify-send' to send a notification
    char command[256];
    snprintf(command, sizeof(command), "notify-send \"%s\" \"%s\"", title, message);
    system(command);
}
void play_sound() {
    // Use linux system command 'aplay' to play a WAV file
    system("aplay ~/Music/level-up.wav");  // Replace with your sound file path
}

int main() {
    char valinta;
    time_t start_time, current_time;
    int elapsed_time;

    while(1) {
        // Display menu
        printf("Pomodoro Timer:\n");
        printf("Press 's' to Start Timer, 'c' to Check Current Time, or 'q' to Quit.\n");
        scanf(" %c", &valinta);  // Note the space before %c to consume any leftover newline

        switch(valinta) {
            case 'c':
                current_time = time(NULL);
                printf("(C)urrent time: %s", ctime(&current_time));
                break;
            case 's':
                // Start the Pomodoro timer (25 minutes)
                printf("Starting Pomodoro Timer for 25 minutes...\n");

                start_time = time(NULL);
                elapsed_time = 0;

                // Timer loop for 25 minutes (Pomodoro duration)
                while (elapsed_time < POMODORO_DURATION) {
                    current_time = time(NULL);
                    elapsed_time = (int)difftime(current_time, start_time);

                    printf("\rTime left: %02d:%02d", 
                           (POMODORO_DURATION - elapsed_time) / 60, 
                           (POMODORO_DURATION - elapsed_time) % 60);
                    fflush(stdout);  // Ensure the output is updated

                    // Sleep for 1 second
                    sleep(1);
                }

                printf("\nPomodoro session complete! Take a 5-minute break.\n");
                
                // Send notification when Pomodoro session finishes
                send_notification("Pomodoro Timer", "Pomodoro session complete! Take a 5-minute break.");
		play_sound();

                // Break time (5 minutes)
                start_time = time(NULL);
                elapsed_time = 0;

                while (elapsed_time < BREAK_DURATION) {
                    current_time = time(NULL);
                    elapsed_time = (int)difftime(current_time, start_time);

                    printf("\rBreak time left: %02d:%02d", 
                           (BREAK_DURATION - elapsed_time) / 60, 
                           (BREAK_DURATION - elapsed_time) % 60);
                    fflush(stdout);  // Ensure the output is updated

                    // Sleep for 1 second
                    sleep(1);
                }

                printf("\nBreak complete! Ready for the next Pomodoro session.\n");

                // Send notification when Break session finishes
                send_notification("Pomodoro Timer", "Break complete! Ready for the next Pomodoro session.");

                break;
            case 'q':
                printf("Quitting program...\n");
                return 0;
            default:
                printf("Invalid input. Please press 's', 'c', or 'q'.\n");
        }
    }

    return 0;
}
