import numpy as np

#a
list1 = [2.4, 10, 5.2]
array1 = np.array(list1)
print(array1.dtype)
print(array1)

#b
tuple1 = (2.4, 10, 5.2)
array2 = np.array(tuple1)
print(array2)

#c
array3 = np.zeros((3,4))
print(array3)

#d
seq = np.arange(0,20,5)
print(seq)

#e
array4 = np.array([[1,2,3,4],[5,6,7,8],[9,10,11,12]])
array5 = np.reshape(array4, (2,2,3))
print("Array before: ")
print(array4)
print("Array after: ")
print(array5)

#f
array6 = np.array([[1,2,3,4],[8,7,6,5],[11,12,9,10]])
#print(array6)
print("Full array max: ", array6.max(), " min: ", array6.min(), " sum: ", array6.sum())
print("Row-wise max: ", array6.max(axis=1), " min: ", array6.min(axis=1), " sum: ", array6.sum(axis=1))
print("Column-wise max: ", array6.max(axis=0), " min: ", array6.min(axis=0), " sum: ", array6.sum(axis=0))