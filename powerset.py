#!/usr/bin/python


def generate_powersets(ls):
	if len(ls) == 0:
		return [[]]
	el = ls.pop()
	power = generate_powersets(ls)
	ret = []
	for s in power:
		ret.append(s + [el])
		ret.append(s)
	return ret

s = [1, 2, 3, 4]
print generate_powersets(s)
