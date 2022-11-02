#pretends it is infinite when compared to other values
class Infinite:
    def __gt__(self, other):
        return True
    
    def __lt__(self, other):
        return False