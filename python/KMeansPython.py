from skimage import io
import numpy as np
import random
import numpy.matlib
import imageio


class KMeans_compressor:
    def __init__(self):
        pass

    # * loading image on colab
    # * Image reading
    # * Image preprocessing
    # * selecting random clusters
    def ImagePreprocessing(self, filepath):
        Img = io.imread(filepath)
        rows = Img.shape[0]
        cols = Img.shape[1]
        Img = Img / 255
        Img = Img.reshape(Img.shape[0] * Img.shape[1], 3)
        return Img, rows, cols

    # Generate random centroids
    def RandomCentroid(self, X, n_clusters):
        centroids = random.sample(list(X), n_clusters)
        return centroids

    # Assigning each data-points to the clusters corresponding to minimum distance with them.
    def ClusterAssignments(self, X, centroids):
        k = np.size(centroids, 0)
        dist_arr = np.empty((np.size(X, 0), 1))
        clusters = np.zeros((np.size(X, 0), 1))
        for i in range(k):
            centroid_array = np.ones((np.size(X, 0), 1)) * centroids[i]
            a = np.sum(np.square(X - centroid_array), 1)
            a = np.asarray(a)
            a.resize((np.size(X, 0), 1))
            dist_arr = np.append(dist_arr, a, axis=1)
        dist_arr = np.delete(dist_arr, 0, axis=1)
        clusters = np.argmin(dist_arr, axis=1)
        return clusters

    # updating centroids
    def UpdateCentroids(self, X, k, clusters):
        n = np.size(X, 1)
        centroid = np.zeros((k, n))
        for i in range(k):
            c = clusters == i
            c = c.astype(int)
            c.resize((np.size(X, 0), 1))
            c = np.matlib.repmat(c, 1, n)
            a = np.multiply(X, c)
            centroid[i] = (1 / sum(c)) * np.sum(a, axis=0)
        return centroid

    def KMeans(self, X, initial_centroids, max_iter):
        k = np.size(initial_centroids, 0)
        n = X.shape[1]
        clusters = np.zeros((np.size(X, 0), 1))
        centroids = initial_centroids
        for i in range(1, max_iter):
            clusters = self.ClusterAssignments(X, centroids)
            centroids = self.UpdateCentroids(X, k, clusters)
        return clusters, centroids

    def main(self, filepath, n_clusters, max_iter):
        Img, rows, cols = self.ImagePreprocessing(filepath)
        init_cent = self.RandomCentroid(Img, n_clusters)
        _clusters, _centroids = self.KMeans(Img, init_cent, max_iter)
        _clusters = self.ClusterAssignments(Img, _centroids)
        X_predicted = _centroids[_clusters]
        X_predicted = np.reshape(X_predicted, (rows, cols, 3))
        imageio.imwrite("compressed.jpeg", X_predicted)


# for testing purpose
# obj = KMeans_compressor()
# obj.main('salvador_dali.jpeg',16,50)
