import numpy as np
import matplotlib.pyplot as plt
from sklearn.utils import shuffle
from sklearn import preprocessing
from sklearn.model_selection import KFold
from sklearn.linear_model import LinearRegression, Ridge, Lasso
from sklearn.metrics import mean_squared_error, mean_absolute_error

# pt acuratete, calc mean sq err si mean abs err
# media scorului pe cele 3 validari (estimare perf 3 folduri)

# 1
def normalize_data(train_data,test_data):
    # luata din lab trecut, standardizare
    scaler = preprocessing.StandardScaler()
    scaler.fit(train_data)
    train_data = scaler.transform(train_data)
    test_data = scaler.transform(test_data)
    return train_data,test_data


# load training data
training_data = np.load('training_data.npy')
prices = np.load('prices.npy')
print('The first 4 samples are:\n ', training_data[:4])
print('The first 4 prices are:\n ', prices[:4])
training_data, prices = shuffle(training_data, prices, random_state=0)

# definirea modelelor
lasso_model = Lasso()

# 2
kf = KFold(n_splits=3,random_state=42,shuffle=True)
mse = []
mae = []
for train_index,test_index in kf.split(training_data):
    print("Train index: ", train_index, "Test index: ", test_index)
    X_train, X_test, Y_train, Y_test = training_data[train_index], training_data[test_index], prices[train_index], prices[test_index]
    X_train,X_test = normalize_data(X_train,X_test)
    linear_regression_model = LinearRegression()
    linear_regression_model.fit(X_train,Y_train)
    predictions = linear_regression_model.predict(X_test)
    mse.append(mean_squared_error(Y_test, predictions))
    mae.append(mean_absolute_error(Y_test, predictions))
print("Mean mse: ", np.mean(mse))
print("Mean mae: ", np.mean(mae))

# 3
# asemanator cu ex 2
kf = KFold(n_splits=3,random_state=42,shuffle=True)
alphas = [1., 10., 100., 1000.]
mse_dict = {}
mae_dict = {}
for train_index,test_index in kf.split(training_data):
    print("Train index: ", train_index, "Test index: ", test_index)
    X_train, X_test, Y_train, Y_test = training_data[train_index], training_data[test_index], prices[train_index], prices[test_index]
    # tot normalizare standard
    X_train,X_test = normalize_data(X_train,X_test)

    for alpha in alphas:
        linear_regression_model = Ridge(alpha=alpha)
        linear_regression_model.fit(X_train,Y_train)
        predictions = linear_regression_model.predict(X_test)

        if alpha not in mse_dict:
            mse_dict[alpha] = [mean_squared_error(Y_test, predictions)]
        else:
            mse_dict[alpha].append(mean_squared_error(Y_test, predictions))

        if alpha not in mae_dict:
            mae_dict[alpha] = [mean_absolute_error(Y_test, predictions)]
        else:
            mae_dict[alpha].append(mean_absolute_error(Y_test, predictions))

for alpha in alphas:
    print("Alpha: ", alpha, "Mean mse: ", np.mean(mse_dict[alpha]), "\n")
    print("Alpha: ", alpha, "Mean mae: ", np.mean(mae_dict[alpha]), "\n")

# 4
# importanta atributelor e proportionala cu abs(w) => cm semnif are coef cel mai mare
# aici este atr 0, adica anul fabricatiei
ridge_model = Ridge(alpha=10)
X_train, _ = normalize_data(training_data, training_data)
ridge_model.fit(X_train, prices)
print(ridge_model.coef_)
print(ridge_model.intercept_)