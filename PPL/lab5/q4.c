#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>

#define MAX_SOURCE_SIZE (0x100000)

int main(void) {
    // Input parameters
    int N;
    printf("Enter the number of binary numbers: ");
    scanf("%d", &N);

    // Allocate memory for input and output arrays
    int *input = (int *)malloc(N * sizeof(int));
    int *output = (int *)malloc(N * sizeof(int));

    // Input binary numbers
    printf("Enter %d binary numbers (each number should be 0 or 1):\n", N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &input[i]);
        if (input[i] != 0 && input[i] != 1) {
            printf("Invalid binary number entered. Please enter 0 or 1.\n");
            return 1;
        }
    }

    // Load the kernel code
    FILE *fp;
    char *source_str;
    size_t source_size;
    fp = fopen("binary_to_decimal.cl", "r");
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

    // Create memory buffers for input and output arrays
    cl_mem input_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, N * sizeof(int), NULL, &ret);
    cl_mem output_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY, N * sizeof(int), NULL, &ret);

    // Copy input array to memory buffer
    ret = clEnqueueWriteBuffer(command_queue, input_mem_obj, CL_TRUE, 0, N * sizeof(int), input, 0, NULL, NULL);

    // Create a program from the kernel source
    cl_program program = clCreateProgramWithSource(context, 1, (const char **)&source_str, (const size_t *)&source_size, &ret);

    // Build the program
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

    // Create the OpenCL kernel
    cl_kernel kernel = clCreateKernel(program, "binary_to_decimal", &ret);

    // Set the arguments of the kernel
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&input_mem_obj);
    ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&output_mem_obj);
    ret = clSetKernelArg(kernel, 2, sizeof(int), (void *)&N);

    // Execute the kernel
    size_t global_item_size = N;
    size_t local_item_size = 1;
    ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);

    // Read the output data from the buffer
    ret = clEnqueueReadBuffer(command_queue, output_mem_obj, CL_TRUE, 0, N * sizeof(int), output, 0, NULL, NULL);

    // Display the result
    printf("Decimal Values:\n");
    for (int i = 0; i < N; i++) {
        printf("%d -> %d\n", input[i], output[i]);
    }

    // Clean up
    ret = clFlush(command_queue);
    ret = clFinish(command_queue);
    ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseMemObject(input_mem_obj);
    ret = clReleaseMemObject(output_mem_obj);
    ret = clReleaseCommandQueue(command_queue);
    ret = clReleaseContext(context);

    // Free allocated memory
    free(input);
    free(output);
    free(source_str);

    return 0;
}
