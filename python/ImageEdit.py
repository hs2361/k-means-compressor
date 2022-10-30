import numpy as np
import matplotlib.pyplot as plt 
from PIL import Image 

class ImageEdit:
    def __init__(self):
      pass

    def FlipImageHorizontly(self,filepath):
        original_img = Image.open(filepath)
        horz_img = original_img.transpose(method=Image.FLIP_LEFT_RIGHT)
        plt.imshow(horz_img)
        horz_img.save("HorizontalImage.png")
        original_img.close()
        horz_img.close()


    def FlipImageVertically(self,filepath):
        original_img = Image.open(filepath)
        vert_img = original_img.transpose(method=Image.FLIP_TOP_BOTTOM)
        plt.imshow(vert_img)
        vert_img.save("VerticalImage.png")
        original_img.close()
        vert_img.close()

    def ConvertToGrayScale(self,filepath):
        orignal_img = Image.open(filepath).convert('RGB')
        orig_img = np.array(orignal_img)
        orig_img = np.dot(orig_img, [0.3, 0.59, 0.11])
        orig_img = np.round(orig_img)
        plt.imshow(orig_img)
        PIL_image = Image.fromarray(np.uint8(orig_img)).convert('RGB')
        PIL_image.save('GrayscaleImage.png')
        PIL_image.close()

# testing purpose
# obj = ImageEdit()
# obj.FlipImageHorizontly("salvador_dali.jpeg")
# obj.FlipImageVertically("salvador_dali.jpeg")
# obj.ConvertToGrayScale("salvador_dali.jpeg")
