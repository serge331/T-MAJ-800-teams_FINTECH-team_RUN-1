import sys
import pandas as pd
import json
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import accuracy_score

def load_data(file_path):
    try:
        data = pd.read_csv(file_path, sep=',')
        return data
    except FileNotFoundError:
        print("File not found.")
        return None

def preprocess_data(data):
    try:
        data['Vitesse'] = data['Vitesse'].apply(lambda x: json.loads(x))
        data['Pluie'] = data['Pluie'].apply(lambda x: json.loads(x))
        data = pd.concat([data.drop(['Vitesse', 'Pluie'], axis=1), data['Vitesse'].apply(pd.Series), data['Pluie'].apply(pd.Series)], axis=1)
        return data
    except KeyError:
        print("Missing columns in the dataset.")
        return None

def train_model(X, y):
    try:
        X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)
        model = LogisticRegression()
        model.fit(X_train, y_train)
        return model, X_test, y_test
    except ValueError:
        print("Invalid data for training the model.")
        return None, None, None

def evaluate_model(model, X_test, y_test):
    try:
        y_pred = model.predict(X_test)
        accuracy = accuracy_score(y_test, y_pred)
        return accuracy
    except AttributeError:
        print("Invalid model for evaluation.")
        return None

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("Please provide the file path as a command-line argument.")
    else:
        # Get the file path from the command-line argument
        file_path = sys.argv[1]

        # Load the data
        data = load_data(file_path)

        if data is not None:
            # Preprocess the data
            preprocessed_data = preprocess_data(data)

            if preprocessed_data is not None:
                # Split data into features (X) and target (y)
                X = preprocessed_data.drop('Accident', axis=1)
                y = preprocessed_data['Accident']

                # Train the model
                model, X_test, y_test = train_model(X, y)

                if model is not None:
                    # Evaluate the model
                    accuracy = evaluate_model(model, X_test, y_test)

                    if accuracy is not None:
                        print(accuracy)
