import numpy as np
import matplotlib.pyplot as plt 
from PIL import Image 

class flipImageHorizontlyAndVertically:
    def flip_images_horizontly_and_vertically(filepath):
        # from PIL import Image
        original_img = Image.open(filepath)
        horz_img = original_img.transpose(method=Image.FLIP_LEFT_RIGHT)
        vert_img = original_img.transpose(method=Image.FLIP_TOP_BOTTOM)
        plt.imshow(horz_img)
        plt.imshow(vert_img)
        horz_img.save("horizontal_image.png")
        vert_img.save("Vertical_image.png")
        original_img.close()
        horz_img.close()
        vert_img.close()