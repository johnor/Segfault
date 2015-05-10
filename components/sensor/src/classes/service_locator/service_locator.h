class Clock;

namespace ServiceLocator
{
    void UseHardwareClock();
    void UseSoftwareClock();
    Clock& GetClock();
}
