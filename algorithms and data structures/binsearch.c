unsigned long binsearch(unsigned long nel, int (*compare)(unsigned long i))
{
    unsigned long left = 0;
    unsigned long right = nel;

    while (left < right) {
        unsigned long mid = left + (right - left) / 2;
        int res = compare(mid);

        if (res == 0) {
            return mid;
        } else if (res < 0) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return nel;
}
