#include "Stress.h"

float stressModifier = 1;
float stressBuffModifier = 1;


 float GhostSPS()
{
	return -0.005 * stressModifier;

}

 float ChildSPS()
{
	return -0.12 * stressModifier;
}

 float PillSP()
{
	return 30 * stressBuffModifier;
}

