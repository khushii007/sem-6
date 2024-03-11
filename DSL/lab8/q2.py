noOfNodes = int(input('Enter number of nodes: '))
initiator = int(input('Enter id of initiator node: '))
failedCoord = int(input('Enter id of failed: '))
activeList = [initiator]
i = (initiator+1) % noOfNodes
while i != initiator:
    if i != failedCoord:
        activeList.append(i)
        print(activeList)
    i = (i+1) % noOfNodes
max = activeList[0]
for i in range(1, len(activeList)):
    if activeList[i] > max:
        max = activeList[i]
for i in range (len(activeList)):
    if i != initiator:
        print(f'{initiator} send COORDINATOR MESSAGE to {i} declaring {max} as the new coordinator.')