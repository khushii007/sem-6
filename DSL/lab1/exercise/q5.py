list = [ 'abcd', 786 , 2.23, 'john', 70.2 ]
tinylist = [123, 'john']
print (list) # Prints complete list
print (list[0]) # Prints first element of the list
print (list[1:3]) # Prints elements starting from 2nd till 3rd
print (list[2:]) # Prints elements starting from 3rd element
print (tinylist * 2) # Prints list two times
print (list + tinylist) # Prints concatenated lists

list.append('maths') # to add an element
print(list)

del list[2] # to delete an element
print(list)

if 'physics' in list: # to check if an element exists
    print('true')
else:
    print('false')
if 70.2 in list:
    print('true')
else:
    print('false')

list.pop() # remove and return the last item from the list
print(list)

list.insert (2, 'happy') # insert an item in the specified index
print(list)

list.remove('abcd') # remove the item specified
print(list)

list.reverse() #reverse the objects of the list in place
print(list)