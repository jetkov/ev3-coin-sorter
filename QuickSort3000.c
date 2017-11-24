#include "Interface.c"
#include "Hardware.c"

task main()
{
  while (getButtonPress(buttonBack) == 0)
  {
    StartTask(autoHopper);

  }
}
