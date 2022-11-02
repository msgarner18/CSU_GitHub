#m is a tm and L(M) is null
def M(w):
    return False

#Etm = L(M)
#R decides Etm
#This means that R returns True if L(M) is null and False if it is not
def R(M):
    return True

def S(M, w):
    #language that is always returns false if M accepts w and always returns True if M doesn't accept w
    def M1(x):
        if x != w:
            return False
        if x == w:
            return M(w)

    return not R(M1)

'''
iff M accepts w, L(M1) = empty set
if M(w):
   return False
return True 
does test accept 2?
M1:
    if x != 2:
        return False
    if x == 2:
        return test(2)
return not R(M1)
if M1 != empty set, test accepts 2.
'''

def test(w):
    if w%2 == 0:
        return True
    return False

def loop(w):
    while(True):
        continue
    return True

# print(S(loop, 2))

'''
if M1 == empty set, M accepts w
def S(M, w):
    return M(w)
    def M1(x):
        if x != w:
            return False
        if x == w:
            return not M(w)

'''


'''
Test 2
'''
#Decider for { M | M is a TM and L(M) = emptySet }
def R(M):
    for i in range(0, 10, 1):
        if M(i):
            return False
    return True

#Decider for Atm
def S(M, w):
    #L(M1) = Null iff M accepts w
    def M1(x):
        if M(w):
            return False
        return True
    return R(M1)

#M such that L(M) = {1}
def M(w):
    if w == 1:
        return True
print(S(M, 2))
