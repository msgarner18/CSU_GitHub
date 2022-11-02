'''
I realized that Atm is still an undecidable language if Atm = { <M, w> | L(M) = {1} }
I tried Atm = { <M, w> | w == "1" }. D(D) returned true
'''
#Atm = { <M, w> | M halts on input w}

#H decides Atm
def H(M, w):
    '''
    run M(w) for 5 seconds. If still running after 5 seconds, conclude loop and return True
    otherwise, False
    '''


def D(M):
    return not H(M, M)

print(D(D))