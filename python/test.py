import time
start = time.time_ns()
j = 0
for i in range(1000000000):
	j+=1
end = time.time_ns()
print(end - start)