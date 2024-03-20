class Cecho:
    def __init__(self, str):
        self.str = str

    def echo(self):
        if len(self.str) == 0:
            print("custom echo ===> Error: string is NULL")
            return False
        else:
            print("custom echo ===> " + self.str)
            return True
