#include <math.h>
#include "esp_timer.h"

#include "mpu.h"
#include "comunication.h"
#include "motors.h"
#include "settings.h"

// MPU data structre         ->  cords
// Controller Data structure ->  controler_readings
// Handling Motors           ->  void motor_set(int i, float speed)

#define RAD2DEG        57.2958f

typedef struct {
    float kp, ki, kd;
    float integral;
} pid_ctrl_t;

static pid_ctrl_t pid_roll  = { .kp = ROLL_KP,  .ki = ROLL_KI,  .kd = ROLL_KD  };
static pid_ctrl_t pid_pitch = { .kp = PITCH_KP, .ki = PITCH_KI, .kd = PITCH_KD };
static pid_ctrl_t pid_yaw   = { .kp = YAW_KP,   .ki = YAW_KI,   .kd = YAW_KD   };

static float roll, pitch;        // filtered angles (deg)
static float throttle = 0;       // 0..1, kept between calls
static int64_t last_us = 0;

static float pid_update(pid_ctrl_t *p, float setpoint, float measure, float rate, float dt)
{
    float error = setpoint - measure;

    p->integral += p->ki * error * dt;
    if (p->integral >  0.1f) p->integral =  0.1f;
    if (p->integral < -0.1f) p->integral = -0.1f;

    return p->kp * error + p->integral - p->kd * rate;
}

void pid_correct(){
	int64_t now = esp_timer_get_time();
	float dt = (now - last_us) / 1e6f;
	last_us = now;
	if (dt <= 0.0f || dt > 0.05f) return;

	mpu_read_cords(&cords);

	// angles: gyro (smooth) + accelerometer (no drift)
	float acc_roll  = atan2f(cords.ay, cords.az) * RAD2DEG;
	float acc_pitch = atan2f(-cords.ax, sqrtf(cords.ay * cords.ay + cords.az * cords.az)) * RAD2DEG;
	roll  = GYRO_TRUST * (roll  + cords.gx * dt) + ACCE_TRUST * acc_roll;
	pitch = GYRO_TRUST * (pitch + cords.gy * dt) + ACCE_TRUST * acc_pitch;

	// setpoints from the controller (-100..100)
	float roll_sp  = controler_readings.left_right * MAX_ANGLE_DEG;
	float pitch_sp = controler_readings.forward_rear * MAX_ANGLE_DEG;
	float yaw_sp   = controler_readings.rotate * MAX_YAW_DPS;

	throttle += controler_readings.up_down * THROTTLE_RATE * dt;
    if (throttle > 1.0f) throttle = 1.0f;
    if (throttle < 0.0f) throttle = 0.0f;

    // PID
    float r_out = pid_update(&pid_roll,  roll_sp,  roll,     cords.gx, dt);
    float p_out = pid_update(&pid_pitch, pitch_sp, pitch,    cords.gy, dt);
    float y_out = pid_update(&pid_yaw,   yaw_sp,   cords.gz, 0.0f,     dt);   // yaw: rate control

    // mixer: 0 = rear-left, 1 = front-left, 2 = front-right, 3 = rear-right
    motor_set(MOTOR1_RL_NUM, throttle + r_out + p_out - y_out);
    motor_set(MOTOR2_FL_NUM, throttle + r_out - p_out + y_out);
    motor_set(MOTOR3_FR_NUM, throttle - r_out - p_out - y_out);
    motor_set(MOTOR4_RR_NUM, throttle - r_out + p_out + y_out);
}