import numpy as np
import matplotlib.pyplot as plt
from sklearn.naive_bayes import MultinomialNB

# 2
def values_to_bins(matr,bins):
    new_matr = np.digitize(matr, bins)
    return new_matr - 1

#6
def confusion_matrix(y_true,y_pred):
    matr = np.zeros((10,10))
    for i in range(0,len(y_true)):
        matr[y_true[i],y_pred[i]]+=1
    return matr

# naive bayes: P(y|x) = P(x|y) * P(y) / P(x)
# x - de obicei un vector
# de ce naive? pp ca elem din x sunt indep intre ele
# pe P(y) il putem consid uniform
# P(x) se normalizeaza si dispare
# ramane P(xi|y) care depinde de implem (multinomial, gaussian, categorical etc)
# categorical - rap nr de cazuri c=x / nr cazuri totale c

train_images = np.loadtxt('train_images.txt') # incarcam imaginile
train_labels = np.loadtxt('train_labels.txt', 'int') # incarcam etichetele avand tipul de date int
image = train_images[0, :] # prima imagine
image = np.reshape(image, (28, 28))
plt.imshow(image.astype(np.uint8), cmap='gray')
plt.show()

# bins = np.linspace(start=0, stop=255, num=num_bins) # returneaza intervalele
# x_to_bins = np.digitize(x, bins) # returneaza pentru fiecare element intervalul corespunzator
# Atentie! In cazul nostru indexarea elementelor va incepe de la 1, intrucat nu avem valori < 0

# template antrenare
# naive_bayes_model = MultinomialNB() / GaussianNB() etc
# naive_bayes_model.fit(training_data, training_labels)
# naive_bayes_model.predict(testing_data)
# naive_bayes_model.score(testing_data, testing_labels)
# accuracy = correct predictions / total predictions (score calc direct chestia asta)
# data = x, labels = y

# 2
'''
num_bins = 5
bins = np.linspace(0, 255+1, num_bins)
discrete_train = values_to_bins(train_images,bins)
# print(train_images[0,:])
# print(discrete_train[0,:])

test_images = np.loadtxt('test_images.txt')
test_labels = np.loadtxt('test_labels.txt', 'int')
discrete_test = values_to_bins(test_images,bins)
# print(test_images[0,:])
# print(discrete_test[0,:])
'''

# 3
'''
naive_bayes_model = MultinomialNB() # / GaussianNB() etc
naive_bayes_model.fit(discrete_train, train_labels)
naive_bayes_model.predict(discrete_test)
(print(naive_bayes_model.score(discrete_test, test_labels)))
'''

# 4
'''
for i in {3,5,7,9,11}:
    num_bins = i
    bins = np.linspace(0, 255 + 1, num_bins)
    discrete_train = values_to_bins(train_images, bins)
    discrete_test = values_to_bins(test_images, bins)

    naive_bayes_model = MultinomialNB() # / GaussianNB() etc
    naive_bayes_model.fit(discrete_train, train_labels)
    naive_bayes_model.predict(discrete_test)
    (print(naive_bayes_model.score(discrete_test, test_labels)))
    # 7 e cel mai bun
'''

# 5
num_bins = 7
bins = np.linspace(0, 255 + 1, num_bins)
test_images = np.loadtxt('test_images.txt')
test_labels = np.loadtxt('test_labels.txt', 'int')
discrete_train = values_to_bins(train_images, bins)
discrete_test = values_to_bins(test_images, bins)

naive_bayes_model = MultinomialNB() # / GaussianNB() etc
naive_bayes_model.fit(discrete_train, train_labels)
predictions = naive_bayes_model.predict(discrete_test)

for i in range(0,len(predictions)):
    if predictions[i] != test_labels[i]:
        image = test_images[i, :]
        image = np.reshape(image, (28, 28))
        #plt.xlabel(f"Classified as: {predictions[i]} and original label was: {test_labels[i]}")
        #plt.imshow(image.astype(np.uint8), cmap='gray')
        #plt.show()

# 6
print(confusion_matrix(test_labels, predictions))









