__kernel void binary_to_decimal(__global int *input, __global int *output, const int N) {
    int gid = get_global_id(0); // Global ID of the current work-item

    if (gid < N) {
        int decimal = 0;
        int multiplier = 1;
        int binary = input[gid];

        // Convert binary to decimal
        while (binary != 0) {
            int remainder = binary % 10;
            decimal += remainder * multiplier;
            binary /= 10;
            multiplier *= 2;
        }

        output[gid] = decimal; // Store the decimal value in the output array
    }
}
