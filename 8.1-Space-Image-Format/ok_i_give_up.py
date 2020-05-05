#!/usr/bin/env python3

class layer:
    def __init__(self, zeroes = 0, ones = 0, twos = 0):
        self.zeroes = zeroes
        self.ones = ones
        self.twos = twos
    def character_count(self):
        return self.zeroes + self.ones + self.twos

width = 25
height = 6

pixels_per_layer = width * height

list_of_layers = []

list_of_layers.append(layer())

with open("input", "r") as file:
    for character in file.read():

        if (list_of_layers[-1].character_count() == pixels_per_layer):
            list_of_layers.append(layer())

        if (character == '0'):
            list_of_layers[-1].zeroes += 1
        elif (character == '1'):
            list_of_layers[-1].ones += 1
        elif (character == '2'):
            list_of_layers[-1].twos += 1

layer_with_fewest_zeroes = list_of_layers[0]
fewest_zeroes = layer_with_fewest_zeroes.zeroes

for layer in list_of_layers:
    if (layer.zeroes < fewest_zeroes):
        fewest_zeroes = layer.zeroes
        layer_with_fewest_zeroes = layer

print(layer_with_fewest_zeroes.ones * layer_with_fewest_zeroes.twos)