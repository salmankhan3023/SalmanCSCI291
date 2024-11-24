#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/distance_sensor.h>
#include <webots/light_sensor.h>
#include <stdio.h>

#define TIME_STEP 64
#define MAX_SPEED 6.28

// Initialize motors
WbDeviceTag left_motor, right_motor;
// Initialize proximity sensors
WbDeviceTag ps[8];
// Initialize light sensors
WbDeviceTag ls[8];

double highest_light_intensity = -1.0;

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

void record_light_intensity() {
  double total_light_intensity = 0.0;
  for (int i = 0; i < 8; i++) {
    total_light_intensity += wb_light_sensor_get_value(ls[i]);
  }
  double average_light_intensity = total_light_intensity / 8.0;

  if (average_light_intensity > highest_light_intensity) {
    highest_light_intensity = average_light_intensity;
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

  while (wb_robot_step(TIME_STEP) != -1) {
    follow_wall();
    record_light_intensity();
    // Optionally, print the highest light intensity for debugging
    printf("Highest light intensity: %f\n", highest_light_intensity);
  }

  wb_robot_cleanup();
  return 0;
}
