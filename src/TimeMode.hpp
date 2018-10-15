class TimeMode {
    public:
        void display();

    private:
        static const uint8_t BRIGHTNESS;
        static const long DURATION;

        bool showDate;
        bool debounce = false;
        int start = 0;

        void printDate();
        void printTime();
};
