#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <Windows.h>
#include <conio.h> 

#define MAX_ALARMS 5


typedef struct {
    int hour;
    int minute;
    int triggered; 
} Alarm;

Alarm alarms[MAX_ALARMS];
int alarm_count = 0;

void display_time();
void manage_alarms();
void add_alarm();
void remove_alarm();
void check_alarms(struct tm *current_time);

int main() {
    int choice;

    while (1) {
        printf("\nDigital Clock\n");
        printf("1. Display Time\n");
        printf("2. Manage Alarms\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                display_time();
                break;
            case 2:
                manage_alarms();
                break;
            case 3:
                printf("Exiting\n");
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}

void display_time() {
    time_t rawtime;
    struct tm *current_time;

    while (1) {
        time(&rawtime);
        current_time = localtime(&rawtime);

        // Clear the console
        system("cls");

        printf("Current Time: %02d:%02d:%02d\n", current_time->tm_hour, current_time->tm_min, current_time->tm_sec);
        check_alarms(current_time);

        printf("\nPress 'q' and Enter to return to the main menu...\n");
        Sleep(1000); 

        if (_kbhit()) { 
            char c = _getch(); 
            if (c == 'q' || c == 'Q') {
                break;
            }
        }
    }
}

void manage_alarms() {
    int choice;

    while (1) {
        printf("\nAlarm Management\n");
        printf("1. Add Alarm\n");
        printf("2. Remove Alarm\n");
        printf("3. View Alarms\n");
        printf("4. Return to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_alarm();
                break;
            case 2:
                remove_alarm();
                break;
            case 3:
                printf("\nCurrent Alarms:\n");
                for (int i = 0; i < alarm_count; i++) {
                    printf("Alarm %d: %02d:%02d\n", i + 1, alarms[i].hour, alarms[i].minute);
                }
                break;
            case 4:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

void add_alarm() {
    if (alarm_count >= MAX_ALARMS) {
        printf("\nAlarm limit reached. Cannot add more alarms.\n");
        return;
    }

    int hour, minute;
    printf("\nEnter alarm time (HH MM): ");
    scanf("%d %d", &hour, &minute);

    if (hour < 0 || hour > 23 || minute < 0 || minute > 59) {
        printf("Invalid time. Please enter a valid time.\n");
        return;
    }

    alarms[alarm_count].hour = hour;
    alarms[alarm_count].minute = minute;
    alarms[alarm_count].triggered = 0; 
    alarm_count++;

    printf("Alarm set for %02d:%02d\n", hour, minute);
}

void remove_alarm() {
    if (alarm_count == 0) {
        printf("\nNo alarms to remove.\n");
        return;
    }

    int index;
    printf("\nEnter the alarm number to remove (1 to %d): ", alarm_count);
    scanf("%d", &index);

    if (index < 1 || index > alarm_count) {
        printf("Invalid alarm number.\n");
        return;
    }

    for (int i = index - 1; i < alarm_count - 1; i++) {
        alarms[i] = alarms[i + 1];
    }
    alarm_count--;

    printf("Alarm removed successfully.\n");
}

void check_alarms(struct tm *current_time) {
    for (int i = 0; i < alarm_count; i++) {
        if (alarms[i].hour == current_time->tm_hour && alarms[i].minute == current_time->tm_min) {
            if (!alarms[i].triggered) {
                printf("\n*** Alarm! Time: %02d:%02d ***\n", alarms[i].hour, alarms[i].minute);
                alarms[i].triggered = 1; 
            }
        } else {
            alarms[i].triggered = 0; 
        }
    }
}
