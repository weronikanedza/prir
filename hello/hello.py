import time

from sklearn import preprocessing
from sklearn.metrics import accuracy_score
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.neighbors import KNeighborsClassifier
import csv
import timeit


def prepareDta(row):
    for i in range(len(row)):
        if row[i]=="a":
            row[i]=1
        if row[i] == "b":
            row[i] = 2
        if row[i] == "c":
            row[i] = 3
        if row[i] == "d":
            row[i] = 4
        if row[i] == "e":
            row[i] = 5
        if row[i] == "f":
            row[i] = 6
        if row[i] == "g":
            row[i] = 7
        if row[i] == "h":
             row[i] = 8


def readData():
    with open('krkopt.csv') as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        X=[]
        Y=[]
        for row in csv_reader:
            prepareDta(row)
            Y.append(row.pop())
            X.append(row)
        return [X,Y]


X,Y = readData()

start = time.time()
normalized_X = preprocessing.normalize(X)
end = time.time()

print ('normalzation : ' , end-start)

start = time.time()
scaler = StandardScaler()
standarized_X = scaler.fit_transform(X)
end = time.time()
print ('standarization : ' , end-start)


start = time.time()
X_train, X_test, y_train, y_test = train_test_split(X, Y, random_state=1)
knn = KNeighborsClassifier(n_neighbors=3, metric='euclidean',algorithm="kd_tree")
knn.fit(X_train, y_train)
y_pred = knn.predict(X_test)
end = time.time()
print ('knn : ' , end-start)
print('accuracy', accuracy_score(y_test, y_pred))
