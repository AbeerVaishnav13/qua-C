# Two qubit grover search to find the number '2' or '10' in binary representation

func grover_search_10 {
	[H, H]
	[-, S]
	[-, H]
	[Co, Cx]
	[-, H]
	[-, S]
	[H, H]
	[X, X]
	[-, H]
	[Co, Cx]
	[-, H]
	[X, X]
	[H, H]
}

quReg a = init [2]
a.name = "quReg1: "
a.prec = 6

a.Pa()
a.grover_search_10()
a.Pa()
