#Times of each layer (in ms) with 3 decimal place precision
#TODO: FILL IN

CONV_L1 = 1.434
RELU_L1 = 0.026
POOL_L1 = 0.040
CONV_L2 = 1.475
RELU_L2 = 0.004
POOL_L2 = 0.030
CONV_L3 = 0.409
RELU_L3 = 0.001
POOL_L3 = 0.003
FC_L1 = 0.003
SOFTMAX_L1 = 0.000
TOTAL_TIME = 3.425


layer_times = [CONV_L1, RELU_L1, POOL_L1, CONV_L2, RELU_L2, POOL_L2, CONV_L3, RELU_L3, POOL_L3, FC_L1, SOFTMAX_L1]
layer_labels = ["CONV_L1", "RELU_L1", "POOL_L1", "CONV_L2", "RELU_L2", "POOL_L2", "CONV_L3", "RELU_L3", "POOL_L3", "FC_L1", "SOFTMAX_L1"]
layer_types = ["CONV", "RELU", "POOL", "FC", "SOFTMAX"]
layer_percents = [x/TOTAL_TIME for x in layer_times]

f = open('answers.txt','w')

f.write("\nQUESTION 1\n\n")
for data in zip(layer_labels, layer_times, layer_percents):
	f.write("{0:<15}: {1:<10} ms / {2:<10.2%}\n".format(*data))

f.write("\nQUESTION 2\n\n")

total_percents = dict(zip(layer_types, [0]*len(layer_types)))

for label, percent in zip(layer_labels, layer_percents):
	total_percents[label[:label.index("_")]] += percent

for label in layer_types:
	f.write("{0:<15}: {1:<10.2%}\n".format(label, total_percents[label]))

f.write("\nQUESTION 3\n\n")

#TODO: FILL IN
ahmdal = lambda p: 1 / (1 - p + (p / 4))

for label in layer_types:
	f.write("{0:<15}: {1:>3.2f}x\n".format(label, ahmdal(total_percents[label])))

optimal_layer = max(total_percents, key=total_percents.get)

f.write("\nLayer we should optimize: {}\n".format(optimal_layer))
f.close()
