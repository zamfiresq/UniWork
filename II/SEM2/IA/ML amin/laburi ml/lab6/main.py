# n-ul ciudat = eta
# y hat - yt = gradient
# gradientul da directia spre maxim, dar noi vrem sa minimizam deci il scadem
# W - vector de ponderi

import numpy as np
import matplotlib.pyplot as plt
from sklearn.utils import shuffle

def compute_y(x, W, bias):
    # dreapta de decizie
    # [x, y] * [W[0], W[1]] + b = 0
    return (-x * W[0] - bias) / (W[1] + 1e-10)
def plot_decision_boundary(X, y , W, b, current_x, current_y):
    x1 = -0.5
    y1 = compute_y(x1, W, b)
    x2 = 0.5
    y2 = compute_y(x2, W, b)
    # sterge continutul ferestrei
    plt.clf()
    # ploteaza multimea de antrenare
    color = 'r'
    if(current_y == -1):
        color = 'b'
    plt.ylim((-1, 2))
    plt.xlim((-1, 2))
    plt.plot(X[y == -1, 0], X[y == -1, 1], 'b+')
    plt.plot(X[y == 1, 0], X[y == 1, 1], 'r+')
    # ploteaza exemplul curent
    plt.plot(current_x[0], current_x[1], color+'s')
    # afisarea dreptei de decizie
    plt.plot([x1, x2] ,[y1, y2], 'black')
    plt.show(block=False)
    plt.pause(0.3)

# 2
def widrow_hoff(x_in, y_in, num_epochs, learning_rate):
    w = np.zeros(2)
    b = 0
    for epoch in range(num_epochs):
        p = np.random.permutation(x_in.shape[0])
        x_in = x_in[p]
        y_in = y_in[p]
        for i in range(x_in.shape[0]):
            y_hat = np.dot(w, x_in[i]) + b
            loss = ((y_hat - y_in[i]) ** 2) / 2
            w = w - learning_rate * (y_hat - y_in[i]) * x_in[i]
            b = b - learning_rate * (y_hat - y_in[i])
            plot_decision_boundary(x_in, y_in, w, b, x_in[i], y_in[i])

# aici lipseste ceva probabil

x = np.array([[0, 0], [0, 1], [1, 0], [1, 1]])
y = np.array([-1, 1, 1, 1])
widrow_hoff(x, y, 70, 0.1)

# 3
x = np.array([ [0, 0], [0, 1], [1, 0], [1, 1] ])
y = [-1, 1, 1, -1]
widrow_hoff(x, y, 70, 0.1)

# 4
num_hidden_neurons = 5
miu = 0
sigma = 1
# generam aleator matr ponderilor stratului ascuns (2-dim_date_intrare, num_hidden_neurons)
W_1 = np.random.normal(size=(2, num_hidden_neurons), loc=miu, scale=sigma)
b_1 = np.zeros(num_hidden_neurons) # init bias
# generam aleator matr ponderilor stratului de iesire (num_hidden_neurons - nr_neuroni_de_p ???
W_2 = np.random.normal(size=(num_hidden_neurons, 1), loc=miu, scale=sigma)
b_2 = np.zeros(1) # init bias

x = np.array([[0, 0], [0, 1], [1, 0], [1, 1]])
y = np.array([[0], [1], [1], [0]])
epochs = 70
learning_rate = 0.5
for i in range(epochs):
    plot_decision(x, W_1, W_2, b_1, b_2)
    p = np.random.permutation(x.shape[0])
    x = x[p]
    y = y[p]
    z_1, a_1, z_2, a_2 = forward(x, W_1, b_1, W_2, b_2)
    loss = (-y * np.log(a_2) - (1-y) * np.log(1-a_2)).mean()
    y_pred = np.round(a_2)
    accuracy = (y_pred==y).mean()
    dw1, db1, dw2, db2 = backward(a_1, a_2, z_1, W_2, x, y, x.shape[0])
    W_1 = learning_rate * dw1
    W_2 = learning_rate * dw2
    b_1 = learning_rate * db1
    b_2 = learning_rate * db2

    print("Loss: ", loss, "Accuracy: ", accuracy)

# asta e tot ce am rip
