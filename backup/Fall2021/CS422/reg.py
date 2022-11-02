#True if L(M) is regular, false if not
def Reg(M):
    for i in range(0, 10, 1):
        if M(i) != True:
            return False
    return True

def S(M, w):
    def M1(x):
        if M(w):
            return True
        return "context-free"
    return Reg(M1)

def M(w):
    if w == 1:
        return True
    return False

print(S(M, 2))