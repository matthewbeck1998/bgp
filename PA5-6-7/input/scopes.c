@p+
int foo(int bar);

int main(int argc, char** argv)
{
    signed unsigned const int b;
    volatile unsigned char c;
    const auto volatile float f;
    @s
    a = 1;
    {
        extern volatile unsigned double d;
        @s
        int char double c;
        @s
        b = 2;
        {
            c = 3;
        }
    }

    {
        float const const float d;
        @s
        {
            int double unsigned float e;
            @s
            d = 4;
            {
                e = 5;
            }
        }
    }
}
