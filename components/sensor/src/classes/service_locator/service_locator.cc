#include "service_locator.h"
#include "interfaces/clock.h"
#include "classes/clock/hardwareclock.h"
#include "classes/clock/softwareclock.h"

namespace ServiceLocator
{
    enum class ActiveClock
    {
        Hardware,
        Software
    };

    ActiveClock activeClock{ActiveClock::Hardware};
    SoftwareClock softwareClock;
    HardwareClock hardwareClock;

    void UseHardwareClock()
    {
        activeClock = ActiveClock::Hardware;
    }

    void UseSoftwareClock()
    {
        activeClock = ActiveClock::Software;
    }

    Clock& GetClock()
    {
        switch (activeClock)
        {
            case ActiveClock::Hardware:
                return hardwareClock;

            case ActiveClock::Software:
                return softwareClock;

            default:
                return hardwareClock;
        }
    }
}
