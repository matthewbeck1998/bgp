int a;

int main()
{
    signed unsigned const int b;
    volatile unsigned char c;
    const auto volatile float f;
    @
    a = 1;
    {
        extern volatile unsigned double d;
        @
        int char double c;
        @
        b = 2;
        {
            c = 3;
        }
    }

    {
        float const const float d;
        @
        {
            int double unsigned float e;
            @
            d = 4;
            {
                e = 5;
            }
        }
    }
}
