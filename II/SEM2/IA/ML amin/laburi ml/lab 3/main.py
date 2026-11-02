import numpy as np
import matplotlib.pyplot as plt

# 1
# x - ex de test, y - ex de antrenare
class Knnclassifier:
    def __init__(self, train_images, train_labels):
        self.train_images = train_images
        self.train_labels = train_labels

    def classify_image(self, test_image, num_neighbors=3, metric='l2'):
        if(metric=='l1'):
            L = np.sum(abs(test_image - self.train_images),1)
            indices = np.argsort(L)
            labels = self.train_labels[indices[:num_neighbors]]
            freq = np.bincount(labels)
            # distances = np.sum(abs(self.train_images-test_image),axis=1)
            return np.argmax(freq)
        elif metric=='l2':
            #sqrt( sum( (Xi - Yi)^2 ) )
            L = np.sqrt(np.sum((test_image - self.train_images) ** 2,1))
            indices = np.argsort(L)
            labels = self.train_labels[indices[:num_neighbors]]
            freq = np.bincount(labels)
            # distances = np.sqrt(np.sum((self.train_images-test_image)**2, axis=1))
            return np.argmax(freq)
        # nu dau return, sortez distances
        '''
        sort_ind = np.argsort(distances)
        sort_ind = sort_ind[:num_neighbours]
        nearest_lb = sekf.train_labels[sort_ind]
        histc = np.bincount(nearest_lb)
        return np.argmax(histc)
        '''
    # 3
    def classify_images(self, test_images, num_neighbours=3, metric='l2'):
        num_test_img = test_images.shape[0]
        pred_labels = np.zeros(num_test_img)
        for i in range(num_test_img):
            pred_labels[i] = self.classify_image(test_images[i,:],num_neighbors=num_neighbours,metric=metric)
        return pred_labels

    def acc_score(self,y_true,y_pred):
        return (y_true == y_pred).mean()

def calc_accurr(obj,test_imgs, test_labels):
    correct = np.shape(test_imgs)[0]
    for i in range(0,np.shape(test_imgs)[0]):
        if KNNmodel.classify_image(test_images[i,:],3,'L2') != test_labels[i]:
            correct -= 1
    acc = correct / np.shape(test_imgs)[0]
    return acc


train_images = np.loadtxt('train_images.txt')  # incarcam imaginile
train_labels = np.loadtxt('train_labels.txt', 'int')

test_images = np.loadtxt('test_images.txt')
test_labels = np.loadtxt('test_labels.txt','int')

KNNmodel = Knnclassifier(train_images,train_labels)
'''
pred = KNNmodel.classify_images(test_images)
acc = KNNmodel.acc_score(test_labels,pred)

np.savetxt("predictii_3nn_l2_mnist.txt",pred)
print(acc)
'''
# print(calc_accurr(KNNmodel,test_images,test_labels))

# d
# acuratetea pt l2 si nn = [1,3,5,7,9]

# grafic cu acuratetile
accuracies = np.zeros((5,))
nn = [1,3,5,7,9]
for i in range(5):
    pred = KNNmodel.classify_images(test_images,num_neighbours=2*i+1,metric='l2')
    acc = KNNmodel.acc_score(test_labels,pred)
    accuracies[i] = acc

plt.plot(nn, accuracies)
plt.xlabel("no of neighbours")
plt.ylabel("accuracy")
plt.show()

np.savetxt("acuratete_l2.txt",accuracies)

# plot si pt l1, si cele doua grafice sa fie in aceeasi figura
accl2 = np.loadtxt("acuratete_l2.txt")

accl1 = np.zeros((5,))
nn = [1,3,5,7,9]
for i in range(5):
    pred = KNNmodel.classify_images(test_images,num_neighbours=2*i+1,metric='l1')
    acc = KNNmodel.acc_score(test_labels,pred)
    accl1[i] = acc

plt.plot(nn,accl2, label="l2 accuracy")
plt.plot(nn,accl1,label="l1 accuracy")
plt.xlabel("no of neighbours")
plt.ylabel("accuracy")
plt.show()