#pragma once

/* ========================================================================== */
/*                             CONTROLLER SETTINGS                            */
/* ========================================================================== */

/* ---- Joystick ------------------------------------------------------------ */
#define JOYSTICK_ADC                ADC_UNIT_1
#define JOYSTICK1_UP_DOWN_CH        0
#define JOYSTICK1_ROTATE_CH         1
#define JOYSTICK2_ADV_REAR_CH       2
#define JOYSTICK2_RIGHT_LEFT_CH     3

#define INVERSE_JOYSTICK            1


/* ========================================================================== */
/*                               DRONE SETTINGS                               */
/* ========================================================================== */

/* ---- Motors -------------------------------------------------------------- */
#define NUM_MOTORS                 4
#define MOTOR1_RL_GPIO             4
#define MOTOR2_FL_GPIO             0
#define MOTOR3_FR_GPIO             5
#define MOTOR4_RR_GPIO             10

#define MOTOR1_RL_NUM              0
#define MOTOR2_FL_NUM              1
#define MOTOR3_FR_NUM              2
#define MOTOR4_RR_NUM              3

/* ---- MPU ----------------------------------------------------------------- */
#define MPU_ADDR                    0x68
#define MPU_PWR_MGMT_1              0x6B
#define MPU_ACCEL_XOUT              0x3B
#define ACCEL_SCALE                 16384.0f    /* ±2g     */
#define GYRO_SCALE                  131.0f      /* ±250 °/s */

/* ---- LEDC (PWM) ---------------------------------------------------------- */
#define LEDC_FREQ_HZ                20000
#define LEDC_TIMER                  LEDC_TIMER_0
#define LEDC_CLOCK_CFG              LEDC_USE_APB_CLK
#define LEDC_SPEED_MODE             LEDC_LOW_SPEED_MODE

#define LEDC_DUTY_RESOLUTION        LEDC_TIMER_10_BIT
#define LEDC_PWN_MAX_DUTY           ((1 << 10) - 1)

#define LEDC_START                  0

/* ---- I2C ----------------------------------------------------------------- */
#define I2C_TIMEOUT_MS              100
#define I2C_SDA_IO                  8
#define I2C_SCL_IO                  9

/* ---- PID ----------------------------------------------------------------- */
#define GYRO_TRUST                  0.98f
#define ACCE_TRUST                  0.02f

#define MAX_ANGLE_DEG               25.0f
#define MAX_YAW_DPS                 120.0f

#define THROTTLE_RATE               0.5f

#define ROLL_KP    0.02f
#define ROLL_KI    0.0f
#define ROLL_KD    0.0f

#define PITCH_KP   0.02f
#define PITCH_KI   0.0f
#define PITCH_KD   0.0f

#define YAW_KP     0.005f
#define YAW_KI     0.0f
#define YAW_KD     0.0f

/* ========================================================================== */
/*                          COMMUNICATION SETTINGS                            */
/* ========================================================================== */

#define WIFI_MODE                   WIFI_MODE_STA
#define WIFI_IF                     WIFI_IF_STA