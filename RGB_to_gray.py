import numpy as np
import matplotlib.pyplot as plt 
from PIL import Image 
class RGB_to_gray:
    def convert_to_gray_scale(filepath):
        orignal_img = Image.open(filepath)
        orig_img = np.array(orignal_img)
        orig_img = np.sum(orig_img*0.33,axis = 2)
        orig_img = np.round(orig_img)
        plt.imshow(orig_img)
        PIL_image = Image.fromarray(np.uint8(orig_img)).convert('RGB')
        PIL_image.save('Grayscale_image.png')
        PIL_image.close()
        
