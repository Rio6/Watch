#include "Mode.hpp"

class TimeMode : public Mode {
    public:
        bool display();

    private:
        bool showDate;
        bool debounce = false;
        int start = 0;

        void printDate();
        void printTime();
};
