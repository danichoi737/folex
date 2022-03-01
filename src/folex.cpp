/******************************************************************************
* Copyright 2022 Hyunwook Choi
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
******************************************************************************/

#include "folex.hpp"


void *threadActuatorValue(void *arg)
{
  while (true)
  {
    actuator.readPresentAngle();
    actuator.readPresentVelocity();
    nanosleep(&read_rate, NULL);
  }
}


int main()
{
  actuator.initActuator();
  actuator.enableActuator(0);

  pthread_create(&actuator_value_, NULL, threadActuatorValue, NULL);
  pthread_join(actuator_value_, NULL);

  return 0;
}
