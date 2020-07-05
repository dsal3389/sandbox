import sys, os
import numpy as np
from PIL import Image


SIZE_WIDTH = 120
SIZE_HEIGHT = 120


def _check_file_exists(filename):
    return os.path.exists(filename)


class Convertor:
    def __init__(self, filename):
        self.filename = filename

        if not _check_file_exists(self.filename):
            raise FileNotFoundError('could not found image named %s' %self.filename)
        self.image = Image.open(self.filename)
        self._to_shades() # terminal is black and white so converting the image to black and white

    def asarry(self):
        return np.asarray(self.image)
    
    def resize(self, height, width):
        self.image.thumbnail((height, width))

    def as_text(self):
        data = self.asarry()

        for pline in data:
            for pixel in pline:
                print(self._get_char_for(pixel), end="")
            print()

    def _to_shades(self):
        self.image = self.image.convert('L')

    def _get_char_for(self, shade): # return char based on pixel shade
        if shade >= 230:
            return "#"
        
        if shade >= 200:
            return "&"
        
        if shade >= 170:
            return "%"
        
        if shade >= 140:
            return "H"
        
        if shade >= 100:
            return "J"
        
        if shade >= 60:
            return "*"
        
        if shade >= 30:
            return "^"
        return '.'


def main(image_name):
    converter = Convertor(image_name)
    converter.resize(SIZE_HEIGHT, SIZE_WIDTH)
    converter.as_text()

if __name__ == "__main__":
    if len(sys.argv) == 1:
        raise IndexError("Missing argument, image name")
    filename = sys.argv[1]
    main(filename)
