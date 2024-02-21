#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>

#define MAX_SOURCE_SIZE (0x100000)

int main(void) {
    // Input parameters
    int N;
    printf("Enter the number of integers (even number): ");
    scanf("%d", &N);

    if (N % 2 != 0) {
        printf("Please enter an even number.\n");
        return 1;
    }

    // Allocate memory for input array
    int *array = (int *)malloc(N * sizeof(int));

    // Input integers
    printf("Enter %d integers:\n", N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &array[i]);
    }

    // Load the kernel code
    FILE *fp;
    char *source_str;
    size_t source_size;
    fp = fopen("swap_adjacent.cl", "r");
    if (!fp) {
        fprintf(stderr, "Failed to load kernel.\n");
        exit(1);
    }
    source_str = (char *)malloc(MAX_SOURCE_SIZE);
    source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);
    fclose(fp);

    // Get platform and device information
    cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
    ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, &ret_num_devices);

    // Create an OpenCL context
    cl_context context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);

    // Create a command queue
    cl_command_queue command_queue = clCreateCommandQueue(context, device_id, NULL, &ret);

    // Create memory buffer for input array
    cl_mem array_mem_obj = clCreateBuffer(context, CL_MEM_READ_WRITE, N * sizeof(int), NULL, &ret);

    // Copy input array to memory buffer
    ret = clEnqueueWriteBuffer(command_queue, array_mem_obj, CL_TRUE, 0, N * sizeof(int), array, 0, NULL, NULL);

    // Create a program from the kernel source
    cl_program program = clCreateProgramWithSource(context, 1, (const char **)&source_str, (const size_t *)&source_size, &ret);

    // Build the program
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

    // Create the OpenCL kernel
    cl_kernel kernel = clCreateKernel(program, "swap_adjacent", &ret);

    // Set the arguments of the kernel
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&array_mem_obj);
    ret = clSetKernelArg(kernel, 1, sizeof(int), (void *)&N);

    // Execute the kernel
    size_t global_item_size = N / 2; // Number of swaps is half of the number of elements
    size_t local_item_size = 1;
    ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);

    // Read the output data from the buffer
    ret = clEnqueueReadBuffer(command_queue, array_mem_obj, CL_TRUE, 0, N * sizeof(int), array, 0, NULL, NULL);

    // Display the result
    printf("Array after swapping adjacent elements:\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    // Clean up
    ret = clFlush(command_queue);
    ret = clFinish(command_queue);
    ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseMemObject(array_mem_obj);
    ret = clReleaseCommandQueue(command_queue);
    ret = clReleaseContext(context);

    // Free allocated memory
    free(array);
    free(source_str);

    return 0;
}
