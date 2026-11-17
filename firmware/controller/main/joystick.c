#include "comunication.h"

void write_reading(int up, int down, int left, int right, int forward, int rear){
	controler_readings.up = up;
	controler_readings.down = down;
	controler_readings.left = left;
	controler_readings.right = right;
	controler_readings.forward = forward;
	controler_readings.rear = rear;
}
