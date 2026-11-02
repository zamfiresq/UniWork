import pickle
from tqdm import tqdm
import numpy as np
import cv2
from sklearn.svm import SVC
from sklearn.neighbors import KNeighborsClassifier
from sklearn.preprocessing import StandardScaler

'''
Creati o functie care primeste ca parametrii o imagine I si dimensiunea vecinatatii unui pixel 
d . Pentru fiecare pixel din imagine comparati intensitatea lui cu intensitatiile pixelilor 
din vecinatatea dxd a acestuia. 

Din operatia anterioara va rezulta pentru fiecare pixel o matrice cu valori binare. 
Liniarizati fiecare matrice sub forma de vector. 

Pentru imaginea data creati o histograma a vectorilor unici obtinuti in urma operatiei anterioare. 
Folositi aceste histograme pentru a antrena un model de machine learning. 
Alegeti voi valorile hyperparametrilor. 
'''

def binary2decimal(binary):
    return sum(val * (2 ** idx) for idx, val in enumerate(reversed(binary)))


def fun(image, dim=3):
    rows, cols = image.shape
    image = np.pad(image, pad_width=(((dim - 1) // 2, (dim - 1) // 2), ((dim - 1) // 2, (dim - 1) // 2)),
                   constant_values=-1)
    res = []
    # parcurg imaginea
    for i in range((dim - 1) // 2, rows):
        for j in range((dim - 1) // 2, cols):
            # vecinatatea
            out = np.zeros((dim * dim) - 1)

            patch = image[i - ((dim - 1) // 2): i + ((dim - 1) // 2) + 1,
                j - ((dim - 1) // 2): j + ((dim - 1) // 2) + 1]
            val = image[i][j]  # pixelul curent
            comparison = (patch > val) * 1  # bool -> int (0/1)
            result = comparison.reshape(-1)  # transf in vector

            # se face pe jumatati pt a sari elem curent
            out[:len(out) // 2] = result[:len(out) // 2]
            out[len(out) // 2:] = result[len(out) // 2 + 1:]
            res.append(out)

    histogram = np.zeros((2 ** (dim * dim - 1)))
    for result in res:
        # se transf in val zecimala
        position = binary2decimal(result)
        # vector de frecv
        histogram[int(position)] += 1
    return histogram


def process_data(images):
    results = []
    for image in tqdm(images):
        hist = fun(image)
        results.append(hist)
    return np.array(results)


def load():
    with open('data.pkl', 'rb') as f:
        dict1 = pickle.load(f)
    return dict1["training_images"], dict1["training_labels"], dict1["test_images"], dict1["test_labels"]


train_images, train_labels, test_images, test_labels = load()

train_images = train_images.reshape(-1, 28, 28)
test_images = test_images.reshape(-1, 28, 28)

train_labels = train_labels
test_labels = test_labels


train_hist = process_data(train_images)
test_hist = process_data(test_images)

clf = SVC()
scaler = StandardScaler()
scaler.fit(train_hist)
train_hist_scaled = scaler.transform(train_hist)
test_hist_scaled = scaler.transform(test_hist)
#clf.fit(train_hist_scaled, train_labels)
#clf.score(test_hist_scaled, test_labels)


# 2
'''
Creati o functie care calculeaza magnitudinea gradientului unei imagini date, G = sqrt(Gx^2 + Gy^2)
unde Gx este gradientul imaginii pe directia x si Gy este gradientul imaginii pe
directia y. Definitia gradientului pentru o functie f(x) este:
lim (f(x+e) - f(x)) / e
e->0

Impartiti imaginea in regiuni de dimensiune 3 x 3 care nu se suprapun si folositi-va de
rezultatul G pentru a gasi primele k regiuni din imaginea originala cu magnitudinea medie
cea mai mare. Pastrati doar aceste k regiuni in antrenarea unui model de machine learning.

Alegeti voi valorile hyperparametrilor.
'''


def fun2(image):
    # filtru sobel - Gx = [ [1,0,-1], [2,0,-2], [1,0,-1] ] * A (A= imaginea mea)
    # Gy = [ [1,2,1], [0,0,0], [-1,-2,-1] ] * A
    # 1,0 e directia -> pe x; 0,1 -> pe y
    sobelx = cv2.Sobel(image, cv2.CV_64F, 1, 0, ksize=3)
    sobely = cv2.Sobel(image, cv2.CV_64F, 0, 1, ksize=3)
    # formula lui G
    grad_mag = np.sqrt(np.square(sobelx) + np.square(sobely))
    return grad_mag


def process_images(images):
    results = []
    for image in tqdm(images):
        # tqdm = loading bar pt for-uri
        results.append(fun2(image))  # calculam magnitudinea gradientului imaginii
    return np.array(results)


train_gradient = process_images(train_images)
test_gradient = process_images(test_images)


# acum primele k regiuni
def get_top_k(magnitude, image, k=30, d=4):
    patches_magni = magnitude.reshape(-1, d, d)
    original_img = image.reshape(-1, d, d)

    # media_axa_1 + media_axa_2 / (linii * col * dim3)
    patches_magni = np.mean(patches_magni, axis=(1, 2))
    # ca sa le putem extrage pe cele mai bune
    sortedindices = np.argsort(patches_magni)
    out = []

    for i in range(original_img.shape[0]):
        # daca nu e in primele k il sar
        if i not in sortedindices[-k:]:
            continue
        out.append(original_img[i])
    return np.array(out).reshape(-1)  # liniarizare


def transform_imgs(images, gradient_magnis):
    result = []
    for i, image in enumerate(tqdm(images)):
        result.append(get_top_k(gradient_magnis[i], image))
    return np.array(result)

'''
ex2_traind = transform_imgs(train_images, train_gradient)
ex2_testd = transform_imgs(test_images, test_gradient)
clf = SVC(C=10)
clf.fit(ex2_traind,train_labels)
clf.fit(ex2_testd,test_labels)
print(clf.score(ex2_testd,test_labels))
'''

# ex3
'''
Similar cu exercitiul anterior calculati magnitudinea gradientului unei imagini, dar
determinati si directia acestuia theta = arctan (Gy/Gx). 
Folosindu-va de aceasta directie comparati fiecare pixel din magnitudinea gradientului cu vecinii corespunzatori. 
Creati o noua matrice care sa contina valorile magnitudinilor pentru pixelii a caror magnitudine este
mai mare decat ale ambilor vecini sau 0 in caz contrar. Folositi imaginile rezultate intr-un
algoritm de machine learning.
'''

def find_direction(image):
    sobelx = cv2.Sobel(image, cv2.CV_64F, 1, 0, ksize=3)
    sobely = cv2.Sobel(image, cv2.CV_64F, 0, 1, ksize=3)
    direction = np.arctan2(sobely, sobelx)
    return direction

def process_img(images):
    results = []
    for image in tqdm(images):
        # tqdm = loading bar pt for-uri
        results.append(find_direction(image))  # calculam magnitudinea gradientului imaginii
    return np.array(results)


# trainw_direction = process_img(train_images)
# testw_direction = process_img(test_images)


def non_max_suppr_gradi(img, direction):
    linii, col = img.shape
    output = np.zeros((linii, col), dtype=np.int32)
    angle = direction * 180 / np.pi
    angle[angle < 0] += 180

    for i in range(1, linii - 1):
        for j in range(1, col - 1):
            neighbour1 = 255
            neighbour2 = 255
            if (0 <= angle[i, j] < 22.5) or (157.5 <= angle[i, j] <= 180):
                neighbour1 = img[i, j + 1]  # orizontal
                neighbour2 = img[i, j - 1]

            elif 22.5 <= angle[i, j] < 67.5:
                neighbour1 = img[i + 1, j - 1]  # Diag sec
                neighbour2 = img[i - 1, j + 1]

            elif 67.5 <= angle[i, j] < 112.5:
                neighbour1 = img[i + 1, j]  # vertical
                neighbour2 = img[i - 1, j]

            elif 112.5 <= angle[i, j] < 157.5:
                neighbour1 = img[i - 1, j - 1]  # Diag princ
                neighbour2 = img[i + 1, j + 1]

            if (img[i, j] >= neighbour1) and (img[i, j] >= neighbour2):
                output[i, j] = img[i, j]
            else:
                output[i, j] = 0
    return output

def process_images3(magnis, directions):
    res = []
    for i, mag in enumerate(magnis):
        res.append((non_max_suppr_gradi(mag,directions[i])))
    return np.array(res)
'''
new_train = process_images3(train_gradient, trainw_direction)
new_test = process_images3(test_gradient, testw_direction)
clf = SVC(C=10)
clf.fit(new_train.reshape(-1,784),train_labels)
print(clf.score(new_test.reshape(-1,784), test_labels))
'''

# ex 4
'''
Impartiti fiecare imagine in regiuni distincte si binarizati-le conform compararii de la exercitiul 1. 
Concatenati vectorii binari rezultati si folositi-va de distanta Hamming implementati metoda celor mai 
apropiati vecini pentru un k ales de voi. 
'''
def binarize(image, d=4):
    patches = image.reshape(-1, d, d)
    output = []
    for patch in patches:
        if d%2 == 0:
            out_rep = np.zeros((d*d))
            value = np.mean(patch[d//2-1 : d//2+1, d//2-1 : d//2+1])
        else:
            out_rep = np.zeros((d*d)-1)
            value = patch[d//2, d//2]
        comparison = (patch >= value) * 1
        result = comparison.reshape(-1)
        if d%2 == 0:
            out_rep = result
        else:
            out_rep[:len(out_rep)//2] = result[:len(out_rep)//2]
            out_rep[len(out_rep)//2:] = result[len(out_rep)//2 + 1:]
        output.append(out_rep)
    return np.concatenate(output)

def process_images4(images):
    results = []
    for image in tqdm(images):
        results.append(binarize(image))
    return np.array(results)

train_data = process_data(train_images)
test_data = process_data(test_images)

neigh = KNeighborsClassifier(n_neighbors=7)
neigh.fit(train_data, train_labels)
print(neigh.score(test_data, test_labels))

# ex 5
'''
Folosind histogramele de la exercitiul 1, antrenati un model SVM cu functia kernel intersectie.
'''
def inters_kernel(hist1, hist2):
    hist1 = np.expand_dims(hist1, axis=0)
    hist2 = np.expand_dims(hist2, axis=0)
    concatenation = np.concatenate((hist1, hist2), axis=0)
    minimum = np.min(concatenation, axis=0)
    return np.sum(minimum)

def compute_kernel_matr(histo1, histo2, train=True):
    kernel_matr = np.zeros((len(histo1), len(histo2)))
    if train:
        for i in tqdm(range(len(histo1))):
            for j in range(i, len(histo2)):
                kernel_matr[i][j] = inters_kernel(histo1[i], histo2[j])
                kernel_matr[j][i] = kernel_matr[i][j]
    else:
        for i in tqdm(range(len(histo1))):
            for j in range(len(histo2)):
                kernel_matr[i][j] = inters_kernel(histo1[i], histo2[j])
    return kernel_matr

train_matr = compute_kernel_matr(train_hist_scaled, train_hist_scaled)
test_matr = compute_kernel_matr(train_hist_scaled, test_hist_scaled, train=False)
clf2 = SVC(kernel='precomputed')

clf2.fit(train_matr, train_labels)
print(clf2.score(test_matr.T, test_labels))