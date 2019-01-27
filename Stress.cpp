#include "Stress.h"

float stressModifier = 3;
float stressBuffModifier = 1;


 float GhostSPS()
{
	return -0.0051 * stressModifier;

}

 float ChildSPS()
{
	return -0.24 * stressModifier;
}

 float PillSP()
{
	return 30 * stressBuffModifier;
}

 float CollectorSPS()
 {
	 return -0.005 * stressModifier;
 }

 float PostasSPS()
 {
	 return +0.006 * stressBuffModifier;
 }

 float MoneySP()
 {
	 return 10 * stressBuffModifier;
 }

 float BallSP()
 {
	 return 25 * stressBuffModifier;
 }

 float GrafferBeatSP()
 {
	 return 10.f * stressBuffModifier;
 }

 float GrafferSPS()
 {
	 return -0.0006 * stressModifier;
 }

 float moneySPS()
 {
	 return -0.00025 * stressModifier;
}