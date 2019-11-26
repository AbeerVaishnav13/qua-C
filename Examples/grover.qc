gate Uw[6] {
    [-, -, -, X, -, -]
    [X, @, @, @, @, @]
    [-, -, -, X, -, -]
}

gate Us[6] {
    [-, H, H, H, H, H]
    [-, X, X, X, X, X]
    [X, @, @, @, @, @]
    [-, X, X, X, X, X]
    [-, H, H, H, H, H]
}

func grover {
    [X, -, -, -, -, -]
    [H, H, H, H, H, H]
    [Uw]
    [Us]
    [Uw]
    [Us]
    [Uw]
    [Us]
    [Uw]
    [Us]
    Pa()
}

quReg qr = new quReg[6] => 'qr1'
qr.setPrecision(6)

qr.Pnz()
qr.grover()
qr.Pnz()


######################################
# Pauli-X: X
# Pauli-Y: Y
# Pauli-Z: Z
# Phase: S
# Rotation: R
# Hadamard: H
# Swap: x
# QFT: ~
# Control: @
# Inverse Control: o
# Power: <gate> ^ <num>    (optional)
# X-axis control: +
# Y-axis control: *
# Identity gate: -
