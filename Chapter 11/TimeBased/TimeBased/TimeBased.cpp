#include <cstdio>

namespace 
{
  const float MAX_TIME     = 10.0f;
  const float ACCELERATION = 20.f;
  const int MAX_STEPS      = 4;
}

float Kinematics(float pos, float vel, float accel, float totalTime)
{
	return pos + (vel * totalTime) + (.5f * (accel * (totalTime * totalTime)));
}
float EulerIntegration(float pos, float vel, float accel, float totalTime, float dt)
{
	float time = 0.0f;
	while (time < totalTime)
	{
		pos += vel * dt;
		vel += accel * dt;
		time += dt;
	}
	return pos;
}
void EulerIntegrationPrint(float pos, float vel, float accel, float totalTime, float dt)
{
	float time = 0.0f;
	while (time <= totalTime)
	{
		printf("  Time = %-2.0f pos = %7.2f vel = %6.2f\n", time, pos, vel);
		pos += vel * dt;
		vel += accel * dt;
		time += dt;
	}
}

int main(void)
{
	float eulerTimeSteps[MAX_STEPS] = {1.0f,  1.0f/30.0f, 1.0f/60.0f, 1.0f/120.0f };
	printf("Kinematics\n");
	printf("  Total Time = %-10.6f pos = %-10.2f\n\n", MAX_TIME, Kinematics(0, 0, ACCELERATION, MAX_TIME));
	printf("Euler Integration\n");
	for (int i = 0; i < MAX_STEPS; ++i)
	{
		printf("  dt = %-10.6f pos = %-10.2f\n",eulerTimeSteps[i],  EulerIntegration(0, 0, ACCELERATION, MAX_TIME, eulerTimeSteps[i]));
	}
	printf("Time Step\n");
	EulerIntegrationPrint(0, 0, ACCELERATION, MAX_TIME, 1);

	return 0;
}