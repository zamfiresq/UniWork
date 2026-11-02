import numpy as np

# a
image0 = np.load("car_0.npy")
image1 = np.load("car_1.npy")
image2 = np.load("car_2.npy")
image3 = np.load("car_3.npy")
image4 = np.load("car_4.npy")
image5 = np.load("car_5.npy")
image6 = np.load("car_6.npy")
image7 = np.load("car_7.npy")
image8 = np.load("car_8.npy")

all_imgs = np.array([image0,image1,image2,image3,image4,image5,image6,image7,image8])
# b
suma = np.sum(all_imgs)
print(suma)

# c, d
maxsum=-1
for i in range(9):
    sumai = np.sum(all_imgs[:, :, i])
    print(sumai)
    if sumai > maxsum:
        maxsum = i
print(maxsum)

# e
from skimage import io
mean_image = np.mean(all_imgs, axis = 0)
io.imshow(mean_image.astype(np.uint8))
io.show()

# f
devi =  np.std(all_imgs)
print(devi)

# g
for img in all_imgs:
    normal_img = np.divide(np.subtract(img, mean_image) , devi)
    io.imshow(normal_img.astype(np.uint8))
    io.show()

# h
for img in all_imgs:
    cropped_img = img[200:300,280:400]
    io.imshow(cropped_img.astype(np.uint8))
    io.show()