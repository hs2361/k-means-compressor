import numpy as np
from imageio import imread, imwrite
from scipy.ndimage.filters import convolve


class seam_carving:
    def __init__(self, file_path, saved_file_name, scale_c, scale_r):
        self.file_path = file_path
        self.saved_file_name = saved_file_name
        self.scale_c = scale_c
        self.scale_r = scale_r

    # Calculating the gradients of image w.r.t X and Y using sobel edge-detector filters which will tells us about the important and unimportant pixels.
    def CalculateEnergyValues(self, img):
        filter_du = np.array(
            [
                [1.0, 2.0, 1.0],
                [0.0, 0.0, 0.0],
                [-1.0, -2.0, -1.0],
            ]
        )
        # For the 3 channels of the image, stacking the same filter one after the another for each RGB channels.
        filter_du = np.stack([filter_du] * 3, axis=2)

        filter_dv = np.array(
            [
                [1.0, 0.0, -1.0],
                [2.0, 0.0, -2.0],
                [1.0, 0.0, -1.0],
            ]
        )
        filter_dv = np.stack([filter_dv] * 3, axis=2)

        img = img.astype("float32")
        convolved = np.absolute(convolve(img, filter_du)) + np.absolute(
            convolve(img, filter_dv)
        )
        energy_map = convolved.sum(axis=2)
        return energy_map

    # Delete all the pixels along the colums of the particular seam.
    def DeleteColumns(self, img, scale):
        r, c, _ = img.shape
        new_c = int(scale * c)
        for i in range(c - new_c):
            img = self.CarveColumn(img)
        return img

    # Delete all the pixels along the rows of the particular seam.
    def DeleteRows(self, img):
        img = self.DeleteColumns(img, self.scale_c)
        img = np.rot90(img, 1, (0, 1))
        img = self.DeleteColumns(img, self.scale_r)
        img = np.rot90(img, 3, (0, 1))
        return img

    def CarveColumn(self, img):
        r, c, _ = img.shape

        M, backtrack = self.CalculateMinimumSeamLine(img)
        mask = np.ones((r, c), dtype=np.bool_)

        j = np.argmin(M[-1])
        for i in reversed(range(r)):
            mask[i, j] = False
            j = backtrack[i, j]
        mask = np.stack([mask] * 3, axis=2)
        img = img[mask].reshape((r, c - 1, 3))
        return img

    # calculating seam line having minimum importance
    def CalculateMinimumSeamLine(self, img):
        r, c, _ = img.shape
        energy_map = self.CalculateEnergyValues(img)

        M = energy_map.copy()
        backtrack = np.zeros_like(M, dtype=np.int64)

        for i in range(1, r):
            for j in range(0, c):
                if j == 0:
                    idx = np.argmin(M[i - 1, j : j + 2])
                    backtrack[i, j] = idx + j
                    min_energy = M[i - 1, idx + j]
                else:
                    idx = np.argmin(M[i - 1, j - 1 : j + 2])
                    backtrack[i, j] = idx + j - 1
                    min_energy = M[i - 1, idx + j - 1]
                M[i, j] += min_energy
        return M, backtrack

    def main(self):
        img = imread(self.file_path)
        out = self.DeleteRows(img)
        imwrite(self.saved_file_name, out)


# testing
# if __name__ == '__main__':
#     obj = seam_carving("salvador_dali.jpeg","seam_img.png",0.5,0.5)
#     obj.main()
