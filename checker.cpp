#include <iostream>
#include <assert.h>
#include <unistd.h>
using namespace std;

void showCriticalMessage(string message) {
    cout << message << endl;
}

void flash() {
    for (int i = 0; i < 6; i++)
    {
      cout << "\r* " << flush;
      sleep(1);
      cout << "\r *" << flush;
      sleep(1);
    }
}

int TemperaturelsOk(float& temperature) {
	if(temperature > 102 || temperature < 95) 
	{
		showCriticalMessage("Temperature critical!");
		flash();
		return 0;
	}
	return 1;
}

int PulseRatelsOk(float& pulseRate) {
	if(pulseRate < 60 || pulseRate > 100) 
	{
		showCriticalMessage("Pulse Rate is out of range!");
		flash();
		return 0;
	}
	return 1;
}

int OxygenLevelIsOk(float& spo2) {
	if(spo2 < 90) 
	{
     showCriticalMessage("Oxygen Saturation out of range!");
     flash();
     return 0;
    }
	return 1;
}
	
bool vitalsOk(float temperature, float pulseRate, float spo2) {

	//At times we can have more than one Vital value at critical stage. For example, suppose temperature 
	//and spO2 both are at critical level then both messages should get printed. Earlier the code was breaking 
	//on assert even if only 1st vital i.e. temperature was critical (giving 0 return value) therefore only Temperature message was getting printed.
  
	bool resultTemp = TemperaturelsOk(temperature);
	bool resultPulse = PulseRatelsOk(pulseRate);
	bool resultOxy = OxygenLevelIsOk(spo2);
	bool result = (resultTemp && resultPulse && resultOxy);
	return result;
}


int main() {
  assert(!vitalsOk(99, 102, 70));
  assert(vitalsOk(98.1f, 70, 98));
  
  
  cout << "Done\n";
}