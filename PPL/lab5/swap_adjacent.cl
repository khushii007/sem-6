__kernel void swap_adjacent(__global int *array, const int N) {
    int gid = get_global_id(0); // Global ID of the current work-item

    if (gid < N / 2) { // Each work-item swaps adjacent elements
        int temp = array[2 * gid];
        array[2 * gid] = array[2 * gid + 1];
        array[2 * gid + 1] = temp;
    }
}
