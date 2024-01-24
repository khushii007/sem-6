import numpy as np
array1=np.array([(1,2,3),(4,5,6)])
rowSums = np.sum(array1, axis=1)
colSums = np.sum(array1, axis=0)
print("Sum of rows: ", rowSums)
print("Sum of columns: ", colSums)