#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/distance_sensor.h>
#include <webots/light_sensor.h>
#include <stdio.h>

#define TIME_STEP 64
#define MAX_SPEED 6.28
#define RUN_DURATION 720.0 // 12 minutes in seconds (5 * 60)
#define WAIT_DURATION 10.0 // Wait time in seconds

WbDeviceTag left_motor, right_motor; // Initialize motors
WbDeviceTag ps[8]; // Initialize proximity sensors
WbDeviceTag ls[8]; // Initialize light sensors

double highest_light_intensity = -1.0;
double threshold_light_intensity = -1.0;
double start_time;

void set_speed(double left_speed, double right_speed) {
  wb_motor_set_velocity(left_motor, left_speed);
  wb_motor_set_velocity(right_motor, right_speed);
}

void follow_wall() {
  double ps_values[8];
  for (int i = 0; i < 8; i++) {
    ps_values[i] = wb_distance_sensor_get_value(ps[i]);
  }

  bool front_wall = ps_values[0] > 90.0 || ps_values[7] > 90.0;
  bool left_wall = ps_values[5] > 100.0;

  if (front_wall) {
    set_speed(1.0, -1.0);  // Turn right
  } else if (left_wall) {
    set_speed(2.0, 2.0);   // Move forward
  } else {
    set_speed(-1.0, 2.0);  // Turn left
  }
}

double get_average_light_intensity() {
  double total_light_intensity = 0.0;
  for (int i = 0; i < 8; i++) {
    total_light_intensity += wb_light_sensor_get_value(ls[i]);
  }
  return total_light_intensity / 8.0;
}

void record_light_intensity() {
  double average_light_intensity = get_average_light_intensity();

  if (average_light_intensity > highest_light_intensity) {
    highest_light_intensity = average_light_intensity;
    printf("New highest light intensity: %f\n", highest_light_intensity);
  }
}

void wait(double seconds) {
  double start = wb_robot_get_time();
  while (wb_robot_get_time() - start < seconds) {
    wb_robot_step(TIME_STEP);
  }
}

int main() {
  wb_robot_init();

  // Get motors
  left_motor = wb_robot_get_device("left wheel motor");
  right_motor = wb_robot_get_device("right wheel motor");
  wb_motor_set_position(left_motor, INFINITY);
  wb_motor_set_position(right_motor, INFINITY);
  wb_motor_set_velocity(left_motor, 0.0);
  wb_motor_set_velocity(right_motor, 0.0);

  // Get and enable proximity sensors
  char ps_names[8][4] = {"ps0", "ps1", "ps2", "ps3", "ps4", "ps5", "ps6", "ps7"};
  for (int i = 0; i < 8; i++) {
    ps[i] = wb_robot_get_device(ps_names[i]);
    wb_distance_sensor_enable(ps[i], TIME_STEP);
  }

  // Get and enable light sensors
  char ls_names[8][4] = {"ls0", "ls1", "ls2", "ls3", "ls4", "ls5", "ls6", "ls7"};
  for (int i = 0; i < 8; i++) {
    ls[i] = wb_robot_get_device(ls_names[i]);
    wb_light_sensor_enable(ls[i], TIME_STEP);
  }

  start_time = wb_robot_get_time();

  while (wb_robot_step(TIME_STEP) != -1) {
    follow_wall();
    record_light_intensity();

    double current_time = wb_robot_get_time();

    if (current_time - start_time >= RUN_DURATION) {
      printf("Stopping after 5 minutes.\n");
      set_speed(0, 0);  // Stop the robot
      wait(WAIT_DURATION);  // Wait for a few seconds

      // Set the threshold light intensity
      threshold_light_intensity = highest_light_intensity - 100.5 ;
      printf("Set threshold light intensity: %f\n", threshold_light_intensity);

      // Restart the robot and continue moving
      start_time = wb_robot_get_time();
      while (wb_robot_step(TIME_STEP) != -1) {
        follow_wall();

        double current_light_intensity = get_average_light_intensity();
        if (current_light_intensity >= threshold_light_intensity) {
          printf("Stopping at light intensity: %f\n", current_light_intensity);
          set_speed(0, 0);  // Stop the robot
          break;
        }

        
        printf("Current light intensity: %f\n", current_light_intensity);
        printf("looking for %f or higher ",threshold_light_intensity);
      }
      break;
    }

 
    printf("Current run time: %f seconds\n", current_time - start_time);
    printf("Highest light intensity so far: %f\n", highest_light_intensity);
  }

  wb_robot_cleanup();  // Cleanup Webots resources
  return 0;  // Exit the program
