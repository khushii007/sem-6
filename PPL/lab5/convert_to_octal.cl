
__kernel void convert_to_octal(__global int *input, __global int *output, const int N)
{
    int gid = get_global_id(0); // Global ID of the current work-item

    if (gid < N)
    {
        int decimal = input[gid]; // Get the decimal input value
        int octal = 0;
        int place = 1;

        // Convert decimal to octal
        while (decimal != 0)
        {
            octal += (decimal % 8) * place;
            decimal /= 8;
            place *= 10;
        }

        output[gid] = octal; // Store the octal value in the output array
    }
}
