inputPath = input("Enter input file path: ")
outputPath = input("Enter output file path: ")
with open(inputPath,"r") as f1:
	data = f1.read()
	reversed_data = data[::-1]
with open(outputPath,"w") as f2:
	f2.write(reversed_data)
print(f"Content reversed and saved to {outputPath}")
