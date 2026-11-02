import numpy as np
from sklearn import svm, preprocessing
import copy

# V1 2
def normalize_data1(train_data, test_data, type=None):
    if type == "standard":
        mean = np.mean(train_data, axis=0)  # mediile atrib
        std = np.std(train_data, axis=0)  # deviatiile standard
        # mean, std vectori de dim egala cu no_features din setul de date
        # aici features sunt frecv cuvintelor
        train_data -= mean
        train_data /= std
        test_data -= mean
        test_data /= std
    elif type == "l1":
        # se aduna 1e-6 daca norma e 0
        # aici norma e 0 daca nu sunt cuvinte in text sau la datele de test cuv nu se gasesc in dict
        # np.expand_dims pt broadcast la impertire
        train_data = train_data / (np.expand_dims((np.linalg.norm(train_data, ord=1, axis=1)),
                                                  axis=1) + 1e-6)
        test_data = train_data / (np.expand_dims((np.linalg.norm(test_data, ord=1, axis=1)),
                                                 axis=1) + 1e-6)
    elif type == "l2":
        norm_train = np.expand_dims((np.linalg.norm(train_data, ord=2, axis=1)), axis=1)
        train_data /= norm_train + 1e-6
        test_data /= (np.expand_dims((np.linalg.norm(test_data, ord=2, axis=1)), axis=1) + 1e-6)
    return train_data, test_data

# V2 2 - cu librarii
def normalize_data(train_data, test_data, type=None):
    if type == "standard":
        scaler = preprocessing.StandardScaler()
        scaler.fit(train_data)
        scaled_train = scaler.transform(train_data)
        scaled_test = scaler.transform(test_data)
        return scaled_train,scaled_test
    if type == "l1":
        normalizer = preprocessing.Normalizer(norm="l1")
        train_data = normalizer.transform(train_data)
        test_data = normalizer.transform(test_data)
        return train_data,test_data
    if type == "l2":
        normalizer = preprocessing.Normalizer(norm="l2")
        train_data = normalizer.transform(train_data)
        test_data = normalizer.transform(test_data)
        return train_data, test_data


# 3
class BagOfWords:
    def __init__(self):
        self.vocab = {}
        self.words = []

    def build_vocabulary(self,data):
        id_word = 0
        for sentence in data:
            for word in sentence:
                if word not in self.vocab:
                    self.vocab[word] = id_word
                    id_word += 1
                    self.words.append(word)

    # 4
    def get_features(self,data):
        # transf enunturile din data in arrays de dim vocab ca contin frecv cuvintelor
        # fiecare rand din feature_matr are vect de frecv pt un enunt
        feature_matr = np.zeros((data.shape[0],len(self.vocab)))
        for i,example in enumerate(data):
            no_word = True
            for word in example:
                if word in self.vocab:
                    feature_matr[i,self.vocab[word]] += 1
                    no_word = False
            if no_word:
                print(example)
        return feature_matr


# 5
train_data = np.load("training_sentences.npy",allow_pickle=True)
test_data = np.load("test_sentences.npy",allow_pickle=True)
train_labels = np.load("training_labels.npy",allow_pickle=True)
test_labels = np.load("test_labels.npy",allow_pickle=True)

bow = BagOfWords()
bow.build_vocabulary(train_data)
print(len(bow.vocab))

train_data = bow.get_features(train_data)
test_data = bow.get_features(test_data)

train_data, test_data = normalize_data(train_data,test_data,type='l2')

# 6
from sklearn.metrics import accuracy_score, f1_score

model = svm.SVC(C=1,kernel="linear")
model.fit(train_data,train_labels)
pred_labels = model.predict(test_data)
print("Accuracy: ", accuracy_score(test_labels,pred_labels),
      "F1 score: ", f1_score(test_labels, pred_labels))

# afisarea cuvintelor cele mai negative si cele mai pozitive
# functioneaza pt ca folosim kernel linear
index_sort = np.argsort(model.coef_[0])
bw = np.array(bow.words)
print("Most positive words: ", bw[index_sort[:10]])
print("Most negative words: ", bw[index_sort[-10:]])
