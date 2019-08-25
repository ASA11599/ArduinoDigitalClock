#include <string>

namespace DigitalClock
{
    class Time
    {
        private:

            int hours;
            int minutes;
            int seconds;
            enum Period {AM, PM};
            Period period;

            static bool in_range(int value, int start, int end)
            {
                return (value >= start) && (value <= end);
            }

            static bool valid_time(int hours, int minutes, int seconds)
            {
                return (Time::in_range(hours, 0, 12))
                        && (Time::in_range(minutes, 0, 59))
                        && (Time::in_range(seconds, 0, 59));
            }

            static std::string format(int n)
            {
                return (n > 9) ? (std::to_string(n)) : ("0" + std::to_string(n));
            }

            std::string periodToString()
            {
                switch (this->period)
                {
                case AM:
                    return "AM";
                case PM:
                    return "PM";
                default:
                    break;
                }
            }

            void incPeriod()
            {
                switch (this->period)
                {
                case AM:
                    this->period = PM;;
                    break;
                case PM:
                    this->period = AM;
                    break;
                default:
                    break;
                }
            }

            void incHours()
            {
                if (this->hours == 11) {
                    this->hours = 0;
                    this->incPeriod();
                } else this->hours++;
            }

            void incMinutes()
            {
                if (this->minutes == 59) {
                    this->minutes = 0;
                    this->incHours();
                } else this->minutes++;
            }

            void incSeconds()
            {
                if (this->seconds == 59) {
                    this->seconds = 0;
                    this->incMinutes();
                } else this->seconds++;
            }

        public:

            Time()
            {
                this->hours = 0;
                this->minutes = 0;
                this->seconds = 0;
                this->period = AM;
            }

            Time(int hours, int minutes, int seconds, Period period)
            {
                if (!(Time::valid_time(hours, minutes, seconds))) Time();
                else {
                    this->hours = hours;
                    this->minutes = minutes;
                    this->seconds = seconds;
                    this->period = period;
                }
            }

            void tick()
            {
                this->incSeconds();
            }

            std::string toString()
            {
                return format(this->hours)
                        + ":"
                        + format(this->minutes)
                        + ":"
                        + format(this->seconds)
                        + " "
                        + this->periodToString();
            }

    };
}