__kernel void one_complement(__global int *input, __global int *output, const int N) {
    int gid = get_global_id(0); // Global ID of the current work-item

    if (gid < N) {
        output[gid] = 1 - input[gid]; // Calculate one's complement
    }
}
