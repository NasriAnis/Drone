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
#define NUM_MOTORS                  4
#define MOTOR1                      4
#define MOTOR2                      0
#define MOTOR3                      5
#define MOTOR4                      10

/* ---- MPU ----------------------------------------------------------------- */
#define MPU_ADDR                    0x68
#define MPU_PWR_MGMT_1              0x6B
#define MPU_ACCEL_XOUT              0x3B
#define ACCEL_SCALE                 16384.0f    /* ±2g     */
#define GYRO_SCALE                  131.0f      /* ±250 °/s */

/* ---- LEDC (PWM) ---------------------------------------------------------- */
#define LEDC_FREQ_HZ                20000
#define TIMER                       LEDC_TIMER_0
#define PWM_MAX_DUTY                ((1 << 10) - 1)

/* ---- I2C ----------------------------------------------------------------- */
#define I2C_TIMEOUT_MS              100
#define I2C_SDA_IO                  8
#define I2C_SCL_IO                  9


/* ========================================================================== */
/*                          COMMUNICATION SETTINGS                            */
/* ========================================================================== */

#define WIFI_MODE                   WIFI_MODE_STA
#define WIFI_IF                     WIFI_IF_STA